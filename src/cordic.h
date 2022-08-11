#include "ap_fixed.h"
#define NUM_ITERATIONS 20	//NUM_ITERATIONS <= 20
#define M 6

typedef ap_fixed<17,2> COS_SIN_TYPE;
typedef ap_fixed<24,9> THETA_TYPE;
typedef ap_uint<1> bit;
typedef ap_uint<8> COUNTER_TYPE;

void cordic(THETA_TYPE theta, COS_SIN_TYPE* s, COS_SIN_TYPE* c);
void cordic_wrap(THETA_TYPE theta_in[M], COUNTER_TYPE len, COS_SIN_TYPE result_s[M], COS_SIN_TYPE result_c[M]);
