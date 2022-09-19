/*
 * Copyright (c) 2006, Mike Tegtmeyer
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of its contributors may
 *       be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef N_STD_CVALARRAY
#define N_STD_CVALARRAY

#include <memory> //for std::size_t
#include <cmath>
#include <cstdlib> //for abs()
#include <algorithm>
#include <cstring>
#include <iostream>

#ifndef UNROLL_LIMIT
#define UNROLL_LIMIT 10
#endif

namespace n_std {

/*
  Loop unrolling essentials
*/
template<typename T>
struct __is_fundamental {
  enum {
    value = false
  };
};

template<typename T>
struct __is_fundamental<T*> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<char> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<unsigned char> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<signed char> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<short int> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<unsigned short int> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<int> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<unsigned int> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<long int> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<unsigned long int> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<float> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<double> {
  enum {
    value = true
  };
};

template<>
struct __is_fundamental<long double> {
  enum {
    value = true
  };
};



/**
 *  Computed assignment
 *
 *  We must use this form because currently c++ doesn't allow partial
 *  specialization of function tempates
*/
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, 
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool Unroll>
struct __static_op {
  static void multiply_assign(LhsT &lhs, const RhsT &rhs);
  static void divides_assign(LhsT &lhs, const RhsT &rhs);
  static void modulus_assign(LhsT &lhs, const RhsT &rhs);
  static void plus_assign(LhsT &lhs, const RhsT &rhs);
  static void minus_assign(LhsT &lhs, const RhsT &rhs);
  static void bitwise_xor_assign(LhsT &lhs, const RhsT &rhs);
  static void bitwise_and_assign(LhsT &lhs, const RhsT &rhs);
  static void bitwise_or_assign(LhsT &lhs, const RhsT &rhs);
  static void left_shift_assign(LhsT &lhs, const RhsT &rhs);
  static void right_shift_assign(LhsT &lhs, const RhsT &rhs);

  template<typename IndT>
  static void multiply_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void divides_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void modulus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void plus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void minus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_xor_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_and_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_or_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void left_shift_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void right_shift_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename IndT>
  static void multiply_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void divides_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void modulus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void plus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void minus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_xor_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_and_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_or_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void left_shift_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void right_shift_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename LhsIndT, typename RhsIndT>
  static void multiply_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void divides_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void modulus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void plus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void minus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_xor_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_and_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_or_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void left_shift_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void right_shift_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
};

/*
  Unrolled computed assignment
*/
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, 
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2>
struct __static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,true> {
  static void multiply_assign(LhsT &lhs, const RhsT &rhs);
  static void divides_assign(LhsT &lhs, const RhsT &rhs);
  static void modulus_assign(LhsT &lhs, const RhsT &rhs);
  static void plus_assign(LhsT &lhs, const RhsT &rhs);
  static void minus_assign(LhsT &lhs, const RhsT &rhs);
  static void bitwise_xor_assign(LhsT &lhs, const RhsT &rhs);
  static void bitwise_and_assign(LhsT &lhs, const RhsT &rhs);
  static void bitwise_or_assign(LhsT &lhs, const RhsT &rhs);
  static void left_shift_assign(LhsT &lhs, const RhsT &rhs);
  static void right_shift_assign(LhsT &lhs, const RhsT &rhs);

  template<typename IndT>
  static void multiply_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void divides_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void modulus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void plus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void minus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_xor_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_and_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_or_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void left_shift_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void right_shift_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename IndT>
  static void multiply_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void divides_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void modulus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void plus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void minus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_xor_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_and_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_or_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void left_shift_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void right_shift_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename LhsIndT, typename RhsIndT>
  static void multiply_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void divides_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void modulus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void plus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void minus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_xor_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_and_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_or_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void left_shift_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void right_shift_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
};

/*
  Unrolled computed assignment partial specialization for upper bound
*/
template<typename LhsT, typename RhsT, std::size_t U, 
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2>
struct __static_op<LhsT,RhsT,U,U,B1,B2,S1,S2,true> {
  static void multiply_assign(LhsT &lhs, const RhsT &rhs) {}
  static void divides_assign(LhsT &lhs, const RhsT &rhs) {}
  static void modulus_assign(LhsT &lhs, const RhsT &rhs) {}
  static void plus_assign(LhsT &lhs, const RhsT &rhs) {}
  static void minus_assign(LhsT &lhs, const RhsT &rhs) {}
  static void bitwise_xor_assign(LhsT &lhs, const RhsT &rhs) {}
  static void bitwise_and_assign(LhsT &lhs, const RhsT &rhs) {}
  static void bitwise_or_assign(LhsT &lhs, const RhsT &rhs) {}
  static void left_shift_assign(LhsT &lhs, const RhsT &rhs) {}
  static void right_shift_assign(LhsT &lhs, const RhsT &rhs) {}

  template<typename IndT>
  static void multiply_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void divides_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void modulus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void plus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void minus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void bitwise_xor_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void bitwise_and_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void bitwise_or_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void left_shift_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void right_shift_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}

  template<typename IndT>
  static void multiply_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void divides_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void modulus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void plus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void minus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void bitwise_xor_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void bitwise_and_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void bitwise_or_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void left_shift_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}
  template<typename IndT>
  static void right_shift_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}

  template<typename LhsIndT, typename RhsIndT>
  static void multiply_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
  template<typename LhsIndT, typename RhsIndT>
  static void divides_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
  template<typename LhsIndT, typename RhsIndT>
  static void modulus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
  template<typename LhsIndT, typename RhsIndT>
  static void plus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
  template<typename LhsIndT, typename RhsIndT>
  static void minus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_xor_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_and_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_or_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
  template<typename LhsIndT, typename RhsIndT>
  static void left_shift_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
  template<typename LhsIndT, typename RhsIndT>
  static void right_shift_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
};

#define MAKE_UNROLLED_STATIC_OP(NAME,OP) \
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, \
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2> \
inline void \
__static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,true>:: NAME (LhsT &lhs, const RhsT &rhs) \
{ \
  lhs[B1+(L*S1)] OP rhs[B2+(L*S2)]; \
  __static_op<LhsT,RhsT,L+1,U,B1,B2,S1,S2,true>:: NAME(lhs,rhs); \
} \
\
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, \
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2> \
template<typename IndT> \
inline void \
__static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,true>::NAME##_lhs_indirect(LhsT &lhs, \
  const RhsT &rhs, const IndT &ind) \
{ \
  lhs[ind[B1+(L*S1)]] OP rhs[B2+(L*S2)]; \
  __static_op<LhsT,RhsT,L+1,U,B1,B2,S1,S2,true>::NAME##_lhs_indirect(lhs,rhs,ind); \
} \
\
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, \
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2> \
template<typename IndT> \
inline void \
__static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,true>::NAME##_rhs_indirect(LhsT &lhs, \
  const RhsT &rhs, const IndT &ind) \
{ \
  lhs[B1+(L*S1)] OP rhs[ind[B2+(L*S2)]]; \
  __static_op<LhsT,RhsT,L+1,U,B1,B2,S1,S2,true>::NAME##_rhs_indirect(lhs,rhs,ind); \
} \
\
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, \
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2> \
  template<typename LhsIndT, typename RhsIndT> \
inline void \
__static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,true>::NAME##_indirect(LhsT &lhs, \
  const RhsT &rhs, const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) \
{ \
  lhs[lhs_ind[B1+(L*S1)]] OP rhs[rhs_ind[B2+(L*S2)]]; \
  __static_op<LhsT,RhsT,L+1,U,B1,B2,S1,S2,true>::NAME##_indirect(lhs,rhs,lhs_ind,rhs_ind); \
}

MAKE_UNROLLED_STATIC_OP(multiply_assign,*=)
MAKE_UNROLLED_STATIC_OP(divides_assign,/=)
MAKE_UNROLLED_STATIC_OP(modulus_assign,%=)
MAKE_UNROLLED_STATIC_OP(plus_assign,+=)
MAKE_UNROLLED_STATIC_OP(minus_assign,-=)
MAKE_UNROLLED_STATIC_OP(bitwise_xor_assign,^=)
MAKE_UNROLLED_STATIC_OP(bitwise_and_assign,&=)
MAKE_UNROLLED_STATIC_OP(bitwise_or_assign,|=)
MAKE_UNROLLED_STATIC_OP(left_shift_assign,<<=)
MAKE_UNROLLED_STATIC_OP(right_shift_assign,>>=)

/*
  Loop computed assignment
*/
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, 
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2>
struct __static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,false> {
  static void multiply_assign(LhsT &lhs, const RhsT &rhs);
  static void divides_assign(LhsT &lhs, const RhsT &rhs);
  static void modulus_assign(LhsT &lhs, const RhsT &rhs);
  static void plus_assign(LhsT &lhs, const RhsT &rhs);
  static void minus_assign(LhsT &lhs, const RhsT &rhs);
  static void bitwise_xor_assign(LhsT &lhs, const RhsT &rhs);
  static void bitwise_and_assign(LhsT &lhs, const RhsT &rhs);
  static void bitwise_or_assign(LhsT &lhs, const RhsT &rhs);
  static void left_shift_assign(LhsT &lhs, const RhsT &rhs);
  static void right_shift_assign(LhsT &lhs, const RhsT &rhs);

  template<typename IndT>
  static void multiply_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void divides_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void modulus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void plus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void minus_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_xor_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_and_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_or_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void left_shift_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void right_shift_assign_lhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename IndT>
  static void multiply_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void divides_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void modulus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void plus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void minus_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_xor_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_and_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void bitwise_or_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void left_shift_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);
  template<typename IndT>
  static void right_shift_assign_rhs_indirect(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename LhsIndT, typename RhsIndT>
  static void multiply_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void divides_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void modulus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void plus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void minus_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_xor_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_and_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void bitwise_or_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void left_shift_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
  template<typename LhsIndT, typename RhsIndT>
  static void right_shift_assign_indirect(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
};

#define MAKE_LOOP_STATIC_OP(NAME,OP) \
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, \
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2> \
inline void \
__static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,false>:: NAME (LhsT &lhs, const RhsT &rhs) \
{ \
  for(std::size_t i=L, s1=B1, s2=B2; i<U; ++i, s1+=S1, s2+=S2) \
    lhs[s1] OP rhs[s2]; \
} \
\
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, \
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2> \
template<typename IndT> \
inline void \
__static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,false>:: NAME##_lhs_indirect(LhsT &lhs, \
  const RhsT &rhs, const IndT &ind) \
{ \
  for(std::size_t i=L, s1=B1, s2=B2; i<U; ++i, s1+=S1, s2+=S2) \
    lhs[ind[s1]] OP rhs[s2]; \
} \
\
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, \
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2> \
template<typename IndT> \
inline void \
__static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,false>:: NAME##_rhs_indirect(LhsT &lhs, \
  const RhsT &rhs, const IndT &ind) \
{ \
  for(std::size_t i=L, s1=B1, s2=B2; i<U; ++i, s1+=S1, s2+=S2) \
    lhs[s1] OP rhs[ind[s2]]; \
} \
\
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, \
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2> \
  template<typename LhsIndT, typename RhsIndT> \
inline void \
__static_op<LhsT,RhsT,L,U,B1,B2,S1,S2,false>:: NAME##_indirect(LhsT &lhs, \
  const RhsT &rhs, const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) \
{ \
  for(std::size_t i=L, s1=B1, s2=B2; i<U; ++i, s1+=S1, s2+=S2) \
    lhs[lhs_ind[s1]] OP rhs[rhs_ind[s2]]; \
}

