//g++ -std=c++11 -pthread ../src/pthread_Mutex.cpp ../stopwatch.o -o pthread_Mutexll


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../include/stopwatch.h"

using namespace std; 

#define NUM_THREADS 4
#define BILLION  1000000000L
//pthread_attr_t attr; 

typedef struct {
	int count; 
	//int primes[1000]; 
	int primeCount; 
} PRIME;
struct thread_data {
	int thread_id;
	int sum; 
	char *message; 
};
struct thread_data thread_data_array[NUM_THREADS];

PRIME p; 
pthread_t callThd[NUM_THREADS]; 
pthread_mutex_t mutexp; 

void *MessagePrinter(void *arg) {
	int i; 
	int prime;
	int num; 
	struct thread_data *td;
	td = (struct thread_data *) arg;

	while(p.primeCount<1000) { 
		pthread_mutex_lock (&mutexp); 
		num = p.count; 
		p.count++;
		pthread_mutex_unlock (&mutexp);
		
		i=2; 
		prime = 1; 
		while(i<num && prime==1) {
			if (num%i==0)
				prime=0; 
			i++; 
		}
		if(prime==1) {
			pthread_mutex_lock (&mutexp);
			//p.primes[p.primeCount] = num;
			p.primeCount++; 
			td->sum++; 
			pthread_mutex_unlock (&mutexp); 
			printf("Thread: %d (%d) Index: %d  Prime: %d \n", 
				td->thread_id, td->sum, p.primeCount-1, num); 
		}
		
	}

	pthread_exit((void*) 0); 

}

int main(int argc, char *argv[]) {
	long i;
	void *status; 	
	size_t stacksize;
	
	// Timer
	stopwatch sw;   

	pthread_attr_t attr; 
	pthread_mutex_init(&mutexp, NULL); 
	pthread_attr_init(&attr);  
	pthread_attr_getstacksize (&attr, &stacksize);
	printf("Default Stack Size %li \n", stacksize);
	pthread_attr_setstacksize (&attr, stacksize*100);
	printf("New Stack Size %li \n", stacksize*100); 
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
	p.count=2; 

	// Start timer. 
	sw.start(); 

	for (i=0; i<NUM_THREADS; i++) {
		thread_data_array[i].thread_id = i; 
		thread_data_array[i].sum = 0; 
		pthread_create(&callThd[i], &attr, MessagePrinter, (void *) &thread_data_array[i]); 
	}

	pthread_attr_destroy(&attr); 

	for (i=0; i<NUM_THREADS; i++) {
		pthread_join(callThd[i], &status); 
	}

	pthread_mutex_destroy(&mutexp);

	// Stop timer and print. 
  sw.stop(); 
	sw.print(); 
  

	printf("New Stack Size %li \n", stacksize*100);
 

	//for(i=0; i<100; i++) {
		//printf("%d \n", p.primes[i]); 
	//}
 
	pthread_exit(NULL); 
}
