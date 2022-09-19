/*! \file sse.hpp
    \brief A thin wrapper on top of Cvalarray and Veclib for writing neat SSE code
    Copyright 2009 Tuomas Tonteri. This file is licensed as public domain.
*/

#ifndef SSE_HPP
#define SSE_HPP

#include "cvalarray.hpp"
#include "veclib/veclib.h"
#include <iostream>

/* Nice notation based on GLSL language. Add "p" in front for double precision
vec2,vec3,vec4               floating point vector
vec2b,vec3b,vec4b            mask type for floating point vector
ivec2,ivec3,ivec4            signed integer vector
ivec2b,ivec3b,ivec4b	     mask type for signed integer vector
uvec2,uvec3,uvec4	     unsigned integer vector
mat4x2,mat4x3,mat4x4         4 column matrix
*/

// Note: veclib only fully implements f32x4 and i32x4 and their masks
typedef veclib::f32x4 vec4;
typedef veclib::f32x4b vec4b;
typedef veclib::i32x4 ivec4;
typedef veclib::i32x4b ivec4b;
// Implement useful types with cvalarray
typedef n_std::cvalarray<vec4,2> mat4x2;
typedef n_std::cvalarray<vec4,3> mat4x3;
typedef n_std::cvalarray<vec4,4> mat4x4;
typedef n_std::cvalarray<float,2> vec2;
typedef n_std::cvalarray<float,3> vec3;
typedef n_std::cvalarray<double,2> pvec2;
typedef n_std::cvalarray<double,3> pvec3;

// A couple of helper functions. Add your own as needed.
inline float sum(const vec3& v)
{
return v[0] + v[1] + v[2];
}

inline vec4 sum(const mat4x3& v)
{
return v[0] + v[1] + v[2];
}

inline double sum(const pvec3& v)
{
return v[0]+v[1]+v[2];
}

inline float sum(const vec4& v) // SSE3 horizontal sum (add to veclib)
{
return v[0]+v[1]+v[2]+v[3];
/*
float result;
__m128 num3 = _mm_hadd_ps(v.m, v.m);
       num3 = _mm_hadd_ps(num3, num3);
_mm_store_ss(&result,num3);
return result;
*/
}

// Overloaded << to ease debugging for vector types

inline std::ostream& operator<< (std::ostream& output, const vec3& v)
{
output << "vec3: " <<  v[0] << "\t" << v[1] << "\t" << v[2] << std::endl;
//output << v[0] << "\t" << v[1] << "\t" << v[2] << std::endl;
return output;
}

inline std::ostream& operator<< (std::ostream& output, const vec4& v)
{
output << "vec4: " <<  v[0] << "\t" << v[1] << "\t" << v[2] << "\t" << v[3] << std::endl;
return output;
}

inline std::ostream& operator<< (std::ostream& output, const vec4b& v2)
{
float* v = (float*)&v2.m;
output << "vec4b: " <<  v[0] << "\t" << v[1] << "\t" << v[2] << "\t" << v[3] << std::endl;
return output;
}

inline std::ostream& operator<< (std::ostream& output, const veclib::i32x4& v)
{
output << "ivec4: " <<  v[0] << "\t" << v[1] << "\t" << v[2] << "\t" << v[3] << std::endl;
return output;
}

inline std::ostream& operator<< (std::ostream& output, const mat4x3& v)
{
for (int i=0;i<3;i++)
	output << "mat4x3 " << std::endl <<i <<"):" <<  v[i][0] << "\t" << v[i][1] << "\t" << v[i][2] << "\t" << v[i][3] << std::endl;
return output;
}

inline std::ostream& operator<< (std::ostream& output, const mat4x4& v)
{
for (int i=0;i<4;i++)
        output << "mat4x4(" << i << "):" <<  v[i][0] << "\t" << v[i][1] << "\t" << v[i][2] << "\t" << v[i][3] << std::endl;
return output;
}

// Veclib has no facility to touch elements in masks..
inline void ToggleMaskOn(int pos, vec4b& mask)
{
   static int ftrue = 0xFFFFFFFF;
   float* fmask= (float*)&mask.m;
   memcpy((void*)&fmask[pos], (void*)&ftrue, 4);
   }
__inline__ void ToggleMaskOff(int pos, vec4b& mask)
{
   static int ffalse = 0x00000000;
   float* fmask= (float*)&mask.m;
   memcpy((void*)&fmask[pos], (void*)&ffalse, 4);
}

#endif
