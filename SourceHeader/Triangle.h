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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"
#include "Quat.h"
#include "AABB.h"

#ifndef ROUNDING_ERROR
#define ROUNDING_ERROR 0.00001f
#endif

class Triangle
{
private:
	
	Vector pointA;
	Vector pointB;
	Vector pointC;
	
public:
	
	inline void GetPoints( Vector& a, Vector& b, Vector& c ) const;
	
	inline Triangle GetRotated( const Quat& rotation ) const;
	inline Triangle GetMoved( const Vector& possition ) const;
	inline Triangle GetScaled( const Vector& scale ) const;
	inline Triangle& Rotate( const Quat& rotation );
	inline Triangle& Move( const Vector& possition );
	inline Triangle& Scale( const Vector& scale );
	
	inline AABB GetAABB() const;
	
	inline bool operator == ( const Triangle& src ) const;
	inline bool operator != ( const Triangle& src ) const;
	inline bool operator < ( const Triangle& src ) const;
	inline bool operator > ( const Triangle& src ) const;
	inline bool operator <= ( const Triangle& src ) const;
	inline bool operator >= ( const Triangle& src ) const;
	
	inline bool IsTotalOutsideBox( const AABB& box ) const;
	
	inline Vector GetClosestPoint( const Vector& point ) const;
	
	inline bool IsPointInside( const Vector& point ) const;		// if point is inside, then point is in the volume of infinite length which perpendicular cross section is triangle, volume edges are parall to each other; using unnormalized vectors
	inline bool GetIntersectionWithLine( const Vector& begin, const Vector& end, Vector& intersection ) const;
	inline bool GetIntersectionOfPlaneWithLine( const Vector& begin, const Vector& end, Vector& intersection ) const;		// using unnormalized vectors
	
	inline void GetMaxMinWithVector( const Vector& dir, float& tmin, float& tmax ) const;
	inline void EdgesDirection( Vector& ab, Vector& bc, Vector& ca ) const;
	
	inline Vector GetNormal() const;
	inline Vector GetNormalFast() const;
	inline bool IsFrontFacing( const Vector& direction ) const;
	inline float GetArea() const;
	inline void Set( const Vector& a, const Vector& b, const Vector& c );
	inline bool IsOnSameSide( const Vector& p1, const Vector& p2, const Vector& a, const Vector& b ) const;
	
	Triangle();
	Triangle( const Vector& a, const Vector& b, const Vector& c );
	~Triangle();
};

#endif

