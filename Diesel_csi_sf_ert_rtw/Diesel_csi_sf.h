/*
 * File: Diesel_csi_sf.h
 *
 * Code generated for Simulink model 'Diesel_csi_sf'.
 *
 * Model version                  : 1.70
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Fri Aug 17 17:50:01 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Diesel_csi_sf_h_
#define RTW_HEADER_Diesel_csi_sf_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef Diesel_csi_sf_COMMON_INCLUDES_
# define Diesel_csi_sf_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Diesel_csi_sf_COMMON_INCLUDES_ */

#include "Diesel_csi_sf_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

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
  real_T Delay90zI;                    /* '<S1>/Delay90(z)I' */
  real_T Delay90zV;                    /* '<S1>/Delay90(z)V' */
  real_T Sum2;                         /* '<S2>/Sum2' */
  real_T Gain7;                        /* '<Root>/Gain7' */
  real_T OutputDCVoltage;              /* '<Root>/Sum2' */
  real_T FilterCoefficient;            /* '<S4>/Filter Coefficient' */
  real_T IntegralGain;                 /* '<S4>/Integral Gain' */
  real_T Sum_h;                        /* '<S4>/Sum' */
  real_T Sum1;                         /* '<Root>/Sum1' */
  real_T xk1[14];                      /* '<S9>/optimizer' */
  real_T u[2];                         /* '<S9>/optimizer' */
  real_T p;                            /* '<S1>/PQ_singlePhase' */
  real_T q;                            /* '<S1>/PQ_singlePhase' */
  boolean_T iAout;                     /* '<S9>/optimizer' */
} B_Diesel_csi_sf_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Delay90zI_states;             /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_states;             /* '<S1>/Delay90(z)V' */
  real_T last_mv_DSTATE[2];            /* '<S9>/last_mv' */
  real_T PRz_states[2];                /* '<S1>/PR(z)' */
  real_T Delay90zI_tmp;                /* '<S1>/Delay90(z)I' */
  real_T Delay90zV_tmp;                /* '<S1>/Delay90(z)V' */
  real_T last_x_PreviousInput[14];     /* '<S9>/last_x' */
  real_T PRz_tmp;                      /* '<S1>/PR(z)' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } MotordeCombustin1_RWORK;           /* '<S2>/Motor de Combustión1' */

  struct {
    void *TUbufferPtrs[2];
  } MotordeCombustin1_PWORK;           /* '<S2>/Motor de Combustión1' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } MotordeCombustin1_IWORK;           /* '<S2>/Motor de Combustión1' */

  boolean_T Memory_PreviousInput;      /* '<S9>/Memory' */
} DW_Diesel_csi_sf_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn1_CSTATE;          /* '<Root>/Transfer Fcn1' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw2_CSTATE[4];                /* '<S1>/Hw2' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
  real_T Actuador1_CSTATE;             /* '<S2>/Actuador1' */
  real_T Dinmicaeneleje1_CSTATE;       /* '<S2>/Dinámica en el eje1' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Filter_CSTATE;                /* '<S4>/Filter' */
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
} X_Diesel_csi_sf_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn1_CSTATE;          /* '<Root>/Transfer Fcn1' */
  real_T Hw1_CSTATE[4];                /* '<S1>/Hw1' */
  real_T Hw2_CSTATE[4];                /* '<S1>/Hw2' */
  real_T Hw6_CSTATE[4];                /* '<S1>/Hw6' */
  real_T Actuador1_CSTATE;             /* '<S2>/Actuador1' */
  real_T Dinmicaeneleje1_CSTATE;       /* '<S2>/Dinámica en el eje1' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
  real_T Filter_CSTATE;                /* '<S4>/Filter' */
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
} XDot_Diesel_csi_sf_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn1_CSTATE;       /* '<Root>/Transfer Fcn1' */
  boolean_T Hw1_CSTATE[4];             /* '<S1>/Hw1' */
  boolean_T Hw2_CSTATE[4];             /* '<S1>/Hw2' */
  boolean_T Hw6_CSTATE[4];             /* '<S1>/Hw6' */
  boolean_T Actuador1_CSTATE;          /* '<S2>/Actuador1' */
  boolean_T Dinmicaeneleje1_CSTATE;    /* '<S2>/Dinámica en el eje1' */
  boolean_T TransferFcn_CSTATE;        /* '<Root>/Transfer Fcn' */
  boolean_T Filter_CSTATE;             /* '<S4>/Filter' */
  boolean_T Integrator_CSTATE;         /* '<S4>/Integrator' */
} XDis_Diesel_csi_sf_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Vload;                        /* '<Root>/Vload' */
  real_T Prefd;                        /* '<Root>/Prefd' */
  real_T Qrefd;                        /* '<Root>/Qrefd' */
  real_T par;                          /* '<Root>/par' */
  real_T flujo;                        /* '<Root>/flujo' */
} ExtU_Diesel_csi_sf_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T i2;                           /* '<Root>/i2' */
} ExtY_Diesel_csi_sf_T;

