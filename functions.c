#include "main.h"

/********************************************************************
 DELTA_T Function Definitions
********************************************************************/
int delta_t(  struct timespec *stop, 
              struct timespec *start, 
              struct timespec *delta_t  )
{
  int dt_sec=stop->tv_sec - start->tv_sec;
  int dt_nsec=stop->tv_nsec - start->tv_nsec;

  if(dt_sec >= 0){
    if(dt_nsec >= 0){
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }else{
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }else{
    if(dt_nsec >= 0){
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }else{
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }

  return(1);
}

/********************************************************************
 Simply prints the current POSIX scheduling policy in effect.
********************************************************************/
void print_scheduler(void)
{
	int schedType;
	schedType = sched_getscheduler(getpid());

	switch(schedType){
		case SCHED_FIFO:
			printf("Pthread Policy is SCHED_FIFO\n");
			break;
		case SCHED_OTHER:
			printf("Pthread Policy is SCHED_OTHER\n");
			break;
		case SCHED_RR:
			printf("Pthread Policy is SCHED_OTHER\n");
			break;
		default:
			printf("Pthread Policy is UNKNOWN\n");
	}
}


