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

#ifndef OCTTREE_H
#define OCTTREE_H

#include <vector>
#include <cstring>
#include <cstdio>

#include "Vector.h"

typedef long long int octtreePosDataType;
#define OCTTREE_PRINTF_SPECIFIER %lld

template < class T >
class OcttreeNode
{
public:
	OcttreeNode<T> * node[2][2][2];
	T * data;
	
	inline void Destroy();
	
	inline octtreePosDataType GetNodeNumber() const;
	inline void Print( const octtreePosDataType i ) const;
	inline void AddToVboEdges( std::vector < Vector > & points, Vector offset, Vector size );
	
	OcttreeNode();
	~OcttreeNode();
};

template < class T >
class Octtree
{
public:
	OcttreeNode<T> node;
	T defaultValue;
	T defaultValueCopy;
	octtreePosDataType lvl;
	
	inline bool PosNotEnable( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z ) const;
	
	inline bool Exist( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z ) const;
	inline void Set( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z, const T src );
	inline T& Get( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z );
	inline T GetConst( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z ) const;		// get only exist node
	inline void Erase( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z );
	
	inline octtreePosDataType GetNumberOfNodes() const;
	
	inline void Print() const;
	inline octtreePosDataType GetSpaceSizeAxes() const;
	
	inline void Clear();
	
	inline void Init( const octtreePosDataType levels_, const T defaultValue_ );
	
	Octtree();
	~Octtree();
};

#endif

