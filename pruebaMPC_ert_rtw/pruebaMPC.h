/*
 * File: pruebaMPC.h
 *
 * Code generated for Simulink model 'pruebaMPC'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Thu Sep 13 11:19:58 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_pruebaMPC_h_
#define RTW_HEADER_pruebaMPC_h_
#include <string.h>
#ifndef pruebaMPC_COMMON_INCLUDES_
# define pruebaMPC_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* pruebaMPC_COMMON_INCLUDES_ */

#include "pruebaMPC_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T dv0[40000];
  real_T dv1[20200];
  real_T xk1[14];                      /* '<S2>/optimizer' */
  real_T u[2];                         /* '<S2>/optimizer' */
  boolean_T iAout;                     /* '<S2>/optimizer' */
} B_pruebaMPC_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T last_mv_DSTATE[2];            /* '<S2>/last_mv' */
  real_T last_x_PreviousInput[14];     /* '<S2>/last_x' */
  boolean_T Memory_PreviousInput;      /* '<S2>/Memory' */
} DW_pruebaMPC_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T StateSpace_CSTATE[12];        /* '<Root>/State-Space' */
} X_pruebaMPC_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T StateSpace_CSTATE[12];        /* '<Root>/State-Space' */
} XDot_pruebaMPC_T;

/* State disabled  */
typedef struct {
  boolean_T StateSpace_CSTATE[12];     /* '<Root>/State-Space' */
} XDis_pruebaMPC_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Computed Parameter: StateSpace_A
   * Referenced by: '<Root>/State-Space'
   */
  real_T StateSpace_A[20];

  /* Computed Parameter: StateSpace_C
   * Referenced by: '<Root>/State-Space'
   */
  real_T StateSpace_C[12];
} ConstP_pruebaMPC_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T sal[2];                       /* '<Root>/sal' */
} ExtY_pruebaMPC_T;

/* Real-time Model Data Structure */
struct tag_RTM_pruebaMPC_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_pruebaMPC_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[12];
  real_T odeF[4][12];
  ODE4_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block signals (auto storage) */
extern B_pruebaMPC_T pruebaMPC_B;

/* Continuous states (auto storage) */
extern X_pruebaMPC_T pruebaMPC_X;

/* Block states (auto storage) */
extern DW_pruebaMPC_T pruebaMPC_DW;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_pruebaMPC_T pruebaMPC_Y;

/* Constant parameters (auto storage) */
extern const ConstP_pruebaMPC_T pruebaMPC_ConstP;

/* Model entry point functions */
extern void pruebaMPC_initialize(void);
extern void pruebaMPC_step(void);
extern void pruebaMPC_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pruebaMPC_T *const pruebaMPC_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S4>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S5>/Vector Dimension Check' : Unused code path elimination
 * Block '<S6>/Vector Dimension Check' : Unused code path elimination
 * Block '<S7>/Vector Dimension Check' : Unused code path elimination
 * Block '<S8>/Vector Dimension Check' : Unused code path elimination
 * Block '<S9>/Vector Dimension Check' : Unused code path elimination
 * Block '<S10>/Vector Dimension Check' : Unused code path elimination
 * Block '<S11>/Vector Dimension Check' : Unused code path elimination
 * Block '<S12>/Vector Dimension Check' : Unused code path elimination
 * Block '<S13>/Vector Dimension Check' : Unused code path elimination
 * Block '<S14>/Vector Dimension Check' : Unused code path elimination
 * Block '<S15>/Vector Dimension Check' : Unused code path elimination
 * Block '<S16>/Vector Dimension Check' : Unused code path elimination
 * Block '<S2>/constant' : Unused code path elimination
 * Block '<S2>/umin_scale2' : Unused code path elimination
 * Block '<S2>/umin_scale3' : Unused code path elimination
 * Block '<S2>/ym_zero' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<S2>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S2>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/ext.mv_scale1' : Eliminated nontunable gain of 1
 * Block '<S2>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S2>/umax_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/umin_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/umin_scale1' : Eliminated nontunable gain of 1
 * Block '<S2>/ymax_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/ymin_scale' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'pruebaMPC'
 * '<S1>'   : 'pruebaMPC/MPC Controller'
 * '<S2>'   : 'pruebaMPC/MPC Controller/MPC'
 * '<S3>'   : 'pruebaMPC/MPC Controller/MPC/MPC Preview Signal Check'
 * '<S4>'   : 'pruebaMPC/MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S5>'   : 'pruebaMPC/MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S6>'   : 'pruebaMPC/MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S7>'   : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check'
 * '<S8>'   : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check11'
 * '<S9>'   : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check2'
 * '<S10>'  : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check3'
 * '<S11>'  : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check4'
 * '<S12>'  : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check5'
 * '<S13>'  : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S14>'  : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check7'
 * '<S15>'  : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check8'
 * '<S16>'  : 'pruebaMPC/MPC Controller/MPC/MPC Vector Signal Check9'
 * '<S17>'  : 'pruebaMPC/MPC Controller/MPC/optimizer'
 */
#endif                                 /* RTW_HEADER_pruebaMPC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
