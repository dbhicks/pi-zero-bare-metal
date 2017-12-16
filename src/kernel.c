/*******************************************************************************
 *  A simple kernel for the raspberry pi zero
 ******************************************************************************/

#include <stdint.h>

#include "framebuffer.h"
#include "mailbox.h"

/* defined in the linker script */
extern int _bss_start_;
extern int _bss_end_;


/*
 *  Initializse the c environment (partially for now). 
 *  Initialize static variables to zero
 */
void init ()
{
  uint32_t * bss = (uint32_t *) _bss_start_;
  uint32_t * bssEnd = (uint32_t *) _bss_end_;

  while (bss < bssEnd) {
    *bss = 0;
    bss++;
  }
}


/*
 * kernel main function, entry point for C code after the ARM Assembly init
 */
void kernel_main ()
{
  init();

  fb_info_t fbInfo;
  initializeFrameBuffer(&fbInfo, 800, 600, 32);
  drawSquareLoop(&fbInfo);

  while (1);
}
