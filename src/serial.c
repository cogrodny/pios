
#include <stdio.h>


void serial_putc(int data) {
    char *ptr = 0x3F215040;
    *ptr = (char)data;

}