/* Real-time Model Data Structure */
struct tag_RTM_Diesel_csi_sf_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_Diesel_csi_sf_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[18];
  real_T odeF[4][18];
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
      uint16_T TID[3];
    } TaskCounters;

    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block signals (auto storage) */
extern B_Diesel_csi_sf_T Diesel_csi_sf_B;

/* Continuous states (auto storage) */
extern X_Diesel_csi_sf_T Diesel_csi_sf_X;

/* Block states (auto storage) */
extern DW_Diesel_csi_sf_T Diesel_csi_sf_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_Diesel_csi_sf_T Diesel_csi_sf_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Diesel_csi_sf_T Diesel_csi_sf_Y;

/* Model entry point functions */
extern void Diesel_csi_sf_initialize(void);
extern void Diesel_csi_sf_step(void);
extern void Diesel_csi_sf_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Diesel_csi_sf_T *const Diesel_csi_sf_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S10>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S11>/Matrix Dimension Check' : Unused code path elimination
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
 * Block '<S22>/Vector Dimension Check' : Unused code path elimination
 * Block '<S23>/Vector Dimension Check' : Unused code path elimination
 * Block '<S9>/constant' : Unused code path elimination
 * Block '<S9>/umin_scale2' : Unused code path elimination
 * Block '<S9>/umin_scale3' : Unused code path elimination
 * Block '<S9>/ym_zero' : Unused code path elimination
 * Block '<S9>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S9>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S9>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S9>/ext.mv_scale1' : Eliminated nontunable gain of 1
 * Block '<S9>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S9>/umax_scale' : Eliminated nontunable gain of 1
 * Block '<S9>/umin_scale' : Eliminated nontunable gain of 1
 * Block '<S9>/umin_scale1' : Eliminated nontunable gain of 1
 * Block '<S9>/ymax_scale' : Eliminated nontunable gain of 1
 * Block '<S9>/ymin_scale' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'Diesel_csi_sf'
 * '<S1>'   : 'Diesel_csi_sf/CSI_Control_BIO1'
 * '<S2>'   : 'Diesel_csi_sf/Diesel Generator'
 * '<S3>'   : 'Diesel_csi_sf/MPC Controller1'
 * '<S4>'   : 'Diesel_csi_sf/PID Controller'
 * '<S5>'   : 'Diesel_csi_sf/CSI_Control_BIO1/PQ2Iab_PH1'
 * '<S6>'   : 'Diesel_csi_sf/CSI_Control_BIO1/PQ_singlePhase'
 * '<S7>'   : 'Diesel_csi_sf/CSI_Control_BIO1/PR Controller_0_ref 1'
 * '<S8>'   : 'Diesel_csi_sf/CSI_Control_BIO1/PR Controller_0_ref 1/Steper6'
 * '<S9>'   : 'Diesel_csi_sf/MPC Controller1/MPC'
 * '<S10>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Preview Signal Check'
 * '<S11>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Preview Signal Check1'
 * '<S12>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Scalar Signal Check'
 * '<S13>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Scalar Signal Check1'
 * '<S14>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check'
 * '<S15>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check11'
 * '<S16>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check2'
 * '<S17>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check3'
 * '<S18>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check4'
 * '<S19>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check5'
 * '<S20>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check6'
 * '<S21>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check7'
 * '<S22>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check8'
 * '<S23>'  : 'Diesel_csi_sf/MPC Controller1/MPC/MPC Vector Signal Check9'
 * '<S24>'  : 'Diesel_csi_sf/MPC Controller1/MPC/optimizer'
 */
#endif                                 /* RTW_HEADER_Diesel_csi_sf_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
