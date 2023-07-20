#ifndef TRANSFORM_H_
#define TRANSFORM_H_

// Needs Vector.h and Matrix.h, but this file is not intended to be included
// directly.  Just include Math.h and everything will be set up correctly.

#include <iostream>

namespace arda 
    {
    namespace Math
        {

        //////////////////////////////////////////////////////////////////////////

        // Transformation by distance d
        template <typename T>
        void get_trans_mat44(arda::Math::Matrix44<T> & M, arda::Math::Vector4<T> d);

        // Rotation by angle around vector v
        template <typename T>
        void get_rot_mat33(arda::Math::Matrix33<T> & M, float angle, arda::Math::Vector3<T> v);

        template <typename T>
        void get_rot_mat44(arda::Math::Matrix44<T> & M, float angle, arda::Math::Vector3<T> v);

        // Uniform scaling by factor of s
        template <typename T>
        void get_scale_mat44(arda::Math::Matrix44<T> & M, float s);

        // Non-uniform scaling
        template <typename T>
        void get_scale_mat44(arda::Math::Matrix44<T> & M, arda::Math::Vector3<T> s);

        // Non-uniform scaling along arbitrary axis
        template <typename T>
        void get_scale_mat44(arda::Math::Matrix44<T> & M, arda::Math::Vector3<T> s,
            arda::Math::Vector3<T> x, arda::Math::Vector3<T> y, arda::Math::Vector3<T> z);

        // Shear ith coordinate with respect to jth coordinate by s.  i and j are zero based column indexes.
        // (x = 0, y = 1, z = 2)
        template <typename T>
        void get_shear_mat44(arda::Math::Matrix44<T> & M, int i, int j, float s);

        // Transformation matrix for combination of translation by d and rotation by angle around v.
        template <typename T>
        void get_transform_mat44(arda::Math::Matrix44<T> & M, float angle, arda::Math::Vector3<T> v, arda::Math::Vector3<T> d);

        // Rotate by angle around v with center of rotation p.
        template <typename T>
        void get_rot_about_point_mat44(arda::Math::Matrix33<T> & M, float angle, arda::Math::Vector3<T> v, arda::Math::Vector3<T> p);

        ////////////////////////////////////////      
        // Projection matrices

        template <typename T>
        void get_ortho_mat44(arda::Math::Matrix44<T> & M, T near, T far, T left, T right, T bottom, T top);

        template <typename T>
        void get_persp_mat44(arda::Math::Matrix44<T> & M, T near, T far, T left, T right, T bottom, T top);

        template <typename T>
        void get_persp_inf_mat44(arda::Math::Matrix44<T> & M, T near, T far, T left, T right, T bottom, T top);

        } // namespace Math
   
    } // namespace arda


