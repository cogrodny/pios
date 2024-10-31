//fat.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fat.h"
#include "sd.h" // See this file for function prototype of ata_lba_read()

#define SECTOR_SIZE 512

struct boot_sector *bs;
char bootSector[512]; // Allocate a global array to store boot sector
char fat_table[8*SECTOR_SIZE];
unsigned int root_sector;
char rde_region[2048];

int fatInit() {
    sd_readblock(0, bootSector, 1); // Read sector 0 from disk drive into bootSector array
    bs = bootSector; // Point boot_sector struct to the boot sector so we can read fields
    // Print out some of the elements of the BIOS information block using rprintf...
    printf("bytes per sector = %d\n", bs->bytes_per_sector);
    printf("sectors per cluster = %d\n", bs->num_sectors_per_cluster);
    printf("reserved sectors = %d\n", bs->num_reserved_sectors);
    printf("number of FATs = %d\n", bs->num_fat_tables);
    printf("number of RDEs = %d\n", bs->num_root_dir_entries);

    // TODO: Validate the boot signature = 0xaa55
    if (bs->boot_signature != 0xAA55) {
        return -1;
    }

    // TODO: Validate fs_type = "FAT12" using strcmp
    if (strcmp(bs->fs_type, "FAT12")) {
        return -1;
    }

    // TODO: Read FAT table from the SD card into array fat_table
    sd_readblock(bs->num_reserved_sectors, fat_table, bs->num_sectors_per_fat);

    // TODO: Compute root_sector as:
    // num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors
    root_sector = (bs->num_fat_tables + bs->num_sectors_per_fat + bs->num_reserved_sectors + bs->num_hidden_sectors);
    return 0;
}


int fileOpen(char *file_name) {
    struct root_directory_entry *rde = (struct root_directory_entry*)rde_region;
    readSector(root_sector, rde_region);

    //change title to uppercase
    char upper_file_name[15];
    strncpy(upper_file_name, file_name, 15);
    for (int i = 0; i < 14; i++) {
	    upper_file_name[i] = toupper(upper_file_name[i]);
    }
    //itterate through rde
    for(int k = 0; k < bs->num_root_dir_entries; k++) {
	if (strncmp(rde[k].file_name, upper_file_name, 11) == 0) {
            return k;
	}
    }
    return -1;
}

int fatRead(char *buf, int num_bytes_to_read, int rde_index) {
    struct root_directory_entry *rde = (struct root_directory_entry*)rde_region;
    int read_cluster = rde[rde_index].cluster;
    int bytes_read = 0;

    //while bytes_read is less than num_bytes_to_read
    while(bytes_read < num_bytes_to_read) {
	sd_readblock(root_sector + read_cluster, buf + bytes_read, 1);
	read_cluster = fat_table[read_cluster];
	bytes_read += bs->bytes_per_sector;
    }
    return bytes_read;
}
