/*
 * GNSS.h
 *
 *  Created on: Sep 7, 2024
 *      Author: PC_6285_Yİ
 */

#ifndef GNSS_GNSS_H_
#define GNSS_GNSS_H_
#include "stdint.h"
typedef struct
{
	uint16_t yil;
	uint8_t ay;
	uint8_t gun;
	uint8_t dakika;
	uint8_t saniye;
	int32_t boylam;
	int32_t enlem;
	enum{
		SM_GNSS_IDLE=0,
		SM_GNSS_WAIT_FOR_REPLY,
		SM_GNSS_NO_REPLY
	}SM;
}GNSS;



void GNSS_Tanimla(GNSS *GNSS_t);
uint8_t GNSS_Veri_Al(GNSS *GNSS_t);
uint8_t GNSS_Send_Command(GNSS *GNSS_t);
void GNSS_Gorev(GNSS *GNSS_t);

#endif /* GNSS_GNSS_H_ */
