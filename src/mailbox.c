/*******************************************************************************
 * Functions to support the mailbox interface between the ARM CPU and the VC
 * processor. Presently, only mailbox 0 is supported. Per the available mailbox
 * documentation, the mailbox accepts 32-bit integers, where the upper 28 bits
 * are the data payload and the lower 4 bits are the channel to send to / sent
 * from.
 *
 * Presently, it is unclear if some data payloads are shifted into the upper
 * 28 bits, but in the case of the framebuffer interface (channel 1) the data
 * payload (framebuffer struct address) is not shifted and must be 16-byte
 * aligned so that the address may be combined with the channel number and not
 * overwritten.
 ******************************************************************************/

#include "mailbox.h"


/*
 * Read from a specific channel in mailbox 0.
 *
 * Params: channel - the channel to read from.
 * Returns: the response from the mailbox channel
 *
 * TODO: presently the response is just stripped of the channel information, but
 * it may be more appropriate to right shift the response.
 */
uint32_t readMB0 (MB0_CHANNEL channel)
{
  uint32_t response = 0; 
  while (1) {
    while (*MB0_STATUS & MAIL_EMPTY) {};
    response = *MB0_READ;
    if ((response & CHANNEL_MASK) == channel) {
      return (response & (~CHANNEL_MASK));
    }
  }
}


/*
 * Write to a specific channel in mailbox 0.
 *
 * Params: data     - the data to write
 *         channel  - the mailbox channel to write to 
 * Preconditions: data must be left shifted four bits or a 16-byte aligned address
 * Returns: none
 */
void writeMB0 (uint32_t data, MB0_CHANNEL channel)
{
  data |= L2_BYPASS_MASK | channel; 
  while (*MB0_STATUS & MAIL_FULL) {};
  *MB0_WRITE = data;
}
