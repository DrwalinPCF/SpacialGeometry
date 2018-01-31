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

#ifndef OCTTREE_CPP
#define OCTTREE_CPP

#include "../SourceHeader/Octtree.h"

template < class T >
inline void OcttreeNode<T>::Destroy()
{
	if( node[0][0][0] != NULL )
	{
		node[0][0][0] -> Destroy();
		delete node[0][0][0];
		node[0][0][0] = NULL;
	}
	if( node[0][1][0] != NULL )
	{
		node[0][1][0] -> Destroy();
		delete node[0][1][0];
		node[0][1][0] = NULL;
	}
	if( node[1][0][0] != NULL )
	{
		node[1][0][0] -> Destroy();
		delete node[1][0][0];
		node[1][0][0] = NULL;
	}
	if( node[1][1][0] != NULL )
	{
		node[1][1][0] -> Destroy();
		delete node[1][1][0];
		node[1][1][0] = NULL;
	}
	
	if( node[0][0][1] != NULL )
	{
		node[0][0][1] -> Destroy();
		delete node[0][0][1];
		node[0][0][1] = NULL;
	}
	if( node[0][1][1] != NULL )
	{
		node[0][1][1] -> Destroy();
		delete node[0][1][1];
		node[0][1][1] = NULL;
	}
	if( node[1][0][1] != NULL )
	{
		node[1][0][1] -> Destroy();
		delete node[1][0][1];
		node[1][0][1] = NULL;
	}
	if( node[1][1][1] != NULL )
	{
		node[1][1][1] -> Destroy();
		delete node[1][1][1];
		node[1][1][1] = NULL;
	}
	if( data != NULL )
	{
		delete data;
		data = NULL;
	}
}

template < class T >
inline octtreePosDataType OcttreeNode<T>::GetNodeNumber() const
{
	int i = 1;
	if( node[0][0][0] != NULL )
	{
		i += (node[0][0][0] -> GetNodeNumber());
	}
	if( node[0][1][0] != NULL )
	{
		i += (node[0][1][0] -> GetNodeNumber());
	}
	if( node[1][0][0] != NULL )
	{
		i += (node[1][0][0] -> GetNodeNumber());
	}
	if( node[1][1][0] != NULL )
	{
		i += (node[1][1][0] -> GetNodeNumber());
	}
	
	if( node[0][0][1] != NULL )
	{
		i += (node[0][0][1] -> GetNodeNumber());
	}
	if( node[0][1][1] != NULL )
	{
		i += (node[0][1][1] -> GetNodeNumber());
	}
	if( node[1][0][1] != NULL )
	{
		i += (node[1][0][1] -> GetNodeNumber());
	}
	if( node[1][1][1] != NULL )
	{
		i += (node[1][1][1] -> GetNodeNumber());
	}
	
	return i;
}

template < class T >
inline void OcttreeNode<T>::Print( const octtreePosDataType i ) const
{
	if( node[0][0][0] != NULL )
	{
		for( octtreePosDataType a = 0; a <= i; ++a )
			printf( " " );
		printf( "00\n" );
		node[0][0][0] -> Print(i+1);
	}
	if( node[0][1][0] != NULL )
	{
		for( octtreePosDataType a = 0; a <= i; ++a )
			printf( " " );
		printf( "01\n" );
		node[0][1][0] -> Print(i+1);
	}
	if( node[1][0][0] != NULL )
	{
		for( octtreePosDataType a = 0; a <= i; ++a )
			printf( " " );
		printf( "10\n" );
		node[1][0][0] -> Print(i+1);
	}
	if( node[1][1][0] != NULL )
	{
		for( octtreePosDataType a = 0; a <= i; ++a )
			printf( " " );
		printf( "11\n" );
		node[1][1][0] -> Print(i+1);
	}
	
	if( node[0][0][1] != NULL )
	{
		for( octtreePosDataType a = 0; a <= i; ++a )
			printf( " " );
		printf( "00\n" );
		node[0][0][1] -> Print(i+1);
	}
	if( node[0][1][1] != NULL )
	{
		for( octtreePosDataType a = 0; a <= i; ++a )
			printf( " " );
		printf( "01\n" );
		node[0][1][1] -> Print(i+1);
	}
	if( node[1][0][1] != NULL )
	{
		for( octtreePosDataType a = 0; a <= i; ++a )
			printf( " " );
		printf( "10\n" );
		node[1][0][1] -> Print(i+1);
	}
	if( node[1][1][1] != NULL )
	{
		for( octtreePosDataType a = 0; a <= i; ++a )
			printf( " " );
		printf( "11\n" );
		node[1][1][1] -> Print(i+1);
	}
	
	if( data != NULL )
	{
		for( octtreePosDataType a = 0; a <= i; ++a )
			printf( " " );
		printf( "data: OCTTREE_PRINTF_SPECIFIER\n", data->size() );
	}
}


