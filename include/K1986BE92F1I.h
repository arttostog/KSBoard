#pragma once

typedef unsigned long bit_depth_t;

/*
    Производственная информация
*/

#define UNIQ_ID_1 (*((const volatile bit_depth_t*) 0x08000FF0))
#define UNIQ_ID_2 (*((const volatile bit_depth_t*) 0x08000FE0))
#define UNIQ_ID_3 (*((const volatile bit_depth_t*) 0x08000FD0))
#define UNIQ_ID_4 (*((const volatile bit_depth_t*) 0x08000FC0))
#define UNIQ_ID_5 (*((const volatile bit_depth_t*) 0x08000FB0))

#define LDO_TRIM (*((const volatile bit_depth_t*) 0x08000FA0) & 7)
#define HSI_TRIM (*((const volatile bit_depth_t*) 0x08000F90) & 63)
#define LSI_TRIM (*((const volatile bit_depth_t*) 0x08000F80) & 31)

/*
    MDR_EEPROM
*/

typedef struct {
    volatile bit_depth_t cmd;
    volatile bit_depth_t adr;
    volatile bit_depth_t di;
    volatile bit_depth_t data; // Обозначение в спецификации - "do"
    volatile bit_depth_t key;
} mdr_eeprom_t;

#define MDR_EEPROM ((volatile mdr_eeprom_t*) 0x40018000)

enum MDR_EEPROM_CMD {
    MDR_EEPROM_CMD_COM   = 1,
    MDR_EEPROM_CMD_DELAY = 7 << 3,
    MDR_EEPROM_CMD_XE    = 1 << 6,
    MDR_EEPROM_CMD_YE    = 1 << 7,
    MDR_EEPROM_CMD_SE    = 1 << 8,
    MDR_EEPROM_CMD_IFREN = 1 << 9,
    MDR_EEPROM_CMD_ERASE = 1 << 10,
    MDR_EEPROM_CMD_MAS1  = 1 << 11
};

/*
    SysTick
*/

typedef struct {
    volatile bit_depth_t ctrl;
    volatile bit_depth_t load;
    volatile bit_depth_t val;
    const volatile bit_depth_t calib;
} sys_tick_t;

#define SYS_TICK ((volatile sys_tick_t*) 0xE000E010)

enum SYS_TICK_CTRL {
    SYS_TICK_CTRL_ENABLE    = 1,
    SYS_TICK_CTRL_TCKINT    = 1 << 1,
    SYS_TICK_CTRL_CLKSOURCE = 1 << 2,
    SYS_TICK_CTRL_COUNTFLAG = 1 << 16,
};

enum SYS_TICK_LOAD {
    SYS_TICK_LOAD = 16777215,
};

enum SYS_TICK_VAL {
    SYS_TICK_VAL = 16777215,
};

enum SYS_TICK_CALIB {
    SYS_TICK_CALIB_TENMS = 16777215,
    SYS_TICK_CALIB_SKEW  = 1 << 30,
    SYS_TICK_CALIB_NOREF = 1 << 31,
};

/*
    MPU
*/

typedef struct {
    const volatile bit_depth_t type;
    volatile bit_depth_t ctrl;
    volatile bit_depth_t rnr;
    volatile bit_depth_t rbar;
    volatile bit_depth_t rasr;
    volatile bit_depth_t rbar_a1;
    volatile bit_depth_t rasr_a1;
    volatile bit_depth_t rbar_a2;
    volatile bit_depth_t rasr_a2;
    volatile bit_depth_t rbar_a3;
    volatile bit_depth_t rasr_a3;
} mpu_t;

#define MPU ((volatile mpu_t*) 0xE000ED90)

enum MPU_TYPE {
    MPU_TYPE_SEPARATE = 1,
    MPU_TYPE_DREGION  = 255 << 8,
    MPU_TYPE_IREGION  = 255 << 16,
};

enum MPU_CTRL {
    MPU_CTRL_ENABLE     = 1,
    MPU_CTRL_HFNMIENA   = 1 << 1,
    MPU_CTRL_PRIVDEFENA = 3 << 2,
};

enum MPU_RNR {
    MPU_RNR_REGION = 255,
};

enum MPU_RBAR {
    MPU_RBAR_REGION = 15,
    MPU_RBAR_VALID  = 3        << 4,
    MPU_RBAR_ADDR   = 16777215 << 8,
};

enum MPU_RASR {
    MPU_RASR_ENABLE = 1,
    MPU_RASR_SIZE   = 15  << 1,
    MPU_RASR_SRD    = 255 << 8,
    MPU_RASR_B      = 1   << 16,
    MPU_RASR_C      = 1   << 17,
    MPU_RASR_S      = 1   << 8,
    MPU_RASR_TEX    = 7   << 19,
    MPU_RASR_AP     = 7   << 24,
    MPU_RASR_NX     = 1   << 28,
};

/*
    MDR_RST_CLK
*/

typedef struct {
    const volatile bit_depth_t clock_status;
    volatile bit_depth_t pll_control;
    volatile bit_depth_t hs_control;
    volatile bit_depth_t cpu_clock;
    volatile bit_depth_t usb_clock;
    volatile bit_depth_t adc_mco_clock;
    volatile bit_depth_t rtc_clock;
    volatile bit_depth_t per_clock;
    volatile bit_depth_t can_clock;
    volatile bit_depth_t tim_clock;
    volatile bit_depth_t uart_clock;
    volatile bit_depth_t ssp_clock;
} mdr_rst_clk_t;

#define MDR_RST_CLK ((volatile mdr_rst_clk_t*) 0x40020000)

#define HSI_FREQUENCY 8000000
#define LSI_FREQUENCY 40000

#define LSE_FREQUENCY 32000

enum MDR_RST_CLK_CLOCK_STATUS {
    MDR_RST_CLK_CLOCK_STATUS_PLLUSBRDY = 1,
    MDR_RST_CLK_CLOCK_STATUS_PLLCPURDY = 1 << 1,
    MDR_RST_CLK_CLOCK_STATUS_HSERDY    = 1 << 2,
};

enum MDR_RST_CLK_PLL_CONTROL {
    MDR_RST_CLK_PLL_CONTROL_PLL_USB_ON  = 1,
    MDR_RST_CLK_PLL_CONTROL_PLL_USB_RLD = 1  << 1,
    MDR_RST_CLK_PLL_CONTROL_PLL_CPU_ON  = 1  << 2,
    MDR_RST_CLK_PLL_CONTROL_PLL_CPU_RLD = 1  << 3,
    MDR_RST_CLK_PLL_CONTROL_PLL_USB_MUL = 15 << 4,
    MDR_RST_CLK_PLL_CONTROL_PLL_CPU_MUL = 15 << 8,
};

enum MDR_RST_CLK_HS_CONTROL {
    MDR_RST_CLK_HS_CONTROL_HSE_ON  = 1,
    MDR_RST_CLK_HS_CONTROL_HSE_BYP = 1 << 1,
};

enum MDR_RST_CLK_CPU_CLOCK {
    MDR_RST_CLK_CPU_CLOCK_CPU_C1_SEL   = 3,
    MDR_RST_CLK_CPU_CLOCK_CPU_C2_SEL   = 1  << 2,
    MDR_RST_CLK_CPU_CLOCK_CPU_C3_SEL   = 15 << 4,
    MDR_RST_CLK_CPU_CLOCK_CPU_HCLK_SEL = 3  << 8,
};

enum MDR_RST_CLK_USB_CLOCK {
    MDR_RST_CLK_USB_CLOCK_USB_C1_SEL = 3,
    MDR_RST_CLK_USB_CLOCK_USB_C2_SEL = 1 << 2,
    MDR_RST_CLK_USB_CLOCK_USB_C3_SEL = 1 << 4,
    MDR_RST_CLK_USB_CLOCK_USB_CLK_EN = 1 << 8,
};

enum MDR_RST_CLK_ADC_MCO_CLOCK {
    MDR_RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL = 3,
    MDR_RST_CLK_ADC_MCO_CLOCK_ADC_C2_SEL = 3  << 4,
    MDR_RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL = 15 << 8,
    MDR_RST_CLK_ADC_MCO_CLOCK_ADC_CLK_EN = 1  << 13,
};

enum MDR_RST_CLK_RTC_CLOCK {
    MDR_RST_CLK_RTC_CLOCK_HSE_C1_SEL = 15,
    MDR_RST_CLK_RTC_CLOCK_HSI_C1_SEL = 15 << 4,
    MDR_RST_CLK_RTC_CLOCK_HSE_RTC_EN = 1  << 8,
    MDR_RST_CLK_RTC_CLOCK_HSI_RTC_EN = 1  << 9,
};

enum MDR_RST_CLK_PER_CLOCK {
    MDR_RST_CLK_PER_CLOCK_PCLK_SEL = 15,      // Названо случайным образом из-за ошибки в спецификации
    MDR_RST_CLK_PER_CLOCK_PCLK_EN  = 1  << 4,
    MDR_RST_CLK_PER_CLOCK_PCLK_PER = 28 << 5, // Названо случайным образом из-за ошибки в спецификации
};

enum MDR_RST_CLK_CAN_CLOCK {
    MDR_RST_CLK_CAN_CLOCK_CAN1_BRG    = 255,
    MDR_RST_CLK_CAN_CLOCK_CAN2_BRG    = 255 << 8,
    MDR_RST_CLK_CAN_CLOCK_CAN1_CLK_EN = 1   << 24,
    MDR_RST_CLK_CAN_CLOCK_CAN2_CLK_EN = 1   << 25,
};

enum MDR_RST_CLK_TIM_CLOCK {
    MDR_RST_CLK_TIM_CLOCK_TIM1_BRG    = 255,
    MDR_RST_CLK_TIM_CLOCK_TIM2_BRG    = 255 << 8,
    MDR_RST_CLK_TIM_CLOCK_TIM3_BRG    = 255 << 16,
    MDR_RST_CLK_TIM_CLOCK_TIM1_CLK_EN = 1   << 24,
    MDR_RST_CLK_TIM_CLOCK_TIM2_CLK_EN = 1   << 25,
    MDR_RST_CLK_TIM_CLOCK_TIM3_CLK_EN = 1   << 26,
};

enum MDR_RST_CLK_UART_CLOCK {
    MDR_RST_CLK_UART_CLOCK_UART1_BRG    = 255,
    MDR_RST_CLK_UART_CLOCK_UART2_BRG    = 255 << 8,
    MDR_RST_CLK_UART_CLOCK_UART1_CLK_EN = 1   << 24,
    MDR_RST_CLK_UART_CLOCK_UART2_CLK_EN = 1   << 25,
};

enum MDR_RST_CLK_SSP_CLOCK {
    MDR_RST_CLK_SSP_CLOCK_SSP1_BRG    = 255,
    MDR_RST_CLK_SSP_CLOCK_SSP2_BRG    = 255 << 8,
    MDR_RST_CLK_SSP_CLOCK_SSP1_CLK_EN = 1   << 24,
    MDR_RST_CLK_SSP_CLOCK_SSP2_CLK_EN = 1   << 25,
};

/*
    MDR_BKP
*/

typedef struct {
    volatile bit_depth_t reg_00;
    volatile bit_depth_t reg_01;
    volatile bit_depth_t reg_02;
    volatile bit_depth_t reg_03;
    volatile bit_depth_t reg_04;
    volatile bit_depth_t reg_05;
    volatile bit_depth_t reg_06;
    volatile bit_depth_t reg_07;
    volatile bit_depth_t reg_08;
    volatile bit_depth_t reg_09;
    volatile bit_depth_t reg_0a;
    volatile bit_depth_t reg_0b;
    volatile bit_depth_t reg_0c;
    volatile bit_depth_t reg_0d;
    volatile bit_depth_t reg_0e;
    volatile bit_depth_t reg_0f;
    volatile bit_depth_t rtc_cnt;
    volatile bit_depth_t rtc_div;
    volatile bit_depth_t rtc_prl;
    volatile bit_depth_t rtc_alrm;
    volatile bit_depth_t rtc_cs;
} mdr_bkp_t;

#define MDR_BKP ((volatile mdr_bkp_t*) 0x400D8000)

enum MDR_BKP_REG_0E {
    MDR_BKP_REG_0E_LOW       = 3,
    MDR_BKP_REG_0E_SELECT_RI = 7 << 3,
    MDR_BKP_REG_0E_JTAG_A    = 1 << 6,
    MDR_BKP_REG_0E_JTAG_B    = 1 << 7,
    MDR_BKP_REG_0E_TRIM      = 7 << 8,
    MDR_BKP_REG_0E_FPOR      = 1 << 11,
    MDR_BKP_REG_0E_MODE      = 7 << 12
};

enum MDR_BKP_REG_0F {
    MDR_BKP_REG_0F_LSE_ON    = 1,
    MDR_BKP_REG_0F_LSE_BYP   = 1   << 1,
    MDR_BKP_REG_0F_RTC_SEL   = 3   << 2,
    MDR_BKP_REG_0F_RTC_EN    = 1   << 4,
    MDR_BKP_REG_0F_RTC_CAL   = 255 << 5,
    MDR_BKP_REG_0F_LSE_RDY   = 1   << 13,
    MDR_BKP_REG_0F_LSI_ON    = 1   << 15,
    MDR_BKP_REG_0F_LSI_TRIM  = 31  << 16,
    MDR_BKP_REG_0F_LSI_RDY   = 1   << 21,
    MDR_BKP_REG_0F_HSI_ON    = 1   << 22,
    MDR_BKP_REG_0F_HSI_RDY   = 1   << 23,
    MDR_BKP_REG_0F_HSI_TRIM  = 63  << 24,
    MDR_BKP_REG_0F_STANDBY   = 1   << 30,
    MDR_BKP_REG_0F_RTC_RESET = 1   << 31
};

