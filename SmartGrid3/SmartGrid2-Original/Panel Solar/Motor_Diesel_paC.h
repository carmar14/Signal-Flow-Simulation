/*
 * File: Motor_Diesel_paC.h
 *
 * Code generated for Simulink model 'Motor_Diesel_paC'.
 *
 * Model version                  : 1.36
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Jan 29 07:35:33 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Motor_Diesel_paC_h_
#define RTW_HEADER_Motor_Diesel_paC_h_
#include <string.h>
#include <stddef.h>
#ifndef Motor_Diesel_paC_COMMON_INCLUDES_
# define Motor_Diesel_paC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Motor_Diesel_paC_COMMON_INCLUDES_ */

#include "Motor_Diesel_paC_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T ActuadorMotorTm001s_states;   /* '<Root>/Actuador - Motor Tm=0.01s' */
  real_T DelayTm001_DSTATE[50];        /* '<Root>/Delay Tm=0.01' */
  real_T EjeTm001s_states;             /* '<Root>/Eje Tm=0.01s' */
} DW_Motor_Diesel_paC_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Actuador;                     /* '<Root>/Actuador' */
  real_T Par;                          /* '<Root>/Par' */
} ExtU_Motor_Diesel_paC_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Flujo;                        /* '<Root>/Flujo' */
  real_T Velocidad;                    /* '<Root>/Velocidad' */
  real_T Tensin;                       /* '<Root>/Tensión' */
} ExtY_Motor_Diesel_paC_T;

/* Real-time Model Data Structure */
struct tag_RTM_Motor_Diesel_paC_T {
  const char_T * volatile errorStatus;
};

/* Block states (auto storage) */
extern DW_Motor_Diesel_paC_T Motor_Diesel_paC_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_Motor_Diesel_paC_T Motor_Diesel_paC_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Motor_Diesel_paC_T Motor_Diesel_paC_Y;

/* Model entry point functions */
extern void Motor_Diesel_paC_initialize(void);
extern void Motor_Diesel_paC_step(void);
extern void Motor_Diesel_paC_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Motor_Diesel_paC_T *const Motor_Diesel_paC_M;

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
 * '<Root>' : 'Motor_Diesel_paC'
 */
#endif                                 /* RTW_HEADER_Motor_Diesel_paC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