template < class T >
inline void OcttreeNode<T>::AddToVboEdges( std::vector < Vector > & points, Vector offset, Vector size )
{
	if( data )
	{
		std::vector < Vector > vertices;
		vertices.resize( 8 );
		int i;
		for( i = 0; i < vertices.size(); ++i )
		{
			vertices[i] = offset;
		}
		vertices[0];
		vertices[1] += Vector( size[0], 0.0f, 		0.0f );
		vertices[2] += Vector( 0.0f, 	size[1], 	0.0f );
		vertices[3] += Vector( 0.0f, 	0.0f, 		size[2] );
		vertices[4] += Vector( size[0], size[1], 	0.0f );
		vertices[5] += Vector( size[0], 0.0f, 		size[2] );
		vertices[6] += Vector( 0.0f, 	size[1], 	size[2] );
		vertices[7] += Vector( size[0], size[1], 	size[2] );
		
		points.push_back( vertices[0] );
		points.push_back( vertices[1] );
		
		points.push_back( vertices[0] );
		points.push_back( vertices[2] );
		
		points.push_back( vertices[0] );
		points.push_back( vertices[3] );
		
		points.push_back( vertices[1] );
		points.push_back( vertices[4] );
		
		points.push_back( vertices[2] );
		points.push_back( vertices[6] );
		
		points.push_back( vertices[3] );
		points.push_back( vertices[5] );
		
		points.push_back( vertices[7] );
		points.push_back( vertices[4] );
		
		points.push_back( vertices[7] );
		points.push_back( vertices[5] );
		
		points.push_back( vertices[7] );
		points.push_back( vertices[6] );
		
		points.push_back( vertices[1] );
		points.push_back( vertices[5] );
		
		points.push_back( vertices[2] );
		points.push_back( vertices[4] );
		
		points.push_back( vertices[3] );
		points.push_back( vertices[6] );
		
		vertices.clear();
	}
	else if( node )
	{
		int i, j, k;
		for( i = 0; i < 2; ++i )
		{
			for( j = 0; j < 2; ++j )
			{
				for( k = 0; k < 2; ++k )
				{
					if( node[i][j][k] )
					{
						node[i][j][k]->AddToVboEdges( points, offset + Vector( i?(size[0]*0.5f):0.0f, j?(size[1]*0.5f):0.0f, k?(size[2]*0.5f):0.0f ), size*0.5f );
					}
				}
			}
		}
		std::vector < Vector > vertices;
		vertices.resize( 18 );
		for( i = 0; i < vertices.size(); ++i )
		{
			vertices[i] = offset;
		}
		vertices[0] += Vector(	size[0]*0.5f,			0.0f,			0.0f );
		vertices[1] += Vector(			0.0f,	size[1]*0.5f,			0.0f );
		vertices[2] += Vector(			0.0f, 			0.0f,	size[2]*0.5f );
		
		vertices[3] += Vector(	size[0]*0.5f,	size[1]+0.0f,			0.0f );
		vertices[4] += Vector(			0.0f,	size[1]*0.5f,	size[2]		 );
		vertices[5] += Vector(	size[0],	 			0.0f,	size[2]*0.5f );
		
		vertices[6] += Vector(	size[0]*0.5f,			0.0f,	size[2]+0.0f );
		vertices[7] += Vector(	size[0],		size[1]*0.5f,			0.0f );
		vertices[8] += Vector(			0.0f, 	size[1],		size[2]*0.5f );
		
		vertices[9]  += Vector(	size[0]*0.5f,	size[1],		size[2]		 );
		vertices[10] += Vector(	size[0],		size[1]*0.5f,	size[2]		 );
		vertices[11] += Vector(	size[0],	 	size[1],		size[2]*0.5f );
		
		vertices[12] += Vector(	size[0]*0.5f,	size[1]*0.5f,			0.0f );
		vertices[13] += Vector(			0.0f,	size[1]*0.5f,	size[2]*0.5f );
		vertices[14] += Vector(	size[0]*0.5f, 			0.0f,	size[2]*0.5f );
		vertices[15] += Vector(	size[0]*0.5f,	size[1]*0.5f,	size[2]*1.0f );
		vertices[16] += Vector(	size[0]*1.0f,	size[1]*0.5f,	size[2]*0.5f );
		vertices[17] += Vector(	size[0]*0.5f, 	size[1]*1.0f,	size[2]*0.5f );
		
		
		points.push_back( vertices[0] );
		points.push_back( vertices[3] );
		points.push_back( vertices[1] );
		points.push_back( vertices[4] );
		points.push_back( vertices[2] );
		points.push_back( vertices[5] );
		
		points.push_back( vertices[0] );
		points.push_back( vertices[6] );
		points.push_back( vertices[1] );
		points.push_back( vertices[7] );
		points.push_back( vertices[2] );
		points.push_back( vertices[8] );
		
		points.push_back( vertices[9] );
		points.push_back( vertices[3] );
		points.push_back( vertices[10] );
		points.push_back( vertices[4] );
		points.push_back( vertices[11] );
		points.push_back( vertices[5] );
		
		points.push_back( vertices[9] );
		points.push_back( vertices[6] );
		points.push_back( vertices[10] );
		points.push_back( vertices[7] );
		points.push_back( vertices[11] );
		points.push_back( vertices[8] );
		
		
		points.push_back( vertices[13] );
		points.push_back( vertices[16] );
		points.push_back( vertices[12] );
		points.push_back( vertices[15] );
		points.push_back( vertices[14] );
		points.push_back( vertices[17] );
		
		vertices.clear();
	}
	return;
}


