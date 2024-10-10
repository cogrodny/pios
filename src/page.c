//page.c

#include "page.h"
#include <stddef.h>
#include <stdint.h>

struct ppage physical_page_array[128]; //256MB of memory split into 128 pages of 2MB each 
struct ppage *free_physical_pages = NULL; 
extern uint32_t endkernel;

void init_pfa_list(void) { //init_pfa_list method
    for (int i = 0; i < 128; i++) {
        physical_page_array[i].physical_addr = (void *)(i * 0x200000);

        if (i == 0) {
            physical_page_array[i].prev = NULL;  
            physical_page_array[i].next = &physical_page_array[i + 1];
        } else if (i == 127) {
            physical_page_array[i].next = NULL;
            physical_page_array[i].prev = &physical_page_array[i - 1]; 
        } else {
            physical_page_array[i].next = &physical_page_array[i + 1]; 
            physical_page_array[i].prev = &physical_page_array[i - 1];  
        }
    }

    free_physical_pages = &physical_page_array[0];
}

struct ppage *allocate_physical_pages(unsigned int npages) { //allocate_physical_pages method
    struct ppage *allocd_list = free_physical_pages; 
    struct ppage *temp = free_physical_pages;

    for (unsigned int i = 0; i < npages; i++) {
        free_physical_pages = temp->next;
        temp->next = NULL;  
        temp = free_physical_pages;
    }

    return allocd_list; 
}

void be_free_physical_pages(struct ppage *ppage_list) { //be_free_physical_pages method, name changed as instructed by professor
    struct ppage *temp = ppage_list;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = free_physical_pages;
    free_physical_pages->prev = temp;

    free_physical_pages = ppage_list;
}