enum MDR_BKP_RTC_DIV {
    MDR_BKP_RTC_DIV_RTC_DIV = 1048575,
};

enum MDR_BKP_RTC_PRL {
    MDR_BKP_RTC_PRL_RTC_PRL = 1048575,
};

enum MDR_BKP_RTC_CS {
    MDR_BKP_RTC_CS_OWF     = 1,
    MDR_BKP_RTC_CS_SECF    = 1 << 1,
    MDR_BKP_RTC_CS_ALRF    = 1 << 2,
    MDR_BKP_RTC_CS_OWF_IE  = 1 << 3,
    MDR_BKP_RTC_CS_SECF_IE = 1 << 4,
    MDR_BKP_RTC_CS_ALRF_IE = 1 << 5,
    MDR_BKP_RTC_CS_WEC     = 1 << 6,
};

/*
    MDR_MDR_PORT
*/

typedef struct {
    volatile bit_depth_t rxtx;
    volatile bit_depth_t oe;
    volatile bit_depth_t func;
    volatile bit_depth_t analog;
    volatile bit_depth_t pull;
    volatile bit_depth_t pd;
    volatile bit_depth_t pwr;
    volatile bit_depth_t gfen;
} mdr_port_t;

#define MDR_PORT_A ((volatile mdr_port_t*) 0x400A8000)
#define MDR_PORT_B ((volatile mdr_port_t*) 0x400B0000)
#define MDR_PORT_C ((volatile mdr_port_t*) 0x400B8000)
#define MDR_PORT_D ((volatile mdr_port_t*) 0x400C0000)
#define MDR_PORT_E ((volatile mdr_port_t*) 0x400C8000)
#define MDR_PORT_F ((volatile mdr_port_t*) 0x400E8000)

enum MDR_PORT_OUT_RXTX {
    MDR_PORT_OUT_0_RXTX  = 1,
    MDR_PORT_OUT_1_RXTX  = 1 << 1,
    MDR_PORT_OUT_2_RXTX  = 1 << 2,
    MDR_PORT_OUT_3_RXTX  = 1 << 3,
    MDR_PORT_OUT_4_RXTX  = 1 << 4,
    MDR_PORT_OUT_5_RXTX  = 1 << 5,
    MDR_PORT_OUT_6_RXTX  = 1 << 6,
    MDR_PORT_OUT_7_RXTX  = 1 << 7,
    MDR_PORT_OUT_8_RXTX  = 1 << 8,
    MDR_PORT_OUT_9_RXTX  = 1 << 9,
    MDR_PORT_OUT_10_RXTX = 1 << 10,
    MDR_PORT_OUT_11_RXTX = 1 << 11,
    MDR_PORT_OUT_12_RXTX = 1 << 12,
    MDR_PORT_OUT_13_RXTX = 1 << 13,
    MDR_PORT_OUT_14_RXTX = 1 << 14,
    MDR_PORT_OUT_15_RXTX = 1 << 15,
};

enum MDR_PORT_OUT_OE {
    MDR_PORT_OUT_0_OE  = 1,
    MDR_PORT_OUT_1_OE  = 1 << 1,
    MDR_PORT_OUT_2_OE  = 1 << 2,
    MDR_PORT_OUT_3_OE  = 1 << 3,
    MDR_PORT_OUT_4_OE  = 1 << 4,
    MDR_PORT_OUT_5_OE  = 1 << 5,
    MDR_PORT_OUT_6_OE  = 1 << 6,
    MDR_PORT_OUT_7_OE  = 1 << 7,
    MDR_PORT_OUT_8_OE  = 1 << 8,
    MDR_PORT_OUT_9_OE  = 1 << 9,
    MDR_PORT_OUT_10_OE = 1 << 10,
    MDR_PORT_OUT_11_OE = 1 << 11,
    MDR_PORT_OUT_12_OE = 1 << 12,
    MDR_PORT_OUT_13_OE = 1 << 13,
    MDR_PORT_OUT_14_OE = 1 << 14,
    MDR_PORT_OUT_15_OE = 1 << 15,
};

enum MDR_PORT_OUT_FUNCTION {
    MDR_PORT_OUT_0_FUNCTION  = 3,
    MDR_PORT_OUT_1_FUNCTION  = 3 << 2,
    MDR_PORT_OUT_2_FUNCTION  = 3 << 4,
    MDR_PORT_OUT_3_FUNCTION  = 3 << 6,
    MDR_PORT_OUT_4_FUNCTION  = 3 << 8,
    MDR_PORT_OUT_5_FUNCTION  = 3 << 10,
    MDR_PORT_OUT_6_FUNCTION  = 3 << 12,
    MDR_PORT_OUT_7_FUNCTION  = 3 << 14,
    MDR_PORT_OUT_8_FUNCTION  = 3 << 16,
    MDR_PORT_OUT_9_FUNCTION  = 3 << 18,
    MDR_PORT_OUT_10_FUNCTION = 3 << 20,
    MDR_PORT_OUT_11_FUNCTION = 3 << 22,
    MDR_PORT_OUT_12_FUNCTION = 3 << 24,
    MDR_PORT_OUT_13_FUNCTION = 3 << 26,
    MDR_PORT_OUT_14_FUNCTION = 3 << 28,
    MDR_PORT_OUT_15_FUNCTION = 3 << 30,
};

enum MDR_PORT_OUT_ANALOG {
    MDR_PORT_OUT_0_ANALOG  = 1,
    MDR_PORT_OUT_1_ANALOG  = 1 << 1,
    MDR_PORT_OUT_2_ANALOG  = 1 << 2,
    MDR_PORT_OUT_3_ANALOG  = 1 << 3,
    MDR_PORT_OUT_4_ANALOG  = 1 << 4,
    MDR_PORT_OUT_5_ANALOG  = 1 << 5,
    MDR_PORT_OUT_6_ANALOG  = 1 << 6,
    MDR_PORT_OUT_7_ANALOG  = 1 << 7,
    MDR_PORT_OUT_8_ANALOG  = 1 << 8,
    MDR_PORT_OUT_9_ANALOG  = 1 << 9,
    MDR_PORT_OUT_10_ANALOG = 1 << 10,
    MDR_PORT_OUT_11_ANALOG = 1 << 11,
    MDR_PORT_OUT_12_ANALOG = 1 << 12,
    MDR_PORT_OUT_13_ANALOG = 1 << 13,
    MDR_PORT_OUT_14_ANALOG = 1 << 14,
    MDR_PORT_OUT_15_ANALOG = 1 << 15,
};

enum MDR_PORT_OUT_PULL {
    MDR_PORT_OUT_0_PULL_UP    = 1 << 16,
    MDR_PORT_OUT_0_PULL_DOWN  = 1,
    MDR_PORT_OUT_1_PULL_UP    = 1 << 17,
    MDR_PORT_OUT_1_PULL_DOWN  = 1 << 1,
    MDR_PORT_OUT_2_PULL_UP    = 1 << 18,
    MDR_PORT_OUT_2_PULL_DOWN  = 1 << 2,
    MDR_PORT_OUT_3_PULL_UP    = 1 << 19,
    MDR_PORT_OUT_3_PULL_DOWN  = 1 << 3,
    MDR_PORT_OUT_4_PULL_UP    = 1 << 20,
    MDR_PORT_OUT_4_PULL_DOWN  = 1 << 4,
    MDR_PORT_OUT_5_PULL_UP    = 1 << 21,
    MDR_PORT_OUT_5_PULL_DOWN  = 1 << 5,
    MDR_PORT_OUT_6_PULL_UP    = 1 << 22,
    MDR_PORT_OUT_6_PULL_DOWN  = 1 << 6,
    MDR_PORT_OUT_7_PULL_UP    = 1 << 23,
    MDR_PORT_OUT_7_PULL_DOWN  = 1 << 7,
    MDR_PORT_OUT_8_PULL_UP    = 1 << 24,
    MDR_PORT_OUT_8_PULL_DOWN  = 1 << 8,
    MDR_PORT_OUT_9_PULL_UP    = 1 << 25,
    MDR_PORT_OUT_9_PULL_DOWN  = 1 << 9,
    MDR_PORT_OUT_10_PULL_UP   = 1 << 26,
    MDR_PORT_OUT_10_PULL_DOWN = 1 << 10,
    MDR_PORT_OUT_11_PULL_UP   = 1 << 27,
    MDR_PORT_OUT_11_PULL_DOWN = 1 << 11,
    MDR_PORT_OUT_12_PULL_UP   = 1 << 28,
    MDR_PORT_OUT_12_PULL_DOWN = 1 << 12,
    MDR_PORT_OUT_13_PULL_UP   = 1 << 29,
    MDR_PORT_OUT_13_PULL_DOWN = 1 << 13,
    MDR_PORT_OUT_14_PULL_UP   = 1 << 30,
    MDR_PORT_OUT_14_PULL_DOWN = 1 << 14,
    MDR_PORT_OUT_15_PULL_UP   = 1 << 31,
    MDR_PORT_OUT_15_PULL_DOWN = 1 << 15,
};

enum MDR_PORT_OUT_PD {
    MDR_PORT_OUT_0_PD_SHM  = 1 << 16,
    MDR_PORT_OUT_0_PD_PD   = 1,
    MDR_PORT_OUT_1_PD_SHM  = 1 << 17,
    MDR_PORT_OUT_1_PD_PD   = 1 << 1,
    MDR_PORT_OUT_2_PD_SHM  = 1 << 18,
    MDR_PORT_OUT_2_PD_PD   = 1 << 2,
    MDR_PORT_OUT_3_PD_SHM  = 1 << 19,
    MDR_PORT_OUT_3_PD_PD   = 1 << 3,
    MDR_PORT_OUT_4_PD_SHM  = 1 << 20,
    MDR_PORT_OUT_4_PD_PD   = 1 << 4,
    MDR_PORT_OUT_5_PD_SHM  = 1 << 21,
    MDR_PORT_OUT_5_PD_PD   = 1 << 5,
    MDR_PORT_OUT_6_PD_SHM  = 1 << 22,
    MDR_PORT_OUT_6_PD_PD   = 1 << 6,
    MDR_PORT_OUT_7_PD_SHM  = 1 << 23,
    MDR_PORT_OUT_7_PD_PD   = 1 << 7,
    MDR_PORT_OUT_8_PD_SHM  = 1 << 24,
    MDR_PORT_OUT_8_PD_PD   = 1 << 8,
    MDR_PORT_OUT_9_PD_SHM  = 1 << 25,
    MDR_PORT_OUT_9_PD_PD   = 1 << 9,
    MDR_PORT_OUT_10_PD_SHM = 1 << 26,
    MDR_PORT_OUT_10_PD_PD  = 1 << 10,
    MDR_PORT_OUT_11_PD_SHM = 1 << 27,
    MDR_PORT_OUT_11_PD_PD  = 1 << 11,
    MDR_PORT_OUT_12_PD_SHM = 1 << 28,
    MDR_PORT_OUT_12_PD_PD  = 1 << 12,
    MDR_PORT_OUT_13_PD_SHM = 1 << 29,
    MDR_PORT_OUT_13_PD_PD  = 1 << 13,
    MDR_PORT_OUT_14_PD_SHM = 1 << 30,
    MDR_PORT_OUT_14_PD_PD  = 1 << 14,
    MDR_PORT_OUT_15_PD_SHM = 1 << 31,
    MDR_PORT_OUT_15_PD_PD  = 1 << 15,
};

enum MDR_PORT_OUT_PWR {
    MDR_PORT_OUT_0_PWR  = 3,
    MDR_PORT_OUT_1_PWR  = 3 << 2,
    MDR_PORT_OUT_2_PWR  = 3 << 4,
    MDR_PORT_OUT_3_PWR  = 3 << 6,
    MDR_PORT_OUT_4_PWR  = 3 << 8,
    MDR_PORT_OUT_5_PWR  = 3 << 10,
    MDR_PORT_OUT_6_PWR  = 3 << 12,
    MDR_PORT_OUT_7_PWR  = 3 << 14,
    MDR_PORT_OUT_8_PWR  = 3 << 16,
    MDR_PORT_OUT_9_PWR  = 3 << 18,
    MDR_PORT_OUT_10_PWR = 3 << 20,
    MDR_PORT_OUT_11_PWR = 3 << 22,
    MDR_PORT_OUT_12_PWR = 3 << 24,
    MDR_PORT_OUT_13_PWR = 3 << 26,
    MDR_PORT_OUT_14_PWR = 3 << 28,
    MDR_PORT_OUT_15_PWR = 3 << 30,
};

