#include <stdio.h>
#include <iostream>

#include <arm_neon.h>

uint32_t vector_add_of_n(uint32_t *ptr, uint32_t items) {
  uint32x4_t vec128 = vdupq_n_u32(0);
  for(uint32_t *i=ptr; i<(ptr+items); i+=4) {
    uint32x4_t temp128 = vld1q_u32(i);

    uint32_t A[4];
    vst1q_u32(A, temp128);
    std::cout << "vec128 (" << i << "): " << A[3] << ", " << A[2] << ", " << A[1] << ", " << A[0] << std::endl; 

    vec128 = vaddq_u32(vec128, temp128);
  }

  uint32x2_t vec64a = vget_low_u32(vec128);
  uint32x2_t vec64b = vget_high_u32(vec128);
  vec64a = vadd_u32(vec64a, vec64b);

  uint32_t result = vget_lane_u32(vec64a, 0);
  result += vget_lane_u32(vec64a, 1);

  return result;
}

float *matrix_mul_4x4(float *ma, float *mb) {
  
  if(ma==nullptr || mb==nullptr)
    return nullptr;

  float32x4_t vec128_mc_r0 = vdupq_n_f32(0.f);
  float32x4_t vec128_mc_r1 = vdupq_n_f32(0.f);
  float32x4_t vec128_mc_r2 = vdupq_n_f32(0.f);
  float32x4_t vec128_mc_r3 = vdupq_n_f32(0.f);

  for(uint8_t i=0; i<4; ++i) {
    float32x4_t vec128_mb = vld1q_f32(mb+4*i);
    vec128_mc_r0 = vfmaq_f32(vec128_mc_r0, vdupq_n_f32(*(ma+0 +i)), vec128_mb);
    vec128_mc_r1 = vfmaq_f32(vec128_mc_r1, vdupq_n_f32(*(ma+4 +i)), vec128_mb);
    vec128_mc_r2 = vfmaq_f32(vec128_mc_r2, vdupq_n_f32(*(ma+8 +i)), vec128_mb);
    vec128_mc_r3 = vfmaq_f32(vec128_mc_r3, vdupq_n_f32(*(ma+12+i)), vec128_mb);
  }

  float *mc = new float[16];
  vst1q_f32(mc+0,  vec128_mc_r0); 
  vst1q_f32(mc+4,  vec128_mc_r1); 
  vst1q_f32(mc+8,  vec128_mc_r2); 
  vst1q_f32(mc+12, vec128_mc_r3); 

  return mc;
}

int main()
{
  std::cout << "neon test" << std::endl;

  unsigned short int A[] = {1, 2, 3, 4};
  uint16x4_t v16;
  v16 = vld1_u16(A);
  v16 = vadd_u16(v16, v16);


  unsigned char B[8];
  uint8x8_t v8;
  v8 = vcreate_u8(0x0102030405060708);
  vst1_u8(B, v8);

  std::cout << "B[2]: " << (int)B[2] << std::endl;


  unsigned char C[24];
  for(int i=0; i<8; ++i) {
    C[i*3+0] = i+1;
    C[i*3+1] = i+1;
    C[i*3+2] = i+1;
  }
  std::cout << "origin C:" << std::endl;
  for(int h=0; h<3; ++h) {
    for(int w=0; w<8; ++w)
      std::cout << (int)C[h+w*3] << ", ";
    std::cout << std::endl;
  }

  uint8x8x3_t v8_3;
  v8_3 = vld3_u8(C);
  v8_3.val[0] = vadd_u8(v8_3.val[0], v8_3.val[0]);
  vst3_u8(C, v8_3);

  std::cout << "after C:" << std::endl;
  for(int h=0; h<3; ++h) {
    for(int w=0; w<8; ++w)
      std::cout << (int)C[h+w*3] << ", ";
    std::cout << std::endl;
  }


  uint32_t D[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  uint32_t sum_D = vector_add_of_n(D, 8);
  std::cout << "D sum: " << sum_D << std::endl;

  
  float *ma = new float[16];
  float *mb = new float[16];
  for(int i=0; i<4; ++i) {
    for(int j=0; j<4; ++j) {
      ma[i*4+j] = j+1; 
    }
  }
  for(int i=0; i<4; ++i) {
    for(int j=0; j<4; ++j) {
      mb[i*4+j] = i+1; 
    }
  }
  std::cout << "ma : " << std::endl;
  for(int i=0; i<4; ++i) {
    for(int j=0; j<4; ++j) {
      std::cout << ma[i*4+j] << ", "; 
    }
    std::cout << std::endl;
  }
  std::cout << "mb : " << std::endl;
  for(int i=0; i<4; ++i) {
    for(int j=0; j<4; ++j) {
      std::cout << mb[i*4+j] << ", "; 
    }
    std::cout << std::endl;
  }
  float *mc = matrix_mul_4x4(ma, mb);
  std::cout << "mc = ma * mb : " << std::endl;
  for(int i=0; i<4; ++i) {
    for(int j=0; j<4; ++j) {
      std::cout << mc[i*4+j] << ", "; 
    }
    std::cout << std::endl;
  }
    
  return 0;
}

