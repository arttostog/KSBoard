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

/*
    MDR_POWER
*/

typedef struct {
    volatile bit_depth_t pvdcs;
} mdr_power_t;

#define MDR_POWER ((volatile mdr_power_t*) 0x40058000)

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

/*
    MDR_DAC
*/

typedef struct {
    volatile bit_depth_t cfg;
    volatile bit_depth_t dac1_data;
    volatile bit_depth_t dac2_data;
} mdr_dac_t;

#define MDR_DAC ((volatile mdr_dac_t*) 0x40090000)

/*
    MDR_COMP
*/

typedef struct {
    volatile bit_depth_t cfg;
    volatile bit_depth_t result;
    volatile bit_depth_t result_latch;
} mdr_comp_t;

#define MDR_COMP ((volatile mdr_comp_t*) 0x40098000)

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

/*
    MDR_WWDG
*/

typedef struct {
    volatile bit_depth_t cr;
    volatile bit_depth_t cfr;
    volatile bit_depth_t sr;
} mdr_wwdg_t;

#define MDR_WWDG ((volatile mdr_wwdg_t*) 0x40060000)