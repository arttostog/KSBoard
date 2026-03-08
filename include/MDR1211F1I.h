#pragma once

#include <system/ksb_types.h>

/*
    Производственная информация
*/

#define UNIQ_ID_1 (*((const volatile size_t*) 0x08000FF0))
#define UNIQ_ID_2 (*((const volatile size_t*) 0x08000FE0))
#define UNIQ_ID_3 (*((const volatile size_t*) 0x08000FD0))
#define UNIQ_ID_4 (*((const volatile size_t*) 0x08000FC0))
#define UNIQ_ID_5 (*((const volatile size_t*) 0x08000FB0))

#define LDO_TRIM (*((const volatile size_t*) 0x08000FA0) & 7)
#define HSI_TRIM (*((const volatile size_t*) 0x08000F90) & 63)
#define LSI_TRIM (*((const volatile size_t*) 0x08000F80) & 31)

/*
    MDR_EEPROM
*/

typedef struct {
    volatile size_t cmd;
    volatile size_t adr;
    volatile size_t di;
    volatile size_t data; // Обозначение в спецификации - "do"
    volatile size_t key;
} mdr_eeprom_t;

#define MDR_EEPROM ((volatile mdr_eeprom_t*) 0x40018000)

/*
    SysTick
*/

typedef struct {
    volatile size_t ctrl;
    volatile size_t load;
    volatile size_t val;
    const volatile size_t calib;
} sys_tick_t;

#define SYS_TICK ((volatile sys_tick_t*) 0xE000E010)

/*
    MPU
*/

typedef struct {
    const volatile size_t type;
    volatile size_t ctrl;
    volatile size_t rnr;
    volatile size_t rbar;
    volatile size_t rasr;
    volatile size_t rbar_a1;
    volatile size_t rasr_a1;
    volatile size_t rbar_a2;
    volatile size_t rasr_a2;
    volatile size_t rbar_a3;
    volatile size_t rasr_a3;
} mpu_t;

#define MPU ((volatile mpu_t*) 0xE000ED90)

/*
    MDR_RST_CLK
*/

typedef struct {
    const volatile size_t clock_status;
    volatile size_t pll_control;
    volatile size_t hs_control;
    volatile size_t cpu_clock;
    volatile size_t usb_clock;
    volatile size_t adc_mco_clock;
    volatile size_t rtc_clock;
    volatile size_t per_clock;
    volatile size_t can_clock;
    volatile size_t tim_clock;
    volatile size_t uart_clock;
    volatile size_t ssp_clock;
} mdr_rst_clk_t;

#define MDR_RST_CLK ((volatile mdr_rst_clk_t*) 0x40020000)

#define HSI_FREQUENCY 8000000
#define LSI_FREQUENCY 40000
#define LSE_FREQUENCY 32000

/*
    MDR_BKP
*/

typedef struct {
    volatile size_t reg_00;
    volatile size_t reg_01;
    volatile size_t reg_02;
    volatile size_t reg_03;
    volatile size_t reg_04;
    volatile size_t reg_05;
    volatile size_t reg_06;
    volatile size_t reg_07;
    volatile size_t reg_08;
    volatile size_t reg_09;
    volatile size_t reg_0a;
    volatile size_t reg_0b;
    volatile size_t reg_0c;
    volatile size_t reg_0d;
    volatile size_t reg_0e;
    volatile size_t reg_0f;
    volatile size_t rtc_cnt;
    volatile size_t rtc_div;
    volatile size_t rtc_prl;
    volatile size_t rtc_alrm;
    volatile size_t rtc_cs;
} mdr_bkp_t;

#define MDR_BKP ((volatile mdr_bkp_t*) 0x400D8000)

/*
    MDR_MDR_PORT
*/

typedef struct {
    volatile size_t rxtx;
    volatile size_t oe;
    volatile size_t func;
    volatile size_t analog;
    volatile size_t pull;
    volatile size_t pd;
    volatile size_t pwr;
    volatile size_t gfen;
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
    volatile size_t pvdcs;
} mdr_power_t;

#define MDR_POWER ((volatile mdr_power_t*) 0x40058000)

/*
    MDR_EBC
*/

#pragma pack(push, 1)
typedef struct {
    const char _padding_0[50];
    volatile size_t nand_cycles;
    volatile size_t control;
    volatile size_t reg_0_cntrl;
    volatile size_t reg_1_cntrl;
    volatile size_t reg_2_cntrl;
    volatile size_t reg_3_cntrl;
} mdr_ebc_t;
#pragma pack(pop)

#define MDR_EBC ((volatile mdr_ebc_t*) 0x400F0000)

