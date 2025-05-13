#include "LA_sup.h"

#ifdef __cplusplus
extern "C"
{
#endif

void __cdecl _swap_u(void *v1, void *v2, size_t size)
{
    if (!v1 || !v2 || !size || v1 == v2)
        return;

    char tmp[size];
    memcpy(tmp, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, tmp, size);
}

#ifdef __cplusplus
}
#endif
