#ifndef ASSERTS_H
#define ASSERTS_H

#define STATIC_ASSERT(condition) \
    static char __static_assert_##condition[(condition) ? (1) : (-1)]


#endif //ASSERTS_H
