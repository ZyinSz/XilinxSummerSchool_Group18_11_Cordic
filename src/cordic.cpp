// The file cordic.h holds definitions for the data types and constant values
#include "cordic.h"

// The cordic phase array holds the angle for the current rotation
THETA_TYPE cordic_phase[20] = {
    45.0000, 26.5651, 14.0362,  7.1250,  3.5763,
	 1.7899,  0.8952,  0.4476,  0.2238,  0.1119,
	 0.0560,  0.0280,  0.0140,  0.0070,  0.0035,
	 0.0017,  0.0009,  0.0004,  0.0002,  0.0001
};

void cordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c)
{
#pragma HLS ARRAY_PARTITION variable=cordic_phase complete dim=0

    // Set the initial vector that we will rotate
    // current_cos = I; current_sin = Q
    COS_SIN_TYPE current_cos = 0.6073;
    COS_SIN_TYPE current_sin = 0;
    COS_SIN_TYPE cos_shift = 0;
    COS_SIN_TYPE sin_shift = 0;
    COUNTER_TYPE j = 0;
	bit reverse = 0;

	if(theta <= 90 && theta >= -90)
	{
		theta = theta;
		reverse = 0;
	}
	else if(theta > 90 && theta <= 180)
	{
		theta = theta - 180;
		reverse = 1;
	}
	else if(theta < -90 && theta >= -180)
	{
		theta = theta + 180;
		reverse = 1;
	}
	else
	{
		theta = 0;
		reverse = 0;
	}

    // This loop iteratively rotates the initial vector to find the
    // sine and cosine values corresponding to the input theta angle
    for(j=0; j<NUM_ITERATIONS; j++)
    {
#pragma HLS PIPELINE II=1
        // Multiply previous iteration by 2^(-j). This is equivalent to
        // a right shift by j on a fixed-point number.
    	cos_shift = current_cos >> j;
    	sin_shift = current_sin >> j;
        
        // Determine if we are rotating by a positive or negative angle 
        if(theta >= 0)
        {
            // Perform the rotation 
            current_cos = current_cos - sin_shift;
            current_sin = current_sin + cos_shift;
            
            // Determine the new theta angle
            theta = theta - cordic_phase[j];
        }
        else
        {
            // Perform the rotation 
        	current_cos = current_cos + sin_shift;
        	current_sin = current_sin - cos_shift;
            
            // Determine the new theta angle
        	theta = theta + cordic_phase[j];
        }
    }

    // Set the final sine and cosine values
    if(reverse == 0)
    {
    	s = current_sin;
        c = current_cos;
    }
    else
    {
    	s = -current_sin;
        c = -current_cos;
    }
}

void cordic_wrap(THETA_TYPE theta_in[M], COUNTER_TYPE len, COS_SIN_TYPE result_s[M], COS_SIN_TYPE result_c[M])
{
#pragma HLS INTERFACE m_axi port=theta_in offset=slave depth=6
#pragma HLS INTERFACE m_axi port=result_s offset=slave depth=6
#pragma HLS INTERFACE m_axi port=result_c offset=slave depth=6
#pragma HLS INTERFACE s_axilite port=len  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

	COUNTER_TYPE i=0;

	for(i=0;i<len;i++)
	{
#pragma HLS PIPELINE II=1
		cordic(theta_in[i], result_s[i], result_c[i]);
	}
}
