/*
 * U-Blox_F9P_Driver.c
 *
 *  Created on: Sep 5, 2024
 *      Author: PC_6285_Yİ
 */

#include "U-Blox_F9P_Driver.h"
#include "stm32h7xx.h"
#include <string.h>
extern UART_HandleTypeDef huart3;
extern uint8_t uart_buffer[501];
uint8_t my_buffer[501];
typedef struct {
	uint8_t sync_char_1;
	uint8_t sync_char_2;
	uint8_t message_class;
	uint8_t message_id;
	uint16_t length;
	uint8_t payload[500];
//checksum payload icinde olacak uint16_t checksum;

} U_Blox_frame_low_layer;

U_Blox_frame_low_layer U_Blox_frame_low_layer_transmit;
uint16_t U_Blox_Calculate_Checksum(U_Blox_frame_low_layer *U_blox_Frame);

static struct {
	enum {
		SM_RX_IDLE = 0, SM_RX_PROCESS
	} Sm;
	uint8_t Buffer[501];
	uint16_t buffer_index;
} U_Blox_Rx;

static struct {
	enum {
		SM_TX_IDLE = 0, SM_TX_PREPARE, SM_TX_SEND,
	} Sm;
	uint8_t Buffer[500];
	uint16_t buffer_index;
} U_Blox_Tx;

void U_Blox_Init() {
	U_Blox_Rx.Sm = SM_RX_IDLE;
	U_Blox_Tx.Sm = SM_TX_IDLE;
	HAL_UART_Receive_DMA(&huart3, U_Blox_Rx.Buffer, 500);
}
void U_Blox_Task() {
	U_Blox_frame_low_layer *U_Blox_frame_low_layer_t;
	switch (U_Blox_Tx.Sm) {
	case SM_TX_IDLE:
		break;
	case SM_TX_PREPARE:
		break;
	case SM_TX_SEND:
		U_Blox_frame_low_layer_t = (U_Blox_frame_low_layer*) U_Blox_Tx.Buffer;
		HAL_UART_Transmit_DMA(&huart3,(uint8_t*)U_Blox_frame_low_layer_t,U_Blox_frame_low_layer_t->length+8);
		//while (U_Blox_Tx.buffer_index < U_Blox_frame_low_layer_t->length + 8) {
		//	U_Blox_Send_Data(U_Blox_Tx.Buffer[U_Blox_Tx.buffer_index]);
		//}
		//if (U_Blox_Tx.buffer_index >= U_Blox_frame_low_layer_t->length + 8) {
		//	U_Blox_Tx.Sm = SM_TX_IDLE;
		//}
		break;
	}
	switch (U_Blox_Rx.Sm) {
	case SM_RX_IDLE:
		U_Blox_Rx.buffer_index = GetRxBufferIndex();
		U_Blox_frame_low_layer_t = (U_Blox_frame_low_layer*) &U_Blox_Rx.Buffer;
		//for(int i=0;i<U_Blox_Rx.buffer_index;i++)
		//{
		if (U_Blox_Rx.buffer_index >= 2) {
			if ((U_Blox_frame_low_layer_t->sync_char_1 == 0xB5)
					&& (U_Blox_frame_low_layer_t->sync_char_2 == 0x62)) {
				if (U_Blox_Rx.buffer_index >= 5) {

					if (U_Blox_Rx.buffer_index
							>= U_Blox_frame_low_layer_t->length + 7) {
						if ((*(uint16_t*) &U_Blox_Rx.Buffer[6
								+ U_Blox_frame_low_layer_t->length])
								== U_Blox_Calculate_Checksum(
										U_Blox_frame_low_layer_t)) {
							HAL_UART_DMAStop(&huart3);
							HAL_UART_Receive_DMA(&huart3, U_Blox_Rx.Buffer,
									500);
							U_Blox_Rx.Sm = SM_RX_PROCESS;
						}
					}
				}
			} else {
				HAL_UART_DMAStop(&huart3);
				HAL_UART_Receive_DMA(&huart3, U_Blox_Rx.Buffer, 500);
			}
		}

		//U_Blox_Rx.buffer_index=GetRxBufferIndex();
		//U_Blox_frame_low_layer_t = (U_Blox_frame_low_layer*) U_Blox_Rx.Buffer;
		//if (U_Blox_Rx.buffer_index >= 2) {
		//	if (!((U_Blox_frame_low_layer_t->sync_char_1 == 0xB5)
		//			&& (U_Blox_frame_low_layer_t->sync_char_2 == 0x62))) {
		//		RxBufferMove(1);
		//	} else if (U_Blox_Rx.buffer_index
		//			>= (U_Blox_frame_low_layer_t->length + 8)) {
		//Payload bilinmeyen uzunlukta oldugu icin checksum degeri payload icerisinden kontrol edildi.
		//		if ((*(uint16_t*) &U_Blox_frame_low_layer_t->payload[U_Blox_frame_low_layer_t->length])
		//				!= U_Blox_Calculate_Checksum(
		//						U_Blox_frame_low_layer_t)) {
		//			RxBufferMove(U_Blox_frame_low_layer_t->length + 8);
		//		} else {
		//			U_Blox_Rx.Sm = SM_RX_PROCESS;
		//			U_Blox_Rx.buffer_index = 0;
		//			RxBufferDeletePackage(U_Blox_frame_low_layer_t->length + 8);
		//		}
		//	}
		//}
		break;
	case SM_RX_PROCESS:
		break;
	}
}

