MCU_CHIP	 	= stm32f0xx
MCU_CORE     	= cortex-m0
MCU_FLOAT    	= softfp
CORTEX_VER   	= $(ENV_CORTEX_VER)
OPENOCD_TARGET 	= stm32f0x

# LIBS += $(GCC_ROOT)$(GCC_LIB)/thumb/$(CORTEX_VER)/nofp/libgcc.a
# LIBS += $(GCC_ROOT)$(GCC_LIB)/../../../../arm-none-eabi/lib/thumb/$(CORTEX_VER)/nofp/libm.a
# LIBS += $(GCC_ROOT)$(GCC_LIB)/../../../../arm-none-eabi/lib/thumb/$(CORTEX_VER)/nofp/libstdc++_nano.a

CFLAGS_COMMON += -DDEBUG_UART=0 -DRS485_UART=1
CFLAGS_COMMON += -DUSART_QUEUE_SZ=64 -DHSE_VALUE=8000000U -DCARIBOU_FLOAT=1 -DSTM32F091xx=1
CFLAGS_COMMON += -DSERIAL_NO_BASE_ADDRESS=0x1FFFF7AC
CFLAGS_COMMON += -fshort-enums -fsigned-char -mlittle-endian -mthumb -mthumb-interwork -mcpu=$(MCU_CORE) -mfloat-abi=$(MCU_FLOAT)

CFLAGS_COMMON += -DLED0_POLARITY=false
CFLAGS_COMMON += -DLED1_POLARITY=false
CFLAGS_COMMON += -DLED2_POLARITY=false

CFLAGS_COMMON += -DTIM_OUT_IRQ=TIM1_BRK_UP_TRG_COM_IRQn
CFLAGS_COMMON += -DTIM1_BUS_HZ=48000000				# Timer Reference Frequency
CFLAGS_COMMON += -DTIM2_BUS_HZ=48000000				# Timer Reference Frequency
CFLAGS_COMMON += -DTIM_TRIGGER=TIM15				# Edge-trigger timer (CH1 Only)
CFLAGS_COMMON += -DTIM_OUT=TIM1						# Waveform output timer
CFLAGS_COMMON += -DTIM_OUT_CHAN=TX_GEN_CHANNEL_1	# Wafeform output channel (TXP)
# CFLAGS_COMMON += -DTIM_OUT_CHAN=TX_GEN_CHANNEL_2	# Wafeform output channel (TIM_TEST0)
CFLAGS_COMMON += -DTIM_OUT_BUS_HZ=TIM1_BUS_HZ		# Output waveform timer reference frquency
CFLAGS_COMMON += -DHW_TIM_TX_FREQ=6000000			# TX Timer Frequency
CFLAGS_COMMON += -DHW_TIM_RX_FREQ=6000000			# RX Timer Frequency

CFLAGS_COMMON += -DTIM_IN=TIM2						# Waveform output timer
CFLAGS_COMMON += -DTIM_IN_CHAN=RX_GEN_CHANNEL_4		# Waveform output channel
CFLAGS_COMMON += -DTIM_IN_BUS_HZ=TIM2_BUS_HZ		# Output waveform timer reference frquency 

CFLAGS_COMMON += -DPIEZO_MAX_DAC_PWR=0x0AFF
CFLAGS_COMMON += -DPIEZO_TX_XDUC_POWER=90.0f
CFLAGS_COMMON += -DPIEZO_TX_XDUC_HZ=50000			# Transducer frequency
CFLAGS_COMMON += -DPIEZO_TX_XDUC_CYCLES=8			# Number of cycles in a chirp
CFLAGS_COMMON += -DXDUC_BAUD_RATE=115200
CFLAGS_COMMON += -DXDUC_ARM_DELAY_MS=10
CFLAGS_COMMON += -DXDUC_TIMEOUT_MS=50
CFLAGS_COMMON += -DXDUC_HEARTBEAT_MS=50
CFLAGS_COMMON += -DMODBUS_SLAVE_ID=2				# Default Slave ID

CFLAGS_COMMON += -DMCP6S92_SPI=SPI2
CFLAGS_COMMON += -DMCP6S92_SPI_PRESCALER=\(SPI_CR1_BR_2\|SPI_CR1_BR_2\)		# (48/64) = 0.75MHz
CFLAGS_COMMON += -DSPI_DATASIZE_8BIT=\(SPI_CR2_DS_2\|SPI_CR2_DS_1\|SPI_CR2_DS_0\)

CFLAGS_COMMON += -DPRODUCT_VERSON_WORD=0x0101
CFLAGS_COMMON += -DPRODUCT_HEARTBEAT_PERIOD=100
CFLAGS_COMMON += -DMODBUS_THREAD_STK_SZ=2048

# sources
include ${SRC_ROOT}/_bsp/${TARGET}/_src.mk
