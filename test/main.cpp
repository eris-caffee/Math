#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

#include "Math.h"
using namespace arda::Math;

#include "gtest/gtest.h"

////////////////////////////////////////////////////////////////////////////////
// Vector2 floating point

typedef ::testing::Types<int, float, double> MyTypes;

template <typename T>
class VectorTest : public ::testing::Test {
public:
    static T x;
    static T y;
    static T z;
    static T w;

    virtual void SetUp() {
        }

    };

TYPED_TEST_CASE( VectorTest, MyTypes );

TYPED_TEST( VectorTest, ConstructFromSingleValue ) {
    TypeParam zero = (TypeParam ) 0;
    TypeParam one  = (TypeParam ) 1;

    Vector2<TypeParam> v2_zero( zero );
    EXPECT_FLOAT_EQ( zero, v2_zero.x ) << "x component is not " << zero;
    EXPECT_FLOAT_EQ( zero, v2_zero.y ) << "y component is not " << zero;

    Vector2<TypeParam> v2_one( one );
    EXPECT_FLOAT_EQ( one, v2_one.x ) << "x component is not " << one;
    EXPECT_FLOAT_EQ( one, v2_one.y ) << "y component is not " << one;

    Vector3<TypeParam> v3_zero( zero );
    EXPECT_FLOAT_EQ( zero, v3_zero.x ) << "x component is not " << zero;
    EXPECT_FLOAT_EQ( zero, v3_zero.y ) << "y component is not " << zero;
    EXPECT_FLOAT_EQ( zero, v3_zero.z ) << "z component is not " << zero;

    Vector3<TypeParam> v3_one( one );
    EXPECT_FLOAT_EQ( one, v3_one.x ) << "x component is not " << one;
    EXPECT_FLOAT_EQ( one, v3_one.y ) << "y component is not " << one;
    EXPECT_FLOAT_EQ( one, v3_one.z ) << "z component is not " << one;

    Vector4<TypeParam> v4_zero( zero );
    EXPECT_FLOAT_EQ( zero, v4_zero.x ) << "x component is not " << zero;
    EXPECT_FLOAT_EQ( zero, v4_zero.y ) << "y component is not " << zero;
    EXPECT_FLOAT_EQ( zero, v4_zero.z ) << "z component is not " << zero;
    EXPECT_FLOAT_EQ( zero, v4_zero.w ) << "w component is not " << zero;

    Vector4<TypeParam> v4_one( one );
    EXPECT_FLOAT_EQ( one, v4_one.x ) << "x component is not " << one;
    EXPECT_FLOAT_EQ( one, v4_one.y ) << "y component is not " << one;
    EXPECT_FLOAT_EQ( one, v4_one.z ) << "z component is not " << one;
    EXPECT_FLOAT_EQ( one, v4_one.w ) << "w component is not " << one;

    }

TYPED_TEST( VectorTest, ConstructFromMultipleValues ) {
    TypeParam x = (TypeParam ) 1.1;
    TypeParam y = (TypeParam ) 2.2;
    TypeParam z = (TypeParam ) 3.3;
    TypeParam w = (TypeParam ) 4.4;

    Vector2<TypeParam> v2( x, y );
    EXPECT_FLOAT_EQ( x, v2.x ) << "x component is not " << x;
    EXPECT_FLOAT_EQ( y, v2.y ) << "y component is not " << y;

    Vector3<TypeParam> v3( x, y, z );
    EXPECT_FLOAT_EQ( x, v3.x ) << "x component is not " << x;
    EXPECT_FLOAT_EQ( y, v3.y ) << "y component is not " << y;
    EXPECT_FLOAT_EQ( z, v3.z ) << "z component is not " << z;

    Vector4<TypeParam> v4( x, y, z, w );
    EXPECT_FLOAT_EQ( x, v4.x ) << "x component is not " << x;
    EXPECT_FLOAT_EQ( y, v4.y ) << "y component is not " << y;
    EXPECT_FLOAT_EQ( z, v4.z ) << "z component is not " << z;
    EXPECT_FLOAT_EQ( w, v4.w ) << "w component is not " << w;
    }

TYPED_TEST( VectorTest, ConstructFromVector ) {
    TypeParam x = (TypeParam ) 1.1;
    TypeParam y = (TypeParam ) 2.2;
    TypeParam z = (TypeParam ) 3.3;
    TypeParam w = (TypeParam ) 4.4;

    Vector2<TypeParam> v2_1( x, y );
    Vector2<TypeParam> v2_2( v2_1 );
    EXPECT_FLOAT_EQ( v2_1.x, v2_2.x ) << "x component is not " << v2_1.x;
    EXPECT_FLOAT_EQ( v2_1.y, v2_2.y ) << "y component is not " << v2_1.y;
    
    Vector3<TypeParam> v3_1( x, y, z );
    Vector3<TypeParam> v3_2( v3_1 );
    EXPECT_FLOAT_EQ( v3_1.x, v3_2.x ) << "x component is not " << v3_1.x;
    EXPECT_FLOAT_EQ( v3_1.y, v3_2.y ) << "y component is not " << v3_1.y;
    EXPECT_FLOAT_EQ( v3_1.z, v3_2.z ) << "z component is not " << v3_1.z;
    
    Vector4<TypeParam> v4_2_1( x, y, z, w );
    Vector4<TypeParam> v2( v4_2_1 );
    EXPECT_FLOAT_EQ( v4_2_1.x, v2.x ) << "x component is not " << v4_2_1.x;
    EXPECT_FLOAT_EQ( v4_2_1.y, v2.y ) << "y component is not " << v4_2_1.y;
    EXPECT_FLOAT_EQ( v4_2_1.z, v2.z ) << "z component is not " << v4_2_1.z;
    EXPECT_FLOAT_EQ( v4_2_1.w, v2.w ) << "w component is not " << v4_2_1.w;
    
    }

