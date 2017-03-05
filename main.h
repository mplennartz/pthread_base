#ifndef MAIN_H
#define MAIN_H

  // INCLUDED HEADER FILES
  #include <pthread.h>
  #include <semaphore.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <sched.h>
  #include <unistd.h>
  #include <time.h>
  #include <syslog.h>
  #include <math.h>
  #include <sys/param.h>


  // DEFINED VARIABLES
  #define FIB_LIMIT_FOR_32_BIT 10
  #define REQ_INTER 2000000
  #define TIME_10_MSEC 10000

  #define NSEC_PER_SEC (1000000000)
  #define NSEC_PER_MSEC (1000000)
  #define NSEC_PER_MICROSEC (1000)

  /********************************************************************
   Variable Declarations
  ********************************************************************/
  pthread_t 		  testThread10;
  pthread_t 		  testThread20;
  pthread_attr_t  rt10_sched_attr;
  pthread_attr_t 	rt20_sched_attr;
  pthread_attr_t 	main_sched_attr;
  sem_t 			    sem_t10;
  sem_t			      sem_t20;
  int 			      rt_max_prio;
  int				      rt_min_prio;
  int				      min;
//  double 			    start_1       = 0;
  int				      abortTest_10;//  = 0;
  int				      abortTest_20;//  = 0;
  int 			      seqIterations;// = FIB_LIMIT_FOR_32_BIT;

  struct timespec    start_time;//    = {0, 0};

  struct sched_param rt10_param;
  struct sched_param rt20_param;
  struct sched_param nrt_param;
  struct sched_param main_param;

  /********************************************************************
   Fibonaci Delay
     Needs improved
  ********************************************************************/
  #define FIB_TEST(seqCnt, iterCnt)      \
     for(idx=0; idx < iterCnt; idx++)    \
     {                                   \
        fib = fib0 + fib1;               \
        while(jdx < seqCnt)              \
        {                                \
           fib0 = fib1;                  \
           fib1 = fib;                   \
           fib = fib0 + fib1;            \
           jdx++;                        \
        }                                \
     }                                   \

// PTHREAD DEFINITIONS
  void  *Thread10 ( void* );                      // address space to thread_id
  void  *Thread20 ( void* );                      // address space to thread_id

// FUNCTION DEFINITIONS
  int   delta_t         ( struct timespec*,       // stop time
                          struct timespec*,       // start time
                          struct timespec*  );    // time diff
  void  print_scheduler ( void              );    // N/A

#endif


















