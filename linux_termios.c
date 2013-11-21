/*
 * This file is part of the libserialport project.
 *
 * Copyright (C) 2013 Martin Ling <martin-libserialport@earth.li>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/termios.h>
#include "linux_termios.h"

int get_termios_get_ioctl(void)
{
#ifdef HAVE_TERMIOS2
	return TCGETS2;
#else
	return TCGETS;
#endif
}

int get_termios_set_ioctl(void)
{
#ifdef HAVE_TERMIOS2
	return TCSETS2;
#else
	return TCSETS;
#endif
}

int get_termios_size(void)
{
#ifdef HAVE_TERMIOS2
	return sizeof(struct termios2);
#else
	return sizeof(struct termios);
#endif
}

int get_termios_speed(void *data)
{
#ifdef HAVE_TERMIOS2
	struct termios2 *term = (struct termios2 *) data;
#else
	struct termios *term = (struct termios *) data;
#endif
	if (term->c_ispeed != term->c_ospeed)
		return -1;
	else
		return term->c_ispeed;
}

void set_termios_speed(void *data, int speed)
{
#ifdef HAVE_TERMIOS2
	struct termios2 *term = (struct termios2 *) data;
#else
	struct termios *term = (struct termios *) data;
#endif
	term->c_cflag &= ~CBAUD;
	term->c_cflag |= BOTHER;
	term->c_ispeed = term->c_ospeed = speed;
}