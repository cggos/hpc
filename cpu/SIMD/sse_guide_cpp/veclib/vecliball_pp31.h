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
template <uint mask>
__m128 _mm_shuffle_(const __m128&v)
{
   return(_mm_shuffle_ps(v, v, mask));
}

__inline__ __m128 _mm_load4a(const float arr[4])
{
   __m128 out;

   out = _mm_load_ps(arr);
   return(out);
}

__inline__ __m128 _mm_load4(const float arr[4])
{
   __m128 out;

   out = _mm_loadu_ps(arr);
   return(out);
}

__inline__ void _mm_store4a(__m128 v, float arr[4])
{
   _mm_store_ps(arr, v);
}
__inline__ void _mm_store4(__m128 v, float arr[4])
{
   _mm_storeu_ps(arr, v);
}
__inline__ __m128 _mm_load3(const float arr[3])
{
   __m128 out;

   out = _mm_shuffle_ps(
      _mm_shuffle_ps(
         _mm_load_ss(arr + 0),
         _mm_load_ss(arr + 1), 0),
      _mm_load_ss(arr + 2),
      0 + (2 << 2) + (0 << 4) + (0 << 6));
   return(out);
}

__inline__ __m128 _mm_load3(float a, float b, float c)
{
   __m128 out;

   out = _mm_shuffle_ps(
      _mm_shuffle_ps(
         _mm_load_ss(&a),
         _mm_load_ss(&b), 0),
      _mm_load_ss(&c),
      0 + (2 << 2) + (0 << 4) + (0 << 6));
   return(out);
}

__inline__ void _mm_store3(__m128 v, float arr[3])
{
   _mm_store_ss(arr + 0, v);
   _mm_store_ss(arr + 1, _mm_shuffle_ps(v, v, 1));
   _mm_store_ss(arr + 2, _mm_shuffle_ps(v, v, 2));
}

__inline__ __m128 _mm_load2(const float arr[2])
{
   __m128 out;

   out = _mm_shuffle_ps(_mm_load_ss(arr + 0), _mm_load_ss(arr + 1), 0);
   out = _mm_shuffle_ps(out, out, 0 + (3 << 2) + (0 << 4) + (3 << 6));
   return(out);
}

__inline__ __m128 _mm_load2(float a, float b)
{
   __m128 out;

   out = _mm_shuffle_ps(_mm_load_ss(&a), _mm_load_ss(&b), 0);
   out = _mm_shuffle_ps(out, out, 0 + (3 << 2) + (0 << 4) + (3 << 6));
   return(out);
}

__inline__ void _mm_store2(__m128 v, float arr[2])
{
   _mm_store_ss(arr + 0, v);
   _mm_store_ss(arr + 1, _mm_shuffle_ps(v, v, 1));
}

__inline__ __m128 _mm_load1(float v)
{
   __m128 out;

   out = _mm_load_ss(&v);
   out = _mm_shuffle_ps(out, out, 0);
   return(out);
}

__inline__ float _mm_store1(__m128 v)
{
   float out;

   _mm_store_ss(&out, v);
   return(out);
}

__inline__ __m128 _mm_nrrcp_ps(const __m128&v)
{
   __m128 out;
   __m128 t = _mm_rcp_ps(v);

   out = _mm_sub_ps(_mm_add_ps(t, t), _mm_mul_ps(_mm_mul_ps(v, t), t));
   return(out);
}

__inline__ __m128 _mm_nrrsqrt_ps(const __m128&v)
{
   __m128 out;
   __m128 t = _mm_rsqrt_ps(v);

   out = _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(0.5f), t),
                    _mm_sub_ps(_mm_set1_ps(3.0f), _mm_mul_ps(_mm_mul_ps(v, t), t)));
   return(out);
}

__inline__ __m128 _mm_bool2mask(bool v)
{
   return(_mm_set1_ps(BitCast <float, u32>(v ? 0xffffffff : 0)));
}

__inline__ void _mm_transpose(const __m128&x, const __m128&y, const __m128&z, const __m128&w,
                              __m128&ox, __m128&oy, __m128&oz, __m128&ow)
{
   __m128 tmp3, tmp2, tmp1, tmp0;

   tmp0 = _mm_shuffle_ps(x, y, 0x44);
   tmp2 = _mm_shuffle_ps(x, y, 0xEE);
   tmp1 = _mm_shuffle_ps(z, w, 0x44);
   tmp3 = _mm_shuffle_ps(z, w, 0xEE);
   ox   = _mm_shuffle_ps(tmp0, tmp1, 0x88);
   oy   = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
   oz   = _mm_shuffle_ps(tmp2, tmp3, 0x88);
   ow   = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
}

__inline__ void _mm_transpose(__m128&x, __m128&y, __m128&z, __m128&w)
{
   _mm_transpose(x, y, z, w, x, y, z, w);
}

class f32x4b;
class f32x4bn;
class f32x4
{
public:
   __inline__ f32x4()
   {
   }
   __inline__ f32x4(const __m128&v) : m(v)
   {
   }
   __inline__ f32x4(const f32x4&rhs) : m(rhs.m)
   {
   }
   __inline__ f32x4(float a, float b, float c, float d) : m(_mm_set_ps(d, c, b, a))
   {
   }
   __inline__ f32x4(float v) : m(_mm_set1_ps(v))
   {
   }
   __inline__ const f32x4&operator=(const f32x4&rhs)
   {
      m = rhs.m;
      return(*this);
   }
   __inline__ const f32x4&operator+=(const f32x4&v)
   {
      m = _mm_add_ps(m, v.m);
      return(*this);
   }
   __inline__ const f32x4&operator-=(const f32x4&v)
   {
      m = _mm_sub_ps(m, v.m);
      return(*this);
   }
   __inline__ const f32x4&operator*=(const f32x4&v)
   {
      m = _mm_mul_ps(m, v.m);
      return(*this);
   }
   __inline__ const f32x4&operator/=(const f32x4&v)
   {
      m = _mm_div_ps(m, v.m);
      return(*this);
   }
   __inline__ f32x4 operator-() const
   {
      return(_mm_sub_ps(_mm_setzero_ps(), m));
   }
   operator f32*()
   {
      return(f);
   }
   operator const f32*() const
   {
      return(f);
   }
   union
   {
      __m128 m;
      float  f[4];
   };
};
template <int m, int n>
struct CConst <f32x4, m, n> {
   static f32x4 Value()
   {
      const float v = ((float)m) / ((float)n);
      return(f32x4(v));
   }
};
class f32x4b
{
public:
   __inline__ f32x4b()
   {
   }
   __inline__ f32x4b(const __m128&v) : m(v)
   {
   }
   __inline__ f32x4b operator^(const f32x4b&v) const
   {
      return(_mm_xor_ps(m, v.m));
   }
   __inline__ f32x4b operator&&(const f32x4b&v) const
   {
      return(_mm_and_ps(m, v.m));
   }
   __inline__ f32x4b operator||(const f32x4b&v) const
   {
      return(_mm_or_ps(m, v.m));
   }
   __m128 m;
};
template <bool v>
struct CBConst <f32x4b, v> {
   static f32x4b Value()
   {
      return(f32x4b(BitCast <float, u32>(v ? 0xffffffff : 0)));
   }
};
class f32x4bn
{
public:
   __inline__ f32x4bn operator^(const f32x4b&v) const
   {
      return(_mm_xor_ps(m, v.m));
   }
   __inline__ f32x4b operator^(const f32x4bn&v) const
   {
      return(_mm_xor_ps(m, v.m));
   }
   __inline__ f32x4b operator!() const
   {
      return(f32x4b(m));
   }
   __inline__ f32x4b operator&&(const f32x4b&v) const
   {
      return(_mm_andnot_ps(m, v.m));
   }
   __inline__ f32x4bn operator&&(const f32x4bn&v) const
   {
      return(_mm_or_ps(m, v.m));
   }
   __inline__ f32x4bn operator||(const f32x4bn&v) const
   {
      return(_mm_and_ps(m, v.m));
   }
   __inline__ f32x4b operator||(const f32x4b&v) const
   {
      return(_mm_or_ps(_mm_andnot_ps(m, _mm_set1_ps(BitCast <float, u32>(~0))), v.m));
   }
   operator f32x4b() const
   {
      return(_mm_andnot_ps(m, _mm_set1_ps(BitCast <float, u32>(~0))));
   }
   const __m128&NegM() const
   {
      return(m);
   }
private:
   __inline__ f32x4bn(const __m128&v) : m(v)
   {
   }
   friend f32x4bn operator!(const f32x4b&);

