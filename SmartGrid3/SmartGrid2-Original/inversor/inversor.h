/*
 * File: inversor.h
 *
 * Code generated for Simulink model 'inversor'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jan 30 13:58:44 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_inversor_h_
#define RTW_HEADER_inversor_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef inversor_COMMON_INCLUDES_
# define inversor_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* inversor_COMMON_INCLUDES_ */

#include "inversor_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "rt_matrixlib.h"

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
  real_T StateSpace_o1[11];            /* '<S52>/State-Space' */
  real_T StateSpace_o2[8];             /* '<S52>/State-Space' */
  real_T DiscreteTransferFcn;          /* '<S4>/Discrete Transfer Fcn' */
  real_T DataTypeConversion;           /* '<S27>/Data Type Conversion' */
  real_T DataTypeConversion_e;         /* '<S34>/Data Type Conversion' */
  real_T DataTypeConversion_m;         /* '<S41>/Data Type Conversion' */
  real_T DataTypeConversion_o;         /* '<S48>/Data Type Conversion' */
  real_T Gain;                         /* '<S1>/Gain' */
  real_T Delay;                        /* '<S11>/Number of samples per cycle' */
  real_T VariableTransportDelay;       /* '<S11>/Variable Transport Delay' */
  real_T Integrator_k;                 /* '<S11>/Integrator' */
  real_T Divide;                       /* '<S3>/Divide' */
  real_T Saturation2;                  /* '<S10>/Saturation2' */
  real_T Kp5;                          /* '<S10>/Kp5' */
  real_T Vq;                           /* '<S3>/Product1' */
  real_T RateLimiter;                  /* '<S3>/Rate Limiter' */
  real_T Sum2;                         /* '<S1>/Sum2' */
  real_T integ1;                       /* '<S9>/integ1' */
  real_T Period;                       /* '<S9>/Period' */
  real_T VariableTransportDelay_b;     /* '<S9>/Variable Transport Delay' */
  real_T Integ2;                       /* '<S9>/Integ2' */
  real_T VariableTransportDelay1;      /* '<S9>/Variable Transport Delay1' */
  real_T MathFunction;                 /* '<S9>/Math Function' */
  real_T Product;                      /* '<S9>/Product' */
  real_T Product1;                     /* '<S9>/Product1' */
} B_inversor_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T StateSpace_DSTATE[3];         /* '<S52>/State-Space' */
  real_T DiscreteTransferFcn_states[2];/* '<S4>/Discrete Transfer Fcn' */
  real_T TimeStampA;                   /* '<S10>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S10>/Derivative' */
  real_T TimeStampB;                   /* '<S10>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S10>/Derivative' */
  real_T PrevYA;                       /* '<S3>/Rate Limiter' */
  real_T PrevYB;                       /* '<S3>/Rate Limiter' */
  real_T LastMajorTimeA;               /* '<S3>/Rate Limiter' */
  real_T LastMajorTimeB;               /* '<S3>/Rate Limiter' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay_RWORK;      /* '<S11>/Variable Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay_RWORK_b;    /* '<S9>/Variable Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[16384];
  } VariableTransportDelay1_RWORK;     /* '<S9>/Variable Transport Delay1' */

  struct {
    void *AS;
    void *BS;
    void *CS;
    void *DS;
    void *DX_COL;
    void *BD_COL;
    void *TMP1;
    void *TMP2;
    void *XTMP;
    void *SWITCH_STATUS;
    void *SWITCH_STATUS_INIT;
    void *SW_CHG;
    void *G_STATE;
    void *USWLAST;
    void *XKM12;
    void *XKP12;
    void *XLAST;
    void *ULAST;
    void *IDX_SW_CHG;
    void *Y_SWITCH;
    void *SWITCH_TYPES;
    void *IDX_OUT_SW;
    void *SWITCH_TOPO_SAVED_IDX;
    void *SWITCH_MAP;
  } StateSpace_PWORK;                  /* '<S52>/State-Space' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay_PWORK;      /* '<S11>/Variable Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay_PWORK_f;    /* '<S9>/Variable Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTransportDelay1_PWORK;     /* '<S9>/Variable Transport Delay1' */

  int_T StateSpace_IWORK[11];          /* '<S52>/State-Space' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay_IWORK;      /* '<S11>/Variable Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay_IWORK_h;    /* '<S9>/Variable Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTransportDelay1_IWORK;     /* '<S9>/Variable Transport Delay1' */

  boolean_T AutomaticGainControl_MODE; /* '<S3>/Automatic Gain Control' */
} DW_inversor_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T StateSpace_CSTATE[2];         /* '<S8>/State-Space' */
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_d;          /* '<S11>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S10>/Integrator' */
  real_T integ1_CSTATE;                /* '<S9>/integ1' */
  real_T Integ2_CSTATE;                /* '<S9>/Integ2' */
} X_inversor_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T StateSpace_CSTATE[2];         /* '<S8>/State-Space' */
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_d;          /* '<S11>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S10>/Integrator' */
  real_T integ1_CSTATE;                /* '<S9>/integ1' */
  real_T Integ2_CSTATE;                /* '<S9>/Integ2' */
} XDot_inversor_T;

