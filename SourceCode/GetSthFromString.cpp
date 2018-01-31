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

#ifndef GET_STH_FROM_STRING_CPP
#define GET_STH_FROM_STRING_CPP

#include "../SourceHeader/GetSthFromString.h"

inline int GetIntFromString( char * src, int id )
{
	// id - which intiger
	int pos = 0;
	int lenght = strlen( src );
	int i = 0;
	
	while( i < lenght && !( (unsigned char)((*(src+i))-48) < 10 && ( ( ( *(src+i-1) == ' ' || *(src+i-1) == ',' || *(src+i-1) == ';' ) && i > 0 ) || ( ( *(src+i-2) == ' ' || *(src+i-2) == ',' || *(src+i-2) == ';' ) && *(src+i-1) == '-' && i > 1 ) || i == 0 || ( i == 1 && *(src+i-1) == '-' ) ) ) )
	{
		i++;
	}
	
	while( i < lenght )
	{
		if( pos < id )
		{
			pos++;
			if( (unsigned char)((*(src+i))-48) < 10 && ( ( ( *(src+i-1) == ' ' || *(src+i-1) == ',' || *(src+i-1) == ';' ) && i > 0 ) || ( ( *(src+i-2) == ' ' || *(src+i-2) == ',' || *(src+i-2) == ';' ) && *(src+i-1) == '-' && i > 1 ) || i == 0 || ( i == 1 && *(src+i-1) == '-' ) ) )
				i++;
			while( i < lenght && !( (unsigned char)((*(src+i))-48) < 10 && ( ( ( *(src+i-1) == ' ' || *(src+i-1) == ',' || *(src+i-1) == ';' ) && i > 0 ) || ( ( *(src+i-2) == ' ' || *(src+i-2) == ',' || *(src+i-2) == ';' ) && *(src+i-1) == '-' && i > 1 ) || i == 0 || ( i == 1 && *(src+i-1) == '-' ) ) ) )
			{
				i++;
			}
		}
		else
		{
			break;
		}
	}
	
	if( i >= lenght )
		return 0;
	
	int positive = 1;
	if( i > 0 )
		if( *(src+i-1) == '-' )
			positive = -1;
	
	int dst = 0;
	while( (unsigned char)((*(src+i))-48) < 10 && i < lenght )
	{
		dst *= 10;
		dst += (int)((*(src+i))-48);
		i++;
	}
	return dst*positive;
}

inline int GetIntFromString( char * src )
{
	return GetIntFromString( src, 0 );
}

inline char * GetStringBetweenCharacter( char * src, char character, int id )
{
	int pos = id;
	int i=0;
	int lenght = strlen( src );
	int beginpos = 0;
	int lenghread = 0;
	while( i < lenght && *(src+i) == character )
		i++;
	for( ; i < lenght; i++ )
	{
		if( pos > 0)
		{
			if( *(src+i) == character )
				pos--;
			else
				continue;
			while( i < lenght && *(src+i) == character )
				i++;
			if( i >= lenght )
				return NULL;
			if( *(src+i) != character && i > 0 )
				i--;
		}
		else
		{
			while( i < lenght && *(src+i) == character )
				i++;
			if( i >= lenght )
				return NULL;
			beginpos = i;
			lenghread = beginpos;
			while( i < lenght && *(src+i) != character )
			{
				lenghread++;
				i++;
			}
			char * dst = new char[lenghread+1-beginpos];
			for( i = beginpos; i < lenghread; i++ )
				*(dst+i-beginpos) = *(src+i);
			*(dst+lenghread-beginpos) = 0;
			return dst;
		}
	}
	return NULL;
}

inline char * GetStringBetweenSpace( char * src, int id )
{
	return GetStringBetweenCharacter( src, ' ', id );
}

inline char * GetStringBetweenSpace( char * src )
{
	return GetStringBetweenSpace( src, 0 );
}

#endif

