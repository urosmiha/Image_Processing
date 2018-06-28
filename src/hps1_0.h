#ifndef _ALTERA_HPS_0_H_
#define _ALTERA_HPS_0_H_

/*
 * This file was automatically generated by the swinfo2header utility.
 * 
 * Created from SOPC Builder system 'soc_system' in
 * file './soc_system.sopcinfo'.
 */

/*
 * This file contains macros for module 'hps_0' and devices
 * connected to the following masters:
 *   h2f_axi_master
 *   h2f_lw_axi_master
 * 
 * Do not include this header file and another header file created for a
 * different module or master group at the same time.
 * Doing so may result in duplicate macro names.
 * Instead, use the system header file which has macros with unique names.
 */

/*
 * Macros for device 'trivium_setup_1', class 'altera_avalon_pio'
 * The macros are prefixed with 'TRIVIUM_SETUP_1_'.
 * The prefix is the slave descriptor.
 */
#define TRIVIUM_SETUP_1_COMPONENT_TYPE altera_avalon_pio
#define TRIVIUM_SETUP_1_COMPONENT_NAME trivium_setup_1
#define TRIVIUM_SETUP_1_BASE 0x0
#define TRIVIUM_SETUP_1_SPAN 16
#define TRIVIUM_SETUP_1_END 0xf
#define TRIVIUM_SETUP_1_BIT_CLEARING_EDGE_REGISTER 0
#define TRIVIUM_SETUP_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TRIVIUM_SETUP_1_CAPTURE 0
#define TRIVIUM_SETUP_1_DATA_WIDTH 32
#define TRIVIUM_SETUP_1_DO_TEST_BENCH_WIRING 0
#define TRIVIUM_SETUP_1_DRIVEN_SIM_VALUE 0
#define TRIVIUM_SETUP_1_EDGE_TYPE NONE
#define TRIVIUM_SETUP_1_FREQ 50000000
#define TRIVIUM_SETUP_1_HAS_IN 0
#define TRIVIUM_SETUP_1_HAS_OUT 1
#define TRIVIUM_SETUP_1_HAS_TRI 0
#define TRIVIUM_SETUP_1_IRQ_TYPE NONE
#define TRIVIUM_SETUP_1_RESET_VALUE 0

/*
 * Macros for device 'trivium_setup_2', class 'altera_avalon_pio'
 * The macros are prefixed with 'TRIVIUM_SETUP_2_'.
 * The prefix is the slave descriptor.
 */
#define TRIVIUM_SETUP_2_COMPONENT_TYPE altera_avalon_pio
#define TRIVIUM_SETUP_2_COMPONENT_NAME trivium_setup_2
#define TRIVIUM_SETUP_2_BASE 0x20
#define TRIVIUM_SETUP_2_SPAN 16
#define TRIVIUM_SETUP_2_END 0x2f
#define TRIVIUM_SETUP_2_BIT_CLEARING_EDGE_REGISTER 0
#define TRIVIUM_SETUP_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TRIVIUM_SETUP_2_CAPTURE 0
#define TRIVIUM_SETUP_2_DATA_WIDTH 32
#define TRIVIUM_SETUP_2_DO_TEST_BENCH_WIRING 0
#define TRIVIUM_SETUP_2_DRIVEN_SIM_VALUE 0
#define TRIVIUM_SETUP_2_EDGE_TYPE NONE
#define TRIVIUM_SETUP_2_FREQ 50000000
#define TRIVIUM_SETUP_2_HAS_IN 0
#define TRIVIUM_SETUP_2_HAS_OUT 1
#define TRIVIUM_SETUP_2_HAS_TRI 0
#define TRIVIUM_SETUP_2_IRQ_TYPE NONE
#define TRIVIUM_SETUP_2_RESET_VALUE 0

/*
 * Macros for device 'trivium_setup_3', class 'altera_avalon_pio'
 * The macros are prefixed with 'TRIVIUM_SETUP_3_'.
 * The prefix is the slave descriptor.
 */
