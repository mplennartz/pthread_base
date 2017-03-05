/* 
 * Author: Nisheeth 	Created on: Apr 4, 2011
 * Update: Lennartz		Updated on: Feb 6, 2017
 *
 *   Updated using methodologies used in prior assignements.
 * Removed custom functions for calculated time and used
 * clock_gettime functions and the previously defined 
 * delta_t function.
 */
#include "main.h"

/********************************************************************
 Thread10
********************************************************************/
void *Thread10(void *threadid){
  struct sched_param param;
  struct timespec finish_time = {0, 0};
  struct timespec thread_dt   = {0, 0};
	int policy;
	int idx = 0, jdx = 1, fib = 0, fib0 = 0, fib1 = 1;
	unsigned long mask = 1; /* processor 0 */


	while (!abortTest_10){
		sem_wait (& sem_t10 );
		FIB_TEST(seqIterations, REQ_INTER);
		clock_gettime(CLOCK_REALTIME, &finish_time);
		pthread_getschedparam(testThread10,&policy ,&param);
		delta_t(&finish_time, &start_time, &thread_dt);
		printf("Thread10 priority = %d and time stamp %lf msec\n",
            param.sched_priority,
            ((double)thread_dt.tv_nsec /(double)NSEC_PER_MSEC)
          );
	}

}

/********************************************************************
 Thread20
********************************************************************/
void *Thread20(void *threadid){
	struct sched_param param;
  struct timespec finish_time = {0, 0};
  struct timespec thread_dt   = {0, 0};
	int policy;
	int idx = 0, jdx = 1, fib = 0, fib0 = 0, fib1 = 1;
	unsigned long mask = 1; /* processor 0 */

	while (!abortTest_20){
		sem_wait (& sem_t20 );
		FIB_TEST(seqIterations*3, REQ_INTER*3);
		clock_gettime(CLOCK_REALTIME, &finish_time);
		pthread_getschedparam(testThread20,&policy ,&param);
		delta_t(&finish_time, &start_time, &thread_dt);
		printf("Thread20 priority = %d and time stamp %lf msec\n",
            param.sched_priority,
            ((double)thread_dt.tv_nsec /(double)NSEC_PER_MSEC)
          );
	}
}