   friend f32x4bn operator^(const f32x4b&, const f32x4bn&);

   __m128 m;
};
__inline__ f32x4bn operator!(const f32x4b&v)
{
   return(f32x4bn(v.m));
}
__inline__ f32x4bn operator^(const f32x4b&a, const f32x4bn&b)
{
   return(f32x4bn(_mm_xor_ps(a.m, b.NegM())));
}
__inline__ f32x4b operator&&(const f32x4b&a, const f32x4bn&b)
{
   return(_mm_andnot_ps(b.NegM(), a.m));
}
__inline__ f32x4b operator||(const f32x4b&a, const f32x4bn&b)
{
   return(_mm_or_ps(a.m, _mm_andnot_ps(b.NegM(), _mm_set1_ps(BitCast <float, u32>(~0)))));
}
__inline__ bool ForAny(const f32x4b&v)
{
   return(_mm_movemask_ps(v.m) ? 1 : 0);
}
__inline__ bool ForAll(const f32x4b&v)
{
   return(_mm_movemask_ps(v.m) == 15);
}
__inline__ int ForWhich(const f32x4b&v)
{
   return(_mm_movemask_ps(v.m));
}
__inline__ f32x4b operator ==(const f32x4&a, const f32x4&b)
{
   return(_mm_cmpeq_ps(a.m, b.m));
}
__inline__ f32x4b operator !=(const f32x4&a, const f32x4&b)
{
   return(_mm_cmpneq_ps(a.m, b.m));
}
__inline__ f32x4b operator <=(const f32x4&a, const f32x4&b)
{
   return(_mm_cmple_ps(a.m, b.m));
}
__inline__ f32x4b operator >=(const f32x4&a, const f32x4&b)
{
   return(_mm_cmpge_ps(a.m, b.m));
}
__inline__ f32x4b operator <(const f32x4&a, const f32x4&b)
{
   return(_mm_cmplt_ps(a.m, b.m));
}
__inline__ f32x4b operator >(const f32x4&a, const f32x4&b)
{
   return(_mm_cmpgt_ps(a.m, b.m));
}
__inline__ f32x4 operator+(const f32x4&a, const f32x4&b)
{
   f32x4 out(a);
   out += b;
   return(out);
}

__inline__ f32x4 operator-(const f32x4&a, const f32x4&b)
{
   f32x4 out(a);
   out -= b;
   return(out);
}

__inline__ f32x4 operator *(const f32x4&a, const f32x4&b)
{
   f32x4 out(a);
   out *= b;
   return(out);
}

__inline__ f32x4 operator/(const f32x4&a, const f32x4&b)
{
   f32x4 out(a);
   out /= b;
   return(out);
}

__inline__ f32x4 Sqrt(const f32x4&v)
{
   return(_mm_sqrt_ps(v.m));
}
__inline__ f32x4 Inv(const f32x4&v)
{
   return(_mm_nrrcp_ps(v.m));
}
__inline__ f32x4 RSqrt(const f32x4&v)
{
   return(_mm_nrrsqrt_ps(v.m));
}
__inline__ f32x4 FastInv(const f32x4&v)
{
   return(_mm_rcp_ps(v.m));
}
__inline__ f32x4 FastRSqrt(const f32x4&v)
{
   return(_mm_rsqrt_ps(v.m));
}
__inline__ f32x4 Abs(const f32x4&v)
{
   return(_mm_and_ps(_mm_set1_ps(BitCast <float, u32>(0x7fffffff)), v.m));
}
__inline__ f32x4 Min(const f32x4&a, const f32x4&b)
{
   return(_mm_min_ps(a.m, b.m));
}
__inline__ f32x4 Max(const f32x4&a, const f32x4&b)
{
   return(_mm_max_ps(a.m, b.m));
}
__inline__ int SignMask(const f32x4&v)
{
   return(_mm_movemask_ps(v.m));
}
__inline__ f32x4 Condition(const f32x4b&test, const f32x4&v1, const f32x4&v2)
{
   return(_mm_or_ps(_mm_and_ps(test.m, v1.m), _mm_andnot_ps(test.m, v2.m)));
}

__inline__ f32x4 Condition(const f32x4bn&test, const f32x4&v1, const f32x4&v2)
{
   return(_mm_or_ps(_mm_andnot_ps(test.NegM(), v1.m), _mm_and_ps(test.NegM(), v2.m)));
}

__inline__ f32x4 Condition(const f32x4b&test, const f32x4&v1)
{
   return(_mm_and_ps(test.m, v1.m));
}
__inline__ f32x4 Condition(const f32x4bn&test, const f32x4&v1)
{
   return(_mm_andnot_ps(test.NegM(), v1.m));
}
template <>
struct ScalarInfo <f32x4>
{
   enum {
      multiplicity = 4, floatingPoint = 1
   };
   typedef f32x4b   TBool;
   __inline__ static f32x4b ElementMask(int n)
   {
      static f32x4b elems[4] =
      {
         _mm_set_ps(UValue(0).f,          UValue(0).f,          UValue(0).f,          UValue(0xffffffff).f),
         _mm_set_ps(UValue(0).f,          UValue(0).f,          UValue(0xffffffff).f, UValue(0).f),
         _mm_set_ps(UValue(0).f,          UValue(0xffffffff).f, UValue(0).f,          UValue(0).f),
         _mm_set_ps(UValue(0xffffffff).f, UValue(0).f,          UValue(0).f,          UValue(0).f),
      };

      return(elems[n]);
   }
};
__inline__ void Broadcast(const float&in, f32x4&out)
{
   out = _mm_load1(in);
}
__inline__ void Convert(const float in[4], f32x4&out)
{
   out = _mm_load4(in);
}
__inline__ void Convert(const f32x4&in, float out[4])
{
   _mm_store4(in.m, out);
}
__inline__ void Convert(float x, float y, float z, float w, f32x4&out)
{
   out = _mm_set_ps(w, z, y, x);
}
__inline__ void Convert(const f32x4&in, float&outX, float&outY, float&outZ, float&outW)
{
   _mm_store_ss(&outX, in.m);
   _mm_store_ss(&outY, _mm_shuffle_ <1>(in.m));
   _mm_store_ss(&outZ, _mm_shuffle_ <2>(in.m));
   _mm_store_ss(&outW, _mm_shuffle_ <3>(in.m));
}

