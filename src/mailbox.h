/*******************************************************************************
 * Functions to support the mailbox interface between ARM CPU and the VC.
 ******************************************************************************/

#ifndef _MAILBOX_H_
#define _MAILBOX_H_

#include <stdint.h>

#include "framebuffer.h"

/* useful constants */
static const uint32_t MAIL_FULL       = 0x80000000;   // status register full flag
static const uint32_t MAIL_EMPTY      = 0x40000000;   // status register empty flag
static const uint32_t L2_BYPASS_MASK  = 0x40000000;   // disable L2 caching
static const uint32_t CHANNEL_MASK    = 0xF;          // channels: lower 4 bits

/*  Mailbox 0 registers of interest */
static volatile uint32_t * const MB0_READ   = (uint32_t *) 0x2000B880;
static volatile uint32_t * const MB0_WRITE  = (uint32_t *) 0x2000B8A0;
static volatile uint32_t * const MB0_STATUS = (uint32_t *) 0x2000B898;

/* available channels in mailbox 0 */
typedef enum {
  POWER_MANAGEMENT,
  FRAMEBUFFER,
  UART,
  VCHIQ,
  LED,
  BUTTON,
  TOUCH,
  __reserved__, // unused?
  ARM_TO_VC,
  VC_TO_ARM
}MB0_CHANNEL;

uint32_t readMB0(MB0_CHANNEL channel);
void writeMB0(uint32_t data, MB0_CHANNEL channel);

#endif