enum MDR_PORT_OUT_GFEN {
    MDR_PORT_OUT_0_GFEN  = 1,
    MDR_PORT_OUT_1_GFEN  = 1 << 1,
    MDR_PORT_OUT_2_GFEN  = 1 << 2,
    MDR_PORT_OUT_3_GFEN  = 1 << 3,
    MDR_PORT_OUT_4_GFEN  = 1 << 4,
    MDR_PORT_OUT_5_GFEN  = 1 << 5,
    MDR_PORT_OUT_6_GFEN  = 1 << 6,
    MDR_PORT_OUT_7_GFEN  = 1 << 7,
    MDR_PORT_OUT_8_GFEN  = 1 << 8,
    MDR_PORT_OUT_9_GFEN  = 1 << 9,
    MDR_PORT_OUT_10_GFEN = 1 << 10,
    MDR_PORT_OUT_11_GFEN = 1 << 11,
    MDR_PORT_OUT_12_GFEN = 1 << 12,
    MDR_PORT_OUT_13_GFEN = 1 << 13,
    MDR_PORT_OUT_14_GFEN = 1 << 14,
    MDR_PORT_OUT_15_GFEN = 1 << 15,
};

/*
    MDR_POWER
*/

typedef struct {
    volatile bit_depth_t pvdcs;
} mdr_power_t;

#define MDR_POWER ((volatile mdr_power_t*) 0x40058000)

enum MDR_POWER_PVDCS {
    MDR_POWER_PVDCS_PVDEN  = 1,
    MDR_POWER_PVDCS_PBLS   = 3 << 1,
    MDR_POWER_PVDCS_PLS    = 7 << 3,
    MDR_POWER_PVDCS_PVBD   = 1 << 6,
    MDR_POWER_PVDCS_PVD    = 1 << 7,
    MDR_POWER_PVDCS_IEPVBD = 1 << 8,
    MDR_POWER_PVDCS_IEPVD  = 1 << 9,
    MDR_POWER_PVDCS_INVB   = 1 << 10,
    MDR_POWER_PVDCS_INV    = 1 << 11,
};

/*
    MDR_EBC
*/

#pragma pack(push, 1)
typedef struct {
    const char _padding_0[50];
    volatile bit_depth_t nand_cycles;
    volatile bit_depth_t control;
    volatile bit_depth_t reg_0_cntrl;
    volatile bit_depth_t reg_1_cntrl;
    volatile bit_depth_t reg_2_cntrl;
    volatile bit_depth_t reg_3_cntrl;
} mdr_ebc_t;
#pragma pack(pop)

#define MDR_EBC ((volatile mdr_ebc_t*) 0x400F0000)

enum MDR_EBC_NAND_CYCLES {
    MDR_EBC_NAND_CYCLES_T_RC   = 15,
    MDR_EBC_NAND_CYCLES_T_WC   = 15 << 4,
    MDR_EBC_NAND_CYCLES_T_REA  = 15 << 8,
    MDR_EBC_NAND_CYCLES_T_WP   = 15 << 12,
    MDR_EBC_NAND_CYCLES_T_WHR  = 15 << 16,
    MDR_EBC_NAND_CYCLES_T_ALEA = 15 << 20,
    MDR_EBC_NAND_CYCLES_T_RR   = 15 << 24
};

enum MDR_EBC_CONTROL {
    MDR_EBC_CONTROL_ROM          = 1,
    MDR_EBC_CONTROL_RAM          = 1  << 1,
    MDR_EBC_CONTROL_NAND         = 1  << 2,
    MDR_EBC_CONTROL_CPOL         = 1  << 3,
    MDR_EBC_CONTROL_ENDIAN       = 1  << 4,
    MDR_EBC_CONTROL_LOW8         = 1  << 5,
    MDR_EBC_CONTROL_LOW16        = 1  << 6,
    MDR_EBC_CONTROL_BUSY         = 1  << 7,
    MDR_EBC_CONTROL_CLOCKOUT_EN  = 1  << 8,
    MDR_EBC_CONTROL_EXT_BUS_MODE = 1  << 9,
    MDR_EBC_CONTROL_EN_FS_RDY    = 1  << 10,
    MDR_EBC_CONTROL_EN_FF_RDY    = 1  << 11,
    MDR_EBC_CONTROL_WAIT_STATE   = 15 << 12,
    MDR_EBC_CONTROL_FS_RDY       = 1  << 16,
    MDR_EBC_CONTROL_FF_RDY       = 1  << 17
};

enum MDR_EBC_REG_CNTRL {
    MDR_EBC_REG_CNTRL_ENABLE    = 1,
    MDR_EBC_REG_CNTRL_WS_ACTIVE = 127 << 1,
    MDR_EBC_REG_CNTRL_WS_SETUP  = 7   << 8,
    MDR_EBC_REG_CNTRL_WS_HOLD   = 7   << 11,
    MDR_EBC_REG_CNTRL_USE_READY = 1   << 14
};

/*
    MDR_USB
*/

#pragma pack(push, 1)
typedef struct {
    volatile bit_depth_t htxc;
    volatile bit_depth_t htxt;
    volatile bit_depth_t htxlc;
    volatile bit_depth_t htxse;
    volatile bit_depth_t htxa;
    volatile bit_depth_t htxe;
    volatile bit_depth_t hfn_l;
    volatile bit_depth_t hfn_h;
    volatile bit_depth_t hsi;
    volatile bit_depth_t him;
    volatile bit_depth_t hrxs;
    volatile bit_depth_t hrxp;
    volatile bit_depth_t hrxa;
    volatile bit_depth_t hrxe;
    volatile bit_depth_t hrxcs;
    volatile bit_depth_t hstm;
    const char _padding_0[0x44];
    volatile bit_depth_t hrxfd;
    const char _padding_1[0x4];
    volatile bit_depth_t hrxfdc;
    const char _padding_2[0x4];
    volatile bit_depth_t hrxfc;
    const char _padding_3[0x30];
    volatile bit_depth_t htxfd;
    const char _padding_4[0x10];
    volatile bit_depth_t htxfc;
    const char _padding_5[0x30];
    volatile bit_depth_t sep_ctrl_0;
    volatile bit_depth_t sep_sts_0;
    volatile bit_depth_t sep_ts_0;
    volatile bit_depth_t sep_nts_0;
    volatile bit_depth_t sep_ctrl_1;
    volatile bit_depth_t sep_sts_1;
    volatile bit_depth_t sep_ts_1;
    volatile bit_depth_t sep_nts_1;
    volatile bit_depth_t sep_ctrl_2;
    volatile bit_depth_t sep_sts_2;
    volatile bit_depth_t sep_ts_2;
    volatile bit_depth_t sep_nts_2;
    volatile bit_depth_t sep_ctrl_3;
    volatile bit_depth_t sep_sts_3;
    volatile bit_depth_t sep_ts_3;
    volatile bit_depth_t sep_nts_3;
    volatile bit_depth_t sc;
    volatile bit_depth_t sls;
    volatile bit_depth_t sis;
    volatile bit_depth_t sim;
    volatile bit_depth_t sa;
    volatile bit_depth_t sfn_l;
    volatile bit_depth_t sfn_h;
    const char _padding_6[0x28];
    volatile bit_depth_t sep_rxfd_0;
    const char _padding_7[0x4];
    volatile bit_depth_t sep_rxfdc_0;
    const char _padding_8[0x4];
    volatile bit_depth_t sep_rxfc_0;
    const char _padding_9[0x30];
    volatile bit_depth_t sep_txfd_0;
    const char _padding_10[0x10];
    volatile bit_depth_t sep_txfdc_0;
    const char _padding_11[0x30];
    volatile bit_depth_t sep_rxfd_1;
    const char _padding_12[0x4];
    volatile bit_depth_t sep_rxfdc_1;
    const char _padding_13[0x4];
    volatile bit_depth_t sep_rxfc_1;
    const char _padding_14[0x30];
    volatile bit_depth_t sep_txfd_1;
    const char _padding_15[0x10];
    volatile bit_depth_t sep_txfdc_1;
    const char _padding_16[0x30];
    volatile bit_depth_t sep_rxfd_2;
    const char _padding_17[0x4];
    volatile bit_depth_t sep_rxfdc_2;
    const char _padding_18[0x4];
    volatile bit_depth_t sep_rxfc_2;
    const char _padding_19[0x30];
    volatile bit_depth_t sep_txfd_2;
    const char _padding_20[0x10];
    volatile bit_depth_t sep_txfdc_2;
    const char _padding_21[0x30];
    volatile bit_depth_t sep_rxfd_3;
    const char _padding_22[0x4];
    volatile bit_depth_t sep_rxfdc_3;
    const char _padding_23[0x4];
    volatile bit_depth_t sep_rxfc_3;
    const char _padding_24[0x30];
    volatile bit_depth_t sep_txfd_3;
    const char _padding_25[0x10];
    volatile bit_depth_t sep_txfdc_3;
    const char _padding_26[0x30];
    volatile bit_depth_t hscr;
    volatile bit_depth_t hsvr;
} mdr_usb_t;
#pragma pack(pop)

#define MDR_USB ((volatile mdr_usb_t*) 0x40010000)

enum MDR_USB_HSCR {
    MDR_USB_HSCR_HOST_MODE   = 1,
    MDR_USB_HSCR_RESET_CORE  = 1 << 1,
    MDR_USB_HSCR_EN_TX       = 1 << 2,
    MDR_USB_HSCR_EN_RX       = 1 << 3,
    MDR_USB_HSCR_DP_PULLUP   = 1 << 4,
    MDR_USB_HSCR_DP_PULLDOWN = 1 << 5,
    MDR_USB_HSCR_DM_PULLUP   = 1 << 6,
    MDR_USB_HSCR_DM_PULLDOWN = 1 << 7,
};

enum MDR_USB_HSVR {
    MDR_USB_HSVR_VERSION  = 15,
    MDR_USB_HSVR_REVISION = 15 << 4,
};

enum MDR_USB_HTXC {
    MDR_USB_HTXC_TREQ  = 1,
    MDR_USB_HTXC_SOFS  = 1 << 1,
    MDR_USB_HTXC_PREEN = 1 << 2,
    MDR_USB_HTXC_ISOEN = 1 << 3,
};

enum MDR_USB_HTXT {
    MDR_USB_HTXT_TTYPE = 3,
};

enum MDR_USB_HTXLC {
    MDR_USB_HTXLC_TXLC = 3,
    MDR_USB_HTXLC_DC   = 1 << 2,
    MDR_USB_HTXLC_FSPL = 1 << 3,
    MDR_USB_HTXLC_FSLR = 1 << 4,
};

enum MDR_USB_HTXSE {
    MDR_USB_HTXSE_SOFEN = 1,
};

enum MDR_USB_HTXA {
    MDR_USB_HTXA_DEVADDR = 127,
};

enum MDR_USB_HTXE {
    MDR_USB_HTXE_EPADDR = 15,
};

enum MDR_USB_HFN {
    MDR_USB_HFN_FNUM = 2047,
};

enum MDR_USB_HSI {
    MDR_USB_HSI_TDONE  = 1,
    MDR_USB_HSI_RESUME = 1 << 1,
    MDR_USB_HSI_CONEV  = 1 << 2,
    MDR_USB_HSI_SOFS   = 1 << 3,
};

enum MDR_USB_HIM {
    MDR_USB_HIM_TDONEIE  = 1,
    MDR_USB_HIM_RESUMEIE = 1 << 1,
    MDR_USB_HIM_CONEVIE  = 1 << 2,
    MDR_USB_HIM_SOFIE    = 1 << 3,
};

enum MDR_USB_HRXS {
    MDR_USB_HRXS_CRCERR     = 1,
    MDR_USB_HRXS_BSERR      = 1 << 1,
    MDR_USB_HRXS_RXOF       = 1 << 2,
    MDR_USB_HRXS_RXTO       = 1 << 3,
    MDR_USB_HRXS_NAK_RXED   = 1 << 4,
    MDR_USB_HRXS_STALL_RXED = 1 << 5,
    MDR_USB_HRXS_ACK_RXED   = 1 << 6,
    MDR_USB_HRXS_DATASEQ    = 1 << 7,
};

enum MDR_USB_HRXP {
    MDR_USB_HRXP_RPID = 15,
};

enum MDR_USB_HRXA {
    MDR_USB_HRXA_RADDR = 127,
};

enum MDR_USB_HRXE {
    MDR_USB_HRXE_RXENDP = 15,
};

enum MDR_USB_HRXCS {
    MDR_USB_HRXCS = 3,
};

enum MDR_USB_HSTM {
    MDR_USB_HSTM_HSTM = 255,
};

enum MDR_USB_HRXFD {
    MDR_USB_HRXFD_RX_FIFO_DATA = 255,
};

enum MDR_USB_HRXFDC {
    MDR_USB_HRXFDC_FIFO_DATA_COUNT = 65535,
};

enum MDR_USB_HRXFC {
    MDR_USB_HRXFC_FIFO_FORCE_EMPTY = 1,
};

enum MDR_USB_HTXFD {
    MDR_USB_HTXFD_TX_FIFO_DATA = 255,
};

enum MDR_USB_HTXFC {
    MDR_USB_HTXFC_FIFO_FORCE_EMPTY = 1,
};

enum MDR_USB_SEP_CTRL {
    MDR_USB_SEP_CTRL_EPEN      = 1,
    MDR_USB_SEP_CTRL_EPRDY     = 1 << 1,
    MDR_USB_SEP_CTRL_EPDATASEQ = 1 << 2,
    MDR_USB_SEP_CTRL_EPSSTALL  = 1 << 3,
    MDR_USB_SEP_CTRL_EPISOEN   = 1 << 4,
};

