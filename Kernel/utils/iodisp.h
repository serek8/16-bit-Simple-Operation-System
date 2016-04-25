#define TRUE  0x01
#define FALSE 0x00







/* this function is used to clear the */
/* screen buffer by splitting spaces  */

void clearScreen() {
     __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0200), "b"(0x0000), "d"(0x0000)
     );
     __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0920), "b"(0x0007), "c"(0x2000)
     );
}


void setCursor(short col, short row) {
     __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0200), "d"((row <<= 8) | col)
     );
}

void showCursor(short choice) {
     if(choice == FALSE) {
          __asm__ __volatile__(
               "int $0x10" : : "a"(0x0100), "c"(0x3200)
          );
     } else {
          __asm__ __volatile__(
               "int $0x10" : : "a"(0x0100), "c"(0x0007)
          );
     }
}



void getch() {
     __asm__ __volatile__ (
          "xorw %ax, %ax\n"
          "int $0x16\n"
     );
}


char getchar() {
     char word;

     __asm__ __volatile__(
          "int $0x16" : : "a"(0x1000)
     );

     __asm__ __volatile__(
          "movb %%al, %0" : "=r"(word)
     );

     return word;
}

/* this function is used to display the*/
/* key on the screen                   */
void putchar(short ch) {
     __asm__ __volatile__(
          "int $0x10" : : "a"(0x0e00 | (char)ch)
     );
}

/* this function is used to print the  */
/* null terminated string on the screen*/
void print_string(const char* pStr) {
     while(*pStr) {
          __asm__ __volatile__ (
               "int $0x10" : : "a"(0x0e00 | *pStr), "b"(0x0002)
          );
          ++pStr;
     }
}
