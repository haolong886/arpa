/*==================================================================*/
/*  Copyright (c) 2010, Texas Instruments Incorporated              */
/*  All rights reserved.                                            */
/*                                                                  */
/*                                                                  */
/* ======== appMain.h ========                                      */
/*   This is main app header file                                   */
/*                                                                  */
/*                                                                  */
/*  Version: 0.0.1                                                  */
/*==================================================================*/

#ifndef appMain_h_
#define appMain_h_
#define ARPA_TRACK_NUM	20

typedef struct target
{
	unsigned int latest_x;
	unsigned int latest_y;
	unsigned int filtration_x;
	unsigned int filtration_y;
	unsigned int prediction_x;
	unsigned int prediction_y;
}TARGET;

typedef struct arpa_track_targets
{
	unsigned int target_num;
	TARGET target_array[ARPA_TRACK_NUM];
}ARPA_TRACK_TARGETS;

#endif 
