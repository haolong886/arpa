/* Include Files */
#include <xdc/std.h>
#include <string.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/xdais/dm/iuniversal.h>

/* Header Intrinsic to xdais algorithm*/
#include "C6Accel.h"

/* Application-Algorithm Interface file includes */
#include "iC6Accel_ti.h"
#include "iC6Accel_ti_priv.h"
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

void arpa_a_b_filter(int *a, int *b, unsigned size_a, unsigned size_b)
{
	ARPA_TRACK_TARGETS *track_targets_in = (ARPA_TRACK_TARGETS *)a;
	ARPA_TRACK_TARGETS *track_targets_out = (ARPA_TRACK_TARGETS *)b;
	track_targets_in->target_array[0].latest_x = 0xf;
	track_targets_in->target_num = 2;
	track_targets_in->target_array[0].filtration_x = 0xa;
	track_targets_in->target_array[0].filtration_y = 0xb;
	track_targets_in->target_array[0].prediction_x = 0xc;
	track_targets_in->target_array[0].prediction_y = 0xd;
}
