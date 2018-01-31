/*
	Copyright (C) 2017 Marek Zalewski
	
	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.
	
	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgment in the product documentation is required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.
*/

#ifndef GET_STH_FROM_STRING_H
#define GET_STH_FROM_STRING_H

#include <cstring>

#ifndef NULL
#define NULL 0
#endif

inline int GetIntFromString( char * src, int id );

inline int GetIntFromString( char * src );

inline char * GetStringBetweenCharacter( char * src, char character, int id );

inline char * GetStringBetweenSpace( char * src, int id );

inline char * GetStringBetweenSpace( char * src );

#endif