enum MDR_USB_SEP_STS {
    MDR_USB_SEP_STS_SC_CRC_ERR    = 1,
    MDR_USB_SEP_STS_SC_BS_ERR     = 1 << 1,
    MDR_USB_SEP_STS_SC_RXOF       = 1 << 2,
    MDR_USB_SEP_STS_SC_RXTO       = 1 << 3,
    MDR_USB_SEP_STS_NAK_SENT      = 1 << 4,
    MDR_USB_SEP_STS_SC_STALL_SENT = 1 << 5,
    MDR_USB_SEP_STS_SC_ACK_RXED   = 1 << 6,
    MDR_USB_SEP_STS_SC_DATA_SEQ   = 1 << 7,
};

enum MDR_USB_SEP_TS {
    MDR_USB_SEP_TS_SCTTYPE = 3,
};

enum MDR_USB_SEP_NTS {
    MDR_USB_SEP_NTS_NTTYPE = 3,
};

enum MDR_USB_SC {
    MDR_USB_SC_SCGEN = 1,
    MDR_USB_SC_SCTXL = 3 << 1,
    MDR_USB_SC_SCDC  = 1 << 3,
    MDR_USB_SC_SCFSP = 1 << 4,
    MDR_USB_SC_SCFSR = 1 << 5,
};

enum MDR_USB_SLS {
    MDR_USB_SLS_SCRXLS = 3,
};

enum MDR_USB_SIS {
    MDR_USB_SIS_SC_TDONE    = 1,
    MDR_USB_SIS_SC_RESUME   = 1 << 1,
    MDR_USB_SIS_SC_RESET_EV = 1 << 2,
    MDR_USB_SIS_SC_SOF_REC  = 1 << 3,
    MDR_USB_SIS_SC_NAK_SENT = 1 << 4,
};

enum MDR_USB_SIM {
    MDR_USB_SIM_SC_TDONE_IE    = 1,
    MDR_USB_SIM_SC_RESUME_IE   = 1 << 1,
    MDR_USB_SIM_SC_RESET_EVIE  = 1 << 2,
    MDR_USB_SIM_SC_SOF_RECIE   = 1 << 3,
    MDR_USB_SIM_SC_NAK_SENT_IE = 1 << 4,
};

enum MDR_USB_SA {
    MDR_USB_SA_SDEVADDR = 127,
};

enum MDR_USB_SFN {
    MDR_USB_SFN_FRAME_NUM = 2047,
};

enum MDR_USB_SEP_RXFD {
    MDR_USB_SEP_RXFD_RX_FIFO_DATA = 255,
};

enum MDR_USB_SEP_RXFDC {
    MDR_USB_SEP_RXFDC_FIFO_DATA_COUNT = 65535,
};

enum MDR_USB_SEP_TXFD {
    MDR_USB_SEP_TXFD_TX_FIFO_DATA = 255,
};

enum MDR_USB_SEP_TXFDC {
    MDR_USB_SEP_TXFDC_FIFO_FORCE_EMPTY = 1,
};

/*
    MDR_CAN
*/

typedef struct {
    volatile bit_depth_t id;
    volatile bit_depth_t dlc;
    volatile bit_depth_t datal;
    volatile bit_depth_t datah;
} can_buf_t;

typedef struct {
    volatile bit_depth_t mask;
    volatile bit_depth_t filter;
} can_buf_filter_t;

#pragma pack(push, 1)
typedef struct {
    volatile bit_depth_t control;
    volatile bit_depth_t status;
    volatile bit_depth_t bittmng;
    volatile bit_depth_t int_en;
    const char _padding_0[0x8];
    volatile bit_depth_t over;
    const char _padding_1[0x4];
    volatile bit_depth_t rxid;
    volatile bit_depth_t rxdlc;
    volatile bit_depth_t rxdatal;
    volatile bit_depth_t rxdatah;
    volatile bit_depth_t txid;
    volatile bit_depth_t txdlc;
    volatile bit_depth_t datal;
    volatile bit_depth_t datah;
    volatile bit_depth_t buf_con[0x20];
    volatile bit_depth_t int_rx;
    volatile bit_depth_t rx;
    volatile bit_depth_t int_tx;
    volatile bit_depth_t tx;
    const char _padding_2[0x130];
    volatile can_buf_t can_buf[0x20];
    const char _padding_3[0x100];
    volatile can_buf_filter_t can_buf_filter[0x20];
} mdr_can_t;
#pragma pack(pop)

#define MDR_CAN1 ((volatile mdr_can_t*) 0x40000000)
#define MDR_CAN2 ((volatile mdr_can_t*) 0x40008000)

enum MDR_CAN_CONTROL {
    MDR_CAN_CONTROL_CAN_EN = 1,
    MDR_CAN_CONTROL_ROM    = 1 << 1,
    MDR_CAN_CONTROL_STM    = 1 << 2,
    MDR_CAN_CONTROL_SAP    = 1 << 3,
    MDR_CAN_CONTROL_ROP    = 1 << 4,
};

enum MDR_CAN_STATUS {
    MDR_CAN_STATUS_RX_READY      = 1,
    MDR_CAN_STATUS_TX_READY      = 1   << 1,
    MDR_CAN_STATUS_ERROR_OVER    = 1   << 2,
    MDR_CAN_STATUS_BIT_ERR       = 1   << 3,
    MDR_CAN_STATUS_BIT_STUFF_ERR = 1   << 4,
    MDR_CAN_STATUS_CRC_ERR       = 1   << 5,
    MDR_CAN_STATUS_FRAME_ERR     = 1   << 6,
    MDR_CAN_STATUS_ACK_ERR       = 1   << 7,
    MDR_CAN_STATUS_ID_LOWER      = 1   << 8,
    MDR_CAN_STATUS_ERR_STATUS    = 3   << 9,
    MDR_CAN_STATUS_RX_ERR_CNT8   = 1   << 11,
    MDR_CAN_STATUS_TX_ERR_CNT8   = 1   << 12,
    MDR_CAN_STATUS_RX_ERR_CNT    = 255 << 16,
    MDR_CAN_STATUS_TX_ERR_CNT    = 255 << 24,
};

enum MDR_CAN_BITTMNG {
    MDR_CAN_BITTMNG_BRP  = 65535,
    MDR_CAN_BITTMNG_PSEG = 7     << 16,
    MDR_CAN_BITTMNG_SEG1 = 7     << 19,
    MDR_CAN_BITTMNG_SEG2 = 7     << 22,
    MDR_CAN_BITTMNG_SJW  = 3     << 25,
    MDR_CAN_BITTMNG_SB   = 1     << 27,
};

enum MDR_CAN_INT_EN {
    MDR_CAN_INT_EN_GLB_INT_EN      = 1,
    MDR_CAN_INT_EN_RX_INT_EN       = 1 << 1,
    MDR_CAN_INT_EN_TX_INT_EN       = 1 << 2,
    MDR_CAN_INT_EN_ERR_INT_EN      = 1 << 3,
    MDR_CAN_INT_EN_ERR_OVER_INT_EN = 1 << 4,
};

enum MDR_CAN_OVER {
    MDR_CAN_OVER_ERROR_MAX = 255,
};

enum MDR_CAN_BUF_CON {
    MDR_CAN_BUF_CON_EN = 1,
    MDR_CAN_BUF_CON_RX_TX = 1 << 1,
    MDR_CAN_BUF_CON_OVER_EN = 1 << 2,
    MDR_CAN_BUF_CON_RTR_EN  = 1 << 3,
    MDR_CAN_BUF_CON_PRIOR   = 1 << 4,
    MDR_CAN_BUF_CON_TX_REQ  = 1 << 5,
    MDR_CAN_BUF_CON_RX_FULL = 1 << 6,
    MDR_CAN_BUF_CON_OVER_WR = 1 << 7,
};

enum MDR_CAN_RXID {
    MDR_CAN_RXID_EID = 262143,
    MDR_CAN_RXID_SID = 2047,
};

enum MDR_CAN_TXID {
    MDR_CAN_TXID_EID = 262143,
    MDR_CAN_TXID_SID = 2047,
};

enum MDR_CAN_BUF_ID {
    MDR_CAN_BUF_ID_EID = 262143,
    MDR_CAN_BUF_ID_SID = 2047,
};

enum MDR_CAN_BUF_FILTER_MASK {
    MDR_CAN_BUF_FILTER_MASK_EID = 262143,
    MDR_CAN_BUF_FILTER_MASK_SID = 2047,
};

enum MDR_CAN_BUF_FILTER_FILTER {
    MDR_CAN_BUF_FILTER_FILTER_EID = 262143,
    MDR_CAN_BUF_FILTER_FILTER_SID = 2047,
};

enum MDR_CAN_RXDLC {
    MDR_CAN_RXDLC_DLC = 15,
    MDR_CAN_RXDLC_RTR = 1  << 8,
    MDR_CAN_RXDLC_R1  = 1  << 9,
    MDR_CAN_RXDLC_R0  = 1  << 10,
    MDR_CAN_RXDLC_SRR = 1  << 11,
    MDR_CAN_RXDLC_IDE = 1  << 12,
};

enum MDR_CAN_TXDLC {
    MDR_CAN_TXDLC_DLC = 15,
    MDR_CAN_TXDLC_RTR = 1  << 8,
    MDR_CAN_TXDLC_R1  = 1  << 9,
    MDR_CAN_TXDLC_R0  = 1  << 10,
    MDR_CAN_TXDLC_SRR = 1  << 11,
    MDR_CAN_TXDLC_IDE = 1  << 12,
};

enum MDR_CAN_CAN_BUF_DLC {
    MDR_CAN_CAN_BUF_DLC_DLC = 15,
    MDR_CAN_CAN_BUF_DLC_RTR = 1  << 8,
    MDR_CAN_CAN_BUF_DLC_R1  = 1  << 9,
    MDR_CAN_CAN_BUF_DLC_R0  = 1  << 10,
    MDR_CAN_CAN_BUF_DLC_SRR = 1  << 11,
    MDR_CAN_CAN_BUF_DLC_IDE = 1  << 12,
};

enum MDR_CAN_RXDATAL {
    MDR_CAN_RXDATAL_DB0 = 255,
    MDR_CAN_RXDATAL_DB1 = 255 << 8,
    MDR_CAN_RXDATAL_DB2 = 255 << 16,
    MDR_CAN_RXDATAL_DB3 = 255 << 24,
};

enum MDR_CAN_TXDATAL {
    MDR_CAN_TXDATAL_DB0 = 255,
    MDR_CAN_TXDATAL_DB1 = 255 << 8,
    MDR_CAN_TXDATAL_DB2 = 255 << 16,
    MDR_CAN_TXDATAL_DB3 = 255 << 24,
};

enum MDR_CAN_CAN_BUF_DATAL {
    MDR_CAN_CAN_BUF_DATAL_DB0 = 255,
    MDR_CAN_CAN_BUF_DATAL_DB1 = 255 << 8,
    MDR_CAN_CAN_BUF_DATAL_DB2 = 255 << 16,
    MDR_CAN_CAN_BUF_DATAL_DB3 = 255 << 24,
};

enum MDR_CAN_RXDATAH {
    MDR_CAN_RXDATAH_DB4 = 255,
    MDR_CAN_RXDATAH_DB5 = 255 << 8,
    MDR_CAN_RXDATAH_DB6 = 255 << 16,
    MDR_CAN_RXDATAH_DB7 = 255 << 24,
};

enum MDR_CAN_TXDATAH {
    MDR_CAN_TXDATAH_DB4 = 255,
    MDR_CAN_TXDATAH_DB5 = 255 << 8,
    MDR_CAN_TXDATAH_DB6 = 255 << 16,
    MDR_CAN_TXDATAH_DB7 = 255 << 24,
};

enum MDR_CAN_CAN_BUF_DATAH {
    MDR_CAN_CAN_BUF_DATAH_DB4 = 255,
    MDR_CAN_CAN_BUF_DATAH_DB5 = 255 << 8,
    MDR_CAN_CAN_BUF_DATAH_DB6 = 255 << 16,
    MDR_CAN_CAN_BUF_DATAH_DB7 = 255 << 24,
};

/*
    MDR_TIMER
*/

#pragma pack(push, 1)
typedef struct {
    volatile bit_depth_t cnt;
    volatile bit_depth_t psg;
    volatile bit_depth_t arr;
    volatile bit_depth_t cntrl;
    volatile bit_depth_t ccr1;
    volatile bit_depth_t ccr2;
    volatile bit_depth_t ccr3;
    volatile bit_depth_t ccr4;
    volatile bit_depth_t ch1_cntrl;
    volatile bit_depth_t ch2_cntrl;
    volatile bit_depth_t ch3_cntrl;
    volatile bit_depth_t ch4_cntrl;
    volatile bit_depth_t ch1_cntrl1;
    volatile bit_depth_t ch2_cntrl1;
    volatile bit_depth_t ch3_cntrl1;
    volatile bit_depth_t ch4_cntrl1;
    volatile bit_depth_t ch1_dtg;
    volatile bit_depth_t ch2_dtg;
    volatile bit_depth_t ch3_dtg;
    volatile bit_depth_t ch4_dtg;
    volatile bit_depth_t brketr_cntrl;
    volatile bit_depth_t status;
    volatile bit_depth_t ie;
    volatile bit_depth_t dma_re;
    volatile bit_depth_t ch1_cntrl2;
    volatile bit_depth_t ch2_cntrl2;
    volatile bit_depth_t ch3_cntrl2;
    volatile bit_depth_t ch4_cntrl2;
    volatile bit_depth_t ccr11;
    volatile bit_depth_t ccr21;
    volatile bit_depth_t ccr31;
    volatile bit_depth_t ccr41;
} mdr_timer_t;
#pragma pack(pop)

