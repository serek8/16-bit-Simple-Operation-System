ENTRY(main);
SECTIONS
{
    . = 0x5000;
    .text : AT(0x0000)
    {
        *(.text);
    }
} 