template < class T >
OcttreeNode<T>::OcttreeNode()
{
	node[0][0][0] = NULL;
	node[0][1][0] = NULL;
	node[1][0][0] = NULL;
	node[1][1][0] = NULL;
	node[0][0][1] = NULL;
	node[0][1][1] = NULL;
	node[1][0][1] = NULL;
	node[1][1][1] = NULL;
	data = NULL;
}

template < class T >
OcttreeNode<T>::~OcttreeNode()
{
	Destroy();
}

template < class T >
inline bool Octtree<T>::PosNotEnable( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z ) const
{
	return _x < 0 || _x >= 1<<lvl || _y < 0 || _y >= 1<<lvl || _z < 0 || _z >= 1<<lvl;
}

template < class T >
inline bool Octtree<T>::Exist( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z ) const
{
	defaultValue = defaultValueCopy;
	if( PosNotEnable( _x, _y, _z ) )
		return false;
	
	octtreePosDataType i, fx, fy, fz;
	
	OcttreeNode<T> * currentNode = &node;
	
	for( i = 0; i < lvl; ++i )
	{
		fx = octtreePosDataType(_x>>(lvl-i))&1;
		fy = octtreePosDataType(_y>>(lvl-i))&1;
		fz = octtreePosDataType(_z>>(lvl-i))&1;
		if( currentNode -> node[fx][fy][fz] != NULL )
		{
			currentNode = currentNode -> node[fx][fy][fz];
		}
		else
		{
			return false;
		}
	}
	
	if( currentNode -> data != NULL )
	{
		return true;
	}
	
	return false;
}

template < class T >
inline void Octtree<T>::Set( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z, const T src )
{
	defaultValue = defaultValueCopy;
	if( PosNotEnable( _x, _y, _z ) )
		return;
	
	int i, fx, fy, fz;
	
	OcttreeNode<T> * currentNode = &node;
	
	for( i = 0; i < lvl; ++i )
	{
		fx = octtreePosDataType(_x>>(lvl-i))&1;
		fy = octtreePosDataType(_y>>(lvl-i))&1;
		fz = octtreePosDataType(_z>>(lvl-i))&1;
		if( currentNode -> node[fx][fy][fz] == NULL )
		{
			currentNode -> node[fx][fy][fz] = new OcttreeNode<T>;
		}
		currentNode = currentNode -> node[fx][fy][fz];
	}
	
	if( currentNode -> data == NULL )
	{
		currentNode -> data = new T;
	}
	
	*(currentNode -> data) = src;
}

template < class T >
inline T& Octtree<T>::Get( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z )
{
	defaultValue = defaultValueCopy;
	if( PosNotEnable( _x, _y, _z ) )
		return defaultValue;
	
	octtreePosDataType i, fx, fy, fz;
	
	OcttreeNode<T> * currentNode = &node;
	
	for( i = 0; i < lvl; ++i )
	{
		fx = octtreePosDataType(_x>>(lvl-i))&1;
		fy = octtreePosDataType(_y>>(lvl-i))&1;
		fz = octtreePosDataType(_z>>(lvl-i))&1;
		if( currentNode -> node[fx][fy][fz] == NULL )
		{
			currentNode -> node[fx][fy][fz] = new OcttreeNode<T>;
		}
		currentNode = currentNode -> node[fx][fy][fz];
	}
	
	if( currentNode -> data == NULL )
	{
		currentNode -> data = new T;
	}
	
	return *(currentNode -> data);
}