#define TRIVIUM_SETUP_3_COMPONENT_TYPE altera_avalon_pio
#define TRIVIUM_SETUP_3_COMPONENT_NAME trivium_setup_3
#define TRIVIUM_SETUP_3_BASE 0x40
#define TRIVIUM_SETUP_3_SPAN 16
#define TRIVIUM_SETUP_3_END 0x4f
#define TRIVIUM_SETUP_3_BIT_CLEARING_EDGE_REGISTER 0
#define TRIVIUM_SETUP_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TRIVIUM_SETUP_3_CAPTURE 0
#define TRIVIUM_SETUP_3_DATA_WIDTH 32
#define TRIVIUM_SETUP_3_DO_TEST_BENCH_WIRING 0
#define TRIVIUM_SETUP_3_DRIVEN_SIM_VALUE 0
#define TRIVIUM_SETUP_3_EDGE_TYPE NONE
#define TRIVIUM_SETUP_3_FREQ 50000000
#define TRIVIUM_SETUP_3_HAS_IN 0
#define TRIVIUM_SETUP_3_HAS_OUT 1
#define TRIVIUM_SETUP_3_HAS_TRI 0
#define TRIVIUM_SETUP_3_IRQ_TYPE NONE
#define TRIVIUM_SETUP_3_RESET_VALUE 0

/*
 * Macros for device 'setup_received', class 'altera_avalon_pio'
 * The macros are prefixed with 'SETUP_RECEIVED_'.
 * The prefix is the slave descriptor.
 */
#define SETUP_RECEIVED_COMPONENT_TYPE altera_avalon_pio
#define SETUP_RECEIVED_COMPONENT_NAME setup_received
#define SETUP_RECEIVED_BASE 0x60
#define SETUP_RECEIVED_SPAN 16
#define SETUP_RECEIVED_END 0x6f
#define SETUP_RECEIVED_BIT_CLEARING_EDGE_REGISTER 0
#define SETUP_RECEIVED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SETUP_RECEIVED_CAPTURE 0
#define SETUP_RECEIVED_DATA_WIDTH 2
#define SETUP_RECEIVED_DO_TEST_BENCH_WIRING 0
#define SETUP_RECEIVED_DRIVEN_SIM_VALUE 0
#define SETUP_RECEIVED_EDGE_TYPE NONE
#define SETUP_RECEIVED_FREQ 50000000
#define SETUP_RECEIVED_HAS_IN 1
#define SETUP_RECEIVED_HAS_OUT 0
#define SETUP_RECEIVED_HAS_TRI 0
#define SETUP_RECEIVED_IRQ_TYPE NONE
#define SETUP_RECEIVED_RESET_VALUE 0

/*
 * Macros for device 'setup_sent', class 'altera_avalon_pio'
 * The macros are prefixed with 'SETUP_SENT_'.
 * The prefix is the slave descriptor.
 */
#define SETUP_SENT_COMPONENT_TYPE altera_avalon_pio
#define SETUP_SENT_COMPONENT_NAME setup_sent
#define SETUP_SENT_BASE 0x80
#define SETUP_SENT_SPAN 16
#define SETUP_SENT_END 0x8f
#define SETUP_SENT_BIT_CLEARING_EDGE_REGISTER 0
#define SETUP_SENT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SETUP_SENT_CAPTURE 0
#define SETUP_SENT_DATA_WIDTH 2
#define SETUP_SENT_DO_TEST_BENCH_WIRING 0
#define SETUP_SENT_DRIVEN_SIM_VALUE 0
#define SETUP_SENT_EDGE_TYPE NONE
#define SETUP_SENT_FREQ 50000000
#define SETUP_SENT_HAS_IN 0
#define SETUP_SENT_HAS_OUT 1
#define SETUP_SENT_HAS_TRI 0
#define SETUP_SENT_IRQ_TYPE NONE
#define SETUP_SENT_RESET_VALUE 0