class i32x4b;
class i32x4bn;
class i32x4
{
public:
   __inline__ i32x4()
   {
   }
   __inline__ i32x4(const __m128i&v) : m(v)
   {
   }
   __inline__ i32x4(const i32x4&rhs) : m(rhs.m)
   {
   }
   __inline__ i32x4(int i) : m(_mm_set1_epi32(i))
   {
   }
   __inline__ i32x4(uint i) : m(_mm_set1_epi32(i))
   {
   }
   __inline__ i32x4(int a, int b, int c, int d) : m(_mm_set_epi32(d, c, b, a))
   {
   }
   __inline__ explicit i32x4(const i32x4b&);
   __inline__ const i32x4&operator=(const i32x4&rhs)
   {
      m = rhs.m;
      return(*this);
   }
   __inline__ explicit i32x4(const f32x4&v) : m(_mm_cvttps_epi32(v.m))
   {
   }
   __inline__ operator f32x4() const
   {
      return(_mm_cvtepi32_ps(m));
   }
   __inline__ const i32x4&operator+=(const i32x4&v)
   {
      m = _mm_add_epi32(m, v.m);
      return(*this);
   }
   __inline__ const i32x4&operator-=(const i32x4&v)
   {
      m = _mm_sub_epi32(m, v.m);
      return(*this);
   }
   __inline__ const i32x4&operator&=(const i32x4&v)
   {
      m = _mm_and_si128(m, v.m);
      return(*this);
   }
   __inline__ const i32x4&operator|=(const i32x4&v)
   {
      m = _mm_or_si128(m, v.m);
      return(*this);
   }
   __inline__ const i32x4&operator^=(const i32x4&v)
   {
      m = _mm_xor_si128(m, v.m);
      return(*this);
   }
   __inline__ const i32x4&operator<<=(const i32x4&v)
   {
      i[0] <<= v.i[0];
      i[1] <<= v.i[1];
      i[2] <<= v.i[2];
      i[3] <<= v.i[3];
      return(*this);
   }

   __inline__ const i32x4&operator>>=(const i32x4&v)
   {
      i[0] >>= v.i[0];
      i[1] >>= v.i[1];
      i[2] >>= v.i[2];
      i[3] >>= v.i[3];
      return(*this);
   }

   __inline__ const i32x4&operator<<=(int i)
   {
      m = _mm_sll_epi32(m, i32x4(i).m);
      return(*this);
   }
   __inline__ const i32x4&operator>>=(int i)
   {
      m = _mm_srl_epi32(m, i32x4(i).m);
      return(*this);
   }
   __inline__ const i32x4&operator*=(const i32x4&v)
   {
      i[0] *= v.i[0];
      i[1] *= v.i[1];
      i[2] *= v.i[2];
      i[3] *= v.i[3];
      return(*this);
   }

   __inline__ const i32x4&operator/=(const i32x4&v)
   {
      __m128d a0 = _mm_cvtepi32_pd(m), b0 = _mm_cvtepi32_pd(v.m);
      __m128d a1 = _mm_cvtepi32_pd(_mm_shuffle_epi32(m, 2 * 1 + 3 * 4)), b1 = _mm_cvtepi32_pd(_mm_shuffle_epi32(v.m, 2 * 1 + 3 * 4));

      a0 = _mm_div_pd(a0, b0);
      a1 = _mm_div_pd(a1, b1);
      m  = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(_mm_cvttpd_epi32(a0)),
                                           _mm_castsi128_ps(_mm_cvttpd_epi32(a1)), 0 + 1 * 4 + 0 * 16 + 1 * 64));
      return(*this);
   }

   __inline__ const i32x4&operator%=(const i32x4&v)
   {
      i[0] %= v.i[0];
      i[1] %= v.i[1];
      i[2] %= v.i[2];
      i[3] %= v.i[3];
   }

   __inline__ const i32x4&operator++()
   {
      m = _mm_add_epi32(m, _mm_set1_epi32(1));
      return(*this);
   }
   __inline__ const i32x4&operator--()
   {
      m = _mm_add_epi32(m, _mm_set1_epi32(1));
      return(*this);
   }
   __inline__ i32x4 operator-() const
   {
      return(_mm_sub_epi32(_mm_setzero_si128(), m));
   }
   __inline__ i32x4 operator~() const
   {
      return(_mm_andnot_si128(m, _mm_set1_epi32(~0)));
   }
   __inline__ i32x4b operator!() const;
   __inline__ operator i32x4bn() const;

   __inline__ operator i32*()
   {
      return(i);
   }
   __inline__ operator const i32*() const
   {
      return(i);
   }
   union
   {
      __m128i m;
      i32     i[4];
      u32     u[4];
   };
};
__inline__ i32x4 operator+(const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out += b;
   return(out);
}

__inline__ i32x4 operator-(const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out -= b;
   return(out);
}

__inline__ i32x4 operator *(const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out *= b;
   return(out);
}

__inline__ i32x4 operator/(const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out /= b;
   return(out);
}

__inline__ i32x4 operator%(const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out %= b;
   return(out);
}

__inline__ i32x4 operator& (const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out &= b;
   return(out);
}

__inline__ i32x4 operator|(const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out |= b;
   return(out);
}

__inline__ i32x4 operator^(const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out ^= b;
   return(out);
}

__inline__ i32x4 operator<<(const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out <<= b;
   return(out);
}

__inline__ i32x4 operator>>(const i32x4&a, const i32x4&b)
{
   i32x4 out(a);
   out >>= b;
   return(out);
}

template <uint bits> __inline__ i32x4 Shl(const i32x4&in)
{
   i32x4 out(_mm_slli_epi32(in.m, bits));
   return(out);
}

template <uint bits> __inline__ i32x4 Shr(const i32x4&in)
{
   i32x4 out(_mm_srli_epi32(in.m, bits));
   return(out);
}

__inline__ i32x4 FastMul(const i32x4&ta, const i32x4&tb)
{
   i32x4  out;
   __m128 a = _mm_cvtepi32_ps(ta.m), b = _mm_cvtepi32_ps(tb.m);

   out.m = _mm_cvttps_epi32(_mm_mul_ps(a, b));
   return(out);
}

__inline__ i32x4 FastDiv(const i32x4&ta, const i32x4&tb)
{
   i32x4  out;
   __m128 a = _mm_cvtepi32_ps(ta.m), b = _mm_cvtepi32_ps(tb.m);

   out.m = _mm_cvttps_epi32(_mm_div_ps(a, b));
   return(out);
}

__inline__ i32x4 Abs(const i32x4&in)
{
   i32x4 out;

   out.m = _mm_abs_epi32(in.m);
   return(out);
}

