#ifndef STOPWATCH_H_
#define STOPWATCH_H_
#include <string>

class stopwatch {
	public:
		void stop();
		void start(); 
		std::string getTimeString(); 
		void getTime(timespec &t); 
		stopwatch();
		void clear(); 
		void print();   

	private: 
		struct timespec startSpec, stopSpec;
};
#endif
