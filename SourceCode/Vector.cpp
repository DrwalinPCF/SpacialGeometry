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

#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "../SourceHeader/Vector.h"

inline float& Vector::operator [] ( int a )
{
	switch( a )
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
	return x;
}

inline Vector Vector::operator + ( const Vector& src ) const
{
	return Vector( x+src.x, y+src.y, z+src.z );
}

inline Vector& Vector::operator += ( const Vector& src )
{
	x += src.x;
	y += src.y;
	z += src.z;
	return *this;
}

inline Vector Vector::operator - ( const Vector& src ) const
{
	return Vector( x-src.x, y-src.y, z-src.z );
}

inline Vector& Vector::operator -= ( const Vector& src )
{
	x -= src.x;
	y -= src.y;
	z -= src.z;
	return *this;
}

inline Vector Vector::operator && ( const Vector& src ) const
{
	return Vector( y*src.z - z*src.y, z*src.x - x*src.z, x*src.y - y*src.x );
}

inline Vector Vector::operator * ( const Vector& src ) const
{
	return Vector( x*src.x, y*src.y, z*src.z );
}

inline Vector& Vector::operator *= ( const Vector& src )
{
	x *= src.x;
	y *= src.y;
	z *= src.z;
	return *this;
}

inline Vector Vector::operator * ( const float src ) const
{
	return Vector( x*src, y*src, z*src );
}

inline Vector& Vector::operator *= ( const float src )
{
	x *= src;
	y *= src;
	z *= src;
	return *this;
}

inline Vector Vector::operator / ( const Vector& src ) const
{
	return Vector( x/src.x, y/src.y, z/src.z );
}

inline Vector& Vector::operator /= ( const Vector& src )
{
	x /= src.x;
	y /= src.y;
	z /= src.z;
	return *this;
}

inline Vector Vector::operator / ( const float src ) const
{
	return Vector( x/src, y/src, z/src );
}

inline Vector& Vector::operator /= ( const float src )
{
	x /= src;
	y /= src;
	z /= src;
	return *this;
}

inline bool Vector::operator == ( const Vector& src ) const
{
    return !memcmp( this, &src, sizeof(Vector) );
}

inline bool Vector::operator != ( const Vector& src ) const
{
    return memcmp( this, &src, sizeof(Vector) );
}

inline bool Vector::operator < ( const float src ) const
{
	if( x < src && x > -src )
		if( y < src && y > -src )
			return z < src && z > -src;
	return false;
}

inline bool Vector::operator > ( const float src ) const
{
	if( x > src || x < -src )
		return true;
	if( y > src || y < -src )
		return true;
	return z > src || z < -src;
}

inline bool Vector::operator < ( const Vector& src ) const
{
	if( x < src.x )
		if( y < src.y )
			return z < src.x;
	return false;
}

inline bool Vector::operator > ( const Vector& src ) const
{
	if( x > src.x )
		if( y > src.y )
			return z > src.x;
	return false;
}

inline bool Vector::operator <= ( const Vector& src ) const
{
	if( x <= src.x )
		if( y <= src.y )
			return z <= src.x;
	return false;
}

inline bool Vector::operator >= ( const Vector& src ) const
{
	if( x >= src.x )
		if( y >= src.y )
			return z >= src.x;
	return false;
}


inline Vector& Vector::Set( const float x, const float y, const float z )
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

inline Vector Vector::Cross( const Vector& src ) const
{
	return Vector( y*src.z - z*src.y, z*src.x - x*src.z, x*src.y - y*src.x );
}

inline float Vector::Dot( const Vector& src ) const
{
	return x*src.x + y*src.y + z*src.z;
}

inline float Vector::Length() const
{
	return sqrtf( x*x + y*y + z*z );
}

inline Vector Vector::Versor() const
{
	float length = Length();
	return Vector( x/length, y/length, z/length );
}

inline Vector& Vector::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
	return *this;
}

inline Vector& Vector::CreateVector( const Vector& src1, const Vector& src2 )
{
	x = src2.x-src1.x;
	y = src2.y-src1.y;
	z = src2.z-src1.z;
	return *this;
}

inline void Vector::SetLength( const float dst )
{
	float mul = dst/Length();
	x /= mul;
	y /= mul;
	z /= mul;
}

inline void Vector::GoToVector( const Vector& dst, const float velocity )
{
	Vector vec = dst - (*this);
	float distance = vec.Length();
	
	if( distance > velocity )
		(*this) = dst;
	else
	{
		(*this) += vec * ( velocity / distance );
	}
}

inline void Vector::GoToLength( const float dst, const float velocity )
{
	float length = Length();
	float distance = dst - length;
	if( distance > velocity || distance < -velocity )
	{
		(*this) = (*this) * ( ( length + ( (distance<0.0f) ? -velocity : velocity ) ) / length );
	}
	else
	{
		/*temp*/length = dst / length;
		x *= length;
		y *= length;
		z *= length;
	}
}

Vector::Vector()
{
	x = y = z = 0.0f;
}

Vector::Vector( const float x, const float y, const float z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

#endif

