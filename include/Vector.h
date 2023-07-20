#ifndef VECTOR_H_
#define VECTOR_H_

#include <cassert>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>


namespace arda 
    {
    namespace Math
        {
        ////////////////////////////////////////////////////////////////////////////////
        /** \class arda::Math::Vector2
         *
         * \brief Templated classes for 2, 3, and 4 dimensional vectors.
         *
         * \tparam T Type is intended to be int, float, and double only. (i.e. if you roll your own base type, it had better act like a numeric scalar.)
         *
         * \verbatim
         * Supported operations on vectors
         *
         * Construction
         *     Vector v;             * Default zero vector.
         *     Vector v2(v);         * Construct from other vector.
         *     T a, b;
         *     Vector v(a, b)        * Construct from values.
         * []
         *     If you have a Vector named v you can access it's member elements as
         *     v[0], v[1], v[2], and v[3]. in addtion to v.x, v.y, v.z, and v.w
         * == != + += - -=
         *     Defined for operations on two vectors of the same type.
         *     TODO Is there a better way to do this?  With integer types this is fine,
         *     but with floating point types this == and != are really worthless.  Is it possible to 
         *     create variant methods in a template class that vary by the type?  Or do I just have
         *     to suck it up and create type specific external functions for comparing vectors?
         * * *= / /=
         *     Defined for scalar multiplication/division with int, float, and double.
         *     * is defined as a standalone template operator for the scalar * Vector form.
         *
         * Note that the following typedefs are defined for convenience:
         *
         * typedef Vector2<int> Vector2i;
         * typedef Vector2<float> Vector2f;
         * typedef Vector2<double> Vector2d;
         * typedef Vector3<int> Vector3i;
         * typedef Vector3<float> Vector3f;
         * typedef Vector3<double> Vector3d;
         * typedef Vector4<int> Vector4i;
         * typedef Vector4<float> Vector4f;
         * typedef Vector4<double> Vector4d;
         *
         *
         *
         * Scalar multiplication and division are overloaded.  Why?
         * I'm not sure I need this.  The idea is to support all likely scalar
         * types without having to rely on implicit or explicit type conversion,
         * especially not a conversion that might result in loss of precision.
         * Multiplying a float Vector by a double scalar, for example.
         *
         * Is there a better way to do this?  Am I worrying about nothing?
         *
         *
         *
         * I suppose I could make this into a single Vector template on two parameters
         * template <typename T, unsigned int N> class Vector
         *    {
         *    T v[N];
         *
         *    etc...
         *
         * This might buy perfect generality, but it would come at the expense of
         * loops in all of the code, so I don't think it would really be worth it.
         *
         * \endverbatim
         */

        /////////////////////////////////////////////////////////////////////////////
        template <typename T> 
        class Vector2
            {
        public:
            T x, y;
	 
            // Constructors
            Vector2() {}
            explicit Vector2(T a) : x (a), y(a) {}
            Vector2(T a, T b) : x (a), y(b) {}

            // Array indexing
            inline T& operator[](unsigned int const i)
                { assert (i<2); if (i==0) return x; return y; }
            inline T operator[](unsigned int const i) const
                { assert (i<2); if (i==0) return x; return y; }

            // Assignment
            inline Vector2<T>& operator=(Vector2<T> const & v2)
                { x = v2.x; y = v2.y; return *this; }

            /** \brief Directly assign values to the vector.
             *
             * Takes 2, 3, or 4 arguments of template type T according to the size of the Vector.
             */

            inline Vector2<T>& assign(T const a, T const b)
                { x = a; y = b; return *this; }

            // Comparison
            inline bool operator==(Vector2<T> const & v2) const
                { return ((x == v2.x) && (y == v2.y)); }
            inline bool operator!=(Vector2<T> const & v2) const
                { return ! (*this == v2); }

            // Vector addition
            inline Vector2<T>& operator+=(Vector2<T> const & v2)
                { x += v2.x; y += v2.y; return *this; }
            inline Vector2<T> operator+(Vector2<T> const & v2) const
                { return Vector2<T>(*this) += v2; }

            // Vector subtraction
            inline Vector2<T>& operator-=(Vector2<T> const & v2)
                { x -= v2.x; y -= v2.y; return *this; }
            inline Vector2<T> operator-(Vector2<T> const & v2) const
                { return Vector2<T>(*this) -= v2; }

            // Scalar multiplication
            inline Vector2<T>& operator*=(int const a)
                { x *= a; y *= a; return *this; }
            inline Vector2<T>& operator*=(float const a)
                { x *= a; y *= a; return *this; }
            inline Vector2<T>& operator*=(double const a)
                { x *= a; y *= a; return *this; }

            inline Vector2<T> operator*(int const a) const
                { return Vector2<T>(*this) *= a;}
            inline Vector2<T> operator*(float const a) const
                { return Vector2<T>(*this) *= a;}
            inline Vector2<T> operator*(double const a) const
                { return Vector2<T>(*this) *= a;}

            // Scalar division
            inline Vector2<T>& operator/=(int const a)
                { assert(a!=0); x /= a; y /= a; return *this; }
            inline Vector2<T>& operator/=(float const a)
                { assert(a!=0); x /= a; y /= a; return *this; }
            inline Vector2<T>& operator/=(double const a)
                { assert(a!=0); x /= a; y /= a; return *this; }

            inline Vector2<T> operator/(int const a) const
                { return Vector2<T>(*this) /= a;}
            inline Vector2<T> operator/(float const a) const
                { return Vector2<T>(*this) /= a;}
            inline Vector2<T> operator/(double const a) const
                { return Vector2<T>(*this) /= a;}


            // methods

            /** \brief The dot product of the vector with v2.
             */
            inline T dot(Vector2<T> const & v2) const
                { return x*v2.x + y*v2.y; }


            /** \brief Returns the angle (in radians) between the vector and v2. Not meaningful for int vectors.
             */
            inline double get_angle(Vector2<T> const & v2)
                { 
                double tmp = dot(v2); 
                return acos(sqrt(tmp*tmp/(dot(*this)*v2.dot(v2))));
                }


            /** \brief Like get_angle(), but the vectors must already be normalized. Not meaningful for int vectors.
             */
            inline double get_anglen(Vector2<T> const & v2)
                { return acos((double) dot(v2)); }


            /** \brief Returns a C string representation of the vector. This is one of the few non-inline Vector functions.
             */
            std::string to_string(void) const;


            /** \brief Get the length of a vector. Returns a double for all vector types.
             */
            inline double length(void) const
                { return sqrt((dot(*this))); }


            /** \brief Normalizes the vector. Not meaningful for int vectors.
             */
            inline Vector2<T>& normalize()
                { 
                double l = length(); 
                if (l == 0.0) return *this; 
                x /= l; y /= l; 
                return *this; }

            /** \brief Calculates the projection of the vector onto v2.  Not meaningful for int vectors.
             */
            inline Vector2<T> proj(Vector2<T> const & v2)
                { Vector2<T> vres; vres = v2 * (dot(v2)/v2.dot(v2)); return vres; }
            /** \copybrief arda::Math::Vector2::proj
             * Returns result in vres
             */
           inline Vector2<T>& proj(Vector2<T> const & v2, Vector2<T>& vres)
                { vres = v2 * dot(v2)/v2.dot(v2); return vres; }
            };

        // Scalar multiplication, continued
        template <typename T> 
        inline Vector2<T> operator*(int const a, Vector2<T> const & v)
            { return Vector2<T>(v) *= a;}

        template <typename T> 
        inline Vector2<T> operator*(float const a, Vector2<T> const & v)
            { return Vector2<T>(v) *= a;}

        template <typename T> 
        inline Vector2<T> operator*(double const a, Vector2<T> const & v)
            { return Vector2<T>(v) *= a;}


        /////////////////////////////////////////////////////////////////////////////
        /** \class arda::Math::Vector3
         *  \copydoc arda::Math::Vector2
         */
        template <typename T> 
        class Vector3
            {
        public:
            T x, y, z;

            // Constructors
            Vector3() {}
            explicit Vector3(T a) : x (a), y(a), z(a) {}
            Vector3(T a, T b, T c) : x (a), y(b), z(c) {}
            Vector3(Vector2<T> v) : x (v.x), y (v.y), z (0) {}

            // Array indexing
            inline T& operator[](unsigned int const i)
                { assert (i<3); if (i==0) return x; if (i==1) return y; return z; }
            inline T operator[](unsigned int const i) const
                { assert (i<3); if (i==0) return x; if (i==1) return y; return z; }

            // Assignment
            inline Vector3<T>& operator=(Vector2<T> const & v2)
                { x = v2.x; y = v2.y; z = T(0); return *this; }
            inline Vector3<T>& operator=(Vector3<T> const & v2)
                { x = v2.x; y = v2.y; z = v2.z; return *this; }

            /** \copydoc arda::Math::Vector2::assign */
            inline Vector3<T>& assign(T const a, T const b, T const c)
                { x = a; y = b; z = c; return *this; }

            // Comparison
            inline bool operator==(Vector3<T> const & v2) const
                { return ((x == v2.x) && (y == v2.y) && (z == v2.z)); }
            inline bool operator!=(Vector3<T> const & v2) const
                { return ! (*this == v2); }

            // Vector addition
            inline Vector3<T>& operator+=(Vector3<T> const & v2)
                { x += v2.x; y += v2.y; z += v2.z; return *this; }
            inline Vector3<T> operator+(Vector3<T> const & v2) const
                { return Vector3<T>(*this) += v2; }

            // Vector subtraction
            inline Vector3<T>& operator-=(Vector3<T> const & v2)
                { x -= v2.x; y -= v2.y; z -= v2.z; return *this; }
            inline Vector3<T> operator-(Vector3<T> const & v2) const
                { return Vector3<T>(*this) -= v2; }

            // Scalar multiplication
            inline Vector3<T>& operator*=(int const a)
                { x *= a; y *= a; z *= a; return *this; }
            inline Vector3<T>& operator*=(float const a)
                { x *= a; y *= a; z *= a; return *this; }
            inline Vector3<T>& operator*=(double const a)
                { x *= a; y *= a; z *= a; return *this; }

            inline Vector3<T> operator*(int const a) const
                { return Vector3<T>(*this) *= a;}
            inline Vector3<T> operator*(float const a) const
                { return Vector3<T>(*this) *= a;}
            inline Vector3<T> operator*(double const a) const
                { return Vector3<T>(*this) *= a;}

            // Scalar division
            inline Vector3<T>& operator/=(int const a)
                { assert(a!=0); x /= a; y /= a; z /= a; return *this; }
            inline Vector3<T>& operator/=(float const a)
                { assert(a!=0); x /= a; y /= a; z /= a; return *this; }
            inline Vector3<T>& operator/=(double const a)
                { assert(a!=0); x /= a; y /= a; z /= a; return *this; }

            inline Vector3<T> operator/(int const a) const
                { return Vector3<T>(*this) /= a;}
            inline Vector3<T> operator/(float const a) const
                { return Vector3<T>(*this) /= a;}
            inline Vector3<T> operator/(double const a) const
                { return Vector3<T>(*this) /= a;}


            // methods

            /** \brief Cross product of the vector with another Vector. Result returned in vres.
             *
             * The version that takes two arguments stores the result in the second
             * argument.  This may be faster since no temporary object is created
             * during the operation.
             */
            inline Vector3<T>& cross(Vector3<T> const & v2, Vector3<T>& vres)
                { 
                vres.x =  y*v2.z - v2.y*z;
                vres.y = -x*v2.z + v2.x*z;
                vres.z =  x*v2.y - v2.x*y;
                return vres;
                }
            /** \brief Cross product of the vector with another Vector.
             * \copydetails arda::Math::Vector3::cross */
            inline Vector3<T> cross(Vector3<T> const & v2)
                { 
                Vector3<T> vres;
                vres.x =  y*v2.z - v2.y*z;
                vres.y = -x*v2.z + v2.x*z;
                vres.z =  x*v2.y - v2.x*y;
                return vres;
                }

            /** \copydoc arda::Math::Vector2::dot */
            inline T dot(Vector3<T> const & v2) const
                { return x*v2.x + y*v2.y + z*v2.z; }

            /** \copydoc arda::Math::Vector2::get_angle */
            inline double get_angle(Vector3<T> const & v2)
                { 
                double tmp = dot(v2); 
                return acos(sqrt(tmp*tmp/(dot(*this)*v2.dot(v2))));
                }

            /** \copydoc arda::Math::Vector2::get_anglen */
            inline double get_anglen(Vector3<T> const & v2)
                { return acos((double) dot(v2)); }

            /** \copydoc arda::Math::Vector2::to_string */
            std::string to_string(void) const;

            /** \copydoc arda::Math::Vector2::length */
            inline double length(void) const
                { return sqrt((dot(*this))); }

            /** \copydoc arda::Math::Vector2::normalize */
            inline Vector3<T>& normalize()
                { double l = length(); if (l == 0.0) return *this; x /= l; y /= l; z /= l; return *this; }

            /** \copydoc arda::Math::Vector2::proj */
            inline Vector3<T> proj(Vector3<T> const & v2)
                { Vector3<T> vres; vres = v2 * dot(v2)/v2.dot(v2); return vres; }
            /** \copybrief arda::Math::Vector2::proj
             * Returns result in vres
             */
            inline Vector3<T>& proj(Vector3<T> const & v2, Vector3<T>& vres)
                { vres = v2 * dot(v2)/v2.dot(v2); return vres; }
            };

        // Scalar multiplication, continued
        template <typename T> 
        inline Vector3<T> operator*(int const a, Vector3<T> const & v)
            { return Vector3<T>(v) *= a;}
      
        template <typename T> 
        inline Vector3<T> operator*(float const a, Vector3<T> const & v)
            { return Vector3<T>(v) *= a;}

        template <typename T> 
        inline Vector3<T> operator*(double const a, Vector3<T> const & v)
            { return Vector3<T>(v) *= a;}

        /////////////////////////////////////////////////////////////////////////////
        /** \class arda::Math::Vector4
         *  \copydoc arda::Math::Vector2
         */
        template <typename T> 
        class Vector4
            {
        public:
            T x, y, z, w;

            // Constructors
            Vector4() {}
            explicit Vector4(T a) : x (a), y(a), z(a), w(a) {}
            Vector4(T a, T b, T c, T d) : x (a), y(b), z(c), w(d) {}
            Vector4(Vector2<T> v) : x (v.x), y (v.y), z (0), w (0) {}
            Vector4(Vector3<T> v) : x (v.x), y (v.y), z (v.z), w (0) {}

            // Array indexing
            inline T& operator[](unsigned int const i)
                { assert (i<4); if (i==0) return x; if (i==1) return y; if (i==2) return z; return w; }
            inline T operator[](unsigned int const i) const
                { assert (i<4); if (i==0) return x; if (i==1) return y; if (i==2) return z; return w; }

            // Assignment
            inline Vector4<T>& operator=(Vector2<T> const & v2)
                { x = v2.x; y = v2.y; z = T(0); w = T(0); return *this; }
            inline Vector4<T>& operator=(Vector3<T> const & v2)
                { x = v2.x; y = v2.y; z = v2.z; w = T(0); return *this; }
            inline Vector4<T>& operator=(Vector4<T> const & v2)
                { x = v2.x; y = v2.y; z = v2.z; w = v2.w; return *this; }

            /** \copydoc arda::Math::Vector2::assign */
            inline Vector4<T>& assign(T const a, T const b, T const c, T const d)
                { x = a; y = b; z = c; w = d; return *this; }

            // Comparison
            inline bool operator==(Vector4<T> const & v2) const
                { return ((x == v2.x) && (y == v2.y) && (z == v2.z) && (w == v2.w)); }
            inline bool operator!=(Vector4<T> const & v2) const
                { return ! (*this == v2); }

            // Vector addition
            inline Vector4<T>& operator+=(Vector4<T> const & v2)
                { x += v2.x; y += v2.y; z += v2.z; w += v2.w; return *this; }
            inline Vector4<T> operator+(Vector4<T> const & v2) const
                { return Vector4<T>(*this) += v2; }

            // Vector subtraction
            inline Vector4<T>& operator-=(Vector4<T> const & v2)
                { x -= v2.x; y -= v2.y; z -= v2.z; w -= v2.w; return *this; }
            inline Vector4<T> operator-(Vector4<T> const & v2) const
                { return Vector4<T>(*this) -= v2; }

            // Scalar multiplication
            inline Vector4<T>& operator*=(int const a)
                { x *= a; y *= a; z *= a; w *= a; return *this; }
            inline Vector4<T>& operator*=(float const a)
                { x *= a; y *= a; z *= a; w *= a; return *this; }
            inline Vector4<T>& operator*=(double const a)
                { x *= a; y *= a; z *= a; w *= a; return *this; }

            inline Vector4<T> operator*(int const a) const
                { return Vector4<T>(*this) *= a;}
            inline Vector4<T> operator*(float const a) const
                { return Vector4<T>(*this) *= a;}
            inline Vector4<T> operator*(double const a) const
                { return Vector4<T>(*this) *= a;}

            // Scalar division
            inline Vector4<T>& operator/=(int const a)
                { assert(a!=0); x /= a; y /= a; z /= a; w /= a; return *this; }
            inline Vector4<T>& operator/=(float const a)
                { assert(a!=0); x /= a; y /= a; z /= a; w /= a; return *this; }
            inline Vector4<T>& operator/=(double const a)
                { assert(a!=0); x /= a; y /= a; z /= a; w /= a; return *this; }

            inline Vector4<T> operator/(int const a) const
                { return Vector4<T>(*this) /= a;}
            inline Vector4<T> operator/(float const a) const
                { return Vector4<T>(*this) /= a;}
            inline Vector4<T> operator/(double const a) const
                { return Vector4<T>(*this) /= a;}


            // methods

            /** \copydoc arda::Math::Vector2::dot */
            inline T dot(Vector4<T> const & v2) const
                { return x*v2.x + y*v2.y + z*v2.z + w*v2.w; }

            /** \copydoc arda::Math::Vector2::get_angle */
            inline double get_angle(Vector4<T> const & v2)
                { 
                double tmp = dot(v2); 
                return acos(sqrt(tmp*tmp/(dot(*this)*v2.dot(v2))));
                }

            /** \copydoc arda::Math::Vector2::get_anglen */
            inline double get_anglen(Vector4<T> const & v2)
                { return acos((double) dot(v2)); }

            /** \copydoc arda::Math::Vector2::to_string */
            std::string to_string(void) const;

            /** \copydoc arda::Math::Vector2::length */
            inline double length(void) const
                { return sqrt((dot(*this))); }

            /** \copydoc arda::Math::Vector2::normalize */
            inline Vector4<T>& normalize()
                { double l = length(); if (l == 0.0) return *this; x /= l; y /= l; z /= l; w /= l; return *this; }

            /** \copydoc arda::Math::Vector2::proj */
            inline Vector4<T> proj(Vector4<T> const & v2)
                { Vector4<T> vres; vres = v2 * dot(v2)/v2.dot(v2); return vres; }
            /** \copybrief arda::Math::Vector2::proj
             * Returns result in vres
             */
            inline Vector4<T>& proj(Vector4<T> const & v2, Vector4<T>& vres)
                { vres = v2 * dot(v2)/v2.dot(v2); return vres; }
            };

        // Scalar multiplication, continued
        template <typename T> 
        inline Vector4<T> operator*(int const a, Vector4<T> const & v)
            { return Vector4<T>(v) *= a;}
      
        template <typename T> 
        inline Vector4<T> operator*(float const a, Vector4<T> const & v)
            { return Vector4<T>(v) *= a;}
      
        template <typename T> 
        inline Vector4<T> operator*(double const a, Vector4<T> const & v)
            { return Vector4<T>(v) *= a;}

        /////////////////////////////////////////////////////////////////////////////

        typedef Vector2<int> Vector2i;
        typedef Vector2<float> Vector2f;
        typedef Vector2<double> Vector2d;

        typedef Vector3<int> Vector3i;
        typedef Vector3<float> Vector3f;
        typedef Vector3<double> Vector3d;

        typedef Vector4<int> Vector4i;
        typedef Vector4<float> Vector4f;
        typedef Vector4<double> Vector4d;

        } // namespace Math

    } // namespace arda

////////////////////////////////////////////////////////////////////////////////
template <typename T> 
std::string arda::Math::Vector2<T>::to_string(void) const
    {
    std::stringstream ss;
    ss << "[ " << x << ", " << y << " ]";
    return ss.str();
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T> 
std::string arda::Math::Vector3<T>::to_string(void) const
    {
    std::stringstream ss;
    ss << "[ " << x << ", " << y << ", " << z << " ]";
    return ss.str();
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T> 
std::string arda::Math::Vector4<T>::to_string(void) const
    {
    std::stringstream ss;
    ss << "[ " << x << ", " << y << ", " << z << ", " << w << " ]";
    return ss.str();
    }


#endif // VECTOR_H_