TYPED_TEST( VectorTest, Indexing ) {
    TypeParam x = (TypeParam ) 1.1;
    TypeParam y = (TypeParam ) 2.2;
    TypeParam z = (TypeParam ) 3.3;
    TypeParam w = (TypeParam ) 4.4;

    Vector2<TypeParam> v2( x, y);
    ASSERT_EQ( x, v2.x ) << "x component is not " << x;
    ASSERT_EQ( y, v2.y ) << "y component is not " << y;

    Vector3<TypeParam> v3( x, y, z);
    ASSERT_FLOAT_EQ( x, v3.x ) << "x component is not " << x;
    ASSERT_FLOAT_EQ( y, v3.y ) << "y component is not " << y;
    ASSERT_FLOAT_EQ( z, v3.z ) << "z component is not " << z;

    Vector4<TypeParam> v4( x, y, z, w);
    ASSERT_FLOAT_EQ( x, v4.x ) << "x component is not " << x;
    ASSERT_FLOAT_EQ( y, v4.y ) << "y component is not " << y;
    ASSERT_FLOAT_EQ( z, v4.z ) << "z component is not " << z;
    ASSERT_FLOAT_EQ( w, v4.w ) << "w component is not " << w;

    }

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


#ifdef NOTHING

////////////////////////////////////////////////////////////////////////////////
void test_vector(void)
   {
   string s1, s2;


   {
   cout << "===============================================================" << endl <<
	 "Testing Vector assignment" << endl;
   Vector2i v2i(1,2);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector2i v2i_2(0);
   Vector3f v3f_2(0);
   Vector4d v4d_2(0);

   cout << "Before assignment" << endl;
   cout << setw(40) << "v2i: " << v2i.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;

   v2i_2 = v2i;
   v3f_2 = v3f;
   v4d_2 = v4d;
   cout << "After assignment by =" << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;

   v2i_2.assign(1, 1);
   v3f_2.assign(2.2, 2.2, 2.2);
   v4d_2.assign(3.3, 3.3, 3.3, 3.3);
   cout << "After assignment by assign()" << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector comparison" << endl;
   Vector2i v2i(1,2);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector2i v2i_2(1,2);
   Vector3f v3f_2(1.1f, 2.2f, 3.3f);
   Vector4d v4d_2(1.1, 2.2, 3.3, 4.4);
   Vector2i v2i_3(0);
   Vector3f v3f_3(0);
   Vector4d v4d_3(0);

   cout << setw(40) << "v2i: " << v2i.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   cout << setw(40) << "v2i_3: " << v2i_3.to_string() << endl;
   cout << setw(40) << "v3f_3: " << v3f_3.to_string() << endl;
   cout << setw(40) << "v4d_3: " << v4d_3.to_string() << endl;
   cout << boolalpha;
   cout << setw(40) << "v2i == v2i_2: " << (v2i == v2i_2) << endl;
   cout << setw(40) << "v2i == v2i_3: " << (v2i == v2i_3) << endl;
   cout << setw(40) << "v2i != v2i_2: " << (v2i != v2i_2) << endl;
   cout << setw(40) << "v2i != v2i_3: " << (v2i != v2i_3) << endl;
   cout << setw(40) << "v3f == v3f_2: " << (v3f == v3f_2) << endl;
   cout << setw(40) << "v3f == v3f_3: " << (v3f == v3f_3) << endl;
   cout << setw(40) << "v3f != v3f_2: " << (v3f != v3f_2) << endl;
   cout << setw(40) << "v3f != v3f_3: " << (v3f != v3f_3) << endl;
   cout << setw(40) << "v4d == v4d_2: " << (v4d == v4d_2) << endl;
   cout << setw(40) << "v4d == v4d_3: " << (v4d == v4d_3) << endl;
   cout << setw(40) << "v4d != v4d_2: " << (v4d != v4d_2) << endl;
   cout << setw(40) << "v4d != v4d_3: " << (v4d != v4d_3) << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector addition" << endl;
   Vector2i v2i(1,2);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector2i v2i_2(3,4);
   Vector3f v3f_2(4.4, 5.5, 6.6);
   Vector4d v4d_2(5.5, 6.6, 7.7, 8.8);
   Vector2i v2i_3(0);
   Vector3f v3f_3(0);
   Vector4d v4d_3(0);

   cout << setw(40) << "v2i: " << v2i.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   v2i_3 = v2i + v2i_2;
   v3f_3 = v3f + v3f_2;
   v4d_3 = v4d + v4d_2;
   cout << setw(40) << "v2i_3 = v2i + v2i_2: " << v2i_3.to_string() << endl;
   cout << setw(40) << "v3f_3 = v3f + v3f_2: " << v3f_3.to_string() << endl;
   cout << setw(40) << "v4d_3 = v4d + v4d_2: " << v4d_3.to_string() << endl;
   v2i_3 += v2i_2;
   v3f_3 += v3f_2;
   v4d_3 += v4d_3;
   cout << setw(40) << "v2i_3 += v2i_2: " << v2i_3.to_string() << endl;
   cout << setw(40) << "v3f_3 += v3f_2: " << v3f_3.to_string() << endl;
   cout << setw(40) << "v4d_3 += v4d_3: " << v4d_3.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector subtraction" << endl;
   Vector2i v2i(1,2);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector2i v2i_2(3,4);
   Vector3f v3f_2(4.4, 5.5, 6.6);
   Vector4d v4d_2(5.5, 6.6, 7.7, 8.8);
   Vector2i v2i_3(0);
   Vector3f v3f_3(0);
   Vector4d v4d_3(0);

   cout << setw(40) << "v2i: " << v2i.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   v2i_3 = v2i - v2i_2;
   v3f_3 = v3f - v3f_2;
   v4d_3 = v4d - v4d_2;
   cout << setw(40) << "v2i_3 = v2i - v2i_2: " << v2i_3.to_string() << endl;
   cout << setw(40) << "v3f_3 = v3f - v3f_2: " << v3f_3.to_string() << endl;
   cout << setw(40) << "v4d_3 = v4d - v4d_2: " << v4d_3.to_string() << endl;
   v2i_3 -= v2i_2;
   v3f_3 -= v3f_2;
   v4d_3 -= v4d_3;
   cout << setw(40) << "v2i_3 -= v2i_2: " << v2i_3.to_string() << endl;
   cout << setw(40) << "v3f_3 -= v3f_2: " << v3f_3.to_string() << endl;
   cout << setw(40) << "v4d_3 -= v4d_3: " << v4d_3.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector scalar multiplication" << endl;
   Vector2i v2i(1,2);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector2i v2i_2(0);
   Vector3f v3f_2(0);
   Vector4d v4d_2(0);
   int i = 2;
   float f = 2.f;
   double d = 2.0;

   cout << setw(40) << "i: " << i << endl;
   cout << setw(40) << "f: " << f << endl;
   cout << setw(40) << "d: " << d << endl;
   cout << setw(40) << "v2i: " << v2i.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   v2i_2 = v2i * i;
   v3f_2 = v3f * f;
   v4d_2 = v4d * d;
   cout << setw(40) << "v2i_2 = v2i * i: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2 = v3f * f: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2 = v4d * d: " << v4d_2.to_string() << endl;
   v2i_2 *= i;
   v3f_2 *= f;
   v4d_2 *= d;
   cout << setw(40) << "v2i_2 *= i: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2 *= f: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2 *= d: " << v4d_2.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector scalar division" << endl;
   Vector2i v2i(1,2);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector2i v2i_2(0);
   Vector3f v3f_2(0);
   Vector4d v4d_2(0);
   int i = 2;
   float f = 2.f;
   double d = 2.0;

   cout << setw(40) << "v2i: " << v2i.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   v2i_2 = v2i / i;
   v3f_2 = v3f / f;
   v4d_2 = v4d / d;
   cout << setw(40) << "v2i_2 = v2i / i: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2 = v3f / f: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2 = v4d / d: " << v4d_2.to_string() << endl;
   v2i_2 /= i;
   v3f_2 /= f;
   v4d_2 /= d;
   cout << setw(40) << "v2i_2 /= i: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f_2 /= f: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d_2 /= d: " << v4d_2.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector cross product" << endl;
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector3f v3f_2(4.4, 5.5, 6.6);
   Vector3f v3f_3(0);
   Vector3f v3f_4(0);
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v3f_3: " << v3f_3.to_string() << endl;
   v3f.cross(v3f_2, v3f_3);
   cout << setw(40) << "v3f.cross(v3f_2, v3f_3): " << v3f_3.to_string() << endl;
   v3f_4 = 2.0 * v3f.cross(v3f_2);
   cout << setw(40) << "2.0 * v3f.cross(v3f_2,): " << v3f_4.to_string() << endl;
   v3f_4.assign(0,0,0);
   v3f.cross(v3f_2, v3f_4);
   cout << setw(40) << "v3f.cross(v3f_2, v3f_4): " << v3f_4.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector dot product" << endl;
   Vector2i v2i(1, 2);
   Vector2i v2i_2(3, 4);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector3f v3f_2(4.4, 5.5, 6.6);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector4d v4d_2(5.5, 6.6, 7.7, 8.8);
   int i;
   float f;
   double d;
   cout << setw(40) << "v2i: " << v2i.to_string() << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   i = v2i.dot(v2i_2);
   cout << setw(40) << "i = v2i.dot(v2i_2): " << i << endl;
   f = v3f.dot(v3f_2);
   cout << setw(40) << "f = v3f.dot(v3f_2): " << f << endl;
   d = v4d.dot(v4d_2);
   cout << setw(40) << "d = v4d.dot(v4d_2): " << d << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector length" << endl;
   Vector2i v2i(1, 2);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   cout << setw(40) << "v2i: " << v2i.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v2i.length(): " << v2i.length() << endl;
   cout << setw(40) << "v3f.length(): " << v3f.length() << endl;
   cout << setw(40) << "v4d.length(): " << v4d.length() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector normalize" << endl;
   Vector2f v2f(1.1, 2.2);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   cout << setw(40) << "v2f: " << v2f.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   v2f.normalize();
   cout << setw(40) << "v2f.normalize() " << v2f.to_string() << endl;
   v3f.normalize();
   cout << setw(40) << "v3f.normalize() " << v3f.to_string() << endl;
   v4d.normalize();
   cout << setw(40) << "v4d.normalize() " << v4d.to_string() << endl;
   cout << setw(40) << "v2f.length(): " << v2f.length() << endl;
   cout << setw(40) << "v3f.length(): " << v3f.length() << endl;
   cout << setw(40) << "v4d.length(): " << v4d.length() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector get_angle" << endl;
   Vector2i v2i(1, 2);
   Vector2i v2i_2(3, 4);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector3f v3f_2(4.4, 5.5, 6.6);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector4d v4d_2(5.5, 6.6, 7.7, 8.8);
   double d;
   cout << setw(40) << "v2i: " << v2i.to_string() << endl;
   cout << setw(40) << "v2i_2: " << v2i_2.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   d = v2i.get_angle(v2i_2);
   cout << setw(40) << "d = v2i.get_angle(v2i_2): " << d << endl;
   d = v3f.get_angle(v3f_2);
   cout << setw(40) << "d = v3f.get_angle(v3f_2): " << d << endl;
   d = v4d.get_angle(v4d_2);
   cout << setw(40) << "d = v4d.get_angle(v4d_2): " << d << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector get_anglen" << endl;
   Vector2f v2f(1.1, 2.2);
   Vector2f v2f_2(3.3, 4.4);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector3f v3f_2(4.4, 5.5, 6.6);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector4d v4d_2(5.5, 6.6, 7.7, 8.8);
   double d;
   v2f.normalize();
   v2f_2.normalize();
   v3f.normalize();
   v3f_2.normalize();
   v4d.normalize();
   v4d_2.normalize();
   cout << setw(40) << "v2f: " << v2f.to_string() << endl;
   cout << setw(40) << "v2f_2: " << v2f_2.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   d = v2f.get_anglen(v2f_2);
   cout << setw(40) << "d = v2f.get_anglen(v2f_2): " << d << endl;
   d = v3f.get_anglen(v3f_2);
   cout << setw(40) << "d = v3f.get_anglen(v3f_2): " << d << endl;
   d = v4d.get_anglen(v4d_2);
   cout << setw(40) << "d = v4d.get_anglen(v4d_2): " << d << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Vector get_proj" << endl;
   Vector2f v2f(1.1, 2.2);
   Vector2f v2f_2(3.3, 4.4);
   Vector2f v2f_3(0);
   Vector3f v3f(1.1f, 2.2f, 3.3f);
   Vector3f v3f_2(4.4, 5.5, 6.6);
   Vector3f v3f_3(0);
   Vector4d v4d(1.1, 2.2, 3.3, 4.4);
   Vector4d v4d_2(5.5, 6.6, 7.7, 8.8);
   Vector4d v4d_3(0);
   cout << setw(40) << "v2f: " << v2f.to_string() << endl;
   cout << setw(40) << "v2f_2: " << v2f_2.to_string() << endl;
   cout << setw(40) << "v3f: " << v3f.to_string() << endl;
   cout << setw(40) << "v3f_2: " << v3f_2.to_string() << endl;
   cout << setw(40) << "v4d: " << v4d.to_string() << endl;
   cout << setw(40) << "v4d_2: " << v4d_2.to_string() << endl;
   v2f_3 = v2f.proj(v2f_2);
   cout << setw(40) << "v2f_3 = v2f.proj(v3f_2): " << v2f_3.to_string() << endl;
   v3f_3 = v3f.proj(v3f_2);
   cout << setw(40) << "v3f_3 = v3f.proj(v3f_2): " << v3f_3.to_string() << endl;
   v4d_3 = v4d.proj(v4d_2);
   cout << setw(40) << "v4d_3 = v4d.proj(v4d_2): " << v4d_3.to_string() << endl;
   v2f_3.assign(0,0);
   v3f_3.assign(0,0,0);
   v4d_3.assign(0,0,0,0);
   v2f.proj(v2f_2, v2f_3);
   cout << setw(40) << "v2f.proj(v2f_2, v2f_3): " << v2f_3.to_string() << endl;
   v3f.proj(v3f_2, v3f_3);
   cout << setw(40) << "v3f.proj(v3f_2, v3f_3): " << v3f_3.to_string() << endl;
   v4d.proj(v4d_2, v4d_3);
   cout << setw(40) << "v4d.proj(v4d_2, v4d_3): " << v4d_3.to_string() << endl;
   }

   }

