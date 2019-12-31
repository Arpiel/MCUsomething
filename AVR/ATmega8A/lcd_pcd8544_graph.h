/*
 * lcd_pcd8544_graph.h
 *  Header file for pcd8544-based display graphics functions
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
 
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <inttypes.h>

/*
 * Draw circle w/center (cx,cy) and radius r
 */
 
void lcd_circle(uint8_t cx, uint8_t cy, uint16_t r);

/*
 * Draw line from (x1,y1) to (x2,y2)
 */

void lcd_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif /* __GRAPH_H__ */
