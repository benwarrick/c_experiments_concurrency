cmake_minimum_required(VERSION 3.5)
project(experiment)
set (CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

include_directories(include)
file(GLOB SOURCES "src/*.cpp") 
add_executable(pthread_Mutex ${SOURCES})

#set (CMAKE_LINK_SHARED_FLAGS "-pthread") 

# I've tried this one by itself 
target_link_libraries(pthread_Mutex Threads::Threads)


#if(THREADS_HAVE_PTHREAD_ARG)
#  target_compile_options(pthread_Mutex PUBLIC "-pthread")
#endif()
#if(CMAKE_THREAD_LIBS_INIT)
#  target_link_libraries(pthread_Mutex "${CMAKE_THREAD_LIBS_INIT}")
#endif()

#target_link_libraries(pthread_Mutex pthread) 
