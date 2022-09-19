#if !defined(VECLIB_SSEPVEC_H) && VECLIB_SSE_VER>=0x10
#define VECLIB_SSEPVEC_H

#include "ssef32.h"
#include "ssevecf32.h"

// Wektorek 'upakowany'; W przeciwienstwie do VecN<f32x4> nie zawiera
// N * 4 wartoci, ale jedynie N (pozostale skadowe rejestru SSE sa ignorowane)
// Komponenty sa read-only; bo przy przypisaniu traciloby sie czesc informacji
// Generalnie korzystanie z takich wektorow o N<4 to marnotrastwo mocy

class pvec2f32;
class pvec3f32;
class pvec4f32;

// -----------------------------------------------------------------------------------------------------------
#define CLASS_NAME pvec2f32
#define ADDITIONAL_CLASS_CODE \
	INLINE explicit pvec2f32(const pvec3f32 &v); \
	INLINE explicit pvec2f32(const pvec4f32 &v); \
	INLINE pvec2f32(float x,float y) { m=_mm_load2(x,y); } \
	INLINE pvec2f32(const Vec2<float> &v) { m=_mm_load2(v.x,v.y); } \
	INLINE operator Vec2<float>() const { return Vec2<float>(x,y); } \
	/*INLINE operator vec2f32x4() const { vec2f32x4 out; out=vec2f32x4(f32x4(x),f32x4(y)); return out; }*/ \
	union { __m128 m; struct { float x,y,t0,t1; }; };


#include "ssepvecf32_gen.h"

#undef ADDITIONAL_CLASS_CODE
#undef CLASS_NAME
// -----------------------------------------------------------------------------------------------------------
#define CLASS_NAME pvec3f32
#define ADDITIONAL_CLASS_CODE \
	INLINE explicit pvec3f32(const pvec2f32 &v); \
	INLINE explicit pvec3f32(const pvec4f32 &v); \
	INLINE pvec3f32(float x,float y,float z) { m=_mm_load3(x,y,z); } \
	INLINE pvec3f32(const Vec3<float> &v) { m=_mm_load3(v.x,v.y,v.z); } \
	INLINE operator Vec3<float>() const { return Vec3<float>(x,y,z); } \
	/*INLINE operator vec3f32x4() const { vec3f32x4 out; out=vec3f32x4(f32x4(x),f32x4(y),f32x4(z)); return out; }*/ \
	union { __m128 m; struct { float x,y,z,t0; }; };

#include "ssepvecf32_gen.h"

#undef ADDITIONAL_CLASS_CODE
#undef CLASS_NAME
// -----------------------------------------------------------------------------------------------------------
#define CLASS_NAME pvec4f32
#define ADDITIONAL_CLASS_CODE \
	INLINE explicit pvec4f32(const pvec2f32 &v) { m=_mm_shuffle_ps(v.m,_mm_setzero_ps(),0+(1<<2)); } \
	INLINE explicit pvec4f32(const pvec3f32 &v) { \
		__m128 zzww=_mm_shuffle_ps(v.m,_mm_setzero_ps(),0); \
		m=_mm_shuffle_ps(v.m,zzww,0+(1<<2)+(0<<4)+(2<<6)); \
	} \
	INLINE pvec4f32(float x,float y,float z,float w) { m=_mm_set_ps(w,z,y,x); } \
	INLINE pvec4f32(const Vec4<float> &v) { m=_mm_set_ps(v.x,v.y,v.z,v.w); } \
	INLINE operator Vec4<float>() const { return Vec4<float>(x,y,z,w); } \
	/*INLINE operator vec4f32x4() const { vec4f32x4 out; out=vec4f32x4(f32x4(x),f32x4(y),f32x4(z),f32x4(w)); return out; }*/ \
	union { __m128 m; struct { float x,y,z,w; }; };

#include "ssepvecf32_gen.h"

#undef ADDITIONAL_CLASS_CODE
#undef CLASS_NAME
// -----------------------------------------------------------------------------------------------------------

pvec3f32::pvec3f32(const pvec2f32 &v) :m(_mm_shuffle_ps(v.m,_mm_setzero_ps(),0+(1<<2))) { }
pvec3f32::pvec3f32(const pvec4f32 &v) :m(v.m) { }

pvec2f32::pvec2f32(const pvec3f32 &v) :m(v.m) { }
pvec2f32::pvec2f32(const pvec4f32 &v) :m(v.m) { }


INLINE float operator|(const pvec2f32 &a,const pvec2f32 &b) {
	union { float out[4]; __m128 t; };

	t=_mm_mul_ps(a.m,b.m);
	t=_mm_add_ss(t,_mm_shuffle_ps(t,t,1));

	return out[0];
}
INLINE float operator|(const pvec3f32 &a,const pvec3f32 &b) {
	__m128 t;
	float out;

	t=_mm_mul_ps(a.m,b.m);
	t=_mm_add_ss(/*Z*/_mm_movehl_ps(t,t),_mm_add_ss(/*X*/t,/*Y*/_mm_shuffle_ps(t,t,1)));
	_mm_store_ss(&out,t);

	return out;
}
INLINE float operator|(const pvec4f32 &a,const pvec4f32 &b) {
	union { float out[4]; __m128 t; };
	t=_mm_mul_ps(a.m,b.m);
	t=_mm_add_ps(t,_mm_shuffle_ps(t,t,0x4E));
	t=_mm_add_ps(t,_mm_shuffle_ps(t,t,0x11));
	return out[0];
}

