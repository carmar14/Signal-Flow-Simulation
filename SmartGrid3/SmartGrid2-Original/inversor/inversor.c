/*
 * File: inversor.c
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

#include "inversor.h"
#include "inversor_private.h"
#include <stdio.h>

/* Block signals (auto storage) */
B_inversor_T inversor_B;

/* Continuous states */
X_inversor_T inversor_X;

/* Block states (auto storage) */
DW_inversor_T inversor_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_inversor_T inversor_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_inversor_T inversor_Y;

/* Real-time model */
RT_MODEL_inversor_T inversor_M_;
RT_MODEL_inversor_T *const inversor_M = &inversor_M_;



//Vairables

double Vdc;
double U1;
double U2;
double Out;
double salida;
double U;




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


void guardarVdc(double vdc)
{
	Vdc=vdc;
	
}

void guardarU(double u)
{
	U1=u;
	U=U1;
	//printf("El U: %3.2f \n",U);
}

void guardarU2(double u)
{
	U2=u;
	U=U2;
	//printf("El U: %3.2f \n",U);
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

/* Simplified version of numjac.cpp, for use with RTW. */
void local_numjac( RTWSolverInfo *si, real_T *y, const real_T *Fty, real_T *fac,
                  real_T *dFdy )
{
  /* constants */
  real_T THRESH = 1e-6;
  real_T EPS = 2.2e-16;                /* utGetEps(); */
  real_T BL = pow(EPS, 0.75);
  real_T BU = pow(EPS, 0.25);
  real_T FACMIN = pow(EPS, 0.78);
  real_T FACMAX = 0.1;
  int_T nx = 7;
  real_T *x = rtsiGetContStates(si);
  real_T del;
  real_T difmax;
  real_T FdelRowmax;
  real_T temp;
  real_T Fdiff;
  real_T maybe;
  real_T xscale;
  real_T fscale;
  real_T *p;
  int_T rowmax;
  int_T i,j;
  if (x != y)
    (void) memcpy(x, y,
                  (uint_T)nx*sizeof(real_T));
  rtsiSetSolverComputingJacobian(si,true);
  for (p = dFdy, j = 0; j < nx; j++, p += nx) {
    /* Select an increment del for a difference approximation to
       column j of dFdy.  The vector fac accounts for experience
       gained in previous calls to numjac. */
    xscale = fabs(x[j]);
    if (xscale < THRESH)
      xscale = THRESH;
    temp = (x[j] + fac[j]*xscale);
    del = temp - y[j];
    while (del == 0.0) {
      if (fac[j] < FACMAX) {
        fac[j] *= 100.0;
        if (fac[j] > FACMAX)
          fac[j] = FACMAX;
        temp = (x[j] + fac[j]*xscale);
        del = temp - x[j];
      } else {
        del = THRESH;                  /* thresh is nonzero */
        break;
      }
    }

    /* Keep del pointing into region. */
    if (Fty[j] >= 0.0)
      del = fabs(del);
    else
      del = -fabs(del);

    /* Form a difference approximation to column j of dFdy. */
    temp = x[j];
    x[j] += del;
    
    Out=inversor_step(Vdc,U);
    
    rtsiSetdX(si,p);
    inversor_derivatives();
    x[j] = temp;
    difmax = 0.0;
    rowmax = 0;
    FdelRowmax = p[0];
    temp = 1.0 / del;
    for (i = 0; i < nx; i++) {
      Fdiff = p[i] - Fty[i];
      maybe = fabs(Fdiff);
      if (maybe > difmax) {
        difmax = maybe;
        rowmax = i;
        FdelRowmax = p[i];
      }

      p[i] = temp * Fdiff;
    }

    /* Adjust fac for next call to numjac. */
    if (((FdelRowmax != 0.0) && (Fty[rowmax] != 0.0)) || (difmax == 0.0)) {
      fscale = fabs(FdelRowmax);
      if (fscale < fabs(Fty[rowmax]))
        fscale = fabs(Fty[rowmax]);
      if (difmax <= BL*fscale) {
        /* The difference is small, so increase the increment. */
        fac[j] *= 10.0;
        if (fac[j] > FACMAX)
          fac[j] = FACMAX;
      } else if (difmax > BU*fscale) {
        /* The difference is large, so reduce the increment. */
        fac[j] *= 0.1;
        if (fac[j] < FACMIN)
          fac[j] = FACMIN;
      }
    }
  }

  rtsiSetSolverComputingJacobian(si,false);
}                                      /* end local_numjac */

/*
 * This function updates continuous states using the ODE14x fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static int_T rt_ODE14x_N[4] = { 12, 8, 6, 4 };

  time_T t0 = rtsiGetT(si);
  time_T t1 = t0;
  time_T h = rtsiGetStepSize(si);
  real_T *x1 = rtsiGetContStates(si);
  int_T order = rtsiGetSolverExtrapolationOrder(si);
  int_T numIter = rtsiGetSolverNumberNewtonIterations(si);
  ODE14X_IntgData *id = (ODE14X_IntgData *)rtsiGetSolverData(si);
  real_T *x0 = id->x0;
  real_T *f0 = id->f0;
  real_T *x1start = id->x1start;
  real_T *f1 = id->f1;
  real_T *Delta = id->Delta;
  real_T *E = id->E;
  real_T *fac = id->fac;
  real_T *dfdx = id->DFDX;
  real_T *W = id->W;
  int_T *pivots = id->pivots;
  real_T *xtmp = id->xtmp;
  real_T *ztmp = id->ztmp;
  int_T *N = &(rt_ODE14x_N[0]);
  int_T i,j,k,iter;
  int_T nx = 7;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(x0, x1,
                (uint_T)nx*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */

  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  inversor_derivatives();
  local_numjac(si,x0,f0,fac,dfdx );
  for (j = 0; j < order; j++) {
    real_T *p;
    real_T hN = h/N[j];

    /* Get the iteration matrix and solution at t0 */

    /* [L,U] = lu(M - hN*J) */
    (void) memcpy(W, dfdx,
                  (uint_T)nx*nx*sizeof(real_T));
    for (p = W, i = 0; i < nx*nx; i++, p++) {
      *p *= (-hN);
    }

    for (p = W, i = 0; i < nx; i++, p += (nx+1)) {
      *p += 1.0;
    }

    rt_lu_real(W, nx,
               pivots);

    /* First Newton's iteration at t0. */
    /* rhs = hN*f0 */
    for (i = 0; i < nx; i++) {
      Delta[i] = hN*f0[i];
    }

    /* Delta = (U \ (L \ rhs)) */
    rt_ForwardSubstitutionRR_Dbl(W, Delta,
      f1, nx,
      1, pivots,
      1);
    rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
      Delta, nx,
      1, 0);

    /* ytmp = y0 + Delta
       ztmp = (ytmp-y0)/h
     */
    (void) memcpy(x1, x0,
                  (uint_T)nx*sizeof(real_T));
    for (i = 0; i < nx; i++) {
      x1[i] += Delta[i];
      ztmp[i] = Delta[i]/hN;
    }

    /* Additional Newton's iterations, if desired.
       for iter = 2:NewtIter
       rhs = hN*feval(odefun,tn,ytmp,extraArgs{:}) - M*(ytmp - yn);
       if statedepM   % only for state dep. Mdel ~= 0
       Mdel = M - feval(massfun,tn,ytmp);
       rhs = rhs + Mdel*ztmp*h;
       end
       Delta = ( U \ ( L \ rhs ) );
       ytmp = ytmp + Delta;
       ztmp = (ytmp - yn)/h
       end
     */
    rtsiSetT(si, t0);
    rtsiSetdX(si, f1);
    for (iter = 1; iter < numIter; iter++) {
      //inversor_step();
      Out=inversor_step(Vdc,U);
      inversor_derivatives();
      for (i = 0; i < nx; i++) {
        Delta[i] = hN*f1[i];
        xtmp[i] = x1[i] - x0[i];
      }

      /* rhs = hN*f(tn,ytmp) - (ytmp-yn) */
      for (i = 0; i < nx; i++) {
        Delta[i] -= xtmp[i];
      }

      rt_ForwardSubstitutionRR_Dbl(W, Delta,
        f1, nx,
        1, pivots,
        1);
      rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
        Delta, nx,
        1, 0);

      /* ytmp = ytmp + delta
         ztmp = (ytmp - yn)/h
       */
      for (i = 0; i < nx; i++) {
        x1[i] += Delta[i];
        ztmp[i] = (x1[i] - x0[i])/hN;
      }
    }

    /* Steps from t0+hN to t1 -- subintegration of N(j) steps for extrapolation
       ttmp = t0;
       for i = 2:N(j)
       ttmp = ttmp + hN
       ytmp0 = ytmp;
       for iter = 1:NewtIter
       rhs = (ytmp0 - ytmp) + hN*feval(odefun,ttmp,ytmp,extraArgs{:});
       Delta = ( U \ ( L \ rhs ) );
       ytmp = ytmp + Delta;
       end
       end
     */
    for (k = 1; k < N[j]; k++) {
      t1 = t0 + k*hN;
      (void) memcpy(x1start, x1,
                    (uint_T)nx*sizeof(real_T));
      rtsiSetT(si, t1);
      rtsiSetdX(si, f1);
      for (iter = 0; iter < numIter; iter++) {
        //inversor_step();
        Out=inversor_step(Vdc,U);
        inversor_derivatives();
        if (iter == 0) {
          for (i = 0; i < nx; i++) {
            Delta[i] = hN*f1[i];
          }
        } else {
          for (i = 0; i < nx; i++) {
            Delta[i] = hN*f1[i];
            xtmp[i] = (x1[i]-x1start[i]);
          }

          /* rhs = hN*f(tn,ytmp) - M*(ytmp-yn) */
          for (i = 0; i < nx; i++) {
            Delta[i] -= xtmp[i];
          }
        }

        rt_ForwardSubstitutionRR_Dbl(W, Delta,
          f1, nx,
          1, pivots,
          1);
        rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
          Delta, nx,
          1, 0);

        /* ytmp = ytmp + Delta
           ztmp = (ytmp - ytmp0)/h
         */
        for (i = 0; i < nx; i++) {
          x1[i] += Delta[i];
          ztmp[i] = (x1[i] - x1start[i])/hN;
        }
      }
    }

    /* Extrapolate to order j
       E(:,j) = ytmp
       for k = j:-1:2
       coef = N(k-1)/(N(j) - N(k-1))
       E(:,k-1) = E(:,k) + coef*( E(:,k) - E(:,k-1) )
       end
     */
    (void) memcpy(&(E[nx*j]), x1,
                  (uint_T)nx*sizeof(real_T));
    for (k = j; k > 0; k--) {
      real_T coef = (real_T)(N[k-1]) / (N[j]-N[k-1]);
      for (i = 0; i < nx; i++) {
        x1[i] = E[nx*k+i] + coef*(E[nx*k+i] - E[nx*(k-1)+i]);
      }

      (void) memcpy(&(E[nx*(k-1)]), x1,
                    (uint_T)nx*sizeof(real_T));
    }
  }

  /* x1 = E(:,1); */
  (void) memcpy(x1, E,
                (uint_T)nx*sizeof(real_T));

  /* t1 = t0 + h; */
  rtsiSetT(si,rtsiGetSolverStopTime(si));
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T q;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    y = (rtNaN);
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    q = fabs(u0 / u1);
    if (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }

  return y;
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  boolean_T yEq;
  real_T q;
  y = u0;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    if (u1 != 0.0) {
      y = (rtNaN);
    }
  } else if (u0 == 0.0) {
    y = u1 * 0.0;
  } else {
    if (u1 != 0.0) {
      y = fmod(u0, u1);
      yEq = (y == 0.0);
      if ((!yEq) && (u1 > floor(u1))) {
        q = fabs(u0 / u1);
        yEq = (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q);
      }

      if (yEq) {
        y = u1 * 0.0;
      } else {
        if ((u0 < 0.0) != (u1 < 0.0)) {
          y += u1;
        }
      }
    }
  }

  return y;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