MAKE_LOOP_STATIC_OP(multiply_assign,*=)
MAKE_LOOP_STATIC_OP(divides_assign,/=)
MAKE_LOOP_STATIC_OP(modulus_assign,%=)
MAKE_LOOP_STATIC_OP(plus_assign,+=)
MAKE_LOOP_STATIC_OP(minus_assign,-=)
MAKE_LOOP_STATIC_OP(bitwise_xor_assign,^=)
MAKE_LOOP_STATIC_OP(bitwise_and_assign,&=)
MAKE_LOOP_STATIC_OP(bitwise_or_assign,|=)
MAKE_LOOP_STATIC_OP(left_shift_assign,<<=)
MAKE_LOOP_STATIC_OP(right_shift_assign,>>=)


// define as necessary                                                          
template<std::size_t B1, std::size_t B2, std::size_t L,
  typename T, std::size_t N1, std::size_t N2>
inline void __restricted_copy(T (&lhs)[N1], const T (&rhs)[N2])
{
  std::memcpy(lhs+B1,rhs+B2,L*sizeof(T));
}

/*
  Static assignment, generic not implemented
  
  Unroll == true, then full unroll
  Unroll == false && FundT == true, then memset/memcopy
  Unroll == false && FundT == false, then loop

*/
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U, 
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool Unroll,
  bool FundT>
struct __static_assign {
  static void copy(LhsT &lhs, const RhsT &rhs);
  