/*
    MDR_USB
*/

#pragma pack(push, 1)
typedef struct {
    volatile size_t htxc;
    volatile size_t htxt;
    volatile size_t htxlc;
    volatile size_t htxse;
    volatile size_t htxa;
    volatile size_t htxe;
    volatile size_t hfn_l;
    volatile size_t hfn_h;
    volatile size_t hsi;
    volatile size_t him;
    volatile size_t hrxs;
    volatile size_t hrxp;
    volatile size_t hrxa;
    volatile size_t hrxe;
    volatile size_t hrxcs;
    volatile size_t hstm;
    const char _padding_0[0x44];
    volatile size_t hrxfd;
    const char _padding_1[0x4];
    volatile size_t hrxfdc;
    const char _padding_2[0x4];
    volatile size_t hrxfc;
    const char _padding_3[0x30];
    volatile size_t htxfd;
    const char _padding_4[0x10];
    volatile size_t htxfc;
    const char _padding_5[0x30];
    volatile size_t sep_ctrl_0;
    volatile size_t sep_sts_0;
    volatile size_t sep_ts_0;
    volatile size_t sep_nts_0;
    volatile size_t sep_ctrl_1;
    volatile size_t sep_sts_1;
    volatile size_t sep_ts_1;
    volatile size_t sep_nts_1;
    volatile size_t sep_ctrl_2;
    volatile size_t sep_sts_2;
    volatile size_t sep_ts_2;
    volatile size_t sep_nts_2;
    volatile size_t sep_ctrl_3;
    volatile size_t sep_sts_3;
    volatile size_t sep_ts_3;
    volatile size_t sep_nts_3;
    volatile size_t sc;
    volatile size_t sls;
    volatile size_t sis;
    volatile size_t sim;
    volatile size_t sa;
    volatile size_t sfn_l;
    volatile size_t sfn_h;
    const char _padding_6[0x28];
    volatile size_t sep_rxfd_0;
    const char _padding_7[0x4];
    volatile size_t sep_rxfdc_0;
    const char _padding_8[0x4];
    volatile size_t sep_rxfc_0;
    const char _padding_9[0x30];
    volatile size_t sep_txfd_0;
    const char _padding_10[0x10];
    volatile size_t sep_txfdc_0;
    const char _padding_11[0x30];
    volatile size_t sep_rxfd_1;
    const char _padding_12[0x4];
    volatile size_t sep_rxfdc_1;
    const char _padding_13[0x4];
    volatile size_t sep_rxfc_1;
    const char _padding_14[0x30];
    volatile size_t sep_txfd_1;
    const char _padding_15[0x10];
    volatile size_t sep_txfdc_1;
    const char _padding_16[0x30];
    volatile size_t sep_rxfd_2;
    const char _padding_17[0x4];
    volatile size_t sep_rxfdc_2;
    const char _padding_18[0x4];
    volatile size_t sep_rxfc_2;
    const char _padding_19[0x30];
    volatile size_t sep_txfd_2;
    const char _padding_20[0x10];
    volatile size_t sep_txfdc_2;
    const char _padding_21[0x30];
    volatile size_t sep_rxfd_3;
    const char _padding_22[0x4];
    volatile size_t sep_rxfdc_3;
    const char _padding_23[0x4];
    volatile size_t sep_rxfc_3;
    const char _padding_24[0x30];
    volatile size_t sep_txfd_3;
    const char _padding_25[0x10];
    volatile size_t sep_txfdc_3;
    const char _padding_26[0x30];
    volatile size_t hscr;
    volatile size_t hsvr;
} mdr_usb_t;
#pragma pack(pop)

#define MDR_USB ((volatile mdr_usb_t*) 0x40010000)

/*
    MDR_CAN
*/

typedef struct {
    volatile size_t id;
    volatile size_t dlc;
    volatile size_t datal;
    volatile size_t datah;
} can_buf_t;

typedef struct {
    volatile size_t mask;
    volatile size_t filter;
} can_buf_filter_t;