/*
 * Macros for device 'keystream_1', class 'altera_avalon_pio'
 * The macros are prefixed with 'KEYSTREAM_1_'.
 * The prefix is the slave descriptor.
 */
#define KEYSTREAM_1_COMPONENT_TYPE altera_avalon_pio
#define KEYSTREAM_1_COMPONENT_NAME keystream_1
#define KEYSTREAM_1_BASE 0xa0
#define KEYSTREAM_1_SPAN 16
#define KEYSTREAM_1_END 0xaf
#define KEYSTREAM_1_BIT_CLEARING_EDGE_REGISTER 0
#define KEYSTREAM_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEYSTREAM_1_CAPTURE 0
#define KEYSTREAM_1_DATA_WIDTH 32
#define KEYSTREAM_1_DO_TEST_BENCH_WIRING 0
#define KEYSTREAM_1_DRIVEN_SIM_VALUE 0
#define KEYSTREAM_1_EDGE_TYPE NONE
#define KEYSTREAM_1_FREQ 50000000
#define KEYSTREAM_1_HAS_IN 1
#define KEYSTREAM_1_HAS_OUT 0
#define KEYSTREAM_1_HAS_TRI 0
#define KEYSTREAM_1_IRQ_TYPE NONE
#define KEYSTREAM_1_RESET_VALUE 0

/*
 * Macros for device 'keystream_2', class 'altera_avalon_pio'
 * The macros are prefixed with 'KEYSTREAM_2_'.
 * The prefix is the slave descriptor.
 */
#define KEYSTREAM_2_COMPONENT_TYPE altera_avalon_pio
#define KEYSTREAM_2_COMPONENT_NAME keystream_2
#define KEYSTREAM_2_BASE 0xc0
#define KEYSTREAM_2_SPAN 16
#define KEYSTREAM_2_END 0xcf
#define KEYSTREAM_2_BIT_CLEARING_EDGE_REGISTER 0
#define KEYSTREAM_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEYSTREAM_2_CAPTURE 0
#define KEYSTREAM_2_DATA_WIDTH 32
#define KEYSTREAM_2_DO_TEST_BENCH_WIRING 0
#define KEYSTREAM_2_DRIVEN_SIM_VALUE 0
#define KEYSTREAM_2_EDGE_TYPE NONE
#define KEYSTREAM_2_FREQ 50000000
#define KEYSTREAM_2_HAS_IN 1
#define KEYSTREAM_2_HAS_OUT 0
#define KEYSTREAM_2_HAS_TRI 0
#define KEYSTREAM_2_IRQ_TYPE NONE
#define KEYSTREAM_2_RESET_VALUE 0

/*
 * Macros for device 'keystream_3', class 'altera_avalon_pio'
 * The macros are prefixed with 'KEYSTREAM_3_'.
 * The prefix is the slave descriptor.
 */
#define KEYSTREAM_3_COMPONENT_TYPE altera_avalon_pio
#define KEYSTREAM_3_COMPONENT_NAME keystream_3
#define KEYSTREAM_3_BASE 0xe0
#define KEYSTREAM_3_SPAN 16
#define KEYSTREAM_3_END 0xef
#define KEYSTREAM_3_BIT_CLEARING_EDGE_REGISTER 0
#define KEYSTREAM_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEYSTREAM_3_CAPTURE 0
#define KEYSTREAM_3_DATA_WIDTH 32
#define KEYSTREAM_3_DO_TEST_BENCH_WIRING 0
#define KEYSTREAM_3_DRIVEN_SIM_VALUE 0
#define KEYSTREAM_3_EDGE_TYPE NONE
#define KEYSTREAM_3_FREQ 50000000
#define KEYSTREAM_3_HAS_IN 1
#define KEYSTREAM_3_HAS_OUT 0
#define KEYSTREAM_3_HAS_TRI 0
#define KEYSTREAM_3_IRQ_TYPE NONE
#define KEYSTREAM_3_RESET_VALUE 0

/*
 * Macros for device 'state', class 'altera_avalon_pio'
 * The macros are prefixed with 'STATE_'.
 * The prefix is the slave descriptor.
 */
