#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "stopwatch.h"

using namespace std; 

struct timespec startSpec, stopSpec, acum, tu; 

stopwatch::stopwatch() {
  startSpec = {0,0}; 
	stopSpec = {0,0};
	acum = {0,0};    
}
void stopwatch::start() {
	if( clock_gettime( CLOCK_REALTIME, &startSpec) == -1 ) {
  		perror( "clock gettime" );
  		exit( EXIT_FAILURE );
  	}
}
void stopwatch::stop() {
	if (stopSpec.tv_nsec > 0) {	
		if( clock_gettime( CLOCK_REALTIME, &stopSpec) == -1 ) {
    	perror( "clock gettime" );
    	exit( EXIT_FAILURE );
  	}
		acum.tv_sec = acum.tv_sec + stopSpec.tv_sec-startSpec.tv_sec;
		acum.tv_nsec = acum.tv_nsec + stopSpec.tv_nsec-startSpec.tv_nsec;
		clear();
	} 
}

void stopwatch::getTime(timespec &t) {
	if (startSpec.tv_nsec > 0) {		
		if( clock_gettime( CLOCK_REALTIME, &stopSpec) == -1 ) {
		  perror( "clock gettime" );
		  exit( EXIT_FAILURE );
		}	
		t.tv_sec = acum.tv_sec + stopSpec.tv_sec-startSpec.tv_sec;
		t.tv_nsec = acum.tv_nsec + stopSpec.tv_nsec-startSpec.tv_nsec; 
	}
	else {
		t.tv_sec = acum.tv_sec; 
		t.tv_nsec = acum.tv_nsec;  
	}
}

string stopwatch::getTimeString() {
	getTime(tu); 
	return to_string(tu.tv_sec) + ":" + to_string(tu.tv_nsec);
}
void stopwatch::clear() {
  startSpec = {0,0}; 
	stopSpec = {0,0};
}
void stopwatch::print() {
	cout << this->getTimeString() << endl;
}
