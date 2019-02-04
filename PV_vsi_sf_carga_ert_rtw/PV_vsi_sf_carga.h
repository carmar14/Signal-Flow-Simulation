/*
 * File: PV_vsi_sf_carga.h
 *
 * Code generated for Simulink model 'PV_vsi_sf_carga'.
 *
 * Model version                  : 1.70
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Sep 17 16:17:21 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PV_vsi_sf_carga_h_
#define RTW_HEADER_PV_vsi_sf_carga_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef PV_vsi_sf_carga_COMMON_INCLUDES_
# define PV_vsi_sf_carga_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* PV_vsi_sf_carga_COMMON_INCLUDES_ */

#include "PV_vsi_sf_carga_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

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
  real_T TransferFcn3;                 /* '<Root>/Transfer Fcn3' */
  real_T Memory;                       /* '<S9>/Memory' */
  real_T Switch;                       /* '<S9>/Switch' */
  real_T Memory_f;                     /* '<S8>/Memory' */
  real_T Switch_c;                     /* '<S8>/Switch' */
  real_T Memory_j;                     /* '<S13>/Memory' */
  real_T Switch_k;                     /* '<S13>/Switch' */
  real_T Memory_m;                     /* '<S12>/Memory' */
  real_T Switch_o;                     /* '<S12>/Switch' */
  real_T refvoltage;                   /* '<Root>/Sine Wave' */
  real_T Sum3;                         /* '<Root>/Sum3' */
  real_T Product;                      /* '<S4>/Product' */
  real_T Product1;                     /* '<S4>/Product1' */
  real_T Sum6;                         /* '<Root>/Sum6' */
  real_T Product_c;                    /* '<S5>/Product' */
  real_T Product1_g;                   /* '<S5>/Product1' */
  real_T Sum4;                         /* '<Root>/Sum4' */
  real_T Sum7;                         /* '<Root>/Sum7' */
} B_PV_vsi_sf_carga_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T TimeStampA;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative1' */
  real_T TimeStampB;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative1' */
  real_T Memory_PreviousInput;         /* '<S9>/Memory' */
  real_T Memory_PreviousInput_j;       /* '<S8>/Memory' */
  real_T Memory_PreviousInput_i;       /* '<S13>/Memory' */
  real_T Memory_PreviousInput_n;       /* '<S12>/Memory' */
  real_T TimeStampA_e;                 /* '<Root>/Derivative' */
  real_T LastUAtTimeA_n;               /* '<Root>/Derivative' */
  real_T TimeStampB_a;                 /* '<Root>/Derivative' */
  real_T LastUAtTimeB_c;               /* '<Root>/Derivative' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK;              /* '<S9>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_g;            /* '<S8>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_j;            /* '<S13>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } TransportDelay_RWORK_g1;           /* '<S12>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S9>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_g;            /* '<S8>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_f;            /* '<S13>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK_n;            /* '<S12>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S9>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_n;            /* '<S8>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_ng;           /* '<S13>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK_d;            /* '<S12>/Transport Delay' */
} DW_PV_vsi_sf_carga_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T VSIlineZ_CSTATE;              /* '<Root>/VSI  line Z' */
  real_T TransferFcn3_CSTATE[2];       /* '<Root>/Transfer Fcn3' */
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T integrator_CSTATE;            /* '<S9>/integrator' */
  real_T integrator_CSTATE_c;          /* '<S8>/integrator' */
  real_T integrator_CSTATE_i;          /* '<S13>/integrator' */
  real_T integrator_CSTATE_b;          /* '<S12>/integrator' */
  real_T TransferFcn2_CSTATE[2];       /* '<S1>/Transfer Fcn2' */
} X_PV_vsi_sf_carga_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T VSIlineZ_CSTATE;              /* '<Root>/VSI  line Z' */
  real_T TransferFcn3_CSTATE[2];       /* '<Root>/Transfer Fcn3' */
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T integrator_CSTATE;            /* '<S9>/integrator' */
  real_T integrator_CSTATE_c;          /* '<S8>/integrator' */
  real_T integrator_CSTATE_i;          /* '<S13>/integrator' */
  real_T integrator_CSTATE_b;          /* '<S12>/integrator' */
  real_T TransferFcn2_CSTATE[2];       /* '<S1>/Transfer Fcn2' */
} XDot_PV_vsi_sf_carga_T;