#define MDR_TIMER1 ((volatile mdr_timer_t*) 0x40070000)
#define MDR_TIMER2 ((volatile mdr_timer_t*) 0x40078000)
#define MDR_TIMER3 ((volatile mdr_timer_t*) 0x40080000)

enum MDR_TIMER_CNT {
    MDR_TIMER_CNT_CNT = 65535,
};

enum MDR_TIMER_PSG {
    MDR_TIMER_PSG_PSG = 65535,
};

enum MDR_TIMER_ARR {
    MDR_TIMER_ARR_ARR = 65535,
};

enum MDR_TIMER_CNTRL {
    MDR_TIMER_CNTRL_CNT_EN    = 1,
    MDR_TIMER_CNTRL_ARRB_EN   = 1  << 1,
    MDR_TIMER_CNTRL_WR_CMPL   = 1  << 2,
    MDR_TIMER_CNTRL_DIR       = 1  << 3,
    MDR_TIMER_CNTRL_FDTS      = 3  << 4,
    MDR_TIMER_CNTRL_CNT_MODE  = 3  << 6,
    MDR_TIMER_CNTRL_EVENT_SEL = 15 << 8,
};

enum MDR_TIMER_CCR {
    MDR_TIMER_CCR_CCR = 65535,
};

enum MDR_TIMER_CCR1 {
    MDR_TIMER_CCR1_CCR1 = 65535,
};

enum MDR_TIMER_CH_CNTRL {
    MDR_TIMER_CH_CNTRL_CHFLTR   = 15,
    MDR_TIMER_CH_CNTRL_CHSEL    = 3  << 4,
    MDR_TIMER_CH_CNTRL_CHPSC    = 3  << 6,
    MDR_TIMER_CH_CNTRL_OCCE     = 1  << 8,
    MDR_TIMER_CH_CNTRL_OCCM     = 7  << 9,
    MDR_TIMER_CH_CNTRL_BRKEN    = 1  << 12,
    MDR_TIMER_CH_CNTRL_ETREN    = 1  << 13,
    MDR_TIMER_CH_CNTRL_WR_CMPL  = 1  << 14,
    MDR_TIMER_CH_CNTRL_CAP_NPWM = 1  << 15,
    MDR_TIMER_CH_CNTRL_WP_CMPL1 = 1  << 16,
};

enum MDR_TIMER_CH_CNTRL1 {
    MDR_TIMER_CH_CNTRL1_SELOE  = 3,
    MDR_TIMER_CH_CNTRL1_SELO   = 3 << 2,
    MDR_TIMER_CH_CNTRL1_INV    = 1 << 4,
    MDR_TIMER_CH_CNTRL1_NSELOE = 3 << 8,
    MDR_TIMER_CH_CNTRL1_NSELO  = 3 << 10,
    MDR_TIMER_CH_CNTRL1_NINV   = 1 << 12,
};

enum MDR_TIMER_CH_CNTRL2 {
    MDR_TIMER_CH_CNTRL2_CHSEL    = 3,
    MDR_TIMER_CH_CNTRL2_CCR1_EN  = 1 << 2,
    MDR_TIMER_CH_CNTRL2_CCRRLD   = 1 << 3,
    MDR_TIMER_CH_CNTRL2_EV_DELAY = 1 << 4,
};

enum MDR_TIMER_CH_DTG {
    MDR_TIMER_CH_DTG_DTGX = 15,
    MDR_TIMER_CH_DTG_EDTS = 1   << 4,
    MDR_TIMER_CH_DTG_DTG  = 255 << 8,
};

enum MDR_TIMER_DRKETR_CNTRL {
    MDR_TIMER_DRKETR_CNTRL_BRK_INV    = 1,
    MDR_TIMER_DRKETR_CNTRL_ETR_INV    = 1  << 1,
    MDR_TIMER_DRKETR_CNTRL_ETR_PSC    = 3  << 2,
    MDR_TIMER_DRKETR_CNTRL_ETR_FILTER = 15 << 4,
};

enum MDR_TIMER_STATUS {
    MDR_TIMER_STATUS_CNT_ZERO_EVENT = 1,
    MDR_TIMER_STATUS_CNT_ARR_EVENT  = 1  << 1,
    MDR_TIMER_STATUS_ETR_RE_EVENT   = 1  << 2,
    MDR_TIMER_STATUS_ETR_FE_EVENT   = 1  << 3,
    MDR_TIMER_STATUS_BRK_EVENT      = 1  << 4,
    MDR_TIMER_STATUS_CCR_CAP_EVENT  = 15 << 5,
    MDR_TIMER_STATUS_CCR_REF_EVENT  = 15 << 9,
    MDR_TIMER_STATUS_CCR_CAP1_EVENT = 15 << 13,
};

enum MDR_TIMER_IE {
    MDR_TIMER_IE_CNT_ZERO_EVENT_IE = 1,
    MDR_TIMER_IE_CNT_ARR_EVENT_IE  = 1  << 1,
    MDR_TIMER_IE_ETR_RE_EVENT_IE   = 1  << 2,
    MDR_TIMER_IE_ETR_FE_EVENT_IE   = 1  << 3,
    MDR_TIMER_IE_BRK_EVENT_IE      = 1  << 4,
    MDR_TIMER_IE_CCR_CAP_EVENT_IE  = 15 << 5,
    MDR_TIMER_IE_CCR_REF_EVENT_IE  = 15 << 9,
    MDR_TIMER_IE_CCR_CAP1_EVENT_IE = 15 << 13,
};

enum MDR_TIMER_DMA_RE {
    MDR_TIMER_DMA_RE_CNT_ZERO_EVENT_RE = 1,
    MDR_TIMER_DMA_RE_CNT_ARR_EVENT_RE  = 1  << 1,
    MDR_TIMER_DMA_RE_ETR_RE_EVENT_RE   = 1  << 2,
    MDR_TIMER_DMA_RE_ETR_FE_EVENT_RE   = 1  << 3,
    MDR_TIMER_DMA_RE_BRK_EVENT_RE      = 1  << 4,
    MDR_TIMER_DMA_RE_CCR_CAP_EVENT_RE  = 15 << 5,
    MDR_TIMER_DMA_RE_CCR_REF_EVENT_RE  = 15 << 9,
    MDR_TIMER_DMA_RE_CCR_CAP1_EVENT_RE = 15 << 13,
};

/*
    MDR_ADC
*/

typedef struct {
    volatile bit_depth_t adc1_cfg;
    volatile bit_depth_t adc2_cfg;
    volatile bit_depth_t adc1_h_level;
    volatile bit_depth_t adc2_h_level;
    volatile bit_depth_t adc1_l_level;
    volatile bit_depth_t adc2_l_level;
    const volatile bit_depth_t adc1_result;
    const volatile bit_depth_t adc2_result;
    volatile bit_depth_t adc1_status;
    volatile bit_depth_t adc2_status;
    volatile bit_depth_t adc1_chsel;
    volatile bit_depth_t adc2_chsel;
} mdr_adc_t;

#define MDR_ADC ((volatile mdr_adc_t*) 0x40088000)

enum MDR_ADC_ADC1_CFG {
    MDR_ADC_ADC1_CFG_CFG_REG_ADON    = 1,
    MDR_ADC_ADC1_CFG_CFG_REG_GO      = 1  << 1,
    MDR_ADC_ADC1_CFG_CFG_REG_CLKS    = 1  << 2,
    MDR_ADC_ADC1_CFG_CFG_REG_SAMPLE  = 1  << 3,
    MDR_ADC_ADC1_CFG_CFG_REG_CHS     = 31 << 4,
    MDR_ADC_ADC1_CFG_CFG_REG_CHCH    = 1  << 9,
    MDR_ADC_ADC1_CFG_CFG_REG_RNGC    = 1  << 10,
    MDR_ADC_ADC1_CFG_CFG_M_REF       = 1  << 11,
    MDR_ADC_ADC1_CFG_CFG_REG_DIVCLK  = 15 << 12,
    MDR_ADC_ADC1_CFG_CFG_SYNC_CONVER = 1  << 16,
    MDR_ADC_ADC1_CFG_TS_EN           = 1  << 17,
    MDR_ADC_ADC1_CFG_TS_BUF_EN       = 1  << 18,
    MDR_ADC_ADC1_CFG_SEL_TS          = 1  << 19,
    MDR_ADC_ADC1_CFG_SEL_VREF        = 1  << 20,
    MDR_ADC_ADC1_CFG_TR              = 15 << 21,
    MDR_ADC_ADC1_CFG_DELAY_GO        = 7  << 25,
    MDR_ADC_ADC1_CFG_DELAY_ADC       = 15 << 28,
};

enum MDR_ADC_ADC2_CFG {
    MDR_ADC_ADC2_CFG_CFG_REG_ADON   = 1,
    MDR_ADC_ADC2_CFG_CFG_REG_GO     = 1  << 1,
    MDR_ADC_ADC2_CFG_CFG_REG_CLKS   = 1  << 2,
    MDR_ADC_ADC2_CFG_CFG_REG_SAMPLE = 1  << 3,
    MDR_ADC_ADC2_CFG_CFG_REG_CHS    = 31 << 4,
    MDR_ADC_ADC2_CFG_CFG_REG_CHCH   = 1  << 9,
    MDR_ADC_ADC2_CFG_CFG_REG_RNGC   = 1  << 10,
    MDR_ADC_ADC2_CFG_CFG_M_REF      = 1  << 11,
    MDR_ADC_ADC2_CFG_CFG_REG_DIVCLK = 15 << 12,
    MDR_ADC_ADC2_CFG_ADC1_OP        = 1  << 17,
    MDR_ADC_ADC2_CFG_ADC2_OP        = 1  << 18,
    MDR_ADC_ADC2_CFG_DELAY_GO       = 7  << 25,
};

enum MDR_ADC_ADC_H_LEVEL {
    MDR_ADC_ADC_H_LEVEL_REG_H_LEVEL = 4095,
};

enum MDR_ADC_ADC_L_LEVEL {
    MDR_ADC_ADC_L_LEVEL_REG_L_LEVEL = 4095,
};

enum MDR_ADC_ADC_RESULT {
    MDR_ADC_ADC_RESULT_RESULT  = 4095,
    MDR_ADC_ADC_RESULT_CHANNEL = 15   << 16,
};

enum MDR_ADC_ADC_STATUS {
    MDR_ADC_ADC_STATUS_FLG_REG_OVERWRITE = 1,
    MDR_ADC_ADC_STATUS_FLG_REG_AWOIFEN   = 1 << 1,
    MDR_ADC_ADC_STATUS_FLG_REG_EOCIF     = 1 << 2,
    MDR_ADC_ADC_STATUS_AWOIF_IE          = 1 << 3,
    MDR_ADC_ADC_STATUS_EOCIF_IE          = 1 << 4,
};

/*
    MDR_DAC
*/

typedef struct {
    volatile bit_depth_t cfg;
    volatile bit_depth_t dac1_data;
    volatile bit_depth_t dac2_data;
} mdr_dac_t;

#define MDR_DAC ((volatile mdr_dac_t*) 0x40090000)

enum MDR_DAC_CFG {
    MDR_DAC_CFG_CFG_M_REF0  = 1,
    MDR_DAC_CFG_CFG_M_REF1  = 1 << 1,
    MDR_DAC_CFG_CFG_ON_DAC0 = 1 << 2,
    MDR_DAC_CFG_CFG_ON_DAC1 = 1 << 3,
    MDR_DAC_CFG_CFG_SYNC_A  = 1 << 4
};

enum MDR_DAC1_DATA {
    MDR_DAC1_DATA_DAC0_DATA = 4095,
    MDR_DAC1_DATA_DAC1_DATA = 4095 << 16,
};

enum MDR_DAC2_DATA {
    MDR_DAC2_DATA_DAC1_DATA = 4095,
    MDR_DAC2_DATA_DAC0_DATA = 4095 << 16,
};

/*
    MDR_COMP
*/

typedef struct {
    volatile bit_depth_t cfg;
    volatile bit_depth_t result;
    volatile bit_depth_t result_latch;
} mdr_comp_t;

#define MDR_COMP ((volatile mdr_comp_t*) 0x40098000)

enum MDR_COMP_CFG {
    MDR_COMP_CFG_ON           = 1,
    MDR_COMP_CFG_CVRR         = 1  << 1,
    MDR_COMP_CFG_CVRSS        = 1  << 2,
    MDR_COMP_CFG_CVREN        = 1  << 3,
    MDR_COMP_CFG_CVR          = 15 << 4,
    MDR_COMP_CFG_CREF         = 1  << 8,
    MDR_COMP_CFG_CCH          = 3  << 9,
    MDR_COMP_CFG_INV          = 1  << 11,
    MDR_COMP_CFG_READY        = 1  << 12,
    MDR_COMP_CFG_READY_CMP_IE = 1  << 13,
};

enum MDR_COMP_RESULT {
    MDR_COMP_RESULT_RSLT_SY = 1,
    MDR_COMP_RESULT_RSLT_AS = 1 << 1,
    MDR_COMP_RESULT_RT_LCH  = 1 << 2,
};

enum MDR_COMP_RESULT_LATCH {
    MDR_COMP_RESULT_LATCH_RST_LCH = 1,
};

/*
    MDR_I2C
*/

