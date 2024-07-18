#ifndef WFI_H
#define WFI_H

static inline void wfi(void)
{
    __asm__ volatile("wfi");
}

#endif /* WFI_H */
