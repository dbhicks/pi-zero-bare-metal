/*******************************************************************************
 *  Simple ascii rendering functions for writing characters to a framebuffer
 ******************************************************************************/

#include "framebuffer.h"
#include "ascii.h"

/* the current x and y offset, in pixels, from (0, 0) */
static uint32_t x_offset = 0;
static uint32_t y_offset = 0;

/* terminal font included as binary defined in assembly */
extern int __terminal_font__;
static uint8_t * terminalFont = (uint8_t *) &__terminal_font__;


/*
 *  renders a null-terminated string to a framebuffer, defined by the
 *  framebuffer pointer parameter, fbInfo
 *
 *  Params: fbInfo - a pointer to the framebuffer to write to
 *          string - the null-terminated string to write
 *  Preconditions: fbInfo must point to a valid and initialized fb_info_t struct
 *  Side effects: writes to the framebuffer
 *  Returns: None
 */
void renderString (fb_info_t * fbInfo, char * string)
{
  char * c = string;

  while (*c != '\0') {
    /* move to the next line if there's no room for the char */
    if ((x_offset + CHAR_WIDTH) > fbInfo->width) {
      x_offset = 0;
      y_offset += CHAR_HEIGHT + CHAR_VERT_SEP;
    }

    /* iterate through the character bitmap data and write out pixels */
    for (uint32_t row = 0; row < CHAR_HEIGHT; row++) {
      uint8_t charBitmapRow = *((uint8_t *)(terminalFont + row + ((*c) << 4)));

      for (uint32_t col = 0; col < CHAR_WIDTH; col++) {
        if (charBitmapRow & 0x1) {
          fbPutPixel(fbInfo, col + x_offset, row + y_offset, FOREGROUND_COLOR);  
        }
        charBitmapRow >>= 1;
      }
    }

    /* update the horizontal offset */
    x_offset += CHAR_WIDTH + CHAR_HORIZ_SEP;
    c++;
  }
}
