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

#ifndef AABB_H
#define AABB_H

#include "Math.h"
#include "Vector.h"
#include "Quat.h"

class AABB
{
private:
	Vector min;
	Vector max;
	
public:
	
	AABB GetRotated( const Quat& quat ) const;
	
	inline float GetVolume() const;
	
	inline AABB & operator = ( const AABB& src );
	inline AABB operator + ( const AABB& src ) const;
	inline AABB operator + ( const Vector& src ) const;
	inline AABB operator - ( const Vector& src ) const;
	inline AABB operator * ( const Vector& src ) const;
	inline AABB operator / ( const Vector& src ) const;
	
	inline bool operator == ( const AABB& src ) const;
	inline bool operator != ( const AABB& src ) const;
	inline bool operator < ( const AABB& src ) const;
	inline bool operator > ( const AABB& src ) const;
	inline bool operator <= ( const AABB& src ) const;
	inline bool operator >= ( const AABB& src ) const;
	
	inline bool IsPointInsie( const Vector& p ) const;
	
	inline static bool SharedPart( const AABB& a, const AABB& b, AABB& dst );
	inline bool SharedPart( const AABB& src, AABB& dst ) const;
	inline bool IsSharedPart( const AABB& src ) const;
	
	inline Vector GetMin() const;
	inline Vector GetMax() const;
	inline Vector GetSize() const;
	inline Vector GetCenter() const;
	
	inline void AddPoint( const Vector& point );
	
	inline bool LineIntersection( Vector beg, Vector end, Vector& intersection );
	
	inline void SetMin( const Vector& min_ );
	inline void SetMax( const Vector& max_ );
	inline void Set( const Vector& min_, const Vector& max_ );
	
	AABB();
	AABB( const Vector& min_, const Vector& max_ );
	~AABB();
};

class AABBint
{
public:
	long long int min[3];
	long long int max[3];
	
	inline AABBint & operator = ( const AABBint& src );
	inline bool operator == ( const AABBint& src ) const;
	inline bool operator != ( const AABBint& src ) const;
	
	inline long long int GetMinX() const;
	inline long long int GetMinY() const;
	inline long long int GetMinZ() const;
	inline long long int GetMaxX() const;
	inline long long int GetMaxY() const;
	inline long long int GetMaxZ() const;
	
	inline void SetMinX( const long long int val );
	inline void SetMinY( const long long int val );
	inline void SetMinZ( const long long int val );
	inline void SetMaxX( const long long int val );
	inline void SetMaxY( const long long int val );
	inline void SetMaxZ( const long long int val );
	
	AABBint( const AABB& src, const AABB& scale, const long long int size );
	AABBint();
	~AABBint();
};

#endif

