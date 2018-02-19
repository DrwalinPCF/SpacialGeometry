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

#ifndef AABB_CPP
#define AABB_CPP

#include "../SourceHeader/AABB.h"

AABB AABB::GetRotated( const Quat& quat ) const
{
	Vector v = quat*min;
	AABB aabb( v, v );
	aabb.AddPoint( quat*Vector(min.x,min.y,max.z) );
	aabb.AddPoint( quat*Vector(min.x,max.y,min.z) );
	aabb.AddPoint( quat*Vector(max.x,min.y,min.z) );
	aabb.AddPoint( quat*Vector(max.x,min.y,max.z) );
	aabb.AddPoint( quat*Vector(max.x,max.y,min.z) );
	aabb.AddPoint( quat*Vector(min.x,max.y,max.z) );
	aabb.AddPoint( quat*Vector(max.x,max.y,max.z) );
	return aabb;
}

inline float AABB::GetVolume() const
{
	Vector a = max-min;
	return abs( a.x * a.y * a.z );
}

inline AABB & AABB::operator = ( const AABB& src )
{
	min = src.min;
	max = src.max;
	return *this;
}

inline AABB AABB::operator + ( const AABB& src ) const
{
	return AABB( Math::Min(min,src.min), Math::Max(max,src.max) );
}

inline AABB AABB::operator + ( const Vector& src ) const
{
	return AABB( min+src, max+src );
}

inline AABB AABB::operator - ( const Vector& src ) const
{
	return AABB( min-src, max-src );
}

inline AABB AABB::operator * ( const Vector& src ) const
{
	return AABB( min*src, max*src );
}

inline AABB AABB::operator / ( const Vector& src ) const
{
	return AABB( min/src, max/src );
}

inline bool AABB::operator == ( const AABB& src ) const
{
	return !memcmp( this, &src, sizeof(AABB) );
}

inline bool AABB::operator != ( const AABB& src ) const
{
	return memcmp( this, &src, sizeof(AABB) );
}

inline bool AABB::operator < ( const AABB& src ) const
{
	return memcmp( this, &src, sizeof(AABB) ) < 0;
}

inline bool AABB::operator > ( const AABB& src ) const
{
	return memcmp( this, &src, sizeof(AABB) ) > 0;
}

inline bool AABB::operator <= ( const AABB& src ) const
{
	return memcmp( this, &src, sizeof(AABB) ) <= 0;
}

inline bool AABB::operator >= ( const AABB& src ) const
{
	return memcmp( this, &src, sizeof(AABB) ) >= 0;
}


inline bool AABB::IsPointInsie( const Vector& p ) const
{
	if( p >= min )
		if( p <= max )
			return true;
	return false;
}

inline bool AABB::SharedPart( const AABB& a, const AABB& b, AABB& dst )
{
	if( a.max > b.min )
	{
		if( a.min < b.max )
		{
			dst.min = Math::Max( a.min, b.min );
			dst.max = Math::Min( a.max, b.max );
			return true;
		}
	}
	return false;
}

inline bool AABB::SharedPart( const AABB& src, AABB& dst ) const
{
	if( max > src.min )
	{
		if( min < src.max )
		{
			dst.min = Math::Max( min, src.min );
			dst.max = Math::Min( max, src.max );
			return true;
		}
	}
	return false;
}

inline bool AABB::IsSharedPart( const AABB& src ) const
{
	if( max > src.min )
	{
		if( min < src.max )
		{
			return true;
		}
	}
	return false;
}

inline Vector AABB::GetMin() const
{
	return min;
}

inline Vector AABB::GetMax() const
{
	return max;
}

inline Vector AABB::GetSize() const
{
	return max-min;
}

inline Vector AABB::GetCenter() const
{
	return (min+max) * 0.5f;
}


inline void AABB::AddPoint( const Vector& point )
{
	if( point.x < min.x )				min.x = point.x;
	else if( point.x > max.x )		max.x = point.x;
	if( point.y < min.y )				min.y = point.y;
	else if( point.y > max.y )		max.y = point.y;
	if( point.z < min.z )				min.z = point.z;
	else if( point.z > max.z )		max.z = point.z;
}

