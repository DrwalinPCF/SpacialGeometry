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

#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include "../SourceHeader/Triangle.h"

inline Triangle:: GetPoints( Vector& a, Vector& b, Vector& c ) const
{
	a = pointA;
	b = pointB;
	c = pointC;
}

inline Triangle Triangle::GetRotated( const Quat& rotation ) const
{
	return Triangle( rotation*pointA, rotation*pointB, rotation*pointC );
}

inline Triangle Triangle::GetMoved( const Vector& possition ) const
{
	return Triangle( possition+pointA, possition+pointB, possition+pointC );
}

inline Triangle Triangle::GetScaled( const Vector& scale ) const
{
	return Triangle( pointA*scale, pointB*scale, pointC*scale );
}

inline Triangle& Triangle::Rotate( const Quat& rotation )
{
	pointA = rotation * pointA;
	pointB = rotation * pointB;
	pointC = rotation * pointC;
	return *this;
}

inline Triangle& Triangle::Move( const Vector& possition )
{
	pointA += possition;
	pointB += possition;
	pointC += possition;
	return *this;
}

inline Triangle& Triangle::Scale( const Vector& scale )
{
	pointA *= scale;
	pointB *= scale;
	pointC *= scale;
	return *this;
}

inline AABB Triangle::GetAABB() const
{
	AABB aabb( pointA, pointA );
	aabb.AddPoint( pointB );
	aabb.AddPoint( pointC );
	return aabb;
}

inline bool Triangle::operator == ( const Triangle& src ) const
{
	return !memcmp( this, &src, sizeof(Triangle) );
}

inline bool Triangle::operator != ( const Triangle& src ) const
{
	return memcmp( this, &src, sizeof(Triangle) );
}

inline bool Triangle::operator < ( const Triangle& src ) const
{
	return memcmp( this, &src, sizeof(Triangle) ) < 0;
}

inline bool Triangle::operator > ( const Triangle& src ) const
{
	return memcmp( this, &src, sizeof(Triangle) ) > 0;
}

inline bool Triangle::operator <= ( const Triangle& src ) const
{
	return memcmp( this, &src, sizeof(Triangle) ) <= 0;
}

inline bool Triangle::operator >= ( const Triangle& src ) const
{
	return memcmp( this, &src, sizeof(Triangle) ) >= 0;
}


inline bool Triangle::IsTotalOutsideBox( const AABB& box ) const
{
	if( pointA.x > box.GetMax().x && pointB.x > box.GetMax().x && pointC.x > box.GetMax().x )	return true;
	if( pointA.y > box.GetMax().y && pointB.y > box.GetMax().y && pointC.y > box.GetMax().y ) return true;
	if( pointA.z > box.GetMax().z && pointB.z > box.GetMax().z && pointC.z > box.GetMax().z ) return true;
	if( pointA.x < box.GetMin().x && pointB.x < box.GetMin().x && pointC.x < box.GetMin().x ) return true;
	if( pointA.y < box.GetMin().y && pointB.y < box.GetMin().y && pointC.y < box.GetMin().y ) return true;
	if( pointA.z < box.GetMin().z && pointB.z < box.GetMin().z && pointC.z < box.GetMin().z ) return true;
	return false;
}

inline Vector Triangle::GetClosestPoint( const Vector& point ) const
{
	Vector ab = pointB - pointA;
	Vector ac = pointC - pointA;
	Vector ap = point - pointA;
	float d1 = ab.Dot(ap);
	float d2 = ac.Dot(ap);
	if (d1 <= 0.0f && d2 <= 0.0f)
		return pointA;
	
	Vector bp = point - pointB;
	float d3 = ab.Dot(bp);
	float d4 = ac.Dot(bp);
	if (d3 >= 0.0f && d4 <= d3)
		return pointB;
	
	float vc = (d1*d4) - (d3*d2);
	if( vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f )
	{
		float v = d1 / (d1 - d3);
		return pointA + (ab * v);
	}
	
	Vector cp = point - pointC;
	float d5 = ab.Dot(cp);
	float d6 = ac.Dot(cp);
	if (d6 >= 0.0f && d5 <= d6)
		return pointC;
	float vb = (d5*d2) - (d1*d6);
	if( vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f )
	{
		float w = d2 / (d2 - d6);
		return pointA + (ac * w);
	}
	float va =( d3*d6) - (d5*d4);
	if( va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f )
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return pointB + ((pointC - pointB) * w);
	}
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	return pointA + (ab * v) + (ac * w);
}