INLINE float Length(const pvec2f32 &v)		{ return Sqrt(v|v); }
INLINE float LengthSq(const pvec2f32 &v)	{ return v|v; }
INLINE float Length(const pvec3f32 &v)		{ return Sqrt(v|v); }
INLINE float LengthSq(const pvec3f32 &v)	{ return v|v; }
INLINE float Length(const pvec4f32 &v)		{ return Sqrt(v|v); }
INLINE float LengthSq(const pvec4f32 &v)	{ return v|v; }

INLINE pvec3f32 operator^(const pvec3f32 &a,const pvec3f32 &b)
{
	pvec3f32 out;

	/*	ay*bz	-	by*az
		az*bx	-	bz*ax
		ax*by	-	bx*ay	*/
	__m128 a1=_mm_shuffle_ps(a.m,a.m,201);	// y,z,x,w
	__m128 b1=_mm_shuffle_ps(b.m,b.m,210);	// z,x,y,w
	__m128 a2=_mm_shuffle_ps(a.m,a.m,210);	// z,x,y,w
	__m128 b2=_mm_shuffle_ps(b.m,b.m,201);	// y,z,x,w

	out.m=_mm_sub_ps(_mm_mul_ps(a1,b1),_mm_mul_ps(a2,b2));
	return out;
}

INLINE void Convert(const Vec2<float> &v,pvec2f32 &out)	{ out.m=_mm_load2(&v.x); }
INLINE void Convert(const float v[2],pvec2f32 &out)		{ out.m=_mm_load2(v+0); }
INLINE void Convert(const pvec2f32 &v,Vec2<float> &out)	{ _mm_store2(v.m,&out.x); }
INLINE void Convert(const pvec2f32 &v,float out[2])		{ _mm_store2(v.m,out+0); }

INLINE void Convert(const Vec3<float> &v,pvec3f32 &out)	{ out.m=_mm_load3(&v.x); }
INLINE void Convert(const float v[3],pvec3f32 &out)		{ out.m=_mm_load3(v+0); }
INLINE void Convert(const pvec3f32 &v,Vec3<float> &out)	{ _mm_store3(v.m,&out.x); }
INLINE void Convert(const pvec3f32 &v,float out[3])		{ _mm_store3(v.m,out+0); }

INLINE void Convert(const Vec4<float> &v,pvec4f32 &out)	{ out.m=_mm_load4(&v.x); }
INLINE void Convert(const float v[4],pvec4f32 &out)		{ out.m=_mm_load4(v+0); }
INLINE void Convert(const pvec4f32 &v,Vec4<float> &out)	{ _mm_store4(v.m,&out.x); }
INLINE void Convert(const pvec4f32 &v,float out[4])		{ _mm_store4(v.m,out+0); }


INLINE void Convert(const vec2f32x4 &in,pvec2f32 out[4]) {
	_mm_transpose(	in.x.m,in.y.m,in.y.m,in.y.m,
					out[0].m,out[1].m,out[2].m,out[3].m);
}

INLINE void Convert(const vec3f32x4 &in,pvec3f32 out[4]) {
	_mm_transpose(	in.x.m,in.y.m,in.z.m,in.z.m,
					out[0].m,out[1].m,out[2].m,out[3].m);
}
INLINE void Convert(const pvec3f32 in[4],vec3f32x4 &out) {
	__m128 tmp3, tmp2, tmp1, tmp0;
	tmp0=_mm_shuffle_ps(in[0].m, in[1].m, 0x44);
	tmp2=_mm_shuffle_ps(in[0].m, in[1].m, 0xEE);
	tmp1=_mm_shuffle_ps(in[2].m, in[3].m, 0x44);
	tmp3=_mm_shuffle_ps(in[2].m, in[3].m, 0xEE);

	out.x.m=_mm_shuffle_ps(tmp0, tmp1, 0x88);
	out.y.m=_mm_shuffle_ps(tmp0, tmp1, 0xDD);
	out.z.m=_mm_shuffle_ps(tmp2, tmp3, 0x88);
}

INLINE void Convert(const vec4f32x4 &in,pvec4f32 out[4]) {
	_mm_transpose(	in.x.m,in.y.m,in.z.m,in.w.m,
					out[0].m,out[1].m,out[2].m,out[3].m);
}
INLINE void Convert(const pvec4f32 in[4],vec4f32x4 &out) {
	__m128 tmp3, tmp2, tmp1, tmp0;
	tmp0=_mm_shuffle_ps(in[0].m, in[1].m, 0x44);
	tmp2=_mm_shuffle_ps(in[0].m, in[1].m, 0xEE);
	tmp1=_mm_shuffle_ps(in[2].m, in[3].m, 0x44);
	tmp3=_mm_shuffle_ps(in[2].m, in[3].m, 0xEE);

	out.x.m=_mm_shuffle_ps(tmp0, tmp1, 0x88);
	out.y.m=_mm_shuffle_ps(tmp0, tmp1, 0xDD);
	out.z.m=_mm_shuffle_ps(tmp2, tmp3, 0x88);
	out.w.m=_mm_shuffle_ps(tmp2, tmp3, 0xDD);
}



#endif

