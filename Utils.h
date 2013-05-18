#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string.h>
#include <stdio.h>

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