typedef struct {
    volatile bit_depth_t prl;
    volatile bit_depth_t prh;
    volatile bit_depth_t ctr;
    const volatile bit_depth_t rxd;
    const volatile bit_depth_t sta;
    volatile bit_depth_t txd;
    volatile bit_depth_t cmd;
} mdr_i2c_t;

#define MDR_I2C ((volatile mdr_i2c_t*) 0x40050000)

enum MDR_I2C_PRL {
    MDR_I2C_PRL_PR = 255,
};

enum MDR_I2C_PRH {
    MDR_I2C_PRH_PR = 255,
};

enum MDR_I2C_CTR {
    MDR_I2C_CTR_S_I2C  = 1 << 5,
    MDR_I2C_CTR_EN_INT = 1 << 6,
    MDR_I2C_CTR_EN_I2C = 1 << 7,
};

enum MDR_I2C_RXD {
    MDR_I2C_RXD_RXD = 255,
};

enum MDR_I2C_STA {
    MDR_I2C_STA_INT      = 1,
    MDR_I2C_STA_TR_PROG  = 1 << 1,
    MDR_I2C_STA_LOST_ARB = 1 << 5,
    MDR_I2C_STA_BUSY     = 1 << 6,
    MDR_I2C_STA_RX_ACK   = 1 << 7,
};

enum MDR_I2C_TXD {
    MDR_I2C_TXD_TXD = 255,
};

enum MDR_I2C_CMD {
    MDR_I2C_CMD_CLR_INT = 1,
    MDR_I2C_CMD_ACK     = 1 << 3,
    MDR_I2C_CMD_WR      = 1 << 4,
    MDR_I2C_CMD_RD      = 1 << 5,
    MDR_I2C_CMD_STOP    = 1 << 6,
    MDR_I2C_CMD_START   = 1 << 7,
};

/*
    MDR_SSP
*/

typedef struct {
    volatile bit_depth_t cr0;
    volatile bit_depth_t cr1;
    volatile bit_depth_t dr;
    const volatile bit_depth_t sr;
    volatile bit_depth_t cpsr;
    volatile bit_depth_t imsc;
    const volatile bit_depth_t ris;
    const volatile bit_depth_t mis;
    volatile bit_depth_t icr;
    volatile bit_depth_t dmacr;
} mdr_ssp_t;

#define MDR_SSP1 ((volatile mdr_ssp_t*) 0x40040000)
#define MDR_SSP2 ((volatile mdr_ssp_t*) 0x400A0000)

enum MDR_SSP_CR0 {
    MDR_SSP_CR0_DSS = 15,
    MDR_SSP_CR0_FRF = 3  << 4,
    MDR_SSP_CR0_SPO = 1  << 6,
    MDR_SSP_CR0_SPH = 1  << 7,
    MDR_SSP_CR0_SCR = 15 << 8,
};

enum MDR_SSP_CR1 {
    MDR_SSP_CR1_LBM = 1,
    MDR_SSP_CR1_SSE = 1 << 1,
    MDR_SSP_CR1_MS  = 1 << 2,
    MDR_SSP_CR1_SOD = 1 << 3,
};

enum MDR_SSP_DR {
    MDR_SSP_DR_DATA = 65535,
};

enum MDR_SSP_SR {
    MDR_SSP_SR_TFE = 1,
    MDR_SSP_SR_TNF = 1 << 1,
    MDR_SSP_SR_RNE = 1 << 2,
    MDR_SSP_SR_RFF = 1 << 3,
    MDR_SSP_SR_BSY = 1 << 4,
};

enum MDR_SSP_CPSR {
    MDR_SSP_CPSR_CPSDVSR = 255,
};

enum MDR_SSP_IMSC {
    MDR_SSP_IMSC_RORIM = 1,
    MDR_SSP_IMSC_RTIM  = 1 << 1,
    MDR_SSP_IMSC_RXIM  = 1 << 2,
    MDR_SSP_IMSC_TXIM  = 1 << 3,
};

enum MDR_SSP_RIS {
    MDR_SSP_RIS_RORRIS = 1,
    MDR_SSP_RIS_RTRIS  = 1 << 1,
    MDR_SSP_RIS_RXRIS  = 1 << 2,
    MDR_SSP_RIS_TXRIS  = 1 << 3,
};

enum MDR_SSP_MIS {
    MDR_SSP_MIS_RORMIS = 1,
    MDR_SSP_MIS_RTMIS  = 1 << 1,
    MDR_SSP_MIS_RXMIS  = 1 << 2,
    MDR_SSP_MIS_TXMIS  = 1 << 3,
};

enum MDR_SSP_ICR {
    MDR_SSP_ICR_RORIC = 1,
    MDR_SSP_ICR_RTIC  = 1 << 1,
};

enum MDR_SSP_DMACR {
    MDR_SSP_DMACR_RXDMAE = 1,
    MDR_SSP_DMACR_TXDMAE = 1 << 1,
};

/*
    MDR_UART
*/

#pragma pack(push, 1)
typedef struct {
    volatile bit_depth_t dr;
    volatile bit_depth_t rsr_ecr;
    const char _padding_0[0x10];
    const volatile bit_depth_t fr;
    const char _padding_1[0x4];
    volatile bit_depth_t ilpr;
    volatile bit_depth_t ibrd;
    volatile bit_depth_t fbrd;
    volatile bit_depth_t lcr_h;
    volatile bit_depth_t cr;
    volatile bit_depth_t ifls;
    volatile bit_depth_t imsc;
    const volatile bit_depth_t ris;
    const volatile bit_depth_t mis;
    volatile bit_depth_t icr;
    volatile bit_depth_t dmacr;
} mdr_uart_t;
#pragma pack(pop)

#define MDR_UART1 ((volatile mdr_uart_t*) 0x40030000)
#define MDR_UARD2 ((volatile mdr_uart_t*) 0x40038000)

enum MDR_UARD_DR {
    MDR_UARD_DR_DATA = 255,
    MDR_UARD_DR_FE   = 1   << 8,
    MDR_UARD_DR_PE   = 1   << 9,
    MDR_UARD_DR_BE   = 1   << 10,
    MDR_UARD_DR_OE   = 1   << 11,
};

enum MDR_UART_RSR_ECR {
    MDR_UART_RSR_ECR_FE = 1,
    MDR_UART_RSR_ECR_PE = 1 << 1,
    MDR_UART_RSR_ECR_BE = 1 << 2,
    MDR_UART_RSR_ECR_OE = 1 << 3,
};

enum MDR_UART_FR {
    MDR_UART_FR_CTS  = 1,
    MDR_UART_FR_DSR  = 1 << 1,
    MDR_UART_FR_DCD  = 1 << 2,
    MDR_UART_FR_BUSY = 1 << 3,
    MDR_UART_FR_RXFE = 1 << 4,
    MDR_UART_FR_TXFF = 1 << 5,
    MDR_UART_FR_RXFF = 1 << 6,
    MDR_UART_FR_TXFE = 1 << 7,
    MDR_UART_FR_RI   = 1 << 8,
};

enum MDR_UART_ILPR {
    MDR_UART_ILPR_ILPDVSR = 255,
};

enum MDR_UART_IBRD {
    MDR_UART_IBRD_BAUDDIV_INT = 65535,
};

enum MDR_UART_FBRD {
    MDR_UART_FBRD_BAUDDIV_FRAC = 63,
};

enum MDR_UART_LCR_H {
    MDR_UART_LCR_H_BRK  = 1,
    MDR_UART_LCR_H_PEN  = 1 << 1,
    MDR_UART_LCR_H_EPS  = 1 << 2,
    MDR_UART_LCR_H_STP2 = 1 << 3,
    MDR_UART_LCR_H_FEN  = 1 << 4,
    MDR_UART_LCR_H_WLEN = 3 << 5,
    MDR_UART_LCR_H_SPS  = 1 << 7,
};

enum MDR_UART_CR {
    MDR_UART_CR_UARTEN = 1,
    MDR_UART_CR_SIREN  = 1 << 1,
    MDR_UART_CR_SIRLP  = 1 << 2,
    MDR_UART_CR_LBE    = 1 << 7,
    MDR_UART_CR_TXE    = 1 << 8,
    MDR_UART_CR_RXE    = 1 << 9,
    MDR_UART_CR_DTR    = 1 << 10,
    MDR_UART_CR_RTS    = 1 << 11,
    MDR_UART_CR_OUT1   = 1 << 12,
    MDR_UART_CR_OUT2   = 1 << 13,
    MDR_UART_CR_RTS_EN = 1 << 14,
    MDR_UART_CR_CTS_EN = 1 << 15,
};

enum MDR_UART_IFLS {
    MDR_UART_IFLS_TXIFLSEL = 7,
    MDR_UART_IFLS_RXIFLSEL = 7 << 3,
};

enum MDR_UART_IMSC {
    MDR_UART_IMSC_RIMIM = 1,
    MDR_UART_IMSC_CTSMIM = 1 << 1,
    MDR_UART_IMSC_DCDMIM = 1 << 2,
    MDR_UART_IMSC_DSRMIM = 1 << 3,
    MDR_UART_IMSC_RXIM   = 1 << 4,
    MDR_UART_IMSC_TXIM   = 1 << 5,
    MDR_UART_IMSC_RTIM   = 1 << 6,
    MDR_UART_IMSC_FEIM   = 1 << 7,
    MDR_UART_IMSC_PEIM   = 1 << 8,
    MDR_UART_IMSC_BEIM   = 1 << 9,
    MDR_UART_IMSC_OEIM   = 1 << 10,
};

enum MDR_UART_RIS {
    MDR_UART_RIS_RIRMIS  = 1,
    MDR_UART_RIS_CTSRMIS = 1 << 1,
    MDR_UART_RIS_DCDRMIS = 1 << 2,
    MDR_UART_RIS_DSRRMIS = 1 << 3,
    MDR_UART_RIS_RXRIS   = 1 << 4,
    MDR_UART_RIS_TXRIS   = 1 << 5,
    MDR_UART_RIS_RTRIS   = 1 << 6,
    MDR_UART_RIS_FERIS   = 1 << 7,
    MDR_UART_RIS_PERIS   = 1 << 8,
    MDR_UART_RIS_BERIS   = 1 << 9,
    MDR_UART_RIS_OERIS   = 1 << 10,
};

enum MDR_UART_MIS {
    MDR_UART_MIS_RIMMIS  = 1,
    MDR_UART_MIS_CTSMMIS = 1 << 1,
    MDR_UART_MIS_DCDMMIS = 1 << 2,
    MDR_UART_MIS_DSRMMIS = 1 << 3,
    MDR_UART_MIS_RXMIS   = 1 << 4,
    MDR_UART_MIS_TXMIS   = 1 << 5,
    MDR_UART_MIS_RTMIS   = 1 << 6,
    MDR_UART_MIS_FEMIS   = 1 << 7,
    MDR_UART_MIS_PEMIS   = 1 << 8,
    MDR_UART_MIS_BEMIS   = 1 << 9,
    MDR_UART_MIS_OEMIS   = 1 << 10
};

enum MDR_UART_ICR {
    MDR_UART_ICR_RIMIC  = 1,
    MDR_UART_ICR_CTSMIC = 1 << 1,
    MDR_UART_ICR_DCDMIC = 1 << 2,
    MDR_UART_ICR_DSRMIC = 1 << 3,
    MDR_UART_ICR_RXIC   = 1 << 4,
    MDR_UART_ICR_TXIC   = 1 << 5,
    MDR_UART_ICR_RTIC   = 1 << 6,
    MDR_UART_ICR_FEIC   = 1 << 7,
    MDR_UART_ICR_PEIC   = 1 << 8,
    MDR_UART_ICR_BEIC   = 1 << 9,
    MDR_UART_ICR_OEIC   = 1 << 10,
};

enum MDR_UART_DMACR {
    MDR_UART_DMACR_RXDMAE   = 1,
    MDR_UART_DMACR_TXDMAE   = 1 << 1,
    MDR_UART_DMACR_DMAONERR = 1 << 2,
};

/*
    MDR_DMA
*/

#pragma pack(push, 1)
typedef struct {
    const volatile bit_depth_t status;
    volatile bit_depth_t cfg;
    volatile bit_depth_t ctrl_base_ptr;
    const volatile bit_depth_t alt_ctrl_base_ptr;
    const volatile bit_depth_t waitonreq_status;
    volatile bit_depth_t chnl_sw_request;
    volatile bit_depth_t chnl_useburst_set;
    volatile bit_depth_t chnl_useburst_clr;
    volatile bit_depth_t chnl_req_mask_set;
    volatile bit_depth_t chnl_req_mask_clr;
    volatile bit_depth_t chnl_enable_set;
    volatile bit_depth_t chnl_enable_clr;
    volatile bit_depth_t chnl_pri_alt_set;
    volatile bit_depth_t chnl_pri_alt_clr;
    volatile bit_depth_t chnl_priority_set;
    volatile bit_depth_t chnl_priority_clr;
    const char _padding_0[0xC];
    volatile bit_depth_t err_clr;
} mdr_dma_t;
#pragma pack(pop)

#define MDR_DMA ((volatile mdr_dma_t*) 0x40028000)

enum MDR_DMA_STATUS {
    MDR_DMA_STATUS_MASTER_ENABLE = 1,
    MDR_DMA_STATUS_STATE         = 15 << 4,
    MDR_DMA_STATUS_CHNLS_MINUS1  = 31 << 16,
    MDR_DMA_STATUS_TEST_STATUS   = 15 << 28,
};

