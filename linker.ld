_stack_top_ = 0x00000000 + 128 * 1024 * 1024;

SECTIONS {
  .init 0x8000 : {
    *(.init)
  }
  
  .text : {
    *(.text)
    . = ALIGN(8);
    *(.rodata)
  }
  
  .data : {
    *(.data)
    . = ALIGN(8);
    _edata = .;
  }
  
  _bss_start_ = .;
  .bss : {
    *(.bss)
    . = ALIGN(8);
  }
  _bss_end_ = .;

  _end_ = .;
}
