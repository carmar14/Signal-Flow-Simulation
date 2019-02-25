/*
 * File: Motor_Diesel_paC.c
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

#include "Motor_Diesel_paC.h"
#include "Motor_Diesel_paC_private.h"
#include <stdio.h>

/* Block states (auto storage) */
DW_Motor_Diesel_paC_T Motor_Diesel_paC_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_Motor_Diesel_paC_T Motor_Diesel_paC_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_Motor_Diesel_paC_T Motor_Diesel_paC_Y;

/* Real-time model */
RT_MODEL_Motor_Diesel_paC_T Motor_Diesel_paC_M_;
RT_MODEL_Motor_Diesel_paC_T *const Motor_Diesel_paC_M = &Motor_Diesel_paC_M_;

/* Model step function */
void Motor_Diesel_paC_step(void)
{
  int32_T k;
  int_T i=0;
  real_T rtb_ActuadorMotorTm001s;
  real_T rtb_Velocidad;
  real_T ActuadorMotorTm001s_tmp;
  real_T EjeTm001s_tmp;

  /* DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s' incorporates:
   *  Inport: '<Root>/Actuador'
   */
  //ActuadorMotorTm001s_tmp = Motor_Diesel_paC_U.Actuador - -0.92307692307692313 *
  ActuadorMotorTm001s_tmp = 1- -0.92307692307692313 *
    Motor_Diesel_paC_DW.ActuadorMotorTm001s_states;
  rtb_ActuadorMotorTm001s = 0.038461538461538464 * ActuadorMotorTm001s_tmp +
    0.038461538461538464 * Motor_Diesel_paC_DW.ActuadorMotorTm001s_states;

  /* Outport: '<Root>/Flujo' */
  Motor_Diesel_paC_Y.Flujo = rtb_ActuadorMotorTm001s;
   //printf("Flujo %5.2f\n",rtb_ActuadorMotorTm001s);

  /* DiscreteTransferFcn: '<Root>/Eje Tm=0.01s' incorporates:
   *  Delay: '<Root>/Delay Tm=0.01'
   *  Inport: '<Root>/Par'
   *  Sum: '<Root>/Sum2'
   */
  EjeTm001s_tmp = (Motor_Diesel_paC_DW.DelayTm001_DSTATE[0] -
                   Motor_Diesel_paC_U.Par) - -0.9997 *
    Motor_Diesel_paC_DW.EjeTm001s_states;
  rtb_Velocidad = 0.00015 * EjeTm001s_tmp + 0.00015 *
    Motor_Diesel_paC_DW.EjeTm001s_states;

  /* Outport: '<Root>/Velocidad' */
  Motor_Diesel_paC_Y.Velocidad = rtb_Velocidad;

  //printf("Velocidad %5.2f\n",rtb_Velocidad);

  /* Outport: '<Root>/Tensión' incorporates:
   *  Gain: '<Root>/ Generador1'
   */
  Motor_Diesel_paC_Y.Tensin = 0.5 * rtb_Velocidad;

  /* Update for DiscreteTransferFcn: '<Root>/Actuador - Motor Tm=0.01s' */
  Motor_Diesel_paC_DW.ActuadorMotorTm001s_states = ActuadorMotorTm001s_tmp;

  /* Update for Delay: '<Root>/Delay Tm=0.01' incorporates:
   *  Gain: '<Root>/ 1'
   */
  for (k = 0; k < 49; k++) {
    Motor_Diesel_paC_DW.DelayTm001_DSTATE[k] =
      Motor_Diesel_paC_DW.DelayTm001_DSTATE[k + 1];
  }

  Motor_Diesel_paC_DW.DelayTm001_DSTATE[49] = 1.15 * rtb_ActuadorMotorTm001s;

  /* End of Update for Delay: '<Root>/Delay Tm=0.01' */

  /* Update for DiscreteTransferFcn: '<Root>/Eje Tm=0.01s' */
  Motor_Diesel_paC_DW.EjeTm001s_states = EjeTm001s_tmp;
  printf("Velocidad %5.2f\n",Motor_Diesel_paC_Y.Velocidad);
}

/* Model initialize function */
void Motor_Diesel_paC_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Motor_Diesel_paC_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Motor_Diesel_paC_DW, 0,
                sizeof(DW_Motor_Diesel_paC_T));

  /* external inputs */
  (void)memset((void *)&Motor_Diesel_paC_U, 0, sizeof(ExtU_Motor_Diesel_paC_T));

  /* external outputs */
  (void) memset((void *)&Motor_Diesel_paC_Y, 0,
                sizeof(ExtY_Motor_Diesel_paC_T));
}

/* Model terminate function */
void Motor_Diesel_paC_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
