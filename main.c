#include "main.h"

/********************************************************************
 Main
********************************************************************/
int main (int argc, char *argv[]){
	int 		rc;
	int			scope,i;
	double 		stop_1 = 0;

  struct timespec finish_time = {0, 0};
  struct timespec thread_dt   = {0, 0};

	abortTest_10  = 0;
	abortTest_20  = 0;
	seqIterations = FIB_LIMIT_FOR_32_BIT;

	start_time.tv_sec = 0;//    = {0,0};
	start_time.tv_nsec = 0;

	useconds_t 	t_10 = TIME_10_MSEC;
	useconds_t	t_20 = TIME_10_MSEC*2;

	sem_init (& sem_t10, 0, 1 );
	sem_init (& sem_t20, 0, 1 );

	printf("Before adjustments to scheduling policy:\n");
	print_scheduler();

	pthread_attr_init(&rt10_sched_attr);
	pthread_attr_init(&rt20_sched_attr);
	pthread_attr_init(&main_sched_attr);

	pthread_attr_setinheritsched(&rt10_sched_attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(&rt20_sched_attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(&main_sched_attr, PTHREAD_EXPLICIT_SCHED);

	pthread_attr_setschedpolicy(&rt10_sched_attr, SCHED_FIFO);
	pthread_attr_setschedpolicy(&rt20_sched_attr, SCHED_FIFO);
	pthread_attr_setschedpolicy(&main_sched_attr, SCHED_FIFO);

	rt_max_prio = sched_get_priority_max(SCHED_FIFO);
	rt_min_prio = sched_get_priority_min(SCHED_FIFO);

	rc=sched_getparam(getpid(), &nrt_param);

	//Large priority = Highest priority
	main_param.sched_priority = rt_max_prio;		// set 99
	rt10_param.sched_priority = rt_max_prio-1;		// set 98
	rt20_param.sched_priority = rt_max_prio-2;		// set 97

	if (sched_setscheduler(getpid(), SCHED_FIFO, &main_param)){
		printf("ERROR; sched_setscheduler rc is %d\n", rc); perror(NULL); exit(-1);
	}

	printf("After adjustments to scheduling policy:\n");
	print_scheduler();
	printf("min prio = %d, max prio = %d\n", rt_min_prio, rt_max_prio);
	pthread_attr_getscope(&rt10_sched_attr, &scope);

	pthread_attr_setschedparam(&rt10_sched_attr, &rt10_param);
	pthread_attr_setschedparam(&rt20_sched_attr, &rt20_param);
	pthread_attr_setschedparam(&main_sched_attr, &main_param);

	clock_gettime(CLOCK_REALTIME, &start_time);

	if (pthread_create (& testThread10, & rt10_sched_attr, Thread10 , ( void *)0 )){ 	//Error if not created
		printf("ERROR during pthread_create() for Thread10\n"); 
		perror(NULL); 
		exit(-1);
	}
	sem_wait (& sem_t10 );	

	if (pthread_create (& testThread20, & rt20_sched_attr, Thread20 , ( void *)0 )){	//Error if not created
		printf("ERROR during pthread_create() for Thread20\n"); 
		perror(NULL); 
		exit(-1);
	}
	sem_wait (& sem_t20 );	

	/* Basic sequence of releases after CI */
	sem_post (& sem_t10 );
	sem_post (& sem_t20 );
	usleep( t_20 );
	sem_post (& sem_t10 );
	usleep( t_20 );
	sem_post (& sem_t10 );
	usleep( t_10 );
	abortTest_20 = 1;
	sem_post (& sem_t20 );
	usleep( t_10 );
	sem_post (& sem_t10 );
	usleep( t_20 );
	abortTest_10 = 1;
	sem_post (& sem_t10 );
	usleep( t_20 );

	clock_gettime(CLOCK_REALTIME, &finish_time);
	delta_t(&finish_time, &start_time, &thread_dt);

	printf("Test Conducted over %lf msec\n",((double)thread_dt.tv_nsec /(double)NSEC_PER_MSEC));
	pthread_join( testThread10, NULL );
	pthread_join( testThread20, NULL );
	if(pthread_attr_destroy(&rt10_sched_attr) != 0)
	perror("attr destroy");
	if(pthread_attr_destroy(&rt20_sched_attr) != 0)
	perror("attr destroy");
	sem_destroy(&sem_t10);
	sem_destroy(&sem_t20);
	rc=sched_setscheduler(getpid(), SCHED_OTHER, &nrt_param);
	printf("TEST COMPLETE\n");

  return 0;

}