#define STATE_COMPONENT_TYPE altera_avalon_pio
#define STATE_COMPONENT_NAME state
#define STATE_BASE 0x100
#define STATE_SPAN 16
#define STATE_END 0x10f
#define STATE_BIT_CLEARING_EDGE_REGISTER 0
#define STATE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define STATE_CAPTURE 0
#define STATE_DATA_WIDTH 2
#define STATE_DO_TEST_BENCH_WIRING 0
#define STATE_DRIVEN_SIM_VALUE 0
#define STATE_EDGE_TYPE NONE
#define STATE_FREQ 50000000
#define STATE_HAS_IN 0
#define STATE_HAS_OUT 1
#define STATE_HAS_TRI 0
#define STATE_IRQ_TYPE NONE
#define STATE_RESET_VALUE 0

/*
 * Macros for device 'test', class 'altera_avalon_pio'
 * The macros are prefixed with 'TEST_'.
 * The prefix is the slave descriptor.
 */
#define TEST_COMPONENT_TYPE altera_avalon_pio
#define TEST_COMPONENT_NAME test
#define TEST_BASE 0x110
#define TEST_SPAN 16
#define TEST_END 0x11f
#define TEST_BIT_CLEARING_EDGE_REGISTER 0
#define TEST_BIT_MODIFYING_OUTPUT_REGISTER 0
#define TEST_CAPTURE 0
#define TEST_DATA_WIDTH 32
#define TEST_DO_TEST_BENCH_WIRING 0
#define TEST_DRIVEN_SIM_VALUE 0
#define TEST_EDGE_TYPE NONE
#define TEST_FREQ 50000000
#define TEST_HAS_IN 1
#define TEST_HAS_OUT 0
#define TEST_HAS_TRI 0
#define TEST_IRQ_TYPE NONE
#define TEST_RESET_VALUE 0

/*
 * Macros for device 'out1', class 'altera_avalon_pio'
 * The macros are prefixed with 'OUT1_'.
 * The prefix is the slave descriptor.
 */
#define OUT1_COMPONENT_TYPE altera_avalon_pio
#define OUT1_COMPONENT_NAME out1
#define OUT1_BASE 0x200
#define OUT1_SPAN 16
#define OUT1_END 0x20f
#define OUT1_BIT_CLEARING_EDGE_REGISTER 0
#define OUT1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT1_CAPTURE 0
#define OUT1_DATA_WIDTH 32
#define OUT1_DO_TEST_BENCH_WIRING 0
#define OUT1_DRIVEN_SIM_VALUE 0
#define OUT1_EDGE_TYPE NONE
#define OUT1_FREQ 50000000
#define OUT1_HAS_IN 1
#define OUT1_HAS_OUT 0
#define OUT1_HAS_TRI 0
#define OUT1_IRQ_TYPE NONE
#define OUT1_RESET_VALUE 0

/*
 * Macros for device 'out2', class 'altera_avalon_pio'
 * The macros are prefixed with 'OUT2_'.
 * The prefix is the slave descriptor.
 */
#define OUT2_COMPONENT_TYPE altera_avalon_pio
#define OUT2_COMPONENT_NAME out2
#define OUT2_BASE 0x300
#define OUT2_SPAN 16
#define OUT2_END 0x30f
#define OUT2_BIT_CLEARING_EDGE_REGISTER 0
#define OUT2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT2_CAPTURE 0
#define OUT2_DATA_WIDTH 32
#define OUT2_DO_TEST_BENCH_WIRING 0
#define OUT2_DRIVEN_SIM_VALUE 0
#define OUT2_EDGE_TYPE NONE
#define OUT2_FREQ 50000000
#define OUT2_HAS_IN 1
#define OUT2_HAS_OUT 0
#define OUT2_HAS_TRI 0
#define OUT2_IRQ_TYPE NONE
#define OUT2_RESET_VALUE 0