#pragma pack(push, 1)
typedef struct {
    volatile size_t control;
    volatile size_t status;
    volatile size_t bittmng;
    volatile size_t int_en;
    const char _padding_0[0x8];
    volatile size_t over;
    const char _padding_1[0x4];
    volatile size_t rxid;
    volatile size_t rxdlc;
    volatile size_t rxdatal;
    volatile size_t rxdatah;
    volatile size_t txid;
    volatile size_t txdlc;
    volatile size_t datal;
    volatile size_t datah;
    volatile size_t buf_con[0x20];
    volatile size_t int_rx;
    volatile size_t rx;
    volatile size_t int_tx;
    volatile size_t tx;
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
    volatile size_t cnt;
    volatile size_t psg;
    volatile size_t arr;
    volatile size_t cntrl;
    volatile size_t ccr1;
    volatile size_t ccr2;
    volatile size_t ccr3;
    volatile size_t ccr4;
    volatile size_t ch1_cntrl;
    volatile size_t ch2_cntrl;
    volatile size_t ch3_cntrl;
    volatile size_t ch4_cntrl;
    volatile size_t ch1_cntrl1;
    volatile size_t ch2_cntrl1;
    volatile size_t ch3_cntrl1;
    volatile size_t ch4_cntrl1;
    volatile size_t ch1_dtg;
    volatile size_t ch2_dtg;
    volatile size_t ch3_dtg;
    volatile size_t ch4_dtg;
    volatile size_t brketr_cntrl;
    volatile size_t status;
    volatile size_t ie;
    volatile size_t dma_re;
    volatile size_t ch1_cntrl2;
    volatile size_t ch2_cntrl2;
    volatile size_t ch3_cntrl2;
    volatile size_t ch4_cntrl2;
    volatile size_t ccr11;
    volatile size_t ccr21;
    volatile size_t ccr31;
    volatile size_t ccr41;
} mdr_timer_t;
#pragma pack(pop)

#define MDR_TIMER1 ((volatile mdr_timer_t*) 0x40070000)
#define MDR_TIMER2 ((volatile mdr_timer_t*) 0x40078000)
#define MDR_TIMER3 ((volatile mdr_timer_t*) 0x40080000)

/*
    MDR_ADC
*/

typedef struct {
    volatile size_t adc1_cfg;
    volatile size_t adc2_cfg;
    volatile size_t adc1_h_level;
    volatile size_t adc2_h_level;
    volatile size_t adc1_l_level;
    volatile size_t adc2_l_level;
    const volatile size_t adc1_result;
    const volatile size_t adc2_result;
    volatile size_t adc1_status;
    volatile size_t adc2_status;
    volatile size_t adc1_chsel;
    volatile size_t adc2_chsel;
} mdr_adc_t;

#define MDR_ADC ((volatile mdr_adc_t*) 0x40088000)

/*
    MDR_DAC
*/

typedef struct {
    volatile size_t cfg;
    volatile size_t dac1_data;
    volatile size_t dac2_data;
} mdr_dac_t;

#define MDR_DAC ((volatile mdr_dac_t*) 0x40090000)

/*
    MDR_COMP
*/

typedef struct {
    volatile size_t cfg;
    volatile size_t result;
    volatile size_t result_latch;
} mdr_comp_t;

#define MDR_COMP ((volatile mdr_comp_t*) 0x40098000)

/*
    MDR_I2C
*/

typedef struct {
    volatile size_t prl;
    volatile size_t prh;
    volatile size_t ctr;
    const volatile size_t rxd;
    const volatile size_t sta;
    volatile size_t txd;
    volatile size_t cmd;
} mdr_i2c_t;

#define MDR_I2C ((volatile mdr_i2c_t*) 0x40050000)

/*
    MDR_SSP
*/

typedef struct {
    volatile size_t cr0;
    volatile size_t cr1;
    volatile size_t dr;
    const volatile size_t sr;
    volatile size_t cpsr;
    volatile size_t imsc;
    const volatile size_t ris;
    const volatile size_t mis;
    volatile size_t icr;
    volatile size_t dmacr;
} mdr_ssp_t;

#define MDR_SSP1 ((volatile mdr_ssp_t*) 0x40040000)
#define MDR_SSP2 ((volatile mdr_ssp_t*) 0x400A0000)

/*
    MDR_UART
*/

#pragma pack(push, 1)
typedef struct {
    volatile size_t dr;
    volatile size_t rsr_ecr;
    const char _padding_0[0x10];
    const volatile size_t fr;
    const char _padding_1[0x4];
    volatile size_t ilpr;
    volatile size_t ibrd;
    volatile size_t fbrd;
    volatile size_t lcr_h;
    volatile size_t cr;
    volatile size_t ifls;
    volatile size_t imsc;
    const volatile size_t ris;
    const volatile size_t mis;
    volatile size_t icr;
    volatile size_t dmacr;
} mdr_uart_t;
#pragma pack(pop)

#define MDR_UART1 ((volatile mdr_uart_t*) 0x40030000)
#define MDR_UART2 ((volatile mdr_uart_t*) 0x40038000)

/*
    MDR_DMA
*/

