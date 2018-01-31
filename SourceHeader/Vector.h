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

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <cstring>

class Vector
{
public:
	
	float x, y, z;
	
	friend class Quat;
	
	inline float& operator [] ( int a );
	
	inline Vector operator + ( const Vector& src ) const;
	inline Vector& operator += ( const Vector& src );
	inline Vector operator - ( const Vector& src ) const;
	inline Vector& operator -= ( const Vector& src );
	
	inline Vector operator && ( const Vector& src ) const;
	
	inline Vector operator * ( const Vector& src ) const;
	inline Vector& operator *= ( const Vector& src );
	inline Vector operator * ( const float src ) const;
	inline Vector& operator *= ( const float src );
	inline Vector operator / ( const Vector& src ) const;
	inline Vector& operator /= ( const Vector& src );
	inline Vector operator / ( const float src ) const;
	inline Vector& operator /= ( const float src );
	
	inline bool operator == ( const Vector& src ) const;
	inline bool operator != ( const Vector& src ) const;
	inline bool operator < ( const float src ) const;
	inline bool operator > ( const float src ) const;
	inline bool operator < ( const Vector& src ) const;
	inline bool operator > ( const Vector& src ) const;
	inline bool operator <= ( const Vector& src ) const;
	inline bool operator >= ( const Vector& src ) const;
	
	inline Vector& Set( const float x, const float y, const float z );
	
	inline Vector Cross( const Vector& src ) const;
	inline float Dot( const Vector& src ) const;
	inline float Length() const;
	inline Vector Versor() const;
	inline Vector& Normalize();
	inline Vector& CreateVector( const Vector& src1, const Vector& src2 );
	
	inline void SetLength( const float dst );
	inline void GoToVector( const Vector& dst, const float velocity );
	inline void GoToLength( const float dst, const float velocity );
	
	Vector();
	Vector( const float x, const float y, const float z );
};

#endif