  // B1, S1, refers to ind. not lhs
  template<typename IndT>
  static void lhs_indirect_copy(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  // B2, S2, refers to ind. not rhs
  template<typename IndT>
  static void rhs_indirect_copy(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  // B1, S1 refers to lhs_ind. B2, S2, refers to rhs_ind.
  template<typename LhsIndT, typename RhsIndT>
  static void indirect_copy(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
};

/*
  Unrolled computed assignment partial specialization for unrolled case
*/
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
struct __static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,true,FundT> {
  static void copy(LhsT &lhs, const RhsT &rhs);

  template<typename IndT>
  static void lhs_indirect_copy(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename IndT>
  static void rhs_indirect_copy(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename LhsIndT, typename RhsIndT>
  static void indirect_copy(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
};

template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
inline void
__static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,true,FundT>::copy(LhsT &lhs, const RhsT &rhs)
{
  lhs[B1+(L*S1)] = rhs[B2+(L*S2)];
  __static_assign<LhsT,RhsT,L+1,U,B1,B2,S1,S2,true,FundT>::copy(lhs,rhs);
}

template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
template<typename IndT>
inline void
__static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,true,FundT>::lhs_indirect_copy(LhsT &lhs,
  const RhsT &rhs, const IndT &ind)
{
  lhs[ind[B1+(L*S1)]] = rhs[B2+(L*S2)];
  __static_assign<LhsT,RhsT,L+1,U,B1,B2,S1,S2,true,FundT>::lhs_indirect_copy(lhs,rhs,ind);
}

template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
template<typename IndT>
inline void
__static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,true,FundT>::rhs_indirect_copy(LhsT &lhs,
  const RhsT &rhs, const IndT &ind)
{
  lhs[B1+(L*S1)] = rhs[ind[B2+(L*S2)]];
  __static_assign<LhsT,RhsT,L+1,U,B1,B2,S1,S2,true,FundT>::rhs_indirect_copy(lhs,rhs,ind);
}

template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
template<typename LhsIndT, typename RhsIndT>
inline void
__static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,true,FundT>::indirect_copy(LhsT &lhs,
  const RhsT &rhs, const LhsIndT &lhs_ind, const RhsIndT &rhs_ind)
{
  lhs[lhs_ind[B1+(L*S1)]] = rhs[rhs_ind[B2+(L*S2)]];
  __static_assign<LhsT,RhsT,L+1,U,B1,B2,S1,S2,true,FundT>::indirect_copy(lhs,rhs,
    lhs_ind,rhs_ind);
}

/*
  Unrolled assignment partial specialization for unrolled upper bound
*/
template<typename LhsT, typename RhsT, std::size_t U, std::size_t S1,
  std::size_t B1, std::size_t B2, std::size_t S2, bool FundT>
struct __static_assign<LhsT,RhsT,U,U,B1,B2,S1,S2,true,FundT> {
  static void copy(LhsT &lhs, const RhsT &rhs) {}

  template<typename IndT>
  static void lhs_indirect_copy(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}

  template<typename IndT>
  static void rhs_indirect_copy(LhsT &lhs, const RhsT &rhs, const IndT &ind) {}

  template<typename LhsIndT, typename RhsIndT>
  static void indirect_copy(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind) {}
};


/*
  Assignment partial specialization for non-rolled case
*/
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
struct __static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,false,FundT> {
  static void copy(LhsT &lhs, const RhsT &rhs);

  template<typename IndT>
  static void lhs_indirect_copy(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename IndT>
  static void rhs_indirect_copy(LhsT &lhs, const RhsT &rhs, const IndT &ind);

  template<typename LhsIndT, typename RhsIndT>
  static void indirect_copy(LhsT &lhs, const RhsT &rhs,
    const LhsIndT &lhs_ind, const RhsIndT &rhs_ind);
};

template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
inline void
__static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,false,FundT>::copy(LhsT &lhs, const RhsT &rhs)
{
  for(std::size_t i=L, s1=B1, s2=B2; i<U; ++i, s1+=S1, s2+=S2) {
    lhs[s1] = rhs[s2];
  }
}

template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
template<typename IndT>
inline void
__static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,false,FundT>::lhs_indirect_copy(LhsT &lhs,
  const RhsT &rhs, const IndT &ind)
{
  for(std::size_t i=L, s1=B1, s2=B2; i<U; ++i, s1+=S1, s2+=S2) {
    lhs[ind[s1]] = rhs[s2];
  }
}

template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
template<typename IndT>
inline void
__static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,false,FundT>::rhs_indirect_copy(LhsT &lhs,
  const RhsT &rhs, const IndT &ind)
{
  for(std::size_t i=L, s1=B1, s2=B2; i<U; ++i, s1+=S1, s2+=S2) {
    lhs[s1] = rhs[ind[s2]];
  }
}

template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2, std::size_t S1, std::size_t S2, bool FundT>
template<typename LhsIndT, typename RhsIndT>
inline void
__static_assign<LhsT,RhsT,L,U,B1,B2,S1,S2,false,FundT>::indirect_copy(LhsT &lhs,
  const RhsT &rhs, const LhsIndT &lhs_ind, const RhsIndT &rhs_ind)
{
  for(std::size_t i=L, s1=B1, s2=B2; i<U; ++i, s1+=S1, s2+=S2) {
    lhs[lhs_ind[s1]] = rhs[rhs_ind[s2]];
  }
}

/*
  Assignment partial specialization for memcopy
  Note: no indirect_copy
*/
template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2>
struct __static_assign<LhsT,RhsT,L,U,B1,B2,1,1,false,true> {
  static void copy(LhsT &lhs, const RhsT &rhs);
};

template<typename LhsT, typename RhsT, std::size_t L, std::size_t U,
  std::size_t B1, std::size_t B2>
inline void
__static_assign<LhsT,RhsT,L,U,B1,B2,1,1,false,true>::copy(LhsT &lhs, const RhsT &rhs)
{
  __restricted_copy<B1,B2,(U-L)>(lhs,rhs);
}

/*
  forward definitions
*/
template<typename T, std::size_t N>
class cvalarray;

template<typename T, std::size_t N, std::size_t M>
class cindirect_array;

template<typename T, std::size_t N, std::size_t StartN, std::size_t LengthN,
  std::size_t StrideN>
class cslice_array;

/*
  Expression template essentials
*/
template<typename T>
struct expression_traits {
  typedef const T & expression_ref;
};

template<typename T>
struct scalar_expression {
  scalar_expression(T s) :scalar(s) {}
  
  T operator[](std::size_t) const {return scalar;}

  T scalar;
};

template<typename T>
struct expression_traits<scalar_expression<T> > {
  typedef scalar_expression<T> expression_ref;
};

template<typename T, std::size_t N, typename RepT>
struct expression {
  expression(const RepT &r) :rep(r) {}

  T operator[](std::size_t i) const {return rep[i];}
  
  //can't take address cause we capture the temporary from return value
  RepT rep;
};

/*
  Unary expression operations
*/
template<typename T, std::size_t N, typename ValT>
struct __positive {
  __positive(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return +(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __negative {
  __negative(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return -(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __compl {
  __compl(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return ~(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __not {
  __not(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return !(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

/*
  Binary expression operations
*/
template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __multiply {
  __multiply(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] * rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __divides {
  __divides(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] / rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __modulus {
  __modulus(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] % rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __plus {
  __plus(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] + rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __minus {
  __minus(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] - rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __bitwise_xor {
  __bitwise_xor(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] ^ rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __bitwise_and {
  __bitwise_and(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] & rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __bitwise_or {
  __bitwise_or(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] | rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __left_shift {
  __left_shift(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] << rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<typename T, std::size_t N, typename LhsT, typename RhsT>
struct __right_shift {
  __right_shift(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  T operator[](std::size_t n) const {return lhs[n] >> rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

/*
  Logical operators
*/
template<std::size_t N, typename LhsT, typename RhsT>
struct __equals {
  __equals(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  bool operator[](std::size_t n) const {return lhs[n] == rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<std::size_t N, typename LhsT, typename RhsT>
struct __not_equals {
  __not_equals(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  bool operator[](std::size_t n) const {return lhs[n] != rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<std::size_t N, typename LhsT, typename RhsT>
struct __less_than {
  __less_than(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  bool operator[](std::size_t n) const {return lhs[n] < rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<std::size_t N, typename LhsT, typename RhsT>
struct __greater_than {
  __greater_than(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  bool operator[](std::size_t n) const {return lhs[n] > rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<std::size_t N, typename LhsT, typename RhsT>
struct __less_than_equal {
  __less_than_equal(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  bool operator[](std::size_t n) const {return lhs[n] <= rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<std::size_t N, typename LhsT, typename RhsT>
struct __greater_than_equal {
  __greater_than_equal(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  bool operator[](std::size_t n) const {return lhs[n] >= rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<std::size_t N, typename LhsT, typename RhsT>
struct __and {
  __and(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  bool operator[](std::size_t n) const {return lhs[n] && rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

template<std::size_t N, typename LhsT, typename RhsT>
struct __or {
  __or(const LhsT &l, const RhsT &r) :lhs(l), rhs(r) {}
  
  bool operator[](std::size_t n) const {return lhs[n] || rhs[n];}
  
  typename expression_traits<LhsT>::expression_ref lhs;
  typename expression_traits<RhsT>::expression_ref rhs;
};

/*
  Transcendental operators
*/
template<typename T, std::size_t N, typename ValT>
struct __abs {
  __abs(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::abs(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __acos {
  __acos(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::acos(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __asin {
  __asin(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::asin(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __atan {
  __atan(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::atan(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename Arg1T, typename Arg2T>
struct __atan2 {
  __atan2(const Arg1T &a1, const Arg2T &a2) :arg1(a1), arg2(a2) {}
  
  T operator[](std::size_t n) const {return std::atan2(arg1[n],arg2[n]);}
  
  typename expression_traits<Arg1T>::expression_ref arg1;
  typename expression_traits<Arg2T>::expression_ref arg2;
};

template<typename T, std::size_t N, typename ValT>
struct __cos {
  __cos(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::cos(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __cosh {
  __cosh(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::cosh(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __exp {
  __exp(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::exp(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __log {
  __log(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::log(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __log10 {
  __log10(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::log10(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename Arg1T, typename Arg2T>
struct __pow {
  __pow(const Arg1T &a1, const Arg2T &a2) :arg1(a1), arg2(a2) {}
  
  T operator[](std::size_t n) const {return std::pow(arg1[n],arg2[n]);}
  
  typename expression_traits<Arg1T>::expression_ref arg1;
  typename expression_traits<Arg2T>::expression_ref arg2;
};

template<typename T, std::size_t N, typename ValT>
struct __sin {
  __sin(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::sin(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __sinh {
  __sinh(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::sinh(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __sqrt {
  __sqrt(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::sqrt(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __tan {
  __tan(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::tan(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};

template<typename T, std::size_t N, typename ValT>
struct __tanh {
  __tanh(const ValT &val) :value(val) {}
  
  T operator[](std::size_t n) const {return std::tanh(value[n]);}
  
  typename expression_traits<ValT>::expression_ref value;
};


/*
  cslice definition and impl
*/
template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
class cslice {
  public:
    enum {
      slice_start = StartN,
      slice_length = LengthN,
      slice_stride = StrideN
    };

    cslice(void);
    ~cslice(void);
    
    std::size_t start(void) const;
    std::size_t size(void) const;
    std::size_t stride(void) const;
    
  private:
};

template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline cslice<StartN,LengthN,StrideN>::cslice(void)
{
}

template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline cslice<StartN,LengthN,StrideN>::~cslice(void)
{
}

template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline std::size_t cslice<StartN,LengthN,StrideN>::start(void) const
{
  return StartN;
}

template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline std::size_t cslice<StartN,LengthN,StrideN>::size(void) const
{
  return LengthN;
}

template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline std::size_t cslice<StartN,LengthN,StrideN>::stride(void) const
{
  return StrideN;
}


/**
 *  cslice_array definition and impl
 *
 *  todo, add unary positive, negative etc to cslice_array
 */
template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
class cslice_array {
  public:
    typedef T value_type;

    T operator[](std::size_t i) const;
    T & operator[](std::size_t i);

    expression<T,LengthN,__positive<T,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > > operator+(void) const;
    expression<T,LengthN,__negative<T,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > > operator-(void) const; 
    expression<T,LengthN,__compl<T,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > > operator~(void) const; 
    expression<bool,LengthN,__not<bool,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > > operator!(void) const; 

    void operator= (const T &rhs) const;
    void operator*= (const T &rhs) const;
    void operator/= (const T &rhs) const;
    void operator%= (const T &rhs) const; 
    void operator+= (const T &rhs) const;
    void operator-= (const T &rhs) const;
    void operator^= (const T &rhs) const;
    void operator&= (const T &rhs) const;
    void operator|= (const T &rhs) const;
    void operator<<=(const T &rhs) const;
    void operator>>=(const T &rhs) const;
    void operator= (const T (&rhs)[LengthN]) const;
    void operator*= (const T (&rhs)[LengthN]) const;
    void operator/= (const T (&rhs)[LengthN]) const;
    void operator%= (const T (&rhs)[LengthN]) const;
    void operator+= (const T (&rhs)[LengthN]) const;
    void operator-= (const T (&rhs)[LengthN]) const;
    void operator^= (const T (&rhs)[LengthN]) const;
    void operator|= (const T (&rhs)[LengthN]) const;
    void operator&= (const T (&rhs)[LengthN]) const;
    void operator<<=(const T (&rhs)[LengthN]) const;
    void operator>>=(const T (&rhs)[LengthN]) const;
    void operator= (const cvalarray<T,LengthN> &rhs) const;
    void operator*= (const cvalarray<T,LengthN> &rhs) const; 
    void operator/= (const cvalarray<T,LengthN> &rhs) const; 
    void operator%= (const cvalarray<T,LengthN> &rhs) const; 
    void operator+= (const cvalarray<T,LengthN> &rhs) const; 
    void operator-= (const cvalarray<T,LengthN> &rhs) const; 
    void operator^= (const cvalarray<T,LengthN> &rhs) const; 
    void operator&= (const cvalarray<T,LengthN> &rhs) const; 
    void operator|= (const cvalarray<T,LengthN> &rhs) const; 
    void operator<<=(const cvalarray<T,LengthN> &rhs) const; 
    void operator>>=(const cvalarray<T,LengthN> &rhs) const; 

    template<typename Rep>
    void operator= (const expression<T,LengthN,Rep> &rhs) const;
    template<typename Rep>
    void operator*= (const expression<T,LengthN,Rep> &rhs) const; 
    template<typename Rep>
    void operator/= (const expression<T,LengthN,Rep> &rhs) const; 
    template<typename Rep>
    void operator%= (const expression<T,LengthN,Rep> &rhs) const; 
    template<typename Rep>
    void operator+= (const expression<T,LengthN,Rep> &rhs) const; 
    template<typename Rep>
    void operator-= (const expression<T,LengthN,Rep> &rhs) const; 
    template<typename Rep>
    void operator^= (const expression<T,LengthN,Rep> &rhs) const; 
    template<typename Rep>
    void operator&= (const expression<T,LengthN,Rep> &rhs) const; 
    template<typename Rep>
    void operator|= (const expression<T,LengthN,Rep> &rhs) const; 
    template<typename Rep>
    void operator<<=(const expression<T,LengthN,Rep> &rhs) const; 
    template<typename Rep>
    void operator>>=(const expression<T,LengthN,Rep> &rhs) const; 

    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator= (const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator*=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator/=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator%=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator+=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator-=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator^=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator&=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator|=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator<<=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
    void operator>>=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const;

    template<std::size_t OtherN, std::size_t M>
    void operator= (const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator*=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator/=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator%=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator+=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator-=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator^=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator&=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator|=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator<<=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN, std::size_t M>
    void operator>>=(const cindirect_array<T,OtherN,M> &rhs) const;

    //void operator=(const T &rhs); 
    ~cslice_array(void);
    
  private:
    template<typename _T, std::size_t _N>
    friend class cvalarray;
    
    template<typename _T, std::size_t _N, std::size_t _StartN,
      std::size_t _LengthN, std::size_t _StrideN>
    friend class cslice_array;
    
    template<typename _T, std::size_t _N, std::size_t _M>
    friend class cindirect_array;

    cslice_array();
    //This reflects issue 253 from c++ working group
    //cslice_array(const cslice_array &rhs)
    //cslice_array& operator=(const cslice_array &rhs);

    // private constructor for construction by cvalarray, int used for
    // disambiguation only
    cslice_array(cvalarray<T,N> &base, int);

    cvalarray<T,N> *cvalarray_base;
};

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline cslice_array<T,N,StartN,LengthN,StrideN>::
  cslice_array(cvalarray<T,N> &base, int) :cvalarray_base(&base)
{
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline cslice_array<T,N,StartN,LengthN,StrideN>::~cslice_array(void)
{
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
T cslice_array<T,N,StartN,LengthN,StrideN>::operator[](std::size_t i) const
{
  return (*cvalarray_base)[StartN+(i*StrideN)];
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
T & cslice_array<T,N,StartN,LengthN,StrideN>::operator[](std::size_t i)
{
  return (*cvalarray_base)[StartN+(i*StrideN)];
}


template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline void cslice_array<T,N,StartN,LengthN,StrideN>::
  operator=(const T &rhs) const
{
  typedef scalar_expression<T> scalar_type;
  __static_assign<T[N],scalar_type,0,LengthN,StartN,0,StrideN,1,
    (N<=UNROLL_LIMIT),false>::copy(cvalarray_base->v,scalar_type(rhs));
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline void cslice_array<T,N,StartN,LengthN,StrideN>::
  operator=(const T (&rhs)[LengthN]) const
{
  __static_assign<T[N],T[LengthN],0,LengthN,StartN,0,StrideN,1,
    (N<=UNROLL_LIMIT),false>::copy(cvalarray_base->v,rhs);
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline void cslice_array<T,N,StartN,LengthN,StrideN>::
  operator=(const cvalarray<T,LengthN> &rhs) const
{
  __static_assign<T[N],T[LengthN],0,LengthN,StartN,0,StrideN,1,
    (N<=UNROLL_LIMIT),false>::copy(cvalarray_base->v,rhs.v);
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
template<typename Rep>
inline void cslice_array<T,N,StartN,LengthN,StrideN>::
  operator=(const expression<T,LengthN,Rep> &rhs) const
{
  __static_assign<T[N],const expression<T,LengthN,Rep>,0,LengthN,StartN,0,
    StrideN,1,(N<=UNROLL_LIMIT),false>::copy(cvalarray_base->v,rhs);
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN>
inline void cslice_array<T,N,StartN,LengthN,StrideN>::
  operator=(const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const
{
  __static_assign<T[N],T[OtherN],0,LengthN,StartN,OtherStartN,StrideN,OtherStrideN,
    (N<=UNROLL_LIMIT),false>::copy(cvalarray_base->v,rhs.cvalarray_base->v);
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
template<std::size_t OtherN, std::size_t M>
inline void cslice_array<T,N,StartN,LengthN,StrideN>::
  operator=(const cindirect_array<T,OtherN,M> &rhs) const
{
  __static_assign<T[N],T[OtherN],0,M,StartN,0,StrideN,1,(N<=UNROLL_LIMIT),false>::
    rhs_indirect_copy(cvalarray_base->v,rhs.cvalarray_base->v,rhs.cvalarray_indirect.v);
}

/*
  Member unary operators
*/
template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline expression<T,LengthN,__positive<T,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > >
cslice_array<T,N,StartN,LengthN,StrideN>::operator+(void) const
{
  typedef __positive<T,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > op_type;

  return expression<T,LengthN,op_type>(op_type(*this));
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline expression<T,LengthN,__negative<T,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > >
cslice_array<T,N,StartN,LengthN,StrideN>::operator-(void) const
{
  typedef __negative<T,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > op_type;

  return expression<T,LengthN,op_type>(op_type(*this));
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline expression<T,LengthN,__compl<T,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > >
cslice_array<T,N,StartN,LengthN,StrideN>::operator~(void) const
{
  typedef __compl<T,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > op_type;

  return expression<T,LengthN,op_type>(op_type(*this));
}

template<typename T, std::size_t N,
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline expression<bool,LengthN,__not<bool,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > >
cslice_array<T,N,StartN,LengthN,StrideN>::operator!(void) const
{
  typedef __not<bool,LengthN,cslice_array<T,N,StartN,LengthN,StrideN> > op_type;

  return expression<bool,LengthN,op_type>(op_type(*this));
}

/*
  computed assignment: 
*/
#define MAKE_CSLICE_ARRAY_MEMBER_OP(NAME,OP) \
template<typename T, std::size_t N, \
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN> \
inline void cslice_array<T,N,StartN,LengthN,StrideN>:: \
  operator OP(const T &rhs) const \
{ \
  typedef scalar_expression<T> scalar_type; \
  __static_op<T[N],scalar_type,0,LengthN,StartN,0,StrideN,1,(N<=UNROLL_LIMIT)>:: \
    NAME(cvalarray_base->v,scalar_type(rhs)); \
} \
\
template<typename T, std::size_t N, \
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN> \
inline void cslice_array<T,N,StartN,LengthN,StrideN>:: \
  operator OP(const T (&rhs)[LengthN]) const \
{ \
  __static_op<T[N],T[LengthN],0,LengthN,StartN,0,StrideN,1,(N<=UNROLL_LIMIT)>:: \
    NAME(cvalarray_base->v,rhs); \
} \
\
template<typename T, std::size_t N, \
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN> \
inline void cslice_array<T,N,StartN,LengthN,StrideN>:: \
  operator OP(const cvalarray<T,LengthN> &rhs) const \
{ \
  __static_op<T[N],T[LengthN],0,LengthN,StartN,0,StrideN,1,(N<=UNROLL_LIMIT)>:: \
    NAME(cvalarray_base->v,rhs.v); \
} \
\
template<typename T, std::size_t N, \
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN> \
template<typename Rep> \
inline void cslice_array<T,N,StartN,LengthN,StrideN>:: \
  operator OP (const expression<T,LengthN,Rep> &rhs) const \
{ \
  typedef const expression<T,LengthN,Rep> expr_t; \
  __static_op<T[N],expr_t,0,LengthN,StartN,0,StrideN,1,(N<=UNROLL_LIMIT)>:: \
    NAME(cvalarray_base->v,rhs); \
}\
\
template<typename T, std::size_t N, \
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN> \
template<std::size_t OtherN, std::size_t OtherStartN, std::size_t OtherStrideN> \
inline void cslice_array<T,N,StartN,LengthN,StrideN>:: \
  operator OP (const cslice_array<T,OtherN,OtherStartN,LengthN,OtherStrideN> &rhs) const \
{ \
  __static_op<T[N],T[OtherN],0,LengthN,StartN,OtherStartN,StrideN,OtherStrideN, \
    (N<=UNROLL_LIMIT)>::NAME(cvalarray_base->v,rhs.cvalarray_base->v); \
} \
\
template<typename T, std::size_t N, \
  std::size_t StartN, std::size_t LengthN, std::size_t StrideN> \
template<std::size_t OtherN, std::size_t M> \
inline void cslice_array<T,N,StartN,LengthN,StrideN>:: \
  operator OP (const cindirect_array<T,OtherN,M> &rhs) const \
{ \
  __static_op<T[N],T[OtherN],0,M,StartN,0,StrideN,1,(N<=UNROLL_LIMIT)>:: \
    NAME##_rhs_indirect(cvalarray_base->v,rhs.cvalarray_base->v, \
    rhs.cvalarray_indirect->v); \
}

MAKE_CSLICE_ARRAY_MEMBER_OP(multiply_assign,*=)
MAKE_CSLICE_ARRAY_MEMBER_OP(divides_assign,/=)
MAKE_CSLICE_ARRAY_MEMBER_OP(modulus_assign,%=)
MAKE_CSLICE_ARRAY_MEMBER_OP(plus_assign,+=)
MAKE_CSLICE_ARRAY_MEMBER_OP(minus_assign,-=)
MAKE_CSLICE_ARRAY_MEMBER_OP(bitwise_xor_assign,^=)
MAKE_CSLICE_ARRAY_MEMBER_OP(bitwise_and_assign,&=)
MAKE_CSLICE_ARRAY_MEMBER_OP(bitwise_or_assign,|=)
MAKE_CSLICE_ARRAY_MEMBER_OP(left_shift_assign,<<=)
MAKE_CSLICE_ARRAY_MEMBER_OP(right_shift_assign,>>=)



/**
 *  cindirect_array definition and impl
 *
 *  todo, add unary positive, negative etc to cindirect_array
 */
template<typename T, std::size_t N, std::size_t M>
class cindirect_array {
  public:
    typedef T value_type;
    
    T operator[](std::size_t i) const;
    T & operator[](std::size_t i);

    expression<T,M,__positive<T,M,cindirect_array<T,N,M> > > operator+(void) const;
    expression<T,M,__negative<T,M,cindirect_array<T,N,M> > > operator-(void) const; 
    expression<T,M,__compl<T,M,cindirect_array<T,N,M> > > operator~(void) const; 
    expression<bool,M,__not<bool,M,cindirect_array<T,N,M> > > operator!(void) const; 

    void operator= (const T &rhs) const;
    void operator*= (const T &rhs) const;
    void operator/= (const T &rhs) const;
    void operator%= (const T &rhs) const; 
    void operator+= (const T &rhs) const;
    void operator-= (const T &rhs) const;
    void operator^= (const T &rhs) const;
    void operator&= (const T &rhs) const;
    void operator|= (const T &rhs) const;
    void operator<<=(const T &rhs) const;
    void operator>>=(const T &rhs) const;
    void operator= (const T (&rhs)[M]) const;
    void operator*= (const T (&rhs)[M]) const;
    void operator/= (const T (&rhs)[M]) const;
    void operator%= (const T (&rhs)[M]) const;
    void operator+= (const T (&rhs)[M]) const;
    void operator-= (const T (&rhs)[M]) const;
    void operator^= (const T (&rhs)[M]) const;
    void operator|= (const T (&rhs)[M]) const;
    void operator&= (const T (&rhs)[M]) const;
    void operator<<=(const T (&rhs)[M]) const;
    void operator>>=(const T (&rhs)[M]) const;
    void operator= (const cvalarray<T,M> &rhs) const;
    void operator*= (const cvalarray<T,M> &rhs) const; 
    void operator/= (const cvalarray<T,M> &rhs) const; 
    void operator%= (const cvalarray<T,M> &rhs) const; 
    void operator+= (const cvalarray<T,M> &rhs) const; 
    void operator-= (const cvalarray<T,M> &rhs) const; 
    void operator^= (const cvalarray<T,M> &rhs) const; 
    void operator&= (const cvalarray<T,M> &rhs) const; 
    void operator|= (const cvalarray<T,M> &rhs) const; 
    void operator<<=(const cvalarray<T,M> &rhs) const; 
    void operator>>=(const cvalarray<T,M> &rhs) const; 

    template<typename Rep>
    void operator= (const expression<T,M,Rep> &rhs) const;
    template<typename Rep>
    void operator*= (const expression<T,M,Rep> &rhs) const; 
    template<typename Rep>
    void operator/= (const expression<T,M,Rep> &rhs) const; 
    template<typename Rep>
    void operator%= (const expression<T,M,Rep> &rhs) const; 
    template<typename Rep>
    void operator+= (const expression<T,M,Rep> &rhs) const; 
    template<typename Rep>
    void operator-= (const expression<T,M,Rep> &rhs) const; 
    template<typename Rep>
    void operator^= (const expression<T,M,Rep> &rhs) const; 
    template<typename Rep>
    void operator&= (const expression<T,M,Rep> &rhs) const; 
    template<typename Rep>
    void operator|= (const expression<T,M,Rep> &rhs) const; 
    template<typename Rep>
    void operator<<=(const expression<T,M,Rep> &rhs) const; 
    template<typename Rep>
    void operator>>=(const expression<T,M,Rep> &rhs) const; 

    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator= (const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator*=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator/=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator%=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator+=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator-=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator^=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator&=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator|=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator<<=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    void operator>>=(const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const;

    template<std::size_t OtherN>
    void operator= (const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator*=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator/=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator%=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator+=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator-=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator^=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator&=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator|=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator<<=(const cindirect_array<T,OtherN,M> &rhs) const;
    template<std::size_t OtherN>
    void operator>>=(const cindirect_array<T,OtherN,M> &rhs) const;

    //void operator=(const T &rhs); 
    ~cindirect_array(void);
    
  private:
    template<typename _T, std::size_t _N>
    friend class cvalarray;
    
    template<typename _T, std::size_t _N, std::size_t _StartN,
      std::size_t _LengthN, std::size_t _StrideN>
    friend class cslice_array;
    
    template<typename _T, std::size_t _N, std::size_t _M>
    friend class cindirect_array;
    
    cindirect_array();
    //This reflects issue 253 from c++ working group
    //cindirect_array(const cindirect_array &rhs)
    //cindirect_array& operator=(const cindirect_array &rhs);

    cindirect_array(const cvalarray<std::size_t,M> &indirect,
      cvalarray<T,N> &base);

    const cvalarray<std::size_t,M> cvalarray_indirect;
    cvalarray<T,N> *cvalarray_base;
};

template<typename T, std::size_t N, std::size_t M>
inline cindirect_array<T,N,M>::
  cindirect_array(const cvalarray<std::size_t,M> &indirect,
  cvalarray<T,N> &base) :cvalarray_indirect(indirect), cvalarray_base(&base)
{
}

template<typename T, std::size_t N, std::size_t M>
inline cindirect_array<T,N,M>::~cindirect_array(void)
{
}

template<typename T, std::size_t N, std::size_t M>
inline T cindirect_array<T,N,M>::operator[](std::size_t i) const
{
  return (*cvalarray_base)[cvalarray_indirect[i]];
}

template<typename T, std::size_t N, std::size_t M>
inline T & cindirect_array<T,N,M>::operator[](std::size_t i)
{
  return (*cvalarray_base)[cvalarray_indirect[i]];
}

template<typename T, std::size_t N, std::size_t M>
inline void cindirect_array<T,N,M>::operator=(const T &rhs) const
{
  typedef scalar_expression<T> scalar_type;
  __static_assign<T[N],scalar_type,0,M,0,0,1,1,(N<=UNROLL_LIMIT),false>
    ::lhs_indirect_copy(cvalarray_base->v,scalar_type(rhs),cvalarray_indirect.v);
}

template<typename T, std::size_t N, std::size_t M>
inline void cindirect_array<T,N,M>::operator=(const T (&rhs)[M]) const
{
  __static_assign<T[N],T[M],0,M,0,0,1,1,(N<=UNROLL_LIMIT),false>
    ::lhs_indirect_copy(cvalarray_base->v,rhs,cvalarray_indirect.v);
}

template<typename T, std::size_t N, std::size_t M>
inline void cindirect_array<T,N,M>::operator=(const cvalarray<T,M> &rhs) const
{
  __static_assign<T[N],T[M],0,M,0,0,1,1,(N<=UNROLL_LIMIT),false>
    ::lhs_indirect_copy(cvalarray_base->v,rhs.v,cvalarray_indirect.v);
}

template<typename T, std::size_t N, std::size_t M>
template<typename Rep>
inline void cindirect_array<T,N,M>::
  operator=(const expression<T,M,Rep> &rhs) const
{
  typedef const expression<T,M,Rep> expr_t;
  __static_assign<T[N],expr_t,0,M,0,0,1,1,(N<=UNROLL_LIMIT),false>
    ::lhs_indirect_copy(cvalarray_base->v,rhs,cvalarray_indirect.v);
}

template<typename T, std::size_t N, std::size_t M>
template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
inline void cindirect_array<T,N,M>::
  operator= (const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const
{
  __static_assign<T[N],T[OtherN],0,M,0,StartN,1,StrideN,(N<=UNROLL_LIMIT),
    false>::lhs_indirect_copy(cvalarray_base->v,rhs.cvalarray_base->v,
    cvalarray_indirect.v);
}

template<typename T, std::size_t N, std::size_t M>
template<std::size_t OtherN>
inline void cindirect_array<T,N,M>::
  operator=(const cindirect_array<T,OtherN,M> &rhs) const
{
  __static_assign<T[N],T[OtherN],0,M,0,0,1,1,(N<=UNROLL_LIMIT),false>
    ::indirect_copy(cvalarray_base->v,rhs.cvalarray_base->v,
    cvalarray_indirect.v,rhs.cvalarray_indirect.v);
}

/*
  Member unary operators
*/
template<typename T, std::size_t N, std::size_t M>
inline expression<T,M,__positive<T,M,cindirect_array<T,N,M> > >
cindirect_array<T,N,M>::operator+(void) const
{
  typedef __positive<T,M,cindirect_array<T,N,M> > op_type;

  return expression<T,M,op_type>(op_type(*this));
}

template<typename T, std::size_t N, std::size_t M>
inline expression<T,M,__negative<T,M,cindirect_array<T,N,M> > >
cindirect_array<T,N,M>::operator-(void) const
{
  typedef __negative<T,M,cindirect_array<T,N,M> > op_type;

  return expression<T,M,op_type>(op_type(*this));
}

template<typename T, std::size_t N, std::size_t M>
inline expression<T,M,__compl<T,M,cindirect_array<T,N,M> > >
cindirect_array<T,N,M>::operator~(void) const
{
  typedef __compl<T,M,cindirect_array<T,N,M> > op_type;

  return expression<T,M,op_type>(op_type(*this));
}

template<typename T, std::size_t N, std::size_t M>
inline expression<bool,M,__not<bool,M,cindirect_array<T,N,M> > >
cindirect_array<T,N,M>::operator!(void) const
{
  typedef __not<bool,M,cindirect_array<T,N,M> > op_type;

  return expression<bool,M,op_type>(op_type(*this));
}

/*
  computed assignment: 
*/
#define MAKE_CINDIRECT_ARRAY_MEMBER_OP(NAME,OP) \
template<typename T, std::size_t N, std::size_t M> \
inline void cindirect_array<T,N,M>::operator OP(const T &rhs) const \
{ \
  typedef scalar_expression<T> scalar_type; \
  __static_op<T[N],scalar_type,0,M,0,0,1,1,(N<=UNROLL_LIMIT)>:: \
    NAME##_lhs_indirect(cvalarray_base->v,scalar_type(rhs),cvalarray_indirect.v); \
} \
\
template<typename T, std::size_t N, std::size_t M> \
inline void cindirect_array<T,N,M>::operator OP(const T (&rhs)[M]) const \
{ \
  __static_op<T[N],T[M],0,M,0,0,1,1,(N<=UNROLL_LIMIT)>:: \
    NAME##_lhs_indirect(cvalarray_base->v,rhs,cvalarray_indirect.v); \
} \
\
template<typename T, std::size_t N, std::size_t M> \
inline void cindirect_array<T,N,M>:: \
  operator OP(const cvalarray<T,M> &rhs) const \
{ \
  __static_op<T[N],T[M],0,M,0,0,1,1,(N<=UNROLL_LIMIT)>:: \
    NAME##_lhs_indirect(cvalarray_base->v,rhs.v,cvalarray_indirect.v); \
} \
\
template<typename T, std::size_t N, std::size_t M> \
template<typename Rep> \
inline void cindirect_array<T,N,M>:: \
  operator OP (const expression<T,M,Rep> &rhs) const \
{ \
  typedef const expression<T,M,Rep> expr_t; \
  __static_op<T[N],expr_t,0,M,0,0,1,1,(N<=UNROLL_LIMIT)>:: \
    NAME##_lhs_indirect(cvalarray_base->v,rhs,cvalarray_indirect.v); \
}\
\
template<typename T, std::size_t N, std::size_t M> \
template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN> \
inline void cindirect_array<T,N,M>:: \
  operator OP (const cslice_array<T,OtherN,StartN,M,StrideN> &rhs) const \
{ \
  __static_op<T[N],T[OtherN],0,M,0,StartN,1,StrideN,(N<=UNROLL_LIMIT)>:: \
    NAME##_lhs_indirect(cvalarray_base->v,rhs.cvalarray_base->v, \
    cvalarray_indirect.v); \
} \
\
template<typename T, std::size_t N, std::size_t M> \
template<std::size_t OtherN> \
inline void cindirect_array<T,N,M>:: \
  operator OP (const cindirect_array<T,OtherN,M> &rhs) const \
{ \
  __static_op<T[N],T[OtherN],0,M,0,0,1,1,(N<=UNROLL_LIMIT)>:: \
    NAME##_indirect(cvalarray_base->v,rhs.cvalarray_base->v, \
    cvalarray_indirect.v, rhs.cvalarray_indirect.v); \
}


//MAKE_CINDIRECT_ARRAY_MEMBER_OP(=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(multiply_assign,*=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(divides_assign,/=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(modulus_assign,%=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(plus_assign,+=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(minus_assign,-=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(bitwise_xor_assign,^=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(bitwise_and_assign,&=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(bitwise_or_assign,|=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(left_shift_assign,<<=)
MAKE_CINDIRECT_ARRAY_MEMBER_OP(right_shift_assign,>>=)

/*
  cvalarray definition and impl
*/
template<typename T, std::size_t N>
class cvalarray { 
  public: 
    typedef T value_type;
    enum {const_size = N};

    //26.3.2.1 construct/destroy: 
    cvalarray(void);
    cvalarray(const T &rhs, std::size_t n);
    cvalarray(const T *rhs, std::size_t n);
    cvalarray(const T (&rhs)[N]); //added
    cvalarray(const cvalarray &rhs);
    
    template<typename RepT>
    cvalarray(const expression<T,N,RepT> &rhs);
    
    template<std::size_t M, std::size_t StartN, std::size_t StrideN>
    cvalarray(const cslice_array<T,M,StartN,N,StrideN> &rhs); 

    template<std::size_t M>
    cvalarray(const cindirect_array<T,M,N> &rhs); 
    ~cvalarray(void);

    //26.3.2.2 assignment: 
    cvalarray<T,N> & operator=(const cvalarray<T,N> &rhs);
    cvalarray<T,N> & operator=(const T &rhs);
    cvalarray<T,N> & operator=(const T (&rhs)[N]);

    template<typename RepT>
    cvalarray<T,N> & operator=(const expression<T,N,RepT> &rhs);

    template<std::size_t M, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator=(const cslice_array<T,M,StartN,N,StrideN> &rhs); 

    template<std::size_t M>
    cvalarray<T,N> & operator=(const cindirect_array<T,M,N> &rhs);
    
    //26.3.2.3 element access: 
    T operator[](std::size_t n) const; 
    T & operator[](std::size_t n); 

    //26.3.2.4 subset operations:
    template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
    cvalarray<T,LengthN> operator[](cslice<StartN,LengthN,StrideN> &) const;

    template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
    cslice_array<T,N,StartN,LengthN,StrideN>
      operator[](const cslice<StartN,LengthN,StrideN> &);

    template<std::size_t M>
    cvalarray<T,M> operator[](const cvalarray<std::size_t,M> &arr) const; 

    template<std::size_t M>
    cindirect_array<T,N,M> operator[](const cvalarray<std::size_t,M> &arr);

    //26.3.2.5 unary operators: 
    expression<T,N,__positive<T,N,cvalarray<T,N> > > operator+(void) const;
    expression<T,N,__negative<T,N,cvalarray<T,N> > > operator-(void) const; 
    expression<T,N,__compl<T,N,cvalarray<T,N> > > operator~(void) const; 
    expression<bool,N,__not<bool,N,cvalarray<T,N> > > operator!(void) const; 

    //26.3.2.6 computed assignment: 
    cvalarray<T,N>& operator*= (const T &rhs);
    cvalarray<T,N>& operator/= (const T &rhs);
    cvalarray<T,N>& operator%= (const T &rhs); 
    cvalarray<T,N>& operator+= (const T &rhs);
    cvalarray<T,N>& operator-= (const T &rhs);
    cvalarray<T,N>& operator^= (const T &rhs);
    cvalarray<T,N>& operator&= (const T &rhs);
    cvalarray<T,N>& operator|= (const T &rhs);
    cvalarray<T,N>& operator<<=(const T &rhs);
    cvalarray<T,N>& operator>>=(const T &rhs);
    cvalarray<T,N>& operator*= (const T (&rhs)[N]);
    cvalarray<T,N>& operator/= (const T (&rhs)[N]);
    cvalarray<T,N>& operator%= (const T (&rhs)[N]);
    cvalarray<T,N>& operator+= (const T (&rhs)[N]);
    cvalarray<T,N>& operator-= (const T (&rhs)[N]);
    cvalarray<T,N>& operator^= (const T (&rhs)[N]);
    cvalarray<T,N>& operator|= (const T (&rhs)[N]);
    cvalarray<T,N>& operator&= (const T (&rhs)[N]);
    cvalarray<T,N>& operator<<=(const T (&rhs)[N]);
    cvalarray<T,N>& operator>>=(const T (&rhs)[N]);
    cvalarray<T,N>& operator*= (const cvalarray<T,N> &rhs);
    cvalarray<T,N>& operator/= (const cvalarray<T,N> &rhs);
    cvalarray<T,N>& operator%= (const cvalarray<T,N> &rhs);
    cvalarray<T,N>& operator+= (const cvalarray<T,N> &rhs);
    cvalarray<T,N>& operator-= (const cvalarray<T,N> &rhs);
    cvalarray<T,N>& operator^= (const cvalarray<T,N> &rhs);
    cvalarray<T,N>& operator|= (const cvalarray<T,N> &rhs);
    cvalarray<T,N>& operator&= (const cvalarray<T,N> &rhs);
    cvalarray<T,N>& operator<<=(const cvalarray<T,N> &rhs);
    cvalarray<T,N>& operator>>=(const cvalarray<T,N> &rhs);

    template<typename RepT>
    cvalarray<T,N> & operator*= (const expression<T,N,RepT> &rhs);
    template<typename RepT>
    cvalarray<T,N> & operator/= (const expression<T,N,RepT> &rhs);
    template<typename RepT>
    cvalarray<T,N> & operator%= (const expression<T,N,RepT> &rhs);
    template<typename RepT>
    cvalarray<T,N> & operator+= (const expression<T,N,RepT> &rhs);
    template<typename RepT>
    cvalarray<T,N> & operator-= (const expression<T,N,RepT> &rhs);
    template<typename RepT>
    cvalarray<T,N> & operator^= (const expression<T,N,RepT> &rhs);
    template<typename RepT>
    cvalarray<T,N> & operator&= (const expression<T,N,RepT> &rhs);
    template<typename RepT>
    cvalarray<T,N> & operator|= (const expression<T,N,RepT> &rhs);
    template<typename RepT>
    cvalarray<T,N> & operator<<=(const expression<T,N,RepT> &rhs);
    template<typename RepT>
    cvalarray<T,N> & operator>>=(const expression<T,N,RepT> &rhs);

    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator*=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator/=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator%=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator+=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator-=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator^=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator&=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator|=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator<<=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);
    template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN>
    cvalarray<T,N> & operator>>=(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs);

    template<std::size_t OtherN>
    cvalarray<T,N> & operator*=(const cindirect_array<T,OtherN,N> &rhs);
    template<std::size_t OtherN>
    cvalarray<T,N> & operator/=(const cindirect_array<T,OtherN,N> &rhs);
    template<std::size_t OtherN>
    cvalarray<T,N> & operator%=(const cindirect_array<T,OtherN,N> &rhs);
    template<std::size_t OtherN>
    cvalarray<T,N> & operator+=(const cindirect_array<T,OtherN,N> &rhs);
    template<std::size_t OtherN>
    cvalarray<T,N> & operator-=(const cindirect_array<T,OtherN,N> &rhs);
    template<std::size_t OtherN>
    cvalarray<T,N> & operator^=(const cindirect_array<T,OtherN,N> &rhs);
    template<std::size_t OtherN>
    cvalarray<T,N> & operator&=(const cindirect_array<T,OtherN,N> &rhs);
    template<std::size_t OtherN>
    cvalarray<T,N> & operator|=(const cindirect_array<T,OtherN,N> &rhs);
    template<std::size_t OtherN>
    cvalarray<T,N> & operator<<=(const cindirect_array<T,OtherN,N> &rhs);
    template<std::size_t OtherN>
    cvalarray<T,N> & operator>>=(const cindirect_array<T,OtherN,N> &rhs);
    
    //26.3.2.7 member functions:
    std::size_t size(void) const; 
    T sum(void) const; 
    T min(void) const; 
    T max(void) const; 
    cvalarray<T,N> shift (int n) const; 
    cvalarray<T,N> cshift(int n) const; 
    cvalarray<T,N> apply(T func(T)) const; 
    cvalarray<T,N> apply(T func(const T&)) const; 

  private:
    template<typename _T, std::size_t _N>
    friend class cvalarray;
    
    template<typename _T, std::size_t _N, std::size_t _StartN,
      std::size_t _LengthN, std::size_t _StrideN>
    friend class cslice_array;
    
    template<typename _T, std::size_t _N, std::size_t _M>
    friend class cindirect_array;

    template<typename _T, std::size_t _N,
      std::size_t _StartN, std::size_t _LengthN, std::size_t _StrideN>
    friend struct slice_expression;

    T v[N];
};

template<typename T, std::size_t N>
inline cvalarray<T,N>::cvalarray(void)
{
}

// todo
template<typename T, std::size_t N>
inline cvalarray<T,N>::cvalarray(const T &rhs, std::size_t n)
{
  if(sizeof(T) == 1)
    std::memset(v,int(rhs),n);
  else
    for(std::size_t i=0; i<n; ++i)
      v[i] = rhs;
}

template<typename T, std::size_t N>
inline cvalarray<T,N>::cvalarray(const T *rhs, std::size_t n)
{
  if(__is_fundamental<T>::value)
      std::memcpy(v,rhs,n*sizeof(T));
  else
    for(std::size_t i=0; i<n; ++i)
      v[i] = rhs[i];
}

template<typename T, std::size_t N>
inline cvalarray<T,N>::cvalarray(const T (&rhs)[N])
{
  __static_assign<T[N],T[N],0,N,0,0,1,1,(N<=UNROLL_LIMIT),
    __is_fundamental<T>::value>::copy(v,rhs);
}

template<typename T, std::size_t N>
inline cvalarray<T,N>::cvalarray(const cvalarray &rhs)
{
  __static_assign<T[N],T[N],0,N,0,0,1,1,(N<=UNROLL_LIMIT),
    __is_fundamental<T>::value>::copy(v,rhs.v);
}

template<typename T, std::size_t N>
template<typename RepT>
inline cvalarray<T,N>::cvalarray(const expression<T,N,RepT> &rhs)
{
  __static_assign<T[N],const expression<T,N,RepT>,0,N,0,0,1,1,(N<=UNROLL_LIMIT),
    false>::copy(v,rhs);
}

template<typename T, std::size_t N>
template<std::size_t M, std::size_t StartN, std::size_t StrideN>
inline cvalarray<T,N>::cvalarray(const cslice_array<T,M,StartN,N,StrideN> &rhs)
{
  __static_assign<T[N],T[M],0,N,0,StartN,1,StrideN,(N<=UNROLL_LIMIT),false>
    ::copy(v,rhs.cvalarray_base->v);
}

template<typename T, std::size_t N>
template<std::size_t M>
inline cvalarray<T,N>::cvalarray(const cindirect_array<T,M,N> &rhs)
{
  __static_assign<T[N],T[M],0,N,0,0,1,1,(N<=UNROLL_LIMIT),false>
    ::rhs_indirect_copy(v,rhs.cvalarray_base->v,rhs.cvalarray_indirect);
}


template<typename T, std::size_t N>
inline cvalarray<T,N>::~cvalarray(void)
{
}

template<typename T, std::size_t N>
inline cvalarray<T,N> & cvalarray<T,N>::operator=(const cvalarray &rhs)
{
  if(this != &rhs) {
    __static_assign<T[N],T[N],0,N,0,0,1,1,(N<=UNROLL_LIMIT),
      __is_fundamental<T>::value>::copy(v,rhs.v);
  }

  return *this;
}

template<typename T, std::size_t N>
inline cvalarray<T,N> & cvalarray<T,N>::operator=(const T &rhs)
{
  typedef scalar_expression<T> scalar_type;
  __static_assign<T[N],scalar_type,0,N,0,0,1,1,(N<=UNROLL_LIMIT),
    false>::copy(v,scalar_type(rhs));

  return *this;
}

template<typename T, std::size_t N>
inline cvalarray<T,N> & cvalarray<T,N>::operator=(const T (&rhs)[N])
{
  __static_assign<T[N],T[N],0,N,0,0,1,1,(N<=UNROLL_LIMIT),
    __is_fundamental<T>::value>::copy(v,rhs);

  return *this;
}


template<typename T, std::size_t N>
template<typename RepT>
inline cvalarray<T,N> &
cvalarray<T,N>::operator=(const expression<T,N,RepT> &rhs)
{
  __static_assign<T[N],const expression<T,N,RepT>,0,N,0,0,1,1,
    (N<=UNROLL_LIMIT),false>::copy(v,rhs);
  
  return *this;
}

template<typename T, std::size_t N>
template<std::size_t M, std::size_t StartN, std::size_t StrideN>
inline cvalarray<T,N> &
cvalarray<T,N>::operator=(const cslice_array<T,M,StartN,N,StrideN> &rhs)
{
  __static_assign<T[N],T[M],0,N,0,StartN,1,StrideN,(N<=UNROLL_LIMIT),
    __is_fundamental<T>::value>::copy(v,rhs.cvalarray_base->v);

  return *this;
} 

template<typename T, std::size_t N>
template<std::size_t M>
inline cvalarray<T,N> & 
cvalarray<T,N>::operator=(const cindirect_array<T,M,N> &rhs)
{
  __static_assign<T[N],T[M],0,N,0,0,1,1,(N<=UNROLL_LIMIT),false>
    ::rhs_indirect_copy(v,rhs.cvalarray_base->v,rhs.cvalarray_indirect.v);

  return *this;
}

template<typename T, std::size_t N>
inline T cvalarray<T,N>::operator[](std::size_t n) const
{
  return v[n];
}

template<typename T, std::size_t N>
inline T & cvalarray<T,N>::operator[](std::size_t n)
{
  return v[n];
}

template<typename T, std::size_t N>
template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline cvalarray<T,LengthN> 
cvalarray<T,N>::operator[](cslice<StartN,LengthN,StrideN> &) const
{
  cvalarray<T,LengthN> res;
  
  __static_assign<T[LengthN],T[N],0,LengthN,0,StartN,1,StrideN,(N<=UNROLL_LIMIT),
    false>::copy(res.v,v);

  return res;
}

template<typename T, std::size_t N>
template<std::size_t StartN, std::size_t LengthN, std::size_t StrideN>
inline cslice_array<T,N,StartN,LengthN,StrideN>
cvalarray<T,N>::operator[](const cslice<StartN,LengthN,StrideN> &)
{
  return cslice_array<T,N,StartN,LengthN,StrideN>(*this,0);
}

template<typename T, std::size_t N>
template<std::size_t M>
inline cvalarray<T,M>
cvalarray<T,N>::operator[](const cvalarray<std::size_t,M> &arr) const
{
  cvalarray<T,M> res;
  
  __static_assign<T[M],T[N],0,M,0,0,1,1,(N<=UNROLL_LIMIT),false>
    ::rhs_indirect_assign(res.v,v,arr.v);
  
  return res;
}

template<typename T, std::size_t N>
template<std::size_t M>
inline cindirect_array<T,N,M>
cvalarray<T,N>::operator[](const cvalarray<std::size_t,M> &arr)
{
  return cindirect_array<T,N,M>(arr,*this);
}

/*
  Member unary operators
*/
template<typename T, std::size_t N>
inline expression<T,N,__positive<T,N,cvalarray<T,N> > >
cvalarray<T,N>::operator+(void) const
{
  typedef __positive<T,N,cvalarray<T,N> > op_type;

  return expression<T,N,op_type>(op_type(*this));
}

template<typename T, std::size_t N>
inline expression<T,N,__negative<T,N,cvalarray<T,N> > >
cvalarray<T,N>::operator-(void) const
{
  typedef __negative<T,N,cvalarray<T,N> > op_type;

  return expression<T,N,op_type>(op_type(*this));
}

template<typename T, std::size_t N>
inline expression<T,N,__compl<T,N,cvalarray<T,N> > >
cvalarray<T,N>::operator~(void) const
{
  typedef __compl<T,N,cvalarray<T,N> > op_type;

  return expression<T,N,op_type>(op_type(*this));
}

template<typename T, std::size_t N>
inline expression<bool,N,__not<bool,N,cvalarray<T,N> > >
cvalarray<T,N>::operator!(void) const
{
  typedef __not<bool,N,cvalarray<T,N> > op_type;

  return expression<bool,N,op_type>(op_type(*this));
}

/*
  computed assignment: 
*/

#define MAKE_MEMBER_UNARYOP(NAME,OP) \
template<typename T, std::size_t N> \
inline cvalarray<T,N> & cvalarray<T,N>::OP(const T &rhs) \
{ \
  typedef scalar_expression<T> scalar_type; \
  __static_op<T[N],scalar_type,0,N,0,0,1,1,(N<=UNROLL_LIMIT)>:: \
    NAME(v,scalar_type(rhs)); \
\
  return *this; \
} \
\
template<typename T, std::size_t N> \
inline cvalarray<T,N> & cvalarray<T,N>::OP(const T (&rhs)[N]) \
{ \
  __static_op<T[N],T[N],0,N,0,0,1,1,(N<=UNROLL_LIMIT)>::NAME(v,rhs); \
  return *this; \
} \
\
template<typename T, std::size_t N> \
inline cvalarray<T,N> & cvalarray<T,N>::OP(const cvalarray<T,N> &rhs) \
{ \
  __static_op<T[N],T[N],0,N,0,0,1,1,(N<=UNROLL_LIMIT)>::NAME(v,rhs.v); \
  return *this; \
} \
\
template<typename T, std::size_t N> \
template<typename RepT> \
inline cvalarray<T,N> & \
cvalarray<T,N>::OP(const expression<T,N,RepT> &rhs) \
{ \
  __static_op<T[N],expression<T,N,RepT>,0,N,0,0,1,1,(N<=UNROLL_LIMIT)>:: \
    NAME(v,rhs); \
\
  return *this; \
} \
\
template<typename T, std::size_t N> \
template<std::size_t OtherN, std::size_t StartN, std::size_t StrideN> \
inline cvalarray<T,N> & \
cvalarray<T,N>::OP(const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  __static_op<T[N],T[OtherN],0,N,0,StartN,1,StrideN,(N<=UNROLL_LIMIT)>:: \
    NAME(v,rhs.v); \
\
  return *this; \
} \
\
template<typename T, std::size_t N> \
template<std::size_t OtherN> \
inline cvalarray<T,N> & \
cvalarray<T,N>::OP(const cindirect_array<T,OtherN,N> &rhs) \
{ \
  __static_op<T[N],T[OtherN],0,N,0,0,1,1,(N<=UNROLL_LIMIT)>:: \
    NAME##_rhs_indirect(v,rhs.cvalarray_base->v,rhs.cvalarray_indirect.v); \
\
  return *this; \
}


MAKE_MEMBER_UNARYOP(multiply_assign,operator*=)
MAKE_MEMBER_UNARYOP(divides_assign,operator/=)
MAKE_MEMBER_UNARYOP(modulus_assign,operator%=)
MAKE_MEMBER_UNARYOP(plus_assign,operator+=)
MAKE_MEMBER_UNARYOP(minus_assign,operator-=)
MAKE_MEMBER_UNARYOP(bitwise_xor_assign,operator^=)
MAKE_MEMBER_UNARYOP(bitwise_and_assign,operator&=)
MAKE_MEMBER_UNARYOP(bitwise_or_assign,operator|=)
MAKE_MEMBER_UNARYOP(left_shift_assign,operator<<=)
MAKE_MEMBER_UNARYOP(right_shift_assign,operator>>=)

/*
  member functions:
*/
template<typename T, std::size_t N>
inline std::size_t cvalarray<T,N>::size(void) const
{
  return N;
}

template<typename T, std::size_t N>
inline T cvalarray<T,N>::sum(void) const
{
  T init = 0;
  for(std::size_t i=0; i<N; ++i)
    init += v[i];
  return init;
}

template<typename T, std::size_t N>
inline T cvalarray<T,N>::min(void) const
{
  return *(std::min_element(v,v+N));
}

template<typename T, std::size_t N>
inline T cvalarray<T,N>::max(void) const
{
  return *(std::max_element(v,v+N));
}

template<typename T, std::size_t N>
cvalarray<T,N> cvalarray<T,N>::shift (int n) const
{
  if(n == 0)
    return *this;
  
  cvalarray<T,N> res;
  if(n > 0) {
    if(std::size_t(n) > N)
      return *this;
    
    for(std::size_t i=0; i<n; ++i)
      res.v[i] = T();
      
    for(std::size_t i=0, _i=n; i<(N-n); ++i, ++_i)
      res.v[_i] = v[i];
  }
  else {
    n = -n;
    for(std::size_t i=0, _i=n; i<(N-n); ++i, ++_i)
      res.v[i] = v[_i];
    
    for(std::size_t i=(N-n); i<N; ++i)
      res[i] = T();
  }

  return res;
}

template<typename T, std::size_t N>
cvalarray<T,N> cvalarray<T,N>::cshift (int n) const
{
  if(n == 0)
    return *this;
  
  cvalarray<T,N> res;
  if(n > 0) {
    n = (n % N);
    
    for(std::size_t i=0, _i = n; _i < N; ++i, ++_i)
      res.v[i] = v[_i];
    for(std::size_t i=0, _i = (N-n); _i < N; ++i, ++_i)
      res.v[_i] = v[i];
  }
  else {
    n = (-n % N);
    for(std::size_t i=0, _i = (N-n); _i < N; ++i, ++_i)
      res.v[i] = v[_i];
    for(std::size_t i=0, _i = n; _i < N; ++i, ++_i)
      res.v[_i] = v[i];
      
  }

  return res;
}

template<typename T, std::size_t N>
inline cvalarray<T,N> cvalarray<T,N>::apply(T func(T)) const
{
  cvalarray<T,N> res;
  for(std::size_t i=0; i<N; ++i)
    res.v[i] = func(v[i]);
  return res;
}

//todo
template<typename T, std::size_t N>
inline cvalarray<T,N> cvalarray<T,N>::apply(T func(const T&)) const
{
  cvalarray<T,N> res;
  for(std::size_t i=0; i<N; ++i)
    res.v[i] = func(v[i]);
  return res;
}

#define MAKE_NONMEMBER_EXPR_UNARYOP(NAME,OP) \
template<typename T, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,expression<T,N,RepT> > > \
OP(const expression<T,N,RepT> &val) \
{ \
  typedef NAME<T,N,expression<T,N,RepT> > op_type; \
\
  return expression<T,N,op_type>(op_type(val)); \
}


/**
 *  Each has:
 *  operator: expression<OP> OP (const cvalarray &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const T &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const T &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const T &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const T &rhs);
 *  operator: expression<OP> OP (const T (&lhs)[N], const cvalarray &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const T (&rhs)[N]);
 *  operator: expression<OP> OP (const T (&lhs)[N], const expression<> &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const T (&rhs)[N]);
 *  
 *  Below reflects issue 93 from c++ working group
 *  operator: expression<OP> OP (const cslice_array &lhs, const cslice_array &rhs);
 *  operator: expression<OP> OP (const cslice_array &lhs, const T &rhs);
 *  operator: expression<OP> OP (const T &lhs, const cslice_array &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const cslice_array &rhs);
 *  operator: expression<OP> OP (const cslice_array &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const cslice_array &rhs);
 *  operator: expression<OP> OP (const cslice_array &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const T (&lhs)[N], const cslice_array &rhs);
 *  operator: expression<OP> OP (const cslice_array &lhs, const T (&rhs)[N]);
 *  operator: expression<OP> OP (const cslice_array &lhs, const cindirect_array &rhs);
 *  
 *  operator: expression<OP> OP (const cindirect_array &lhs, const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const T &rhs);
 *  operator: expression<OP> OP (const T &lhs, const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const T (&lhs)[N], const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const T (&rhs)[N]);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const cslice_array &rhs);
 */

#define MAKE_NONMEMBER_BINOP(NAME,OP) \
template<typename T, std::size_t N> \
inline expression<T,N,NAME<T,N,cvalarray<T,N>,cvalarray<T,N> > > \
OP(const cvalarray<T,N> &lhs, const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<T,N,cvalarray<T,N>,cvalarray<T,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N>  \
inline expression<T,N,NAME<T,N,scalar_expression<T>,cvalarray<T,N> > > \
OP(const T &lhs, const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<T,N,scalar_expression<T>,cvalarray<T,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N> \
inline expression<T,N,NAME<T,N,cvalarray<T,N>,scalar_expression<T> > > \
OP(const cvalarray<T,N> &lhs, const T &rhs) \
{ \
  typedef NAME<T,N,cvalarray<T,N>,scalar_expression<T> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT1, typename RepT2> \
inline expression<T,N,NAME<T,N,RepT1,RepT2> > \
OP(const expression<T,N,RepT1> &lhs, const expression<T,N,RepT2> &rhs) \
{ \
  typedef NAME<T,N,RepT1,RepT2> op_type; \
\
  return expression<T,N,op_type>(op_type(lhs.rep,rhs.rep)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,cvalarray<T,N>,RepT> > \
OP(const cvalarray<T,N> &lhs, const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<T,N,cvalarray<T,N>,RepT> op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,RepT,cvalarray<T,N> > > \
OP(const expression<T,N,RepT> &lhs, const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<T,N,RepT,cvalarray<T,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,scalar_expression<T>,RepT> > \
OP(const T &lhs, const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<T,N,scalar_expression<T>,RepT> op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,RepT,scalar_expression<T> > > \
OP(const expression<T,N,RepT> &lhs, const T &rhs) \
{ \
  typedef NAME<T,N,RepT,scalar_expression<T> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t N> \
inline expression<T,N,NAME<T,N,cvalarray<T,N>,T[N]> > \
OP(const cvalarray<T,N> &lhs, const T (&rhs)[N]) \
{ \
  typedef NAME<T,N,cvalarray<T,N>,T[N]> op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N> \
inline expression<T,N,NAME<T,N,T[N],cvalarray<T,N> > > \
OP(const T (&lhs)[N], const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<T,N,T[N],cvalarray<T,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,T[N],RepT> > \
OP(const T (&lhs)[N], const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<T,N,T[N],RepT> op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,RepT,T[N]> > \
OP(const expression<T,N,RepT> &lhs, const T (&rhs)[N]) \
{ \
  typedef NAME<T,N,RepT,T[N]> op_type; \
\
  return expression<T,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, std::size_t OtherM, \
  std::size_t StartN, std::size_t StartM, std::size_t StrideN, std::size_t StrideM> \
inline expression<T,N,NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>, \
  cslice_array<T,OtherM,StartM,N,StrideM> > > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, const cslice_array<T,OtherM,StartM,N,StrideM> &rhs) \
{ \
  typedef NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>, \
    cslice_array<T,OtherM,StartM,N,StrideM> > op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>, \
  scalar_expression<T> > > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, const T &rhs) \
{ \
  typedef scalar_expression<T> scalar_t; \
  typedef NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>, \
    scalar_t> op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,scalar_t(rhs))); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,scalar_expression<T>, \
  cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const T &lhs, const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<T,N,scalar_expression<T>, \
    cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,cvalarray<T,N>, \
  cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const cvalarray<T,N> &lhs, \
  const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<T,N,cvalarray<T,N>,cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>, \
   cvalarray<T,N> > > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, \
  const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>, \
    cvalarray<T,N> > op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,RepT,cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const expression<T,N,RepT> &lhs, const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<T,N,RepT,cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>,RepT> > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>,RepT> op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,T[N],cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const T (&lhs)[N], const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<T,N,T[N],cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>,T[N]> > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, const T (&rhs)[N]) \
{ \
  typedef NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>,T[N]> op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t O, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>, \
  cindirect_array<T,O,N> > >\
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, \
  const cindirect_array<T,O,N> &rhs) \
{ \
  typedef NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN>, \
    cindirect_array<T,O,N> > op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t O, std::size_t N> \
inline expression<T,N,NAME<T,N,cindirect_array<T,M,N>,cindirect_array<T,O,N> > > \
OP(const cindirect_array<T,M,N> &lhs, const cindirect_array<T,O,N> &rhs) \
{ \
  typedef NAME<T,N,cindirect_array<T,M,N>,cindirect_array<T,O,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<T,N,NAME<T,N,cindirect_array<T,M,N>,scalar_expression<T> > > \
OP(const cindirect_array<T,M,N> &lhs, const T &rhs) \
{ \
  typedef NAME<T,N,cindirect_array<T,M,N>,scalar_expression<T> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<T,N,NAME<T,N,scalar_expression<T>,cindirect_array<T,M,N> > > \
OP(const T &lhs, const cindirect_array<T,M,N> &rhs) \
{ \
  typedef NAME<T,N,scalar_expression<T>,cindirect_array<T,M,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<T,N,NAME<T,N,cvalarray<T,N>,cindirect_array<T,M,N> > > \
OP(const cvalarray<T,N> &lhs, const cindirect_array<T,M,N> &rhs) \
{ \
  typedef NAME<T,N,cvalarray<T,N>,cindirect_array<T,M,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<T,N,NAME<T,N,cindirect_array<T,M,N>,cvalarray<T,N> > > \
OP(const cindirect_array<T,M,N> &lhs, const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<T,N,cindirect_array<T,M,N>,cvalarray<T,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,RepT,cindirect_array<T,M,N> > > \
OP(const expression<T,N,RepT> &lhs, const cindirect_array<T,M,N> &rhs) \
{ \
  typedef NAME<T,N,RepT,cindirect_array<T,M,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,cindirect_array<T,M,N>,RepT> > \
OP(const cindirect_array<T,M,N> &lhs, const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<T,N,cindirect_array<T,M,N>,RepT> op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<T,N,NAME<T,N,T[N],cindirect_array<T,M,N> > > \
OP(const T (&lhs)[N], const cindirect_array<T,M,N> &rhs) \
{ \
  typedef NAME<T,N,T[N],cindirect_array<T,M,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<T,N,NAME<T,N,cindirect_array<T,M,N>,T[N]> > \
OP(const cindirect_array<T,M,N> &lhs, const T (&rhs)[N]) \
{ \
  typedef NAME<T,N,cindirect_array<T,M,N>,T[N]> op_type; \
\
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t O, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,cindirect_array<T,O,N>, \
  cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const cindirect_array<T,O,N> &lhs, \
  const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<T,N,cindirect_array<T,O,N>, \
    cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<T,N,op_type>(op_type(lhs,rhs)); \
}


/**
 *  The non-mamber logic binary functions are the same as normal binary ops
 *  except that they return a boolean valued expression
 *  
 *  Each has:
 *  operator: expression<OP> OP (const cvalarray &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const T &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const T &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const T &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const T &rhs);
 *  operator: expression<OP> OP (const T (&lhs)[N], const cvalarray &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const T (&rhs)[N]);
 *  operator: expression<OP> OP (const T (&lhs)[N], const expression<> &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const T (&rhs)[N]);
 *  
 *  Below reflects issue 93 from c++ working group
 *  operator: expression<OP> OP (const cslice_array &lhs, const cslice_array &rhs);
 *  operator: expression<OP> OP (const cslice_array &lhs, const T &rhs);
 *  operator: expression<OP> OP (const T &lhs, const cslice_array &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const cslice_array &rhs);
 *  operator: expression<OP> OP (const cslice_array &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const cslice_array &rhs);
 *  operator: expression<OP> OP (const cslice_array &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const T (&lhs)[N], const cslice_array &rhs);
 *  operator: expression<OP> OP (const cslice_array &lhs, const T (&rhs)[N]);
 *  operator: expression<OP> OP (const cslice_array &lhs, const cindirect_array &rhs);
 *  
 *  operator: expression<OP> OP (const cindirect_array &lhs, const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const T &rhs);
 *  operator: expression<OP> OP (const T &lhs, const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cvalarray &lhs, const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const cvalarray &rhs);
 *  operator: expression<OP> OP (const expression<> &lhs, const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const expression<> &rhs);
 *  operator: expression<OP> OP (const T (&lhs)[N], const cindirect_array &rhs);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const T (&rhs)[N]);
 *  operator: expression<OP> OP (const cindirect_array &lhs, const cslice_array &rhs);
 */

#define MAKE_NONMEMBER_LOGIC_BINOP(NAME,OP) \
template<typename T, std::size_t N> \
inline expression<bool,N,NAME<N,cvalarray<T,N>,cvalarray<T,N> > > \
OP(const cvalarray<T,N> &lhs, const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<N,cvalarray<T,N>,cvalarray<T,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N>  \
inline expression<bool,N,NAME<N,scalar_expression<T>,cvalarray<T,N> > > \
OP(const T &lhs, const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<N,scalar_expression<T>,cvalarray<T,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N> \
inline expression<bool,N,NAME<N,cvalarray<T,N>,scalar_expression<T> > > \
OP(const cvalarray<T,N> &lhs, const T &rhs) \
{ \
  typedef NAME<N,cvalarray<T,N>,scalar_expression<T> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT1, typename RepT2> \
inline expression<bool,N,NAME<N,RepT1,RepT2> > \
OP(const expression<T,N,RepT1> &lhs, const expression<T,N,RepT2> &rhs) \
{ \
  typedef NAME<N,RepT1,RepT2> op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs.rep,rhs.rep)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<bool,N,NAME<N,cvalarray<T,N>,RepT> > \
OP(const cvalarray<T,N> &lhs, const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<N,cvalarray<T,N>,RepT> op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<bool,N,NAME<N,RepT,cvalarray<T,N> > > \
OP(const expression<T,N,RepT> &lhs, const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<N,RepT,cvalarray<T,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<bool,N,NAME<N,scalar_expression<T>,RepT> > \
OP(const T &lhs, const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<N,scalar_expression<T>,RepT> op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<bool,N,NAME<N,RepT,scalar_expression<T> > > \
OP(const expression<T,N,RepT> &lhs, const T &rhs) \
{ \
  typedef NAME<N,RepT,scalar_expression<T> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t N> \
inline expression<bool,N,NAME<N,cvalarray<T,N>,T[N]> > \
OP(const cvalarray<T,N> &lhs, const T (&rhs)[N]) \
{ \
  typedef NAME<N,cvalarray<T,N>,T[N]> op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N> \
inline expression<bool,N,NAME<N,T[N],cvalarray<T,N> > > \
OP(const T (&lhs)[N], const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<N,T[N],cvalarray<T,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<bool,N,NAME<N,T[N],RepT> > \
OP(const T (&lhs)[N], const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<N,T[N],RepT> op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<bool,N,NAME<N,RepT,T[N]> > \
OP(const expression<T,N,RepT> &lhs, const T (&rhs)[N]) \
{ \
  typedef NAME<N,RepT,T[N]> op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, std::size_t OtherM, \
  std::size_t StartN, std::size_t StartM, std::size_t StrideN, std::size_t StrideM> \
inline expression<bool,N,NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>, \
  cslice_array<T,OtherM,StartM,N,StrideM> > > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, const cslice_array<T,OtherM,StartM,N,StrideM> &rhs) \
{ \
  typedef NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>, \
    cslice_array<T,OtherM,StartM,N,StrideM> > op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>, \
  scalar_expression<T> > > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, const T &rhs) \
{ \
  typedef scalar_expression<T> scalar_t; \
  typedef NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>, \
    scalar_t> op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,scalar_t(rhs))); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,scalar_expression<T>, \
  cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const T &lhs, const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<N,scalar_expression<T>, \
    cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,cvalarray<T,N>, \
  cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const cvalarray<T,N> &lhs, \
  const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<N,cvalarray<T,N>,cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>, \
   cvalarray<T,N> > > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, \
  const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>, \
    cvalarray<T,N> > op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,RepT,cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const expression<T,N,RepT> &lhs, const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<N,RepT,cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t N, typename RepT, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>,RepT> > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>,RepT> op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,T[N],cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const T (&lhs)[N], const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<N,T[N],cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>,T[N]> > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, const T (&rhs)[N]) \
{ \
  typedef NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>,T[N]> op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t O, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>, \
  cindirect_array<T,O,N> > >\
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &lhs, \
  const cindirect_array<T,O,N> &rhs) \
{ \
  typedef NAME<N,cslice_array<T,OtherN,StartN,N,StrideN>, \
    cindirect_array<T,O,N> > op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t O, std::size_t N> \
inline expression<bool,N,NAME<N,cindirect_array<T,M,N>,cindirect_array<T,O,N> > > \
OP(const cindirect_array<T,M,N> &lhs, const cindirect_array<T,O,N> &rhs) \
{ \
  typedef NAME<N,cindirect_array<T,M,N>,cindirect_array<T,O,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<bool,N,NAME<N,cindirect_array<T,M,N>,scalar_expression<T> > > \
OP(const cindirect_array<T,M,N> &lhs, const T &rhs) \
{ \
  typedef NAME<N,cindirect_array<T,M,N>,scalar_expression<T> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<bool,N,NAME<N,scalar_expression<T>,cindirect_array<T,M,N> > > \
OP(const T &lhs, const cindirect_array<T,M,N> &rhs) \
{ \
  typedef NAME<N,scalar_expression<T>,cindirect_array<T,M,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<bool,N,NAME<N,cvalarray<T,N>,cindirect_array<T,M,N> > > \
OP(const cvalarray<T,N> &lhs, const cindirect_array<T,M,N> &rhs) \
{ \
  typedef NAME<N,cvalarray<T,N>,cindirect_array<T,M,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<bool,N,NAME<N,cindirect_array<T,M,N>,cvalarray<T,N> > > \
OP(const cindirect_array<T,M,N> &lhs, const cvalarray<T,N> &rhs) \
{ \
  typedef NAME<N,cindirect_array<T,M,N>,cvalarray<T,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N, typename RepT> \
inline expression<bool,N,NAME<N,RepT,cindirect_array<T,M,N> > > \
OP(const expression<T,N,RepT> &lhs, const cindirect_array<T,M,N> &rhs) \
{ \
  typedef NAME<N,RepT,cindirect_array<T,M,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs.rep,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N, typename RepT> \
inline expression<bool,N,NAME<N,cindirect_array<T,M,N>,RepT> > \
OP(const cindirect_array<T,M,N> &lhs, const expression<T,N,RepT> &rhs) \
{ \
  typedef NAME<N,cindirect_array<T,M,N>,RepT> op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs.rep)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<bool,N,NAME<N,T[N],cindirect_array<T,M,N> > > \
OP(const T (&lhs)[N], const cindirect_array<T,M,N> &rhs) \
{ \
  typedef NAME<N,T[N],cindirect_array<T,M,N> > op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t M, std::size_t N> \
inline expression<bool,N,NAME<N,cindirect_array<T,M,N>,T[N]> > \
OP(const cindirect_array<T,M,N> &lhs, const T (&rhs)[N]) \
{ \
  typedef NAME<N,cindirect_array<T,M,N>,T[N]> op_type; \
\
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
} \
\
template<typename T, std::size_t N, std::size_t O, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<bool,N,NAME<N,cindirect_array<T,O,N>, \
  cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const cindirect_array<T,O,N> &lhs, \
  const cslice_array<T,OtherN,StartN,N,StrideN> &rhs) \
{ \
  typedef NAME<N,cindirect_array<T,O,N>, \
    cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
  \
  return expression<bool,N,op_type>(op_type(lhs,rhs)); \
}

/*
  Each has:
  
  expression<OP> OP (const cvalarray &rhs);
  expression<OP> OP (const expression<> &rhs);
  
  Below reflects issue 93 from c++ working group
  operator expression<OP> OP (const slice_array &rhs);
  operator expression<OP> OP (const cindirect_array &rhs);
*/

#define MAKE_NONMEMBER_UNARYOP(NAME,OP) \
template<typename T, std::size_t N> \
inline expression<T,N,NAME<T,N,cvalarray<T,N> > > \
OP(const cvalarray<T,N> &val) \
{ \
  typedef NAME<T,N,cvalarray<T,N> > op_type; \
\
  return expression<T,N,op_type>(op_type(val)); \
} \
\
template<typename T, std::size_t N, typename RepT> \
inline expression<T,N,NAME<T,N,RepT> > \
OP(const expression<T,N,RepT> &val) \
{ \
  typedef NAME<T,N,RepT> op_type; \
\
  return expression<T,N,op_type>(op_type(val.rep)); \
} \
\
template<typename T, std::size_t N, std::size_t OtherN, \
  std::size_t StartN, std::size_t StrideN> \
inline expression<T,N,NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN> > > \
OP(const cslice_array<T,OtherN,StartN,N,StrideN> &val) \
{ \
  typedef NAME<T,N,cslice_array<T,OtherN,StartN,N,StrideN> > op_type; \
\
  return expression<T,N,op_type>(op_type(val)); \
} \
\
template<typename T, std::size_t N, std::size_t M> \
inline expression<T,N,NAME<T,N,cindirect_array<T,N,M> > > \
OP(const cindirect_array<T,N,M> &val) \
{ \
  typedef NAME<T,N,cindirect_array<T,N,M> > op_type; \
\
  return expression<T,N,op_type>(op_type(val)); \
}

MAKE_NONMEMBER_EXPR_UNARYOP(__positive,operator+)
MAKE_NONMEMBER_EXPR_UNARYOP(__negative,operator-)
MAKE_NONMEMBER_EXPR_UNARYOP(__compl,operator~)
MAKE_NONMEMBER_EXPR_UNARYOP(__not,operator!)

MAKE_NONMEMBER_BINOP(__multiply,operator*)
MAKE_NONMEMBER_BINOP(__divides,operator/)
MAKE_NONMEMBER_BINOP(__modulus,operator%)
MAKE_NONMEMBER_BINOP(__plus,operator+)
MAKE_NONMEMBER_BINOP(__minus,operator-)
MAKE_NONMEMBER_BINOP(__bitwise_xor,operator^)
MAKE_NONMEMBER_BINOP(__bitwise_and,operator&)
MAKE_NONMEMBER_BINOP(__bitwise_or,operator|)
MAKE_NONMEMBER_BINOP(__left_shift,operator<<)
MAKE_NONMEMBER_BINOP(__right_shift,operator>>)

MAKE_NONMEMBER_LOGIC_BINOP(__equals,operator==)
MAKE_NONMEMBER_LOGIC_BINOP(__not_equals,operator!=)
MAKE_NONMEMBER_LOGIC_BINOP(__less_than,operator<)
MAKE_NONMEMBER_LOGIC_BINOP(__greater_than,operator>)
MAKE_NONMEMBER_LOGIC_BINOP(__less_than_equal,operator<=)
MAKE_NONMEMBER_LOGIC_BINOP(__greater_than_equal,operator>=)
MAKE_NONMEMBER_LOGIC_BINOP(__and,operator&&)
MAKE_NONMEMBER_LOGIC_BINOP(__or,operator||)

MAKE_NONMEMBER_BINOP(__atan2,atan2)
MAKE_NONMEMBER_BINOP(__pow,pow)

MAKE_NONMEMBER_UNARYOP(__abs,abs)
MAKE_NONMEMBER_UNARYOP(__acos,acos)
MAKE_NONMEMBER_UNARYOP(__asin,asin)
MAKE_NONMEMBER_UNARYOP(__atan,atan)
MAKE_NONMEMBER_UNARYOP(__cos,cos)
MAKE_NONMEMBER_UNARYOP(__cosh,cosh)
MAKE_NONMEMBER_UNARYOP(__exp,exp)
MAKE_NONMEMBER_UNARYOP(__log,log)
MAKE_NONMEMBER_UNARYOP(__log10,log10)
MAKE_NONMEMBER_UNARYOP(__sin,sin)
MAKE_NONMEMBER_UNARYOP(__sinh,sinh)
MAKE_NONMEMBER_UNARYOP(__sqrt,sqrt)
MAKE_NONMEMBER_UNARYOP(__tan,tan)
MAKE_NONMEMBER_UNARYOP(__tanh,tanh)

}

#endif
