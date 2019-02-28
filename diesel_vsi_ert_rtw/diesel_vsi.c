/*
 * File: diesel_vsi.c
 *
 * Code generated for Simulink model 'diesel_vsi'.
 *
 * Model version                  : 1.23
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Wed Feb 27 11:18:07 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "diesel_vsi.h"
#include "diesel_vsi_private.h"

/* Block signals (default storage) */
B_diesel_vsi_T diesel_vsi_B;

/* Continuous states */
X_diesel_vsi_T diesel_vsi_X;

/* Block states (default storage) */
DW_diesel_vsi_T diesel_vsi_DW;

/* External inputs (root inport signals with default storage) */
ExtU_diesel_vsi_T diesel_vsi_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_diesel_vsi_T diesel_vsi_Y;

/* Real-time model */
RT_MODEL_diesel_vsi_T diesel_vsi_M_;
RT_MODEL_diesel_vsi_T *const diesel_vsi_M = &diesel_vsi_M_;

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 8;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  diesel_vsi_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  diesel_vsi_step();
  diesel_vsi_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  diesel_vsi_step();
  diesel_vsi_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  diesel_vsi_step();
  diesel_vsi_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void diesel_vsi_step(void)
{
  /* local block i/o variables */
  real_T rtb_u;
  real_T rtb_MotordeCombustin1;
  if (rtmIsMajorTimeStep(diesel_vsi_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&diesel_vsi_M->solverInfo,
                          ((diesel_vsi_M->Timing.clockTick0+1)*
      diesel_vsi_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(diesel_vsi_M)) {
    diesel_vsi_M->Timing.t[0] = rtsiGetT(&diesel_vsi_M->solverInfo);
  }

  {
    real_T *lastU;
    real_T lastTime;
    real_T rtb_VSIlineZ1;

    /* Gain: '<S2>/ 1' incorporates:
     *  TransferFcn: '<S2>/Actuador1'
     */
    rtb_u = 8.0 * diesel_vsi_X.Actuador1_CSTATE * 1.15;

    /* Outport: '<Root>/flujo' */
    diesel_vsi_Y.flujo = rtb_u;

    /* TransferFcn: '<Root>/VSI  line Z1' */
    rtb_VSIlineZ1 = 200.0 * diesel_vsi_X.VSIlineZ1_CSTATE;

    /* Sin: '<Root>/Sine Wave2' incorporates:
     *  Sin: '<Root>/Sine Wave1'
     */
    diesel_vsi_B.SineWave2 = sin(376.99111843077515 * diesel_vsi_M->Timing.t[0])
      * 170.0;

    /* Derivative: '<Root>/Derivative3' */
    if ((diesel_vsi_DW.TimeStampA >= diesel_vsi_M->Timing.t[0]) &&
        (diesel_vsi_DW.TimeStampB >= diesel_vsi_M->Timing.t[0])) {
      diesel_vsi_Y.i2 = 0.0;
    } else {
      lastTime = diesel_vsi_DW.TimeStampA;
      lastU = &diesel_vsi_DW.LastUAtTimeA;
      if (diesel_vsi_DW.TimeStampA < diesel_vsi_DW.TimeStampB) {
        if (diesel_vsi_DW.TimeStampB < diesel_vsi_M->Timing.t[0]) {
          lastTime = diesel_vsi_DW.TimeStampB;
          lastU = &diesel_vsi_DW.LastUAtTimeB;
        }
      } else {
        if (diesel_vsi_DW.TimeStampA >= diesel_vsi_M->Timing.t[0]) {
          lastTime = diesel_vsi_DW.TimeStampB;
          lastU = &diesel_vsi_DW.LastUAtTimeB;
        }
      }

      diesel_vsi_Y.i2 = (diesel_vsi_B.SineWave2 - *lastU) /
        (diesel_vsi_M->Timing.t[0] - lastTime);
    }

    /* End of Derivative: '<Root>/Derivative3' */

    /* Sum: '<Root>/Sum13' incorporates:
     *  Gain: '<Root>/Gain9'
     */
    diesel_vsi_Y.i2 = rtb_VSIlineZ1 - 2.2E-5 * diesel_vsi_Y.i2;

    /* Sin: '<Root>/Sine Wave1' */
    diesel_vsi_B.refvoltage = diesel_vsi_B.SineWave2;

    /* Derivative: '<Root>/Derivative2' */
    if ((diesel_vsi_DW.TimeStampA_f >= diesel_vsi_M->Timing.t[0]) &&
        (diesel_vsi_DW.TimeStampB_g >= diesel_vsi_M->Timing.t[0])) {
      rtb_MotordeCombustin1 = 0.0;
    } else {
      lastTime = diesel_vsi_DW.TimeStampA_f;
      lastU = &diesel_vsi_DW.LastUAtTimeA_b;
      if (diesel_vsi_DW.TimeStampA_f < diesel_vsi_DW.TimeStampB_g) {
        if (diesel_vsi_DW.TimeStampB_g < diesel_vsi_M->Timing.t[0]) {
          lastTime = diesel_vsi_DW.TimeStampB_g;
          lastU = &diesel_vsi_DW.LastUAtTimeB_l;
        }
      } else {
        if (diesel_vsi_DW.TimeStampA_f >= diesel_vsi_M->Timing.t[0]) {
          lastTime = diesel_vsi_DW.TimeStampB_g;
          lastU = &diesel_vsi_DW.LastUAtTimeB_l;
        }
      }

      rtb_MotordeCombustin1 = (diesel_vsi_B.refvoltage - *lastU) /
        (diesel_vsi_M->Timing.t[0] - lastTime);
    }

    /* End of Derivative: '<Root>/Derivative2' */

    /* Sum: '<Root>/Sum11' incorporates:
     *  Gain: '<Root>/Gain6'
     *  Sum: '<Root>/Sum10'
     */
    diesel_vsi_B.Sum11 = (2.2E-5 * rtb_MotordeCombustin1 + diesel_vsi_Y.i2) -
      rtb_VSIlineZ1;

    /* TransferFcn: '<S1>/Transfer Fcn2' */
    rtb_MotordeCombustin1 = 0.0;
    rtb_MotordeCombustin1 += 2.0 * diesel_vsi_X.TransferFcn2_CSTATE[0];
    rtb_MotordeCombustin1 += 0.0 * diesel_vsi_X.TransferFcn2_CSTATE[1];

    /* Sum: '<S1>/Sum9' incorporates:
     *  Gain: '<S1>/Gain2'
     *  Sum: '<S1>/Sum5'
     */
    rtb_MotordeCombustin1 += 0.002 * diesel_vsi_B.Sum11;

    /* Outport: '<Root>/duty' */
    diesel_vsi_Y.duty = rtb_MotordeCombustin1;

    /* Gain: '<Root>/Gain8' */
    rtb_VSIlineZ1 = 2.0 * rtb_MotordeCombustin1;

    /* TransferFcn: '<Root>/Transfer Fcn5' */
    rtb_MotordeCombustin1 = 0.0;
    rtb_MotordeCombustin1 += 1.639344262295082 *
      diesel_vsi_X.TransferFcn5_CSTATE;

    /* Sum: '<Root>/Sum12' incorporates:
     *  Product: '<Root>/Product3'
     */
    diesel_vsi_B.Sum12 = rtb_VSIlineZ1 * rtb_MotordeCombustin1 -
      diesel_vsi_B.SineWave2;

    /* Outport: '<Root>/vdc' */
    diesel_vsi_Y.vdc = rtb_MotordeCombustin1;

    /* Sum: '<Root>/Sum8' incorporates:
     *  Constant: '<Root>/Constant8'
     *  Gain: '<Root>/Gain11'
     *  Gain: '<Root>/Gain12'
     *  Gain: '<Root>/Gain7'
     *  Gain: '<S2>/ Generador1'
     *  Gain: '<S2>/Gain1'
     *  Product: '<Root>/Divide1'
     *  Product: '<Root>/Multiply1'
     *  Sum: '<Root>/Sum14'
     *  Sum: '<Root>/Sum17'
     *  TransferFcn: '<S2>/Din�mica en el eje1'
     */
    diesel_vsi_B.OutputDCVoltage = 0.03 * diesel_vsi_X.Dinmicaeneleje1_CSTATE *
      0.5 * 12000.0 * 0.05 - (diesel_vsi_Y.i2 * diesel_vsi_B.SineWave2 * 1.1 /
      (rtb_MotordeCombustin1 + 1.0) + 0.05 * rtb_MotordeCombustin1);

    /* Sum: '<Root>/Sum9' incorporates:
     *  Constant: '<Root>/Constant6'
     */
    rtb_MotordeCombustin1 = 1000.0 - rtb_MotordeCombustin1;

    /* Gain: '<S3>/Filter Coefficient' incorporates:
     *  Gain: '<S3>/Derivative Gain'
     *  Integrator: '<S3>/Filter'
     *  Sum: '<S3>/SumD'
     */
    diesel_vsi_B.FilterCoefficient = (0.00224356290205903 *
      rtb_MotordeCombustin1 - diesel_vsi_X.Filter_CSTATE) * 0.155980576752107;

    /* Sum: '<S3>/Sum' incorporates:
     *  Gain: '<S3>/Proportional Gain'
     *  Integrator: '<S3>/Integrator'
     */
    diesel_vsi_B.Sum = (0.000853612192208084 * rtb_MotordeCombustin1 +
                        diesel_vsi_X.Integrator_CSTATE) +
      diesel_vsi_B.FilterCoefficient;

    /* Gain: '<S3>/Integral Gain' */
    diesel_vsi_B.IntegralGain = 3.94394231511782E-5 * rtb_MotordeCombustin1;

    /* TransportDelay: '<S2>/Motor de Combusti�n1' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_vsi_DW.MotordeCombustin1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_vsi_DW.MotordeCombustin1_PWORK.TUbufferPtrs[1];
      real_T simTime = diesel_vsi_M->Timing.t[0];
      real_T tMinusDelay = simTime - 0.5;
      rtb_MotordeCombustin1 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        diesel_vsi_DW.MotordeCombustin1_IWORK.CircularBufSize,
        &diesel_vsi_DW.MotordeCombustin1_IWORK.Last,
        diesel_vsi_DW.MotordeCombustin1_IWORK.Tail,
        diesel_vsi_DW.MotordeCombustin1_IWORK.Head,
        0.0,
        0,
        0);
    }

    /* Sum: '<S2>/Sum2' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    diesel_vsi_B.Sum2 = rtb_MotordeCombustin1 - 0.1;
  }

  if (rtmIsMajorTimeStep(diesel_vsi_M)) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative3' */
    if (diesel_vsi_DW.TimeStampA == (rtInf)) {
      diesel_vsi_DW.TimeStampA = diesel_vsi_M->Timing.t[0];
      lastU = &diesel_vsi_DW.LastUAtTimeA;
    } else if (diesel_vsi_DW.TimeStampB == (rtInf)) {
      diesel_vsi_DW.TimeStampB = diesel_vsi_M->Timing.t[0];
      lastU = &diesel_vsi_DW.LastUAtTimeB;
    } else if (diesel_vsi_DW.TimeStampA < diesel_vsi_DW.TimeStampB) {
      diesel_vsi_DW.TimeStampA = diesel_vsi_M->Timing.t[0];
      lastU = &diesel_vsi_DW.LastUAtTimeA;
    } else {
      diesel_vsi_DW.TimeStampB = diesel_vsi_M->Timing.t[0];
      lastU = &diesel_vsi_DW.LastUAtTimeB;
    }

    *lastU = diesel_vsi_B.SineWave2;

    /* End of Update for Derivative: '<Root>/Derivative3' */

    /* Update for Derivative: '<Root>/Derivative2' */
    if (diesel_vsi_DW.TimeStampA_f == (rtInf)) {
      diesel_vsi_DW.TimeStampA_f = diesel_vsi_M->Timing.t[0];
      lastU = &diesel_vsi_DW.LastUAtTimeA_b;
    } else if (diesel_vsi_DW.TimeStampB_g == (rtInf)) {
      diesel_vsi_DW.TimeStampB_g = diesel_vsi_M->Timing.t[0];
      lastU = &diesel_vsi_DW.LastUAtTimeB_l;
    } else if (diesel_vsi_DW.TimeStampA_f < diesel_vsi_DW.TimeStampB_g) {
      diesel_vsi_DW.TimeStampA_f = diesel_vsi_M->Timing.t[0];
      lastU = &diesel_vsi_DW.LastUAtTimeA_b;
    } else {
      diesel_vsi_DW.TimeStampB_g = diesel_vsi_M->Timing.t[0];
      lastU = &diesel_vsi_DW.LastUAtTimeB_l;
    }

    *lastU = diesel_vsi_B.refvoltage;

    /* End of Update for Derivative: '<Root>/Derivative2' */

    /* Update for TransportDelay: '<S2>/Motor de Combusti�n1' */
    {
      real_T **uBuffer = (real_T**)
        &diesel_vsi_DW.MotordeCombustin1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &diesel_vsi_DW.MotordeCombustin1_PWORK.TUbufferPtrs[1];
      real_T simTime = diesel_vsi_M->Timing.t[0];
      diesel_vsi_DW.MotordeCombustin1_IWORK.Head =
        ((diesel_vsi_DW.MotordeCombustin1_IWORK.Head <
          (diesel_vsi_DW.MotordeCombustin1_IWORK.CircularBufSize-1)) ?
         (diesel_vsi_DW.MotordeCombustin1_IWORK.Head+1) : 0);
      if (diesel_vsi_DW.MotordeCombustin1_IWORK.Head ==
          diesel_vsi_DW.MotordeCombustin1_IWORK.Tail) {
        diesel_vsi_DW.MotordeCombustin1_IWORK.Tail =
          ((diesel_vsi_DW.MotordeCombustin1_IWORK.Tail <
            (diesel_vsi_DW.MotordeCombustin1_IWORK.CircularBufSize-1)) ?
           (diesel_vsi_DW.MotordeCombustin1_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[diesel_vsi_DW.MotordeCombustin1_IWORK.Head] = simTime;
      (*uBuffer)[diesel_vsi_DW.MotordeCombustin1_IWORK.Head] = rtb_u;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(diesel_vsi_M)) {
    rt_ertODEUpdateContinuousStates(&diesel_vsi_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++diesel_vsi_M->Timing.clockTick0;
    diesel_vsi_M->Timing.t[0] = rtsiGetSolverStopTime(&diesel_vsi_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      diesel_vsi_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void diesel_vsi_derivatives(void)
{
  XDot_diesel_vsi_T *_rtXdot;
  _rtXdot = ((XDot_diesel_vsi_T *) diesel_vsi_M->derivs);

  /* Derivatives for TransferFcn: '<S2>/Actuador1' */
  _rtXdot->Actuador1_CSTATE = 0.0;
  _rtXdot->Actuador1_CSTATE += -8.0 * diesel_vsi_X.Actuador1_CSTATE;
  _rtXdot->Actuador1_CSTATE += diesel_vsi_B.Sum;

  /* Derivatives for TransferFcn: '<Root>/VSI  line Z1' */
  _rtXdot->VSIlineZ1_CSTATE = 0.0;
  _rtXdot->VSIlineZ1_CSTATE += -20.0 * diesel_vsi_X.VSIlineZ1_CSTATE;
  _rtXdot->VSIlineZ1_CSTATE += diesel_vsi_B.Sum12;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += -2.0 * diesel_vsi_X.TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += -142122.30337568672 *
    diesel_vsi_X.TransferFcn2_CSTATE[1];
  _rtXdot->TransferFcn2_CSTATE[1] += diesel_vsi_X.TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[0] += diesel_vsi_B.Sum11;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn5' */
  _rtXdot->TransferFcn5_CSTATE = 0.0;
  _rtXdot->TransferFcn5_CSTATE += -0.0 * diesel_vsi_X.TransferFcn5_CSTATE;
  _rtXdot->TransferFcn5_CSTATE += diesel_vsi_B.OutputDCVoltage;

  /* Derivatives for TransferFcn: '<S2>/Din�mica en el eje1' */
  _rtXdot->Dinmicaeneleje1_CSTATE = 0.0;
  _rtXdot->Dinmicaeneleje1_CSTATE += -0.03 * diesel_vsi_X.Dinmicaeneleje1_CSTATE;
  _rtXdot->Dinmicaeneleje1_CSTATE += diesel_vsi_B.Sum2;

  /* Derivatives for Integrator: '<S3>/Filter' */
  _rtXdot->Filter_CSTATE = diesel_vsi_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = diesel_vsi_B.IntegralGain;
}

/* Model initialize function */
void diesel_vsi_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)diesel_vsi_M, 0,
                sizeof(RT_MODEL_diesel_vsi_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&diesel_vsi_M->solverInfo,
                          &diesel_vsi_M->Timing.simTimeStep);
    rtsiSetTPtr(&diesel_vsi_M->solverInfo, &rtmGetTPtr(diesel_vsi_M));
    rtsiSetStepSizePtr(&diesel_vsi_M->solverInfo,
                       &diesel_vsi_M->Timing.stepSize0);
    rtsiSetdXPtr(&diesel_vsi_M->solverInfo, &diesel_vsi_M->derivs);
    rtsiSetContStatesPtr(&diesel_vsi_M->solverInfo, (real_T **)
                         &diesel_vsi_M->contStates);
    rtsiSetNumContStatesPtr(&diesel_vsi_M->solverInfo,
      &diesel_vsi_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&diesel_vsi_M->solverInfo,
      &diesel_vsi_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&diesel_vsi_M->solverInfo,
      &diesel_vsi_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&diesel_vsi_M->solverInfo,
      &diesel_vsi_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&diesel_vsi_M->solverInfo, (&rtmGetErrorStatus
      (diesel_vsi_M)));
    rtsiSetRTModelPtr(&diesel_vsi_M->solverInfo, diesel_vsi_M);
  }

  rtsiSetSimTimeStep(&diesel_vsi_M->solverInfo, MAJOR_TIME_STEP);
  diesel_vsi_M->intgData.y = diesel_vsi_M->odeY;
  diesel_vsi_M->intgData.f[0] = diesel_vsi_M->odeF[0];
  diesel_vsi_M->intgData.f[1] = diesel_vsi_M->odeF[1];
  diesel_vsi_M->intgData.f[2] = diesel_vsi_M->odeF[2];
  diesel_vsi_M->intgData.f[3] = diesel_vsi_M->odeF[3];
  diesel_vsi_M->contStates = ((X_diesel_vsi_T *) &diesel_vsi_X);
  rtsiSetSolverData(&diesel_vsi_M->solverInfo, (void *)&diesel_vsi_M->intgData);
  rtsiSetSolverName(&diesel_vsi_M->solverInfo,"ode4");
  rtmSetTPtr(diesel_vsi_M, &diesel_vsi_M->Timing.tArray[0]);
  diesel_vsi_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &diesel_vsi_B), 0,
                sizeof(B_diesel_vsi_T));

  /* states (continuous) */
  {
    (void) memset((void *)&diesel_vsi_X, 0,
                  sizeof(X_diesel_vsi_T));
  }

  /* states (dwork) */
  (void) memset((void *)&diesel_vsi_DW, 0,
                sizeof(DW_diesel_vsi_T));

  /* external inputs */
  (void)memset((void *)&diesel_vsi_U, 0, sizeof(ExtU_diesel_vsi_T));

  /* external outputs */
  (void) memset((void *)&diesel_vsi_Y, 0,
                sizeof(ExtY_diesel_vsi_T));

  /* Start for TransportDelay: '<S2>/Motor de Combusti�n1' */
  {
    real_T *pBuffer = &diesel_vsi_DW.MotordeCombustin1_RWORK.TUbufferArea[0];
    diesel_vsi_DW.MotordeCombustin1_IWORK.Tail = 0;
    diesel_vsi_DW.MotordeCombustin1_IWORK.Head = 0;
    diesel_vsi_DW.MotordeCombustin1_IWORK.Last = 0;
    diesel_vsi_DW.MotordeCombustin1_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = diesel_vsi_M->Timing.t[0];
    diesel_vsi_DW.MotordeCombustin1_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    diesel_vsi_DW.MotordeCombustin1_PWORK.TUbufferPtrs[1] = (void *) &pBuffer
      [1024];
  }

  /* InitializeConditions for TransferFcn: '<S2>/Actuador1' */
  diesel_vsi_X.Actuador1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/VSI  line Z1' */
  diesel_vsi_X.VSIlineZ1_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative3' */
  diesel_vsi_DW.TimeStampA = (rtInf);
  diesel_vsi_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Derivative: '<Root>/Derivative2' */
  diesel_vsi_DW.TimeStampA_f = (rtInf);
  diesel_vsi_DW.TimeStampB_g = (rtInf);

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2' */
  diesel_vsi_X.TransferFcn2_CSTATE[0] = 0.0;
  diesel_vsi_X.TransferFcn2_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn5' */
  diesel_vsi_X.TransferFcn5_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Din�mica en el eje1' */
  diesel_vsi_X.Dinmicaeneleje1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Filter' */
  diesel_vsi_X.Filter_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  diesel_vsi_X.Integrator_CSTATE = 0.0;
}

/* Model terminate function */
void diesel_vsi_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