/*
 * Macros for device 'out3', class 'altera_avalon_pio'
 * The macros are prefixed with 'OUT3_'.
 * The prefix is the slave descriptor.
 */
#define OUT3_COMPONENT_TYPE altera_avalon_pio
#define OUT3_COMPONENT_NAME out3
#define OUT3_BASE 0x400
#define OUT3_SPAN 16
#define OUT3_END 0x40f
#define OUT3_BIT_CLEARING_EDGE_REGISTER 0
#define OUT3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OUT3_CAPTURE 0
#define OUT3_DATA_WIDTH 16
#define OUT3_DO_TEST_BENCH_WIRING 0
#define OUT3_DRIVEN_SIM_VALUE 0
#define OUT3_EDGE_TYPE NONE
#define OUT3_FREQ 50000000
#define OUT3_HAS_IN 1
#define OUT3_HAS_OUT 0
#define OUT3_HAS_TRI 0
#define OUT3_IRQ_TYPE NONE
#define OUT3_RESET_VALUE 0

/*
 * Macros for device 'sobelInputs1', class 'altera_avalon_pio'
 * The macros are prefixed with 'SOBELINPUTS1_'.
 * The prefix is the slave descriptor.
 */
#define SOBELINPUTS1_COMPONENT_TYPE altera_avalon_pio
#define SOBELINPUTS1_COMPONENT_NAME sobelInputs1
#define SOBELINPUTS1_BASE 0x420
#define SOBELINPUTS1_SPAN 16
#define SOBELINPUTS1_END 0x42f
#define SOBELINPUTS1_BIT_CLEARING_EDGE_REGISTER 0
#define SOBELINPUTS1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SOBELINPUTS1_CAPTURE 0
#define SOBELINPUTS1_DATA_WIDTH 32
#define SOBELINPUTS1_DO_TEST_BENCH_WIRING 0
#define SOBELINPUTS1_DRIVEN_SIM_VALUE 0
#define SOBELINPUTS1_EDGE_TYPE NONE
#define SOBELINPUTS1_FREQ 50000000
#define SOBELINPUTS1_HAS_IN 0
#define SOBELINPUTS1_HAS_OUT 1
#define SOBELINPUTS1_HAS_TRI 0
#define SOBELINPUTS1_IRQ_TYPE NONE
#define SOBELINPUTS1_RESET_VALUE 0

/*
 * Macros for device 'sobelInputs2', class 'altera_avalon_pio'
 * The macros are prefixed with 'SOBELINPUTS2_'.
 * The prefix is the slave descriptor.
 */
#define SOBELINPUTS2_COMPONENT_TYPE altera_avalon_pio
#define SOBELINPUTS2_COMPONENT_NAME sobelInputs2
#define SOBELINPUTS2_BASE 0x440
#define SOBELINPUTS2_SPAN 16
#define SOBELINPUTS2_END 0x44f
#define SOBELINPUTS2_BIT_CLEARING_EDGE_REGISTER 0
#define SOBELINPUTS2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SOBELINPUTS2_CAPTURE 0
#define SOBELINPUTS2_DATA_WIDTH 32
#define SOBELINPUTS2_DO_TEST_BENCH_WIRING 0
#define SOBELINPUTS2_DRIVEN_SIM_VALUE 0
#define SOBELINPUTS2_EDGE_TYPE NONE
#define SOBELINPUTS2_FREQ 50000000
#define SOBELINPUTS2_HAS_IN 0
#define SOBELINPUTS2_HAS_OUT 1
#define SOBELINPUTS2_HAS_TRI 0
#define SOBELINPUTS2_IRQ_TYPE NONE
#define SOBELINPUTS2_RESET_VALUE 0

/*
 * Macros for device 'sobelInputs3', class 'altera_avalon_pio'
 * The macros are prefixed with 'SOBELINPUTS3_'.
 * The prefix is the slave descriptor.
 */
