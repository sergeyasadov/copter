#ifndef ASSERTS_H
#define ASSERTS_H

#if defined(__cplusplus)
#define STATIC_ASSERT(condition) static_assert((condition), #condition)
#elif __STDC_VERSION__ >= 201112L
#define STATIC_ASSERT(condition) _Static_assert((condition), #condition)
#else
#define STATIC_ASSERT(condition) \
    extern char (*STATIC_ASSERTS_CHECK)[(condition) ? (1) : (-1)]

#endif

#endif //ASSERTS_H
