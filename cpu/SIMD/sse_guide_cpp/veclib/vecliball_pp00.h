namespace veclib
{
union UValue32
{
   UValue32(u32 v) : u(v)
   {
   }
   UValue32(i32 v) : i(v)
   {
   }
   UValue32(f32 v) : f(v)
   {
   }
   f32 f;
   i32 i;
   u32 u;
};
union UValue64
{
   UValue64(u64 v) : u(v)
   {
   }
   UValue64(i64 v) : i(v)
   {
   }
   UValue64(f64 v) : f(v)
   {
   }
   f64 f;
   i64 i;
   u64 u;
};
typedef UValue32   UValue;
template <class Dst, class Src>
Dst BitCast(const Src&src)
{
   union {
      Dst d;
      Src s;
   } u;
   u.s = src;
   return(u.d);
}

template <class Base, int m, int n> struct CConst {
   static Base Value()
   {
      return(Base(m) / Base(n));
   }
};
template <class Base, bool v> struct CBConst {
   static Base Value()
   {
      return(Base(v));
   }
};
template <class Base, int m, int n> Base Const()
{
   return(CConst <Base, m, n>::Value());
}
template <class Base, int m> Base Const()
{
   return(CConst <Base, m, 1>::Value());
}
template <class Base, bool v> Base BConst()
{
   return(CBConst <Base, v>::Value());
}
template <class Base> Base ConstPI()
{
   return(Const <Base, 245850922, 78256779>());
};
template <class Base> Base Const2PI()
{
   return(Const <Base, 2 *245850922, 78256779>());
};
template <class Base> Base ConstInvPI()
{
   return(Const <Base, 78256779, 245850922>());
};
template <class Base> Base ConstInv2PI()
{
   return(Const <Base, 78256779, 2 *245850922>());
};
template <class Base> Base ConstEpsilon()
{
   return(Const <Base, 1, 10000>());
};
template <class T>
struct ScalarInfo
{
   enum {
      multiplicity = 1, floatingPoint = 1
   };
   typedef bool   TBool;
   __inline__ static bool ElementMask(int n)
   {
      return(1);
   }
};
__inline__ float Sqrt(float v)
{
   return(sqrtf(v));
}
__inline__ float Inv(float v)
{
   return(1.0f / v);
}
__inline__ float RSqrt(float v)
{
   return(1.0f / Sqrt(v));
}
__inline__ float FastInv(float v)
{
   return(Inv(v));
}
__inline__ float FastRSqrt(float v)
{
   return(RSqrt(v));
}
__inline__ float Condition(bool expr, float a, float b)
{
   return(expr ? a : b);
}
__inline__ float Condition(bool expr, float v)
{
   return(expr ? v : 0.0f);
}
__inline__ int SignMask(float v)
{
   return(v < 0.0f ? 1 : 0);
}
__inline__ float Abs(float v)
{
   return(v < 0.0f ? -v : v);
}
__inline__ int Round(float f)
{
   return(int (f + 0.5f));
}
__inline__ int Trunc(float f)
{
   return(int (f));
}
__inline__ float Sin(float rad)
{
   return(sin(rad));
}
__inline__ float Cos(float rad)
{
   return(cos(rad));
}
__inline__ float FRand()
{
   return(float (rand()) / float (RAND_MAX));
}
__inline__ bool ForAny(bool expr)
{
   return(expr);
}
__inline__ bool ForAll(bool expr)
{
   return(expr);
}
__inline__ int ForWhich(bool expr)
{
   return(expr ? 1 : 0);
}
template <class T, class T1> __inline__ T Max(const T&a, const T1&b)
{
   return(a > b ? a : b);
}
template <class T, class T1> __inline__ T Min(const T&a, const T1&b)
{
   return(a < b ? a : b);
}
template <class T> __inline__ T Clamp(const T&obj, const T&min, const T&max)
{
   return(Min(Max(obj, min), max));
}
template <class T> __inline__ T VClamp(const T&obj, const T&min, const T&max)
{
   return(VMin(VMax(obj, min), max));
}
template <class Obj, class Scl> __inline__ Obj Lerp(const Obj&a, const Obj&b, const Scl&x)
{
   return(a + (b - a) * x);
}
template <class Obj, class Scl> __inline__ Obj VLerp(const Obj&a, const Obj&b, const Scl&x)
{
   return(a + (b - a) * x);
}
template <class T> __inline__ void Swap(T&a, T&b)
{
   T temp(a);
   a = b;
   b = temp;
}

template <class T> __inline__ void Convert(const T&in, T&out)
{
   out = in;
}
template <class base> class Vec3;
template <class base> class Vec4;
template <class base>
class Vec2 {
public:
   typedef base                                TScalar;
   typedef typename ScalarInfo <base>::TBool   TBool;
   __inline__ Vec2()
   {
   }
   __inline__ Vec2(const base&t) : x(t), y(t)
   {
   }
   __inline__ Vec2(const base arr[2]) : x(arr[0]), y(arr[1])
   {
   }
   __inline__ Vec2(const base&tx, const base&ty) : x(tx), y(ty)
   {
   }
   __inline__ Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y)
   {
   }
   __inline__ const Vec2&operator=(const Vec2&rhs)
   {
      x = rhs.x;
      y = rhs.y;
      return(*this);
   }
   template <class VEC>
   __inline__ explicit Vec2(const VEC&v) : x(v.x), y(v.y)
   {
   }
   explicit __inline__ Vec2(const Vec3 <base>&);
   explicit __inline__ Vec2(const Vec4 <base>&);
   template <class GenericVec3> __inline__ const Vec2&operator +=(const GenericVec3&v)
   {
      x += v.x;
      y += v.y;
      return(*this);
   }
   template <class GenericVec3> __inline__ const Vec2&operator -=(const GenericVec3&v)
   {
      x -= v.x;
      y -= v.y;
      return(*this);
   }
   template <class GenericVec3> __inline__ const Vec2&operator *=(const GenericVec3&v)
   {
      x *= v.x;
      y *= v.y;
      return(*this);
   }
   template <class GenericVec3> __inline__ const Vec2&operator /=(const GenericVec3&v)
   {
      x /= v.x;
      y /= v.y;
      return(*this);
   }
   __inline__ TBool operator==(const Vec2&rhs) const
   {
      return(x == rhs.x && y == rhs.y);
   }
   __inline__ TBool operator!=(const Vec2&rhs) const
   {
      return(x != rhs.x || y != rhs.y);
   }
   __inline__ const Vec2&operator*=(const base&s)
   {
      x *= s;
      y *= s;
      return(*this);
   }

   __inline__ const Vec2&operator/=(const base&s)
   {
      base inv = Inv(s);

      x *= inv;
      y *= inv;
      return(*this);
   }

   __inline__ Vec2 operator-() const
   {
      Vec2 out;

      out.x = -x;
      out.y = -y;
      return(out);
   }

   base x, y;
};
template <class base> class Vec4;
template <class base>
class Vec3 {
public:
   typedef base                                TScalar;
   typedef typename ScalarInfo <base>::TBool   TBool;
   __inline__ Vec3()
   {
   }
   __inline__ Vec3(const base&t) : x(t), y(t), z(t)
   {
   }
   __inline__ Vec3(const base arr[3]) : x(arr[0]), y(arr[1]), z(arr[2])
   {
   }
   __inline__ Vec3(const base&tx, const base&ty, const base&tz) : x(tx), y(ty), z(tz)
   {
   }
   __inline__ Vec3(const Vec3&rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
   {
   }
   const Vec3& operator=(const Vec3&rhs)
   {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
      return(*this);
   }
   explicit __inline__ Vec3(const Vec2 <base>&v) : x(v.x), y(v.y), z(Const <base, 0>())
   {
   }
   explicit __inline__ Vec3(const Vec4 <base>&);
   template <class VEC>
   explicit __inline__ Vec3(const VEC&v) : x(v.x), y(v.y), z(v.z)
   {
   }
   template <class GenericVec3> __inline__ const Vec3&operator +=(const GenericVec3&v)
   {
      x += v.x;
      y += v.y;
      z += v.z;
      return(*this);
   }
   template <class GenericVec3> __inline__ const Vec3&operator -=(const GenericVec3&v)
   {
      x -= v.x;
      y -= v.y;
      z -= v.z;
      return(*this);
   }
   template <class GenericVec3> __inline__ const Vec3&operator *=(const GenericVec3&v)
   {
      x *= v.x;
      y *= v.y;
      z *= v.z;
      return(*this);
   }
   template <class GenericVec3> __inline__ const Vec3&operator /=(const GenericVec3&v)
   {
      x /= v.x;
      y /= v.y;
      z /= v.z;
      return(*this);
   }
   __inline__ TBool operator==(const Vec3&rhs) const
   {
      return(x == rhs.x && y == rhs.y && z == rhs.z);
   }
   __inline__ TBool operator!=(const Vec3&rhs) const
   {
      return(x != rhs.x || y != rhs.y || z != rhs.z);
   }
   __inline__ const Vec3&operator*=(const base&s)
   {
      x *= s;
      y *= s;
      z *= s;
      return(*this);
   }

   __inline__ const Vec3&operator/=(const base&s)
   {
      base inv = Inv(s);

      x *= inv;
      y *= inv;
      z *= inv;
      return(*this);
   }

   __inline__ Vec3 operator-() const
   {
      Vec3 out;

      out.x = -x;
      out.y = -y;
      out.z = -z;
      return(out);
   }

   __inline__ base& operator[](int i)
   {
      return(i == 0 ? x : i == 1 ? y : z);
   }
   __inline__ const base& operator[](int i) const
   {
      return(i == 0 ? x : i == 1 ? y : z);
   }
   base x, y, z;
};
template <class base>
class Vec4 {
public:
   typedef base                                TScalar;
   typedef typename ScalarInfo <base>::TBool   TBool;
   __inline__ Vec4()
   {
   }
   __inline__ Vec4(const base&t) : x(t), y(t), z(t), w(t)
   {
   }
   __inline__ Vec4(const base arr[4]) : x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3])
   {
   }
   __inline__ Vec4(const base&tx, const base&ty, const base&tz, const base&tw) : x(tx), y(ty), z(tz), w(tw)
   {
   }
   __inline__ Vec4(const Vec4&rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
   {
   }
   __inline__ const Vec4& operator=(const Vec4&rhs)
   {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
      w = rhs.w;
      return(*this);
   }
   explicit __inline__ Vec4(const Vec2 <base>&v) : x(v.x), y(v.y), z(Const <base, 0>()), w(Const <base, 0>())
   {
   }
   explicit __inline__ Vec4(const Vec3 <base>&v) : x(v.x), y(v.y), z(v.z), w(Const <base, 0>())
   {
   }
   template <class VEC>
   __inline__ explicit Vec4(const VEC&v) : x(v.x), y(v.y), z(v.z), w(v.w)
   {
   }
   template <class GenericVec> __inline__ const Vec4&operator +=(const GenericVec&v)
   {
      x += v.x;
      y += v.y;
      z += v.z;
      w += v.w;
      return(*this);
   }
   template <class GenericVec> __inline__ const Vec4&operator -=(const GenericVec&v)
   {
      x -= v.x;
      y -= v.y;
      z -= v.z;
      w -= v.w;
      return(*this);
   }
   template <class GenericVec> __inline__ const Vec4&operator *=(const GenericVec&v)
   {
      x *= v.x;
      y *= v.y;
      z *= v.z;
      w *= v.w;
      return(*this);
   }
   template <class GenericVec> __inline__ const Vec4&operator /=(const GenericVec&v)
   {
      x /= v.x;
      y /= v.y;
      z /= v.z;
      w /= v.w;
      return(*this);
   }
   __inline__ TBool operator==(const Vec4&rhs) const
   {
      return(x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
   }
   __inline__ TBool operator!=(const Vec4&rhs) const
   {
      return(x != rhs.x || y != rhs.y || z == rhs.z || w == rhs.w);
   }
   __inline__ const Vec4&operator*=(const base&s)
   {
      x *= s;
      y *= s;
      z *= s;
      w *= s;
      return(*this);
   }

   __inline__ const Vec4&operator/=(const base&s)
   {
      base inv = Inv(s);

      x *= inv;
      y *= inv;
      z *= inv;
      w *= inv;
      return(*this);
   }

   __inline__ Vec4 operator-() const
   {
      Vec4 out;

      out.x = -x;
      out.y = -y;
      out.z = -z;
      out.w = -w;
      return(out);
   }

   base x, y, z, w;
};
template <class base, class GenericVec> __inline__ Vec4 <base> operator +(const Vec4 <base>&a, const GenericVec&b)
{
   Vec4 <base> out(a);
   out += b;
   return(out);
}
template <class base, class GenericVec> __inline__ Vec4 <base> operator -(const Vec4 <base>&a, const GenericVec&b)
{
   Vec4 <base> out(a);
   out -= b;
   return(out);
}
template <class base, class GenericVec> __inline__ Vec4 <base> operator *(const Vec4 <base>&a, const GenericVec&b)
{
   Vec4 <base> out(a);
   out *= b;
   return(out);
}
template <class base, class GenericVec> __inline__ Vec4 <base> operator /(const Vec4 <base>&a, const GenericVec&b)
{
   Vec4 <base> out(a);
   out /= b;
   return(out);
}
template <class base> __inline__ Vec4 <base> operator *(const Vec4 <base>&a, const base&s)
{
   Vec4 <base> out(a);
   out *= s;
   return(out);
}
template <class base> __inline__ Vec4 <base> operator /(const Vec4 <base>&a, const base&s)
{
   Vec4 <base> out(a);
   out /= s;
   return(out);
}
template <class base, class GenericVec>
__inline__ base operator|(const Vec4 <base>&a, const GenericVec&b)
{
   base out = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

   return(out);
}

template <class base>
__inline__ base Sum(const Vec4 <base>&v)
{
   base out = v.x + v.y + v.z + v.w;

   return(out);
}

template <class base> __inline__ Vec4 <base> VInv(const Vec4 <base>&v)
{
   Vec4 <base> out;
   out.x = Inv(v.x);
   out.y = Inv(v.y);
   out.z = Inv(v.z);
   out.w = Inv(v.w);
   return(out);
}
template <class base> __inline__ Vec4 <base> VSqrt(const Vec4 <base>&v)
{
   Vec4 <base> out;
   out.x = Sqrt(v.x);
   out.y = Sqrt(v.y);
   out.z = Sqrt(v.z);
   out.w = Sqrt(v.w);
   return(out);
}
template <class base> __inline__ Vec4 <base> VRSqrt(const Vec4 <base>&v)
{
   Vec4 <base> out;
   out.x = RSqrt(v.x);
   out.y = RSqrt(v.y);
   out.z = RSqrt(v.z);
   out.w = RSqrt(v.w);
   return(out);
}
template <class base> __inline__ Vec4 <base> VAbs(const Vec4 <base>&v)
{
   Vec4 <base> out;
   out.x = Abs(v.x);
   out.y = Abs(v.y);
   out.z = Abs(v.z);
   out.w = Abs(v.w);
   return(out);
}
template <class base> __inline__ Vec4 <base> VFastInv(const Vec4 <base>&v)
{
   Vec4 <base> out;
   out.x = FastInv(v.x);
   out.y = FastInv(v.y);
   out.z = FastInv(v.z);
   out.w = FastInv(v.w);
   return(out);
}
template <class base> __inline__ Vec4 <base> VFastRSqrt(const Vec4 <base>&v)
{
   Vec4 <base> out;
   out.x = FastRSqrt(v.x);
   out.y = FastRSqrt(v.y);
   out.z = FastRSqrt(v.z);
   out.w = FastRSqrt(v.w);
   return(out);
}
template <class base> __inline__ Vec4 <base> VMax(const Vec4 <base>&a, const Vec4 <base>&b)
{
   Vec4 <base> out;
   out.x = Max(a.x, b.x);
   out.y = Max(a.y, b.y);
   out.z = Max(a.z, b.z);
   out.w = Max(a.w, b.w);
   return(out);
}
template <class base> __inline__ Vec4 <base> VMin(const Vec4 <base>&a, const Vec4 <base>&b)
{
   Vec4 <base> out;
   out.x = Min(a.x, b.x);
   out.y = Min(a.y, b.y);
   out.z = Min(a.z, b.z);
   out.w = Min(a.w, b.w);
   return(out);
}
template <class base> __inline__ base Length(const Vec4 <base>&v)
{
   return(Sqrt(v | v));
}
template <class base> __inline__ base LengthSq(const Vec4 <base>&v)
{
   return(v | v);
}
template <class base> __inline__ Vec4 <base> Condition(const typename Vec4 <base>::TBool&expr, const Vec4 <base>&a, const Vec4 <base>&b)
{
   return(Vec4 <base>(Condition(expr, a.x, b.x), Condition(expr, a.y, b.y), Condition(expr, a.z, b.z), Condition(expr, a.w, b.w)));
}
template <class base> __inline__ Vec4 <base> Condition(const typename Vec4 <base>::TBool&expr, const Vec4 <base>&v)
{
   return(Vec4 <base>(Condition(expr, v.x), Condition(expr, v.y), Condition(expr, v.z), Condition(expr, v.w)));
}
template <> __inline__ Vec4 <float> Condition(const bool&expr, const Vec4 <float>&a, const Vec4 <float>&b)
{
   return(expr ? a : b);
}
template <> __inline__ Vec4 <float> Condition(const bool&expr, const Vec4 <float>&a)
{
   return(expr ? a : Vec4 <float>(0.0f, 0.0f, 0.0f, 0.0f));
}
template <class base1, class base2> __inline__ void Convert(const Vec4 <base1>&vec, base2&outX, base2&outY, base2&outZ, base2&outW)
{
   Convert(vec.x, outX);
   Convert(vec.y, outY);
   Convert(vec.z, outZ);
   Convert(vec.w, outW);
}
template <class base1, class base2> __inline__ void Convert(const base1&x, const base1&y, const base1&z, const base1&w, Vec4 <base2>&out)
{
   Convert(x, out.x);
   Convert(y, out.y);
   Convert(z, out.z);
   Convert(w, out.w);
   Convert(z, out.z);
}
template <class base>
Vec3 <base>::Vec3(const Vec4 <base>&v) : x(v.x), y(v.y), z(v.z)
{
}
template <class base, class GenericVec> __inline__ Vec3 <base> operator +(const Vec3 <base>&a, const GenericVec&b)
{
   Vec3 <base> out(a);
   out += b;
   return(out);
}
template <class base, class GenericVec> __inline__ Vec3 <base> operator -(const Vec3 <base>&a, const GenericVec&b)
{
   Vec3 <base> out(a);
   out -= b;
   return(out);
}
template <class base, class GenericVec> __inline__ Vec3 <base> operator *(const Vec3 <base>&a, const GenericVec&b)
{
   Vec3 <base> out(a);
   out *= b;
   return(out);
}
template <class base, class GenericVec> __inline__ Vec3 <base> operator /(const Vec3 <base>&a, const GenericVec&b)
{
   Vec3 <base> out(a);
   out /= b;
   return(out);
}
template <class base> __inline__ Vec3 <base> operator *(const Vec3 <base>&a, const base&s)
{
   Vec3 <base> out(a);
   out *= s;
   return(out);
}
template <class base> __inline__ Vec3 <base> operator /(const Vec3 <base>&a, const base&s)
{
   Vec3 <base> out(a);
   out /= s;
   return(out);
}
template <class base, class GenericVec>
__inline__ base operator|(const Vec3 <base>&a, const GenericVec&b)
{
   base out = a.x * b.x + a.y * b.y + a.z * b.z;

   return(out);
}

template <class base>
__inline__ base Sum(const Vec3 <base>&v)
{
   base out = v.x + v.y + v.z;

   return(out);
}

template <class base, class GenericVec>
__inline__ Vec3 <base> operator^(const Vec3 <base>&b, const GenericVec&c)
{
   Vec3 <base> out;
   out.x = b.y * c.z - b.z * c.y;
   out.y = b.z * c.x - b.x * c.z;
   out.z = b.x * c.y - b.y * c.x;
   return(out);
}

template <class base> __inline__ Vec3 <base> VInv(const Vec3 <base>&v)
{
   Vec3 <base> out;
   out.x = Inv(v.x);
   out.y = Inv(v.y);
   out.z = Inv(v.z);
   return(out);
}
template <class base> __inline__ Vec3 <base> VSqrt(const Vec3 <base>&v)
{
   Vec3 <base> out;
   out.x = Sqrt(v.x);
   out.y = Sqrt(v.y);
   out.z = Sqrt(v.z);
   return(out);
}
template <class base> __inline__ Vec3 <base> VRSqrt(const Vec3 <base>&v)
{
   Vec3 <base> out;
   out.x = RSqrt(v.x);
   out.y = RSqrt(v.y);
   out.z = RSqrt(v.z);
   return(out);
}
template <class base> __inline__ Vec3 <base> VAbs(const Vec3 <base>&v)
{
   Vec3 <base> out;
   out.x = Abs(v.x);
   out.y = Abs(v.y);
   out.z = Abs(v.z);
   return(out);
}
template <class base> __inline__ Vec3 <base> VFastInv(const Vec3 <base>&v)
{
   Vec3 <base> out;
   out.x = FastInv(v.x);
   out.y = FastInv(v.y);
   out.z = FastInv(v.z);
   return(out);
}
template <class base> __inline__ Vec3 <base> VFastRSqrt(const Vec3 <base>&v)
{
   Vec3 <base> out;
   out.x = FastRSqrt(v.x);
   out.y = FastRSqrt(v.y);
   out.z = FastRSqrt(v.z);
   return(out);
}
template <class base> __inline__ Vec3 <base> VMax(const Vec3 <base>&a, const Vec3 <base>&b)
{
   Vec3 <base> out;
   out.x = Max(a.x, b.x);
   out.y = Max(a.y, b.y);
   out.z = Max(a.z, b.z);
   return(out);
}
template <class base> __inline__ Vec3 <base> VMin(const Vec3 <base>&a, const Vec3 <base>&b)
{
   Vec3 <base> out;
   out.x = Min(a.x, b.x);
   out.y = Min(a.y, b.y);
   out.z = Min(a.z, b.z);
   return(out);
}
template <class base> __inline__ base Length(const Vec3 <base>&v)
{
   return(Sqrt(v | v));
}
template <class base> __inline__ base LengthSq(const Vec3 <base>&v)
{
   return(v | v);
}
template <class base> __inline__ Vec3 <base> Condition(const typename Vec3 <base>::TBool&expr, const Vec3 <base>&a, const Vec3 <base>&b)
{
   return(Vec3 <base>(Condition(expr, a.x, b.x), Condition(expr, a.y, b.y), Condition(expr, a.z, b.z)));
}
template <class base> __inline__ Vec3 <base> Condition(const typename Vec3 <base>::TBool&expr, const Vec3 <base>&v)
{
   return(Vec3 <base>(Condition(expr, v.x), Condition(expr, v.y), Condition(expr, v.z)));
}
template <> __inline__ Vec3 <float> Condition(const bool&expr, const Vec3 <float>&a, const Vec3 <float>&b)
{
   return(expr ? a : b);
}
template <> __inline__ Vec3 <float> Condition(const bool&expr, const Vec3 <float>&a)
{
   return(expr ? a : Vec3 <float>(0.0f, 0.0f, 0.0f));
}
template <class base1, class base2> __inline__ void Convert(const Vec3 <base1>&vec, base2&outX, base2&outY, base2&outZ)
{
   Convert(vec.x, outX);
   Convert(vec.y, outY);
   Convert(vec.z, outZ);
}
template <class base1, class base2> __inline__ void Convert(const base1&x, const base1&y, const base1&z, Vec3 <base2>&out)
{
   Convert(x, out.x);
   Convert(y, out.y);
   Convert(z, out.z);
}
template <class base>
Vec2 <base>::Vec2(const Vec3 <base>&v) : x(v.x), y(v.y)
{
}
template <class base>
Vec2 <base>::Vec2(const Vec4 <base>&v) : x(v.x), y(v.y)
{
}
template <class base, class GenericVec> __inline__ Vec2 <base> operator +(const Vec2 <base>&a, const GenericVec&b)
{
   Vec2 <base> out(a);
   out += b;
   return(out);
}
template <class base, class GenericVec> __inline__ Vec2 <base> operator -(const Vec2 <base>&a, const GenericVec&b)
{
   Vec2 <base> out(a);
   out -= b;
   return(out);
}
template <class base, class GenericVec> __inline__ Vec2 <base> operator *(const Vec2 <base>&a, const GenericVec&b)
{
   Vec2 <base> out(a);
   out *= b;
   return(out);
}
template <class base, class GenericVec> __inline__ Vec2 <base> operator /(const Vec2 <base>&a, const GenericVec&b)
{
   Vec2 <base> out(a);
   out /= b;
   return(out);
}
template <class base> __inline__ Vec2 <base> operator *(const Vec2 <base>&a, const base&s)
{
   Vec2 <base> out(a);
   out *= s;
   return(out);
}
template <class base> __inline__ Vec2 <base> operator /(const Vec2 <base>&a, const base&s)
{
   Vec2 <base> out(a);
   out /= s;
   return(out);
}
template <class base, class GenericVec>
__inline__ base operator|(const Vec2 <base>&a, const GenericVec&b)
{
   return(a.x * b.x + a.y * b.y);
}
template <class base>
__inline__ base Sum(const Vec2 <base>&v)
{
   return(v.x + v.y);
}
template <class base> __inline__ Vec2 <base> VInv(const Vec2 <base>&v)
{
   Vec2 <base> out;
   out.x = Inv(v.x);
   out.y = Inv(v.y);
   return(out);
}
template <class base> __inline__ Vec2 <base> VSqrt(const Vec2 <base>&v)
{
   Vec2 <base> out;
   out.x = Sqrt(v.x);
   out.y = Sqrt(v.y);
   return(out);
}
template <class base> __inline__ Vec2 <base> VRSqrt(const Vec2 <base>&v)
{
   Vec2 <base> out;
   out.x = RSqrt(v.x);
   out.y = RSqrt(v.y);
   return(out);
}
template <class base> __inline__ Vec2 <base> VAbs(const Vec2 <base>&v)
{
   Vec2 <base> out;
   out.x = Abs(v.x);
   out.y = Abs(v.y);
   return(out);
}
template <class base> __inline__ Vec2 <base> VFastInv(const Vec2 <base>&v)
{
   Vec2 <base> out;
   out.x = FastInv(v.x);
   out.y = FastInv(v.y);
   return(out);
}
template <class base> __inline__ Vec2 <base> VFastRSqrt(const Vec2 <base>&v)
{
   Vec2 <base> out;
   out.x = FastRSqrt(v.x);
   out.y = FastRSqrt(v.y);
   return(out);
}
template <class base> __inline__ Vec2 <base> VMax(const Vec2 <base>&a, const Vec2 <base>&b)
{
   Vec2 <base> out;
   out.x = Max(a.x, b.x);
   out.y = Max(a.y, b.y);
   return(out);
}
template <class base> __inline__ Vec2 <base> VMin(const Vec2 <base>&a, const Vec2 <base>&b)
{
   Vec2 <base> out;
   out.x = Min(a.x, b.x);
   out.y = Min(a.y, b.y);
   return(out);
}
template <class base> __inline__ base Length(const Vec2 <base>&v)
{
   return(Sqrt(v | v));
}
template <class base> __inline__ base LengthSq(const Vec2 <base>&v)
{
   return(v | v);
}
template <class base> __inline__ Vec2 <base> Condition(const typename Vec2 <base>::TBool&expr, const Vec2 <base>&a, const Vec2 <base>&b)
{
   return(Vec2 <base>(Condition(expr, a.x, b.x), Condition(expr, a.y, b.y)));
}
template <class base> __inline__ Vec2 <base> Condition(const typename Vec2 <base>::TBool&expr, const Vec2 <base>&v)
{
   return(Vec2 <base>(Condition(expr, v.x), Condition(expr, v.y)));
}
template <> __inline__ Vec2 <float> Condition(const bool&expr, const Vec2 <float>&a, const Vec2 <float>&b)
{
   return(expr ? a : b);
}
template <> __inline__ Vec2 <float> Condition(const bool&expr, const Vec2 <float>&a)
{
   return(expr ? a : Vec2 <float>(0.0f, 0.0f));
}
template <class base1, class base2> __inline__ void Convert(const Vec2 <base1>&vec, base2&outX, base2&outY)
{
   Convert(vec.x, outX);
   Convert(vec.y, outY);
}
template <class base1, class base2> __inline__ void Convert(const base1&x, const base1&y, Vec2 <base2>&out)
{
   Convert(x, out.x);
   Convert(y, out.y);
}
template <class vbase> class Matrix;
template <class T = void>
struct Identity : public Matrix <T>
{
   Identity() : Matrix <T>(Identity <void>())
   {
   }
   operator Matrix < T>& ()
   {
      return(*(Matrix <T> *) this);
   }
   operator const Matrix < T>& () const
   {
      return(*(Matrix <T> *) this);
   }
};
template <> struct Identity <void> { };
template <class vbase>
class Matrix
{
public:
   typedef typename vbase::TScalar   TScalar;
   typedef vbase                     TVector;
   __inline__ Matrix()
   {
   }

   __inline__ Matrix(const vbase&a, const vbase&b, const vbase&c, const vbase&d) : x(a), y(b), z(c), w(d)
   {
   }

   __inline__ Matrix(Identity <void> )
   {
      TScalar zero = Const <TScalar, 0>(), one = Const <TScalar, 1>();

      x = vbase(one, zero, zero, zero);
      y = vbase(zero, one, zero, zero);
      z = vbase(zero, zero, one, zero);
      w = vbase(zero, zero, zero, one);
   }

   template <class tbase>
   __inline__ Matrix(const Matrix <tbase>&other) : x(other.x), y(other.y), z(other.z), w(other.w)
   {
   }
   __inline__ const Matrix&operator*=(const Matrix&m)
   {
      Matrix t  = Transpose(m);
      vbase  x_ = x, y_ = y, z_ = z;

      x = vbase(x_ | t.x, x_ | t.y, x_ | t.z, x_ | t.w);
      y = vbase(y_ | t.x, y_ | t.y, y_ | t.z, y_ | t.w);
      z = vbase(z_ | t.x, z_ | t.y, z_ | t.z, z_ | t.w);
      w = vbase(w | t.x, w | t.y, w | t.z, w | t.w);
      return(*this);
   }

   __inline__ const Matrix&operator+=(const Matrix&m)
   {
      x += m.x;
      y += m.y;
      z += m.z;
      w += m.w;
      return(*this);
   }

   __inline__ const Matrix&operator-=(const Matrix&m)
   {
      x -= m.x;
      y -= m.y;
      z -= m.z;
      w -= m.w;
      return(*this);
   }

   __inline__ Matrix operator-() const
   {
      Matrix out;

      out.x = -x;
      out.y = -y;
      out.z = -z;
      out.w = -w;
      return(out);
   }

   vbase x, y, z, w;
};
template <class vbase>
__inline__ Matrix <vbase> operator*(const Matrix <vbase>&a, const Matrix <vbase>&b)
{
   Matrix <vbase> out;
   out  = a;
   out *= b;
   return(out);
}

template <class vbase>
__inline__ Matrix <vbase> Transpose(const Matrix <vbase>&m)
{
   Matrix <vbase> out;
   out.x = vbase(m.x.x, m.y.x, m.z.x, m.w.x);
   out.y = vbase(m.x.y, m.y.y, m.z.y, m.w.y);
   out.z = vbase(m.x.z, m.y.z, m.z.z, m.w.z);
   out.w = vbase(m.x.w, m.y.w, m.z.w, m.w.w);
   return(out);
}

template <class mbase, class vbase>
__inline__ Vec4 <vbase> operator*(const Matrix <mbase>&m, const Vec4 <vbase>&v)
{
   Vec4 <vbase> out;
   out.x = v | m.x;
   out.y = v | m.y;
   out.z = v | m.z;
   out.w = v | m.w;
   return(out);
}

template <class mbase, class vbase>
__inline__ Vec3 <vbase> operator*(const Matrix <mbase>&m, const Vec3 <vbase>&v)
{
   Vec3 <vbase> out;
   out.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + m.w.x;
   out.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + m.w.y;
   out.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + m.w.z;
   return(out);
}

template <class mbase, class vbase>
__inline__ Vec3 <vbase> operator&(const Matrix <mbase>&m, const Vec3 <vbase>&v)
{
   Vec3 <vbase> out;
   out.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
   out.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
   out.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;
   return(out);
}

template <class mbase, class vbase>
__inline__ Vec2 <vbase> operator*(const Matrix <mbase>&m, const Vec2 <vbase>&v)
{
   Vec2 <vbase> out;
   out.x = v.x * m.x.x + v.y * m.x.y + m.w.x;
   out.y = v.x * m.y.x + v.y * m.y.y + m.w.y;
   return(out);
}

__inline__ Matrix <Vec4 <float> > RotateX(float angle)
{
   float c = cos(angle), s = sin(angle);

   Matrix <Vec4 <float> > out = Identity <Vec4 <float> >();
   out.y.y = c;
   out.y.z = s;
   out.z.y = -s;
   out.z.z = c;
   return(out);
}

__inline__ Matrix <Vec4 <float> > RotateY(float angle)
{
   float c = cos(angle), s = sin(angle);

   Matrix <Vec4 <float> > out = Identity <Vec4 <float> >();
   out.x.x = c;
   out.x.z = s;
   out.z.x = -s;
   out.z.z = c;
   return(out);
}

__inline__ Matrix <Vec4 <float> > RotateZ(float angle)
{
   float c = cos(angle), s = sin(angle);

   Matrix <Vec4 <float> > out = Identity <Vec4 <float> >();
   out.x.x = c;
   out.x.y = -s;
   out.y.x = s;
   out.y.y = c;
   return(out);
}

__inline__ Matrix <Vec4 <float> > Rotate(float yaw, float pitch, float roll)
{
   return(RotateZ(roll) * RotateX(pitch) * RotateY(pitch));
}

__inline__ Matrix <Vec4 <float> > Translate(const Vec3 <float>&vec)
{
   Matrix <Vec4 <float> > out = Identity <Vec4 <float> >();
   out.w.x = vec.x;
   out.w.y = vec.y;
   out.w.z = vec.z;
   return(out);
}
}
