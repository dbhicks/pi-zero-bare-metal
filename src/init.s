/*******************************************************************************
 * A simple ARM assembly entry point that sets the stack pointer to the stack
 * top, defined in the linker script, and then jumps to the C entry point,
 * the kernel main function.
 ******************************************************************************/

.section .init
.globl _start

_start:
  ldr sp,=_stack_top_
  b kernel_main
