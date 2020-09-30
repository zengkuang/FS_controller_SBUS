#ifndef SBUS_H
#define SBUS_H
#include "main.h"
#include "rc.h"


#define SBUS_RX_BUF_NUM 36u
#define RC_FRAME_LENGTH 25u

#define RC_CH_VALUE_MIN ((uint16_t)240)
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1807)


#define RC_SW_UP ((uint16_t)0)
#define RC_SW_MID ((uint16_t)1)
#define RC_SW_DOWN ((uint16_t)2)

extern uint16_t SBUS_ChanelVal[];
extern uint8_t SBUS_MsgPack[];



/* ----------------------- Data Struct ------------------------------------- */
typedef __packed struct
{
        __packed struct
        {
                int16_t ch[6];  // -784~783
        } rc;
        __packed struct
        {
                int16_t swA;
                int16_t swB;
                int16_t swC;
								int16_t swD;
        } sw;

}RC_ctrl_t;

/* ----------------------- Internal Data ----------------------------------- */

extern void Remote_Config(void);
extern const RC_ctrl_t *get_remote_control_point(void);
extern uint8_t RC_data_is_error(void);
extern void slove_RC_lost(void);
extern void slove_data_error(void);
#endif
