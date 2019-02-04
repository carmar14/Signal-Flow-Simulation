/*
 * File: PV_vsi_sf_carga.c
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

#include "PV_vsi_sf_carga.h"
#include "PV_vsi_sf_carga_private.h"

/* Block signals (auto storage) */
B_PV_vsi_sf_carga_T PV_vsi_sf_carga_B;

/* Continuous states */
X_PV_vsi_sf_carga_T PV_vsi_sf_carga_X;

/* Block states (auto storage) */
DW_PV_vsi_sf_carga_T PV_vsi_sf_carga_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_PV_vsi_sf_carga_T PV_vsi_sf_carga_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_PV_vsi_sf_carga_T PV_vsi_sf_carga_Y;

/* Real-time model */
RT_MODEL_PV_vsi_sf_carga_T PV_vsi_sf_carga_M_;
RT_MODEL_PV_vsi_sf_carga_T *const PV_vsi_sf_carga_M = &PV_vsi_sf_carga_M_;

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

real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
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
  int_T nXc = 10;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  PV_vsi_sf_carga_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  PV_vsi_sf_carga_step();
  PV_vsi_sf_carga_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  PV_vsi_sf_carga_step();
  PV_vsi_sf_carga_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  PV_vsi_sf_carga_step();
  PV_vsi_sf_carga_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T a;
  a = fabs(u0);
  y = fabs(u1);
  if (a < y) {
    a /= y;
    y *= sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = sqrt(y * y + 1.0) * a;
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void PV_vsi_sf_carga_step(void)
{
  /* local block i/o variables */
  real_T rtb_integrator;
  real_T rtb_TransportDelay;
  real_T rtb_integrator_m;
  real_T rtb_TransportDelay_g;
  real_T rtb_integrator_e;
  real_T rtb_TransportDelay_d;
  real_T rtb_integrator_o;
  real_T rtb_TransportDelay_e;
  if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&PV_vsi_sf_carga_M->solverInfo,
                          ((PV_vsi_sf_carga_M->Timing.clockTick0+1)*
      PV_vsi_sf_carga_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(PV_vsi_sf_carga_M)) {
    PV_vsi_sf_carga_M->Timing.t[0] = rtsiGetT(&PV_vsi_sf_carga_M->solverInfo);
  }

  {
    real_T *lastU;
    real_T rtb_vsicurrent;
    real_T rtb_VSIlineZ;
    real_T rtb_y;
    real_T rtb_ComplextoMagnitudeAngle_o1;
    real_T rtb_ComplextoMagnitudeAngle_o2;

    /* TransferFcn: '<Root>/VSI  line Z' */
    rtb_VSIlineZ = 33.333333333333336 * PV_vsi_sf_carga_X.VSIlineZ_CSTATE;

    /* TransferFcn: '<Root>/Transfer Fcn3' */
    PV_vsi_sf_carga_B.TransferFcn3 = 0.0;
    PV_vsi_sf_carga_B.TransferFcn3 += 376.7897513187641 *
      PV_vsi_sf_carga_X.TransferFcn3_CSTATE[0];
    PV_vsi_sf_carga_B.TransferFcn3 += 0.0 *
      PV_vsi_sf_carga_X.TransferFcn3_CSTATE[1];

    /* Derivative: '<Root>/Derivative1' */
    if ((PV_vsi_sf_carga_DW.TimeStampA >= PV_vsi_sf_carga_M->Timing.t[0]) &&
        (PV_vsi_sf_carga_DW.TimeStampB >= PV_vsi_sf_carga_M->Timing.t[0])) {
      rtb_vsicurrent = 0.0;
    } else {
      rtb_ComplextoMagnitudeAngle_o2 = PV_vsi_sf_carga_DW.TimeStampA;
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA;
      if (PV_vsi_sf_carga_DW.TimeStampA < PV_vsi_sf_carga_DW.TimeStampB) {
        if (PV_vsi_sf_carga_DW.TimeStampB < PV_vsi_sf_carga_M->Timing.t[0]) {
          rtb_ComplextoMagnitudeAngle_o2 = PV_vsi_sf_carga_DW.TimeStampB;
          lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB;
        }
      } else {
        if (PV_vsi_sf_carga_DW.TimeStampA >= PV_vsi_sf_carga_M->Timing.t[0]) {
          rtb_ComplextoMagnitudeAngle_o2 = PV_vsi_sf_carga_DW.TimeStampB;
          lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB;
        }
      }

      rtb_vsicurrent = (PV_vsi_sf_carga_B.TransferFcn3 - *lastU) /
        (PV_vsi_sf_carga_M->Timing.t[0] - rtb_ComplextoMagnitudeAngle_o2);
    }

    /* End of Derivative: '<Root>/Derivative1' */

    /* Sum: '<Root>/Sum5' incorporates:
     *  Gain: '<Root>/Gain2'
     */
    rtb_vsicurrent = rtb_VSIlineZ - 0.00061 * rtb_vsicurrent;

    /* Outport: '<Root>/i3' */
    PV_vsi_sf_carga_Y.i3 = rtb_vsicurrent;

    /* Integrator: '<Root>/Integrator' */
    /* Limited  Integrator  */
    if (PV_vsi_sf_carga_X.Integrator_CSTATE >= 1.0) {
      PV_vsi_sf_carga_X.Integrator_CSTATE = 1.0;
    } else {
      if (PV_vsi_sf_carga_X.Integrator_CSTATE <= 0.0) {
        PV_vsi_sf_carga_X.Integrator_CSTATE = 0.0;
      }
    }

    /* MATLAB Function: '<Root>/MATLAB Function SOC ' incorporates:
     *  Integrator: '<Root>/Integrator'
     */
    /* MATLAB Function 'MATLAB Function SOC ': '<S2>:1' */
    /* '<S2>:1:3' y = -0.03536*u+100; */
    rtb_y = -0.03536 * PV_vsi_sf_carga_X.Integrator_CSTATE + 100.0;

    /* Outport: '<Root>/SOC' */
    PV_vsi_sf_carga_Y.SOC = rtb_y;

    /* Integrator: '<S9>/integrator' */
    rtb_integrator = PV_vsi_sf_carga_X.integrator_CSTATE;

    /* TransportDelay: '<S9>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = PV_vsi_sf_carga_M->Timing.t[0];
      real_T tMinusDelay = simTime - (0.016666666666666666);
      rtb_TransportDelay = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK.CircularBufSize,
        &PV_vsi_sf_carga_DW.TransportDelay_IWORK.Last,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK.Tail,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK.Head,
        0.0,
        0,
        0);
    }

    if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
      /* Memory: '<S9>/Memory' */
      PV_vsi_sf_carga_B.Memory = PV_vsi_sf_carga_DW.Memory_PreviousInput;
    }

    /* Switch: '<S9>/Switch' incorporates:
     *  Clock: '<S9>/Clock'
     *  Constant: '<S9>/K1'
     *  Gain: '<S9>/Gain'
     *  RelationalOperator: '<S9>/Relational Operator'
     *  Sum: '<S9>/Sum'
     */
    if (PV_vsi_sf_carga_M->Timing.t[0] >= 0.016666666666666666) {
      PV_vsi_sf_carga_B.Switch = (rtb_integrator - rtb_TransportDelay) * 60.0;
    } else {
      PV_vsi_sf_carga_B.Switch = PV_vsi_sf_carga_B.Memory;
    }

    /* End of Switch: '<S9>/Switch' */

    /* Integrator: '<S8>/integrator' */
    rtb_integrator_m = PV_vsi_sf_carga_X.integrator_CSTATE_c;

    /* TransportDelay: '<S8>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_g.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_g.TUbufferPtrs[1];
      real_T simTime = PV_vsi_sf_carga_M->Timing.t[0];
      real_T tMinusDelay = simTime - (0.016666666666666666);
      rtb_TransportDelay_g = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.CircularBufSize,
        &PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Last,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Tail,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Head,
        0.0,
        0,
        0);
    }

    if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
      /* Memory: '<S8>/Memory' */
      PV_vsi_sf_carga_B.Memory_f = PV_vsi_sf_carga_DW.Memory_PreviousInput_j;
    }

    /* Switch: '<S8>/Switch' incorporates:
     *  Clock: '<S8>/Clock'
     *  Constant: '<S8>/K1'
     *  Gain: '<S8>/Gain'
     *  RelationalOperator: '<S8>/Relational Operator'
     *  Sum: '<S8>/Sum'
     */
    if (PV_vsi_sf_carga_M->Timing.t[0] >= 0.016666666666666666) {
      PV_vsi_sf_carga_B.Switch_c = (rtb_integrator_m - rtb_TransportDelay_g) *
        60.0;
    } else {
      PV_vsi_sf_carga_B.Switch_c = PV_vsi_sf_carga_B.Memory_f;
    }

    /* End of Switch: '<S8>/Switch' */

    /* Integrator: '<S13>/integrator' */
    rtb_integrator_e = PV_vsi_sf_carga_X.integrator_CSTATE_i;

    /* TransportDelay: '<S13>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[1];
      real_T simTime = PV_vsi_sf_carga_M->Timing.t[0];
      real_T tMinusDelay = simTime - (0.016666666666666666);
      rtb_TransportDelay_d = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.CircularBufSize,
        &PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Last,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Tail,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Head,
        0.0,
        0,
        0);
    }

    if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
      /* Memory: '<S13>/Memory' */
      PV_vsi_sf_carga_B.Memory_j = PV_vsi_sf_carga_DW.Memory_PreviousInput_i;
    }

    /* Switch: '<S13>/Switch' incorporates:
     *  Clock: '<S13>/Clock'
     *  Constant: '<S13>/K1'
     *  Gain: '<S13>/Gain'
     *  RelationalOperator: '<S13>/Relational Operator'
     *  Sum: '<S13>/Sum'
     */
    if (PV_vsi_sf_carga_M->Timing.t[0] >= 0.016666666666666666) {
      PV_vsi_sf_carga_B.Switch_k = (rtb_integrator_e - rtb_TransportDelay_d) *
        60.0;
    } else {
      PV_vsi_sf_carga_B.Switch_k = PV_vsi_sf_carga_B.Memory_j;
    }

    /* End of Switch: '<S13>/Switch' */

    /* Integrator: '<S12>/integrator' */
    rtb_integrator_o = PV_vsi_sf_carga_X.integrator_CSTATE_b;

    /* TransportDelay: '<S12>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_n.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_n.TUbufferPtrs[1];
      real_T simTime = PV_vsi_sf_carga_M->Timing.t[0];
      real_T tMinusDelay = simTime - (0.016666666666666666);
      rtb_TransportDelay_e = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.CircularBufSize,
        &PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Last,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Tail,
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Head,
        0.0,
        0,
        0);
    }

    if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
      /* Memory: '<S12>/Memory' */
      PV_vsi_sf_carga_B.Memory_m = PV_vsi_sf_carga_DW.Memory_PreviousInput_n;
    }

    /* Switch: '<S12>/Switch' incorporates:
     *  Clock: '<S12>/Clock'
     *  Constant: '<S12>/K1'
     *  Gain: '<S12>/Gain'
     *  RelationalOperator: '<S12>/Relational Operator'
     *  Sum: '<S12>/Sum'
     */
    if (PV_vsi_sf_carga_M->Timing.t[0] >= 0.016666666666666666) {
      PV_vsi_sf_carga_B.Switch_o = (rtb_integrator_o - rtb_TransportDelay_e) *
        60.0;
    } else {
      PV_vsi_sf_carga_B.Switch_o = PV_vsi_sf_carga_B.Memory_m;
    }

    /* End of Switch: '<S12>/Switch' */

    /* Gain: '<S3>/Gain1' incorporates:
     *  ComplexToMagnitudeAngle: '<S4>/Complex to Magnitude-Angle'
     *  ComplexToMagnitudeAngle: '<S5>/Complex to Magnitude-Angle'
     *  Product: '<S3>/Product'
     *  RealImagToComplex: '<S4>/Real-Imag to Complex'
     *  RealImagToComplex: '<S5>/Real-Imag to Complex'
     */
    rtb_ComplextoMagnitudeAngle_o1 = rt_hypotd_snf(PV_vsi_sf_carga_B.Switch,
      PV_vsi_sf_carga_B.Switch_c) * rt_hypotd_snf(PV_vsi_sf_carga_B.Switch_k,
      PV_vsi_sf_carga_B.Switch_o) * 0.5;

    /* Gain: '<S3>/Deg->Rad' incorporates:
     *  ComplexToMagnitudeAngle: '<S4>/Complex to Magnitude-Angle'
     *  ComplexToMagnitudeAngle: '<S5>/Complex to Magnitude-Angle'
     *  Gain: '<S4>/Rad->Deg.'
     *  Gain: '<S5>/Rad->Deg.'
     *  RealImagToComplex: '<S4>/Real-Imag to Complex'
     *  RealImagToComplex: '<S5>/Real-Imag to Complex'
     *  Sum: '<S3>/Sum'
     */
    rtb_ComplextoMagnitudeAngle_o2 = (57.295779513082323 * rt_atan2d_snf
      (PV_vsi_sf_carga_B.Switch_c, PV_vsi_sf_carga_B.Switch) -
      57.295779513082323 * rt_atan2d_snf(PV_vsi_sf_carga_B.Switch_o,
      PV_vsi_sf_carga_B.Switch_k)) * 0.017453292519943295;

    /* Outport: '<Root>/Pm' incorporates:
     *  Product: '<S3>/Product1'
     *  Trigonometry: '<S3>/Trigonometric Function1'
     */
    PV_vsi_sf_carga_Y.Pm = rtb_ComplextoMagnitudeAngle_o1 * cos
      (rtb_ComplextoMagnitudeAngle_o2);

    /* Outport: '<Root>/Qm' incorporates:
     *  Product: '<S3>/Product3'
     *  Trigonometry: '<S3>/Trigonometric Function2'
     */
    PV_vsi_sf_carga_Y.Qm = rtb_ComplextoMagnitudeAngle_o1 * sin
      (rtb_ComplextoMagnitudeAngle_o2);

    /* Outport: '<Root>/Vload1' */
    PV_vsi_sf_carga_Y.Vload1 = PV_vsi_sf_carga_B.TransferFcn3;

    /* Sin: '<Root>/Sine Wave' */
    PV_vsi_sf_carga_B.refvoltage = sin(376.99111843077515 *
      PV_vsi_sf_carga_M->Timing.t[0]) * 170.0;

    /* Derivative: '<Root>/Derivative' */
    if ((PV_vsi_sf_carga_DW.TimeStampA_e >= PV_vsi_sf_carga_M->Timing.t[0]) &&
        (PV_vsi_sf_carga_DW.TimeStampB_a >= PV_vsi_sf_carga_M->Timing.t[0])) {
      rtb_ComplextoMagnitudeAngle_o1 = 0.0;
    } else {
      rtb_ComplextoMagnitudeAngle_o2 = PV_vsi_sf_carga_DW.TimeStampA_e;
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA_n;
      if (PV_vsi_sf_carga_DW.TimeStampA_e < PV_vsi_sf_carga_DW.TimeStampB_a) {
        if (PV_vsi_sf_carga_DW.TimeStampB_a < PV_vsi_sf_carga_M->Timing.t[0]) {
          rtb_ComplextoMagnitudeAngle_o2 = PV_vsi_sf_carga_DW.TimeStampB_a;
          lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB_c;
        }
      } else {
        if (PV_vsi_sf_carga_DW.TimeStampA_e >= PV_vsi_sf_carga_M->Timing.t[0]) {
          rtb_ComplextoMagnitudeAngle_o2 = PV_vsi_sf_carga_DW.TimeStampB_a;
          lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB_c;
        }
      }

      rtb_ComplextoMagnitudeAngle_o1 = (PV_vsi_sf_carga_B.refvoltage - *lastU) /
        (PV_vsi_sf_carga_M->Timing.t[0] - rtb_ComplextoMagnitudeAngle_o2);
    }

    /* End of Derivative: '<Root>/Derivative' */

    /* Sum: '<Root>/Sum3' incorporates:
     *  Gain: '<Root>/Gain'
     *  Sum: '<Root>/Sum2'
     */
    PV_vsi_sf_carga_B.Sum3 = (0.00061 * rtb_ComplextoMagnitudeAngle_o1 +
      rtb_vsicurrent) - rtb_VSIlineZ;

    /* Product: '<S4>/Product' incorporates:
     *  Sin: '<S4>/sin(wt)'
     */
    PV_vsi_sf_carga_B.Product = sin(376.99111843077515 *
      PV_vsi_sf_carga_M->Timing.t[0]) * 2.0 * PV_vsi_sf_carga_B.TransferFcn3;

    /* Product: '<S4>/Product1' incorporates:
     *  Sin: '<S4>/cos(wt)'
     */
    PV_vsi_sf_carga_B.Product1 = sin(376.99111843077515 *
      PV_vsi_sf_carga_M->Timing.t[0] + 1.5707963267948966) * 2.0 *
      PV_vsi_sf_carga_B.TransferFcn3;

    /* Sum: '<Root>/Sum6' incorporates:
     *  Inport: '<Root>/i1'
     *  Inport: '<Root>/i2'
     */
    PV_vsi_sf_carga_B.Sum6 = (PV_vsi_sf_carga_U.i1 + PV_vsi_sf_carga_U.i2) +
      rtb_vsicurrent;

    /* Product: '<S5>/Product' incorporates:
     *  Sin: '<S5>/sin(wt)'
     */
    PV_vsi_sf_carga_B.Product_c = sin(376.99111843077515 *
      PV_vsi_sf_carga_M->Timing.t[0]) * 2.0 * PV_vsi_sf_carga_B.Sum6;

    /* Product: '<S5>/Product1' incorporates:
     *  Sin: '<S5>/cos(wt)'
     */
    PV_vsi_sf_carga_B.Product1_g = sin(376.99111843077515 *
      PV_vsi_sf_carga_M->Timing.t[0] + 1.5707963267948966) * 2.0 *
      PV_vsi_sf_carga_B.Sum6;

    /* Sum: '<Root>/Sum4' incorporates:
     *  Gain: '<Root>/Gain1'
     *  Gain: '<Root>/Gain4'
     *  Gain: '<S1>/Gain2'
     *  Lookup_n-D: '<Root>/1-D Lookup Table2'
     *  Product: '<Root>/Product2'
     *  Sum: '<S1>/Sum5'
     *  TransferFcn: '<S1>/Transfer Fcn2'
     */
    PV_vsi_sf_carga_B.Sum4 = ((2.0 * PV_vsi_sf_carga_X.TransferFcn2_CSTATE[0] +
      0.0 * PV_vsi_sf_carga_X.TransferFcn2_CSTATE[1]) + 0.002 *
      PV_vsi_sf_carga_B.Sum3) * 2.0 * (2.0 * look1_binlxpw(rtb_y,
      PV_vsi_sf_carga_ConstP.uDLookupTable2_bp01Data,
      PV_vsi_sf_carga_ConstP.uDLookupTable2_tableData, 8U)) -
      PV_vsi_sf_carga_B.TransferFcn3;

    /* Sum: '<Root>/Sum7' incorporates:
     *  Constant: '<Root>/Current Panel'
     */
    PV_vsi_sf_carga_B.Sum7 = rtb_VSIlineZ + 1.5;
  }

  if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative1' */
    if (PV_vsi_sf_carga_DW.TimeStampA == (rtInf)) {
      PV_vsi_sf_carga_DW.TimeStampA = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA;
    } else if (PV_vsi_sf_carga_DW.TimeStampB == (rtInf)) {
      PV_vsi_sf_carga_DW.TimeStampB = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB;
    } else if (PV_vsi_sf_carga_DW.TimeStampA < PV_vsi_sf_carga_DW.TimeStampB) {
      PV_vsi_sf_carga_DW.TimeStampA = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA;
    } else {
      PV_vsi_sf_carga_DW.TimeStampB = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB;
    }

    *lastU = PV_vsi_sf_carga_B.TransferFcn3;

    /* End of Update for Derivative: '<Root>/Derivative1' */

    /* Update for TransportDelay: '<S9>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = PV_vsi_sf_carga_M->Timing.t[0];
      PV_vsi_sf_carga_DW.TransportDelay_IWORK.Head =
        ((PV_vsi_sf_carga_DW.TransportDelay_IWORK.Head <
          (PV_vsi_sf_carga_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (PV_vsi_sf_carga_DW.TransportDelay_IWORK.Head+1) : 0);
      if (PV_vsi_sf_carga_DW.TransportDelay_IWORK.Head ==
          PV_vsi_sf_carga_DW.TransportDelay_IWORK.Tail) {
        PV_vsi_sf_carga_DW.TransportDelay_IWORK.Tail =
          ((PV_vsi_sf_carga_DW.TransportDelay_IWORK.Tail <
            (PV_vsi_sf_carga_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
           (PV_vsi_sf_carga_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[PV_vsi_sf_carga_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[PV_vsi_sf_carga_DW.TransportDelay_IWORK.Head] = rtb_integrator;
    }

    if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
      /* Update for Memory: '<S9>/Memory' */
      PV_vsi_sf_carga_DW.Memory_PreviousInput = PV_vsi_sf_carga_B.Switch;
    }

    /* Update for TransportDelay: '<S8>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_g.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_g.TUbufferPtrs[1];
      real_T simTime = PV_vsi_sf_carga_M->Timing.t[0];
      PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Head =
        ((PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Head <
          (PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.CircularBufSize-1)) ?
         (PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Head+1) : 0);
      if (PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Head ==
          PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Tail) {
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Tail =
          ((PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Tail <
            (PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.CircularBufSize-1)) ?
           (PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Tail+1) : 0);
      }

      (*tBuffer)[PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Head] = simTime;
      (*uBuffer)[PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Head] =
        rtb_integrator_m;
    }

    if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
      /* Update for Memory: '<S8>/Memory' */
      PV_vsi_sf_carga_DW.Memory_PreviousInput_j = PV_vsi_sf_carga_B.Switch_c;
    }

    /* Update for TransportDelay: '<S13>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[1];
      real_T simTime = PV_vsi_sf_carga_M->Timing.t[0];
      PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Head =
        ((PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Head <
          (PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.CircularBufSize-1)) ?
         (PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Head+1) : 0);
      if (PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Head ==
          PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Tail) {
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Tail =
          ((PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Tail <
            (PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.CircularBufSize-1)) ?
           (PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Tail+1) : 0);
      }

      (*tBuffer)[PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Head] = simTime;
      (*uBuffer)[PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Head] =
        rtb_integrator_e;
    }

    if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
      /* Update for Memory: '<S13>/Memory' */
      PV_vsi_sf_carga_DW.Memory_PreviousInput_i = PV_vsi_sf_carga_B.Switch_k;
    }

    /* Update for TransportDelay: '<S12>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_n.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &PV_vsi_sf_carga_DW.TransportDelay_PWORK_n.TUbufferPtrs[1];
      real_T simTime = PV_vsi_sf_carga_M->Timing.t[0];
      PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Head =
        ((PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Head <
          (PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.CircularBufSize-1)) ?
         (PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Head+1) : 0);
      if (PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Head ==
          PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Tail) {
        PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Tail =
          ((PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Tail <
            (PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.CircularBufSize-1)) ?
           (PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Tail+1) : 0);
      }

      (*tBuffer)[PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Head] = simTime;
      (*uBuffer)[PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Head] =
        rtb_integrator_o;
    }

    if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
      /* Update for Memory: '<S12>/Memory' */
      PV_vsi_sf_carga_DW.Memory_PreviousInput_n = PV_vsi_sf_carga_B.Switch_o;
    }

    /* Update for Derivative: '<Root>/Derivative' */
    if (PV_vsi_sf_carga_DW.TimeStampA_e == (rtInf)) {
      PV_vsi_sf_carga_DW.TimeStampA_e = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA_n;
    } else if (PV_vsi_sf_carga_DW.TimeStampB_a == (rtInf)) {
      PV_vsi_sf_carga_DW.TimeStampB_a = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB_c;
    } else if (PV_vsi_sf_carga_DW.TimeStampA_e < PV_vsi_sf_carga_DW.TimeStampB_a)
    {
      PV_vsi_sf_carga_DW.TimeStampA_e = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeA_n;
    } else {
      PV_vsi_sf_carga_DW.TimeStampB_a = PV_vsi_sf_carga_M->Timing.t[0];
      lastU = &PV_vsi_sf_carga_DW.LastUAtTimeB_c;
    }

    *lastU = PV_vsi_sf_carga_B.refvoltage;

    /* End of Update for Derivative: '<Root>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(PV_vsi_sf_carga_M)) {
    rt_ertODEUpdateContinuousStates(&PV_vsi_sf_carga_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++PV_vsi_sf_carga_M->Timing.clockTick0;
    PV_vsi_sf_carga_M->Timing.t[0] = rtsiGetSolverStopTime
      (&PV_vsi_sf_carga_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      PV_vsi_sf_carga_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void PV_vsi_sf_carga_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_PV_vsi_sf_carga_T *_rtXdot;
  _rtXdot = ((XDot_PV_vsi_sf_carga_T *) PV_vsi_sf_carga_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/VSI  line Z' */
  _rtXdot->VSIlineZ_CSTATE = 0.0;
  _rtXdot->VSIlineZ_CSTATE += -0.03333333333333334 *
    PV_vsi_sf_carga_X.VSIlineZ_CSTATE;
  _rtXdot->VSIlineZ_CSTATE += PV_vsi_sf_carga_B.Sum4;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn3' */
  _rtXdot->TransferFcn3_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn3_CSTATE[0] += -75.357950263752812 *
    PV_vsi_sf_carga_X.TransferFcn3_CSTATE[0];
  _rtXdot->TransferFcn3_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn3_CSTATE[0] += -72.459567561300787 *
    PV_vsi_sf_carga_X.TransferFcn3_CSTATE[1];
  _rtXdot->TransferFcn3_CSTATE[1] += PV_vsi_sf_carga_X.TransferFcn3_CSTATE[0];
  _rtXdot->TransferFcn3_CSTATE[0] += PV_vsi_sf_carga_B.Sum6;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  lsat = (PV_vsi_sf_carga_X.Integrator_CSTATE <= 0.0);
  usat = (PV_vsi_sf_carga_X.Integrator_CSTATE >= 1.0);
  if (((!lsat) && (!usat)) || (lsat && (PV_vsi_sf_carga_B.Sum7 > 0.0)) || (usat &&
       (PV_vsi_sf_carga_B.Sum7 < 0.0))) {
    _rtXdot->Integrator_CSTATE = PV_vsi_sf_carga_B.Sum7;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<Root>/Integrator' */

  /* Derivatives for Integrator: '<S9>/integrator' */
  _rtXdot->integrator_CSTATE = PV_vsi_sf_carga_B.Product;

  /* Derivatives for Integrator: '<S8>/integrator' */
  _rtXdot->integrator_CSTATE_c = PV_vsi_sf_carga_B.Product1;

  /* Derivatives for Integrator: '<S13>/integrator' */
  _rtXdot->integrator_CSTATE_i = PV_vsi_sf_carga_B.Product_c;

  /* Derivatives for Integrator: '<S12>/integrator' */
  _rtXdot->integrator_CSTATE_b = PV_vsi_sf_carga_B.Product1_g;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn2' */
  _rtXdot->TransferFcn2_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += -2.0 *
    PV_vsi_sf_carga_X.TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn2_CSTATE[0] += -142122.30337568672 *
    PV_vsi_sf_carga_X.TransferFcn2_CSTATE[1];
  _rtXdot->TransferFcn2_CSTATE[1] += PV_vsi_sf_carga_X.TransferFcn2_CSTATE[0];
  _rtXdot->TransferFcn2_CSTATE[0] += PV_vsi_sf_carga_B.Sum3;
}

