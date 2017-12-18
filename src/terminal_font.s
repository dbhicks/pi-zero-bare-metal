/*******************************************************************************
 * Simple assembly instructions to include a binary bitmap font for use later
 * by C portions of the kernel in font rendering
 ******************************************************************************/

.data
.align 4
.globl __terminal_font__

__terminal_font__:
  .incbin "src/monospace_font.bin" 
