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

#ifndef VMATRIX_H
#define VMATRIX_H

#include "Vector.h"

class VMatrix
{
private:
	
	float m[4][4];
	
public:
	
	inline VMatrix SetMatrix(
		const float src00, const float src01, const float src02, const float src03,
		const float src10, const float src11, const float src12, const float src13,
		const float src20, const float src21, const float src22, const float src23,
		const float src30, const float src31, const float src32, const float src33 );
	inline VMatrix SetMatrix( const VMatrix& src );
	inline VMatrix SetMatrix( const float **src );
	
	inline VMatrix& InitEmpty();
	
	inline VMatrix& operator = ( const VMatrix& src );
	
	inline bool operator == ( const VMatrix& src ) const;
	inline bool operator != ( const VMatrix& src ) const;
	inline bool operator < ( const VMatrix& src ) const;
	inline bool operator > ( const VMatrix& src ) const;
	inline bool operator <= ( const VMatrix& src ) const;
	inline bool operator >= ( const VMatrix& src ) const;
	
	inline VMatrix& operator += ( const Vector& src );
	inline VMatrix operator * ( const VMatrix& src ) const;
	inline VMatrix& operator *= ( const VMatrix& src );
	inline Vector operator * ( const Vector& src ) const;
	inline VMatrix operator * ( const float src ) const;
	inline VMatrix& operator *= ( const float src );
	
	inline VMatrix& Translate( const Vector& src );
	inline VMatrix& RotateX( const float angle );
	inline VMatrix& RotateY( const float angle );
	inline VMatrix& RotateZ( const float angle );
	inline VMatrix& Scale( const Vector& src );
	inline VMatrix& Scale( const float src );
	
	inline Vector GetVertex( const Vector& src ) const;
	inline Vector GetVertexBack( const Vector& src ) const;
	
	inline VMatrix GetReverse() const;
	inline VMatrix& Reverse();
	
	inline float GetDet() const;
	
	VMatrix();
};

#endif