template < class T >
inline T Octtree<T>::GetConst( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z ) const
{
	if( PosNotEnable( _x, _y, _z ) )
		return defaultValue;
	
	octtreePosDataType i, fx, fy, fz;
	
	OcttreeNode<T> * currentNode = (OcttreeNode<T>*)&node;
	
	for( i = 0; i < lvl; ++i )
	{
		fx = octtreePosDataType(_x>>(lvl-i))&1;
		fy = octtreePosDataType(_y>>(lvl-i))&1;
		fz = octtreePosDataType(_z>>(lvl-i))&1;
		if( currentNode -> node[fx][fy][fz] != NULL )
		{
			currentNode = currentNode -> node[fx][fy][fz];
		}
		else
		{
			return defaultValue;
		}
	}
	
	if( currentNode -> data == NULL )
	{
		return defaultValue;
	}
	
	return *(currentNode -> data);
}

template < class T >
inline void Octtree<T>::Erase( const octtreePosDataType _x, const octtreePosDataType _y, const octtreePosDataType _z )
{
	defaultValue = defaultValueCopy;
	if( PosNotEnable( _x, _y, _z ) )
		return;
	
	octtreePosDataType i, j, k, fx, fy, fz, fast, last = 0, lx = 0, ly = 0, lz = 0;
	
	OcttreeNode<T> * currentNode = &node;
	OcttreeNode<T> * lastNode = &node;
	
	for( i = 0; i < lvl; ++i )
	{
		fx = octtreePosDataType(_x>>(lvl-i))&1;
		fy = octtreePosDataType(_y>>(lvl-i))&1;
		fz = octtreePosDataType(_z>>(lvl-i))&1;
		
		fast = 0;
		fast += ( currentNode->node[0][0][0] != NULL ) ? 1 : 0;
		fast += ( currentNode->node[0][1][0] != NULL ) ? 1 : 0;
		fast += ( currentNode->node[1][0][0] != NULL ) ? 1 : 0;
		fast += ( currentNode->node[1][1][0] != NULL ) ? 1 : 0;
		fast += ( currentNode->node[0][0][1] != NULL ) ? 1 : 0;
		fast += ( currentNode->node[0][1][1] != NULL ) ? 1 : 0;
		fast += ( currentNode->node[1][0][1] != NULL ) ? 1 : 0;
		fast += ( currentNode->node[1][1][1] != NULL ) ? 1 : 0;
		
		if( fast > 1 )
		{
			last = i;
			lx = fx;
			ly = fy;
			lz = fz;
			lastNode = currentNode;
		}
		
		if( currentNode -> node[fx][fy][fz] != NULL )
		{
			currentNode = currentNode -> node[fx][fy][fz];
		}
		else
		{
			currentNode = NULL;
			break;
		}
	}
	
	if( lastNode != NULL )
	{
		if( lastNode -> node[lx][ly][lz] != NULL )
		{
			lastNode -> node[lx][ly][lz] -> Destroy();
			delete lastNode -> node[lx][ly][lz];
			lastNode -> node[lx][ly][lz] = NULL;
		}
	}
}

template < class T >
inline octtreePosDataType Octtree<T>::GetNumberOfNodes() const
{
	return node.GetNodeNumber();
}

template < class T >
inline void Octtree<T>::Print() const
{
	printf( "\n" );
	node.Print( 0 );
}

template < class T >
inline octtreePosDataType Octtree<T>::GetSpaceSizeAxes() const
{
	return ((octtreePosDataType)(1))<<lvl;
}

template < class T >
inline void Octtree<T>::Clear()
{
	node.Destroy();
}

template < class T >
inline void Octtree<T>::Init( const octtreePosDataType levels_, const T defaultValue_ )
{
	if( levels_ > 62 )
		lvl = 62;
	else if( levels_ == 0 )
		lvl = 1;
	else
		lvl = levels_;
	defaultValue = defaultValue_;
	defaultValueCopy = defaultValue;
}

template < class T >
Octtree<T>::Octtree()
{
	memset( &defaultValue, 0, sizeof(T) );
	lvl = 1;
}

template < class T >
Octtree<T>::~Octtree()
{
	memset( &defaultValue, 0, sizeof(T) );
	node.Destroy();
	lvl = 0;
}

#endif