////////////////////////////////////////////////////////////////////////////////
void test_matrix(void)
   {
   string s1, s2;

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix constructors" << endl;
   Matrix22i m22i_1(0);
   Matrix22i m22i_2(1);
   Matrix22i m22i_3(1, 2, 3, 4);
   Matrix22i m22i_4(m22i_3);

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   cout << setw(40) << "m22i_2: " << m22i_2.to_string() << endl;
   cout << setw(40) << "m22i_3: " << m22i_3.to_string() << endl;
   cout << setw(40) << "m22i_4: " << m22i_4.to_string() << endl;

   Matrix33f m33f_1(0.0f);
   Matrix33f m33f_2(1.1f);
   Matrix33f m33f_3(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_4(m33f_3);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   cout << setw(40) << "m33f_2: " << m33f_2.to_string() << endl;
   cout << setw(40) << "m33f_3: " << m33f_3.to_string() << endl;
   cout << setw(40) << "m33f_4: " << m33f_4.to_string() << endl;

   Matrix44d m44d_1(0.0);
   Matrix44d m44d_2(1.1);
   Matrix44d m44d_3(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_4(m44d_3);

   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   cout << setw(40) << "m44d_2: " << m44d_2.to_string() << endl;
   cout << setw(40) << "m44d_3: " << m44d_3.to_string() << endl;
   cout << setw(40) << "m44d_4: " << m44d_4.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix array indexing" << endl;
   Matrix22i m22i(1, 2, 3, 4);

   cout << setw(40) << "m22i: " << m22i[0] << " "  << m22i[1] << " " << m22i[2] << " " << m22i[3] << " "<< endl;

   Matrix33f m33f(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);

   cout << setw(40) << "m33f: " << m33f[0] << " " << m33f[1] << " " << m33f[2] << " " << m33f[3] << " " << m33f[4] << " " << m33f[5] << " " << m33f[6] << " " << m33f[7] << " " << m33f[8] << endl;

   Matrix44d m44d(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		  12.12, 13.13, 14.14, 15.15, 16.16);

   cout << setw(40) << "m44d: " << m44d[0] << " " << m44d[1] << " " << m44d[2] << " " << m44d[3] << " " << m44d[4] << " " << m44d[5] << " " << m44d[6] << " " << m44d[7] << " " << m44d[8] << " " << m44d[9] << " " << m44d[10] << " " << m44d[11] << " " << m44d[12] << " " << m44d[13] << " " << m44d[14] << " " << m44d[15] << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix assignment" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   Matrix22i m22i_2(5, 6, 7, 8);

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   cout << setw(40) << "m22i_2: " << m22i_2.to_string() << endl;

   m22i_2 = m22i_1;
   cout << setw(40) << "m22i_2 = m22i_1: " << m22i_2.to_string() << endl;

   m22i_2.assign(9, 10, 11, 12);
   cout << setw(40) << "m22i_2.assign(9, 10, 11, 12): " 
	<< m22i_2.to_string() << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_2(10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   cout << setw(40) << "m33f_2: " << m33f_2.to_string() << endl;

   m33f_2 = m33f_1;
   cout << setw(40) << "m33f_2 = m33f_1: " << m33f_2.to_string() << endl;

   m33f_2.assign(19.19f, 20.20f, 21.21f, 22.22f, 23.23f, 24.24f, 25.25f, 26.26f, 27.27f);
   cout << setw(40) << "m33f_2.assign(19.19f, 20.20f, ... , 27.27f): " 
	<< m33f_2.to_string() << endl;

   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_2(16.16, 17.17, 18.18, 19.19,
		    20.20, 21.21, 22.22, 23.23,
		    24.24, 25.25, 26.26, 27.27,
		    28.28, 29.29, 30.30, 31.31);

   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   cout << setw(40) << "m44d_2: " << m44d_2.to_string() << endl;

   m44d_2 = m44d_1;
   cout << setw(40) << "m44d_2 = m44d_1: " << m44d_2.to_string() << endl;

   m44d_2.assign(32.32, 33.33, 34.34, 35.35,
		 36.36, 37.37, 38.38, 39.39,
		 40.40, 41.41, 42.42, 43.43,
		 44.44, 45.45, 46.46, 47.47);
   cout << setw(40) << "m44d_2.assign(32.32, 33.33, ... , 47.47): " 
	<< m44d_2.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix comparison" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   Matrix22i m22i_2(1, 2, 3, 4);
   Matrix22i m22i_3(0);

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   cout << setw(40) << "m22i_2: " << m22i_2.to_string() << endl;
   cout << setw(40) << "m22i_3: " << m22i_3.to_string() << endl;
   cout << boolalpha;
   cout << setw(40) << "m22i_1 == m22i_2: " << (m22i_1 == m22i_2) << endl;
   cout << setw(40) << "m22i_1 == m22i_3: " << (m22i_2 == m22i_3) << endl;
   cout << setw(40) << "m22i_1 != m22i_2: " << (m22i_1 != m22i_2) << endl;
   cout << setw(40) << "m22i_1 != m22i_3: " << (m22i_2 != m22i_3) << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_2(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_3(0.0f);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   cout << setw(40) << "m33f_2: " << m33f_2.to_string() << endl;
   cout << setw(40) << "m33f_3: " << m33f_3.to_string() << endl;
   cout << boolalpha;
   cout << setw(40) << "m33f_1 == m33f_2: " << (m33f_1 == m33f_2) << endl;
   cout << setw(40) << "m33f_1 == m33f_3: " << (m33f_2 == m33f_3) << endl;
   cout << setw(40) << "m33f_1 != m33f_2: " << (m33f_1 != m33f_2) << endl;
   cout << setw(40) << "m33f_1 != m33f_3: " << (m33f_2 != m33f_3) << endl;

   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_2(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_3(0.0);

   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   cout << setw(40) << "m44d_2: " << m44d_2.to_string() << endl;
   cout << setw(40) << "m44d_3: " << m44d_3.to_string() << endl;
   cout << boolalpha;
   cout << setw(40) << "m44d_1 == m44d_2: " << (m44d_1 == m44d_2) << endl;
   cout << setw(40) << "m44d_1 == m44d_3: " << (m44d_2 == m44d_3) << endl;
   cout << setw(40) << "m44d_1 != m44d_2: " << (m44d_1 != m44d_2) << endl;
   cout << setw(40) << "m44d_1 != m44d_3: " << (m44d_2 != m44d_3) << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix addition" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   Matrix22i m22i_2(5, 6, 7, 8);
   Matrix22i m22i_3(0);

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   cout << setw(40) << "m22i_2: " << m22i_2.to_string() << endl;
   cout << setw(40) << "m22i_3: " << m22i_3.to_string() << endl;
   m22i_3 = m22i_1 + m22i_2;
   cout << setw(40) << "m22i_3 = m22i_1 + m22i_2: " << m22i_3.to_string() << endl;

   m22i_3 += m22i_1;
   cout << setw(40) << "m22i_3 += m22i_1: " << m22i_3.to_string() << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_2(10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f);
   Matrix33f m33f_3(0.0f);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   cout << setw(40) << "m33f_2: " << m33f_2.to_string() << endl;
   cout << setw(40) << "m33f_3: " << m33f_3.to_string() << endl;
   m33f_3 = m33f_1 + m33f_2;
   cout << setw(40) << "m33f_3 = m33f_1 + m33f_2: " << m33f_3.to_string() << endl;

   m33f_3 += m33f_1;
   cout << setw(40) << "m33f_3 += m33f_1: " << m33f_3.to_string() << endl;

   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_2(16.16, 17.17, 18.18, 19.19,
		    20.20, 21.21, 22.22, 23.23,
		    24.24, 25.25, 26.26, 27.27,
		    28.28, 29.29, 30.30, 31.31);
   Matrix44d m44d_3(0.0);

   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   cout << setw(40) << "m44d_2: " << m44d_2.to_string() << endl;
   cout << setw(40) << "m44d_3: " << m44d_3.to_string() << endl;
   m44d_3 = m44d_1 + m44d_2;
   cout << setw(40) << "m44d_3 = m44d_1 + m44d_2: " << m44d_3.to_string() << endl;

   m44d_3 += m44d_1;
   cout << setw(40) << "m44d_3 += m44d_1: " << m44d_3.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix subtraction" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   Matrix22i m22i_2(5, 6, 7, 8);
   Matrix22i m22i_3(0);

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   cout << setw(40) << "m22i_2: " << m22i_2.to_string() << endl;
   cout << setw(40) << "m22i_3: " << m22i_3.to_string() << endl;
   m22i_3 = m22i_1 - m22i_2;
   cout << setw(40) << "m22i_3 = m22i_1 - m22i_2: " << m22i_3.to_string() << endl;

   m22i_3 -= m22i_1;
   cout << setw(40) << "m22i_3 -= m22i_1: " << m22i_3.to_string() << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_2(10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f);
   Matrix33f m33f_3(0.0f);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   cout << setw(40) << "m33f_2: " << m33f_2.to_string() << endl;
   cout << setw(40) << "m33f_3: " << m33f_3.to_string() << endl;
   m33f_3 = m33f_1 - m33f_2;
   cout << setw(40) << "m33f_3 = m33f_1 - m33f_2: " << m33f_3.to_string() << endl;

   m33f_3 -= m33f_1;
   cout << setw(40) << "m33f_3 -= m33f_1: " << m33f_3.to_string() << endl;

   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_2(16.16, 17.17, 18.18, 19.19,
		    20.20, 21.21, 22.22, 23.23,
		    24.24, 25.25, 26.26, 27.27,
		    28.28, 29.29, 30.30, 31.31);
   Matrix44d m44d_3(0.0);

   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   cout << setw(40) << "m44d_2: " << m44d_2.to_string() << endl;
   cout << setw(40) << "m44d_3: " << m44d_3.to_string() << endl;
   m44d_3 = m44d_1 - m44d_2;
   cout << setw(40) << "m44d_3 = m44d_1 - m44d_2: " << m44d_3.to_string() << endl;

   m44d_3 -= m44d_1;
   cout << setw(40) << "m44d_3 -= m44d_1: " << m44d_3.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Matrix scalar multiplication" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   Matrix22i m22i_2(0);
   int i = 2;

   cout << setw(40) << "i: " << i << endl;
   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   cout << setw(40) << "m22i_2: " << m22i_2.to_string() << endl;
   m22i_2 = m22i_1 *i;
   cout << setw(40) << "m22i_2 = m22i_1 * i: " << m22i_2.to_string() << endl;
   m22i_2 = i * m22i_1;
   cout << setw(40) << "m22i_2 = i * m22i_1: " << m22i_2.to_string() << endl;
   m22i_2 *= i;
   cout << setw(40) << "m22i_2 *= i: " << m22i_2.to_string() << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_2(0.0f);
   float f = 2.0f;

   cout << setw(40) << "f: " << f << endl;
   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   cout << setw(40) << "m33f_2: " << m33f_2.to_string() << endl;
   m33f_2 = m33f_1 * f;
   cout << setw(40) << "m33f_2 = m33f_1 * f: " << m33f_2.to_string() << endl;
   m33f_2 = f * m33f_1;
   cout << setw(40) << "m33f_2 = f * m33f_1: " << m33f_2.to_string() << endl;
   m33f_2 *= f;
   cout << setw(40) << "m33f_2 *= f: " << m33f_2.to_string() << endl;

   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_2(0.0);
   double d = 2.0f;

   cout << setw(40) << "d: " << d << endl;
   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   cout << setw(40) << "m44d_2: " << m44d_2.to_string() << endl;
   m44d_2 = m44d_1 * d;
   cout << setw(40) << "m44d_2 = m44d_1 * d: " << m44d_2.to_string() << endl;
   m44d_2 = d * m44d_1;
   cout << setw(40) << "m44d_2 = d * m44d_1: " << m44d_2.to_string() << endl;
   m44d_2 *= d;
   cout << setw(40) << "m44d_2 *= d: " << m44d_2.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Matrix scalar division" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   Matrix22i m22i_2(0);
   int i = 2;

   cout << setw(40) << "i: " << i << endl;
   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   cout << setw(40) << "m22i_2: " << m22i_2.to_string() << endl;
   m22i_2 = m22i_1 / i;
   cout << setw(40) << "m22i_2 = m22i_1 / i: " << m22i_2.to_string() << endl;
   m22i_1 /= i;
   cout << setw(40) << "m22i_1 /= i: " << m22i_2.to_string() << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_2(0.0f);
   float f = 2.0f;

   cout << setw(40) << "f: " << f << endl;
   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   cout << setw(40) << "m33f_2: " << m33f_2.to_string() << endl;
   m33f_2 = m33f_1 / f;
   cout << setw(40) << "m33f_2 = m33f_1 / f: " << m33f_2.to_string() << endl;
   m33f_1 /= f;
   cout << setw(40) << "m33f_1 /= f: " << m33f_2.to_string() << endl;

   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_2(0.0);
   double d = 2.0f;

   cout << setw(40) << "d: " << d << endl;
   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   cout << setw(40) << "m44d_2: " << m44d_2.to_string() << endl;
   m44d_2 = m44d_1 / d;
   cout << setw(40) << "m44d_2 = m44d_1 / d: " << m44d_2.to_string() << endl;
   m44d_1 /= d;
   cout << setw(40) << "m44d_1 /= d: " << m44d_2.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix multiplication" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   Matrix22i m22i_2(5, 6, 7, 8);
   Matrix22i m22i_3(0);

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   cout << setw(40) << "m22i_2: " << m22i_2.to_string() << endl;
   cout << setw(40) << "m22i_3: " << m22i_3.to_string() << endl;
   m22i_3 = m22i_1 * m22i_2;
   cout << setw(40) << "m22i_3 = m22i_1 * m22i_2: " << m22i_3.to_string() << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_2(10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f, 17.17f, 18.18f);
   Matrix33f m33f_3(0.0f);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   cout << setw(40) << "m33f_2: " << m33f_2.to_string() << endl;
   cout << setw(40) << "m33f_3: " << m33f_3.to_string() << endl;
   m33f_3 = m33f_1 * m33f_2;
   cout << setw(40) << "m33f_3 = m33f_1 * m33f_2: " << m33f_3.to_string() << endl;

   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_2(16.16, 17.17, 18.18, 19.19,
		    20.20, 21.21, 22.22, 23.23,
		    24.24, 25.25, 26.26, 27.27,
		    28.28, 29.29, 30.30, 31.31);
   Matrix44d m44d_3(0.0);

   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   cout << setw(40) << "m44d_2: " << m44d_2.to_string() << endl;
   cout << setw(40) << "m44d_3: " << m44d_3.to_string() << endl;
   m44d_3 = m44d_1 * m44d_2;
   cout << setw(40) << "m44d_3 = m44d_1 * m44d_2: " << m44d_3.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix det" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   double d;

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   d = det(m22i_1);
   cout << setw(40) << "d = det(m22i_1): " << d << endl;

   // Note: singular matrix.  The real determinant is exactly zero.
   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   d = det(m33f_1);
   cout << setw(40) << "d = det(m33f_1): " << d << endl;

   // Note: singular matrix.  The real determinant is exactly zero.
   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		  12.12, 13.13, 14.14, 15.15, 16.16);

   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   d = det(m44d_1);
   cout << setw(40) << "d = det(m44d_1): " << d << endl;

   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix transpose" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   Matrix22i m22i_2;

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   m22i_2 = transpose(m22i_1);
   cout << setw(40) << "m22i_2 = transpose(m22i_1): " << m22i_2.to_string() << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Matrix33f m33f_2(0.0f);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   m33f_2 = transpose(m33f_1);
   cout << setw(40) << "m33f_2 = transpose(m33f_1): " << m33f_2.to_string() << endl;

   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Matrix44d m44d_2(0.0);

   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   m44d_2 = transpose(m44d_1);
   cout << setw(40) << "m44d_2 = transpose(m44d_1): " << m44d_2.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Maxtrix setidentity" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   m22i_1.setidentity();
   cout << setw(40) << "m22i_1.setidentity(): " << m22i_1.to_string() << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   m33f_1.setidentity();
   cout << setw(40) << "m33f_1.setidentity(): " << m33f_1.to_string() << endl;
   
   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   
   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   m44d_1.setidentity();
   cout << setw(40) << "m44d_1.setidentity(): " << m44d_1.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Matrix getrow() and getcol()" << endl;
   Matrix22i m22i_1(1, 2, 3, 4);
   Vector2i v2i_1(0);

   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   v2i_1 = m22i_1.getrow(0);
   cout << setw(40) << "v2i_1 = m22i_1.getrow(0): " << v2i_1.to_string() << endl;
   v2i_1 = m22i_1.getrow(1);
   cout << setw(40) << "v2i_1 = m22i_1.getrow(1): " << v2i_1.to_string() << endl;
   v2i_1 = m22i_1.getcol(0);
   cout << setw(40) << "v2i_1 = m22i_1.getcol(0): " << v2i_1.to_string() << endl;
   v2i_1 = m22i_1.getcol(1);
   cout << setw(40) << "v2i_1 = m22i_1.getcol(1): " << v2i_1.to_string() << endl;

   Matrix33f m33f_1(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f);
   Vector3f v3f_1(0);

   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   v3f_1 = m33f_1.getrow(0);
   cout << setw(40) << "v3f_1 = m33f_1.getrow(0): " << v3f_1.to_string() << endl;
   v3f_1 = m33f_1.getrow(1);
   cout << setw(40) << "v3f_1 = m33f_1.getrow(1): " << v3f_1.to_string() << endl;
   v3f_1 = m33f_1.getrow(2);
   cout << setw(40) << "v3f_1 = m33f_1.getrow(2): " << v3f_1.to_string() << endl;
   v3f_1 = m33f_1.getcol(0);
   cout << setw(40) << "v3f_1 = m33f_1.getcol(0): " << v3f_1.to_string() << endl;
   v3f_1 = m33f_1.getcol(1);
   cout << setw(40) << "v3f_1 = m33f_1.getcol(1): " << v3f_1.to_string() << endl;
   v3f_1 = m33f_1.getcol(2);
   cout << setw(40) << "v3f_1 = m33f_1.getcol(2): " << v3f_1.to_string() << endl;

   Matrix44d m44d_1(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11,
		    12.12, 13.13, 14.14, 15.15, 16.16);
   Vector4d v4d_1(0);

   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   v4d_1 = m44d_1.getrow(0);
   cout << setw(40) << "v4d_1 = m44d_1.getrow(0): " << v4d_1.to_string() << endl;
   v4d_1 = m44d_1.getrow(1);
   cout << setw(40) << "v4d_1 = m44d_1.getrow(1): " << v4d_1.to_string() << endl;
   v4d_1 = m44d_1.getrow(2);
   cout << setw(40) << "v4d_1 = m44d_1.getrow(2): " << v4d_1.to_string() << endl;
   v4d_1 = m44d_1.getrow(3);
   cout << setw(40) << "v4d_1 = m44d_1.getrow(3): " << v4d_1.to_string() << endl;

   v4d_1 = m44d_1.getcol(0);
   cout << setw(40) << "v4d_1 = m44d_1.getcol(0): " << v4d_1.to_string() << endl;
   v4d_1 = m44d_1.getcol(1);
   cout << setw(40) << "v4d_1 = m44d_1.getcol(1): " << v4d_1.to_string() << endl;
   v4d_1 = m44d_1.getcol(2);
   cout << setw(40) << "v4d_1 = m44d_1.getcol(2): " << v4d_1.to_string() << endl;
   v4d_1 = m44d_1.getcol(3);
   cout << setw(40) << "v4d_1 = m44d_1.getcol(3): " << v4d_1.to_string() << endl;
   }

   {
   cout << "===============================================================" << endl <<
	 "Testing Matrix setrow() and setcol()" << endl;
   Matrix22i m22i_1;
   Vector2i v2i_1(2, 3);

   m22i_1.setidentity();
   cout << setw(40) << "m22i_1: " << m22i_1.to_string() << endl;
   m22i_1.setrow(0, v2i_1);
   cout << setw(40) << "m22i_1.setrow(0, v2i_1): " << m22i_1.to_string() << endl;

   m22i_1.setidentity();
   m22i_1.setrow(1, v2i_1);
   cout << setw(40) << "m22i_1.setrow(1, v2i_1): " << m22i_1.to_string() << endl;

   m22i_1.setidentity();
   m22i_1.setrow(1, 4, 5);
   cout << setw(40) << "m22i_1.setrow(1, 4, 5): " << m22i_1.to_string() << endl;

   m22i_1.setidentity();
   m22i_1.setcol(0, v2i_1);
   cout << setw(40) << "m22i_1.setcol(0, v2i_1): " << m22i_1.to_string() << endl;

   m22i_1.setidentity();
   m22i_1.setcol(1, v2i_1);
   cout << setw(40) << "m22i_1.setcol(1, v2i_1): " << m22i_1.to_string() << endl;

   m22i_1.setidentity();
   m22i_1.setcol(1, 4, 5);
   cout << setw(40) << "m22i_1.setcol(1, 4, 5): " << m22i_1.to_string() << endl;

   Matrix33f m33f_1;
   Vector3f v3f_1(0);

   m33f_1.setidentity();
   cout << setw(40) << "m33f_1: " << m33f_1.to_string() << endl;
   m33f_1.setrow(0, v3f_1);
   cout << setw(40) << "m33f_1.setrow(0, v3f_1): " << m33f_1.to_string() << endl;

   m33f_1.setidentity();
   m33f_1.setrow(1, v3f_1);
   cout << setw(40) << "m33f_1.setrow(1, v3f_1): " << m33f_1.to_string() << endl;

   m33f_1.setidentity();
   m33f_1.setrow(1, 2.2f, 3.3f, 4.4f);
   cout << setw(40) << "m33f_1.setrow(1, 2.2f, 3.3f, 4.4f): " 
	<< m33f_1.to_string() << endl;

   m33f_1.setidentity();
   m33f_1.setcol(0, v3f_1);
   cout << setw(40) << "m33f_1.setcol(0, v3f_1): " << m33f_1.to_string() << endl;

   m33f_1.setidentity();
   m33f_1.setcol(1, v3f_1);
   cout << setw(40) << "m33f_1.setcol(1, v3f_1): " << m33f_1.to_string() << endl;

   m33f_1.setidentity();
   m33f_1.setcol(1, 2.2f, 3.3f, 4.4f);
   cout << setw(40) << "m33f_1.setcol(1, 2.2f, 3.3f, 4.4f: " 
	<< m33f_1.to_string() << endl;

   Matrix44d m44d_1;
   Vector4d v4d_1(0);

   m44d_1.setidentity();
   cout << setw(40) << "m44d_1: " << m44d_1.to_string() << endl;
   m44d_1.setrow(0, v4d_1);
   cout << setw(40) << "m44d_1.setrow(0, v4d_1): " << m44d_1.to_string() << endl;

   m44d_1.setidentity();
   m44d_1.setrow(1, v4d_1);
   cout << setw(40) << "m44d_1.setrow(1, v4d_1): " << m44d_1.to_string() << endl;

   m44d_1.setidentity();
   m44d_1.setrow(1, 2.2, 3.3, 4.4, 5.5);
   cout << setw(40) << "m44d_1.setrow(1, 2.2, 3.3, 4.4, 5.5): " 
	<< m44d_1.to_string() << endl;

   m44d_1.setidentity();
   m44d_1.setcol(0, v4d_1);
   cout << setw(40) << "m44d_1.setcol(0, v4d_1): " << m44d_1.to_string() << endl;

   m44d_1.setidentity();
   m44d_1.setcol(1, v4d_1);
   cout << setw(40) << "m44d_1.setcol(1, v4d_1): " << m44d_1.to_string() << endl;

   m44d_1.setidentity();
   m44d_1.setcol(1, 2.2, 3.3, 4.4, 5.5);
   cout << setw(40) << "m44d_1.setcol(1, 2.2, 3.3, 4.4, 5.5: " 
	<< m44d_1.to_string() << endl;
   }
   }

////////////////////////////////////////////////////////////////////////////////
void test_all(void)
   {
   test_vector();
   test_matrix();
   }

////////////////////////////////////////////////////////////////////////////////
void show_menu(void)
   {
   cout << endl << endl
	<< "Test what?" << endl
	<< "0)      All" << endl << endl
	<< "1)      Vector" << endl
	<< "2)      Matrix" << endl
	<< endl
	<< "99      Quit" << endl;
   }

////////////////////////////////////////////////////////////////////////////////
int main (int argc, char * argv[]) 
   {
   int retval = 0;

   test_all();
   return 0;

   try
      {
      int choice = -1;
      
      while (choice != 99)
	 {
	 show_menu();
	 cin >> choice;
	 if(!cin)
	    {
	    cin.clear();
	    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	    }
	 if (choice != 99)
	    {
	    switch (choice)
	       {
	       case 0:
		  test_all();
		  break;
	       case 1:
		  test_vector();
		  break;
	       case 2:
		  test_matrix();
		  break;
	       default:
		  cout << "Unrecognized choice.  Please try again." << endl;
	       }
	    choice = -1;
	    }
	 }
      }
   catch (const std::exception & error)
      {
      string e = "Caught exception: ";
      e += error.what();
      cerr << e << endl;
      retval = 1;
      }

   return retval;;

   }

#endif
