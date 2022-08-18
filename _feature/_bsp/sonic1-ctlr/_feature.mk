MCU_CHIP	 	= stm32f10x
MCU_CORE     	= cortex-m3
MCU_FLOAT    	= softfp
CORTEX_VER   	= $(ENV_CORTEX_VER)
OPENOCD_TARGET 	= stm32f1x

# Xtal / PLL
CFLAGS_COMMON += -DHXTAL_VALUE=6250000				
CFLAGS_COMMON += -DHSE_PLLMUL=11											# 11 * 6.25Mhz = 68.75MHz PLL
CFLAGS_COMMON += -DHSI_PLLMUL=16											# 16 * 4Mhz = 64MHz PLL
CFLAGS_COMMON += -DNO_SYSTEM_INIT=1											# Don't call the SystemInit() fn.

CFLAGS_COMMON += -Wno-address-of-packed-member
CFLAGS_COMMON += -DSERIAL_NO_BASE_ADDRESS=0x1FFFF7E8
CFLAGS_COMMON += -fshort-enums -fsigned-char -mlittle-endian 
CFLAGS_COMMON += -mthumb -mthumb-interwork -mcpu=$(MCU_CORE) -mfloat-abi=$(MCU_FLOAT)
CFLAGS_COMMON += -DUSE_STDPERIPH_DRIVER=1
CFLAGS_COMMON += -DGD32F10X_HD=1
CFLAGS_COMMON += -DETH_IRQn=EXTI9_5_IRQn
CFLAGS_COMMON += -DETH_LINE=EXTI_Line8
CFLAGS_COMMON += -DLED0_POLARITY=true
CFLAGS_COMMON += -DLED1_POLARITY=true
CFLAGS_COMMON += -DBTN0_POLARITY=true
CFLAGS_COMMON += -DBTN1_POLARITY=true
CFLAGS_COMMON += -DUSDELAY_FACTOR=6
CFLAGS_COMMON += -DFEATURE_DELAY=64
CFLAGS_COMMON += -DLOCAL_OPTIMIZATION=1

# BRISCITS
# CFLAGS_COMMON += -DUNBUFFERED_STDERR=1
CFLAGS_COMMON += -DUSE_NATIVE_STDARG=1
CFLAGS_COMMON += -DBRISCITS_POSIX_STDIO=1
CFLAGS_COMMON += -DUSART_QUEUE_SZ=64
CFLAGS_COMMON += -DDEBUG_UART=0
CFLAGS_COMMON += -DRS485_UART_0=1
CFLAGS_COMMON += -DDEBUG_SPEED_DEF=UART_BAUD_115200
CFLAGS_COMMON += -DRS485_SPEED_0_DEF=UART_BAUD_115200

# MICROSD
CFLAGS_COMMON += -DSD_CLK_DIV_TRANS=6										# SD clock division in transmission phase default: 3
CFLAGS_COMMON += -DSD_CLK_DIV_INIT=127										# SD clock division in initilization phase default: 255
CFLAGS_COMMON += -DMICROSD_SDIO=1
CFLAGS_COMMON += -DMICROSD_SDIO_DMA=DMA1
CFLAGS_COMMON += -DMICROSD_SDIO_DMA_CH=DMA_CH3
CFLAGS_COMMON += -DBOARD_IDLE_DISKIO=1
CFLAGS_COMMON += -DMICROSD_PRESCALER=SPI_PSC_4								# (68.75/4) = 17.1875MHz

# Ethernet
CFLAGS_COMMON += -DENC28J60_USE_DMA=1
CFLAGS_COMMON += -DENC28J60_DMA=DMA0										# DMA Controller 
CFLAGS_COMMON += -DENC28J60_SPI=SPI1
CFLAGS_COMMON += -DENC28J60_DMA_CHANNEL_TX=DMA_CH4
CFLAGS_COMMON += -DENC28J60_DMA_CHANNEL_RX=DMA_CH3
CFLAGS_COMMON += -DENC28J60_MAX_PACKET=1500
CFLAGS_COMMON += -DENC28J60_SPI_MODE=SPI_CTL0_MSTMOD						# Master / Slave mode
CFLAGS_COMMON += -DENC28J60_SPI_NSS=\(SPI_CTL0_SWNSSEN\|SPI_CTL0_SWNSS\)	# Slave Select mode
CFLAGS_COMMON += -DENC28J60_SPI_PRESCALER=SPI_PSC_2							# ((68.75/2) = 34.375) / 2 = 17.1875MHz
CFLAGS_COMMON += -DIP_FRAG_MAX_MTU=1514
CFLAGS_COMMON += -DENC28J60_MAXFRAME=IP_FRAG_MAX_MTU
CFLAGS_COMMON += -DPRODUCT_HOSTNAME=\"sonic\"
CFLAGS_COMMON += -DPRODUCT_DHCP_THREAD_STACK_SZ=1024
CFLAGS_COMMON += -DPRODUCT_DHCP_THREAD_PRIORITY=1
CFLAGS_COMMON += -DPRODUCT_ETHIF_THREAD_STK_SZ=1024
CFLAGS_COMMON += -DPRODUCT_ETHIF_THREAD_PRIO=1
CFLAGS_COMMON += -DPRODUCT_ETHIN_WD_COUNT=100
CFLAGS_COMMON += -DENC28J60_TX_BUFS=6										# Number of transmitter buffers
CFLAGS_COMMON += -DENC28J60_RX_BUFS=6										# Number of receiver buffers

