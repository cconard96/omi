/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "sleep.h"

#if defined(CONFIG_POSIX)
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <sys/types.h>
#endif

PAL_Boolean PAL_Time(
    PAL_Uint64* self)
{
#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0) && defined(_POSIX_MONOTONIC_CLOCK) && (_POSIX_MONOTONIC_CLOCK > 0)

    struct timespec ts;
    memset( &ts, 0, sizeof(ts));

    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
        return PAL_FALSE;

    /* Seconds to microseconds plus nano seconds to microseconds */
    *self = ((PAL_Uint64)ts.tv_sec * (PAL_Uint64)1000000) + ((PAL_Uint64)ts.tv_nsec / (PAL_Uint64)1000);
    return PAL_TRUE;
#else
    struct timeval tv;
    struct timezone tz;
    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return PAL_FALSE;

    *self = (PAL_Uint64)tv.tv_sec * (PAL_Uint64)1000000 + (PAL_Uint64)tv.tv_usec;
    return PAL_TRUE;
#endif
}