void U_Blox_Set_Frame(U_Blox_frame_high_layer *U_Blox_frame_high_layer_t) {
	U_Blox_frame_low_layer *U_Blox_frame_low_layer_t=(U_Blox_frame_low_layer*)U_Blox_Tx.Buffer;
	U_Blox_frame_low_layer_t->sync_char_1=0xB5;
	U_Blox_frame_low_layer_t->sync_char_2=0x62;
	U_Blox_frame_low_layer_t->message_id=U_Blox_frame_high_layer_t->message_id;
	U_Blox_frame_low_layer_t->message_class=U_Blox_frame_high_layer_t->message_class;
    U_Blox_frame_low_layer_t->length=U_Blox_frame_high_layer_t->length;
    memcpy(U_Blox_frame_low_layer_t->payload,U_Blox_frame_high_layer_t->payload.data,U_Blox_frame_high_layer_t->length);
    (*(uint16_t*)&U_Blox_frame_low_layer_t->payload[U_Blox_frame_low_layer_t->length])=U_Blox_Calculate_Checksum(U_Blox_frame_low_layer_t);
	U_Blox_Tx.Sm = SM_TX_PREPARE;
}
uint8_t U_Blox_Send_Frame() {
//paket hazır mı kontrolu gerek
	HAL_UART_Transmit(&huart3,
			(uint8_t*) &U_Blox_frame_low_layer_transmit.sync_char_1, 6, 100);
	HAL_UART_Transmit(&huart3,
			(uint8_t*) &U_Blox_frame_low_layer_transmit.payload,
			U_Blox_frame_low_layer_transmit.length + 2, 100);
	return 1;
}
uint16_t U_Blox_Calculate_Checksum(U_Blox_frame_low_layer *U_blox_Frame) {
	uint8_t ck_a = 0;
	uint8_t ck_b = 0;
	uint8_t *data = (uint8_t*) &U_blox_Frame->message_class;
	for (int i = 0; i < U_blox_Frame->length + 4; i++) {
		ck_a = ck_a + *data;
		ck_b = ck_b + ck_a;
		data++;
	}
	return (uint16_t) (ck_a + (uint16_t) ((uint16_t) ck_b << 8));
}
void U_Blox_Receive_Data(uint8_t data) {
	if (U_Blox_Rx.buffer_index > 498) {
		U_Blox_Rx.buffer_index = 0;
		RxBufferMove(400);
	}
	U_Blox_Rx.Buffer[U_Blox_Rx.buffer_index] = data;
	U_Blox_Rx.buffer_index++;
}

uint8_t U_Blox_Is_Packet_Ready() {
	return (U_Blox_Rx.Sm == SM_RX_PROCESS);
}

uint8_t U_Blox_Is_Packet_Ready_To_Send(void) {
	return (U_Blox_Tx.Sm == SM_TX_IDLE);
}

void U_Blox_Send_Packet() {
	if (U_Blox_Tx.Sm == SM_TX_PREPARE) {
		U_Blox_Tx.buffer_index = 0;
		U_Blox_Tx.Sm = SM_TX_SEND;
	}
}
void U_Blox_Send_Data(uint8_t data) {
	HAL_UART_Transmit(&huart3, &data, 1, 10);
}
void U_Blox_Get_Package(U_Blox_frame_high_layer *U_Blox_frame_high_layer_t) {
	U_Blox_frame_low_layer *U_Blox_frame_low_layer_t =
			(U_Blox_frame_low_layer*) U_Blox_Rx.Buffer;

	U_Blox_frame_high_layer_t->length = U_Blox_frame_low_layer_t->length;
	U_Blox_frame_high_layer_t->message_class =
			U_Blox_frame_low_layer_t->message_class;
	U_Blox_frame_high_layer_t->message_id =
			U_Blox_frame_low_layer_t->message_id;
	for (int i = 0; i < 500; i++) {
		U_Blox_frame_high_layer_t->payload.data[i] =
				U_Blox_frame_low_layer_t->payload[i];
	}
	memset(U_Blox_Rx.Buffer, 0, 8 + U_Blox_frame_low_layer_t->length);
	U_Blox_Rx.Sm = SM_RX_IDLE;
}

void U_Blox_Receive_5_Byte(uint8_t *data) {
	memcpy(U_Blox_Rx.Buffer, data, 5);
	U_Blox_Rx.buffer_index = U_Blox_Rx.buffer_index + 5;
}
void RxBufferMove(uint16_t move) {
	int tempMove = move;
	int index = 0;
	while (move < U_Blox_Rx.buffer_index) {
		U_Blox_Rx.Buffer[index++] = U_Blox_Rx.Buffer[move++];
	}
	U_Blox_Rx.buffer_index -= tempMove;
}

void RxBufferDeletePackage(uint16_t size) {
	uint32_t index = 0;
	while (size < 500) {
		U_Blox_Rx.Buffer[index++] = U_Blox_Rx.Buffer[size++];
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
	U_Blox_Tx.Sm = SM_TX_IDLE;
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_TxCpltCallback can be implemented in the user file.
   */
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	/* Prevent unused argument(s) compilation warning */

	HAL_UART_Receive_DMA(&huart3, U_Blox_Rx.Buffer, 500);
	/* NOTE : This function should not be modified, when the callback is needed,
	 the HAL_UART_RxCpltCallback can be implemented in the user file.
	 */
}
uint16_t GetRxBufferIndex() {
	int a = 0;
	a = 499 - DMA1_Stream0->NDTR;
	if (a < 0) {
		return 0;
	} else {
		return a;
	}
}