double inversor_step(double vdc, double u)
{
  if (rtmIsMajorTimeStep(inversor_M)) {
    /* set solver stop time */
    if (!(inversor_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&inversor_M->solverInfo,
                            ((inversor_M->Timing.clockTickH0 + 1) *
        inversor_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&inversor_M->solverInfo,
                            ((inversor_M->Timing.clockTick0 + 1) *
        inversor_M->Timing.stepSize0 + inversor_M->Timing.clockTickH0 *
        inversor_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(inversor_M)) {
    inversor_M->Timing.t[0] = rtsiGetT(&inversor_M->solverInfo);
  }

  {
    real_T *lastU;
    real_T riseValLimit;
    real_T rtb_Step;
    boolean_T rtb_RelationalOperator;
    real_T rtb_TrigonometricFunction;
    uint8_T rtb_Gain;
    uint8_T rtb_Gain1;
    real_T StateSpace;
    real_T Sum1;
    real_T Sum2_p;
    
    //printf("Tiempo %5.2f\n",rtmIsMajorTimeStep(inversor_M));
    if (rtmIsMajorTimeStep(inversor_M)) {
    //if (true) {
      /* S-Function (sfun_spssw_discc): '<S52>/State-Space' incorporates:
       *  Constant: '<S54>/SwitchCurrents'
       *  Inport: '<Root>/Vdc'
       */

      /* S-Function block: <S52>/State-Space */
      {
        real_T accum;

        /* Circuit has switches */
        int_T *switch_status = (int_T*)
          inversor_DW.StateSpace_PWORK.SWITCH_STATUS;
        int_T *switch_status_init = (int_T*)
          inversor_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;
        int_T *SwitchChange = (int_T*) inversor_DW.StateSpace_PWORK.SW_CHG;
        int_T *gState = (int_T*) inversor_DW.StateSpace_PWORK.G_STATE;
        real_T *yswitch = (real_T*)inversor_DW.StateSpace_PWORK.Y_SWITCH;
        int_T *switchTypes = (int_T*) inversor_DW.StateSpace_PWORK.SWITCH_TYPES;
        int_T *idxOutSw = (int_T*) inversor_DW.StateSpace_PWORK.IDX_OUT_SW;
        real_T *DxCol = (real_T*)inversor_DW.StateSpace_PWORK.DX_COL;
        real_T *tmp2 = (real_T*)inversor_DW.StateSpace_PWORK.TMP2;
        real_T *BDcol = (real_T*)inversor_DW.StateSpace_PWORK.BD_COL;
        real_T *tmp1 = (real_T*)inversor_DW.StateSpace_PWORK.TMP1;
        real_T *uswlast = (real_T*)inversor_DW.StateSpace_PWORK.USWLAST;
        int_T newState;
        int_T swChanged = 0;
        int loopsToDo = 20;
        real_T temp;

        /* keep an initial copy of switch_status*/
        memcpy(switch_status_init, switch_status, 8 * sizeof(int_T));
        memcpy(uswlast, &inversor_B.StateSpace_o1[0], 8*sizeof(real_T));
        do {
          if (loopsToDo == 1) {        /* Need to reset some variables: */
            swChanged = 0;

            /* return to the original switch status*/
            {
              int_T i1;
              for (i1=0; i1 < 8; i1++) {
                swChanged = ((SwitchChange[i1] = switch_status_init[i1] -
                              switch_status[i1]) != 0) ? 1 : swChanged;
                switch_status[i1] = switch_status_init[i1];
              }
            }
          } else {
            /*
             * Compute outputs:
             * ---------------
             */
            real_T *Cs = (real_T*)inversor_DW.StateSpace_PWORK.CS;
            real_T *Ds = (real_T*)inversor_DW.StateSpace_PWORK.DS;

            {
              int_T i1;
              real_T *y0 = &inversor_B.StateSpace_o1[0];
              for (i1=0; i1 < 11; i1++) {
                accum = 0.0;
                accum += *(Cs++) * inversor_DW.StateSpace_DSTATE[0];
                accum += *(Cs++) * inversor_DW.StateSpace_DSTATE[1];
                accum += *(Cs++) * inversor_DW.StateSpace_DSTATE[2];

                {
                  int_T i2;
                  const real_T *u0 = inversor_ConstP.SwitchCurrents_Value;
                  for (i2=0; i2 < 8; i2++) {
                    accum += *(Ds++) * u0[i2];
                  }

                  //accum += *(Ds++) * inversor_U.Vdc;
                  accum += *(Ds++) * vdc;//340;
                }

                y0[i1] = accum;
              }
            }

            swChanged = 0;

            {
              int_T i1;
              real_T *y0 = &inversor_B.StateSpace_o1[0];
              for (i1=0; i1 < 8; i1++) {
                switch (switchTypes[i1]) {
                 case 1 :              /* Ideal switch */
                  newState = gState[i1] > 0 ? 1 : 0;
                  break;

                 case 3 :              /* Diodes */
                  newState = y0[i1] > 0.0 ? 1 : ((y0[i1] < 0.0) ? 0 :
                    switch_status[i1]);
                  break;
                }

                swChanged = ((SwitchChange[i1] = newState - switch_status[i1])
                             != 0) ? 1 : swChanged;
                switch_status[i1] = newState;/* Keep new state */
              }
            }
          }

          /*
           * Compute new As, Bs, Cs and Ds matrixes:
           * --------------------------------------
           */
          if (swChanged) {
            real_T *As = (real_T*)inversor_DW.StateSpace_PWORK.AS;
            real_T *Cs = (real_T*)inversor_DW.StateSpace_PWORK.CS;
            real_T *Bs = (real_T*)inversor_DW.StateSpace_PWORK.BS;
            real_T *Ds = (real_T*)inversor_DW.StateSpace_PWORK.DS;
            real_T a1;

            {
              int_T i1;
              for (i1=0; i1 < 8; i1++) {
                if (SwitchChange[i1] != 0) {
                  a1 = yswitch[i1]*SwitchChange[i1];
                  temp = 1/(1-Ds[i1*10]*a1);

                  {
                    int_T i2;
                    for (i2=0; i2 < 11; i2++) {
                      DxCol[i2]= Ds[i2 * 9 + i1]*temp*a1;
                    }
                  }

                  DxCol[i1] = temp;
                  BDcol[0]= Bs[0 + i1]*a1;
                  BDcol[1]= Bs[9 + i1]*a1;
                  BDcol[2]= Bs[18 + i1]*a1;

                  /* Copy row nSw of Cs into tmp1 and zero it out in Cs */
                  memcpy(tmp1, &Cs[i1 * 3], 3 * sizeof(real_T));
                  memset(&Cs[i1 * 3], '\0', 3 * sizeof(real_T));

                  /* Copy row nSw of Ds into tmp2 and zero it out in Ds */
                  memcpy(tmp2, &Ds[i1 * 9], 9 * sizeof(real_T));
                  memset(&Ds[i1 * 9], '\0', 9 * sizeof(real_T));

                  /* Cs = Cs + DxCol * tmp1, Ds = Ds + DxCol * tmp2 *******************/
                  {
                    int_T i2;
                    for (i2=0; i2 < 11; i2++) {
                      a1 = DxCol[i2];
                      Cs[i2 * 3 + 0] += a1 * tmp1[0];
                      Cs[i2 * 3 + 1] += a1 * tmp1[1];
                      Cs[i2 * 3 + 2] += a1 * tmp1[2];

                      {
                        int_T i3;
                        for (i3=0; i3 < 9; i3++) {
                          Ds[i2 * 9 + i3] += a1 * tmp2[i3];
                        }
                      }
                    }
                  }

                  /* As = As + BdCol*Cs(nSw,:), Bs = Bs + BdCol*Ds(nSw,:) *************/
                  a1 = BDcol[0];
                  As[0 + 0] += a1 * Cs[i1 * 3 + 0];
                  As[0 + 1] += a1 * Cs[i1 * 3 + 1];
                  As[0 + 2] += a1 * Cs[i1 * 3 + 2];

                  {
                    int_T i2;
                    for (i2=0; i2 < 9; i2++) {
                      Bs[0 + i2] += a1 * Ds[i1 * 9 + i2];
                    }
                  }

                  a1 = BDcol[1];
                  As[3 + 0] += a1 * Cs[i1 * 3 + 0];
                  As[3 + 1] += a1 * Cs[i1 * 3 + 1];
                  As[3 + 2] += a1 * Cs[i1 * 3 + 2];

                  {
                    int_T i2;
                    for (i2=0; i2 < 9; i2++) {
                      Bs[9 + i2] += a1 * Ds[i1 * 9 + i2];
                    }
                  }

                  a1 = BDcol[2];
                  As[6 + 0] += a1 * Cs[i1 * 3 + 0];
                  As[6 + 1] += a1 * Cs[i1 * 3 + 1];
                  As[6 + 2] += a1 * Cs[i1 * 3 + 2];

                  {
                    int_T i2;
                    for (i2=0; i2 < 9; i2++) {
                      Bs[18 + i2] += a1 * Ds[i1 * 9 + i2];
                    }
                  }
                }
              }
            }
          }                            /* if (swChanged) */
        } while (swChanged > 0 && --loopsToDo > 0);

        if (loopsToDo == 0) {
          real_T *Cs = (real_T*)inversor_DW.StateSpace_PWORK.CS;
          real_T *Ds = (real_T*)inversor_DW.StateSpace_PWORK.DS;

          {
            int_T i1;
            real_T *y0 = &inversor_B.StateSpace_o1[0];
            for (i1=0; i1 < 11; i1++) {
              accum = 0.0;
              accum += *(Cs++) * inversor_DW.StateSpace_DSTATE[0];
              accum += *(Cs++) * inversor_DW.StateSpace_DSTATE[1];
              accum += *(Cs++) * inversor_DW.StateSpace_DSTATE[2];

              {
                int_T i2;
                const real_T *u0 = inversor_ConstP.SwitchCurrents_Value;
                for (i2=0; i2 < 8; i2++) {
                  accum += *(Ds++) * u0[i2];
                }

                //accum += *(Ds++) * inversor_U.Vdc;
                accum += *(Ds++) * vdc;//340;
              }

              y0[i1] = accum;
            }
          }
        }

        /* Output new switches states */
        {
          int_T i1;
          real_T *y1 = &inversor_B.StateSpace_o2[0];
          for (i1=0; i1 < 8; i1++) {
            y1[i1] = (real_T)switch_status[i1];
          }
        }
      }

      /* Outport: '<Root>/Volt' */
      inversor_Y.Volt = inversor_B.StateSpace_o1[9];

      /* Outport: '<Root>/Current' */
      inversor_Y.Current = inversor_B.StateSpace_o1[10];
      salida=inversor_Y.Current; //.Volt ;
      //printf("Voltaje %5.2f\n",salida);
    }

    if (rtmIsMajorTimeStep(inversor_M)) {
      /* DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn' */
      inversor_B.DiscreteTransferFcn = 0.001167 *
        inversor_DW.DiscreteTransferFcn_states[0] + -0.001167 *
        inversor_DW.DiscreteTransferFcn_states[1];

      /* Gain: '<S1>/Gain' */
      inversor_B.Gain = 0.00333 * inversor_B.StateSpace_o1[9];
    }

    /* RelationalOperator: '<S7>/Relational Operator' incorporates:
     *  Clock: '<S51>/Clock'
     *  Constant: '<S51>/Constant'
     *  Lookup_n-D: '<S51>/Look-Up Table1'
     *  Math: '<S51>/Math Function'
     *  S-Function (sfun_tstart): '<S51>/startTime'
     *  Sum: '<S51>/Sum'
     */
    rtb_RelationalOperator = (look1_binlxpw(rt_remd_snf(inversor_M->Timing.t[0]
      - (0.0), 0.0002), inversor_ConstP.LookUpTable1_bp01Data,
      inversor_ConstP.LookUpTable1_tableData, 2U) >=
      inversor_B.DiscreteTransferFcn);

    /* Gain: '<S7>/Gain' */
    rtb_Gain = (uint8_T)(rtb_RelationalOperator ? 160 : 0);

    /* DataTypeConversion: '<S27>/Data Type Conversion' */
    inversor_B.DataTypeConversion = (real_T)rtb_Gain * 0.0625;

    /* Gain: '<S7>/Gain1' incorporates:
     *  Logic: '<S7>/Logical Operator'
     */
    rtb_Gain1 = (uint8_T)(!rtb_RelationalOperator ? 160 : 0);

    /* DataTypeConversion: '<S34>/Data Type Conversion' */
    inversor_B.DataTypeConversion_e = (real_T)rtb_Gain1 * 0.0625;

    /* DataTypeConversion: '<S41>/Data Type Conversion' */
    inversor_B.DataTypeConversion_m = (real_T)rtb_Gain1 * 0.0625;

    /* DataTypeConversion: '<S48>/Data Type Conversion' */
    inversor_B.DataTypeConversion_o = (real_T)rtb_Gain * 0.0625;

    /* StateSpace: '<S8>/State-Space' */
    StateSpace = 24674.011002723397 * inversor_X.StateSpace_CSTATE[1];

    /* Integrator: '<S3>/Integrator' */
    /* Limited  Integrator  */
    if (inversor_X.Integrator_CSTATE >= (rtInf)) {
      inversor_X.Integrator_CSTATE = (rtInf);
    } else {
      if (inversor_X.Integrator_CSTATE <= (rtMinusInf)) {
        inversor_X.Integrator_CSTATE = (rtMinusInf);
      }
    }

    /* Math: '<S3>/Math Function' incorporates:
     *  Constant: '<S3>/Constant4'
     *  Integrator: '<S3>/Integrator'
     */
    rtb_Step = rt_modd_snf(inversor_X.Integrator_CSTATE, 6.2831853071795862);

    /* Trigonometry: '<S3>/Trigonometric Function' */
    rtb_TrigonometricFunction = sin(rtb_Step);

    /* Trigonometry: '<S3>/Trigonometric Function2' */
    rtb_Step = cos(rtb_Step);

    /* Outputs for Enabled SubSystem: '<S3>/Automatic Gain Control' incorporates:
     *  EnablePort: '<S9>/Enable'
     */
    if (rtmIsMajorTimeStep(inversor_M) && rtmIsMajorTimeStep(inversor_M) &&
        inversor_DW.AutomaticGainControl_MODE) {
      inversor_DW.AutomaticGainControl_MODE = false;
    }

    if (inversor_DW.AutomaticGainControl_MODE) {
      /* Integrator: '<S9>/integ1' */
      inversor_B.integ1 = inversor_X.integ1_CSTATE;

      /* Saturate: '<S9>/To avoid division by zero' */
      if (StateSpace > 1.0E+6) {
        Sum1 = 1.0E+6;
      } else if (StateSpace < 1.0E-6) {
        Sum1 = 1.0E-6;
      } else {
        Sum1 = StateSpace;
      }

      /* End of Saturate: '<S9>/To avoid division by zero' */

      /* Fcn: '<S9>/Period' */
      inversor_B.Period = 1.0 / Sum1;

      /* VariableTransportDelay: '<S9>/Variable Transport Delay' */
      {
        real_T **uBuffer = (real_T**)
          &inversor_DW.VariableTransportDelay_PWORK_f.TUbufferPtrs[0];
        real_T **tBuffer = (real_T**)
          &inversor_DW.VariableTransportDelay_PWORK_f.TUbufferPtrs[1];
        real_T simTime = inversor_M->Timing.t[0];
        real_T appliedDelay;
        appliedDelay = inversor_B.Period;

        /* For variable time delay, output here */
        if (appliedDelay > 1.0) {
          appliedDelay = 1.0;
        }

        if (appliedDelay < 0.0) {
          /* negative delay is not supported
           *  set delay to 0
           */
          appliedDelay = 0.0;
        }

        inversor_B.VariableTransportDelay_b = rt_TDelayInterpolate(
          simTime - appliedDelay,
          0.0,
          *tBuffer,
          *uBuffer,
          inversor_DW.VariableTransportDelay_IWORK_h.CircularBufSize,
          &inversor_DW.VariableTransportDelay_IWORK_h.Last,
          inversor_DW.VariableTransportDelay_IWORK_h.Tail,
          inversor_DW.VariableTransportDelay_IWORK_h.Head,
          1.0,
          0,
          0);
      }

      /* Integrator: '<S9>/Integ2' */
      inversor_B.Integ2 = inversor_X.Integ2_CSTATE;

      /* VariableTransportDelay: '<S9>/Variable Transport Delay1' */
      {
        real_T **uBuffer = (real_T**)
          &inversor_DW.VariableTransportDelay1_PWORK.TUbufferPtrs[0];
        real_T **tBuffer = (real_T**)
          &inversor_DW.VariableTransportDelay1_PWORK.TUbufferPtrs[1];
        real_T simTime = inversor_M->Timing.t[0];
        real_T appliedDelay;
        appliedDelay = inversor_B.Period;

        /* For variable time delay, output here */
        if (appliedDelay > 1.0) {
          appliedDelay = 1.0;
        }

        if (appliedDelay < 0.0) {
          /* negative delay is not supported
           *  set delay to 0
           */
          appliedDelay = 0.0;
        }

        inversor_B.VariableTransportDelay1 = rt_TDelayInterpolate(
          simTime - appliedDelay,
          0.0,
          *tBuffer,
          *uBuffer,
          inversor_DW.VariableTransportDelay1_IWORK.CircularBufSize,
          &inversor_DW.VariableTransportDelay1_IWORK.Last,
          inversor_DW.VariableTransportDelay1_IWORK.Tail,
          inversor_DW.VariableTransportDelay1_IWORK.Head,
          0.0,
          0,
          0);
      }

      /* Sum: '<S9>/Sum' incorporates:
       *  Fcn: '<S9>/Fcn'
       *  Fcn: '<S9>/Fcn1'
       *  Sum: '<S9>/Sum1'
       *  Sum: '<S9>/Sum2'
       */
      Sum1 = rt_powd_snf(inversor_B.integ1 - inversor_B.VariableTransportDelay_b,
                         2.0) + rt_powd_snf(inversor_B.Integ2 -
        inversor_B.VariableTransportDelay1, 2.0);

      /* Fcn: '<S9>/Fcn2' */
      if (Sum1 < 0.0) {
        Sum1 = -sqrt(-Sum1);
      } else {
        Sum1 = sqrt(Sum1);
      }

      /* End of Fcn: '<S9>/Fcn2' */

      /* Saturate: '<S9>/Saturation' */
      if (Sum1 > 2.0) {
        Sum1 = 2.0;
      } else {
        if (Sum1 < 0.01) {
          Sum1 = 0.01;
        }
      }

      /* End of Saturate: '<S9>/Saturation' */

      /* Math: '<S9>/Math Function'
       *
       * About '<S9>/Math Function':
       *  Operator: reciprocal
       */
      inversor_B.MathFunction = 1.0 / Sum1;

      /* Product: '<S9>/Product2' incorporates:
       *  Gain: '<S9>/Gain10'
       */
      Sum1 = 2.0 * StateSpace * inversor_B.Gain;

      /* Product: '<S9>/Product' */
      inversor_B.Product = rtb_TrigonometricFunction * Sum1;

      /* Product: '<S9>/Product1' */
      inversor_B.Product1 = Sum1 * rtb_Step;
    }

    /* End of Outputs for SubSystem: '<S3>/Automatic Gain Control' */

    /* Saturate: '<S11>/To avoid division by zero' */
    if (StateSpace > 1.0E+6) {
      Sum1 = 1.0E+6;
    } else if (StateSpace < 1.0E-6) {
      Sum1 = 1.0E-6;
    } else {
      Sum1 = StateSpace;
    }

    /* End of Saturate: '<S11>/To avoid division by zero' */

    /* Fcn: '<S11>/Number of samples per cycle' */
    inversor_B.Delay = 1.0 / Sum1;

    /* VariableTransportDelay: '<S11>/Variable Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &inversor_DW.VariableTransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &inversor_DW.VariableTransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = inversor_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = inversor_B.Delay;

      /* For variable time delay, output here */
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      if (appliedDelay < 0.0) {
        /* negative delay is not supported
         *  set delay to 0
         */
        appliedDelay = 0.0;
      }

      inversor_B.VariableTransportDelay = rt_TDelayInterpolate(
        simTime - appliedDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        inversor_DW.VariableTransportDelay_IWORK.CircularBufSize,
        &inversor_DW.VariableTransportDelay_IWORK.Last,
        inversor_DW.VariableTransportDelay_IWORK.Tail,
        inversor_DW.VariableTransportDelay_IWORK.Head,
        0.0,
        0,
        0);
    }

    /* Integrator: '<S11>/Integrator' */
    inversor_B.Integrator_k = inversor_X.Integrator_CSTATE_d;

    /* Switch: '<S11>/Switch' incorporates:
     *  Constant: '<S11>/Constant'
     *  Product: '<S11>/Product'
     *  Step: '<S11>/Step'
     *  Sum: '<S11>/Sum7'
     */
    if (!(inversor_M->Timing.t[0] < 0.016666666666666666) >= 0.5) {
      StateSpace *= inversor_B.Integrator_k - inversor_B.VariableTransportDelay;
    } else {
      StateSpace = 0.0;
    }

    /* End of Switch: '<S11>/Switch' */

    /* Product: '<S3>/Divide' */
    inversor_B.Divide = StateSpace * inversor_B.MathFunction;

    /* Integrator: '<S10>/Integrator' */
    /* Limited  Integrator  */
    if (inversor_X.Integrator_CSTATE_c >= 10000.0) {
      inversor_X.Integrator_CSTATE_c = 10000.0;
    } else {
      if (inversor_X.Integrator_CSTATE_c <= 0.0) {
        inversor_X.Integrator_CSTATE_c = 0.0;
      }
    }

    /* Derivative: '<S10>/Derivative' */
    if ((inversor_DW.TimeStampA >= inversor_M->Timing.t[0]) &&
        (inversor_DW.TimeStampB >= inversor_M->Timing.t[0])) {
      StateSpace = 0.0;
    } else {
      StateSpace = inversor_DW.TimeStampA;
      lastU = &inversor_DW.LastUAtTimeA;
      if (inversor_DW.TimeStampA < inversor_DW.TimeStampB) {
        if (inversor_DW.TimeStampB < inversor_M->Timing.t[0]) {
          StateSpace = inversor_DW.TimeStampB;
          lastU = &inversor_DW.LastUAtTimeB;
        }
      } else {
        if (inversor_DW.TimeStampA >= inversor_M->Timing.t[0]) {
          StateSpace = inversor_DW.TimeStampB;
          lastU = &inversor_DW.LastUAtTimeB;
        }
      }

      StateSpace = (inversor_B.Divide - *lastU) / (inversor_M->Timing.t[0] -
        StateSpace);
    }

    /* End of Derivative: '<S10>/Derivative' */

    /* Sum: '<S10>/Sum6' incorporates:
     *  Gain: '<S10>/Kp4'
     *  Integrator: '<S10>/Integrator'
     */
    StateSpace += 180.0 * inversor_B.Divide + inversor_X.Integrator_CSTATE_c;

    /* Saturate: '<S10>/Saturation2' */
    if (StateSpace > 10000.0) {
      inversor_B.Saturation2 = 10000.0;
    } else if (StateSpace < 0.0) {
      inversor_B.Saturation2 = 0.0;
    } else {
      inversor_B.Saturation2 = StateSpace;
    }

    /* End of Saturate: '<S10>/Saturation2' */

    /* Gain: '<S3>/Gain10' */
    StateSpace = 0.15915494309189535 * inversor_B.Saturation2;

    /* Gain: '<S10>/Kp5' */
    inversor_B.Kp5 = 3200.0 * inversor_B.Divide;

    /* Product: '<S3>/Product1' */
    inversor_B.Vq = inversor_B.Gain * rtb_Step;

    /* RateLimiter: '<S3>/Rate Limiter' */
    if ((inversor_DW.LastMajorTimeA >= inversor_M->Timing.t[0]) &&
        (inversor_DW.LastMajorTimeB >= inversor_M->Timing.t[0])) {
      inversor_B.RateLimiter = StateSpace;
    } else {
      if (((inversor_DW.LastMajorTimeA < inversor_DW.LastMajorTimeB) &&
           (inversor_DW.LastMajorTimeB < inversor_M->Timing.t[0])) ||
          ((inversor_DW.LastMajorTimeA >= inversor_DW.LastMajorTimeB) &&
           (inversor_DW.LastMajorTimeA >= inversor_M->Timing.t[0]))) {
        Sum2_p = inversor_M->Timing.t[0] - inversor_DW.LastMajorTimeB;
        rtb_Step = inversor_DW.PrevYB;
      } else {
        Sum2_p = inversor_M->Timing.t[0] - inversor_DW.LastMajorTimeA;
        rtb_Step = inversor_DW.PrevYA;
      }

      riseValLimit = Sum2_p * 12.0;
      Sum1 = StateSpace - rtb_Step;
      if (Sum1 > riseValLimit) {
        inversor_B.RateLimiter = rtb_Step + riseValLimit;
      } else {
        Sum2_p *= -12.0;
        if (Sum1 < Sum2_p) {
          inversor_B.RateLimiter = rtb_Step + Sum2_p;
        } else {
          inversor_B.RateLimiter = StateSpace;
        }
      }
    }

    /* End of RateLimiter: '<S3>/Rate Limiter' */

    /* Sum: '<S1>/Sum2' incorporates:
     *  Inport: '<Root>/u1'
     *  Product: '<S1>/Product'
     */
    //inversor_B.Sum2 = rtb_TrigonometricFunction * inversor_U.u1 -
    inversor_B.Sum2 = rtb_TrigonometricFunction * u -
      inversor_B.StateSpace_o1[10];
  }

  if (rtmIsMajorTimeStep(inversor_M)) {
    real_T denAccum;
    real_T *lastU;
    if (rtmIsMajorTimeStep(inversor_M)) {
      /* Update for S-Function (sfun_spssw_discc): '<S52>/State-Space' incorporates:
       *  Constant: '<S54>/SwitchCurrents'
       *  Update for Inport: '<Root>/Vdc'
       */

      /* S-Function block: <S52>/State-Space */
      {
        const real_T *As = (real_T*)inversor_DW.StateSpace_PWORK.AS;
        const real_T *Bs = (real_T*)inversor_DW.StateSpace_PWORK.BS;
        real_T *xtmp = (real_T*)inversor_DW.StateSpace_PWORK.XTMP;
        real_T accum;

        /* Calculate new states... */
        accum = 0.0;
        accum += *(As++) * inversor_DW.StateSpace_DSTATE[0];
        accum += *(As++) * inversor_DW.StateSpace_DSTATE[1];
        accum += *(As++) * inversor_DW.StateSpace_DSTATE[2];

        {
          int_T i1;
          const real_T *u0 = inversor_ConstP.SwitchCurrents_Value;
          for (i1=0; i1 < 8; i1++) {
            accum += *(Bs++) * u0[i1];
          }

          //accum += *(Bs++) * inversor_U.Vdc;
          accum += *(Bs++) * vdc;//340;
        }

        xtmp[0] = accum;
        accum = 0.0;
        accum += *(As++) * inversor_DW.StateSpace_DSTATE[0];
        accum += *(As++) * inversor_DW.StateSpace_DSTATE[1];
        accum += *(As++) * inversor_DW.StateSpace_DSTATE[2];

        {
          int_T i1;
          const real_T *u0 = inversor_ConstP.SwitchCurrents_Value;
          for (i1=0; i1 < 8; i1++) {
            accum += *(Bs++) * u0[i1];
            
          }

          //accum += *(Bs++) * inversor_U.Vdc;
          accum += *(Bs++) * vdc;//340;
        }

        xtmp[1] = accum;
        accum = 0.0;
        accum += *(As++) * inversor_DW.StateSpace_DSTATE[0];
        accum += *(As++) * inversor_DW.StateSpace_DSTATE[1];
        accum += *(As++) * inversor_DW.StateSpace_DSTATE[2];

        {
          int_T i1;
          const real_T *u0 = inversor_ConstP.SwitchCurrents_Value;
          for (i1=0; i1 < 8; i1++) {
            accum += *(Bs++) * u0[i1];
          }

          //accum += *(Bs++) * inversor_U.Vdc;
		  accum += *(Bs++) * vdc;//340;
        }

        xtmp[2] = accum;
        inversor_DW.StateSpace_DSTATE[0] = xtmp[0];
        inversor_DW.StateSpace_DSTATE[1] = xtmp[1];
        inversor_DW.StateSpace_DSTATE[2] = xtmp[2];

        {
          int_T *gState = (int_T*)inversor_DW.StateSpace_PWORK.G_STATE;

          /* Store switch gates values for next step */
          *(gState++) = (int_T) inversor_B.DataTypeConversion_o;
          *(gState++) = (int_T) inversor_B.DataTypeConversion;
          *(gState++) = (int_T) inversor_B.DataTypeConversion_e;
          *(gState++) = (int_T) inversor_B.DataTypeConversion_m;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
          *(gState++) = (int_T) 0.0;
        }
      }

      /* Update for DiscreteTransferFcn: '<S4>/Discrete Transfer Fcn' */
      denAccum = (inversor_B.Sum2 - -2.0 *
                  inversor_DW.DiscreteTransferFcn_states[0]) - 0.9999 *
        inversor_DW.DiscreteTransferFcn_states[1];
      inversor_DW.DiscreteTransferFcn_states[1] =
        inversor_DW.DiscreteTransferFcn_states[0];
      inversor_DW.DiscreteTransferFcn_states[0] = denAccum;
    }

    /* Update for Enabled SubSystem: '<S3>/Automatic Gain Control' incorporates:
     *  Update for EnablePort: '<S9>/Enable'
     */
    if (inversor_DW.AutomaticGainControl_MODE) {
      /* Update for VariableTransportDelay: '<S9>/Variable Transport Delay' */
      {
        real_T **uBuffer = (real_T**)
          &inversor_DW.VariableTransportDelay_PWORK_f.TUbufferPtrs[0];
        real_T **tBuffer = (real_T**)
          &inversor_DW.VariableTransportDelay_PWORK_f.TUbufferPtrs[1];
        real_T simTime = inversor_M->Timing.t[0];
        real_T appliedDelay;
        appliedDelay = inversor_B.Period;
        if (appliedDelay > 1.0) {
          appliedDelay = 1.0;
        }

        inversor_DW.VariableTransportDelay_IWORK_h.Head =
          ((inversor_DW.VariableTransportDelay_IWORK_h.Head <
            (inversor_DW.VariableTransportDelay_IWORK_h.CircularBufSize-1)) ?
           (inversor_DW.VariableTransportDelay_IWORK_h.Head+1) : 0);
        if (inversor_DW.VariableTransportDelay_IWORK_h.Head ==
            inversor_DW.VariableTransportDelay_IWORK_h.Tail) {
          inversor_DW.VariableTransportDelay_IWORK_h.Tail =
            ((inversor_DW.VariableTransportDelay_IWORK_h.Tail <
              (inversor_DW.VariableTransportDelay_IWORK_h.CircularBufSize-1)) ?
             (inversor_DW.VariableTransportDelay_IWORK_h.Tail+1) : 0);
        }

        (*tBuffer)[inversor_DW.VariableTransportDelay_IWORK_h.Head] = simTime;
        (*uBuffer)[inversor_DW.VariableTransportDelay_IWORK_h.Head] =
          inversor_B.integ1;

        /* when use fixed buffer, reset solver at when buffer is updated
         * to avoid output consistency fail.
         */
      }

      /* Update for VariableTransportDelay: '<S9>/Variable Transport Delay1' */
      {
        real_T **uBuffer = (real_T**)
          &inversor_DW.VariableTransportDelay1_PWORK.TUbufferPtrs[0];
        real_T **tBuffer = (real_T**)
          &inversor_DW.VariableTransportDelay1_PWORK.TUbufferPtrs[1];
        real_T simTime = inversor_M->Timing.t[0];
        real_T appliedDelay;
        appliedDelay = inversor_B.Period;
        if (appliedDelay > 1.0) {
          appliedDelay = 1.0;
        }

        inversor_DW.VariableTransportDelay1_IWORK.Head =
          ((inversor_DW.VariableTransportDelay1_IWORK.Head <
            (inversor_DW.VariableTransportDelay1_IWORK.CircularBufSize-1)) ?
           (inversor_DW.VariableTransportDelay1_IWORK.Head+1) : 0);
        if (inversor_DW.VariableTransportDelay1_IWORK.Head ==
            inversor_DW.VariableTransportDelay1_IWORK.Tail) {
          inversor_DW.VariableTransportDelay1_IWORK.Tail =
            ((inversor_DW.VariableTransportDelay1_IWORK.Tail <
              (inversor_DW.VariableTransportDelay1_IWORK.CircularBufSize-1)) ?
             (inversor_DW.VariableTransportDelay1_IWORK.Tail+1) : 0);
        }

        (*tBuffer)[inversor_DW.VariableTransportDelay1_IWORK.Head] = simTime;
        (*uBuffer)[inversor_DW.VariableTransportDelay1_IWORK.Head] =
          inversor_B.Integ2;

        /* when use fixed buffer, reset solver at when buffer is updated
         * to avoid output consistency fail.
         */
      }
    }

    /* End of Update for SubSystem: '<S3>/Automatic Gain Control' */

    /* Update for VariableTransportDelay: '<S11>/Variable Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &inversor_DW.VariableTransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)
        &inversor_DW.VariableTransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = inversor_M->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = inversor_B.Delay;
      if (appliedDelay > 1.0) {
        appliedDelay = 1.0;
      }

      inversor_DW.VariableTransportDelay_IWORK.Head =
        ((inversor_DW.VariableTransportDelay_IWORK.Head <
          (inversor_DW.VariableTransportDelay_IWORK.CircularBufSize-1)) ?
         (inversor_DW.VariableTransportDelay_IWORK.Head+1) : 0);
      if (inversor_DW.VariableTransportDelay_IWORK.Head ==
          inversor_DW.VariableTransportDelay_IWORK.Tail) {
        inversor_DW.VariableTransportDelay_IWORK.Tail =
          ((inversor_DW.VariableTransportDelay_IWORK.Tail <
            (inversor_DW.VariableTransportDelay_IWORK.CircularBufSize-1)) ?
           (inversor_DW.VariableTransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[inversor_DW.VariableTransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[inversor_DW.VariableTransportDelay_IWORK.Head] =
        inversor_B.Integrator_k;

      /* when use fixed buffer, reset solver at when buffer is updated
       * to avoid output consistency fail.
       */
    }

    /* Update for Derivative: '<S10>/Derivative' */
    if (inversor_DW.TimeStampA == (rtInf)) {
      inversor_DW.TimeStampA = inversor_M->Timing.t[0];
      lastU = &inversor_DW.LastUAtTimeA;
    } else if (inversor_DW.TimeStampB == (rtInf)) {
      inversor_DW.TimeStampB = inversor_M->Timing.t[0];
      lastU = &inversor_DW.LastUAtTimeB;
    } else if (inversor_DW.TimeStampA < inversor_DW.TimeStampB) {
      inversor_DW.TimeStampA = inversor_M->Timing.t[0];
      lastU = &inversor_DW.LastUAtTimeA;
    } else {
      inversor_DW.TimeStampB = inversor_M->Timing.t[0];
      lastU = &inversor_DW.LastUAtTimeB;
    }

    *lastU = inversor_B.Divide;

    /* End of Update for Derivative: '<S10>/Derivative' */

    /* Update for RateLimiter: '<S3>/Rate Limiter' */
    if (inversor_DW.LastMajorTimeA == (rtInf)) {
      inversor_DW.LastMajorTimeA = inversor_M->Timing.t[0];
      inversor_DW.PrevYA = inversor_B.RateLimiter;
    } else if (inversor_DW.LastMajorTimeB == (rtInf)) {
      inversor_DW.LastMajorTimeB = inversor_M->Timing.t[0];
      inversor_DW.PrevYB = inversor_B.RateLimiter;
    } else if (inversor_DW.LastMajorTimeA < inversor_DW.LastMajorTimeB) {
      inversor_DW.LastMajorTimeA = inversor_M->Timing.t[0];
      inversor_DW.PrevYA = inversor_B.RateLimiter;
    } else {
      inversor_DW.LastMajorTimeB = inversor_M->Timing.t[0];
      inversor_DW.PrevYB = inversor_B.RateLimiter;
    }

    /* End of Update for RateLimiter: '<S3>/Rate Limiter' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(inversor_M)) {
    rt_ertODEUpdateContinuousStates(&inversor_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++inversor_M->Timing.clockTick0)) {
      ++inversor_M->Timing.clockTickH0;
    }

    inversor_M->Timing.t[0] = rtsiGetSolverStopTime(&inversor_M->solverInfo);

    {
      /* Update absolute timer for sample time: [1.6666666666666667E-6s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 1.6666666666666667E-6, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      inversor_M->Timing.clockTick1++;
      if (!inversor_M->Timing.clockTick1) {
        inversor_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
  /*printf("La salida es: %3.2f \n",salida);
  printf("El Vdc: %3.2f \n",Vdc);
  printf("El U: %3.2f \n",U);*/
  return salida;
}

/* Derivatives for root system: '<Root>' */
void inversor_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_inversor_T *_rtXdot;
  _rtXdot = ((XDot_inversor_T *) inversor_M->derivs);

  /* Derivatives for StateSpace: '<S8>/State-Space' */
  _rtXdot->StateSpace_CSTATE[0] = 0.0;
  _rtXdot->StateSpace_CSTATE[1] = 0.0;
  _rtXdot->StateSpace_CSTATE[0] += -222.11060060879836 *
    inversor_X.StateSpace_CSTATE[0];
  _rtXdot->StateSpace_CSTATE[0] += -24674.011002723397 *
    inversor_X.StateSpace_CSTATE[1];
  _rtXdot->StateSpace_CSTATE[1] += inversor_X.StateSpace_CSTATE[0];
  _rtXdot->StateSpace_CSTATE[0] += inversor_B.RateLimiter;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (inversor_X.Integrator_CSTATE <= (rtMinusInf));
  usat = (inversor_X.Integrator_CSTATE >= (rtInf));
  if (((!lsat) && (!usat)) || (lsat && (inversor_B.Saturation2 > 0.0)) || (usat &&
       (inversor_B.Saturation2 < 0.0))) {
    _rtXdot->Integrator_CSTATE = inversor_B.Saturation2;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */

  /* Derivatives for Enabled SubSystem: '<S3>/Automatic Gain Control' */
  if (inversor_DW.AutomaticGainControl_MODE) {
    /* Derivatives for Integrator: '<S9>/integ1' */
    _rtXdot->integ1_CSTATE = inversor_B.Product;

    /* Derivatives for VariableTransportDelay: '<S9>/Variable Transport Delay' */
    {
    }

    /* Derivatives for Integrator: '<S9>/Integ2' */
    _rtXdot->Integ2_CSTATE = inversor_B.Product1;

    /* Derivatives for VariableTransportDelay: '<S9>/Variable Transport Delay1' */
    {
    }
  } else {
    {
      real_T *dx;
      int_T i;
      dx = &(((XDot_inversor_T *) inversor_M->derivs)->integ1_CSTATE);
      for (i=0; i < 2; i++) {
        dx[i] = 0.0;
      }
    }
  }

  /* End of Derivatives for SubSystem: '<S3>/Automatic Gain Control' */

  /* Derivatives for VariableTransportDelay: '<S11>/Variable Transport Delay' */
  {
  }

  /* Derivatives for Integrator: '<S11>/Integrator' */
  _rtXdot->Integrator_CSTATE_d = inversor_B.Vq;

  /* Derivatives for Integrator: '<S10>/Integrator' */
  lsat = (inversor_X.Integrator_CSTATE_c <= 0.0);
  usat = (inversor_X.Integrator_CSTATE_c >= 10000.0);
  if (((!lsat) && (!usat)) || (lsat && (inversor_B.Kp5 > 0.0)) || (usat &&
       (inversor_B.Kp5 < 0.0))) {
    _rtXdot->Integrator_CSTATE_c = inversor_B.Kp5;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE_c = 0.0;
  }

  /* End of Derivatives for Integrator: '<S10>/Integrator' */
}

/* Model initialize function */
void inversor_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)inversor_M, 0,
                sizeof(RT_MODEL_inversor_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&inversor_M->solverInfo,
                          &inversor_M->Timing.simTimeStep);
    rtsiSetTPtr(&inversor_M->solverInfo, &rtmGetTPtr(inversor_M));
    rtsiSetStepSizePtr(&inversor_M->solverInfo, &inversor_M->Timing.stepSize0);
    rtsiSetdXPtr(&inversor_M->solverInfo, &inversor_M->derivs);
    rtsiSetContStatesPtr(&inversor_M->solverInfo, (real_T **)
                         &inversor_M->contStates);
    rtsiSetNumContStatesPtr(&inversor_M->solverInfo,
      &inversor_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&inversor_M->solverInfo,
      &inversor_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&inversor_M->solverInfo,
      &inversor_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&inversor_M->solverInfo,
      &inversor_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&inversor_M->solverInfo, (&rtmGetErrorStatus
      (inversor_M)));
    rtsiSetRTModelPtr(&inversor_M->solverInfo, inversor_M);
  }

  rtsiSetSimTimeStep(&inversor_M->solverInfo, MAJOR_TIME_STEP);
  inversor_M->intgData.x0 = inversor_M->odeX0;
  inversor_M->intgData.f0 = inversor_M->odeF0;
  inversor_M->intgData.x1start = inversor_M->odeX1START;
  inversor_M->intgData.f1 = inversor_M->odeF1;
  inversor_M->intgData.Delta = inversor_M->odeDELTA;
  inversor_M->intgData.E = inversor_M->odeE;
  inversor_M->intgData.fac = inversor_M->odeFAC;

  /* initialize */
  {
    int_T i;
    real_T *f = inversor_M->intgData.fac;
    for (i = 0; i < (int_T)(sizeof(inversor_M->odeFAC)/sizeof(real_T)); i++) {
      f[i] = 1.5e-8;
    }
  }

  inversor_M->intgData.DFDX = inversor_M->odeDFDX;
  inversor_M->intgData.W = inversor_M->odeW;
  inversor_M->intgData.pivots = inversor_M->odePIVOTS;
  inversor_M->intgData.xtmp = inversor_M->odeXTMP;
  inversor_M->intgData.ztmp = inversor_M->odeZTMP;
  inversor_M->intgData.isFirstStep = true;
  rtsiSetSolverExtrapolationOrder(&inversor_M->solverInfo, 4);
  rtsiSetSolverNumberNewtonIterations(&inversor_M->solverInfo, 1);
  inversor_M->contStates = ((X_inversor_T *) &inversor_X);
  rtsiSetSolverData(&inversor_M->solverInfo, (void *)&inversor_M->intgData);
  rtsiSetSolverName(&inversor_M->solverInfo,"ode14x");
  rtmSetTPtr(inversor_M, &inversor_M->Timing.tArray[0]);
  inversor_M->Timing.stepSize0 = 1.6666666666666667E-6;

  /* block I/O */
  (void) memset(((void *) &inversor_B), 0,
                sizeof(B_inversor_T));

  /* states (continuous) */
  {
    (void) memset((void *)&inversor_X, 0,
                  sizeof(X_inversor_T));
  }

  /* states (dwork) */
  (void) memset((void *)&inversor_DW, 0,
                sizeof(DW_inversor_T));

  /* external inputs */
  (void)memset((void *)&inversor_U, 0, sizeof(ExtU_inversor_T));

  /* external outputs */
  (void) memset((void *)&inversor_Y, 0,
                sizeof(ExtY_inversor_T));

  /* Start for S-Function (sfun_spssw_discc): '<S52>/State-Space' incorporates:
   *  Constant: '<S54>/SwitchCurrents'
   *  Start for Inport: '<Root>/Vdc'
   */

  /* S-Function block: <S52>/State-Space */
  {
    inversor_DW.StateSpace_PWORK.AS = (real_T*)calloc(3 * 3, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.BS = (real_T*)calloc(3 * 9, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.CS = (real_T*)calloc(11 * 3, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.DS = (real_T*)calloc(11 * 9, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.DX_COL = (real_T*)calloc(11, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.TMP2 = (real_T*)calloc(9, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.BD_COL = (real_T*)calloc(3, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.TMP1 = (real_T*)calloc(3, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.XTMP = (real_T*)calloc(3, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.SWITCH_STATUS = (int_T*)calloc(8, sizeof(int_T));
    inversor_DW.StateSpace_PWORK.SW_CHG = (int_T*)calloc(8, sizeof(int_T));
    inversor_DW.StateSpace_PWORK.G_STATE = (int_T*)calloc(8, sizeof(int_T));
    inversor_DW.StateSpace_PWORK.Y_SWITCH = (real_T*)calloc(8, sizeof(real_T));
    inversor_DW.StateSpace_PWORK.SWITCH_TYPES = (int_T*)calloc(8, sizeof(int_T));
    inversor_DW.StateSpace_PWORK.IDX_OUT_SW = (int_T*)calloc(8, sizeof(int_T));
    inversor_DW.StateSpace_PWORK.SWITCH_STATUS_INIT = (int_T*)calloc(8, sizeof
      (int_T));
    inversor_DW.StateSpace_PWORK.USWLAST = (real_T*)calloc(8, sizeof(real_T));
  }

  /* Start for Enabled SubSystem: '<S3>/Automatic Gain Control' */

  /* Start for VariableTransportDelay: '<S9>/Variable Transport Delay' */
  {
    real_T *pBuffer = &inversor_DW.VariableTransportDelay_RWORK_b.TUbufferArea[0];
    int_T j;
    inversor_DW.VariableTransportDelay_IWORK_h.Tail = 0;
    inversor_DW.VariableTransportDelay_IWORK_h.Head = 0;
    inversor_DW.VariableTransportDelay_IWORK_h.Last = 0;
    inversor_DW.VariableTransportDelay_IWORK_h.CircularBufSize = 8192;
    for (j=0; j < 8192; j++) {
      pBuffer[j] = 1.0;
      pBuffer[8192 + j] = inversor_M->Timing.t[0];
    }

    inversor_DW.VariableTransportDelay_PWORK_f.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    inversor_DW.VariableTransportDelay_PWORK_f.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* Start for VariableTransportDelay: '<S9>/Variable Transport Delay1' */
  {
    real_T *pBuffer = &inversor_DW.VariableTransportDelay1_RWORK.TUbufferArea[0];
    int_T j;
    inversor_DW.VariableTransportDelay1_IWORK.Tail = 0;
    inversor_DW.VariableTransportDelay1_IWORK.Head = 0;
    inversor_DW.VariableTransportDelay1_IWORK.Last = 0;
    inversor_DW.VariableTransportDelay1_IWORK.CircularBufSize = 8192;
    for (j=0; j < 8192; j++) {
      pBuffer[j] = 0.0;
      pBuffer[8192 + j] = inversor_M->Timing.t[0];
    }

    inversor_DW.VariableTransportDelay1_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    inversor_DW.VariableTransportDelay1_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* End of Start for SubSystem: '<S3>/Automatic Gain Control' */

  /* Start for VariableTransportDelay: '<S11>/Variable Transport Delay' */
  {
    real_T *pBuffer = &inversor_DW.VariableTransportDelay_RWORK.TUbufferArea[0];
    int_T j;
    inversor_DW.VariableTransportDelay_IWORK.Tail = 0;
    inversor_DW.VariableTransportDelay_IWORK.Head = 0;
    inversor_DW.VariableTransportDelay_IWORK.Last = 0;
    inversor_DW.VariableTransportDelay_IWORK.CircularBufSize = 8192;
    for (j=0; j < 8192; j++) {
      pBuffer[j] = 0.0;
      pBuffer[8192 + j] = inversor_M->Timing.t[0];
    }

    inversor_DW.VariableTransportDelay_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    inversor_DW.VariableTransportDelay_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[8192];
  }

  /* InitializeConditions for S-Function (sfun_spssw_discc): '<S52>/State-Space' incorporates:
   *  Constant: '<S54>/SwitchCurrents'
   *  InitializeConditions for Inport: '<Root>/Vdc'
   */
  {
    int32_T i, j;
    real_T *As = (real_T*)inversor_DW.StateSpace_PWORK.AS;
    real_T *Bs = (real_T*)inversor_DW.StateSpace_PWORK.BS;
    real_T *Cs = (real_T*)inversor_DW.StateSpace_PWORK.CS;
    real_T *Ds = (real_T*)inversor_DW.StateSpace_PWORK.DS;
    real_T *X0 = (real_T*)&inversor_DW.StateSpace_DSTATE[0];
    for (i = 0; i < 3; i++) {
      X0[i] = (inversor_ConstP.StateSpace_X0_param[i]);
    }

    /* Copy and transpose A and B */
    for (i=0; i<3; i++) {
      for (j=0; j<3; j++)
        As[i*3 + j] = (inversor_ConstP.StateSpace_AS_param[i + j*3]);
      for (j=0; j<9; j++)
        Bs[i*9 + j] = (inversor_ConstP.StateSpace_BS_param[i + j*3]);
    }

    /* Copy and transpose C */
    for (i=0; i<11; i++) {
      for (j=0; j<3; j++)
        Cs[i*3 + j] = (inversor_ConstP.StateSpace_CS_param[i + j*11]);
    }

    /* Copy and transpose D */
    for (i=0; i<11; i++) {
      for (j=0; j<9; j++)
        Ds[i*9 + j] = (inversor_ConstP.StateSpace_DS_param[i + j*11]);
    }

    {
      /* Switches work vectors */
      int_T *switch_status = (int_T*) inversor_DW.StateSpace_PWORK.SWITCH_STATUS;
      int_T *gState = (int_T*)inversor_DW.StateSpace_PWORK.G_STATE;
      real_T *yswitch = (real_T*)inversor_DW.StateSpace_PWORK.Y_SWITCH;
      int_T *switchTypes = (int_T*)inversor_DW.StateSpace_PWORK.SWITCH_TYPES;
      int_T *idxOutSw = (int_T*)inversor_DW.StateSpace_PWORK.IDX_OUT_SW;
      int_T *switch_status_init = (int_T*)
        inversor_DW.StateSpace_PWORK.SWITCH_STATUS_INIT;

      /* Initialize work vectors */
      switch_status[0] = 0;
      switch_status_init[0] = 0;
      gState[0] = (int_T) 0.0;
      yswitch[0] = 1/0.1;
      switchTypes[0] = (int_T)1.0;
      idxOutSw[0] = ((int_T)0.0) - 1;
      switch_status[1] = 0;
      switch_status_init[1] = 0;
      gState[1] = (int_T) 0.0;
      yswitch[1] = 1/0.1;
      switchTypes[1] = (int_T)1.0;
      idxOutSw[1] = ((int_T)0.0) - 1;
      switch_status[2] = 0;
      switch_status_init[2] = 0;
      gState[2] = (int_T) 0.0;
      yswitch[2] = 1/0.1;
      switchTypes[2] = (int_T)1.0;
      idxOutSw[2] = ((int_T)0.0) - 1;
      switch_status[3] = 0;
      switch_status_init[3] = 0;
      gState[3] = (int_T) 0.0;
      yswitch[3] = 1/0.1;
      switchTypes[3] = (int_T)1.0;
      idxOutSw[3] = ((int_T)0.0) - 1;
      switch_status[4] = 0;
      switch_status_init[4] = 0;
      gState[4] = (int_T) 0.0;
      yswitch[4] = 1/0.01;
      switchTypes[4] = (int_T)3.0;
      idxOutSw[4] = ((int_T)0.0) - 1;
      switch_status[5] = 0;
      switch_status_init[5] = 0;
      gState[5] = (int_T) 0.0;
      yswitch[5] = 1/0.01;
      switchTypes[5] = (int_T)3.0;
      idxOutSw[5] = ((int_T)0.0) - 1;
      switch_status[6] = 0;
      switch_status_init[6] = 0;
      gState[6] = (int_T) 0.0;
      yswitch[6] = 1/0.01;
      switchTypes[6] = (int_T)3.0;
      idxOutSw[6] = ((int_T)0.0) - 1;
      switch_status[7] = 0;
      switch_status_init[7] = 0;
      gState[7] = (int_T) 0.0;
      yswitch[7] = 1/0.01;
      switchTypes[7] = (int_T)3.0;
      idxOutSw[7] = ((int_T)0.0) - 1;
    }
  }

  /* InitializeConditions for StateSpace: '<S8>/State-Space' */
  inversor_X.StateSpace_CSTATE[0] = 0.0;
  inversor_X.StateSpace_CSTATE[1] = 0.0024317084074161064;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  inversor_X.Integrator_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S11>/Integrator' */
  inversor_X.Integrator_CSTATE_d = 0.0;

  /* InitializeConditions for Integrator: '<S10>/Integrator' */
  inversor_X.Integrator_CSTATE_c = 376.99111843077515;

  /* InitializeConditions for Derivative: '<S10>/Derivative' */
  inversor_DW.TimeStampA = (rtInf);
  inversor_DW.TimeStampB = (rtInf);

  /* InitializeConditions for RateLimiter: '<S3>/Rate Limiter' */
  inversor_DW.LastMajorTimeA = (rtInf);
  inversor_DW.LastMajorTimeB = (rtInf);

  /* SystemInitialize for Enabled SubSystem: '<S3>/Automatic Gain Control' */
  /* InitializeConditions for Integrator: '<S9>/integ1' */
  inversor_X.integ1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S9>/Integ2' */
  inversor_X.Integ2_CSTATE = 0.0;

  /* SystemInitialize for Outport: '<S9>/Gain' */
  inversor_B.MathFunction = 1.0;

  /* End of SystemInitialize for SubSystem: '<S3>/Automatic Gain Control' */
}

/* Model terminate function */
void inversor_terminate(void)
{
  /* Terminate for S-Function (sfun_spssw_discc): '<S52>/State-Space' incorporates:
   *  Constant: '<S54>/SwitchCurrents'
   *  Terminate for Inport: '<Root>/Vdc'
   */

  /* S-Function block: <S52>/State-Space */
  {
    /* Free memory */
    free(inversor_DW.StateSpace_PWORK.AS);
    free(inversor_DW.StateSpace_PWORK.BS);
    free(inversor_DW.StateSpace_PWORK.CS);
    free(inversor_DW.StateSpace_PWORK.DS);
    free(inversor_DW.StateSpace_PWORK.DX_COL);
    free(inversor_DW.StateSpace_PWORK.TMP2);
    free(inversor_DW.StateSpace_PWORK.BD_COL);
    free(inversor_DW.StateSpace_PWORK.TMP1);
    free(inversor_DW.StateSpace_PWORK.XTMP);

    /*
     * Circuit has switches*/
    free(inversor_DW.StateSpace_PWORK.G_STATE);
    free(inversor_DW.StateSpace_PWORK.SWITCH_STATUS);
    free(inversor_DW.StateSpace_PWORK.SW_CHG);
    free(inversor_DW.StateSpace_PWORK.SWITCH_STATUS_INIT);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