/* State disabled  */
typedef struct {
  boolean_T StateSpace_CSTATE[2];      /* '<S8>/State-Space' */
  boolean_T Integrator_CSTATE;         /* '<S3>/Integrator' */
  boolean_T Integrator_CSTATE_d;       /* '<S11>/Integrator' */
  boolean_T Integrator_CSTATE_c;       /* '<S10>/Integrator' */
  boolean_T integ1_CSTATE;             /* '<S9>/integ1' */
  boolean_T Integ2_CSTATE;             /* '<S9>/Integ2' */
} XDis_inversor_T;

#ifndef ODE14X_INTG
#define ODE14X_INTG

/* ODE14X Integration Data */
typedef struct {
  real_T *x0;
  real_T *f0;
  real_T *x1start;
  real_T *f1;
  real_T *Delta;
  real_T *E;
  real_T *fac;
  real_T *DFDX;
  real_T *W;
  int_T *pivots;
  real_T *xtmp;
  real_T *ztmp;
  real_T *M;
  real_T *M1;
  real_T *Edot;
  real_T *xdot;
  real_T *fminusMxdot;
  boolean_T isFirstStep;
} ODE14X_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: zeros(8,1)
   * Referenced by: '<S54>/SwitchCurrents'
   */
  real_T SwitchCurrents_Value[8];

  /* Expression: S.A
   * Referenced by: '<S52>/State-Space'
   */
  real_T StateSpace_AS_param[9];

  /* Expression: S.B
   * Referenced by: '<S52>/State-Space'
   */
  real_T StateSpace_BS_param[27];

  /* Expression: S.C
   * Referenced by: '<S52>/State-Space'
   */
  real_T StateSpace_CS_param[33];

  /* Expression: S.D
   * Referenced by: '<S52>/State-Space'
   */
  real_T StateSpace_DS_param[99];

  /* Expression: S.x0
   * Referenced by: '<S52>/State-Space'
   */
  real_T StateSpace_X0_param[3];

  /* Expression: rep_seq_y
   * Referenced by: '<S51>/Look-Up Table1'
   */
  real_T LookUpTable1_tableData[3];

  /* Expression: rep_seq_t - min(rep_seq_t)
   * Referenced by: '<S51>/Look-Up Table1'
   */
  real_T LookUpTable1_bp01Data[3];
} ConstP_inversor_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Vdc;                          /* '<Root>/Vdc' */
  real_T u1;                           /* '<Root>/u1' */
} ExtU_inversor_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Volt;                         /* '<Root>/Volt' */
  real_T Current;                      /* '<Root>/Current' */
} ExtY_inversor_T;

/* Real-time Model Data Structure */
struct tag_RTM_inversor_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_inversor_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  real_T odeX0[7];
  real_T odeF0[7];
  real_T odeX1START[7];
  real_T odeF1[7];
  real_T odeDELTA[7];
  real_T odeE[4*7];
  real_T odeFAC[7];
  real_T odeDFDX[7*7];
  real_T odeW[7*7];
  int_T odePIVOTS[7];
  real_T odeXTMP[7];
  real_T odeZTMP[7];
  ODE14X_IntgData intgData;

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
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (auto storage) */
extern B_inversor_T inversor_B;

/* Continuous states (auto storage) */
extern X_inversor_T inversor_X;

/* Block states (auto storage) */
extern DW_inversor_T inversor_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_inversor_T inversor_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_inversor_T inversor_Y;

/* Constant parameters (auto storage) */
extern const ConstP_inversor_T inversor_ConstP;

/* Model entry point functions */
extern void inversor_initialize(void);
extern double inversor_step(double vdc, double u);//void inversor_step(void);
extern void inversor_terminate(void);

