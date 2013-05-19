/*********************************************************************
 * Copyright © 2011-2012,
 * Marwan Abdellah: <abdellah.marwan@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 ********************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string.h>
#include <stdio.h>

#define COUT std::cout
#define ENDL std::endl
#define STRG std::string
#define TAB  "       "
#define LINE "_________________________________________________" << ENDL

#define INFO( MESSAGE )                                         			\
COUT << STRG( __FILE__ ) << ":[" << ( __LINE__ ) << "]" <<      			\
ENDL << TAB << "* " << STRG( __FUNCTION__ ) << TAB <<          				\
STRG( MESSAGE ) << ENDL;

#define EXIT( CODE ) 														\
COUT << STRG( __FILE__ ) << ":[" <<                             			\
( __LINE__ ) << "]" << ENDL << TAB <<                           			\
STRG( __FUNCTION__ ) << ": EXITING " << CODE << ENDL;           			\
exit( 0 );

#endif // UTILS_H
