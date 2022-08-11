#include "cordic.h"
#include <iostream>
#define N 6
using namespace std;

 int main ()
 {
     cout << "-------------------------------" << endl;
     cout << "Test started." << endl;

     THETA_TYPE theta[N] = {
    		 90, 80, 70, 60, 50, 40
     };

     COS_SIN_TYPE standard_s[N] = {
    		 1.0000, 0.9848, 0.9397, 0.8660, 0.7660, 0.6428
     };
     COS_SIN_TYPE standard_c[N] = {
    		 0.0000, 0.1736, 0.3420, 0.5000, 0.6428, 0.7660
     };


     COS_SIN_TYPE result_s[N];
     COS_SIN_TYPE result_c[N];
     COUNTER_TYPE i = 0;

     cordic_wrap(theta, N, result_s, result_c);

     for(i = 0; i < N; i++)
     {
    	 if ((result_s[i] - standard_s[i]) > 0.001
    			 || (standard_s[i] - result_s[i]) > 0.001
				 || (result_c[i] - standard_c[i]) > 0.001
				 || (standard_c[i] - result_c[i]) > 0.001)
      	 {
        	 cout << theta[i] << endl;
        	 cout << result_s[i] << endl;
        	 cout << result_c[i] << endl;
    		 cout << "Test failed." << endl;
    		 return -1;
    	 }
     }

     cout << "Test passed." << endl;
     cout << "Test finished." << endl;
     cout << "-------------------------------" << endl;

     return 0;
 }