enum MDR_DMA_CFG {
    MDR_DMA_CFG_MASTER_ENABLE  = 1,
    MDR_DMA_CFG_CHNL_PROT_CTRL = 7 << 5,
};

enum MDR_DMA_CTRL_BASE_PTR {
    MDR_DMA_CTRL_BASE_PTR_CTRL_BASE_PTR = 4194303 << 10,
};

enum MDR_DMA_WAITONREQ_STATUS {
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_0  = 1,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_1  = 1 << 1,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_2  = 1 << 2,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_3  = 1 << 3,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_4  = 1 << 4,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_5  = 1 << 5,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_6  = 1 << 6,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_7  = 1 << 7,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_8  = 1 << 8,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_9  = 1 << 9,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_10 = 1 << 10,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_11 = 1 << 11,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_12 = 1 << 12,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_13 = 1 << 13,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_14 = 1 << 14,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_15 = 1 << 15,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_16 = 1 << 16,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_17 = 1 << 17,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_18 = 1 << 18,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_19 = 1 << 19,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_20 = 1 << 20,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_21 = 1 << 21,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_22 = 1 << 22,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_23 = 1 << 23,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_24 = 1 << 24,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_25 = 1 << 25,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_26 = 1 << 26,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_27 = 1 << 27,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_28 = 1 << 28,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_29 = 1 << 29,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_30 = 1 << 30,
    MDR_DMA_WAITONREQ_STATUS_DMA_WAITONREG_STATUS_FOR_DMA_WAITNREG_31 = 1 << 31,
};

enum MDR_DMA_CHNL_SW_REQUEST {
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_0  = 1,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_1  = 1 << 1,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_2  = 1 << 2,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_3  = 1 << 3,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_4  = 1 << 4,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_5  = 1 << 5,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_6  = 1 << 6,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_7  = 1 << 7,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_8  = 1 << 8,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_9  = 1 << 9,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_10 = 1 << 10,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_11 = 1 << 11,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_12 = 1 << 12,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_13 = 1 << 13,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_14 = 1 << 14,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_15 = 1 << 15,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_16 = 1 << 16,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_17 = 1 << 17,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_18 = 1 << 18,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_19 = 1 << 19,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_20 = 1 << 20,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_21 = 1 << 21,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_22 = 1 << 22,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_23 = 1 << 23,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_24 = 1 << 24,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_25 = 1 << 25,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_26 = 1 << 26,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_27 = 1 << 27,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_28 = 1 << 28,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_29 = 1 << 29,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_30 = 1 << 30,
    MDR_DMA_CHNL_SW_REQUEST_CHNL_SW_REQUEST_FOR_CHANNEL_31 = 1 << 31,
};

enum MDR_DMA_CHNL_USEBURST_SET {
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_0  = 1,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_1  = 1 << 1,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_2  = 1 << 2,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_3  = 1 << 3,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_4  = 1 << 4,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_5  = 1 << 5,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_6  = 1 << 6,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_7  = 1 << 7,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_8  = 1 << 8,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_9  = 1 << 9,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_10 = 1 << 10,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_11 = 1 << 11,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_12 = 1 << 12,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_13 = 1 << 13,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_14 = 1 << 14,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_15 = 1 << 15,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_16 = 1 << 16,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_17 = 1 << 17,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_18 = 1 << 18,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_19 = 1 << 19,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_20 = 1 << 20,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_21 = 1 << 21,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_22 = 1 << 22,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_23 = 1 << 23,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_24 = 1 << 24,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_25 = 1 << 25,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_26 = 1 << 26,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_27 = 1 << 27,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_28 = 1 << 28,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_29 = 1 << 29,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_30 = 1 << 30,
    MDR_DMA_CHNL_USEBURST_SET_CHNL_USEBURST_SET_FOR_CHANNEL_31 = 1 << 31,
};

enum MDR_DMA_CHNL_USEBURST_CLR {
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_0  = 1,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_1  = 1 << 1,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_2  = 1 << 2,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_3  = 1 << 3,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_4  = 1 << 4,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_5  = 1 << 5,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_6  = 1 << 6,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_7  = 1 << 7,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_8  = 1 << 8,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_9  = 1 << 9,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_10 = 1 << 10,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_11 = 1 << 11,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_12 = 1 << 12,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_13 = 1 << 13,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_14 = 1 << 14,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_15 = 1 << 15,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_16 = 1 << 16,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_17 = 1 << 17,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_18 = 1 << 18,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_19 = 1 << 19,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_20 = 1 << 20,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_21 = 1 << 21,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_22 = 1 << 22,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_23 = 1 << 23,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_24 = 1 << 24,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_25 = 1 << 25,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_26 = 1 << 26,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_27 = 1 << 27,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_28 = 1 << 28,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_29 = 1 << 29,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_30 = 1 << 30,
    MDR_DMA_CHNL_USEBURST_CLR_CHNL_USEBURST_CLR_FOR_CHANNEL_31 = 1 << 31,
};

enum MDR_DMA_CHNL_REQ_MASK_SET {
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_0  = 1,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_1  = 1 << 1,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_2  = 1 << 2,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_3  = 1 << 3,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_4  = 1 << 4,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_5  = 1 << 5,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_6  = 1 << 6,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_7  = 1 << 7,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_8  = 1 << 8,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_9  = 1 << 9,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_10 = 1 << 10,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_11 = 1 << 11,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_12 = 1 << 12,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_13 = 1 << 13,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_14 = 1 << 14,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_15 = 1 << 15,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_16 = 1 << 16,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_17 = 1 << 17,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_18 = 1 << 18,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_19 = 1 << 19,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_20 = 1 << 20,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_21 = 1 << 21,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_22 = 1 << 22,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_23 = 1 << 23,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_24 = 1 << 24,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_25 = 1 << 25,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_26 = 1 << 26,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_27 = 1 << 27,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_28 = 1 << 28,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_29 = 1 << 29,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_30 = 1 << 30,
    MDR_DMA_CHNL_REQ_MASK_SET_CHNL_REG_MASK_SET_FOR_DMA_REQ_AND_DMA_SREQ_31 = 1 << 31,
};

enum MDR_DMA_CHNL_REQ_MASK_CLR {
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_0  = 1,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_1  = 1 << 1,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_2  = 1 << 2,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_3  = 1 << 3,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_4  = 1 << 4,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_5  = 1 << 5,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_6  = 1 << 6,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_7  = 1 << 7,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_8  = 1 << 8,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_9  = 1 << 9,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_10 = 1 << 10,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_11 = 1 << 11,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_12 = 1 << 12,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_13 = 1 << 13,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_14 = 1 << 14,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_15 = 1 << 15,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_16 = 1 << 16,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_17 = 1 << 17,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_18 = 1 << 18,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_19 = 1 << 19,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_20 = 1 << 20,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_21 = 1 << 21,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_22 = 1 << 22,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_23 = 1 << 23,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_24 = 1 << 24,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_25 = 1 << 25,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_26 = 1 << 26,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_27 = 1 << 27,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_28 = 1 << 28,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_29 = 1 << 29,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_30 = 1 << 30,
    MDR_DMA_CHNL_REQ_MASK_CLR_CHNL_REG_MASK_CLR_FOR_DMA_REQ_AND_DMA_SREQ_31 = 1 << 31,
};

enum MDR_DMA_CHNL_ENABLE_SET {
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_0  = 1,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_1  = 1 << 1,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_2  = 1 << 2,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_3  = 1 << 3,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_4  = 1 << 4,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_5  = 1 << 5,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_6  = 1 << 6,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_7  = 1 << 7,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_8  = 1 << 8,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_9  = 1 << 9,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_10 = 1 << 10,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_11 = 1 << 11,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_12 = 1 << 12,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_13 = 1 << 13,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_14 = 1 << 14,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_15 = 1 << 15,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_16 = 1 << 16,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_17 = 1 << 17,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_18 = 1 << 18,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_19 = 1 << 19,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_20 = 1 << 20,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_21 = 1 << 21,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_22 = 1 << 22,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_23 = 1 << 23,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_24 = 1 << 24,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_25 = 1 << 25,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_26 = 1 << 26,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_27 = 1 << 27,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_28 = 1 << 28,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_29 = 1 << 29,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_30 = 1 << 30,
    MDR_DMA_CHNL_ENABLE_SET_CHNL_ENABLE_SET_FOR_CHANNEL_31 = 1 << 31,
};

enum MDR_DMA_CHNL_ENABLE_CLR {
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_0  = 1,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_1  = 1 << 1,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_2  = 1 << 2,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_3  = 1 << 3,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_4  = 1 << 4,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_5  = 1 << 5,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_6  = 1 << 6,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_7  = 1 << 7,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_8  = 1 << 8,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_9  = 1 << 9,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_10 = 1 << 10,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_11 = 1 << 11,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_12 = 1 << 12,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_13 = 1 << 13,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_14 = 1 << 14,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_15 = 1 << 15,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_16 = 1 << 16,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_17 = 1 << 17,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_18 = 1 << 18,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_19 = 1 << 19,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_20 = 1 << 20,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_21 = 1 << 21,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_22 = 1 << 22,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_23 = 1 << 23,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_24 = 1 << 24,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_25 = 1 << 25,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_26 = 1 << 26,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_27 = 1 << 27,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_28 = 1 << 28,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_29 = 1 << 29,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_30 = 1 << 30,
    MDR_DMA_CHNL_ENABLE_CLR_CHNL_ENABLE_CLR_FOR_CHANNEL_31 = 1 << 31,
};

enum MDR_DMA_CHNL_PRI_ALT_SET {
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_0  = 1,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_1  = 1 << 1,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_2  = 1 << 2,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_3  = 1 << 3,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_4  = 1 << 4,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_5  = 1 << 5,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_6  = 1 << 6,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_7  = 1 << 7,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_8  = 1 << 8,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_9  = 1 << 9,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_10 = 1 << 10,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_11 = 1 << 11,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_12 = 1 << 12,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_13 = 1 << 13,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_14 = 1 << 14,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_15 = 1 << 15,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_16 = 1 << 16,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_17 = 1 << 17,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_18 = 1 << 18,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_19 = 1 << 19,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_20 = 1 << 20,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_21 = 1 << 21,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_22 = 1 << 22,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_23 = 1 << 23,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_24 = 1 << 24,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_25 = 1 << 25,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_26 = 1 << 26,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_27 = 1 << 27,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_28 = 1 << 28,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_29 = 1 << 29,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_30 = 1 << 30,
    MDR_DMA_CHNL_PRI_ALT_SET_CHNL_PRI_ALT_SET_FOR_CHANNEL_31 = 1 << 31,
};

enum MDR_DMA_CHNL_PRI_ALT_CLR {
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_0  = 1,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_1  = 1 << 1,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_2  = 1 << 2,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_3  = 1 << 3,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_4  = 1 << 4,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_5  = 1 << 5,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_6  = 1 << 6,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_7  = 1 << 7,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_8  = 1 << 8,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_9  = 1 << 9,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_10 = 1 << 10,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_11 = 1 << 11,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_12 = 1 << 12,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_13 = 1 << 13,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_14 = 1 << 14,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_15 = 1 << 15,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_16 = 1 << 16,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_17 = 1 << 17,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_18 = 1 << 18,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_19 = 1 << 19,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_20 = 1 << 20,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_21 = 1 << 21,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_22 = 1 << 22,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_23 = 1 << 23,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_24 = 1 << 24,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_25 = 1 << 25,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_26 = 1 << 26,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_27 = 1 << 27,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_28 = 1 << 28,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_29 = 1 << 29,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_30 = 1 << 30,
    MDR_DMA_CHNL_PRI_ALT_CLR_CHNL_PRI_ALT_CLR_FOR_CHANNEL_31 = 1 << 31,
};

enum MDR_DMA_CHNL_PRIORITY_SET {
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_0  = 1,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_1  = 1 << 1,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_2  = 1 << 2,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_3  = 1 << 3,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_4  = 1 << 4,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_5  = 1 << 5,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_6  = 1 << 6,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_7  = 1 << 7,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_8  = 1 << 8,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_9  = 1 << 9,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_10 = 1 << 10,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_11 = 1 << 11,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_12 = 1 << 12,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_13 = 1 << 13,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_14 = 1 << 14,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_15 = 1 << 15,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_16 = 1 << 16,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_17 = 1 << 17,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_18 = 1 << 18,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_19 = 1 << 19,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_20 = 1 << 20,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_21 = 1 << 21,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_22 = 1 << 22,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_23 = 1 << 23,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_24 = 1 << 24,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_25 = 1 << 25,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_26 = 1 << 26,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_27 = 1 << 27,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_28 = 1 << 28,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_29 = 1 << 29,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_30 = 1 << 30,
    MDR_DMA_CHNL_PRIORITY_SET_CHNL_PRIORITY_SET_FOR_CHANNEL_31 = 1 << 31,
};