extern void guardarVdc(double vdc); 
extern void guardarU1(double U);
extern void guardarU2(double U);

/* Real-time Model object */
extern RT_MODEL_inversor_T *const inversor_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S6>/A_Filtro' : Unused code path elimination
 * Block '<S17>/Add' : Unused code path elimination
 * Block '<S25>/0 1' : Unused code path elimination
 * Block '<S25>/Gain' : Unused code path elimination
 * Block '<S25>/Saturation' : Unused code path elimination
 * Block '<S25>/Sum' : Unused code path elimination
 * Block '<S25>/Switch' : Unused code path elimination
 * Block '<S25>/eee' : Unused code path elimination
 * Block '<S27>/0 1' : Unused code path elimination
 * Block '<S27>/1//Rsw' : Unused code path elimination
 * Block '<S27>/Switch' : Unused code path elimination
 * Block '<S18>/Add' : Unused code path elimination
 * Block '<S32>/0 1' : Unused code path elimination
 * Block '<S32>/Gain' : Unused code path elimination
 * Block '<S32>/Saturation' : Unused code path elimination
 * Block '<S32>/Sum' : Unused code path elimination
 * Block '<S32>/Switch' : Unused code path elimination
 * Block '<S32>/eee' : Unused code path elimination
 * Block '<S34>/0 1' : Unused code path elimination
 * Block '<S34>/1//Rsw' : Unused code path elimination
 * Block '<S34>/Switch' : Unused code path elimination
 * Block '<S19>/Add' : Unused code path elimination
 * Block '<S39>/0 1' : Unused code path elimination
 * Block '<S39>/Gain' : Unused code path elimination
 * Block '<S39>/Saturation' : Unused code path elimination
 * Block '<S39>/Sum' : Unused code path elimination
 * Block '<S39>/Switch' : Unused code path elimination
 * Block '<S39>/eee' : Unused code path elimination
 * Block '<S41>/0 1' : Unused code path elimination
 * Block '<S41>/1//Rsw' : Unused code path elimination
 * Block '<S41>/Switch' : Unused code path elimination
 * Block '<S20>/Add' : Unused code path elimination
 * Block '<S46>/0 1' : Unused code path elimination
 * Block '<S46>/Gain' : Unused code path elimination
 * Block '<S46>/Saturation' : Unused code path elimination
 * Block '<S46>/Sum' : Unused code path elimination
 * Block '<S46>/Switch' : Unused code path elimination
 * Block '<S46>/eee' : Unused code path elimination
 * Block '<S48>/0 1' : Unused code path elimination
 * Block '<S48>/1//Rsw' : Unused code path elimination
 * Block '<S48>/Switch' : Unused code path elimination
 * Block '<S21>/do not delete this gain' : Unused code path elimination
 * Block '<S1>/Ref1' : Unused code path elimination
 * Block '<S7>/Scope1' : Unused code path elimination
 * Block '<S7>/Scope2' : Unused code path elimination
 * Block '<S10>/Kp1' : Eliminated nontunable gain of 1
 * Block '<S12>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S13>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S51>/Output' : Eliminate redundant signal conversion block
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
 * '<Root>' : 'inversor'
 * '<S1>'   : 'inversor/Subsystem1'
 * '<S2>'   : 'inversor/powergui'
 * '<S3>'   : 'inversor/Subsystem1/1-phase PLL'
 * '<S4>'   : 'inversor/Subsystem1/Control PR'
 * '<S5>'   : 'inversor/Subsystem1/Filtro'
 * '<S6>'   : 'inversor/Subsystem1/Inversor4'
 * '<S7>'   : 'inversor/Subsystem1/SPWM'
 * '<S8>'   : 'inversor/Subsystem1/1-phase PLL/2nd-Order Filter'
 * '<S9>'   : 'inversor/Subsystem1/1-phase PLL/Automatic Gain Control'
 * '<S10>'  : 'inversor/Subsystem1/1-phase PLL/PID Controller'
 * '<S11>'  : 'inversor/Subsystem1/1-phase PLL/Variable Frequency Mean value'
 * '<S12>'  : 'inversor/Subsystem1/Filtro/Current Measurement'
 * '<S13>'  : 'inversor/Subsystem1/Filtro/Vo3'
 * '<S14>'  : 'inversor/Subsystem1/Filtro/Current Measurement/Model'
 * '<S15>'  : 'inversor/Subsystem1/Filtro/Vo3/Model'
 * '<S16>'  : 'inversor/Subsystem1/Inversor4/Controlled Voltage Source2'
 * '<S17>'  : 'inversor/Subsystem1/Inversor4/Mosfet'
 * '<S18>'  : 'inversor/Subsystem1/Inversor4/Mosfet1'
 * '<S19>'  : 'inversor/Subsystem1/Inversor4/Mosfet2'
 * '<S20>'  : 'inversor/Subsystem1/Inversor4/Mosfet3'
 * '<S21>'  : 'inversor/Subsystem1/Inversor4/Vo4'
 * '<S22>'  : 'inversor/Subsystem1/Inversor4/Mosfet/Diode'
 * '<S23>'  : 'inversor/Subsystem1/Inversor4/Mosfet/Ideal Switch'
 * '<S24>'  : 'inversor/Subsystem1/Inversor4/Mosfet/Measurement list'
 * '<S25>'  : 'inversor/Subsystem1/Inversor4/Mosfet/Diode/Model'
 * '<S26>'  : 'inversor/Subsystem1/Inversor4/Mosfet/Diode/Model/Measurement list'
 * '<S27>'  : 'inversor/Subsystem1/Inversor4/Mosfet/Ideal Switch/Model'
 * '<S28>'  : 'inversor/Subsystem1/Inversor4/Mosfet/Ideal Switch/Model/Measurement list'
 * '<S29>'  : 'inversor/Subsystem1/Inversor4/Mosfet1/Diode'
 * '<S30>'  : 'inversor/Subsystem1/Inversor4/Mosfet1/Ideal Switch'
 * '<S31>'  : 'inversor/Subsystem1/Inversor4/Mosfet1/Measurement list'
 * '<S32>'  : 'inversor/Subsystem1/Inversor4/Mosfet1/Diode/Model'
 * '<S33>'  : 'inversor/Subsystem1/Inversor4/Mosfet1/Diode/Model/Measurement list'
 * '<S34>'  : 'inversor/Subsystem1/Inversor4/Mosfet1/Ideal Switch/Model'
 * '<S35>'  : 'inversor/Subsystem1/Inversor4/Mosfet1/Ideal Switch/Model/Measurement list'
 * '<S36>'  : 'inversor/Subsystem1/Inversor4/Mosfet2/Diode'
 * '<S37>'  : 'inversor/Subsystem1/Inversor4/Mosfet2/Ideal Switch'
 * '<S38>'  : 'inversor/Subsystem1/Inversor4/Mosfet2/Measurement list'
 * '<S39>'  : 'inversor/Subsystem1/Inversor4/Mosfet2/Diode/Model'
 * '<S40>'  : 'inversor/Subsystem1/Inversor4/Mosfet2/Diode/Model/Measurement list'
 * '<S41>'  : 'inversor/Subsystem1/Inversor4/Mosfet2/Ideal Switch/Model'
 * '<S42>'  : 'inversor/Subsystem1/Inversor4/Mosfet2/Ideal Switch/Model/Measurement list'
 * '<S43>'  : 'inversor/Subsystem1/Inversor4/Mosfet3/Diode'
 * '<S44>'  : 'inversor/Subsystem1/Inversor4/Mosfet3/Ideal Switch'
 * '<S45>'  : 'inversor/Subsystem1/Inversor4/Mosfet3/Measurement list'
 * '<S46>'  : 'inversor/Subsystem1/Inversor4/Mosfet3/Diode/Model'
 * '<S47>'  : 'inversor/Subsystem1/Inversor4/Mosfet3/Diode/Model/Measurement list'
 * '<S48>'  : 'inversor/Subsystem1/Inversor4/Mosfet3/Ideal Switch/Model'
 * '<S49>'  : 'inversor/Subsystem1/Inversor4/Mosfet3/Ideal Switch/Model/Measurement list'
 * '<S50>'  : 'inversor/Subsystem1/Inversor4/Vo4/Model'
 * '<S51>'  : 'inversor/Subsystem1/SPWM/10V~5KHz'
 * '<S52>'  : 'inversor/powergui/EquivalentModel1'
 * '<S53>'  : 'inversor/powergui/EquivalentModel1/Gates'
 * '<S54>'  : 'inversor/powergui/EquivalentModel1/Sources'
 * '<S55>'  : 'inversor/powergui/EquivalentModel1/Status'
 * '<S56>'  : 'inversor/powergui/EquivalentModel1/Yout'
 */
#endif                                 /* RTW_HEADER_inversor_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