#pragma pack(push, 1)
typedef struct {
    const volatile size_t status;
    volatile size_t cfg;
    volatile size_t ctrl_base_ptr;
    const volatile size_t alt_ctrl_base_ptr;
    const volatile size_t waitonreq_status;
    volatile size_t chnl_sw_request;
    volatile size_t chnl_useburst_set;
    volatile size_t chnl_useburst_clr;
    volatile size_t chnl_req_mask_set;
    volatile size_t chnl_req_mask_clr;
    volatile size_t chnl_enable_set;
    volatile size_t chnl_enable_clr;
    volatile size_t chnl_pri_alt_set;
    volatile size_t chnl_pri_alt_clr;
    volatile size_t chnl_priority_set;
    volatile size_t chnl_priority_clr;
    const char _padding_0[0xC];
    volatile size_t err_clr;
} mdr_dma_t;
#pragma pack(pop)

#define MDR_DMA ((volatile mdr_dma_t*) 0x40028000)

/*
    NVIC
*/

#pragma pack(push, 1)
typedef struct {
    volatile size_t iser_0;
    volatile size_t iser_1;
    volatile size_t iser_2;
    volatile size_t iser_3;
    volatile size_t iser_4;
    volatile size_t iser_5;
    volatile size_t iser_6;
    volatile size_t iser_7;
    const char _padding_0[0x60];
    volatile size_t icer_0;
    volatile size_t icer_1;
    volatile size_t icer_2;
    volatile size_t icer_3;
    volatile size_t icer_4;
    volatile size_t icer_5;
    volatile size_t icer_6;
    volatile size_t icer_7;
    volatile size_t ispr_0;
    volatile size_t ispr_1;
    volatile size_t ispr_2;
    volatile size_t ispr_3;
    volatile size_t ispr_4;
    volatile size_t ispr_5;
    volatile size_t ispr_6;
    volatile size_t ispr_7;
    const char _padding_1[0x60];
    volatile size_t icpr_0;
    volatile size_t icpr_1;
    volatile size_t icpr_2;
    volatile size_t icpr_3;
    volatile size_t icpr_4;
    volatile size_t icpr_5;
    volatile size_t icpr_6;
    volatile size_t icpr_7;
    const volatile size_t iabr_0;
    const volatile size_t iabr_1;
    const volatile size_t iabr_2;
    const volatile size_t iabr_3;
    const volatile size_t iabr_4;
    const volatile size_t iabr_5;
    const volatile size_t iabr_6;
    const volatile size_t iabr_7;
    const char _padding_2[0xE0];
    volatile size_t ipr_0;
    volatile size_t ipr_1;
    volatile size_t ipr_2;
    volatile size_t ipr_3;
    volatile size_t ipr_4;
    volatile size_t ipr_5;
    volatile size_t ipr_6;
    volatile size_t ipr_7;
    const char _padding_3[0xAE0];
    volatile size_t stir;
} nvic_t;
#pragma pack(pop)

#define NVIC ((volatile nvic_t*) 0xE000E100)

/*
    SCB
*/

#pragma pack(push, 1)
typedef struct {
    const char _padding_0[0x8];
    volatile size_t actlr;
} interrupt_t;
#pragma pack(push)

#define INTERRUPT_TYPE ((volatile size_terrupt_t*) 0xE000E000)

#pragma pack(push, 1)
typedef struct {
    const volatile size_t cpuid;
    volatile size_t icsr;
    volatile size_t vtor;
    volatile size_t aircr;
    volatile size_t scr;
    volatile size_t ccr;
    volatile size_t shpr1;
    volatile size_t shpr2;
    volatile size_t shpr3;
    volatile size_t shcrs;
    const volatile size_t cfsr;
    const volatile size_t mmsr;
    const volatile size_t bfsr;
    const volatile size_t ufsr;
    volatile size_t hfsr;
    const volatile size_t mmar;
    const volatile size_t bfar;
} scb_t;
#pragma pack(push)

#define SCB ((volatile scb_t*) 0xE000ED00)

/*
    MDR_IWDG2
*/

typedef struct {
    volatile size_t kr;
    volatile size_t pr;
    volatile size_t rlr;
    const volatile size_t sr;
} mdr_iwdg_t;

#define MDR_IWDG ((volatile mdr_iwdg_t*) 0x40068000)

/*
    MDR_WWDG
*/

typedef struct {
    volatile size_t cr;
    volatile size_t cfr;
    volatile size_t sr;
} mdr_wwdg_t;

#define MDR_WWDG ((volatile mdr_wwdg_t*) 0x40060000)