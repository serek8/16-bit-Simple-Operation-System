__asm__(".code16gcc\n");
__asm__("jmp $0x0000, $main\n");

extern void _PrintString(const char *str, const char *str2);
extern char* _LoadFileWithName(char *filename);
extern char* _ListFiles();
extern void list_fat12_all(char*);


#include "utils/iodisp.h"
#include "utils/filenameConverter.h"


typedef char bool;
#define true 1
#define false 0

#define NULL 0


#define CARRIAGE_RETURN_ASCII 0x0D
#define NEW_LINE_ASCII 0x0A


/* this function is used to sleep for  */
/* a given number of seconds           */

void delay(int seconds) {
     __asm__ __volatile__(
          "int $0x15" : : "a"(0x8600), "c"(0x000f * seconds), "d"(0x4240 * seconds)
     );
}

/* string functions */
/* this function isused to calculate   */
/* length of the string and then return*/
/* it                                  */

int strlength(const char* pStr) {
     int i = 0;

     while(*pStr) {
          ++i;
     }
     return i;
     }

bool compare_strings(const char *str_1, const char *str_2)
{
  unsigned short i = 0;
  while(1)
    {
      if(str_1[i] == NULL && str_2[i]== NULL)
		 return TRUE;
      else if (str_1[i] != str_2[i]) return FALSE;
      ++i;
    }
}
bool compare_strings_with_space(const char *str_option, const char *str_2)
{
    unsigned short i = 0;
    while(1)
    {
        if((str_option[i] == NULL && str_2[i]== NULL) ||
           (str_option[i] == ' ' ))
            return TRUE;
        else if (str_option[i] != str_2[i]) return FALSE;
        ++i;
    }
}


void print_pwr_logo()
{
  char* logo = _LoadFileWithName("PWRPWR  TXT");

  print_string("Politechnika Wroclawska");

  for (int i = 55; i < 116; ++i)
  {
    for (int j = 15; j < 76; ++j)
    {
      if (*logo == '0')
      {
        drawPixel(4, i, j);
      }
      else
      {
        drawPixel(14, i, j);
      }
      logo++;
    }
  }
  getch();
}

void command_cat(char *task_str)
{
	char option_buf[20];
	char filename_buf[20];
	get_option(task_str, option_buf);
	name_to_fat_12_format(option_buf, filename_buf);
	print_string(_LoadFileWithName(filename_buf));
}

void print_windows_logo()
{
  char* logo = _LoadFileWithName("WINDOW  TXT");

  for (int i = 0; i < 100; ++i)
  {
    for (int j = 0; j < 100; ++j)
    {
      if (*logo == '0')
      {
        drawPixel(0, i, j);
      }
      else if (*logo == '1')
      {
        drawPixel(12, i, j);
      }
      else if (*logo == '2')
      {
        drawPixel(10, i, j);
      }
      else if (*logo == '3')
      {
        drawPixel(11, i, j);
      }
      else if (*logo == '4')
      {
        drawPixel(14, i, j);
      }
      logo++;
    }
  }
  getch();
}


/* * * * * * * * * * * * * * * * * * * * * * * * */
/* Wykonuje polecenie dla podanego stringu       */
/* POST:                                         */
/*      true  - jesli wykonano polecenie         */
/*      false - jesli polecenie nie istnieje     */

bool execute_shell_task(char *task_str)
{
  if(compare_strings(task_str, "info"))
    {
        print_string("System operacyjny PWR 16");
    }
  else if(compare_strings(task_str, "color"))
    {
        print_string("Wlaczam kolorowe okienka");
        delay(3);
        __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0013)
      );
    }
  else if(compare_strings(task_str, "nocolor"))
    {
        print_string("Wylaczam kolorowe okienka");
        delay(3);
        __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0003)
      );
    }
  else if(compare_strings(task_str, "logo"))
    {
      clearScreen();
      __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0013)
      );
      print_pwr_logo();
      __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0003)
      );
    }
  else if(compare_strings(task_str, "windows"))
    {
      clearScreen();
      __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0013)
      );
      print_windows_logo();
      __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0003)
      );
    }
else if (compare_strings(task_str, "help"))
    {
      print_string("Lista dostepnych komend:");
      putchar(NEW_LINE_ASCII);
      putchar(NEW_LINE_ASCII);
      putchar(CARRIAGE_RETURN_ASCII);
      print_string("info - informacje o systemie");
      putchar(NEW_LINE_ASCII);
      putchar(CARRIAGE_RETURN_ASCII);
      print_string("logo - logo PWR");
      putchar(NEW_LINE_ASCII);
      putchar(CARRIAGE_RETURN_ASCII);
      print_string("color - kolorowe okienka");
      putchar(NEW_LINE_ASCII);
      putchar(CARRIAGE_RETURN_ASCII);
      print_string("nocolor - wylaczenie kolorowych okienek");
      putchar(NEW_LINE_ASCII);
      putchar(CARRIAGE_RETURN_ASCII);
      print_string("ls - lista dostepnych programow");
      putchar(NEW_LINE_ASCII);
      putchar(NEW_LINE_ASCII);
      putchar(CARRIAGE_RETURN_ASCII);
      print_string("help - lista dostepnych komend");
      putchar(NEW_LINE_ASCII);
      putchar(NEW_LINE_ASCII);
      putchar(CARRIAGE_RETURN_ASCII);
    }
  else if(compare_strings(task_str, "abi"))
    {
     // _PrintString();
    }
  else if(compare_strings_with_space(task_str, "cat"))
    { 
	command_cat(task_str);
    } 
  else if(compare_strings(task_str, "ls"))
    { 
	char result[13*10];
	list_fat12_all(result);
	print_string(result);
    } 
  else return false;
  return true;
}


void list_fat12_all(char *result)
{
	
	char *all_table = _ListFiles();
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<11; j++)
		{
		
			result[(i*13)+j] = all_table[i*64+j];
		}
		result[(i+1)*13-2] = '\n';
		result[(i+1)*13-1] = CARRIAGE_RETURN_ASCII;
	}
}

void shell() 
{
  const char *command_prompt_str = "$> ";
  char buffer[256];
  unsigned char i = 0;

  clearScreen();
  showCursor(TRUE);

  while(TRUE) {
    print_string(command_prompt_str);
    char byte;
    while((byte = getchar())) 
      {
	if(byte == CARRIAGE_RETURN_ASCII)
	  {
	    putchar(NEW_LINE_ASCII);
	    putchar(CARRIAGE_RETURN_ASCII);

	    buffer[i] = NULL;
	    if(!execute_shell_task(buffer))
	      {
		print_string("Nie rozpoznano polecenia !");
	      }
	    putchar(NEW_LINE_ASCII);
	    putchar(CARRIAGE_RETURN_ASCII);
	    i=0;
	    break;
	  }
	else 
	  {
	    putchar(byte);
	    buffer[i] = byte;
	  }
	++i;
      }
  }
}





/* this is the main entry for the kernel*/
void main() {


     print_string("\nWcisnij dowolny klawisz aby kontynuowac !");
     getch();
	
     shell(); 

     while(1);
}






