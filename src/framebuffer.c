/*******************************************************************************
 *  support functions for the raspberry pi zero's framebuffer interface
 ******************************************************************************/

#include "framebuffer.h"
#include "mailbox.h"

/*
 * Initializes a framebuffer struct, sends to the VC via mailbox 0, then awaits the response
 *
 * Params: fbInfo - pointer to the framebuffer information structure
 *         width  - the requested frame width
 *         height - the requested frame height
 *         depth  - the requested bit depth
 * Side effects: the VC overwrites the fbInfo structure with the provided framebuffer information
 * Returns: none
 */
void initializeFrameBuffer (fb_info_t * fbInfo, uint32_t width, uint32_t height, uint32_t depth)
{
  fbInfo->width = width;
  fbInfo->height = height;
  fbInfo->vWidth = width;
  fbInfo->vHeight = height;
  fbInfo->depth = depth;
  fbInfo->yOffset = 0;
  fbInfo->xOffset = 0;
  fbInfo->fbSize = 0;
  fbInfo->pitch = 0;
  fbInfo->fb = 0;
  
  /* write the fbInfo to mailbox 0, channel 1 and await a response */
  writeMB0((uint32_t) fbInfo, FRAMEBUFFER);
  readMB0(FRAMEBUFFER);
}


/*
 *  Draws a simple square to the passed in framebuffer by simply writing 0xFF
 *  into each byte in the buffer
 *
 *  Params: fbInfo - a pointer to the framebuffer to write to
 *  Side effects: the framebuffer will be written to
 *  Returns: none
 */
void drawSquareLoop (fb_info_t * fbInfo)
{
  volatile uint8_t * pix = (volatile uint8_t *) (fbInfo->fb & (~L2_BYPASS_MASK));

  while (1) {
    for (uint32_t i = 0; i < fbInfo->fbSize; i++) {
      pix[i] = 0xFF;
    }
  }
}


/*
 *  Draw an individual pixel to a framebuffer
 *
 *  Params: fbInfo  - pointer to the framebuffer info struct defining the 
 *                    framebuffer to write to
 *          x       - x coordinate of the pixel 
 *          y       - y coordinate of the pixel
 *          color   - the color to write
 *
 */
void fbPutPixel (fb_info_t * fbInfo, uint32_t x, uint32_t y, uint32_t color)
{
  /* get the byte offset of the pixel and write in the color */
  uint32_t offset = (y * fbInfo->pitch) + (x << 2);
  uint32_t * pixel = (uint32_t *) (fbInfo->fb + offset);
  *pixel = color;
}
