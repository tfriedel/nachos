#include "utility.h"

//----------------------------------------------------------------------
// CopyStr
//      Make a copy of a string on the heap.
//----------------------------------------------------------------------

char* CopyStr(char *src) {  // makes a copy of a string on the heap
        int len = strlen(src);
        char *dest = new char[len + 1];
        memcpy(dest, src, len + 1);
        return dest;
}

//----------------------------------------------------------------------
// getRealTicks
//      returns ticks in milliseconds using the time of the OS nachos 
//      is running in
//      can be used to measure time more exactly than nachos system ticks
//----------------------------------------------------------------------

#include <sys/time.h>

long secondsAtStart = 0;
long millisAtStart = 0;

long getRealTicks() {
    
    timeval tv;
    gettimeofday(&tv, NULL);
    
    if (secondsAtStart == 0) {
        secondsAtStart = tv.tv_sec;
        millisAtStart = tv.tv_usec / 1000;
    }
    
    return (tv.tv_sec - secondsAtStart) * 1000 + (tv.tv_usec/1000 - millisAtStart);
    
}

#ifdef CYGWIN

    void millisleep(long time) {
        if (time > 0) {
            timespec ts;
            ts.tv_sec = time / 1000;
            ts.tv_nsec = (time % 1000) * 1000000;
            nanosleep(&ts, NULL);    
        }
    }
        
#else
    
    void millisleep(long time) {
        int rfd = 0, wfd = 0, xfd = 0;
        int retVal;
        struct timeval pollTime;
        pollTime.tv_sec = time / 1000;
        pollTime.tv_usec = (time % 1000) * 1000;
        retVal = select(32, (fd_set*)&rfd, (fd_set*)&wfd, (fd_set*)&xfd, &pollTime);
    }
    
#endif

