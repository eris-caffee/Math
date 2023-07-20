#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vector.h"

#include <cmath>
#include <cstring>
#include <string>
#include <sstream>

namespace arda 
   {
   namespace Math
      {
      //////////////////////////////////////////////////////////////////////////
      // Maxtrices
      //
      // Supported operations on matrices
      //
      // []
      //     If you have a Matrix named m you can access it's member elements as
      //     m[0], m[1], m[2], etc.  The indexing is COLUMN MAJOR.  So for a 2x2
      //     matrix, m[0] and m[1] are the elements of the first column, not the
      //     first row.
      // == != + += - -=
      //     Defined for operations on two matrices of the same type.
      //     TODO Is there a better way to do this?  With integer types this is fine,
      //     but with floating point types this == and != are really worthless.  Is it possible to 
      //     create variant methods in a template class that vary by the type?  Or do I just have
      //     to suck it up and create type specific external functions for comparing Matrices?
      // * *= / /=
      //     Defined for scalar multiplication/division with int, float, and double.
      //     * is defined as a standalone template operator for the scalar * Matrix
      //     form.
      // * *=
      //     Also defined for Matrix * Matrix
      //
      // assign()          Assign the value of one matrix to another.
      // getcol()          Returns the vector that is column n of the matrix.
      // to_string()       Returns a printable string representation of the matrix.
      // setcol()          Set the vector that is column n of the matrix.
      //                   Overloaded so that you can set from a vector or from
      //                   specific values.
      // setidentity()     Sets a matrix to the identity matrix.
      //
      //
      //
      // The following are functions, not class methods.  This is because I think
      // that the notation det(m) and transpose(m), for example, is more natural
      // to write and read than m.det() and m.transpose().  Using functional
      // notation just more naturally mimics the standard mathematical notation.
      //
      // det()             Calculates the determinant of a matrix.
      // transpose()       Returns the transpose of a matrix.
      
      //////////////////////////////////////////////////////////////////////////
      template <typename T> 
      class Matrix22
	 {
	 public:
	 T m[4];

	 // Constructors
	 Matrix22() {}
	 explicit Matrix22(T a) { m[0] = m[1] = m[2] = m[3] = a; }
	 Matrix22(T a0, T a1, T a2, T a3) 
	    { 
	    m[0] = a0; m[2] = a2;
	    m[1] = a1; m[3] = a3; 
	    } 

	 // Array indexing
	 // Remember: column major order is used.
	 inline T& operator[](unsigned int const i) 
	    { assert (i<4); return m[i]; }
	 inline T operator[](unsigned int const i) const
	    { assert (i<4); return m[i]; }

	 // Assignment
	 inline Matrix22<T>& operator=(Matrix22<T> const & m2)
	    { 
	    m[0] = m2[0]; m[2] = m2[2]; 
	    m[1] = m2[1]; m[3] = m2[3]; 
	    return *this;
	    }
	 inline Matrix22<T>& assign(T const a0, T const a1, 
				    T const a2, T const a3)
	    { 
	    m[0] = a0; m[2] = a2;
	    m[1] = a1; m[3] = a3; 
	    return *this;
	    }

	 // Comparison
	 inline bool operator==(Matrix22<T> const & m2) const
	    {
	    return  
		  m[0] == m2[0] && m[2] == m2[2] &&
		  m[1] == m2[1] && m[3] == m2[3]; 
	    }
	 inline bool operator!=(Matrix22<T> const & m2) const
	    { return ! (*this == m2); } 

	 // Matrix addition
	 inline Matrix22<T>& operator+=(Matrix22<T> const & m2)
	    {
	    m[0] += m2[0]; m[2] += m2[2]; 
	    m[1] += m2[1]; m[3] += m2[3];
	    return *this;
	    }
	 inline Matrix22<T> operator+(Matrix22<T> const & m2) const
	    { return Matrix22<T>(*this) += m2; }

	 // Matrix subtraction
	 inline Matrix22<T>& operator-=(Matrix22<T> const & m2)
	    {
	    m[0] -= m2[0]; m[2] -= m2[2]; 
	    m[1] -= m2[1]; m[3] -= m2[3];
	    return *this;
	    }
	 inline Matrix22<T> operator-(Matrix22<T> const & m2) const
	    { return Matrix22<T>(*this) -= m2; }
      
	 // Scalar multiplication
	 inline Matrix22<T>& operator*=(int const a)
	    {
	    m[0] *= a; m[2] *= a;
	    m[1] *= a; m[3] *= a;
	    return *this;
	    }
	 inline Matrix22<T>& operator*=(float const a)
	    {
	    m[0] *= a; m[2] *= a;
	    m[1] *= a; m[3] *= a;
	    return *this;
	    }
	 inline Matrix22<T>& operator*=(double const a)
	    {
	    m[0] *= a; m[2] *= a;
	    m[1] *= a; m[3] *= a;
	    return *this;
	    }

	 // Scalar division
	 inline Matrix22<T>& operator/=(int const a)
	    {
	    assert(a!=0);
	    m[0] /= a; m[2] /= a;
	    m[1] /= a; m[3] /= a;
	    return *this;
	    }
	 inline Matrix22<T>& operator/=(float const a)
	    {
	    assert(a!=0);
	    m[0] /= a; m[2] /= a;
	    m[1] /= a; m[3] /= a;
	    return *this;
	    }
	 inline Matrix22<T>& operator/=(double const a)
	    {
	    assert(a!=0);
	    m[0] /= a; m[2] /= a;
	    m[1] /= a; m[3] /= a;
	    return *this;
	    }
	 inline Matrix22<T> operator/(int const a)
	    { return Matrix22<T>(*this) /= a; }
	 inline Matrix22<T> operator/(float const a)
	    { return Matrix22<T>(*this) /= a; }
	 inline Matrix22<T> operator/(double const a)
	    { return Matrix22<T>(*this) /= a; }

	 // Matrix multiplication
	 // Not sure if this should be inlined at all.  Sure the compiler will
	 // probably ignore the inline request here, but maybe it won't and maybe
	 // that would be bad.  Needs real testing.
	 inline Matrix22<T>& operator*=(Matrix22<T> const & m2)
	    {
	    const int size=2;
	    Matrix22<T> mres(0);
	    int i, j, k;
	    for (i=0; i<size; ++i)
	       for (j=0; j<size; ++j)
		  for (k=0; k<size; ++k)
		     mres[size*i+j] += (*this)[size*k+j] * m2[size*i+k];
	    *this = mres;
	    return *this;
	    }
	 inline Matrix22<T> operator*(Matrix22<T> const & m2) const
	    { return Matrix22<T>(*this) *= m2; }


	 inline Vector2<T> getcol(unsigned int const i) const
	    {
	    assert(i<2);
	    int const size=2;
	    return Vector2<T>(m[i*size], m[i*size+1]);
	    }

	 inline Vector2<T> getrow(unsigned int const i) const
	    {
	    assert(i<2);
	    int const size=2;
	    return Vector2<T>(m[i], m[i+size]);
	    }
	 
	 inline Matrix22<T>& setcol(unsigned int const i, Vector2<T> const & v)
	    {
	    assert(i<2);
	    int const size=2;
	    m[i*size] = v[0];
	    m[i*size+1] = v[1];
	    return *this;
	    }

	 inline Matrix22<T>& setcol(unsigned int const i, T const a, T const b)
	    {
	    assert(i<2);
	    const int size=2;
	    m[i*size] = a;
	    m[i*size+1] = b;
	    return *this;
	    }

	 inline Matrix22<T>& setrow(unsigned int const i, Vector2<T> const & v)
	    {
	    assert(i<2);
	    int const size=2;
	    m[i] = v[0];
	    m[i+size] = v[1];
	    return *this;
	    }

	 inline Matrix22<T>& setrow(unsigned int const i, T const a, T const b)
	    {
	    assert(i<2);
	    int const size=2;
	    m[i] = a;
	    m[i+size] = b;
	    return *this;
	    }

	 std::string to_string(void) const;

	 inline Matrix22<T>& setidentity()
	    {
	    memset(m, 0, sizeof(m));
	    m[0] = m[3] = T(1);
	    return *this;
	    }

	 };

      // Scalar multiplication continued
      template <typename T> 
      inline Matrix22<T> operator*(Matrix22<T> const & m, int const a)
	 { return Matrix22<T>(m) *= a; }

      template <typename T> 
      inline Matrix22<T> operator*(int const a, Matrix22<T> const & m)
	 { return Matrix22<T>(m) *= a; }

      template <typename T> 
      inline Matrix22<T> operator*(Matrix22<T> const & m, float const a)
	 { return Matrix22<T>(m) *= a; }

      template <typename T> 
      inline Matrix22<T> operator*(float const a, Matrix22<T> const & m)
	 { return Matrix22<T>(m) *= a; }

      template <typename T> 
      inline Matrix22<T> operator*(Matrix22<T> const & m, double const a)
	 { return Matrix22<T>(m) *= a; }

      template <typename T> 
      inline Matrix22<T> operator*(double const a, Matrix22<T> const & m)
	 { return Matrix22<T>(m) *= a; }




      //////////////////////////////////////////////////////////////////////////
      template <typename T> 
      class Matrix33
	 {
	 public:
	 T m[9];

	 // Constructors
	 Matrix33() {}
	 explicit Matrix33(T a) 
	    { 
	    // TODO:  Is this really more efficient than memset?
	    m[0] = m[1] = m[2] = m[3] = m[4] = m[5] = m[6] = m[7] = m[8] = a;
	    }
	 Matrix33(T a0, T a1, T a2, 
		  T a3, T a4, T a5, 
		  T a6, T a7, T a8) 
	    { 
	    m[0] = a0; m[3] = a3; m[6] = a6;
	    m[1] = a1; m[4] = a4; m[7] = a7;
	    m[2] = a2; m[5] = a5; m[8] = a8;
	    } 

	 // Array indexing
	 // Remember: column major order is used.
	 inline T& operator[](unsigned int const i) 
	    { assert (i<9); return m[i]; }
	 inline T operator[](unsigned int const i) const
	    { assert (i<9); return m[i]; }

	 // Assignment
	 inline Matrix33<T>& operator=(Matrix33<T> const & m2)
	    { 
	    m[0] = m2[0]; m[3] = m2[3]; m[6] = m2[6];
	    m[1] = m2[1]; m[4] = m2[4]; m[7] = m2[7];
	    m[2] = m2[2]; m[5] = m2[5]; m[8] = m2[8];
	    return *this;
	    }
	 inline Matrix33<T>& assign(T const a0, T const a1, T const a2, 
				    T const a3, T const a4, T const a5, 
				    T const a6, T const a7, T const a8) 
	    { 
	    m[0] = a0; m[3] = a3; m[6] = a6;
	    m[1] = a1; m[4] = a4; m[7] = a7;
	    m[2] = a2; m[5] = a5; m[8] = a8;
	    return *this;
	    }

	 // Comparison
	 inline bool operator==(Matrix33<T> const & m2) const
	    {
	    return  
		  m[0] == m2[0] && m[3] == m2[3] && m[6] == m2[6] &&
		  m[1] == m2[1] && m[4] == m2[4] && m[7] == m2[7] &&
		  m[2] == m2[2] && m[5] == m2[5] && m[8] == m2[8];
	    }
	 inline bool operator!=(Matrix33<T> const & m2) const
	    { return ! (*this == m2); } 

	 // Matrix addition
	 inline Matrix33<T>& operator+=(Matrix33<T> const & m2)
	    {
	    m[0] += m2[0]; m[3] += m2[3]; m[6] += m2[6];
	    m[1] += m2[1]; m[4] += m2[4]; m[7] += m2[7];
	    m[2] += m2[2]; m[5] += m2[5]; m[8] += m2[8];
	    return *this;
	    }
	 inline Matrix33<T> operator+(Matrix33<T> const & m2) const
	    { return Matrix33<T>(*this) += m2; }

	 // Matrix subtraction
	 inline Matrix33<T>& operator-=(Matrix33<T> const & m2)
	    {
	    m[0] -= m2[0]; m[3] -= m2[3]; m[6] -= m2[6];
	    m[1] -= m2[1]; m[4] -= m2[4]; m[7] -= m2[7];
	    m[2] -= m2[2]; m[5] -= m2[5]; m[8] -= m2[8];
	    return *this;
	    }
	 inline Matrix33<T> operator-(Matrix33<T> const & m2) const
	    { return Matrix33<T>(*this) -= m2; }
      
	 // Scalar multiplication
	 inline Matrix33<T>& operator*=(int const a)
	    {
	    m[0] *= a; m[3] *= a; m[6] *= a;
	    m[1] *= a; m[4] *= a; m[7] *= a;
	    m[2] *= a; m[5] *= a; m[8] *= a;
	    return *this;
	    }
	 inline Matrix33<T>& operator*=(float const a)
	    {
	    m[0] *= a; m[3] *= a; m[6] *= a;
	    m[1] *= a; m[4] *= a; m[7] *= a;
	    m[2] *= a; m[5] *= a; m[8] *= a;
	    return *this;
	    }
	 inline Matrix33<T>& operator*=(double const a)
	    {
	    m[0] *= a; m[3] *= a; m[6] *= a;
	    m[1] *= a; m[4] *= a; m[7] *= a;
	    m[2] *= a; m[5] *= a; m[8] *= a;
	    return *this;
	    }

	 // Scalar division
	 inline Matrix33<T>& operator/=(int const a)
	    {
	    assert(a!=0);
	    m[0] /= a; m[3] /= a; m[6] /= a;
	    m[1] /= a; m[4] /= a; m[7] /= a;
	    m[2] /= a; m[5] /= a; m[8] /= a;
	    return *this;
	    }
	 inline Matrix33<T>& operator/=(float const a)
	    {
	    assert(a!=0);
	    m[0] /= a; m[3] /= a; m[6] /= a;
	    m[1] /= a; m[4] /= a; m[7] /= a;
	    m[2] /= a; m[5] /= a; m[8] /= a;
	    return *this;
	    }
	 inline Matrix33<T>& operator/=(double const a)
	    {
	    assert(a!=0);
	    m[0] /= a; m[3] /= a; m[6] /= a;
	    m[1] /= a; m[4] /= a; m[7] /= a;
	    m[2] /= a; m[5] /= a; m[8] /= a;
	    return *this;
	    }
	 inline Matrix33<T> operator/(int const a)
	    { return Matrix33<T>(*this) /= a; }
	 inline Matrix33<T> operator/(float const a)
	    { return Matrix33<T>(*this) /= a; }
	 inline Matrix33<T> operator/(double const a)
	    { return Matrix33<T>(*this) /= a; }

	 // Matrix multiplication
	 // Not sure if this should be inlined at all.  Sure the compiler will
	 // probably ignore the inline request here, but maybe it won't and maybe
	 // that would be bad.  Needs real testing.
	 inline Matrix33<T>& operator*=(Matrix33<T> const & m2)
	    {
	    const int size=3;
	    Matrix33<T> mres(0);
	    int i, j, k;
	    for (i=0; i<size; ++i)
	       for (j=0; j<size; ++j)
		  for (k=0; k<size; ++k)
		     mres[size*i+j] += (*this)[size*k+j] * m2[size*i+k];
	    *this = mres;
	    return *this;
	    }
	 inline Matrix33<T> operator*(Matrix33<T> const & m2) const
	    { return Matrix33<T>(*this) *= m2; }


	 inline Vector3<T> getcol(unsigned int const i) const
	    {
	    assert(i<3);
	    const int size=3;
	    return Vector3<T>(m[i*size], m[i*size+1], m[i*size+2]);
	    }

	 inline Vector3<T> getrow(unsigned int const i) const
	    {
	    assert(i<3);
	    const int size=3;
	    return Vector3<T>(m[i], m[i+size], m[i+2*size]);
	    }
	 
	 inline Matrix33<T>& setcol(unsigned int const i, Vector3<T> const & v)
	    {
	    assert(i<3);
	    const int size=3;
	    m[i*size] = v[0];
	    m[i*size+1] = v[1];
	    m[i*size+2] = v[2];
	    return *this;
	    }

	 inline Matrix33<T>& setcol(unsigned int const i, 
				    T const a0, T const a1, T const a2)
	    {
	    assert(i<3);
	    const int size=3;
	    m[i*size] = a0;
	    m[i*size+1] = a1;
	    m[i*size+2] = a2;
	    return *this;
	    }

	 inline Matrix33<T>& setrow(unsigned int const i, Vector3<T> const & v)
	    {
	    assert(i<3);
	    const int size=3;
	    m[i] = v[0];
	    m[i+size] = v[1];
	    m[i+2*size] = v[2];
	    return *this;
	    }

	 inline Matrix33<T>& setrow(unsigned int const i, 
				    T const a0, T const a1, T const a2)
	    {
	    assert(i<3);
	    const int size=3;
	    m[i] = a0;
	    m[i+size] = a1;
	    m[i+2*size] = a2;
	    return *this;
	    }

	 std::string to_string(void) const;

	 inline Matrix33<T>& setidentity()
	    {
	    memset(m, 0, sizeof(m));
	    m[0] = m[4] = m[8] = T(1);
	    return *this;
	    }

	 };

      // Scalar multiplication continued
      template <typename T> 
      inline Matrix33<T> operator*(Matrix33<T> const & m, int const a)
	 { return Matrix33<T>(m) *= a; }

      template <typename T> 
      inline Matrix33<T> operator*(int const a, Matrix33<T> const & m)
	 { return Matrix33<T>(m) *= a; }

      template <typename T> 
      inline Matrix33<T> operator*(Matrix33<T> const & m, float const a)
	 { return Matrix33<T>(m) *= a; }

      template <typename T> 
      inline Matrix33<T> operator*(float const a, Matrix33<T> const & m)
	 { return Matrix33<T>(m) *= a; }

      template <typename T> 
      inline Matrix33<T> operator*(Matrix33<T> const & m, double const a)
	 { return Matrix33<T>(m) *= a; }

      template <typename T> 
      inline Matrix33<T> operator*(double const a, Matrix33<T> const & m)
	 { return Matrix33<T>(m) *= a; }




      //////////////////////////////////////////////////////////////////////////
      template <typename T> 
      class Matrix44
	 {
	 public:
	 T m[16];

	 // Constructors
	 Matrix44() {}
	 explicit Matrix44(T a) 
	    { 
	    // TODO:  Is this really more efficient than memset?
	    m[0] = m[1] = m[2] = m[3] = m[4] = m[5] = m[6] = m[7] = m[8] = 
		  m[9] = m[10] = m[11] = m[12] = m[13] = m[14] = m[15] = a;
	    }
	 Matrix44(T a0, T a1, T a2, T a3, 
		  T a4, T a5, T a6, T a7, 
		  T a8, T a9, T a10, T a11,
		  T a12, T a13, T a14, T a15) 
	    { 
	    m[0] = a0; m[4] = a4;  m[8] = a8;  m[12] = a12;
	    m[1] = a1; m[5] = a5;  m[9] = a9;  m[13] = a13;
	    m[2] = a2; m[6] = a6; m[10] = a10; m[14] = a14;
	    m[3] = a3; m[7] = a7; m[11] = a11; m[15] = a15;
	    } 

	 // Array indexing
	 // Remember: column major order is used.
	 inline T& operator[](unsigned int const i) 
	    { assert (i<16); return m[i]; }
	 inline T operator[](unsigned int const i) const
	    { assert (i<16); return m[i]; }

	 // Assignment
	 inline Matrix44<T>& operator=(Matrix44<T> const & m2)
	    { 
	    m[0] = m2[0]; m[4] = m2[4];  m[8] = m2[8];  m[12] = m2[12];
	    m[1] = m2[1]; m[5] = m2[5];  m[9] = m2[9];  m[13] = m2[13];
	    m[2] = m2[2]; m[6] = m2[6]; m[10] = m2[10]; m[14] = m2[14];
	    m[3] = m2[3]; m[7] = m2[7]; m[11] = m2[11]; m[15] = m2[15];
	    return *this;
	    }
	 inline Matrix44<T>& assign(T const a0,  T const a1,  T const a2,  T const a3, 
				    T const a4,  T const a5,  T const a6,  T const a7, 
				    T const a8,  T const a9,  T const a10, T const a11,
				    T const a12, T const a13, T const a14, T const a15)
	    { 
	    m[0] = a0; m[4] = a4;  m[8] = a8;  m[12] = a12;
	    m[1] = a1; m[5] = a5;  m[9] = a9;  m[13] = a13;
	    m[2] = a2; m[6] = a6; m[10] = a10; m[14] = a14;
	    m[3] = a3; m[7] = a7; m[11] = a11; m[15] = a15;
	    return *this;
	    }

	 // Comparison
	 inline bool operator==(Matrix44<T> const & m2) const
	    {
	    // TODO: Should this use memcmp?
	    return  
		  m[0] == m2[0] && m[4] == m2[4] &&  m[8] == m2[8] &&  m[12] == m2[12] &&
		  m[1] == m2[1] && m[5] == m2[5] &&  m[9] == m2[9] &&  m[13] == m2[13] &&
		  m[2] == m2[2] && m[6] == m2[6] && m[10] == m2[10] && m[14] == m2[14] &&
		  m[3] == m2[3] && m[7] == m2[7] && m[11] == m2[11] && m[15] == m2[15];
	    }
	 inline bool operator!=(Matrix44<T> const & m2) const
	    { return ! (*this == m2); } 

	 // Matrix addition
	 inline Matrix44<T>& operator+=(Matrix44<T> const & m2)
	    {
	    m[0] += m2[0]; m[4] += m2[4];  m[8] += m2[8];  m[12] += m2[12];
	    m[1] += m2[1]; m[5] += m2[5];  m[9] += m2[9];  m[13] += m2[13];
	    m[2] += m2[2]; m[6] += m2[6]; m[10] += m2[10]; m[14] += m2[14];
	    m[3] += m2[3]; m[7] += m2[7]; m[11] += m2[11]; m[15] += m2[15];
	    return *this;
	    }
	 inline Matrix44<T> operator+(Matrix44<T> const & m2) const
	    { return Matrix44<T>(*this) += m2; }

	 // Matrix subtraction
	 inline Matrix44<T>& operator-=(Matrix44<T> const & m2)
	    {
	    m[0] -= m2[0]; m[4] -= m2[4];  m[8] -= m2[8];  m[12] -= m2[12];
	    m[1] -= m2[1]; m[5] -= m2[5];  m[9] -= m2[9];  m[13] -= m2[13];
	    m[2] -= m2[2]; m[6] -= m2[6]; m[10] -= m2[10]; m[14] -= m2[14];
	    m[3] -= m2[3]; m[7] -= m2[7]; m[11] -= m2[11]; m[15] -= m2[15];
	    return *this;
	    }
	 inline Matrix44<T> operator-(Matrix44<T> const & m2) const
	    { return Matrix44<T>(*this) -= m2; }
      
	 // Scalar multiplication
	 inline Matrix44<T>& operator*=(int const a)
	    {
	    m[0] *= a; m[4] *= a;  m[8] *= a; m[12] *= a;
	    m[1] *= a; m[5] *= a;  m[9] *= a; m[13] *= a;
	    m[2] *= a; m[6] *= a; m[10] *= a; m[14] *= a;
	    m[3] *= a; m[7] *= a; m[11] *= a; m[15] *= a;
	    return *this;
	    }
	 inline Matrix44<T>& operator*=(float const a)
	    {
	    m[0] *= a; m[4] *= a;  m[8] *= a; m[12] *= a;
	    m[1] *= a; m[5] *= a;  m[9] *= a; m[13] *= a;
	    m[2] *= a; m[6] *= a; m[10] *= a; m[14] *= a;
	    m[3] *= a; m[7] *= a; m[11] *= a; m[15] *= a;
	    return *this;
	    }
	 inline Matrix44<T>& operator*=(double const a)
	    {
	    m[0] *= a; m[4] *= a;  m[8] *= a; m[12] *= a;
	    m[1] *= a; m[5] *= a;  m[9] *= a; m[13] *= a;
	    m[2] *= a; m[6] *= a; m[10] *= a; m[14] *= a;
	    m[3] *= a; m[7] *= a; m[11] *= a; m[15] *= a;
	    return *this;
	    }

	 // Scalar division
	 inline Matrix44<T>& operator/=(int const a)
	    {
	    assert(a!=0);
	    m[0] /= a; m[4] /= a;  m[8] /= a; m[12] /= a;
	    m[1] /= a; m[5] /= a;  m[9] /= a; m[13] /= a;
	    m[2] /= a; m[6] /= a; m[10] /= a; m[14] /= a;
	    m[3] /= a; m[7] /= a; m[11] /= a; m[15] /= a;
	    return *this;
	    }
	 inline Matrix44<T>& operator/=(float const a)
	    {
	    assert(a!=0);
	    m[0] /= a; m[4] /= a;  m[8] /= a; m[12] /= a;
	    m[1] /= a; m[5] /= a;  m[9] /= a; m[13] /= a;
	    m[2] /= a; m[6] /= a; m[10] /= a; m[14] /= a;
	    m[3] /= a; m[7] /= a; m[11] /= a; m[15] /= a;
	    return *this;
	    }
	 inline Matrix44<T>& operator/=(double const a)
	    {
	    assert(a!=0);
	    m[0] /= a; m[4] /= a;  m[8] /= a; m[12] /= a;
	    m[1] /= a; m[5] /= a;  m[9] /= a; m[13] /= a;
	    m[2] /= a; m[6] /= a; m[10] /= a; m[14] /= a;
	    m[3] /= a; m[7] /= a; m[11] /= a; m[15] /= a;
	    return *this;
	    }
	 inline Matrix44<T> operator/(int const a)
	    { return Matrix44<T>(*this) /= a; }
	 inline Matrix44<T> operator/(float const a)
	    { return Matrix44<T>(*this) /= a; }
	 inline Matrix44<T> operator/(double const a)
	    { return Matrix44<T>(*this) /= a; }

	 // Matrix multiplication
	 // Not sure if this should be inlined at all.  Sure the compiler will
	 // probably ignore the inline request here, but maybe it won't and maybe
	 // that would be bad.  Needs real testing.
	 inline Matrix44<T>& operator*=(Matrix44<T> const & m2)
	    {
	    const int size=4;
	    Matrix44<T> mres(0);
	    int i, j, k;
	    for (i=0; i<size; ++i)
	       for (j=0; j<size; ++j)
		  for (k=0; k<size; ++k)
		     mres[size*i+j] += (*this)[size*k+j] * m2[size*i+k];
	    *this = mres;
	    return *this;
	    }
	 inline Matrix44<T> operator*(Matrix44<T> const & m2) const
	    { return Matrix44<T>(*this) *= m2; }


	 inline Vector4<T> getcol(unsigned int const i) const
	    {
	    assert(i<4);
	    const int size=4;
	    return Vector4<T>(m[i*size], m[i*size+1], m[i*size+2], m[i*size+3]);
	    }

	 inline Vector4<T> getrow(unsigned int const i) const
	    {
	    assert(i<4);
	    const int size=4;
	    return Vector4<T>(m[i], m[i+size], m[i+2*size], m[i+3*size]);
	    }
	 
	 inline Matrix44<T>& setcol(unsigned int const i, Vector4<T> const & v)
	    {
	    assert(i<4);
	    const int size=4;
	    m[i*size] = v[0];
	    m[i*size+1] = v[1];
	    m[i*size+2] = v[2];
	    m[i*size+3] = v[3];
	    return *this;
	    }

	 inline Matrix44<T>& setcol(unsigned int const i, 
				    T const a0, T const a1, T const a2, T const a3)
	    {
	    assert(i<4);
	    const int size=4;
	    m[i*size] = a0;
	    m[i*size+1] = a1;
	    m[i*size+2] = a2;
	    m[i*size+3] = a3;
	    return *this;
	    }

	 inline Matrix44<T>& setrow(unsigned int const i, Vector4<T> const & v)
	    {
	    assert(i<4);
	    const int size=4;
	    m[i] = v[0];
	    m[i+size] = v[1];
	    m[i+2*size] = v[2];
	    m[i+3*size] = v[3];
	    return *this;
	    }

	 inline Matrix44<T>& setrow(unsigned int const i, 
				    T const a0, T const a1, T const a2, T const a3)
	    {
	    assert(i<4);
	    const int size=4;
	    m[i] = a0;
	    m[i+size] = a1;
	    m[i+2*size] = a2;
	    m[i+3*size] = a3;
	    return *this;
	    }

	 std::string to_string(void) const;

	 inline Matrix44<T>& setidentity()
	    {
	    memset(m, 0, sizeof(m));
	    m[0] = m[5] = m[10] = m[15] = T(1);
	    return *this;
	    }

	 };

      // Scalar multiplication continued
      template <typename T> 
      inline Matrix44<T> operator*(Matrix44<T> const & m, int const a)
	 { return Matrix44<T>(m) *= a; }

      template <typename T> 
      inline Matrix44<T> operator*(int const a, Matrix44<T> const & m)
	 { return Matrix44<T>(m) *= a; }

      template <typename T> 
      inline Matrix44<T> operator*(Matrix44<T> const & m, float const a)
	 { return Matrix44<T>(m) *= a; }

      template <typename T> 
      inline Matrix44<T> operator*(float const a, Matrix44<T> const & m)
	 { return Matrix44<T>(m) *= a; }

      template <typename T> 
      inline Matrix44<T> operator*(Matrix44<T> const & m, double const a)
	 { return Matrix44<T>(m) *= a; }

      template <typename T> 
      inline Matrix44<T> operator*(double const a, Matrix44<T> const & m)
	 { return Matrix44<T>(m) *= a; }




      //////////////////////////////////////////////////////////////////////////
      typedef Matrix22<int> Matrix22i;
      typedef Matrix22<float> Matrix22f;
      typedef Matrix22<double> Matrix22d;

      typedef Matrix33<int> Matrix33i;
      typedef Matrix33<float> Matrix33f;
      typedef Matrix33<double> Matrix33d;
      
      typedef Matrix44<int> Matrix44i;
      typedef Matrix44<float> Matrix44f;
      typedef Matrix44<double> Matrix44d;


      //////////////////////////////////////////////////////////////////////////
      // Matrix functions
      // TODO: The determinant functions suffer from some bad round off error.
      // Is it significant?  I don't know.  None of the other game engines
      // I've checked bother to do anything to calculate det more accurately.
      // So maybe it just doesn't matter enough for game purposes.

      template <typename T> 
      inline double det(Matrix22<T> const & m)
	 { 
	 return (double) (m[0] * m[3]) - (double) (m[1] * m[2]); 
	 }

      template <typename T> 
      inline Matrix22<T> transpose(Matrix22<T> const & m)
	 {
	 const int size=2;
	 Matrix22<T> mres(0);
	 int i, j;
	 for (i=0; i<size; ++i)
	    for (j=0; j<size; j++)
	       mres[size*i+j] = m[size*j+i];
	 return mres;
	 }

      template <typename T> 
      inline double det(Matrix33<T> const & m)
	 {
	 return   m[0] * ( (double) m[4] * m[8] - (double) m[5] * m[7])  
	       -  m[3] * ( (double) m[1] * m[8] - (double) m[2] * m[7]) 
	       +  m[6] * ( (double) m[1] * m[5] - (double) m[2] * m[4]);
	 }
      template <typename T> 
      inline Matrix33<T> transpose(Matrix33<T> const & m)
	 {
	 const int size=3;
	 Matrix33<T> mres(0);
	 int i, j;
	 for (i=0; i<size; ++i)
	    for (j=0; j<size; j++)
	       mres[size*i+j] = m[size*j+i];
	 return mres;
	 }

      template <typename T> 
      inline double det(Matrix44<T> const & m)
	 { 
	 return  m[0]  * (  m[5]  * (m[10] * m[15] - m[11] * m[14])
		          - m[9]  * (m[6]  * m[15] - m[7]  * m[14])
		          + m[13] * (m[6]  * m[11] - m[7]  * m[10]))
	       - m[4]  * (  m[1]  * (m[10] * m[15] - m[11] * m[14])
		          - m[9]  * (m[2]  * m[15] - m[3]  * m[14])
		          + m[13] * (m[2]  * m[11] - m[3]  * m[10]))
	       + m[8]  * (  m[1]  * (m[6]  * m[15] - m[7]  * m[14])
		          - m[5]  * (m[2]  * m[15] - m[3]  * m[14])
		          + m[13] * (m[2]  * m[7]  - m[3]  * m[6]))
	       + m[12] * (  m[1]  * (m[6]  * m[11] - m[7]  * m[10])
		          - m[5]  * (m[2]  * m[11] - m[3]  * m[10])
		          + m[9]  * (m[2]  * m[7]  - m[3]  * m[6]));
	 }
      template <typename T> 
      inline Matrix44<T> transpose(Matrix44<T> const & m)
	 {
	 const int size=4;
	 Matrix44<T> mres(0);
	 int i, j;
	 for (i=0; i<size; ++i)
	    for (j=0; j<size; j++)
	       mres[size*i+j] = m[size*j+i];
	 return mres;
	 }

      } // namespace Math
   } // namespace arda


