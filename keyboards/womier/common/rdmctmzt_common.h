/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdio.h>
#include <stdint.h>
#include "quantum.h"
#include "quantum_keycodes.h"
#include "dynamic_keymap.h"
#include "md_adc.h"
#include "usb_main.h"
#include "raw_hid.h"
#include "usb_descriptor.h"

#include "three_mode.h"
#include "user_battery.h"
#include "user_eeprom.h"
#include "user_emi.h"
#include "user_led_custom.h"
#include "user_spi.h"
#include "user_system.h"

#define ES_BATT_ADC_IO      (C4)
#define ES_BATT_STDBY_IO    (A13)
#define ES_USB_POWER_IO     (C5)
#define ES_SPI_ACK_IO       (A4)
#define ES_PWM_DMA_IO       (A2)

#define ES_WUKEUP_IO        (D1)
#define ES_SDB_POWER_IO     (A3)
#define ES_LED_POWER_IO     (D0)

#define PAL_ES32_PUPDR_PULLDOWN   PAL_ES32_PUD_PULLDOWN

#define USER_KEY_BYTE_LENGTH	0X08
#define USER_KEY_BIT_LENGTH		0X0F
#define USER_MOUSE_LENGTH		0X08
#define USER_CONSUMER_LENGTH	0X03
#define USER_SYSTEM_LENGTH		0X03
#define USER_BATTERY_LENGTH		0X02

#define KB_REPORT_ID            0x06    // Extend keyboard report ID.
#define SYS_REPORT_ID     	    0x03    // Extend System   report ID.
#define CON_REPORT_ID     	    0x04    // Extend Consumer report ID.
#define MOUSE_REPORT_ID  	    0x02    // Extend mouse	   report ID.

#define USER_DEFINE_KEY         (QK_KB)
enum Custom_Keycodes {
    QMK_KB_MODE_2P4G = USER_DEFINE_KEY,
    QMK_KB_MODE_BLE1,
    QMK_KB_MODE_BLE2,
    QMK_KB_MODE_BLE3,
    QMK_KB_MODE_USB,
    QMK_BATT_NUM,
    QMK_WIN_LOCK,
    QMK_KB_SIX_N_CH,
    QMK_TEST_COLOUR,
    QMK_KB_2P4G_PAIR,
    QMK_KB_BLE1_PAIR,
    QMK_KB_BLE2_PAIR,
    QMK_KB_BLE3_PAIR
};

enum Custom_KeyModes {
    QMK_BLE_MODE = 0,
    QMK_2P4G_MODE,
    QMK_USB_MODE
};

enum Custom_BleChannels {
    QMK_BLE_CHANNEL_1 = 1,
    QMK_BLE_CHANNEL_2,
    QMK_BLE_CHANNEL_3
};

enum Custom_Ble_24G_Status_S {
    BLE_24G_NONE,
    BLE_24G_PIAR,
    BLE_24G_RETURN
};

typedef struct {
	uint8_t Key_Mode;
	uint8_t Ble_Channel;
	uint8_t Batt_Number;
	uint8_t Nkro;
	uint8_t Mac_Win_Mode;
	uint8_t Win_Lock;
} Keyboard_Info_t;

typedef struct {
	uint8_t System_Work_Status;
	uint8_t System_Work_Mode;
	uint8_t System_Work_Channel;
	uint8_t System_Connect_Status;
	uint8_t System_Led_Status;
	uint8_t System_Sleep_Mode;
} Keyboard_Status_t;

typedef enum {
	KB_MODE_CONNECT_OK,
	KB_MODE_CONNECT_PAIR,
	KB_MODE_CONNECT_RETURN,
} keyboard_System_state_e;

typedef enum {
	USER_SLEEP_PASS,
	USER_SLEEP_FIAL,
} keyboard_System_Sleep_Status_s;

#define INIT_WORK_MODE              (QMK_USB_MODE)
#define INIT_BLE_CHANNEL            (QMK_BLE_CHANNEL_1)
#define INIT_BATT_NUMBER            (50)

#define INIT_SIX_KEY                (0)
#define INIT_ALL_KEY                (1)
#define INIT_ALL_SIX_KEY            (INIT_ALL_KEY)

#define INIT_WIN_MODE               (0)
#define INIT_MAC_MODE               (1)
#define INIT_WIN_MAC_MODE           (INIT_WIN_MODE)

#define INIT_WIN_NLOCK              (0)
#define INIT_WIN_LOCK               (1)
#define INIT_WIN_LOCK_NLOCK         (INIT_WIN_NLOCK)

#define U_PWM                       (RGB_MATRIX_MAXIMUM_BRIGHTNESS)

#define USER_BATT_DELAY_TIME        (100 * 25)  //25S
#define USER_TIME_3S_TIME           (100 * 3)   //3S

#define KC_K29 	KC_BACKSLASH
#define KC_K42 	KC_NONUS_HASH
#define KC_K45 	KC_NONUS_BACKSLASH
#define KC_K56 	KC_INTERNATIONAL_1
#define KC_K14  KC_INTERNATIONAL_3
#define KC_K132	KC_INTERNATIONAL_4
#define KC_K131	KC_INTERNATIONAL_5
#define KC_K133	KC_INTERNATIONAL_2
#define KC_K151	KC_LANGUAGE_1
#define KC_K150	KC_LANGUAGE_2

#define MD_24G	QMK_KB_MODE_2P4G
#define MD_BLE1	QMK_KB_MODE_BLE1
#define MD_BLE2	QMK_KB_MODE_BLE2
#define MD_BLE3	QMK_KB_MODE_BLE3
#define MD_USB	QMK_KB_MODE_USB
#define QK_BAT  QMK_BATT_NUM
#define QK_WLO	QMK_WIN_LOCK
#define SIX_N	QMK_KB_SIX_N_CH
#define TEST_CL	QMK_TEST_COLOUR

extern Keyboard_Info_t Keyboard_Info;
extern Keyboard_Status_t Keyboard_Status;

extern const uint32_t g_es_dma_ch2pri_cfg;
extern const uint32_t g_es_dma_ch2alt_cfg;

extern bool Led_Rf_Pair_Flg;
extern bool Key_2p4g_Status;
extern bool Key_Ble_1_Status;
extern bool Key_Ble_2_Status;
extern bool Key_Ble_3_Status;
extern bool Key_Reset_Status;
extern bool Keyboard_Reset;
extern bool Init_Eeprom_Flg;
extern bool Led_Off_Start;
extern bool Led_Power_Up;
extern bool Usb_If_Ok_Led;
extern uint16_t Led_Power_Up_Delay;
extern uint8_t Temp_System_Led_Status;

extern uint8_t Systick_6ms_Count;
extern uint8_t Systick_10ms_Count;
extern uint16_t Systick_Interval_Count;
extern uint8_t Systick_Led_Count;
extern uint8_t Batt_Led_Count;
extern uint16_t Time_3s_Count;
extern uint16_t Func_Time_3s_Count;

extern void Init_Keyboard_Infomation(void);
extern void es_change_qmk_nkro_mode_enable(void);
void es_change_qmk_nkro_mode_disable(void);
