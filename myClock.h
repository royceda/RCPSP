/* 
 * File:   myClock.h
 * Author: yoannjvr
 *
 * Created on 22 octobre 2015, 19:58
 */
#include <sys/time.h>

#ifndef MYCLOCK_H
#define	MYCLOCK_H

class MyClock {
public:

    MyClock() {
    }

    ~MyClock() {
    }

    void start() {
        gettimeofday(&_beginTimeVal, &_timeZone);
    }

    void end() {
        gettimeofday(&_endTimeVal, &_timeZone);
    }

    double elapsedTime() {
        return (_endTimeVal.tv_sec - _beginTimeVal.tv_sec) + 
           (_endTimeVal.tv_usec - _beginTimeVal.tv_usec) * 1e-6;
    }

private:
    struct timeval _beginTimeVal;
    struct timeval _endTimeVal;
    struct timezone _timeZone;
};


#endif	/* MYCLOCK_H */