////////////////////////////////////////////////////////////////////////////////
// Matrix methods

template <typename T> 
std::string arda::Math::Matrix22<T>::to_string(void) const
   {
   std::stringstream ss;
   ss << "[ "
	 "[ " << m[0] << ", " << m[1] << " ], "
	 "[ " << m[2] << ", " << m[3] << " ] ]";
   return ss.str();
   }

template <typename T> 
std::string arda::Math::Matrix33<T>::to_string(void) const
   {
   std::stringstream ss;
   ss << "[ "
	 "[ " << m[0] << ", " << m[1] << ", " << m[2] << " ], "
	 "[ " << m[3] << ", " << m[4] << ", " << m[5] << " ], "
	 "[ " << m[6] << ", " << m[7] << ", " << m[8] << " ], ""]";
   return ss.str();
   }


template <typename T> 
std::string arda::Math::Matrix44<T>::to_string(void) const
   {
   std::stringstream ss;
   ss << "[ "
	 "[ " << m[0] << ", " << m[1] << ", " << m[2] << ", " << m[3] << " ], "
	 "[ " << m[4] << ", " << m[5] << ", " << m[6] << ", " << m[7] << " ], "
	 "[ " << m[8] << ", " << m[9] << ", " << m[10] << ", " << m[11] << " ], "
	 "[ " << m[12] << ", " << m[13] << ", " << m[14] << ", " << m[15] << " ], ""]";
   return ss.str();
   }

#endif // MATRIX_H_
