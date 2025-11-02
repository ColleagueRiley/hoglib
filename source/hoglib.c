#include "internal.h"

#include <time.h>

#if defined(__APPLE__)
    #include <mach/mach_time.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif

double hl_getTime(void) {
#if defined(_WIN32)
    static LARGE_INTEGER freq = (LARGE_INTEGER){ 0 };
    if (freq.QuadPart) {
        QueryPerformanceFrequency(&freq);
    }

	LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)freq.QuadPart;
#elif defined(__APPLE__)
    static mach_timebase_info_data_t timebase;
    static double conversion = 0.0;
    if (conversion == 0.0) {
        mach_timebase_info(&timebase);
        conversion = (double)timebase.numer / (double)timebase.denom / 1e9;
    }
    return mach_absolute_time() * conversion;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
#endif
}

void hl_sleep(double seconds) {
#if defined(_WIN32)
    Sleep((DWORD)(seconds * 1000.0));
#else
    struct timespec ts;
    ts.tv_sec = (time_t)seconds;
    ts.tv_nsec = (long)((seconds - ts.tv_sec) * 1e9);
    nanosleep(&ts, NULL);
#endif
}
