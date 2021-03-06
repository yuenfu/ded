#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint16_t signature;
    uint16_t bytes_in_last_block;
    uint16_t blocks_in_file;
    uint16_t num_relocs;
    uint16_t header_paragraphs;
    uint16_t min_extra_paragraphs;
    uint16_t max_extra_paragraphs;
    uint16_t ss;
    uint16_t sp;
    uint16_t checksum;
    uint16_t ip;
    uint16_t cs;
    uint16_t reloc_table_offset;
    uint16_t overlay_number;
} __attribute__((packed, aligned(1))) MZ_Hdr;

typedef struct {
    uint16_t offset;
    uint16_t segment;
} MZ_Reloc;

typedef struct node {
    uint64_t value;
    bool visited;
    bool is_proc;
    struct node *next;
} list;

typedef enum {
    CALL_ADDR = 0,
    JUMP_ADDR,
} addr_type;

// Functions
MZ_Hdr *read_mz_header(FILE *fd);
uint64_t get_entry(MZ_Hdr *mz_hdr);
size_t get_exe_size(MZ_Hdr *mz_hdr);
void disp_header(MZ_Hdr *mz_hdr);

list *search_addr(uint64_t addr, size_t size, uint8_t *buffer, addr_type mode);
void rt_disasm(uint64_t entry, uint64_t addr, size_t size, uint8_t *buffer, list *call, list *jump);
void ls_disasm(uint64_t addr, size_t size, uint8_t *buffer);

void list_free(list *node);

#endif // CORE_H
