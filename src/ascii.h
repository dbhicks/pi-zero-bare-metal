/*******************************************************************************
 *  Simple ascii rendering functions for writing characters to a framebuffer
 ******************************************************************************/

#ifndef _ASCII_H_
#define _ASCII_H_

#include <stdint.h>

static const uint8_t  CHAR_WIDTH        = 8;
static const uint8_t  CHAR_HEIGHT       = 16;
static const uint8_t  CHAR_VERT_SEP     = 8;
static const uint8_t  CHAR_HORIZ_SEP    = 8;
static const uint32_t FOREGROUND_COLOR  = 0xFFFFFFFF;

void renderString(fb_info_t * fbInfo, char * string);

#endif
