#ifndef H_MEMORY
#define H_MEMORY

enum memory_address {
    VGA_ADDR = 0xb8000,
};

static inline void __native_flush_tlb_single(unsigned long addr) {
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

void* get_physaddr(void* virtualaddr) {
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x3FF;

    // Check if PD entry is present.
    unsigned long *pd = (unsigned long*)0xFFFFF000;

    // Check if PT entry is present.
    unsigned long *pt = ((unsigned long*)0xFFC00000) + (0x400 * pdindex);

    return (void *)((pt[ptindex] & ~0xFFF) + ((unsigned long)virtualaddr & 0xFFF));
}

#endif