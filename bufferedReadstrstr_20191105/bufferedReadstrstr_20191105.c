#include <stdio.h>
#include <stdlib.h>

const char eeprom[] = "BEIOXSDYWUUBVXOSCSCBAAAAWKVLNJVHMPPPRSVJABCQOSMRHMXUQHMWAPLUEXGYJOWSJMNUQAXYDRLYXPJFNMACVADACAQOSGPSWSJKMIEIIJILCYWOLZGBGTBPWXIZICWZILJJIQGEEDJFKDRKQVOUZSVDKLXCXWZBQZZFPEVRLWMIVKUDPTPJNIPSEETNTIELEAUEIPCNHQMGIYWZOYRLYMTABHTYRMEZFASRLBQOTNBJREQVDJAMLTTCJJKKHUSHPXUYLFFUVXSNARACJWFNFJBCEPFYQTZVJAZJDBOLKNRXQGBRGNSVEVWDSZJBJBZYTTQYPIVRTXZNLSJJHJIEMIXIGEKJIIKXJQPXYEPCXENYYGCXNVIFAOALHEZIECWWUWXRZTFZSLXVXYHZGSFFOBCHHQVPJTCGNVSKHCBVTQBGLAOJFVUHBLFHILOEZIACDJQFBLGYAKLMAHIJICADVHJYPAYBPPAMGORREPSMRCJGATRONXOTWYDJMPPT";


// const char eeprom[] = "MPPTXSDYWUUBVXOSCSCBWKVLNJVHBCOMPPTRSVJQOSMAGYYRHMXUQHMWAPLUEXGYJOWSJMNUQAXYDRLYXPJFNMACVADACAQOSGPSWSJKMIEIIJILCYWOLZGBGTBPWXIZICWZILJJIQGEEDJFKDRKQVOUZSVDKLXCXWZBQZZFPEVRLWMIVKUDPTPJNIPSEETNTIELEAUEIPCNHQMGIYWZOYRLYMTABHTYRMEZFASRLBQOTNBJREQVDJAMLTTCJJKKHUSHPXUYLFFUVXSNARACJWFNFJBCEPFYQTZVJAZJDBOLKNRXQGBRGNSVEVWDSZJBJBZYTTQYPIVRTXZNLSJJHJIEMIXIGEKJIIKXJQPXYEPCXENYYGCXNVIFAOALHEZIECWWUWXRZTFZSLXVXYHZGSFFOBCHHQVPJTCGNVSKHCBVTQBGLAOJFVUHBLFHILOEZIACDJQFBLGYAKLMAHIJICADVHJYPAYBPPAMGORREPSMRCJGATRONXOTWYDJWVJB";
#define EEPROM_LENGTH_BYTES 512

const char pattern[] = "MPPT";
#define PATTERN_LENGTH_BYTES 4

#define MAX_READ_LENGTH_BYTES 32

void read_eeprom_bytes(char * dest, const int start_address, const int num_bytes_to_read)
{
    const char * local_eeprom_ptr = eeprom + start_address;
    int local_num_bytes_to_read = (num_bytes_to_read > MAX_READ_LENGTH_BYTES) ? MAX_READ_LENGTH_BYTES : num_bytes_to_read;
    const int end_address = start_address + local_num_bytes_to_read;

    if (end_address > EEPROM_LENGTH_BYTES)
    {
        printf("Out-of-bounds read attempted at address [%d-%d]\n", start_address, end_address);
        abort();
    }

    while (local_num_bytes_to_read)
    {
        *(dest++) = *(local_eeprom_ptr++);
        local_num_bytes_to_read--;
    }
}

/**
   32
 |--------|
      ^
       ^
       read
       |-------

        startIdx = 4       |----------------------|
        0 1 2 3 4  .... 28 29 30 31     57 58 59 60 61
        ^                  ^
                                           ^---^
        startIdx = 29
     i = 30
     i = 58
     29 + 32 - 4 = 57 => 58
*/

int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

int find_first_occurrence_of_pattern_kmp(void) {
    char next[PATTERN_LENGTH_BYTES+1] = {0};
    next[0] = -1;
    int j = -1;
    for (int i = 0; i < PATTERN_LENGTH_BYTES; i++) {
        while (j >= 0 && pattern[j] != pattern[i]) {
            j = next[j];
        }
        j++;
        next[i+1] = j;
    }
    char buf[MAX_READ_LENGTH_BYTES];
    int startIdx = -1; // indicating buf is cache from which what startaddress
    j = 0;
    for (int i = 0; i < EEPROM_LENGTH_BYTES; i++) {
        if (startIdx == -1 || i - startIdx >= MAX_READ_LENGTH_BYTES) {
            read_eeprom_bytes(&buf[0], i, min(MAX_READ_LENGTH_BYTES, EEPROM_LENGTH_BYTES - i));
            startIdx = i;
        }
        while (j >= 0 && buf[i - startIdx] != pattern[j]) {
            j = next[j];
        }
        j++;
        if (j == PATTERN_LENGTH_BYTES) {
            return i - PATTERN_LENGTH_BYTES + 1;
        }
    }
    return -1;
}

int find_first_occurrence_of_pattern(void)
{
    /* TODO */
    char buf[32];
    int startIdx = 0; // indicating this read from which start addreess from EPROM
    read_eeprom_bytes(&buf[0], 0, min(MAX_READ_LENGTH_BYTES, EEPROM_LENGTH_BYTES - 0));
    for (int i = 0; i + PATTERN_LENGTH_BYTES - 1 < EEPROM_LENGTH_BYTES; i++) {
  // for (int i = 0; i + PATTERN_LENGTH_BYTES - 1 < 8; i++) {
      if (i > startIdx + MAX_READ_LENGTH_BYTES - PATTERN_LENGTH_BYTES) {
        // min(MAX_READ_LENGTH_BYTES, remain)
        // remain = EEPROM_LENGTH_BYTES - i
        // 493 + 32 - 1
        // 512 - 493 = 19
        // 493 + 19 - 1=> 511
        read_eeprom_bytes(&buf[0], i, min(MAX_READ_LENGTH_BYTES, EEPROM_LENGTH_BYTES - i));
        startIdx = i;
        // printf("hhere\n");
      }
      int j = 0;
      for (; j < PATTERN_LENGTH_BYTES; j++) {
        // printf("buf[%d]:%c, j:%d\n", i, buf[i-startIdx], j);
        // printf("eeprom[%d]:%c, j:%d\n", i, eeprom[i], j);
        if (buf[i - startIdx + j] != pattern[j]) {
          break;
        }
      }
      if (j == PATTERN_LENGTH_BYTES) {
        return i;
      }
    }
    return -1;
}

int main(void)
{
    const int result = find_first_occurrence_of_pattern_kmp();
    if (result >= 0)
    {
        printf("Search pattern found at address %d\n", result);
    }
    else
    {
        puts("Search pattern not found");
    }

    return 0;
}