////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_trans_mat44(arda::Math::Matrix44<T> & M, arda::Math::Vector3<T> d)
    {
    M.setidentity();
    M.setcol(3, d.x, d.y, d.z, 1);
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_rot_mat33(arda::Math::Matrix33<T> & M, float angle, arda::Math::Vector3<T> v)
    {
    // TODO Replace == comparision of floating point number!
    if (0.0 == v.length()) {
        M.setidentity();
        return;
        }

    // TODO: I should also immediately return identity if angle is a multiple of 2*PI but I'm not
    // yet sure how I should I check for that (taking into account floating point imprecision).


    v.normalize();

    float c = cos(angle);
    float s = sin(angle);
    float one_minus_c = 1.0f - c;

    // Remember: the "rows" as written here are actually the columns of the matrix.
    M.assign(
        c + one_minus_c * v.x * v.x         ,   one_minus_c * v.x * v.y + s * v.z   ,   one_minus_c * v.x * v.z - s * v.y   ,
        one_minus_c * v.x * v.y - s * v.z   ,   c + one_minus_c * v.y * v.y         ,   one_minus_c * v.y * v.z + s * v.x   ,
        one_minus_c * v.x * v.z + s * v.y   ,   one_minus_c * v.y * v.z - s * v.x   ,   c + one_minus_c * v.z * v.z
        );
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_rot_mat44(arda::Math::Matrix44<T> & M, float angle, arda::Math::Vector3<T> v)
    {
    arda::Math::Matrix33<T> M33;
    arda::Math::get_rot_mat33(M33, angle, v);
    M.assign(M33[0], M33[1], M33[2], 0, M33[3], M33[4], M33[5], 0, M33[6], M33[7], M33[8], 0, 0, 0, 0, 1);
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_scale_mat44(arda::Math::Matrix44<T> & M, float s)
    {
    M.setidentity();
    M *= s;
    M[15] = 1;
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_scale_mat44(arda::Math::Matrix44<T> & M, arda::Math::Vector3<T> s)
    {
    M.setidentity();
    M[0] = s.x;
    M[5] = s.y;
    M[10] = s.z;
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_scale_mat44(arda::Math::Matrix44<T> & M, arda::Math::Vector3<T> s,
    arda::Math::Vector3<T> x, arda::Math::Vector3<T> y, arda::Math::Vector3<T> z)
    {
    // TODO Replace == comparision of floating point number!
    assert(0 == x.dot(y));
    assert(0 == x.dot(z));
    assert(0 == y.dot(z));

    arda::Math::Matrix44<T> F, Ft, S;
    F.setcol(0, x.x, x.y, x.z, 0);
    F.setcol(1, y.x, y.y, y.z, 0);
    F.setcol(2, z.x, z.y, z.z, 0);
    F.setcol(3, 0, 0, 0, 1);

    Ft = arda::Math::transpose(F);
    arda::Math::get_scale_mat44(S, s);

    M = F * S * Ft;
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_shear_mat44(arda::Math::Matrix44<T> & M, int i, int j, float s)
    {
    assert(i<3 && i>=0);
    assert(j<3 && j>=0);
    M.setidentity();
    M[4*j + i] = s;
    }


////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_transform_mat44(arda::Math::Matrix44<T> & M, 
    float angle, arda::Math::Vector3<T> v,
    arda::Math::Vector3<T> d)
    {
    arda::Math::Matrix33<T> M33;
    arda::Math::get_rot_mat33(M33, angle, v);
    M.assign(M33[0], M33[1], M33[2], 0, M33[3], M33[4], M33[5], 0, M33[6], M33[7], M33[8], 0, d.x, d.y, d.z, 1);
    }



////////////////////////////////////////////////////////////////////////////////
// I initially wrote this while trying to do a rotation about an arbitrary vector with the center of rotation at point p.
// It seems to work, but I'm not sure of it's generality.

template <typename T>
void arda::Math::get_rot_about_point_mat44(arda::Math::Matrix44<T> & M, 
    float angle, arda::Math::Vector3<T> v,
    arda::Math::Vector3<T> p)
    {
    arda::Math::Matrix33f M33(0);
    get_rot_mat33(M33, angle, v);
    arda::Math::Vector3f p1 = M33 * p;

    M[0] = M33[0];
    M[1] = M33[1];
    M[2] = M33[2];
    M[3] = T(0);

    M[4] = M33[3];
    M[5] = M33[4];
    M[6] = M33[5];
    M[7] = T(0);

    M[8] = M33[6];
    M[9] = M33[7];
    M[10] = M33[8];
    M[11] = T(0);

    M[12] = p.x - p1.x;
    M[13] = p.y - p1.y;
    M[14] = p.z - p1.z;
    M[15] = T(1);
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_ortho_mat44(arda::Math::Matrix44<T> & M, T near, T far, T left, T right, T bottom, T top)
    {
    M.assign(
        2 / (right - left),                T(0),                              T(0),                          T(0),
        T(0),                              2 / (top - bottom),                T(0),                          T(0),
        T(0),                              T(0),                              - 2 / (far - near),            T(0),
        - (right + left) / (right - left), - (top + bottom) / (top - bottom), - (far + near) / (far - near), T(1) );
    
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_persp_mat44(arda::Math::Matrix44<T> & M, T near, T far, T left, T right, T bottom, T top)
    {
    M.assign(
        (2 * near) / (right - left),       T(0),                              T(0),                               T(0),
        T(0),                              (2 * near) / (top - bottom),       T(0),                               T(0), 
        (right + left) / (right - left),   (top + bottom) / (top - bottom),   - (far + near) / (far - near),      T(-1),
        T(0),                              T(0),                              - (2 * near * far) / (far - near),  T(0) 
    );
    
    }

////////////////////////////////////////////////////////////////////////////////
template <typename T>
void arda::Math::get_persp_inf_mat44(arda::Math::Matrix44<T> & M, T near, T far, T left, T right, T bottom, T top)
    {
    M.assign(
        (2 * near) / (right - left),       T(0),                              T(0),           T(0),
        T(0),                              (2 * near) / (top - bottom),       T(0),           T(0), 
        (right + left) / (right - left),   (top + bottom) / (top - bottom),   T(-1),          T(-1),
        T(0),                              T(0),                              - 2 * near,     T(0) 
    );
    
    }


#endif
