/*==================================================================*/
/*  Copyright (c) 2010, Texas Instruments Incorporated              */
/*  All rights reserved.                                            */
/*                                                                  */
/*                                                                  */
/* ======== appMain.c ========                                      */
/*This is main app file that sets the testing mechnaism and calls   */
/*  functions to test kernels in C6Accel in C6ACCEL                 */
/*                                                                  */
/*                                                                  */
/*  Version: 0.0.1                                                  */
/*==================================================================*/

#include <fcntl.h>
/* Codec Engine and xdc includes */ 
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/osal/Memory.h>

/* system time include*/
#include <sys/time.h>
/* Include C6ACCEL headers */
#include "../c6accelw/c6accelw.h"

/* Test application include */
#include "appMain.h"

#include "arpa_alg.h"
#include "arpa_qt_display.h"

void track_targets_init(ARPA_TRACK_TARGETS *track_targets)
{
	track_targets->target_num = 1;
	track_targets->target_array[0].latest_x = 2;
	track_targets->target_array[0].latest_y = 3;
}


/******************************************************************************
 * appMain
 ******************************************************************************/
int main(int argc, char *argv[])
{
	unsigned int *i;
	ARPA_TRACK_TARGETS *track_targets = NULL;
//	track_targets = 
	printf("v0.2\n");
	dsp_init(&track_targets);
	track_targets_init(track_targets);
	
	printf("$$$$$$$$$$$ track_targets x = %x\n", track_targets->target_array[0].latest_x);
	printf("$$$$$$$$$$$ track_targets y = %x\n", track_targets->target_array[0].latest_y);
    dsp_process_main(track_targets);
	printf("$$$$$$$$$$$ track_targets filtration_x = %x\n", track_targets->target_array[0].filtration_x);
	printf("$$$$$$$$$$$ track_targets filtration_y = %x\n", track_targets->target_array[0].filtration_y);
	printf("$$$$$$$$$$$ track_targets prediction_x = %x\n", track_targets->target_array[0].prediction_x);
	printf("$$$$$$$$$$$ track_targets prediction_y = %x\n", track_targets->target_array[0].prediction_y);
	dsp_distroy(track_targets);
	return 0;
}





