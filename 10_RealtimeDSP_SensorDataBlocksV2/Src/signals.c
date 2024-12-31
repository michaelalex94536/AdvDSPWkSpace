#ifndef __SIGNALS_H__
#define __SIGNALS_H__
#include "arm_math.h"

#include "signals.h"


/*Low pass filter : Fpass 1hz Fstop 3hz Fs 100hz Order 31*/
 float LP_1HZ_2HZ_IMPULSE_RESPONSE[IMP_RSP_LENGTH]={
0.014279,0.016942,0.01968,0.022452,0.025216,0.02793,0.03055,0.033033,0.035336,
0.037422,0.039253,0.040797,0.042028,0.042923,0.043467,0.043649,0.043467,0.042923,
0.042028,0.040797,0.039253,0.037422,0.035336,0.033033,0.03055,0.02793,0.025216,
0.022452,0.01968,0.016942,0.014279
};



float _5hz_signal[HZ_5_SIG_LEN]=
{
	0,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,1.2246e-16,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-2.4493e-16,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,3.6739e-16,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-4.8986e-16,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,6.1232e-16,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-7.3479e-16,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,-2.6955e-15,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-9.7972e-16,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,1.1022e-15,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-1.2246e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,-2.2056e-15,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-1.4696e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,-1.9607e-15,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,5.3909e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,5.3897e-15,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-9.0649e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,5.6346e-15,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-2.2044e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,5.8795e-15,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-2.4493e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,-9.8096e-16,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,4.4112e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,6.3694e-15,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-2.9392e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,-4.911e-16,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,3.9213e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,-7.3516e-15,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-3.429e-15,0.30902,0.58779,0.80902,0.95106,1,0.95106,0.80902,0.58779,0.30902,-1.238e-18,-0.30902,-0.58779,-0.80902,-0.95106,-1,-0.95106,-0.80902,-0.58779,-0.30902,-1.0779e-14

};



float32_t input_signal_f32_1kHz_15kHz[KHZ1_15_SIG_LEN] =
{
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
-0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
-0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
-0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
-0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f,
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f,
-0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f,
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f,
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f,
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f,
};
#endif