class i32x4b
{
public:
   __inline__ i32x4b()
   {
   }
   __inline__ i32x4b(const __m128i&v) : m(v)
   {
   }
   __inline__ i32x4b operator^(const i32x4b&v) const
   {
      return(_mm_xor_si128(m, v.m));
   }
   __inline__ i32x4b operator&&(const i32x4b&v) const
   {
      return(_mm_and_si128(m, v.m));
   }
   __inline__ i32x4b operator||(const i32x4b&v) const
   {
      return(_mm_or_si128(m, v.m));
   }
   __inline__ i32x4b(const f32x4b&v) : m(_mm_castps_si128(v.m))
   {
   }
   __inline__ operator f32x4b() const
   {
      return(_mm_castsi128_ps(m));
   }
   __m128i m;
};
i32x4::i32x4(const i32x4b&v) : m(v.m)
{
}
template <bool v>
struct CBConst <i32x4b, v> {
   static i32x4b Value()
   {
      return(i32x4b(_mm_set1_epi32(v ? ~0 : 0)));
   }
};
class i32x4bn
{
public:
   __inline__ i32x4bn operator^(const i32x4b&v) const
   {
      return(_mm_xor_si128(m, v.m));
   }
   __inline__ i32x4b operator^(const i32x4bn&v) const
   {
      return(_mm_xor_si128(m, v.m));
   }
   __inline__ i32x4b operator!() const
   {
      return(i32x4b(m));
   }
   __inline__ i32x4b operator&&(const i32x4b&v) const
   {
      return(_mm_andnot_si128(m, v.m));
   }
   __inline__ i32x4bn operator&&(const i32x4bn&v) const
   {
      return(_mm_or_si128(m, v.m));
   }
   __inline__ i32x4bn operator||(const i32x4bn&v) const
   {
      return(_mm_and_si128(m, v.m));
   }
   __inline__ i32x4b operator||(const i32x4b&v) const
   {
      return(_mm_or_si128(_mm_andnot_si128(m, _mm_set1_epi32(~0)), v.m));
   }
   __inline__ operator i32x4b() const
   {
      return(_mm_andnot_si128(m, _mm_set1_epi32(~0)));
   }
   __inline__ const __m128i&NegM() const
   {
      return(m);
   }
private:
   __inline__ i32x4bn(const __m128i&v) : m(v)
   {
   }
   friend i32x4bn operator!(const i32x4b&);

   friend i32x4bn operator^(const i32x4b&, const i32x4bn&);

   friend i32x4bn operator!=(const i32x4&, const i32x4&);

   friend i32x4bn operator<=(const i32x4&, const i32x4&);

   friend i32x4bn operator>=(const i32x4&, const i32x4&);

   friend i32x4::operator i32x4bn() const;
   __m128i m;
};
i32x4::operator i32x4bn() const
{
   return(i32x4bn(_mm_cmpeq_epi32(m, _mm_setzero_si128())));
}
i32x4b i32x4::operator!() const
{
   return(i32x4b(_mm_cmpeq_epi32(m, _mm_setzero_si128())));
}
__inline__ i32x4bn operator!(const i32x4b&v)
{
   return(i32x4bn(v.m));
}
__inline__ i32x4bn operator^(const i32x4b&a, const i32x4bn&b)
{
   return(i32x4bn(_mm_xor_si128(a.m, b.NegM())));
}
__inline__ i32x4b operator&&(const i32x4b&a, const i32x4bn&b)
{
   return(_mm_andnot_si128(b.NegM(), a.m));
}
__inline__ i32x4b operator||(const i32x4b&a, const i32x4bn&b)
{
   return(_mm_or_si128(a.m, _mm_andnot_si128(b.NegM(), _mm_set1_epi32(~0))));
}
__inline__ bool ForAny(const i32x4b&test)
{
   return(_mm_movemask_epi8(test.m) ? 1 : 0);
}
__inline__ bool ForAll(const i32x4b&test)
{
   return(_mm_movemask_epi8(test.m) == 0xffff ? 1 : 0);
}
__inline__ int ForWhich(const i32x4b&test)
{
   int mask = _mm_movemask_epi8(test.m);

   return(((mask & 0x000f) ? 1 : 0) | ((mask & 0x00f0) ? 2 : 0) | ((mask & 0x0f00) ? 4 : 0) | ((mask & 0xf000) ? 8 : 0));
}

__inline__ i32x4bn operator!=(const i32x4&a, const i32x4&b)
{
   return(_mm_cmpeq_epi32(a.m, b.m));
}
__inline__ i32x4b operator==(const i32x4&a, const i32x4&b)
{
   return(_mm_cmpeq_epi32(a.m, b.m));
}
__inline__ i32x4b operator<(const i32x4&a, const i32x4&b)
{
   return(_mm_cmplt_epi32(a.m, b.m));
}
__inline__ i32x4b operator>(const i32x4&a, const i32x4&b)
{
   return(_mm_cmpgt_epi32(a.m, b.m));
}
__inline__ i32x4bn operator<=(const i32x4&a, const i32x4&b)
{
   return(_mm_cmpgt_epi32(a.m, b.m));
}
__inline__ i32x4bn operator>=(const i32x4&a, const i32x4&b)
{
   return(_mm_cmplt_epi32(a.m, b.m));
}
__inline__ i32x4 Condition(const i32x4b&test, const i32x4&v1, const i32x4&v2)
{
   return(_mm_or_si128(_mm_and_si128(test.m, v1.m), _mm_andnot_si128(test.m, v2.m)));
}
__inline__ i32x4 Condition(const i32x4b&test, const i32x4&v1)
{
   return(_mm_and_si128(test.m, v1.m));
}
__inline__ i32x4 Condition(const i32x4bn&test, const i32x4&v1, const i32x4&v2)
{
   return(_mm_or_si128(_mm_andnot_si128(test.NegM(), v1.m), _mm_and_si128(test.NegM(), v2.m)));
}
__inline__ i32x4 Condition(const i32x4bn&test, const i32x4&v1)
{
   return(_mm_andnot_si128(test.NegM(), v1.m));
}
__inline__ i32x4 Max(const i32x4&a, const i32x4&b)
{
   i32x4 out(_mm_cmpgt_epi32(a.m, b.m));

   out.m = _mm_or_si128(_mm_andnot_si128(out.m, b.m), _mm_and_si128(out.m, a.m));
   return(out);
}

__inline__ i32x4 Min(const i32x4&a, const i32x4&b)
{
   i32x4 out(_mm_cmpgt_epi32(a.m, b.m));

   out.m = _mm_or_si128(_mm_and_si128(out.m, b.m), _mm_andnot_si128(out.m, a.m));
   return(out);
}

template <>
struct ScalarInfo <i32x4>
{
   enum {
      multiplicity = 4, floatingPoint = 0
   };
   typedef i32x4b   TBool;
   __inline__ static i32x4 ElementMask(int n)
   {
      static __m128i elems[4] =
      {
         _mm_set_epi32(0, 0, 0, ~0), _mm_set_epi32(0, 0, ~0, 0), _mm_set_epi32(0, ~0, 0, 0), _mm_set_epi32(~0, 0, 0, 0)
      };

      return(i32x4(elems[n]));
   }
};
__inline__ void Broadcast(const int&in, i32x4&out)
{
   out = _mm_set1_epi32(in);
}
__inline__ void Convert(const int in[4], i32x4&out)
{
   out = _mm_loadu_si128((__m128i *)in);
}
__inline__ void Convert(const i32x4&in, int out[4])
{
   _mm_storeu_si128((__m128i *)out, in.m);
}
__inline__ void Convert(int inX, int inY, int inZ, int inW, i32x4&out)
{
   out = _mm_set_epi32(inW, inZ, inY, inX);
}

