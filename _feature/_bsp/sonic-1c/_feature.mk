MCU_CHIP	 	= gd32f30x
MCU_CORE     	= cortex-m4
MCU_FLOAT    	= soft
CORTEX_VER   	= $(ENV_CORTEX_VER)
OPENOCD_TARGET 	= $(MCU_CHIP)

CFLAGS_COMMON += -Wno-address-of-packed-member
CFLAGS_COMMON += -fshort-enums -fsigned-char -mlittle-endian -mthumb -mthumb-interwork -mcpu=$(MCU_CORE) -mfloat-abi=$(MCU_FLOAT)
CFLAGS_COMMON += -DBRISCITS_FLOAT=1 -DGD32F30x=1 -DGD32F30X_XD=1
CFLAGS_COMMON += -DSERIAL_NO_BASE_ADDRESS=0x1FFFF7E8

CFLAGS_COMMON += -DFEATURE_MODBUS_MASTER_PORT_0=RS485_UART_0 
CFLAGS_COMMON += -DFEATURE_MODBUS_MASTER_DIR_0=gpio_rs485_dir_0
CFLAGS_COMMON += -DFEATURE_MODBUS_MASTER_BAUD_0=115200

CFLAGS_COMMON += -DFEATURE_MODBUS_MASTER_PORT_1=RS485_UART_1
CFLAGS_COMMON += -DFEATURE_MODBUS_MASTER_DIR_1=gpio_rs485_dir_1
CFLAGS_COMMON += -DFEATURE_MODBUS_MASTER_BAUD_1=115200

CFLAGS_COMMON += -DDISCO_REFRESH_PERIOD=1000*15
CFLAGS_COMMON += -DMIN_DISCO_DELAY=64				# Minimum discovery delay
CFLAGS_COMMON += -DMAX_DISCO_DELAY=250				# Maximum discovery delay
CFLAGS_COMMON += -Dgpio_rs485_dir=gpio_rs485_dir_0

CFLAGS_COMMON += -DUSART_QUEUE_SZ=128

CFLAGS_COMMON += -DDEBUG_UART=3 		-DDEBUG_SPEED_DEF=UART_BAUD_115200
CFLAGS_COMMON += -DRS485_UART_0=1 		-DRS485_SPEED_0_DEF=UART_BAUD_115200
CFLAGS_COMMON += -DRS485_UART_1=2 		-DRS485_SPEED_1_DEF=UART_BAUD_115200
CFLAGS_COMMON += -DRS485_UART=RS485_UART_0

CFLAGS_COMMON += -DBRISCITS_TEST_VECTOR_BOUNDS=1
CFLAGS_COMMON += -DMODBUS_SLAVE_ID=2

CFLAGS_COMMON += -DENC28J60_PRESCALER=SPI_PSC_2			# (60/4) = 15MHz
CFLAGS_COMMON += -DMICROSD_PRESCALER=SPI_PSC_4			# (60/4) = 15MHz

CFLAGS_COMMON += -DXDUC_ARM_DELAY_MS=10
CFLAGS_COMMON += -DMEASURE_PERIOD=250

CFLAGS_COMMON += -DUSDELAY_FACTOR=11
CFLAGS_COMMON += -DFEATURE_DELAY=64

CFLAGS_COMMON += -DMICROSD_SPI=SPI2

CFLAGS_COMMON += -DPINTRIGGER_IRQ=EXTI5_9_IRQn
CFLAGS_COMMON += -DPINTRIGGER_LINE=EXTI_6
CFLAGS_COMMON += -DPINTRIGGER_EDGE=EXTI_TRIG_FALLING