#define SOBELINPUTS3_COMPONENT_TYPE altera_avalon_pio
#define SOBELINPUTS3_COMPONENT_NAME sobelInputs3
#define SOBELINPUTS3_BASE 0x460
#define SOBELINPUTS3_SPAN 16
#define SOBELINPUTS3_END 0x46f
#define SOBELINPUTS3_BIT_CLEARING_EDGE_REGISTER 0
#define SOBELINPUTS3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SOBELINPUTS3_CAPTURE 0
#define SOBELINPUTS3_DATA_WIDTH 32
#define SOBELINPUTS3_DO_TEST_BENCH_WIRING 0
#define SOBELINPUTS3_DRIVEN_SIM_VALUE 0
#define SOBELINPUTS3_EDGE_TYPE NONE
#define SOBELINPUTS3_FREQ 50000000
#define SOBELINPUTS3_HAS_IN 0
#define SOBELINPUTS3_HAS_OUT 1
#define SOBELINPUTS3_HAS_TRI 0
#define SOBELINPUTS3_IRQ_TYPE NONE
#define SOBELINPUTS3_RESET_VALUE 0

/*
 * Macros for device 'sobelControl', class 'altera_avalon_pio'
 * The macros are prefixed with 'SOBELCONTROL_'.
 * The prefix is the slave descriptor.
 */
#define SOBELCONTROL_COMPONENT_TYPE altera_avalon_pio
#define SOBELCONTROL_COMPONENT_NAME sobelControl
#define SOBELCONTROL_BASE 0x480
#define SOBELCONTROL_SPAN 16
#define SOBELCONTROL_END 0x48f
#define SOBELCONTROL_BIT_CLEARING_EDGE_REGISTER 0
#define SOBELCONTROL_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SOBELCONTROL_CAPTURE 0
#define SOBELCONTROL_DATA_WIDTH 8
#define SOBELCONTROL_DO_TEST_BENCH_WIRING 0
#define SOBELCONTROL_DRIVEN_SIM_VALUE 0
#define SOBELCONTROL_EDGE_TYPE NONE
#define SOBELCONTROL_FREQ 50000000
#define SOBELCONTROL_HAS_IN 1
#define SOBELCONTROL_HAS_OUT 1
#define SOBELCONTROL_HAS_TRI 0
#define SOBELCONTROL_IRQ_TYPE NONE
#define SOBELCONTROL_RESET_VALUE 0

/*
 * Macros for device 'sobelResult', class 'altera_avalon_pio'
 * The macros are prefixed with 'SOBELRESULT_'.
 * The prefix is the slave descriptor.
 */
#define SOBELRESULT_COMPONENT_TYPE altera_avalon_pio
#define SOBELRESULT_COMPONENT_NAME sobelResult
#define SOBELRESULT_BASE 0x4a0
#define SOBELRESULT_SPAN 16
#define SOBELRESULT_END 0x4af
#define SOBELRESULT_BIT_CLEARING_EDGE_REGISTER 0
#define SOBELRESULT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SOBELRESULT_CAPTURE 0
#define SOBELRESULT_DATA_WIDTH 8
#define SOBELRESULT_DO_TEST_BENCH_WIRING 0
#define SOBELRESULT_DRIVEN_SIM_VALUE 0
#define SOBELRESULT_EDGE_TYPE NONE
#define SOBELRESULT_FREQ 50000000
#define SOBELRESULT_HAS_IN 1
#define SOBELRESULT_HAS_OUT 0
#define SOBELRESULT_HAS_TRI 0
#define SOBELRESULT_IRQ_TYPE NONE
#define SOBELRESULT_RESET_VALUE 0

/*
 * Macros for device 'sysid_qsys', class 'altera_avalon_sysid_qsys'
 * The macros are prefixed with 'SYSID_QSYS_'.
 * The prefix is the slave descriptor.
 */
#define SYSID_QSYS_COMPONENT_TYPE altera_avalon_sysid_qsys
#define SYSID_QSYS_COMPONENT_NAME sysid_qsys
#define SYSID_QSYS_BASE 0x10000
#define SYSID_QSYS_SPAN 8
#define SYSID_QSYS_END 0x10007
#define SYSID_QSYS_ID 2899645186
#define SYSID_QSYS_TIMESTAMP 1525673074

