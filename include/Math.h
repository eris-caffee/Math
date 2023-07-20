#ifndef MATH_H_
#define MATH_H_

#include "Vector.h"
#include "Matrix.h"
#include "Transform.h"

///////////////////////////////////////////////////////////////////////////////////
// Notes for improvement
//
// The angle related constants (PI, 2PI, etc) and functions (deg_to_rad, rad_to_deg)
// could be made faster by using #define's.  In fact, this would turn them into
// compile time operations.  But it would also put them, effectively, in the
// global namespace.  Do I want that?  For now I'm leaving things as const
// variables and inline functions.  I can profile things later to see if changes
// are really needed.

namespace arda 
   {

   ////////////////////////////////////////////////////////////////////////////////
   // Angles

   namespace Math
      {
      // This many decimals is enough to cover even IEEE quad precision (128 bit)
      // reals.  Run on PA-RISC lately?  :)
      // Should these be #defines?  I'm starting to think that they should be.
      static long double const PI             =  3.14159265358979323846264338327950288;
      static long double const TWO_PI         =  6.28318530717958647692528676655900577;
      static long double const PI_DIV_180     =  0.01745329251994329576923690768488613;
      static long double const INV_PI_DIV_180 = 57.29577951308232087679815481410517033;

      //////////////////////////////////////////////////////////////////////////
      // Mixed Vector / Matrix operations.
      // * *=
      //     Defined for Vector * Matrix and Matrix * Vector, but these
      //     operators are not part of the class.  They are defined independently.
      //

      // Vector2 * Matrix22
      template <typename T> 
      inline Vector2<T>& operator*=(Vector2<T>  & v, 
				    Matrix22<T> const & m)
	 {
	 Vector2<T> vres(0);
	 vres[0] = v[0]*m[0] + v[1]*m[1];
	 vres[1] = v[0]*m[2] + v[1]*m[3];
	 v = vres;
	 return v;
	 }

      template <typename T> 
      inline Vector2<T> operator*(Vector2<T>  const & v,
				  Matrix22<T> const & m)
	 { return Vector2<T>(v) *= m; }

      // Note: can't define Matrix *= Vector since the result is a Vector.
      template <typename T> 
      inline Vector2<T> operator*(Matrix22<T> const & m,
				  Vector2<T>  const & v)
	 { 
	 Vector2<T> vres(0);
	 vres[0] = m[0]*v[0] + m[2]*v[1];
	 vres[1] = m[1]*v[0] + m[3]*v[1];
	 return vres;
	 }

      ////////////////////////////////////////
      // Vector3 * Matrix33
      template <typename T> 
      inline Vector3<T>& operator*=(Vector3<T>  & v, 
				    Matrix33<T> const & m)
	 {
	 Vector3<T> vres(0);
	 vres[0] = v[0]*m[0] + v[1]*m[1] + v[2]*m[2];
	 vres[1] = v[0]*m[3] + v[1]*m[4] + v[2]*m[5];
	 vres[2] = v[0]*m[6] + v[1]*m[7] + v[2]*m[8];
	 v = vres;
	 return v;
	 }

      template <typename T> 
      inline Vector3<T> operator*(Vector3<T>  const & v,
				  Matrix33<T> const & m)
	 { return Vector3<T>(v) *= m; }

      // Matrix * Vector
      // Note: can't define Matrix *= Vector since the result is a Vector.
      template <typename T> 
      inline Vector3<T> operator*(Matrix33<T> const & m,
				  Vector3<T>  const & v)
	 { 
	 Vector3<T> vres(0);
	 vres[0] = m[0]*v[0] + m[3]*v[1] + m[6]*v[2];
	 vres[1] = m[1]*v[0] + m[4]*v[1] + m[7]*v[2];
	 vres[2] = m[2]*v[0] + m[5]*v[1] + m[8]*v[2];
	 return vres;
	 }

      ////////////////////////////////////////
      // Vector4 * Matrix44
      template <typename T> 
      inline Vector4<T>& operator*=(Vector4<T>  & v, 
				    Matrix44<T> const & m)
	 {
	 Vector4<T> vres(0);
	 vres[0] = v[0]*m[0] + v[1]*m[1] + v[2]*m[2] + v[3]*m[3];
	 vres[1] = v[0]*m[4] + v[1]*m[5] + v[2]*m[6] + v[3]*m[7];
	 vres[2] = v[0]*m[8] + v[1]*m[9] + v[2]*m[10] + v[3]*m[11];
	 vres[3] = v[0]*m[12] + v[1]*m[13] + v[2]*m[14] + v[3]*m[15];
	 v = vres;
	 return v;
	 }

      template <typename T> 
      inline Vector4<T> operator*(Vector4<T>  const & v,
				  Matrix44<T> const & m)
	 { return Vector4<T>(v) *= m; }

      // Matrix * Vector
      // Note: can't define Matrix *= Vector since the result is a Vector.
      template <typename T> 
      inline Vector4<T> operator*(Matrix44<T> const & m,
				  Vector4<T>  const & v)
	 { 
	 Vector4<T> vres(0);
	 vres[0] = m[0]*v[0] + m[4]*v[1] + m[8]*v[2] + m[12]*v[3];
	 vres[1] = m[1]*v[0] + m[5]*v[1] + m[9]*v[2] + m[13]*v[3];
	 vres[2] = m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3];
	 vres[3] = m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3];
	 return vres;
	 }

      //////////////////////////////////////////////////////////////////////////

      /** \brief Converts degrees to radians
       */
      inline double deg_to_rad(double deg) { return deg * PI_DIV_180; };


      /** \brief Converts radians to degrees.
       */
      inline double rad_to_deg(double rad) { return rad * INV_PI_DIV_180; };

      } // namespace Math

   } // namespace arda


#endif
