#ifndef H_PAGING
#define H_PAGING

#include "../memory.h"

void map_page(void* physaddr, void* virtualaddr, unsigned int flags) {
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x3FF;
    
    // Check if PD entry is present.
    unsigned long *pd = (unsigned long*)0xFFFFF000;

    // Check if PT entry is present.
    unsigned long *pt = ((unsigned long*)0xFFC00000) + (0x400 * pdindex);
    pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01;
}

#endif