/*
 * Macros for device 'jtag_uart', class 'altera_avalon_jtag_uart'
 * The macros are prefixed with 'JTAG_UART_'.
 * The prefix is the slave descriptor.
 */
#define JTAG_UART_COMPONENT_TYPE altera_avalon_jtag_uart
#define JTAG_UART_COMPONENT_NAME jtag_uart
#define JTAG_UART_BASE 0x20000
#define JTAG_UART_SPAN 8
#define JTAG_UART_END 0x20007
#define JTAG_UART_IRQ 2
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8

#define SDRAM_COMPONENT_TYPE altera_avalon_new_sdram_controller
#define SDRAM_COMPONENT_NAME SDRAM
#define SDRAM_BASE 0x0
#define SDRAM_SPAN 67108864
#define SDRAM_END 0x3ffffff
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 7.8125
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 25
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_T_AC 5.4
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 15.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 15.0
#define SDRAM_T_WR 14.0
#define SDRAM_MEMORY_INFO_DAT_SYM_INSTALL_DIR SIM_DIR
#define SDRAM_MEMORY_INFO_GENERATE_DAT_SYM 1
#define SDRAM_MEMORY_INFO_MEM_INIT_DATA_WIDTH 16


/*
 * Macros for device 'filter_select', class 'altera_avalon_pio'
 * The macros are prefixed with 'FILTER_SELECT_'.
 * The prefix is the slave descriptor.
 */
#define FILTER_SELECT_COMPONENT_TYPE altera_avalon_pio
#define FILTER_SELECT_COMPONENT_NAME filter_select
#define FILTER_SELECT_BASE 0x500
#define FILTER_SELECT_SPAN 16
#define FILTER_SELECT_END 0x50f
#define FILTER_SELECT_BIT_CLEARING_EDGE_REGISTER 0
#define FILTER_SELECT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FILTER_SELECT_CAPTURE 0
#define FILTER_SELECT_DATA_WIDTH 8
#define FILTER_SELECT_DO_TEST_BENCH_WIRING 0
#define FILTER_SELECT_DRIVEN_SIM_VALUE 0
#define FILTER_SELECT_EDGE_TYPE NONE
#define FILTER_SELECT_FREQ 50000000
#define FILTER_SELECT_HAS_IN 0
#define FILTER_SELECT_HAS_OUT 1
#define FILTER_SELECT_HAS_TRI 0
#define FILTER_SELECT_IRQ_TYPE NONE
#define FILTER_SELECT_RESET_VALUE 0

/*
 * Macros for device 'Pixel_DMA_Addr_Translation', class 'altera_up_avalon_video_dma_ctrl_addr_trans'
 * The macros are prefixed with 'PIXEL_DMA_ADDR_TRANSLATION_'.
 * The prefix is the slave descriptor.
 */
#define PIXEL_DMA_ADDR_TRANSLATION_COMPONENT_TYPE altera_up_avalon_video_dma_ctrl_addr_trans
#define PIXEL_DMA_ADDR_TRANSLATION_COMPONENT_NAME Pixel_DMA_Addr_Translation
#define PIXEL_DMA_ADDR_TRANSLATION_BASE 0x0
#define PIXEL_DMA_ADDR_TRANSLATION_SPAN 16
#define PIXEL_DMA_ADDR_TRANSLATION_END 0xf

/*
 * Macros for device 'AV_Config', class 'altera_up_avalon_audio_and_video_config'
 * The macros are prefixed with 'AV_CONFIG_'.
 * The prefix is the slave descriptor.
 */
#define AV_CONFIG_COMPONENT_TYPE altera_up_avalon_audio_and_video_config
#define AV_CONFIG_COMPONENT_NAME AV_Config
#define AV_CONFIG_BASE 0x3020
#define AV_CONFIG_SPAN 16
#define AV_CONFIG_END 0x302f

