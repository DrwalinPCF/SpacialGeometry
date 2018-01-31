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

#ifndef MATH_H
#define MATH_H

#include "cmath"
#include "Vector.h"
#include "Quat.h"

namespace Math
{
	const float pi = 3.14159265359f;
	inline float Min( const float a, const float b );
	inline float Max( const float a, const float b );
	inline Vector Min( const Vector& a, const Vector& b );
	inline Vector Max( const Vector& a, const Vector& b );
	inline float Abs( const float a );
	inline unsigned long long int Log( const unsigned long long int base, const unsigned long long int a );
	inline float Log( const float base, const float a );							// returns not the best approximation: abs(log(base,a) - Math::Log(base,a)) <~ 0.2
	inline float Interpolate( const float a, const float b, const float t );		// 0 <= t <= 1, sin
	inline Vector Interpolate( const Vector& a, const Vector& b, const float t );		// 0 <= t <= 1, sin
	inline Vector GetForwardVector( const Vector& rotator );
	inline Vector GetLeftVector( const Vector& rotator );
	inline Vector GetUpVector( const Vector& rotator );
	inline float Clamp( const float a, const float min, const float max );
	inline float Sqrt( const float a );
	inline float SaveAcos( const float a );
};

#endif

