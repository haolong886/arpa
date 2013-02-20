/* Standard includes */
#include <stdio.h>
#include <math.h>

/* Codec Engine and xdc includes */ 
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/osal/Memory.h>

/* system time include*/
#include <sys/time.h>
/* Include C6ACCEL headers */
#include "../c6accelw/c6accelw.h"

#include "appMain.h"

/* Define Engine ,algorithm and application names */
/* Pick engine name based on platform */
#if (PLATFORM == 3530)
 #define ENGINENAME "omap3530"
 #warning ENGINENAME "omap3530"
#elif (PLATFORM == 138)
 #define ENGINENAME "omapl138" 
 #warning ENGINENAME "omapl138"
 #define DEVICE_FLOAT  
#endif
#define ALGNAME "c6accel"
#define APPNAME "app"

/* Memory buffers used for test */
/*added by haolong for test arpa, 20130201*/
Int8 *pSrcbuf_arpa=NULL;
Int8 *pOutbuf_arpa=NULL;

/* Following vars/code are required by MACROs defined in benchmark.h*/
FILE* benchmarkFd;

/* Codec Engine engine and codec labels, defined in cfg file: */
static String algName      = ALGNAME;
static String engineName   = ENGINENAME;
static String progName     = APPNAME;

/* This object is used in MACRO in benchmark.h */
#include "timeObj.h"
Time_Object sTime;
UInt32      time;

void Time_reset(Time_Object *sTime)
{
 struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1) {
        return;
    }

    sTime->original = tv;
    sTime->previous = tv;

    return;
}

void Time_delta(Time_Object* sTime, UInt32 *deltaPtr)
{
    struct timeval tv;
    time_t         s;
    suseconds_t    us;

    if (gettimeofday(&tv, NULL) == -1) {
        return;
    }

    s = tv.tv_sec - sTime->previous.tv_sec;
    us = tv.tv_usec - sTime->previous.tv_usec;

    *deltaPtr = s * 1000000l + us;

    sTime->previous = tv;

    return;
}

/* Now include benchmark.h after it's supporting functions/vars are declared*/
#include "benchmark.h"

UInt32 arpa_buf_size_a, arpa_buf_size_b;
Memory_AllocParams memParams;
#define 	RESERVED_BUF_B 		1;
extern void CERuntime_init(void);
/*Define a C6Accel Handle to call the abstracted wrapper APIs*/
C6accel_Handle hC6 = NULL;

int dsp_init(ARPA_TRACK_TARGETS **track_targets)
{
	
    int i;
	memParams = Memory_DEFAULTPARAMS;
    /* This call must be made before the Memory_xxx() functions as it is required for the tracing functions
     in all the codec engine APIs that are used*/
    CERuntime_init();

    /* Reset timeObj used for benchmarking*/
    Time_reset(&sTime);

    /* Create call generates a C6ACCEL handle */
    hC6 = C6accel_create(engineName, NULL,algName, NULL);
	
    /*Check for failure*/
    if ( hC6 == NULL)
       {printf("%s: C6accel_create() failed \n",progName);
        goto end;
    }
   
    /* Create buffers for use by algorithms */

    /* Want to use cached & contiguous memory to get best performance from cortex when it also uses the buffers.*/
    memParams.flags = Memory_CACHED;
    memParams.type = Memory_CONTIGHEAP;

    /*added by haolong for test arpa, 20130201*/
    arpa_buf_size_a = sizeof(ARPA_TRACK_TARGETS);
    pSrcbuf_arpa = Memory_alloc(arpa_buf_size_a, &memParams);
    if (pSrcbuf_arpa == NULL) {
        goto end;
    }
    else {
       Memory_cacheWbInv(pSrcbuf_arpa, arpa_buf_size_a);
    }
    arpa_buf_size_b = arpa_buf_size_a;
    pOutbuf_arpa = Memory_alloc(arpa_buf_size_b, &memParams);
    if (pOutbuf_arpa == NULL) {
        goto end;
    }
    else {
       Memory_cacheWbInv(pOutbuf_arpa, arpa_buf_size_b);
    }
    /*----------------------------------------*/
    /* Create 16bit buffers for use by algorithms*/
    
    /* Set C6Accel instance for asynchronous call*/
    C6Accel_setSync(hC6);
    if (C6Accel_readCallType(hC6) == SYNC){
       printf("->  Synchronous Calls\n");
     }
     else 
       printf("->  Asynchronous Calls\n");

    /* open file for reporting benchmarking output*/
    OPEN_LOG_FILE("benchmarking.txt");
   
    /* Call test functions for kernels in C6accel*/
    LOG_STRING("IMGLib Functions\n");
    LOG_STRING("640x480 8bit/pixel b/w Test Image \n");
	
    memset(pOutbuf_arpa, 0x0, arpa_buf_size_a);
    memset(pSrcbuf_arpa, 0x0, arpa_buf_size_b);
	*track_targets = pSrcbuf_arpa;
	return 0;
	
end:
	if(pSrcbuf_arpa)
		Memory_free(pSrcbuf_arpa, arpa_buf_size_a, &memParams);
	if(pOutbuf_arpa)
		Memory_free(pOutbuf_arpa, arpa_buf_size_b, &memParams);
	return -1;
}

void dsp_distroy(ARPA_TRACK_TARGETS *track_targets)
{
	
	if(pSrcbuf_arpa)
		Memory_free(pSrcbuf_arpa, arpa_buf_size_a, &memParams);
	if(pOutbuf_arpa)
		Memory_free(pOutbuf_arpa, arpa_buf_size_b, &memParams);
     // Tear down C6ACCEL
    if (hC6)
       C6accel_delete(hC6);
}

int dsp_process_main(ARPA_TRACK_TARGETS *track_targets)
{
    int status;
	ARPA_TRACK_TARGETS *out = (ARPA_TRACK_TARGETS *)pOutbuf_arpa;
    status = C6accel_DSPF_arpa_a_b_filter(hC6, (int *)pSrcbuf_arpa, (int *)pOutbuf_arpa, arpa_buf_size_a, arpa_buf_size_b);
	if(status !=0)
		return -1;
	return (0);
}

