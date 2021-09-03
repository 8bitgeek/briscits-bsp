#include <ff.h>
#include <filesystem.h>

#define PERIOD  400     // ms

typedef struct _filesystem_t_
{
  uint32_t              jiffies;
  uint32_t              sustained;
  bool                  is_media;
  bool                  is_mounted;
  FATFS                 filesystem;
  filesystem_callback_t callback;
} filesystem_t;

filesystem_t filesystem;

void filesystem_setup(filesystem_callback_t callback)
{
  filesystem.sustained = 0;
  filesystem.jiffies = caribou_state.jiffies;
  filesystem.callback = callback;
}

bool filesystem_is_media(void)
{
  return filesystem.is_media;
}

bool filesystem_is_mounted(void)
{
  return filesystem.is_mounted;
}

void filesystem_service(void)
{
  bool is_media_now = !hw_gpio_state(&gpio_microsd_cd);
  uint32_t now = caribou_state.jiffies;
  uint32_t delta = now - filesystem.jiffies;
  filesystem.jiffies = now;

  if (is_media_now) {
    filesystem.sustained += delta;
    if (PERIOD <= filesystem.sustained) {
      if (!filesystem.is_mounted) {
        filesystem.is_mounted = (f_mount(&filesystem.filesystem, "", 0) == FR_OK);
        filesystem.sustained = 0;
        if ( filesystem.callback != NULL )
          filesystem.callback();
      }
    }
  } else {
    filesystem.sustained = 0;
    if (filesystem.is_mounted && filesystem.is_media) {
      filesystem.is_mounted = !(f_mount(NULL, "", 0) == FR_OK);
        if ( filesystem.callback != NULL )
          filesystem.callback();
    }
  }
  filesystem.is_media = is_media_now;
}
