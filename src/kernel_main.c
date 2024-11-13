//Clearbss completed
//systimer completed
//comment test VM

//This part is completed and should work :)

#include "serial.h"
#include "page.h"
#include "mmu.h"
#include "fat.h"

/*char glbl[128];

unsigned char global_variable;

char huge_array[8192];

int milliseconds = 1000;

unsigned long get_timer_count() {
    unsigned long *timer_count_register = 0x3f003004;
    return *timer_count_register;
}

int wait_timer() {
    unsigned long count = get_timer_count();
    unsigned long wait_count = count + (milliseconds * 1000);
    return wait_count;
}

void setGlobalValue() {
    global_variable = 0x12345678;
}

int getEL() {
    return 1;
}*/

//extern struct table_descriptor_stage1 L1table[512];

void kernel_main() {
    
    //extern int __bss_start, __bss_end;
    //char *bssstart, *bssend;

    //bssstart = &__bss_start;
    //bssend = &__bss_end;
    
    //char *begin_bss = &__bss_start;
    //char *end_bss = &__bss_end;

    //mapPages((void *)0x00000000, (void *)0x00000000);
    
    //loadPageTable(L1table);	

    //char* test = 0x800000;
    //*test = 1;

    //esp_printf(putc, "Current Execution Level is %d\r\n", getEL());

    //struct ppage *allocated_pages = allocate_physical_pages(4); 
    //struct ppage *more_allocated_pages = allocate_physical_pages(2);
    //free_physical_pages(allocated_pages);
    
    //for (char *ptr = bssstart; ptr < bssend; ptr++) {
        //*ptr = 0x0;
    //}

    //unsigned long count = get_timer_count();    
    //unsigned long wait_count = wait_timer();
    
    char buf[1024];
    int n = 1024;

    fatOpen("TESTFILETXT");
    fatRead(buf, n, fileOpen("TESTFILETXT"));    

}
