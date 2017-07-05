/* @TAG(DATA61_BSD) */

#include <camkes.h>
#include <stddef.h>
#include <stdint.h>

extern char *morecore_area;
extern size_t morecore_size;

int run(void) {
    m_morecore_range((uintptr_t)morecore_area, morecore_size);
    return 0;
}
