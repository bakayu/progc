#include <stdint.h>
#include <stdio.h>

void address_translation(uint32_t virtual_address) {
    uint32_t page_number = 0;
    uint32_t offset = 0;

    page_number = virtual_address >> 12;
    offset = virtual_address & 0xFFF;

    printf("[1A] Addr: 0x%08X -> Page: %u (0x%X), Offset: %u (0x%X)\n",
           virtual_address, page_number, page_number, offset, offset);
}

int main(void) {
    int test_cases[] = {0x00000000, 0x00000FFF, 0x00001000, 0x00003A2C};

    for (int i = 0; i < 4; i++)
        address_translation(test_cases[i]);
    return 0;
}
