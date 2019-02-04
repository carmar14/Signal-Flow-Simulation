/*
 * File: mpc_doubleint_private.h
 *
 * Code generated for Simulink model 'mpc_doubleint'.
 *
 * Model version                  : 1.56
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Sep 11 09:07:00 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_mpc_doubleint_private_h_
#define RTW_HEADER_mpc_doubleint_private_h_
#include "rtwtypes.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

extern real_T rt_hypotd_snf(real_T u0, real_T u1);

/* private model entry point functions */
extern void mpc_doubleint_derivatives(void);

#endif                                 /* RTW_HEADER_mpc_doubleint_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