inline bool AABB::LineIntersection( Vector beg, Vector end, Vector& intersection )
{
	Vector bot = min - beg;		// bottom
	Vector size = max - min;
	Vector dir = end - beg;
	Vector top = bot + size;
	
	Vector temp;
	float t = 1.0f, tempf;
	if( t < 0.1f )
		return false;
	bool collide = false;
	
	for( int i = 0; i < 3; ++i )
	{
		if( dir[i] < -ROUNDING_ERROR  || dir[i] > ROUNDING_ERROR )
		{
			tempf = bot[i] / dir[i];
			temp = dir * tempf;
			if( temp[(i+1)%3] <= top[(i+1)%3] )
			{
				if( temp[(i+2)%3] <= top[(i+2)%3] )
				{
					if( temp[(i+1)%3] >= bot[(i+1)%3] )
					{
						if( temp[(i+2)%3] >= bot[(i+2)%3] )
						{
							if( collide == false || tempf < t )
							{
								collide = true;
								t = tempf;
							}
						}
					}
				}
			}
			
			tempf = top[i] / dir[i];
			temp = dir * tempf;
			if( temp[(i+1)%3] <= top[(i+1)%3] )
			{
				if( temp[(i+2)%3] <= top[(i+2)%3] )
				{
					if( temp[(i+1)%3] >= bot[(i+1)%3] )
					{
						if( temp[(i+2)%3] >= bot[(i+2)%3] )
						{
							if( collide == false || tempf < t )
							{
								collide = true;
								t = tempf;
							}
						}
					}
				}
			}
		}
	}
	
	if( collide )
	{
		intersection = beg + ( dir * t );
		return true;
	}
	return false
}

inline void AABB::SetMin( const Vector& min_ )
{
	min = min_;
}

inline void AABB::SetMax( const Vector& max_ )
{
	max = max_;
}

inline void AABB::Set( const Vector& min_, const Vector& max_ )
{
	min = min_;
	max = max_;
}

AABB::AABB()
{
	min.Set( 0.0f, 0.0f, 0.0f );
	max.Set( 0.0f, 0.0f, 0.0f );
}

AABB::AABB( const Vector& min_, const Vector& max_ )
{
	min = min_;
	max = max_;
}

AABB::~AABB()
{
	min.Set( 0.0f, 0.0f, 0.0f );
	max.Set( 0.0f, 0.0f, 0.0f );
}








inline AABBint & AABBint::operator = ( const AABBint& src )
{
	memcpy( this, &src, sizeof(AABBint) );
	return *this;
}

inline bool AABBint::operator == ( const AABBint& src ) const
{
	return memcmp( this, &src, sizeof(AABBint) ) == 0;
}

inline bool AABBint::operator != ( const AABBint& src ) const
{
	return memcmp( this, &src, sizeof(AABBint) ) != 0;
}

inline long long int AABBint::GetMinX() const
{
	return min[0];
}

inline long long int AABBint::GetMinY() const
{
	return min[1];
}

inline long long int AABBint::GetMinZ() const
{
	return min[2];
}

inline long long int AABBint::GetMaxX() const
{
	return max[0];
}

inline long long int AABBint::GetMaxY() const
{
	return max[1];
}

inline long long int AABBint::GetMaxZ() const
{
	return max[2];
}


inline void AABBint::SetMinX( const long long int val )
{
	min[0] = val;
}

inline void AABBint::SetMinY( const long long int val )
{
	min[1] = val;
}

inline void AABBint::SetMinZ( const long long int val )
{
	min[2] = val;
}

inline void AABBint::SetMaxX( const long long int val )
{
	max[0] = val;
}

inline void AABBint::SetMaxY( const long long int val )
{
	max[1] = val;
}

inline void AABBint::SetMaxZ( const long long int val )
{
	max[2] = val;
}


AABBint::AABBint( const AABB& src, const AABB& scale, const long long int size )
{
	Vector scale_ = scale.GetSize();
	scale_ = Vector( ((float)(size))/scale_.x, ((float)(size))/scale_[1], ((float)(size))/scale_[2] );
	AABB temp = src-scale.GetMin();
	temp.Set( temp.GetMin()*scale_, temp.GetMax()*scale_ );
	min[0] = src.GetMin().x;
	min[1] = src.GetMin().y;
	min[2] = src.GetMin().z;
	max[0] = src.GetMax().x;
	max[1] = src.GetMax().y;
	max[2] = src.GetMax().z;
}

AABBint::AABBint()
{
	memset( min, 0, sizeof(min) );
	memset( max, 0, sizeof(max) );
}

AABBint::~AABBint()
{
	memset( min, 0, sizeof(min) );
	memset( max, 0, sizeof(max) );
}

#endif

