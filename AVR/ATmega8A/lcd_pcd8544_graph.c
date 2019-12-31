/*
 * lcd_pcd8544_graph.c
 *  Routines for drawing lines & circles (well, kinda circles) on pcd8544-based
 *  displays (requires pcd8544 core functions to work)
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
 
#include "lcd_pcd8544.h"
#include "lcd_pcd8544_graph.h"

/*
 * Plot 8 sectors (for circle drawing)
 */

static inline void plot8sects(uint8_t cx, uint8_t cy, uint8_t x, uint8_t y)
{
	lcd_plot(cx + x, cy + y);
	lcd_plot(cx - x, cy + y);
	lcd_plot(cx + x, cy - y);
	lcd_plot(cx - x, cy - y);
	lcd_plot(cx + y, cy + x);
	lcd_plot(cx - y, cy + x);
	lcd_plot(cx + y, cy - x);
	lcd_plot(cx - y, cy - x);
}


/*
 * Draw a circle, center (cx, cy) with radius r
 *  Unfortunately it's a little blocky with small displays
 */

void lcd_circle(uint8_t cx, uint8_t cy, uint16_t r)
{
	// Bresenham algorithm

	uint8_t x = 0;
	uint8_t y = r;
	int8_t d = 3 - (r * 2);


	while (x < y) {
		plot8sects(cx, cy, x, y);	

		if (d < 0) {
			d += (x << 2) + 3;
		} else {
			d -= ((x - y) << 2) + 5;
			y--;
		}
		x++;
	}
}


/*
 * Draw line from (x1,y1) to (x2,y2)
 */

void lcd_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
/* Takes a lot more code to draw a line than a circle.
 *  Crazy, huh.
 *
 * More Bresenham...
 */

	int16_t dx;
	int16_t dy;
	int8_t xinc;
	int8_t yinc;
	int8_t xyinc;
	uint8_t d;
	uint8_t dmod;
	uint8_t dmod2;
	
	
	dx = x2 - x1;
	dy = y2 - y1;
	
	if (dx < 0) {
		dx = -dx;
		xinc = -1;
	} else {
		xinc = 1;
	}
	
	if (dy < 0) {
		dy = -dy;
		yinc = -1;
	} else {
		yinc = 1;
	}
	
	xyinc = xinc + yinc;
	
	if (dy > dx) {
		dmod = dy << 1;
		d = -dx;
		dmod2 = d << 1;
		dy = dx >> 1;
		
		while (1) {
			lcd_plot(x1, y1);
			lcd_plot(x2, y2);

			if ((d += dmod) > 0) {
				x1 += xyinc;
				x2 -= xyinc;
				d += dmod2;

				if (--dy > 0)
					continue;
					
				lcd_plot(x1, y1);				
				if (!(dx & 1))
					break;
					
				lcd_plot(x2, y2);				
				break;					
			} else {
				x1 += xinc;
				x2 -= xinc;
				
				if (--dy > 0)
					continue;
					
				lcd_plot(x1, y1);
				if (!(dx & 1))
					break;	
					
				lcd_plot(x2, y2);
				break;
			}
		}
	} else {
		dmod = dx << 1;
		d = -dy;
		dmod2 = d << 1;
		dx = dy >> 1;
		
		while (1) {
			lcd_plot(x1, y1);
			lcd_plot(x2, y2);

			if ((d += dmod) > 0) {
				y1 += xyinc;
				y2 -= xyinc;
				d += dmod2;
				
				if (--dx > 0)
					continue;
					
				lcd_plot(x1, y1);
				if (!(dy & 1))
					break;
					
				lcd_plot(x2, y2);
				break;
			} else {
				y1 += yinc;
				y2 -= yinc;
				
				if (--dx > 0)
					continue;
					
				lcd_plot(x1, y1);
				if (!(dy & 1))
					break;
					
				lcd_plot(x2, y2);
				break;
			}
		}
	}
}