/*
 * Macros for device 'VGA_Subsystem_VGA_Char_Buffer_avalon_char_control_slave', class 'altera_up_avalon_video_character_buffer_with_dma'
 * The macros are prefixed with 'VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_'.
 * The prefix is the slave descriptor.
 */
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_COMPONENT_TYPE altera_up_avalon_video_character_buffer_with_dma
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_COMPONENT_NAME VGA_Subsystem_VGA_Char_Buffer
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_BASE 0x3030
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_SPAN 8
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_END 0x3037

/*
 * Macros for device 'sysid_qsys', class 'altera_avalon_sysid_qsys'
 * The macros are prefixed with 'SYSID_QSYS_'.
 * The prefix is the slave descriptor.
 */
#define SYSID_QSYS_COMPONENT_TYPE altera_avalon_sysid_qsys
#define SYSID_QSYS_COMPONENT_NAME sysid_qsys
#define SYSID_QSYS_BASE 0x10000
#define SYSID_QSYS_SPAN 8
#define SYSID_QSYS_END 0x10007
#define SYSID_QSYS_ID 2899645186
#define SYSID_QSYS_TIMESTAMP 1521668924

/*
 * Macros for device 'jtag_uart', class 'altera_avalon_jtag_uart'
 * The macros are prefixed with 'JTAG_UART_'.
 * The prefix is the slave descriptor.
 */
#define JTAG_UART_COMPONENT_TYPE altera_avalon_jtag_uart
#define JTAG_UART_COMPONENT_NAME jtag_uart
#define JTAG_UART_BASE 0x20000
#define JTAG_UART_SPAN 8
#define JTAG_UART_END 0x20007
#define JTAG_UART_IRQ 2
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8

/*
 * Macros for device 'onchip_memory2_0', class 'altera_avalon_onchip_memory2'
 * The macros are prefixed with 'ONCHIP_MEMORY2_0_'.
 * The prefix is the slave descriptor.
 */
#define ONCHIP_MEMORY2_0_COMPONENT_TYPE altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_COMPONENT_NAME onchip_memory2_0
#define ONCHIP_MEMORY2_0_BASE 0x8000000
#define ONCHIP_MEMORY2_0_SPAN 262144
#define ONCHIP_MEMORY2_0_END 0x803ffff
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 1
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE AUTO
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE soc_system_onchip_memory2_0
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID NONE
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE AUTO
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE DONT_CARE
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 1
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 262144
#define ONCHIP_MEMORY2_0_WRITABLE 1
#define ONCHIP_MEMORY2_0_MEMORY_INFO_DAT_SYM_INSTALL_DIR SIM_DIR
#define ONCHIP_MEMORY2_0_MEMORY_INFO_GENERATE_DAT_SYM 1
#define ONCHIP_MEMORY2_0_MEMORY_INFO_GENERATE_HEX 1
#define ONCHIP_MEMORY2_0_MEMORY_INFO_HAS_BYTE_LANE 0
#define ONCHIP_MEMORY2_0_MEMORY_INFO_HEX_INSTALL_DIR QPF_DIR
#define ONCHIP_MEMORY2_0_MEMORY_INFO_MEM_INIT_DATA_WIDTH 32
#define ONCHIP_MEMORY2_0_MEMORY_INFO_MEM_INIT_FILENAME soc_system_onchip_memory2_0

/*
 * Macros for device 'VGA_Subsystem_VGA_Char_Buffer_avalon_char_buffer_slave', class 'altera_up_avalon_video_character_buffer_with_dma'
 * The macros are prefixed with 'VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_'.
 * The prefix is the slave descriptor.
 */
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_COMPONENT_TYPE altera_up_avalon_video_character_buffer_with_dma
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_COMPONENT_NAME VGA_Subsystem_VGA_Char_Buffer
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE 0x9000000
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_SPAN 8192
#define VGA_SUBSYSTEM_VGA_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_END 0x9001fff
#endif /* _ALTERA_HPS_0_H_ */