inline bool Triangle::IsPointInside( const Vector& point ) const
{
	Vector ab = pointB - pointA;
	Vector ac = pointA - pointC;
	Vector cb = pointC - pointB;
	Vector normal = ab && ac;
	
	Vector _ab = normal && ab;
	Vector _ac = normal && ac;
	Vector _cb = normal && cb;
	
	if( _ab.Dot( point - pointA ) * _ab.Dot( cb ) >= 0.0f )
		if( _ac.Dot( point - pointA ) * _ac.Dot( ab ) >= 0.0f )
			if( _cb.Dot( point - pointC ) * _cb.Dot( ac ) >= 0.0f )
				return true;
	return false;
	
	/*
	Vector p_ = p - pointA;
	float x = ( pointB - pointA ).Dot( p_ );
	float y = ( pointC - pointA ).Dot( p_ );
	float z = ( pointC - pointB ).Dot( p - pointB );
	
	if( x + y < 1.000001f )
		if( y + z > 1.000001f )
			if( z - x < 0.000001f )
				return true;
	return false;
	*/
	
	/*
	if( ( pointB - pointA ).Dot( p - pointA ) + ( pointC - pointA ).Dot( p - pointA ) < 1.000001f )
		if( ( pointA - pointB ).Dot( p - pointB ) + ( pointC - pointB ).Dot( p - pointB ) < 1.000001f )
			if( ( pointA - pointC ).Dot( p - pointC ) + ( pointB - pointC ).Dot( p - pointC ) < 1.000001f )
				return true;
	return false;
	*/
	
	/*
	Vector p = point - pointA;
	float x = ( pointB - pointA ).Dot( p );
	float y = ( pointC - pointA ).Dot( p );
	
	if( x > -0.000001f )
		if( y > -0.000001f )
			return y + x < 1.000001f;
	return false;
	*/
	
	/*
	const Vector a = pointC - pointA;
	const Vector b = pointB - pointA;
	const Vector c = point - pointA;

	const float dotAA = a.Dot( a );
	const float dotAB = a.Dot( b );
	const float dotAC = a.Dot( c );
	const float dotBB = b.Dot( b );
	const float dotBC = b.Dot( c );

	const float invDenom =  1/(dotAA * dotBB - dotAB * dotAB);
	const float u = (dotBB * dotAC - dotAB * dotBC) * invDenom;
	const float v = (dotAA * dotBC - dotAB * dotAC ) * invDenom;

	return (u > -ROUNDING_ERROR) && (v >= 0) && (u + v < 1+ROUNDING_ERROR);
	*/
}

inline bool Triangle::GetIntersectionWithLine( const Vector& begin, const Vector& end, Vector& intersection ) const
{
	if( GetIntersectionOfPlaneWithLine( begin, end, intersection ) )
		return IsPointInside( intersection );
	return false;
}

inline bool Triangle::GetIntersectionOfPlaneWithLine( const Vector& begin, const Vector& end, Vector& intersection ) const
{
	Vector normal = GetNormal();
	Vector direction = end - begin;
	float dot = normal.Dot( direction );
	
	if( dot == 0.0f )
		return false;
	
	float t = normal.Dot( pointA - begin ) / ( dot );
	
	if( t < 0.0f || t > 1.0f )
		return false;
	
	intersection = begin + ( direction * t );
	return true;
}

inline void Triangle::GetMaxMinWithVector( const Vector& dir, float& tmin, float& tmax ) const
{
	float temp;
	tmin = dir.Dot(pointA);
	tmax = tmin;
	temp = dir.Dot(pointB);
	if( temp < tmin )
		tmin = temp;
	else if( temp > tmax )
		tmax = temp;
	temp = dir.Dot(pointC);
	if( temp < tmin )
		tmin = temp;
	else if( temp > tax )
		tmax = temp;
}

inline void Triangle::EdgesDirection( Vector& ab, Vector& bc, Vector& ca ) const
{
	ab = b-a;
	bc = c-b;
	ca = a-c;
}

inline Vector Triangle::GetNormal() const
{
	return (pointB-pointA) && (pointC-pointA).Versor();
}

inline Vector Triangle::GetNormalFast() const
{
	return (pointB-pointA) && (pointC-pointA);
}

inline bool Triangle::IsFrontFacing( const Vector& direction ) const
{
	return GetNormalFast().Dot( direction ) <= 0.0f;
}

inline float Triangle::GetArea() const
{
	return ( (pointB - pointA) && (pointC - pointA) ).Length() * 0.5f;
}

inline void Triangle::Set( const Vector& a, const Vector& b, const Vector& c )
{
	pointA = a;
	pointB = b;
	pointC = c;
}

inline bool Triangle::IsOnSameSide( const Vector& p1, const Vector& p2, const Vector& a, const Vector& b ) const
{
	Vector bminusa = b - a;
	Vector cp1 = bminusa && (p1-a);
	Vector cp2 = bminusa && (p2-a);
	float res = cp1.Dot( cp2 );
	if( res < 0.0f )
	{
		cp1 = bminusa.Versor() && ((p1-a).Versor());
		if( cp1.x > -ROUNDING_ERROR && cp1.x < ROUNDING_ERROR && cp1.y > -ROUNDING_ERROR && cp1.y < ROUNDING_ERROR && cp1.z > -ROUNDING_ERROR && cp1.z < ROUNDING_ERROR )
			return true;
		return false;
	}
	return true;
}

Triangle::Triangle()
{
	pointA.Set( 0.0f, 0.0f, 0.0f );
	pointC = pointB = pointA;
}

Triangle::Triangle( const Vector& a, const Vector& b, const Vector& c )
{
	pointA = a;
	pointB = b;
	pointC = c;
}

Triangle::~Triangle()
{
	pointA.Set( 0.0f, 0.0f, 0.0f );
	pointC = pointB = pointA;
}

#endif

