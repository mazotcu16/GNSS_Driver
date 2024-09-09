/*
 * U-Blox_F9P_Driver.h
 *
 *  Created on: Sep 5, 2024
 *      Author: PC_6285_Yİ
 */

#ifndef U_BLOX_F9P_DRIVER_U_BLOX_F9P_DRIVER_H_
#define U_BLOX_F9P_DRIVER_U_BLOX_F9P_DRIVER_H_

#include <stdint.h>

#define UBX_MESSAGE_CLASS_CFG 0x06
#define UBX_MESSAGE_CLASS_ACK 0x05
#define UBX_MESSAGE_CLASS_NAV 0x01
#define UBX_MESSAGE_ID_PRT    0x00
#define UBX_MESSAGE_ID_PVT    0x07
#define UBX_MESSAGE_ID_ACK    0x01
#define UBX_CFG_PRT_LEN       20
#define UBX_
typedef union {
	struct {
		uint8_t en_u1 :1;
		uint8_t pol_u1 :1;
		uint8_t pin_4_0_u5 :5;
		uint16_t thres_8_0_u9 :9;
	} bit_s;
	uint16_t u16;
} Tx_Ready;

typedef union {
	struct {
		uint8_t reserved_5_0_u6    :6;
		uint8_t char_len_1_0_u2    :2;
		uint8_t reserved_u1        :1;
		uint8_t parity_2_0_u3      :3;
		uint8_t n_stop_bits_1_0_u2 :2;
		uint32_t reserved_16_0_u18 :18;

	} __attribute__((packed)) bit_s;
	uint32_t u32;
} __attribute__((packed)) Mode;

typedef union {
	struct {
		uint8_t in_Ubx_u1 :1;
		uint8_t in_Nmea_u1 :1;
		uint8_t in_Rtcm_u1 :1;
		uint8_t reserved_1_0_u2 :2;
		uint8_t in_Rtcm3_u1 :1;
		uint16_t reserved_9_0_u10 :10;
	} bit_s;
	uint16_t u16;
} in_Proto_Mask;

typedef union {
	struct {
		uint8_t out_Ubx_u1 :1;
		uint8_t out_Nmea_u1 :1;
		uint8_t out_Rtcm_u1 :1;
		uint8_t reserved_1_0_u2 :2;
		uint8_t out_Rtcm3_u1 :1;
		uint16_t reserved_9_0_u10 :10;
	} bit_s;
	uint16_t u16;
} out_Proto_Mask;

typedef union {
	struct {
		uint8_t reserved_u1 :1;
		uint8_t extended_Tx_Timeout_u1 :1;
		uint16_t reserved_13_0_u14 :14;

	} bit_s;
	uint16_t u16;
} Flags;
typedef struct {
	uint8_t port_id;
	uint8_t reserved_7_0_u8;
	Tx_Ready Tx_Ready_t;
	Mode Mode_t;
	uint32_t baudrate;
	in_Proto_Mask in_Proto_Mask_t;
	out_Proto_Mask out_Proto_Mask_t;
	Flags Flags_t;
	uint16_t reserved_15_0_u16;
} U_Blox_Payload_Cfg_Prt;







typedef union{
	struct{
		uint8_t valid_Date_u1           :1;
		uint8_t valid_Time_u1           :1;
        uint8_t fully_resolved_u1       :1;
        uint8_t valid_mag_u1            :1;
        uint8_t reserved_3_0_u4         :4;
	}bit_s;
	uint8_t u8;
}Valid;

typedef union{
	struct{
		uint8_t gnss_fix_ok_u1           :1;
		uint8_t diff_so_in_u1            :1;
		uint8_t psm_state_2_0_u3         :3;
		uint8_t head_veh_valid_u1        :1;
		uint8_t carr_so_in_1_0_u2        :2;
	}bit_s;
	uint8_t u8;
}Nav_Flags_1;

typedef union{
	struct
	{
		uint8_t reserved_4_0_u5          :5;
		uint8_t confirmed_avai           :1;
		uint8_t confirmed_date           :1;
		uint8_t confirmed_time           :1;
	}bit_s;
	uint8_t u8;
}Nav_Flags_2;

typedef union{
	struct
	{
     uint8_t invalid_lih_u1                 :1;
     uint8_t last_correction_age_3_0_u4     :4;
     uint8_t reserved_2_0_u3                :3;
	}bit_s;
	uint16_t u16;
}Nav_Flags_3;

typedef struct {
uint32_t itow;
uint16_t year;
uint8_t month;
uint8_t day;
uint8_t hour;
uint8_t min;
uint8_t sec;
Valid   valid_t;
uint32_t t_acc;
int32_t  nano;
uint8_t fix_type;
Nav_Flags_1 Nav_Flags_1_t;
Nav_Flags_2 Nav_Flags_2_t;
uint8_t num_sv;
int32_t lon;
int32_t lat;
int32_t height;
int32_t hMSL;
int32_t hAcc;
int32_t vAcc;
int32_t ve_ln;
int32_t ve_le;
int32_t ve_id;
int32_t g_speed;
int32_t head_mot;
uint32_t s_acc;
uint32_t head_acc;
uint16_t p_dop;
Nav_Flags_3 Nav_Flags_3_t;
uint32_t reserved;
int32_t head_veh;
int16_t mag_dec;
int16_t mag_acc;
}U_Blox_Payload_Nav_Pvt;

typedef union {
	U_Blox_Payload_Cfg_Prt U_Blox_Payload_Cfg_Prt_t;
	U_Blox_Payload_Nav_Pvt U_Blox_Payload_Nav_Pvt_t;
	uint8_t data[500];
} U_Blox_Payload;

typedef struct {
	uint8_t message_class;
	uint8_t message_id;
	uint16_t length;
	U_Blox_Payload payload;
} U_Blox_frame_high_layer;


void U_Blox_Set_Frame(U_Blox_frame_high_layer* U_blox_Frame);
void U_Blox_Get_Package(U_Blox_frame_high_layer* U_Blox_frame_high_layer_t);
uint8_t U_Blox_Send_Frame();
void U_Blox_Receive_Data(uint8_t data);
void U_Blox_Send_Data(uint8_t data);
void U_Blox_Task();
void RxBufferMove(uint16_t move);
void U_Blox_Init();
uint8_t U_Blox_Is_Packet_Ready_To_Send(void);
void U_Blox_Send_Packet();
uint8_t U_Blox_Is_Packet_Ready();
#endif /* U_BLOX_F9P_DRIVER_U_BLOX_F9P_DRIVER_H_ */