# Serial SRAM 120 MHz Bus SPI0
CFLAGS_COMMON += -DSRAM_PRESCALER=SPI_PSC_8				# (120/8) = 15MHz
CFLAGS_COMMON += -DSRAM_SPI=SPI0
CFLAGS_COMMON += -DSRAM_DMA=DMA0
CFLAGS_COMMON += -DSRAM_DMA_IRQ=DMA0_Channel2_IRQn
CFLAGS_COMMON += -DSRAM_DMA_CHANNEL_RX=DMA_CH1
CFLAGS_COMMON += -DSRAM_DMA_CHANNEL_TX=DMA_CH2
CFLAGS_COMMON += -DPATTERN_BUFFER_SZ=32

# XDUC ADC DMA
CFLAGS_COMMON += -DXDUC_ADC_TIM_TRIGGER=ADC0_1_EXTTRIG_REGULAR_T3_CH3
CFLAGS_COMMON += -DXDUC_DMA_DEV=DMA0 
CFLAGS_COMMON += -DXDUC_DMA_CH=DMA_CH0 
CFLAGS_COMMON += -DXDUC_DMA_IRQ=DMA0_Channel0_IRQn
CFLAGS_COMMON += -DXDUC_ADC_DEV=ADC0 
CFLAGS_COMMON += -DXDUC_ADC_CHAN=ADC_CHANNEL_8
CFLAGS_COMMON += -DXDUC_ADC_TIM_BASE_HZ=60000000
CFLAGS_COMMON += -DXDUC_ADC_TIM=TIMER3
CFLAGS_COMMON += -DXDUC_ADC_TIM_CH=TIMER_CH_3
# ADC Sample buffer must be even multiples of 1024
# Samples are 16-bit words. This size will be divided
# into two buffers for operation in double buffer 
# streaming mode
CFLAGS_COMMON += -DXDUC_ADC_SAMPLE_SZ=2048  		   	# 1K * 2

#
# @FIXME - clock is running too fast
#
# CFLAGS_COMMON += -DPIEZO_RX_XDUC_SAMP_HZ=500000		# Sample Freq
CFLAGS_COMMON += -DPIEZO_RX_XDUC_SAMP_HZ=250000			# Sample Freq

CFLAGS_COMMON += -DDEFAULT_XDUC_RX_GAIN=11
CFLAGS_COMMON += -DDEFAULT_XDUC_TX_POWER=85
CFLAGS_COMMON += -DDEFAULT_XDUC_TX_DURATION=16

CFLAGS_COMMON += -DBTN0_POLARITY=true
CFLAGS_COMMON += -DLED0_POLARITY=true
CFLAGS_COMMON += -DBLINK_RATE_LO=125
CFLAGS_COMMON += -DBLINK_RATE_HI=64

CFLAGS_COMMON += -DBOOT_LOADER=\"LOADER.S19\"
CFLAGS_COMMON += -DBOOT_FIRMWARE=\"FIRMWARE.S19\"
CFLAGS_COMMON += -DBOOT_ARMED_TIMEOUT=4000

CFLAGS_COMMON += -DBOOT_LOAD_ADDR_BASE=0x20000000
CFLAGS_COMMON += -DBOOT_LOAD_ADDR_TOP=0x2000FFFF

CFLAGS_COMMON += -DBOOSTRAP_DEBUG=0

CFLAGS_COMMON += -DHEAP_BLOCK_SIZE=32

CFLAGS_COMMON += -DWAVESTORE_DEPTH=32
CFLAGS_COMMON += -DWAVESTORE_WIDTH=500

CFLAGS_COMMON += -DDEFAULT_XFER_PAGE_SIZE=100
CFLAGS_COMMON += -DDEFAULT_XFER_START_TIMEOUT=10000
CFLAGS_COMMON += -DDEFAULT_XFER_WAIT_TIMEOUT=5000

CFLAGS_COMMON += -DBRISCITS_THREAD_DEF_STKSZ=1024
CFLAGS_COMMON += -DBRISCITS_THREAD_NORMALPRIO=1