__inline__ void Convert(const i32x4&in, int&outX, int&outY, int&outZ, int&outW)
{
   outX = in[0];
   outY = in[1];
   outZ = in[2];
   outW = in[3];
}

__inline__ i32x4 Round(const f32x4&flt)
{
   return(_mm_cvtps_epi32(flt.m));
}
__inline__ i32x4 Trunc(const f32x4&flt)
{
   return(_mm_cvttps_epi32(flt.m));
}
__inline__ void Cast(const i32x4&src, f32x4&dst)
{
   dst.m = _mm_castsi128_ps(src.m);
}
__inline__ void Cast(const f32x4&src, i32x4&dst)
{
   dst.m = _mm_castps_si128(src.m);
}
typedef Vec2 <f32x4>   vec2f32x4;
typedef Vec3 <f32x4>   vec3f32x4;
typedef Vec4 <f32x4>   vec4f32x4;
__inline__ vec2f32x4 Condition(const f32x4bn&test, const vec2f32x4&v1, const vec2f32x4&v2)
{
   vec2f32x4 out;

   out.x = Condition(test, v1.x, v2.x);
   out.y = Condition(test, v1.y, v2.y);
   return(out);
}

__inline__ vec2f32x4 Condition(const f32x4bn&test, const vec2f32x4&v1)
{
   vec2f32x4 out;

   out.x = Condition(test, v1.x);
   out.y = Condition(test, v1.y);
   return(out);
}

__inline__ vec3f32x4 Condition(const f32x4bn&test, const vec3f32x4&v1, const vec3f32x4&v2)
{
   vec3f32x4 out;

   out.x = Condition(test, v1.x, v2.x);
   out.y = Condition(test, v1.y, v2.y);
   out.z = Condition(test, v1.z, v2.z);
   return(out);
}

__inline__ vec3f32x4 Condition(const f32x4bn&test, const vec3f32x4&v1)
{
   vec3f32x4 out;

   out.x = Condition(test, v1.x);
   out.y = Condition(test, v1.y);
   out.z = Condition(test, v1.z);
   return(out);
}

__inline__ vec4f32x4 Condition(const f32x4bn&test, const vec4f32x4&v1, const vec4f32x4&v2)
{
   vec4f32x4 out;

   out.x = Condition(test, v1.x, v2.x);
   out.y = Condition(test, v1.y, v2.y);
   out.z = Condition(test, v1.z, v2.z);
   out.w = Condition(test, v1.w, v2.w);
   return(out);
}

__inline__ vec4f32x4 Condition(const f32x4bn&test, const vec4f32x4&v1)
{
   vec4f32x4 out;

   out.x = Condition(test, v1.x);
   out.y = Condition(test, v1.y);
   out.z = Condition(test, v1.z);
   out.w = Condition(test, v1.w);
   return(out);
}

__inline__ void Broadcast(const Vec2 <float>&in, vec2f32x4&out)
{
   out = vec2f32x4(f32x4(in.x), f32x4(in.y));
}

__inline__ void Convert(const Vec2 <float> in[4], vec2f32x4&out)
{
   Convert(in[0].x, in[1].x, in[2].x, in[3].x, out.x);
   Convert(in[0].y, in[1].y, in[2].y, in[3].y, out.y);
}

__inline__ void Convert(const vec2f32x4&in, Vec2 <float> out[4])
{
   Convert(in.x, out[0].x, out[1].x, out[2].x, out[3].x);
   Convert(in.y, out[0].y, out[1].y, out[2].y, out[3].y);
}

__inline__ void Convert(const Vec2 <float>&a, const Vec2 <float>&b, const Vec2 <float>&c, const Vec2 <float>&d, vec2f32x4&out)
{
   Convert(a.x, b.x, c.x, d.x, out.x);
   Convert(a.y, b.y, c.y, d.y, out.y);
}

__inline__ void Convert(const vec2f32x4&in, Vec2 <float>&outA, Vec2 <float>&outB, Vec2 <float>&outC, Vec2 <float>&outD)
{
   Convert(in.x, outA.x, outB.x, outC.x, outD.x);
   Convert(in.y, outA.y, outB.y, outC.y, outD.y);
}

__inline__ void Broadcast(const Vec3 <float>&in, vec3f32x4&out)
{
   out = vec3f32x4(f32x4(in.x), f32x4(in.y), f32x4(in.z));
}

__inline__ void Convert(const Vec3 <float> in[4], vec3f32x4&out)
{
   Convert(in[0].x, in[1].x, in[2].x, in[3].x, out.x);
   Convert(in[0].y, in[1].y, in[2].y, in[3].y, out.y);
   Convert(in[0].z, in[1].z, in[2].z, in[3].z, out.z);
}

__inline__ void Convert(const vec3f32x4&in, Vec3 <float> out[4])
{
   Convert(in.x, out[0].x, out[1].x, out[2].x, out[3].x);
   Convert(in.y, out[0].y, out[1].y, out[2].y, out[3].y);
   Convert(in.z, out[0].z, out[1].z, out[2].z, out[3].z);
}

__inline__ void Convert(const Vec3 <float>&a, const Vec3 <float>&b, const Vec3 <float>&c, const Vec3 <float>&d, vec3f32x4&out)
{
   Convert(a.x, b.x, c.x, d.x, out.x);
   Convert(a.y, b.y, c.y, d.y, out.y);
   Convert(a.z, b.z, c.z, d.z, out.z);
}

__inline__ void Convert(const vec3f32x4&in, Vec3 <float>&outA, Vec3 <float>&outB, Vec3 <float>&outC, Vec3 <float>&outD)
{
   Convert(in.x, outA.x, outB.x, outC.x, outD.x);
   Convert(in.y, outA.y, outB.y, outC.y, outD.y);
   Convert(in.z, outA.z, outB.z, outC.z, outD.z);
}

__inline__ void Broadcast(const Vec4 <float>&in, vec4f32x4&out)
{
   out = vec4f32x4(f32x4(in.x), f32x4(in.y), f32x4(in.z), f32x4(in.w));
}

__inline__ void Convert(const Vec4 <float> in[4], vec4f32x4&out)
{
   Convert(in[0].x, in[1].x, in[2].x, in[3].x, out.x);
   Convert(in[0].y, in[1].y, in[2].y, in[3].y, out.y);
   Convert(in[0].z, in[1].z, in[2].z, in[3].z, out.z);
   Convert(in[0].w, in[1].w, in[2].w, in[3].w, out.w);
}

__inline__ void Convert(const vec4f32x4&in, Vec4 <float> out[4])
{
   Convert(in.x, out[0].x, out[1].x, out[2].x, out[3].x);
   Convert(in.y, out[0].y, out[1].y, out[2].y, out[3].y);
   Convert(in.z, out[0].z, out[1].z, out[2].z, out[3].z);
   Convert(in.w, out[0].w, out[1].w, out[2].w, out[3].w);
}