/* Model initialize function */
void PV_vsi_sf_carga_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)PV_vsi_sf_carga_M, 0,
                sizeof(RT_MODEL_PV_vsi_sf_carga_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PV_vsi_sf_carga_M->solverInfo,
                          &PV_vsi_sf_carga_M->Timing.simTimeStep);
    rtsiSetTPtr(&PV_vsi_sf_carga_M->solverInfo, &rtmGetTPtr(PV_vsi_sf_carga_M));
    rtsiSetStepSizePtr(&PV_vsi_sf_carga_M->solverInfo,
                       &PV_vsi_sf_carga_M->Timing.stepSize0);
    rtsiSetdXPtr(&PV_vsi_sf_carga_M->solverInfo, &PV_vsi_sf_carga_M->derivs);
    rtsiSetContStatesPtr(&PV_vsi_sf_carga_M->solverInfo, (real_T **)
                         &PV_vsi_sf_carga_M->contStates);
    rtsiSetNumContStatesPtr(&PV_vsi_sf_carga_M->solverInfo,
      &PV_vsi_sf_carga_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&PV_vsi_sf_carga_M->solverInfo,
      &PV_vsi_sf_carga_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&PV_vsi_sf_carga_M->solverInfo,
      &PV_vsi_sf_carga_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&PV_vsi_sf_carga_M->solverInfo,
      &PV_vsi_sf_carga_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&PV_vsi_sf_carga_M->solverInfo, (&rtmGetErrorStatus
      (PV_vsi_sf_carga_M)));
    rtsiSetRTModelPtr(&PV_vsi_sf_carga_M->solverInfo, PV_vsi_sf_carga_M);
  }

  rtsiSetSimTimeStep(&PV_vsi_sf_carga_M->solverInfo, MAJOR_TIME_STEP);
  PV_vsi_sf_carga_M->intgData.y = PV_vsi_sf_carga_M->odeY;
  PV_vsi_sf_carga_M->intgData.f[0] = PV_vsi_sf_carga_M->odeF[0];
  PV_vsi_sf_carga_M->intgData.f[1] = PV_vsi_sf_carga_M->odeF[1];
  PV_vsi_sf_carga_M->intgData.f[2] = PV_vsi_sf_carga_M->odeF[2];
  PV_vsi_sf_carga_M->intgData.f[3] = PV_vsi_sf_carga_M->odeF[3];
  PV_vsi_sf_carga_M->contStates = ((X_PV_vsi_sf_carga_T *) &PV_vsi_sf_carga_X);
  rtsiSetSolverData(&PV_vsi_sf_carga_M->solverInfo, (void *)
                    &PV_vsi_sf_carga_M->intgData);
  rtsiSetSolverName(&PV_vsi_sf_carga_M->solverInfo,"ode4");
  rtmSetTPtr(PV_vsi_sf_carga_M, &PV_vsi_sf_carga_M->Timing.tArray[0]);
  PV_vsi_sf_carga_M->Timing.stepSize0 = 0.0001;

  /* block I/O */
  (void) memset(((void *) &PV_vsi_sf_carga_B), 0,
                sizeof(B_PV_vsi_sf_carga_T));

  /* states (continuous) */
  {
    (void) memset((void *)&PV_vsi_sf_carga_X, 0,
                  sizeof(X_PV_vsi_sf_carga_T));
  }

  /* states (dwork) */
  (void) memset((void *)&PV_vsi_sf_carga_DW, 0,
                sizeof(DW_PV_vsi_sf_carga_T));

  /* external inputs */
  (void)memset((void *)&PV_vsi_sf_carga_U, 0, sizeof(ExtU_PV_vsi_sf_carga_T));

  /* external outputs */
  (void) memset((void *)&PV_vsi_sf_carga_Y, 0,
                sizeof(ExtY_PV_vsi_sf_carga_T));

  /* Start for TransportDelay: '<S9>/Transport Delay' */
  {
    real_T *pBuffer = &PV_vsi_sf_carga_DW.TransportDelay_RWORK.TUbufferArea[0];
    PV_vsi_sf_carga_DW.TransportDelay_IWORK.Tail = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK.Head = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK.Last = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = PV_vsi_sf_carga_M->Timing.t[0];
    PV_vsi_sf_carga_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer
      [0];
    PV_vsi_sf_carga_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer
      [8192];
  }

  /* Start for TransportDelay: '<S8>/Transport Delay' */
  {
    real_T *pBuffer = &PV_vsi_sf_carga_DW.TransportDelay_RWORK_g.TUbufferArea[0];
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Tail = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Head = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.Last = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_n.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = PV_vsi_sf_carga_M->Timing.t[0];
    PV_vsi_sf_carga_DW.TransportDelay_PWORK_g.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    PV_vsi_sf_carga_DW.TransportDelay_PWORK_g.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S13>/Transport Delay' */
  {
    real_T *pBuffer = &PV_vsi_sf_carga_DW.TransportDelay_RWORK_j.TUbufferArea[0];
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Tail = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Head = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.Last = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_ng.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = PV_vsi_sf_carga_M->Timing.t[0];
    PV_vsi_sf_carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    PV_vsi_sf_carga_DW.TransportDelay_PWORK_f.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* Start for TransportDelay: '<S12>/Transport Delay' */
  {
    real_T *pBuffer = &PV_vsi_sf_carga_DW.TransportDelay_RWORK_g1.TUbufferArea[0];
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Tail = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Head = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.Last = 0;
    PV_vsi_sf_carga_DW.TransportDelay_IWORK_d.CircularBufSize = 8192;
    pBuffer[0] = 0.0;
    pBuffer[8192] = PV_vsi_sf_carga_M->Timing.t[0];
    PV_vsi_sf_carga_DW.TransportDelay_PWORK_n.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    PV_vsi_sf_carga_DW.TransportDelay_PWORK_n.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* InitializeConditions for TransferFcn: '<Root>/VSI  line Z' */
  PV_vsi_sf_carga_X.VSIlineZ_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  PV_vsi_sf_carga_DW.TimeStampA = (rtInf);
  PV_vsi_sf_carga_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  PV_vsi_sf_carga_X.Integrator_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S9>/integrator' */
  PV_vsi_sf_carga_X.integrator_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S9>/Memory' */
  PV_vsi_sf_carga_DW.Memory_PreviousInput = 1.0;

  /* InitializeConditions for Integrator: '<S8>/integrator' */
  PV_vsi_sf_carga_X.integrator_CSTATE_c = 0.0;

  /* InitializeConditions for Integrator: '<S13>/integrator' */
  PV_vsi_sf_carga_X.integrator_CSTATE_i = 0.0;

  /* InitializeConditions for Memory: '<S13>/Memory' */
  PV_vsi_sf_carga_DW.Memory_PreviousInput_i = 1.0;

  /* InitializeConditions for Integrator: '<S12>/integrator' */
  PV_vsi_sf_carga_X.integrator_CSTATE_b = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  PV_vsi_sf_carga_DW.TimeStampA_e = (rtInf);
  PV_vsi_sf_carga_DW.TimeStampB_a = (rtInf);

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn3' */
  PV_vsi_sf_carga_X.TransferFcn3_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2' */
  PV_vsi_sf_carga_X.TransferFcn2_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn3' */
  PV_vsi_sf_carga_X.TransferFcn3_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn2' */
  PV_vsi_sf_carga_X.TransferFcn2_CSTATE[1] = 0.0;
}

/* Model terminate function */
void PV_vsi_sf_carga_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
