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

#ifndef STANDARD_MANAGER_C_H
#define STANDARD_MANAGER_C_H

#include <vector>
#include <map>

template < class T, class T2 >
void GetKeys( std::vector < T > & dst, std::map < T, T2 > & src );

template < class T, class T2 >
void GetValues( std::vector < T2 > & dst, std::map < T, T2 > & src );

template < class T >
void PushVectorBack( std::vector < T > & dst, std::vector < T > & src );

template < class T, class T2 >
bool HaveEqualPart( std::map < T, T2 > & src_a, std::map < T, T2 > & src_b );

template < class T, class T2 >
void GetEqualPart( std::vector < T > & dst, std::map < T, T2 > & src_a, std::map < T, T2 > & src_b );

template < class T, class T2 >
void GetEqualPart( std::map < T, T2 > & dst, std::map < T, T2 > & src_a, std::map < T, T2 > & src_b );

template < class T, class T2 >
void MapPushBack( std::map < T, T2 > & dst, std::map < T, T2 > & src );

template < class T, class T2 >
void SumSortedVectorWithMapKeys( std::vector < T > & dst, const std::map < T, T2 > & src );

#endif