/* State disabled  */
typedef struct {
  boolean_T VSIlineZ_CSTATE;           /* '<Root>/VSI  line Z' */
  boolean_T TransferFcn3_CSTATE[2];    /* '<Root>/Transfer Fcn3' */
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T integrator_CSTATE;         /* '<S9>/integrator' */
  boolean_T integrator_CSTATE_c;       /* '<S8>/integrator' */
  boolean_T integrator_CSTATE_i;       /* '<S13>/integrator' */
  boolean_T integrator_CSTATE_b;       /* '<S12>/integrator' */
  boolean_T TransferFcn2_CSTATE[2];    /* '<S1>/Transfer Fcn2' */
} XDis_PV_vsi_sf_carga_T;

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
  /* Expression: [0 10 200 500 800 1000 1140 1150 1200]
   * Referenced by: '<Root>/1-D Lookup Table2'
   */
  real_T uDLookupTable2_tableData[9];

  /* Expression: [0 10 20 30 40 50 70 80 100]
   * Referenced by: '<Root>/1-D Lookup Table2'
   */
  real_T uDLookupTable2_bp01Data[9];
} ConstP_PV_vsi_sf_carga_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Vload;                        /* '<Root>/Vload' */
  real_T Ipv;                          /* '<Root>/Ipv' */
  real_T i1;                           /* '<Root>/i1' */
  real_T i2;                           /* '<Root>/i2' */
} ExtU_PV_vsi_sf_carga_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T i3;                           /* '<Root>/i3' */
  real_T SOC;                          /* '<Root>/SOC' */
  real_T Pm;                           /* '<Root>/Pm' */
  real_T Qm;                           /* '<Root>/Qm' */
  real_T Vload1;                       /* '<Root>/Vload1' */
} ExtY_PV_vsi_sf_carga_T;

/* Real-time Model Data Structure */
struct tag_RTM_PV_vsi_sf_carga_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_PV_vsi_sf_carga_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeY[10];
  real_T odeF[4][10];
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
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (auto storage) */
extern B_PV_vsi_sf_carga_T PV_vsi_sf_carga_B;

/* Continuous states (auto storage) */
extern X_PV_vsi_sf_carga_T PV_vsi_sf_carga_X;

/* Block states (auto storage) */
extern DW_PV_vsi_sf_carga_T PV_vsi_sf_carga_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_PV_vsi_sf_carga_T PV_vsi_sf_carga_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_PV_vsi_sf_carga_T PV_vsi_sf_carga_Y;

/* Constant parameters (auto storage) */
extern const ConstP_PV_vsi_sf_carga_T PV_vsi_sf_carga_ConstP;

/* Model entry point functions */
extern void PV_vsi_sf_carga_initialize(void);
extern void PV_vsi_sf_carga_step(void);
extern void PV_vsi_sf_carga_terminate(void);

/* Real-time Model object */
extern RT_MODEL_PV_vsi_sf_carga_T *const PV_vsi_sf_carga_M;

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
 * '<Root>' : 'PV_vsi_sf_carga'
 * '<S1>'   : 'PV_vsi_sf_carga/Control PR VSI'
 * '<S2>'   : 'PV_vsi_sf_carga/MATLAB Function SOC '
 * '<S3>'   : 'PV_vsi_sf_carga/Power'
 * '<S4>'   : 'PV_vsi_sf_carga/Power/Fourier'
 * '<S5>'   : 'PV_vsi_sf_carga/Power/Fourier1'
 * '<S6>'   : 'PV_vsi_sf_carga/Power/Fourier/Mean'
 * '<S7>'   : 'PV_vsi_sf_carga/Power/Fourier/Mean value1'
 * '<S8>'   : 'PV_vsi_sf_carga/Power/Fourier/Mean/Model'
 * '<S9>'   : 'PV_vsi_sf_carga/Power/Fourier/Mean value1/Model'
 * '<S10>'  : 'PV_vsi_sf_carga/Power/Fourier1/Mean'
 * '<S11>'  : 'PV_vsi_sf_carga/Power/Fourier1/Mean value1'
 * '<S12>'  : 'PV_vsi_sf_carga/Power/Fourier1/Mean/Model'
 * '<S13>'  : 'PV_vsi_sf_carga/Power/Fourier1/Mean value1/Model'
 */
#endif                                 /* RTW_HEADER_PV_vsi_sf_carga_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
