__asm__(".code16gcc\n");
__asm__("jmp $0x0000, $main\n");


#include "../../Kernel/utils/iodisp.h"


#define CARRIAGE_RETURN_ASCII 0x0D

void main() 
{
	char byte;
	int i = 0;
	char buffer[256];
	print_string("\nPodaj dzialanie: ");

	while((byte = getchar()))
	{
		if(byte == CARRIAGE_RETURN_ASCII)
	  	{
		    break;
	  	}
		else 
	  	{
	    	putchar(byte);
	    	buffer[i] = byte;
	    	++i;
	  	}
	}
	putchar(CARRIAGE_RETURN_ASCII);

	i = 0;
	int first_number = 0, second_number = 0, result = 0;
	char operation;
	

	while (buffer[i] >= '0' && buffer[i] <= '9')
	{
		first_number *= 10;
		first_number += (int)buffer[i] - '0';
		++i;
	}
	
	operation = buffer[i];
	++i;

	while (buffer[i] >= '0' && buffer[i] <= '9')
	{
		second_number *= 10;
		second_number += (int)buffer[i] - '0';
		++i;
	}

	switch (operation)
	{
	case '+':
		result = first_number + second_number;
		break;
	case '-':
		result = first_number - second_number;
		break;
	case '*':
		result = first_number * second_number;
		break;
	case 'x':
		result = first_number * second_number;
		break;
	case '/':
		result = first_number / second_number;
		break;
	case ':':
		result = first_number / second_number;
		break;
	default:
		print_string("\nNiewlasciwe dzialanie! \n");
		break;
	}

	char result_ascii[256];

	int digit[256];
	i = 0;

	while (result != 0)
	{
		digit[i] = result % 10;
		result /= 10;
		++i;
	}

	for (int j = i - 1, k = 0; j >= 0; --j, ++k)
	{
		result_ascii[j] = digit[k] + '0';
	}
    
	print_string("\nWynik: ");

    for (int j = 0; j < i; ++j)
    {
    	putchar(result_ascii[j]);
    }

}