CFLAGS_COMMON += -DPRODUCT_PROTOCOL_SNMP_ENABLED=1
CFLAGS_COMMON += -DPRODUCT_IF_NAME=\"ei\"
CFLAGS_COMMON += -DPRODUCT_HTTP_SERVER_STK_SZ=1024
CFLAGS_COMMON += -DPRODUCT_HTTP_THREAD_STK_SZ=\(1024*4\)
CFLAGS_COMMON += -DPRODUCT_FTP_SERVER_STK_SZ=1024
CFLAGS_COMMON += -DPRODUCT_FTP_THREAD_STK_SZ=\(1024*4\)
CFLAGS_COMMON += -DPRODUCT_HTTP_SERVER_NAME=\"httpd\"
CFLAGS_COMMON += -DPRODUCT_HTTP_THREAD_PRIO=1
CFLAGS_COMMON += -DPRODUCT_HTTPD_WD_COUNT=100
CFLAGS_COMMON += -DPRODUCT_HTTP_SEND_BUFFER_SZ=1024
CFLAGS_COMMON += -DPRODUCT_HTTP_PORT=80
CFLAGS_COMMON += -DPRODUCT_HTTP_BACKLOG=16
CFLAGS_COMMON += -DPRODUCT_HTTP_SESSION_NAME=\"http\" 
CFLAGS_COMMON += -DPRODUCT_HTTP_SESSION_PRIO=1
CFLAGS_COMMON += -DPRODUCT_HTTP_WD_COUNT=100
CFLAGS_COMMON += -DPRODUCT_I2CSPEED=30
CFLAGS_COMMON += -DPRODUCT_HTTP_ROOT=\"/\"
CFLAGS_COMMON += -DPRODUCT_EEPROM_BPP=16
CFLAGS_COMMON += -DPRODUCT_HOSTNAME=\"sonic\"
CFLAGS_COMMON += -DPRODUCT_VERSION=\"0.1\"
CFLAGS_COMMON += -DPRODUCT_DHCP_THREAD_STACK_SZ=1024
CFLAGS_COMMON += -DPRODUCT_DHCP_THREAD_PRIORITY=1
CFLAGS_COMMON += -DENC28J60_SPI=SPI1
CFLAGS_COMMON += -DENC28J60_USE_DMA=0
CFLAGS_COMMON += -DENC28J60_MAX_PACKET=1500
CFLAGS_COMMON += -DPRODUCT_ETHIF_THREAD_STK_SZ=1024
CFLAGS_COMMON += -DPRODUCT_ETHIF_THREAD_PRIO=1
CFLAGS_COMMON += -DPRODUCT_ETHIN_WD_COUNT=100
CFLAGS_COMMON += -DPRODUCT_DEBUG_SETTINGS=1
CFLAGS_COMMON += -DPRODUCT_THREAD_NORMAL_PRIO=1
CFLAGS_COMMON += -DETH_IRQn=EXTI5_9_IRQn

CFLAGS_COMMON += -DPIEZO_ADC_DEVICE=ADC0 					# XDUC Analog Input Device
CFLAGS_COMMON += -DPIEZO_RX_ADC_CHANNEL_X=HW_ADC_CHANNEL_8	# XDUC Analog IN

CFLAGS_COMMON += -DHW_ADC_DMA=DMA0					# ADC DMA Controller 
CFLAGS_COMMON += -DHW_ADC_DMA_CH=DMA_CH0			# ADC DMA Channel 
CFLAGS_COMMON += -DHW_ADC_DMA_CNT=18				# ADC DMA Channel Count

CFLAGS_COMMON += -DVREF_ADC=ADC0
CFLAGS_COMMON += -DVREF_ADC_CH=15					# -2 for regular sequnce
CFLAGS_COMMON += -DVREF_ADC_CH_TEMPC=14				# -2hw_adc
CFLAGS_COMMON += -DVREF_V=2.4f

CFLAGS_COMMON += -DPRODUCT_HAS_BUS_SWITCHED=1		# relay switches bus power

# sources
include ${SRC_ROOT}/_bsp/${TARGET}/_src.mk

include ${SRC_ROOT}/filesystem/_src.mk
