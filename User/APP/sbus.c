#include "sbus.h"
#include "stm32f4xx.h"
#include "rc.h"
uint8_t SBUS_MsgPack[25];
uint16_t SBUS_ChanelVal[16];

#define RC_CHANNAL_ERROR_VALUE 700

static int16_t RC_abs(int16_t value);
static void SBUS_Decode(uint8_t *MsgPack, RC_ctrl_t *rc_ctrl);
static uint16_t msg[4];
RC_ctrl_t rc_ctrl;

uint8_t SBUS_rx_buf[2][SBUS_RX_BUF_NUM];

void Remote_Config(void)
{
    RC_Init(SBUS_rx_buf[0], SBUS_rx_buf[1], SBUS_RX_BUF_NUM);
}

const RC_ctrl_t *get_remote_control_point(void)
{
    return &rc_ctrl;
}

uint8_t RC_data_is_error(void)
{
    if (RC_abs(rc_ctrl.rc.ch[0]) > RC_CHANNAL_ERROR_VALUE)
    {
        goto error;
    }
    if (RC_abs(rc_ctrl.rc.ch[1]) > RC_CHANNAL_ERROR_VALUE)
    {
        goto error;
    }
    if (RC_abs(rc_ctrl.rc.ch[2]) > RC_CHANNAL_ERROR_VALUE)
    {
        goto error;
    }
    if (RC_abs(rc_ctrl.rc.ch[3]) > RC_CHANNAL_ERROR_VALUE)
    {
        goto error;
    }

    return 0;

error:
    rc_ctrl.rc.ch[0] = 0;
    rc_ctrl.rc.ch[1] = 0;
    rc_ctrl.rc.ch[2] = 0;
    rc_ctrl.rc.ch[3] = 0;
    rc_ctrl.rc.ch[4] = 0;

    return 1;
}

void slove_RC_lost(void)
{
    RC_restart(SBUS_RX_BUF_NUM);
}
void slove_data_error(void)
{
    RC_restart(SBUS_RX_BUF_NUM);
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        USART_ReceiveData(USART1);
    }
    else if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {
        static uint16_t this_time_rx_len = 0;
        USART_ReceiveData(USART1);

        if (DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0)
        {
            DMA_Cmd(DMA2_Stream2, DISABLE);
            this_time_rx_len = SBUS_RX_BUF_NUM - DMA_GetCurrDataCounter(DMA2_Stream2);
            DMA_SetCurrDataCounter(DMA2_Stream2, SBUS_RX_BUF_NUM);
            DMA2_Stream2->CR |= DMA_SxCR_CT;
            DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA2_Stream2, ENABLE);
            if (this_time_rx_len == RC_FRAME_LENGTH)
            {
							SBUS_Decode(SBUS_rx_buf[0], &rc_ctrl);
								
            }
        }
        else
        {
            DMA_Cmd(DMA2_Stream2, DISABLE);
            this_time_rx_len = SBUS_RX_BUF_NUM - DMA_GetCurrDataCounter(DMA2_Stream2);
            DMA_SetCurrDataCounter(DMA2_Stream2, SBUS_RX_BUF_NUM);
            DMA2_Stream2->CR &= ~(DMA_SxCR_CT);
            DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA2_Stream2, ENABLE);
            if (this_time_rx_len == RC_FRAME_LENGTH)
            {
								SBUS_Decode(SBUS_rx_buf[1], &rc_ctrl);
            }
        }
    }
}

static int16_t RC_abs(int16_t value)
{
    if (value > 0)
    {
        return value;
    }
    else
    {
        return -value;
    }
}




static void SBUS_Decode(uint8_t *MsgPack , RC_ctrl_t *rc_ctrl)
{

	rc_ctrl->rc.ch[0] = ((MsgPack[1]		| MsgPack[2] << 8)	& 0x07FF);
	rc_ctrl->rc.ch[1] = ((MsgPack[2] >> 3	| MsgPack[3] << 5)	& 0x07FF);
	rc_ctrl->rc.ch[2] = ((MsgPack[3] >> 6	| MsgPack[4] << 2 | MsgPack[5] << 10)	& 0x07FF);
	rc_ctrl->rc.ch[3] = ((MsgPack[5] >> 1	| MsgPack[6] << 7)	& 0x07FF);
	rc_ctrl->rc.ch[4] = ((MsgPack[12]		| MsgPack[13] << 8)	& 0x07FF);
	rc_ctrl->rc.ch[5] = ((MsgPack[13] >> 3	| MsgPack[14]<<5)	& 0x07FF);


	msg[0] = ((MsgPack[6] >> 4	| MsgPack[7] <<4)	& 0x07FF);
	msg[1] = ((MsgPack[7] >> 7	| MsgPack[8] << 1 | MsgPack[9] << 9)	& 0x07FF);
	msg[2] = ((MsgPack[9] >> 2	| MsgPack[10] << 6)	& 0x07FF);
	msg[3] = ((MsgPack[10] >> 5	| MsgPack[11] << 3)	& 0x07FF);
	
	if(msg[0] < 1024){
		rc_ctrl->sw.swA = 0;
	}
	else{
		rc_ctrl->sw.swA = 2;		
	}
		
	if(msg[1] < 600){
		rc_ctrl->sw.swB = 0;
	}
	else if(msg[1] > 600 &&	msg[1] < 1400){
		rc_ctrl->sw.swB = 1;
	}
	else{
		rc_ctrl->sw.swB = 2;			
	}

	
	if(msg[2] < 600){
		rc_ctrl->sw.swC = 0;
	
	}
	else if(msg[2] > 600 && msg[2] < 1400){
		rc_ctrl->sw.swC = 1;	
	}
	else{
		rc_ctrl->sw.swC = 2;		
	}
	
	if(msg[3] < 1024){
		rc_ctrl->sw.swD = 0;
	}
	else{
		rc_ctrl->sw.swD = 2;	
	}
	
	
	
	rc_ctrl->rc.ch[0] -= RC_CH_VALUE_OFFSET;
  rc_ctrl->rc.ch[1] -= RC_CH_VALUE_OFFSET;
  rc_ctrl->rc.ch[2] -= RC_CH_VALUE_OFFSET;
  rc_ctrl->rc.ch[3] -= RC_CH_VALUE_OFFSET;
  rc_ctrl->rc.ch[4] -= RC_CH_VALUE_OFFSET;
	rc_ctrl->rc.ch[5] -= RC_CH_VALUE_OFFSET;
}

