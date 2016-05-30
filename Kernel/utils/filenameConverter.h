#define TRUE  0x01
#define FALSE 0x00

char to_upper(char x)
{
    if(x > 'Z') x = x - 32;
    return x;
}
void name_to_fat_12_format(char *source, char *dest)
{
    int i=0;
    for( ; i<12; i++)
    {
        if(source[i] == '.') break;
        dest[i] = to_upper(source[i]);
        
    }
    char format[3];
    format[0] = to_upper(source[i+1]);
    format[1] = to_upper(source[i+2]);
    format[2] = to_upper(source[i+3]);
    for( ; i<9; i++)
    {
        dest[i] = ' ';
    }
    
    dest[9] = to_upper(format[0]);
    dest[10] = to_upper(format[1]);
    dest[11] = to_upper(format[2]);
    
}


void get_option(char *source, char *dest)
{
    int i=0;
    for ( ;i<255; i++)
        if (source[i] == ' ') break;
    i++;
    for (int j=0; j<255; j++, i++)
    {
        if(source[i] == '\0') break;
        dest[j]=source[i];
    }
}