# Modbus RTU
CFLAGS_COMMON += -DFEATURE_MODBUS_MASTER_PORT_0=RS485_UART_0
CFLAGS_COMMON += -DFEATURE_MODBUS_MASTER_DIR_0=gpio_rs485_dir_0
CFLAGS_COMMON += -DFEATURE_MODBUS_MASTER_BAUD_0=115200
CFLAGS_COMMON += -DDISCO_REFRESH_PERIOD=1000*15
CFLAGS_COMMON += -DMIN_DISCO_DELAY=10										# Minimum discovery delay
CFLAGS_COMMON += -DMAX_DISCO_DELAY=64										# Maximum discovery delay

# Serial SRAM 
CFLAGS_COMMON += -DSRAM_PRESCALER=SPI_PSC_4									# (68.75/4) = 17.1875MHz
CFLAGS_COMMON += -DSRAM_SPI=SPI0
CFLAGS_COMMON += -DSRAM_DMA=DMA0
CFLAGS_COMMON += -DSRAM_DMA_IRQ=DMA0_Channel2_IRQn
CFLAGS_COMMON += -DSRAM_DMA_CHANNEL_RX=DMA_CH1
CFLAGS_COMMON += -DSRAM_DMA_CHANNEL_TX=DMA_CH2
CFLAGS_COMMON += -DSRAM_DMA_RX_IFCR=\(DMA_IFCR_CGIF2\|DMA_IFCR_CTCIF2\|DMA_IFCR_CHTIF2\|DMA_IFCR_CTEIF2\)
CFLAGS_COMMON += -DSRAM_DMA_TX_IFCR=\(DMA_IFCR_CGIF3\|DMA_IFCR_CTCIF3\|DMA_IFCR_CHTIF3\|DMA_IFCR_CTEIF3\)
CFLAGS_COMMON += -DSRAM_DMA_RX_TC=DMA_ISR_TCIF3
CFLAGS_COMMON += -DSRAM_DMA_TX_TC=DMA_ISR_TCIF3
CFLAGS_COMMON += -DPATTERN_BUFFER_SZ=32
CFLAGS_COMMON += -DRAM_SIZE_BYTES=32768

# ADC DMA 
CFLAGS_COMMON += -DHW_ADC=ADC0												# ADC Controller 
CFLAGS_COMMON += -DHW_ADC_DMA=DMA0											# ADC DMA Controller 
CFLAGS_COMMON += -DHW_ADC_DMA_CH=DMA_CH0									# ADC DMA Channel 
CFLAGS_COMMON += -DHW_ADC_DMA_CNT=16										# ADC DMA Channel Count
CFLAGS_COMMON += -DHW_ADC_TIM=TIMER0										# ADC Timer
CFLAGS_COMMON += -DHW_ADC_TIM_CH=0											# ADC Timer Channel
CFLAGS_COMMON += -DXDUC_ADC_TIM_BASE_HZ=SystemCoreClock

# EXTSEL Bits: Timer 2 CC2
# CFLAGS_COMMON += -DHW_ADC_INJECT_MASK=\(ADC_CR2_JEXTSEL_1\|ADC_CR2_JEXTSEL_0\)
CFLAGS_COMMON += -DHW_ADC_INJECT_MASK=CTL1_ETSIC\(3\)

CFLAGS_COMMON += -DHW_XDUC_DMA_ADC_CHAN=8									# XDUC ADC CHAN
CFLAGS_COMMON += -DXDUC_DMA_IRQ=DMA1_Channel1_IRQn
# ADC Sample buffer must be even multiples of 1024
# Samples are 16-bit words. This size will be divided
# into two buffers for operation in double buffer 
# streaming mode
CFLAGS_COMMON += -DXDUC_ADC_SAMPLE_SZ=2048  								# 1K * 2
CFLAGS_COMMON += -DHW_ADC_SAMPLETIME=ADC_SAMPLETIME_13POINT5				# ADC Channel Sample Time

# Enable timer outputs on LED 
# outputs instead of GPIO 
CFLAGS_COMMON += -DTIMER3_BUS_HZ=SystemCoreClock
CFLAGS_COMMON += -DHW_DAC_PWM_BUS_HZ=TIMER3_BUS_HZ
CFLAGS_COMMON += -DHW_DAC_PWM_TIM=TIMER3
CFLAGS_COMMON += -DHW_DAC_PWM_CH0=PWM_CHANNEL_3
CFLAGS_COMMON += -DHW_DAC_PWM_CH1=PWM_CHANNEL_4
CFLAGS_COMMON += -DHW_DAC_PWM_HZ=300000
CFLAGS_COMMON += -DHW_DAC_PWM_CK=36000000

CFLAGS_COMMON += -DPRODUCT_PROTOCOL_SNMP_ENABLED=0
CFLAGS_COMMON += -DPRODUCT_IF_NAME=\"ei\"
CFLAGS_COMMON += -DPRODUCT_HTTP_SERVER_STK_SZ=1024
CFLAGS_COMMON += -DPRODUCT_HTTP_THREAD_STK_SZ=\(1024*4\)
CFLAGS_COMMON += -DPRODUCT_FTP_SERVER_STK_SZ=1024
CFLAGS_COMMON += -DPRODUCT_FTP_THREAD_STK_SZ=\(1024*3\)
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
CFLAGS_COMMON += -DPRODUCT_VERSION=\"0.1\"
CFLAGS_COMMON += -DPRODUCT_DEBUG_SETTINGS=1
CFLAGS_COMMON += -DPRODUCT_THREAD_NORMAL_PRIO=1

# sources
include ${SRC_ROOT}/_bsp/${TARGET}/_src.mk