__inline__ void Convert(const Vec4 <float>&a, const Vec4 <float>&b, const Vec4 <float>&c, const Vec4 <float>&d, vec4f32x4&out)
{
   Convert(a.x, b.x, c.x, d.x, out.x);
   Convert(a.y, b.y, c.y, d.y, out.y);
   Convert(a.z, b.z, c.z, d.z, out.z);
   Convert(a.w, b.w, c.w, d.w, out.w);
}

__inline__ void Convert(const vec4f32x4&in, Vec4 <float>&outA, Vec4 <float>&outB, Vec4 <float>&outC, Vec4 <float>&outD)
{
   Convert(in.x, outA.x, outB.x, outC.x, outD.x);
   Convert(in.y, outA.y, outB.y, outC.y, outD.y);
   Convert(in.z, outA.z, outB.z, outC.z, outD.z);
   Convert(in.w, outA.w, outB.w, outC.w, outD.w);
}

class pvec2f32;
class pvec3f32;
class pvec4f32;
class pvec2f32 {
public:
   typedef float   TScalar;
   typedef bool    TBool;
   __inline__ pvec2f32()
   {
   }
   __inline__ pvec2f32(const __m128&v) : m(v)
   {
   }
   __inline__ pvec2f32(const pvec2f32&rhs) : m(rhs.m)
   {
   }
   __inline__ explicit pvec2f32(float v) : m(_mm_set1_ps(v))
   {
   }
   __inline__ const pvec2f32&operator=(const pvec2f32&rhs)
   {
      m = rhs.m;
      return(*this);
   }
   __inline__ pvec2f32 operator-() const
   {
      return(_mm_sub_ps(_mm_setzero_ps(), m));
   }
   __inline__ const pvec2f32&operator+=(const pvec2f32&v)
   {
      m = _mm_add_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec2f32&operator-=(const pvec2f32&v)
   {
      m = _mm_sub_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec2f32&operator*=(const pvec2f32&v)
   {
      m = _mm_mul_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec2f32&operator/=(const pvec2f32&v)
   {
      m = _mm_div_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec2f32&operator*=(float s)
   {
      m = _mm_mul_ps(m, _mm_set1_ps(s));
      return(*this);
   }
   __inline__ const pvec2f32&operator/=(float s)
   {
      m = _mm_div_ps(m, _mm_set1_ps(s));
      return(*this);
   }
   __inline__ explicit pvec2f32(const pvec3f32&v);
   __inline__ explicit pvec2f32(const pvec4f32&v);
   __inline__ pvec2f32(float x, float y)
   {
      m = _mm_load2(x, y);
   } __inline__ pvec2f32(const Vec2 <float>&v)
   {
      m = _mm_load2(v.x, v.y);
   } __inline__ operator Vec2 < float> () const
   {
      return(Vec2 <float>(x, y));
   }
   union {
      __m128 m;
      struct {
         float x, y, t0, t1;
      };
   };
};
__inline__ pvec2f32 VSqrt(const pvec2f32&v)
{
   return(_mm_sqrt_ps(v.m));
}
__inline__ pvec2f32 VInv(const pvec2f32&v)
{
   return(_mm_nrrcp_ps(v.m));
}
__inline__ pvec2f32 VRSqrt(const pvec2f32&v)
{
   return(_mm_nrrsqrt_ps(v.m));
}
__inline__ pvec2f32 VAbs(const pvec2f32&v)
{
   return(_mm_and_ps(_mm_set1_ps(BitCast <float, u32>(0x7fffffff)), v.m));
}
__inline__ pvec2f32 VFastInv(const pvec2f32&v)
{
   return(_mm_rcp_ps(v.m));
}
__inline__ pvec2f32 VFastRSqrt(const pvec2f32&v)
{
   return(_mm_rsqrt_ps(v.m));
}
__inline__ pvec2f32 VMin(const pvec2f32&a, const pvec2f32&b)
{
   return(_mm_min_ps(a.m, b.m));
}
__inline__ pvec2f32 VMax(const pvec2f32&a, const pvec2f32&b)
{
   return(_mm_max_ps(a.m, b.m));
}
__inline__ pvec2f32 operator+(const pvec2f32&a, const pvec2f32&b)
{
   pvec2f32 out(a);
   out += b;
   return(out);
}

__inline__ pvec2f32 operator-(const pvec2f32&a, const pvec2f32&b)
{
   pvec2f32 out(a);
   out -= b;
   return(out);
}

__inline__ pvec2f32 operator *(const pvec2f32&a, const pvec2f32&b)
{
   pvec2f32 out(a);
   out *= b;
   return(out);
}

__inline__ pvec2f32 operator/(const pvec2f32&a, const pvec2f32&b)
{
   pvec2f32 out(a);
   out /= b;
   return(out);
}

__inline__ pvec2f32 operator *(const pvec2f32&a, float v)
{
   pvec2f32 out(a);
   out *= v;
   return(out);
}

__inline__ pvec2f32 operator/(const pvec2f32&a, float v)
{
   pvec2f32 out(a);
   out /= v;
   return(out);
}

__inline__ pvec2f32 Condition(bool test_, const pvec2f32&v1, const pvec2f32&v2)
{
   __m128 test = _mm_bool2mask(test_);

   return(_mm_or_ps(_mm_and_ps(test, v1.m), _mm_andnot_ps(test, v2.m)));
}

__inline__ pvec2f32 Condition(bool test_, const pvec2f32&v1)
{
   __m128 test = _mm_bool2mask(test_);

   return(_mm_and_ps(test, v1.m));
}

class pvec3f32 {
public:
   typedef float   TScalar;
   typedef bool    TBool;
   __inline__ pvec3f32()
   {
   }
   __inline__ pvec3f32(const __m128&v) : m(v)
   {
   }
   __inline__ pvec3f32(const pvec3f32&rhs) : m(rhs.m)
   {
   }
   __inline__ explicit pvec3f32(float v) : m(_mm_set1_ps(v))
   {
   }
   __inline__ const pvec3f32&operator=(const pvec3f32&rhs)
   {
      m = rhs.m;
      return(*this);
   }
   __inline__ pvec3f32 operator-() const
   {
      return(_mm_sub_ps(_mm_setzero_ps(), m));
   }
   __inline__ const pvec3f32&operator+=(const pvec3f32&v)
   {
      m = _mm_add_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec3f32&operator-=(const pvec3f32&v)
   {
      m = _mm_sub_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec3f32&operator*=(const pvec3f32&v)
   {
      m = _mm_mul_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec3f32&operator/=(const pvec3f32&v)
   {
      m = _mm_div_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec3f32&operator*=(float s)
   {
      m = _mm_mul_ps(m, _mm_set1_ps(s));
      return(*this);
   }
   __inline__ const pvec3f32&operator/=(float s)
   {
      m = _mm_div_ps(m, _mm_set1_ps(s));
      return(*this);
   }
   __inline__ explicit pvec3f32(const pvec2f32&v);
   __inline__ explicit pvec3f32(const pvec4f32&v);
   __inline__ pvec3f32(float x, float y, float z)
   {
      m = _mm_load3(x, y, z);
   } __inline__ pvec3f32(const Vec3 <float>&v)
   {
      m = _mm_load3(v.x, v.y, v.z);
   } __inline__ operator Vec3 < float> () const
   {
      return(Vec3 <float>(x, y, z));
   }
   union {
      __m128 m;
      struct {
         float x, y, z, t0;
      };
   };
};
__inline__ pvec3f32 VSqrt(const pvec3f32&v)
{
   return(_mm_sqrt_ps(v.m));
}
__inline__ pvec3f32 VInv(const pvec3f32&v)
{
   return(_mm_nrrcp_ps(v.m));
}
__inline__ pvec3f32 VRSqrt(const pvec3f32&v)
{
   return(_mm_nrrsqrt_ps(v.m));
}
__inline__ pvec3f32 VAbs(const pvec3f32&v)
{
   return(_mm_and_ps(_mm_set1_ps(BitCast <float, u32>(0x7fffffff)), v.m));
}
__inline__ pvec3f32 VFastInv(const pvec3f32&v)
{
   return(_mm_rcp_ps(v.m));
}
__inline__ pvec3f32 VFastRSqrt(const pvec3f32&v)
{
   return(_mm_rsqrt_ps(v.m));
}
__inline__ pvec3f32 VMin(const pvec3f32&a, const pvec3f32&b)
{
   return(_mm_min_ps(a.m, b.m));
}
__inline__ pvec3f32 VMax(const pvec3f32&a, const pvec3f32&b)
{
   return(_mm_max_ps(a.m, b.m));
}
__inline__ pvec3f32 operator+(const pvec3f32&a, const pvec3f32&b)
{
   pvec3f32 out(a);
   out += b;
   return(out);
}

__inline__ pvec3f32 operator-(const pvec3f32&a, const pvec3f32&b)
{
   pvec3f32 out(a);
   out -= b;
   return(out);
}

__inline__ pvec3f32 operator *(const pvec3f32&a, const pvec3f32&b)
{
   pvec3f32 out(a);
   out *= b;
   return(out);
}

__inline__ pvec3f32 operator/(const pvec3f32&a, const pvec3f32&b)
{
   pvec3f32 out(a);
   out /= b;
   return(out);
}

__inline__ pvec3f32 operator *(const pvec3f32&a, float v)
{
   pvec3f32 out(a);
   out *= v;
   return(out);
}

__inline__ pvec3f32 operator/(const pvec3f32&a, float v)
{
   pvec3f32 out(a);
   out /= v;
   return(out);
}

__inline__ pvec3f32 Condition(bool test_, const pvec3f32&v1, const pvec3f32&v2)
{
   __m128 test = _mm_bool2mask(test_);

   return(_mm_or_ps(_mm_and_ps(test, v1.m), _mm_andnot_ps(test, v2.m)));
}

__inline__ pvec3f32 Condition(bool test_, const pvec3f32&v1)
{
   __m128 test = _mm_bool2mask(test_);

   return(_mm_and_ps(test, v1.m));
}

class pvec4f32 {
public:
   typedef float   TScalar;
   typedef bool    TBool;
   __inline__ pvec4f32()
   {
   }
   __inline__ pvec4f32(const __m128&v) : m(v)
   {
   }
   __inline__ pvec4f32(const pvec4f32&rhs) : m(rhs.m)
   {
   }
   __inline__ explicit pvec4f32(float v) : m(_mm_set1_ps(v))
   {
   }
   __inline__ const pvec4f32&operator=(const pvec4f32&rhs)
   {
      m = rhs.m;
      return(*this);
   }
   __inline__ pvec4f32 operator-() const
   {
      return(_mm_sub_ps(_mm_setzero_ps(), m));
   }
   __inline__ const pvec4f32&operator+=(const pvec4f32&v)
   {
      m = _mm_add_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec4f32&operator-=(const pvec4f32&v)
   {
      m = _mm_sub_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec4f32&operator*=(const pvec4f32&v)
   {
      m = _mm_mul_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec4f32&operator/=(const pvec4f32&v)
   {
      m = _mm_div_ps(m, v.m);
      return(*this);
   }
   __inline__ const pvec4f32&operator*=(float s)
   {
      m = _mm_mul_ps(m, _mm_set1_ps(s));
      return(*this);
   }
   __inline__ const pvec4f32&operator/=(float s)
   {
      m = _mm_div_ps(m, _mm_set1_ps(s));
      return(*this);
   }
   __inline__ explicit pvec4f32(const pvec2f32&v)
   {
      m = _mm_shuffle_ps(v.m, _mm_setzero_ps(), 0 + (1 << 2));
   } __inline__ explicit pvec4f32(const pvec3f32&v)
   {
      __m128 zzww = _mm_shuffle_ps(v.m, _mm_setzero_ps(), 0);
      m = _mm_shuffle_ps(v.m, zzww, 0 + (1 << 2) + (0 << 4) + (2 << 6));
   } __inline__ pvec4f32(float x, float y, float z, float w)
   {
      m = _mm_set_ps(w, z, y, x);
   } __inline__ pvec4f32(const Vec4 <float>&v)
   {
      m = _mm_set_ps(v.x, v.y, v.z, v.w);
   } __inline__ operator Vec4 < float> () const
   {
      return(Vec4 <float>(x, y, z, w));
   }
   union {
      __m128 m;
      struct {
         float x, y, z, w;
      };
   };
};
__inline__ pvec4f32 VSqrt(const pvec4f32&v)
{
   return(_mm_sqrt_ps(v.m));
}
__inline__ pvec4f32 VInv(const pvec4f32&v)
{
   return(_mm_nrrcp_ps(v.m));
}
__inline__ pvec4f32 VRSqrt(const pvec4f32&v)
{
   return(_mm_nrrsqrt_ps(v.m));
}
__inline__ pvec4f32 VAbs(const pvec4f32&v)
{
   return(_mm_and_ps(_mm_set1_ps(BitCast <float, u32>(0x7fffffff)), v.m));
}
__inline__ pvec4f32 VFastInv(const pvec4f32&v)
{
   return(_mm_rcp_ps(v.m));
}
__inline__ pvec4f32 VFastRSqrt(const pvec4f32&v)
{
   return(_mm_rsqrt_ps(v.m));
}
__inline__ pvec4f32 VMin(const pvec4f32&a, const pvec4f32&b)
{
   return(_mm_min_ps(a.m, b.m));
}
__inline__ pvec4f32 VMax(const pvec4f32&a, const pvec4f32&b)
{
   return(_mm_max_ps(a.m, b.m));
}
__inline__ pvec4f32 operator+(const pvec4f32&a, const pvec4f32&b)
{
   pvec4f32 out(a);
   out += b;
   return(out);
}

__inline__ pvec4f32 operator-(const pvec4f32&a, const pvec4f32&b)
{
   pvec4f32 out(a);
   out -= b;
   return(out);
}

__inline__ pvec4f32 operator *(const pvec4f32&a, const pvec4f32&b)
{
   pvec4f32 out(a);
   out *= b;
   return(out);
}

__inline__ pvec4f32 operator/(const pvec4f32&a, const pvec4f32&b)
{
   pvec4f32 out(a);
   out /= b;
   return(out);
}

__inline__ pvec4f32 operator *(const pvec4f32&a, float v)
{
   pvec4f32 out(a);
   out *= v;
   return(out);
}

__inline__ pvec4f32 operator/(const pvec4f32&a, float v)
{
   pvec4f32 out(a);
   out /= v;
   return(out);
}

__inline__ pvec4f32 Condition(bool test_, const pvec4f32&v1, const pvec4f32&v2)
{
   __m128 test = _mm_bool2mask(test_);

   return(_mm_or_ps(_mm_and_ps(test, v1.m), _mm_andnot_ps(test, v2.m)));
}

__inline__ pvec4f32 Condition(bool test_, const pvec4f32&v1)
{
   __m128 test = _mm_bool2mask(test_);

   return(_mm_and_ps(test, v1.m));
}

pvec3f32::pvec3f32(const pvec2f32&v) : m(_mm_shuffle_ps(v.m, _mm_setzero_ps(), 0 + (1 << 2)))
{
}
pvec3f32::pvec3f32(const pvec4f32&v) : m(v.m)
{
}
pvec2f32::pvec2f32(const pvec3f32&v) : m(v.m)
{
}
pvec2f32::pvec2f32(const pvec4f32&v) : m(v.m)
{
}
__inline__ float operator|(const pvec2f32&a, const pvec2f32&b)
{
   union {
      float  out[4];
      __m128 t;
   };
   t = _mm_mul_ps(a.m, b.m);
   t = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));
   return(out[0]);
}

__inline__ float operator|(const pvec3f32&a, const pvec3f32&b)
{
   __m128 t;
   float  out;

   t = _mm_mul_ps(a.m, b.m);
   t = _mm_add_ss(_mm_movehl_ps(t, t), _mm_add_ss(t, _mm_shuffle_ps(t, t, 1)));
   _mm_store_ss(&out, t);
   return(out);
}

__inline__ float operator|(const pvec4f32&a, const pvec4f32&b)
{
   union {
      float  out[4];
      __m128 t;
   };
   t = _mm_mul_ps(a.m, b.m);
   t = _mm_add_ps(t, _mm_shuffle_ps(t, t, 0x4E));
   t = _mm_add_ps(t, _mm_shuffle_ps(t, t, 0x11));
   return(out[0]);
}

__inline__ float Length(const pvec2f32&v)
{
   return(Sqrt(v | v));
}
__inline__ float LengthSq(const pvec2f32&v)
{
   return(v | v);
}
__inline__ float Length(const pvec3f32&v)
{
   return(Sqrt(v | v));
}
__inline__ float LengthSq(const pvec3f32&v)
{
   return(v | v);
}
__inline__ float Length(const pvec4f32&v)
{
   return(Sqrt(v | v));
}
__inline__ float LengthSq(const pvec4f32&v)
{
   return(v | v);
}
__inline__ pvec3f32 operator^(const pvec3f32&a, const pvec3f32&b)
{
   pvec3f32 out;
   __m128   a1 = _mm_shuffle_ps(a.m, a.m, 201);
   __m128   b1 = _mm_shuffle_ps(b.m, b.m, 210);
   __m128   a2 = _mm_shuffle_ps(a.m, a.m, 210);
   __m128   b2 = _mm_shuffle_ps(b.m, b.m, 201);

   out.m = _mm_sub_ps(_mm_mul_ps(a1, b1), _mm_mul_ps(a2, b2));
   return(out);
}

__inline__ void Convert(const Vec2 <float>&v, pvec2f32&out)
{
   out.m = _mm_load2(&v.x);
}
__inline__ void Convert(const float v[2], pvec2f32&out)
{
   out.m = _mm_load2(v + 0);
}
__inline__ void Convert(const pvec2f32&v, Vec2 <float>&out)
{
   _mm_store2(v.m, &out.x);
}
__inline__ void Convert(const pvec2f32&v, float out[2])
{
   _mm_store2(v.m, out + 0);
}
__inline__ void Convert(const Vec3 <float>&v, pvec3f32&out)
{
   out.m = _mm_load3(&v.x);
}
__inline__ void Convert(const float v[3], pvec3f32&out)
{
   out.m = _mm_load3(v + 0);
}
__inline__ void Convert(const pvec3f32&v, Vec3 <float>&out)
{
   _mm_store3(v.m, &out.x);
}
__inline__ void Convert(const pvec3f32&v, float out[3])
{
   _mm_store3(v.m, out + 0);
}
__inline__ void Convert(const Vec4 <float>&v, pvec4f32&out)
{
   out.m = _mm_load4(&v.x);
}
__inline__ void Convert(const float v[4], pvec4f32&out)
{
   out.m = _mm_load4(v + 0);
}
__inline__ void Convert(const pvec4f32&v, Vec4 <float>&out)
{
   _mm_store4(v.m, &out.x);
}
__inline__ void Convert(const pvec4f32&v, float out[4])
{
   _mm_store4(v.m, out + 0);
}
__inline__ void Convert(const vec2f32x4&in, pvec2f32 out[4])
{
   _mm_transpose(in.x.m, in.y.m, in.y.m, in.y.m,
                 out[0].m, out[1].m, out[2].m, out[3].m);
}

__inline__ void Convert(const vec3f32x4&in, pvec3f32 out[4])
{
   _mm_transpose(in.x.m, in.y.m, in.z.m, in.z.m,
                 out[0].m, out[1].m, out[2].m, out[3].m);
}

__inline__ void Convert(const pvec3f32 in[4], vec3f32x4&out)
{
   __m128 tmp3, tmp2, tmp1, tmp0;

   tmp0    = _mm_shuffle_ps(in[0].m, in[1].m, 0x44);
   tmp2    = _mm_shuffle_ps(in[0].m, in[1].m, 0xEE);
   tmp1    = _mm_shuffle_ps(in[2].m, in[3].m, 0x44);
   tmp3    = _mm_shuffle_ps(in[2].m, in[3].m, 0xEE);
   out.x.m = _mm_shuffle_ps(tmp0, tmp1, 0x88);
   out.y.m = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
   out.z.m = _mm_shuffle_ps(tmp2, tmp3, 0x88);
}

__inline__ void Convert(const vec4f32x4&in, pvec4f32 out[4])
{
   _mm_transpose(in.x.m, in.y.m, in.z.m, in.w.m,
                 out[0].m, out[1].m, out[2].m, out[3].m);
}

__inline__ void Convert(const pvec4f32 in[4], vec4f32x4&out)
{
   __m128 tmp3, tmp2, tmp1, tmp0;

   tmp0    = _mm_shuffle_ps(in[0].m, in[1].m, 0x44);
   tmp2    = _mm_shuffle_ps(in[0].m, in[1].m, 0xEE);
   tmp1    = _mm_shuffle_ps(in[2].m, in[3].m, 0x44);
   tmp3    = _mm_shuffle_ps(in[2].m, in[3].m, 0xEE);
   out.x.m = _mm_shuffle_ps(tmp0, tmp1, 0x88);
   out.y.m = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
   out.z.m = _mm_shuffle_ps(tmp2, tmp3, 0x88);
   out.w.m = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
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
