

char glbl[128];

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

void kernel_main() {

    extern int __bss_start, __bss_end;
    char *bssstart, *bssend;

    bssstart = &__bss_start;
    bssend = &__bss_end;

    unsigned long count = get_timer_count();    
    unsigned long wait_count = wait_timer();
    
    while(bssstart < bssend){
        *bssstart++ = 0;
    }
}
