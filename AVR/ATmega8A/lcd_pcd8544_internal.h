/*
 * lcd_pcd8544_internal.h
 *  LCD commands and general internal #defines for PCD8544-based display
 *  control
 *
 * (c) 2004 Tymm Twillman (tymm@booyaka.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
#ifndef __LCD_PCD8544_INTERNAL_H__
#define __LCD_PCD8544_INTERNAL_H__

#include "lcd_pcd8544.h" // mainly for screen size defs

/*
 * Commands 
 */

#define PCD8544_CMD_NOP          0x00

// Function command -- OR with FUNC bits

#define PCD8544_CMD_FUNC         0x20

// Display control commands

#define PCD8544_CMD_DISP_OFF     0x08
#define PCD8544_CMD_DISP_NORM    0x0c
#define PCD8544_CMD_DISP_ALLON   0x09
#define PCD8544_CMD_DISP_INVERSE 0x0d

// Set X/Y address commands

#define PCD8544_CMD_Y_ADDR       0x40
#define PCD8544_CMD_X_ADDR       0x80


/* 
 * Extended Commands -- set extended command use
 *  with FUNC command, XCMD function flag
 */

// Set temp compensation

#define PCD8544_XCMD_TC     0x04

// Set bias voltage

#define PCD8544_XCMD_BIAS   0x10

// Set LCD voltage

#define PCD8544_XCMD_VOP 0x80


/*
 * FUNCTION command flags 
 */

// Function flags

#define PCD8544_FUNC_FLAG_PDOWN     0x04
#define PCD8544_FUNC_FLAG_VERT_ADDR 0x02
#define PCD8544_FUNC_FLAG_XCMD      0x01


/*
 * Maximums and masks 
 */

// Maximum X/Y addresses

#define PCD8544_Y_ADDR_MAX 5
#define PCD8544_X_ADDR_MAX 80

// Temp control mask (bits 0 & 1 for temp control)

#define PCD8544_TC_MASK  0x03

// Bias mask (bits 0, 1, 2 for bias settings)

#define PCD8544_BIAS_MASK  0x07

// Voltage control mask (bits 0-7 set voltage)

#define PCD8544_VOP_MASK 0x7f


/*
 * Defaults 
 */

#define PCD8544_VOP_DEFAULT 0x22
#define PCD8544_BIAS_DEFAULT 2
#define PCD8544_TC_DEFAULT 2


/*
 * Control definitions -- for internal use of lcd_pcd8544.c
 */
 
// Screen buffer size

#define PCD8544_BUF_SIZE ((LCD_HEIGHT / 8) * LCD_WIDTH)

// little special commands

#define lcd_pcd8544_do_set_display_off() (lcd_pcd8544_send(PCD8544_CMD_DISP_OFF))
#define lcd_pcd8544_do_set_display_normal() (lcd_pcd8544_send(PCD8544_CMD_DISP_NORM))
#define lcd_pcd8544_do_set_display_inverse() (lcd_pcd8544_send(PCD8544_CMD_DISP_INVERSE))
#define lcd_pcd8544_do_set_display_allon() (lcd_pcd8544_send(PCD8544_CMD_DISP_ALLON))

#define lcd_pcd8544_do_set_x_addr(x) (lcd_pcd8544_send(PCD8544_CMD_X_ADDR | (x)))
#define lcd_pcd8544_do_set_y_addr(y) (lcd_pcd8544_send(PCD8544_CMD_Y_ADDR | (y)))

// Send function command; function flags stored in static variable so they're not
//  forgotten.

#define lcd_pcd8544_do_func() (lcd_pcd8544_send(PCD8544_CMD_FUNC | pcd8544_func))

// Set framebuffer refresh parameters

#define lcd_set_lorefresh(lo) ((lcd_lorefresh > (lo)) ? lcd_lorefresh = (lo) : 0) 
#define lcd_set_hirefresh(hi) ((lcd_hirefresh < (hi)) ? lcd_hirefresh = (hi) : 0)    

#define lcd_set_allrefresh() (lcd_lorefresh = 0, lcd_hirefresh = PCD8544_BUF_SIZE - 1)
#define lcd_set_norefresh() (lcd_lorefresh = PCD8544_BUF_SIZE, lcd_hirefresh = 0)

// buffer index at location (x,yrow) -- yrow is index of full 8-bit row, not a
//  single pixel height.

#define lcd_buf_loc(x,yrow) (lcd_row_addr[(yrow)] + (x))

// value of lcd buffer location at position (x,yrow)

#define lcd_buf_val(x,yrow) (lcd_buf[lcd_buf_loc((x),(yrow))])

#endif // #ifndef __LCD_PCD8544_INTERNAL_H__