enum MDR_DMA_CHNL_PRIORITY_CLR {
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_0  = 1,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_1  = 1 << 1,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_2  = 1 << 2,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_3  = 1 << 3,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_4  = 1 << 4,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_5  = 1 << 5,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_6  = 1 << 6,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_7  = 1 << 7,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_8  = 1 << 8,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_9  = 1 << 9,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_10 = 1 << 10,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_11 = 1 << 11,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_12 = 1 << 12,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_13 = 1 << 13,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_14 = 1 << 14,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_15 = 1 << 15,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_16 = 1 << 16,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_17 = 1 << 17,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_18 = 1 << 18,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_19 = 1 << 19,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_20 = 1 << 20,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_21 = 1 << 21,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_22 = 1 << 22,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_23 = 1 << 23,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_24 = 1 << 24,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_25 = 1 << 25,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_26 = 1 << 26,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_27 = 1 << 27,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_28 = 1 << 28,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_29 = 1 << 29,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_30 = 1 << 30,
    MDR_DMA_CHNL_PRIORITY_CLR_CHNL_PRIORITY_CLR_FOR_CHANNEL_31 = 1 << 31,
};

enum MDR_DMA_ERR_CLR {
    MDR_DMA_ERR_CLR = 1,
};

/*
    NVIC
*/

#pragma pack(push, 1)
typedef struct {
    volatile bit_depth_t iser_0;
    volatile bit_depth_t iser_1;
    volatile bit_depth_t iser_2;
    volatile bit_depth_t iser_3;
    volatile bit_depth_t iser_4;
    volatile bit_depth_t iser_5;
    volatile bit_depth_t iser_6;
    volatile bit_depth_t iser_7;
    const char _padding_0[0x60];
    volatile bit_depth_t icer_0;
    volatile bit_depth_t icer_1;
    volatile bit_depth_t icer_2;
    volatile bit_depth_t icer_3;
    volatile bit_depth_t icer_4;
    volatile bit_depth_t icer_5;
    volatile bit_depth_t icer_6;
    volatile bit_depth_t icer_7;
    volatile bit_depth_t ispr_0;
    volatile bit_depth_t ispr_1;
    volatile bit_depth_t ispr_2;
    volatile bit_depth_t ispr_3;
    volatile bit_depth_t ispr_4;
    volatile bit_depth_t ispr_5;
    volatile bit_depth_t ispr_6;
    volatile bit_depth_t ispr_7;
    const char _padding_1[0x60];
    volatile bit_depth_t icpr_0;
    volatile bit_depth_t icpr_1;
    volatile bit_depth_t icpr_2;
    volatile bit_depth_t icpr_3;
    volatile bit_depth_t icpr_4;
    volatile bit_depth_t icpr_5;
    volatile bit_depth_t icpr_6;
    volatile bit_depth_t icpr_7;
    const volatile bit_depth_t iabr_0;
    const volatile bit_depth_t iabr_1;
    const volatile bit_depth_t iabr_2;
    const volatile bit_depth_t iabr_3;
    const volatile bit_depth_t iabr_4;
    const volatile bit_depth_t iabr_5;
    const volatile bit_depth_t iabr_6;
    const volatile bit_depth_t iabr_7;
    const char _padding_2[0xE0];
    volatile bit_depth_t ipr_0;
    volatile bit_depth_t ipr_1;
    volatile bit_depth_t ipr_2;
    volatile bit_depth_t ipr_3;
    volatile bit_depth_t ipr_4;
    volatile bit_depth_t ipr_5;
    volatile bit_depth_t ipr_6;
    volatile bit_depth_t ipr_7;
    const char _padding_3[0xAE0];
    volatile bit_depth_t stir;
} nvic_t;
#pragma pack(pop)

#define NVIC ((volatile nvic_t*) 0xE000E100)

enum NVIC_IPR {
    NVIC_IPR_IP_0 = 7 << 5,
    NVIC_IPR_IP_1 = 7 << 13,
    NVIC_IPR_IP_2 = 7 << 21,
    NVIC_IPR_IP_3 = 7 << 29,
};

enum NVIC_STIR {
    NVIC_STIR_INTID = 511,
};

/*
    SCB
*/

#pragma pack(push, 1)
typedef struct {
    const char _padding_0[0x8];
    volatile bit_depth_t actlr;
} interrupt_t;
#pragma pack(push)

#define INTERRUPT_TYPE ((volatile bit_depth_terrupt_t*) 0xE000E000)

enum INTERRUPT_TYPE_ACTLR {
    INTERRUPT_TYPE_ACTLR_DISMCYCINT = 1,
    INTERRUPT_TYPE_ACTLR_DISDEFWBUF = 1 << 1,
    INTERRUPT_TYPE_ACTLR_DISFOLD    = 1 << 2,
};

#pragma pack(push, 1)
typedef struct {
    const volatile bit_depth_t cpuid;
    volatile bit_depth_t icsr;
    volatile bit_depth_t vtor;
    volatile bit_depth_t aircr;
    volatile bit_depth_t scr;
    volatile bit_depth_t ccr;
    volatile bit_depth_t shpr1;
    volatile bit_depth_t shpr2;
    volatile bit_depth_t shpr3;
    volatile bit_depth_t shcrs;
    const volatile bit_depth_t cfsr;
    const volatile bit_depth_t mmsr;
    const volatile bit_depth_t bfsr;
    const volatile bit_depth_t ufsr;
    volatile bit_depth_t hfsr;
    const volatile bit_depth_t mmar;
    const volatile bit_depth_t bfar;
} scb_t;
#pragma pack(push)

#define SCB ((volatile scb_t*) 0xE000ED00)

enum SCB_CPUID {
    SCB_CPUID_REVISION    = 15,
    SCB_CPUID_PARTNO      = 4095 << 4,
    SCB_CPUID_CONSTANT    = 15   << 16,
    SCB_CPUID_VARIANT     = 15   << 20,
    SCB_CPUID_IMPLEMENTER = 255  << 24,
};

enum SCB_ICSR {
    SCB_ICSR_VECTACTIVE         = 511,
    SCB_ICSR_RETTOBASE          = 1   << 11,
    SCB_ICSR_VECTPENDING        = 1023 << 12,
    SCB_ICSR_ISRPENDING         = 1 << 22,
    SCB_ICSR_RESERVED_FOR_DEBUG = 1 << 23,
    SCB_ICSR_PENDSTCLR          = 1 << 25,
    SCB_ICSR_PENDSTSET          = 1 << 26,
    SCB_ICSR_PENDSVCLR          = 1 << 27,
    SCB_ICSR_PENDSVSET          = 1 << 28,
};

enum SCB_VTOR {
    SCB_VTOR_RESERVED = 127,
    SCB_VTOR_TBLOFF   = 8388607 << 6,
};

enum SCB_AIRCR {
    SCB_AIRCR_VECTREST                             = 1,
    SCB_AIRCR_VECTCLRACTIVE                        = 1     << 1,
    SCB_AIRCR_SYSRESETREQ                          = 1     << 2,
    SCB_AIRCR_PRIGROUP                             = 7     << 8,
    SCB_AIRCR_ENDIANESS                            = 1     << 15,
    SCB_AIRCR_ON_READ_VECTKEYSTAT_ON_WRITE_VECTKEY = 65535 << 16,
};

enum SCB_SCR {
    SCB_SCR_SLEEONEXIT = 1 << 1,
    SCB_SCR_SLEEPDEEP  = 1 << 2,
    SCB_SCR_SEVONPEND  = 1 << 3,
};

enum SCB_CCR {
    SCB_CCR_NONBASETHRDENA = 1,
    SCB_CCR_USERSETMPEND   = 1 << 1,
    SCB_CCR_UNALIGN_TRP    = 1 << 3,
    SCB_CCR_DIV_O_TRP      = 1 << 4,
    SCB_CCR_BFHFNMIGN      = 1 << 8,
    SCB_CCR_STKALIGN       = 1 << 9,
};

enum SCB_SHP_1 {
    SCB_SHP_1_PRI_4 = 255,
    SCB_SHP_1_PRI_5 = 255 << 8,
    SCB_SHP_1_PRI_6 = 255 << 16,
    SCB_SHP_1_PRI_7 = 255 << 24,
};

enum SCB_SHP_2 {
    SCB_SHP_2_PRI_11 = 255 << 24,
};

enum SCB_SHP_3 {
    SCB_SHP_3_PRI_14 = 255 << 16,
    SCB_SHP_3_PRI_15 = 255 << 24,
};

enum SCB_SHCSR {
    SCB_SHCSR_MEMFAULTACT    = 1,
    SCB_SHCSR_BUSFAULTACT    = 1 << 1,
    SCB_SHCSR_USGFAULTACT    = 1 << 3,
    SCB_SHCSR_CVCALLAVCT     = 1 << 7,
    SCB_SHCSR_MONITORACT     = 1 << 8,
    SCB_SHCSR_PEND_SVACT     = 1 << 10,
    SCB_SHCSR_SYSTICKACT     = 1 << 11,
    SCB_SHCSR_USGFAULTPENDED = 1 << 12,
    SCB_SHCSR_MEMFAULTPENDED = 1 << 13,
    SCB_SHCSR_BUSFAULTPENDED = 1 << 14,
    SCB_SHCSR_SVCALLPENDED   = 1 << 15,
    SCB_SHCSR_MEMFAULTENA    = 1 << 16,
    SCB_SHCSR_BUSFAULTENA    = 1 << 17,
    SCB_SHCSR_USGFAULTENA    = 1 << 18,
};

enum SCB_CFSR {
    SCB_CFSR_MMFSR            = 255,
    SCB_CFSR_MMFSR_IACCVIOL   = 1,
    SCB_CFSR_MMFSR_DACCVIOL   = 1     << 1,
    SCB_CFSR_MMFSR_MUNSTKERR  = 1     << 3,
    SCB_CFSR_MMFSR_MSTKERR    = 1     << 4,
    SCB_CFSR_MMFSR_MMARVALID  = 1     << 7,
    SCB_CFSR_BFSR             = 255   << 8,
    SCB_CFSR_BFSR_IBU_SERR    = 1     << 8,
    SCB_CFSR_BFSR_PRECISERR   = 1     << 9,
    SCB_CFSR_BFSR_IMPRECISSER = 1     << 10,
    SCB_CFSR_BFSR_UNSTKERR    = 1     << 11,
    SCB_CFSR_BFSR_STKERR      = 1     << 12,
    SCB_CFSR_BFSR_BFRVALID    = 1     << 15,
    SCB_CFSR_UFSR             = 65535 << 16,
    SCB_CFSR_UFSR_UNDEFINSTR  = 1     << 16,
    SCB_CFSR_UFSR_INVSTATE    = 1     << 17,
    SCB_CFSR_UFSR_INVPC       = 1     << 18,
    SCB_CFSR_UFSR_NOCP        = 1     << 19,
    SCB_CFSR_UFSR_UNALIGNED   = 1     << 24,
    SCB_CFSR_UFSR_DIVBYZERO   = 1     << 25,
};

enum SCB_HFSR {
    SCB_HFSR_RESERVED = 1,
    SCB_HFSR_VECTTBL  = 1 << 1,
    SCB_HFSR_FORCED   = 1 << 30,
    SCB_HFSR_DEBUGEVT = 1 << 31,
};

/*
    MDR_IWDG2
*/

typedef struct {
    volatile bit_depth_t kr;
    volatile bit_depth_t pr;
    volatile bit_depth_t rlr;
    const volatile bit_depth_t sr;
} mdr_iwdg_t;

#define MDR_IWDG ((volatile mdr_iwdg_t*) 0x40068000)

enum MDR_IWDG_KR {
    MDR_IWDG_KR_KEY = 65535,
};

enum MDR_IWDG_PR {
    MDR_IWDG_PR_PR = 7,
};

enum MDR_IWDG_RLR {
    MDR_IWDG_RLR_RLR = 4095,
};

enum MDR_IWDG_SR {
    MDR_IWDG_SR_PVU = 1,
    MDR_IWDG_SR_RVU = 1 << 1,
};

/*
    MDR_WWDG
*/

typedef struct {
    volatile bit_depth_t cr;
    volatile bit_depth_t cfr;
    volatile bit_depth_t sr;
} mdr_wwdg_t;

#define MDR_WWDG ((volatile mdr_wwdg_t*) 0x40060000)

enum MDR_WWDG_CR {
    MDR_WWDG_CR_T    = 127,
    MDR_WWDG_CR_T_0  = 1,
    MDR_WWDG_CR_T_1  = 1   << 1,
    MDR_WWDG_CR_T_2  = 1   << 2,
    MDR_WWDG_CR_T_3  = 1   << 3,
    MDR_WWDG_CR_T_4  = 1   << 4,
    MDR_WWDG_CR_T_5  = 1   << 5,
    MDR_WWDG_CR_T_6  = 1   << 6,
    MDR_WWDG_CR_WDGA = 1   << 7,
};

enum MDR_WWDG_CFR {
    MDR_WWDG_CFR_W      = 127,
    MDR_WWDG_CFR_W_0    = 1,
    MDR_WWDG_CFR_W_1    = 1   << 1,
    MDR_WWDG_CFR_W_2    = 1   << 2,
    MDR_WWDG_CFR_W_3    = 1   << 3,
    MDR_WWDG_CFR_W_4    = 1   << 4,
    MDR_WWDG_CFR_W_5    = 1   << 5,
    MDR_WWDG_CFR_W_6    = 1   << 6,
    MDR_WWDG_CFR_WGTB   = 3   << 7,
    MDR_WWDG_CFR_WGTB_1 = 1   << 7,
    MDR_WWDG_CFR_WGTB_2 = 1   << 8,
    MDR_WWDG_CFR_EWI    = 1   << 9,
};

enum MDR_WWDG_SR {
    MDR_WWDG_SR_EWIF = 1,
};