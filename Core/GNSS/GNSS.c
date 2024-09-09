/*
 * GNSS.c
 *
 *  Created on: Sep 7, 2024
 *      Author: PC_6285_Yİ
 */
#include "GNSS.h"
#include "U-Blox_F9P_Driver/U-Blox_F9P_Driver.h"
#include "SysTick_Timer.h"
U_Blox_frame_high_layer U_Blox_frame_tx;
U_Blox_frame_high_layer U_Blox_frame_rx;
int b=0;
static uint32_t zaman;
void GNSS_Tanimla(GNSS *GNSS_t) {
	U_Blox_Init();
	for (int i = 0; i < 26; i++) {
		U_Blox_frame_tx.payload.data[i] = 0;
	}
	U_Blox_frame_tx.message_class = UBX_MESSAGE_CLASS_CFG; //config classi
	U_Blox_frame_tx.message_id = UBX_MESSAGE_ID_PRT; //Port
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.Flags_t.bit_s.extended_Tx_Timeout_u1 =
			0;
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.Mode_t.bit_s.char_len_1_0_u2 =
			3;
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.Mode_t.bit_s.reserved_5_0_u6 =
			16;
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.Mode_t.bit_s.n_stop_bits_1_0_u2 =
			0;
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.Mode_t.bit_s.parity_2_0_u3 =
			4;
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.baudrate = 38400;
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.Tx_Ready_t.u16 = 0;
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.in_Proto_Mask_t.bit_s.in_Ubx_u1 =
			1;
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.out_Proto_Mask_t.bit_s.out_Ubx_u1 =
			1;
	U_Blox_frame_tx.payload.U_Blox_Payload_Cfg_Prt_t.port_id = 1;
	U_Blox_frame_tx.length = UBX_CFG_PRT_LEN;
	U_Blox_Set_Frame(&U_Blox_frame_tx);
	if(U_Blox_Is_Packet_Ready_To_Send())
	{
		U_Blox_Send_Packet();
	}
	U_Blox_Send_Frame();
	//while(!U_Blox_Is_Packet_Ready());
	GNSS_t->SM=SM_GNSS_WAIT_FOR_REPLY;
	zaman=SystickGetMs();
}
uint8_t GNSS_Veri_Al(GNSS *GNSS_t) {
	if(SystickCheckMs(zaman,500))
	{
	U_Blox_frame_tx.message_class = UBX_MESSAGE_CLASS_NAV;
	U_Blox_frame_tx.message_id = UBX_MESSAGE_ID_PVT;
	U_Blox_frame_tx.length = 0;
	U_Blox_Set_Frame(&U_Blox_frame_tx);
	if(U_Blox_Is_Packet_Ready_To_Send())
	{
		U_Blox_Send_Packet();
		GNSS_t->SM=SM_GNSS_IDLE;
	}
	U_Blox_Send_Frame();
	zaman=SystickGetMs();
	}

	if (U_Blox_Is_Packet_Ready()) {
		U_Blox_Get_Package(&U_Blox_frame_rx);
		if (U_Blox_frame_rx.message_class == UBX_MESSAGE_CLASS_NAV) {
			GNSS_t->ay = U_Blox_frame_rx.payload.U_Blox_Payload_Nav_Pvt_t.month;
			GNSS_t->boylam =
					U_Blox_frame_rx.payload.U_Blox_Payload_Nav_Pvt_t.lon;
			GNSS_t->enlem = U_Blox_frame_rx.payload.U_Blox_Payload_Nav_Pvt_t.lat;
			GNSS_t->gun = U_Blox_frame_rx.payload.U_Blox_Payload_Nav_Pvt_t.day;
			GNSS_t->dakika =
					U_Blox_frame_rx.payload.U_Blox_Payload_Nav_Pvt_t.min;
			GNSS_t->yil = U_Blox_frame_rx.payload.U_Blox_Payload_Nav_Pvt_t.year;
			GNSS_t->saniye =
					U_Blox_frame_rx.payload.U_Blox_Payload_Nav_Pvt_t.sec;
			U_Blox_frame_tx.message_class = UBX_MESSAGE_CLASS_NAV;
			U_Blox_frame_tx.message_id = UBX_MESSAGE_ID_PVT;
			U_Blox_frame_tx.length = 0;
			U_Blox_Set_Frame(&U_Blox_frame_tx);
			U_Blox_Send_Frame();
		}
		if (U_Blox_frame_rx.message_class == 5) {
			b++;
		}
        return 1;
	}
	else{
		return 0;
	}
}

void GNSS_Gorev(GNSS *GNSS_t) {
	U_Blox_Task();
}
