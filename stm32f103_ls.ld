ENTRY(Reset_Handler)

MEMORY{
    FLASH(rx): ORIGIN = 0x08000000, LENGTH = 64K
    SRAM(rwx): ORIGIN = 0x20000000, LENGTH = 20K
}
_estack = ORIGIN(SRAM) + LENGTH(SRAM);
SECTIONS 
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text.*)
	    *(.rodata)
	    *(.rodata.*)
	    . = ALIGN(4);
    } > FLASH

    .data :
    {
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);

        _edata = .;
    } > SRAM AT > FLASH
    _sidata = LOADADDR(.data);

    .bss :
    {
        _sbss = .;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        _ebss = .;
    } >SRAM 
}