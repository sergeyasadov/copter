#ifndef __COPTER_UTILS_H__
#define __COPTER_UTILS_H__

#define ARR_SIZE(__arr) (sizeof(__arr) / sizeof(__arr[0]))

#define ARR_FOREACH(__arr, __i) \
    for(uint_fast8_t __i = 0, __s = ARR_SIZE(__arr); __i < __s; __i++)

#endif // __COPTER_UTILS_H__