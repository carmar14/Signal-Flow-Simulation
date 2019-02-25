/*
 * File: MPC.h
 *
 * Code generated for Simulink model 'MPC'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Fri Feb 02 10:54:17 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MPC_h_
#define RTW_HEADER_MPC_h_
#include <math.h>
#include <string.h>
#ifndef MPC_COMMON_INCLUDES_
# define MPC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* MPC_COMMON_INCLUDES_ */

#include "MPC_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T last_mv_DSTATE[2];            /* '<S7>/last_mv' */
  real_T last_x_PreviousInput[6];      /* '<S7>/last_x' */
  boolean_T Memory_PreviousInput[6];   /* '<S7>/Memory' */
} DW_MPC_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Corriente1;                   /* '<Root>/Corriente 1' */
  real_T Corriente2;                   /* '<Root>/Corriente 2' */
} ExtU_MPC_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T u1;                           /* '<Root>/u1' */
  real_T u2;                           /* '<Root>/u2' */
} ExtY_MPC_T;

/* Real-time Model Data Structure */
struct tag_RTM_MPC_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block states (auto storage) */
extern DW_MPC_T MPC_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_MPC_T MPC_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_MPC_T MPC_Y;

/* Model entry point functions */
extern void MPC_initialize(void);
//extern void MPC_step(void);
extern void step(double corriente1, double corriente2, double ref1, double ref2);
extern void guardoU(double u1);
extern void guardoU2(double u2);
extern double getU();
extern double getU2(); 
extern void MPC_terminate(void);

/* Real-time Model object */
extern RT_MODEL_MPC_T *const MPC_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S8>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S9>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S10>/Vector Dimension Check' : Unused code path elimination
 * Block '<S11>/Vector Dimension Check' : Unused code path elimination
 * Block '<S12>/Vector Dimension Check' : Unused code path elimination
 * Block '<S13>/Vector Dimension Check' : Unused code path elimination
 * Block '<S14>/Vector Dimension Check' : Unused code path elimination
 * Block '<S15>/Vector Dimension Check' : Unused code path elimination
 * Block '<S16>/Vector Dimension Check' : Unused code path elimination
 * Block '<S17>/Vector Dimension Check' : Unused code path elimination
 * Block '<S18>/Vector Dimension Check' : Unused code path elimination
 * Block '<S19>/Vector Dimension Check' : Unused code path elimination
 * Block '<S20>/Vector Dimension Check' : Unused code path elimination
 * Block '<S21>/Vector Dimension Check' : Unused code path elimination
 * Block '<S7>/constant' : Unused code path elimination
 * Block '<S7>/umin_scale2' : Unused code path elimination
 * Block '<S7>/umin_scale3' : Unused code path elimination
 * Block '<S7>/ym_zero' : Unused code path elimination
 * Block '<S7>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S7>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S7>/ext.mv_scale1' : Eliminated nontunable gain of 1
 * Block '<S7>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S7>/umax_scale' : Eliminated nontunable gain of 1
 * Block '<S7>/umin_scale' : Eliminated nontunable gain of 1
 * Block '<S7>/umin_scale1' : Eliminated nontunable gain of 1
 * Block '<S7>/ymax_scale' : Eliminated nontunable gain of 1
 * Block '<S7>/ymin_scale' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MPC'
 * '<S1>'   : 'MPC/Controlled Current Source'
 * '<S2>'   : 'MPC/Controlled Current Source1'
 * '<S3>'   : 'MPC/Linear Transformer'
 * '<S4>'   : 'MPC/MPC Controller'
 * '<S5>'   : 'MPC/powergui1'
 * '<S6>'   : 'MPC/Linear Transformer/Model'
 * '<S7>'   : 'MPC/MPC Controller/MPC'
 * '<S8>'   : 'MPC/MPC Controller/MPC/MPC Preview Signal Check'
 * '<S9>'   : 'MPC/MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S10>'  : 'MPC/MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S11>'  : 'MPC/MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S12>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check'
 * '<S13>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check11'
 * '<S14>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check2'
 * '<S15>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check3'
 * '<S16>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check4'
 * '<S17>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check5'
 * '<S18>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S19>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check7'
 * '<S20>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check8'
 * '<S21>'  : 'MPC/MPC Controller/MPC/MPC Vector Signal Check9'
 * '<S22>'  : 'MPC/MPC Controller/MPC/optimizer'
 * '<S23>'  : 'MPC/powergui1/EquivalentModel1'
 * '<S24>'  : 'MPC/powergui1/EquivalentModel1/Sources'
 */
#endif                                 /* RTW_HEADER_MPC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
