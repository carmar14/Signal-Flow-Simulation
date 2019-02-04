/*
 * File: mpc_doubleint.c
 *
 * Code generated for Simulink model 'mpc_doubleint'.
 *
 * Model version                  : 1.56
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Sep 11 09:07:00 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "mpc_doubleint.h"
#include "mpc_doubleint_private.h"

/* Block signals (auto storage) */
B_mpc_doubleint_T mpc_doubleint_B;

/* Continuous states */
X_mpc_doubleint_T mpc_doubleint_X;

/* Block states (auto storage) */
DW_mpc_doubleint_T mpc_doubleint_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_mpc_doubleint_T mpc_doubleint_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_mpc_doubleint_T mpc_doubleint_Y;

/* Real-time model */
RT_MODEL_mpc_doubleint_T mpc_doubleint_M_;
RT_MODEL_mpc_doubleint_T *const mpc_doubleint_M = &mpc_doubleint_M_;

/* Forward declaration for local functions */
static void mpc_doubleint_Unconstrained(const real_T b_Hinv[16], const real_T f
  [4], real_T x[4], int16_T n);
static real_T mpc_doubleint_norm(const real_T x[4]);
static void mpc_doubleint_abs_e(const real_T x[6], real_T y[6]);
static real_T mpc_doubleint_xnrm2(int32_T n, const real_T x[16], int32_T ix0);
static void mpc_doubleint_xgeqrf(real_T b_A[16], real_T tau[4]);
static void mpc_doubleint_qr(const real_T b_A[16], real_T Q[16], real_T R[16]);
static real_T mpc_doubleint_KWIKfactor(const real_T b_Ac[24], const int16_T iC[6],
  int16_T nA, const real_T b_Linv[16], real_T RLinv[16], real_T D[16], real_T
  b_H[16], int16_T n);
static void mpc_doubleint_DropConstraint(int16_T kDrop, int16_T iA[6], int16_T
  *nA, int16_T iC[6]);
static void mpc_doubleint_abs(const real_T x[4], real_T y[4]);
static void mpc_doubleint_qpkwik(const real_T b_Linv[16], const real_T b_Hinv[16],
  const real_T f[4], const real_T b_Ac[24], const real_T b[6], int16_T iA[6],
  int16_T b_maxiter, real_T FeasTol, real_T x[4], real_T lambda[6], real_T
  *status);

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
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  mpc_doubleint_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  mpc_doubleint_step();
  mpc_doubleint_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  mpc_doubleint_step();
  mpc_doubleint_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  mpc_doubleint_step();
  mpc_doubleint_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Function for MATLAB Function: '<S2>/optimizer' */
static void mpc_doubleint_Unconstrained(const real_T b_Hinv[16], const real_T f
  [4], real_T x[4], int16_T n)
{
  int16_T i;
  for (i = 1; i <= n; i++) {
    x[i - 1] = ((-b_Hinv[i - 1] * f[0] + -b_Hinv[i + 3] * f[1]) + -b_Hinv[i + 7]
                * f[2]) + -b_Hinv[i + 11] * f[3];
  }
}

/* Function for MATLAB Function: '<S2>/optimizer' */
static real_T mpc_doubleint_norm(const real_T x[4])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  scale = 2.2250738585072014E-308;
  absxk = fabs(x[0]);
  if (absxk > 2.2250738585072014E-308) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    y = t * t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[3]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrt(y);
}

/* Function for MATLAB Function: '<S2>/optimizer' */
static void mpc_doubleint_abs_e(const real_T x[6], real_T y[6])
{
  int32_T k;
  for (k = 0; k < 6; k++) {
    y[k] = fabs(x[k]);
  }
}

/* Function for MATLAB Function: '<S2>/optimizer' */
static real_T mpc_doubleint_xnrm2(int32_T n, const real_T x[16], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 2.2250738585072014E-308;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
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

/* Function for MATLAB Function: '<S2>/optimizer' */
static void mpc_doubleint_xgeqrf(real_T b_A[16], real_T tau[4])
{
  real_T work[4];
  real_T b_atmp;
  real_T xnorm;
  int32_T knt;
  int32_T lastv;
  int32_T lastc;
  int32_T coltop;
  int32_T ia;
  int32_T ix;
  real_T b_c;
  int32_T g;
  int32_T b_ia;
  int32_T b_ix;
  int32_T exitg1;
  boolean_T exitg2;
  work[0] = 0.0;
  work[1] = 0.0;
  work[2] = 0.0;
  work[3] = 0.0;
  b_atmp = b_A[0];
  b_c = 0.0;
  xnorm = mpc_doubleint_xnrm2(3, b_A, 2);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(b_A[0], xnorm);
    if (b_A[0] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        for (lastc = 1; lastc + 1 < 5; lastc++) {
          b_A[lastc] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        b_atmp *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(b_atmp, mpc_doubleint_xnrm2(3, b_A, 2));
      if (b_atmp >= 0.0) {
        xnorm = -xnorm;
      }

      b_c = (xnorm - b_atmp) / xnorm;
      b_atmp = 1.0 / (b_atmp - xnorm);
      for (lastc = 1; lastc + 1 < 5; lastc++) {
        b_A[lastc] *= b_atmp;
      }

      for (lastv = 1; lastv <= knt; lastv++) {
        xnorm *= 1.0020841800044864E-292;
      }

      b_atmp = xnorm;
    } else {
      b_c = (xnorm - b_A[0]) / xnorm;
      b_atmp = 1.0 / (b_A[0] - xnorm);
      for (lastv = 1; lastv + 1 < 5; lastv++) {
        b_A[lastv] *= b_atmp;
      }

      b_atmp = xnorm;
    }
  }

  tau[0] = b_c;
  b_A[0] = b_atmp;
  b_atmp = b_A[0];
  b_A[0] = 1.0;
  knt = 4;
  if (b_c != 0.0) {
    lastv = 4;
    lastc = 3;
    while ((lastv > 0) && (b_A[lastc] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = 3;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      coltop = ((lastc - 1) << 2) + 5;
      ia = coltop;
      do {
        exitg1 = 0;
        if (ia <= (coltop + lastv) - 1) {
          if (b_A[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      for (coltop = 1; coltop <= lastc; coltop++) {
        work[coltop - 1] = 0.0;
      }

      coltop = 0;
      ia = ((lastc - 1) << 2) + 5;
      for (b_ix = 5; b_ix <= ia; b_ix += 4) {
        ix = 0;
        b_c = 0.0;
        g = (b_ix + lastv) - 1;
        for (b_ia = b_ix; b_ia <= g; b_ia++) {
          b_c += b_A[b_ia - 1] * b_A[ix];
          ix++;
        }

        work[coltop] += b_c;
        coltop++;
      }
    }

    if (!(-tau[0] == 0.0)) {
      coltop = 0;
      for (ia = 1; ia <= lastc; ia++) {
        if (work[coltop] != 0.0) {
          b_c = work[coltop] * -tau[0];
          b_ix = 0;
          ix = lastv + knt;
          for (g = knt; g + 1 <= ix; g++) {
            b_A[g] += b_A[b_ix] * b_c;
            b_ix++;
          }
        }

        coltop++;
        knt += 4;
      }
    }
  }

  b_A[0] = b_atmp;
  b_atmp = b_A[5];
  b_c = 0.0;
  xnorm = mpc_doubleint_xnrm2(2, b_A, 7);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(b_A[5], xnorm);
    if (b_A[5] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        for (lastc = 6; lastc + 1 < 9; lastc++) {
          b_A[lastc] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        b_atmp *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(b_atmp, mpc_doubleint_xnrm2(2, b_A, 7));
      if (b_atmp >= 0.0) {
        xnorm = -xnorm;
      }

      b_c = (xnorm - b_atmp) / xnorm;
      b_atmp = 1.0 / (b_atmp - xnorm);
      for (lastc = 6; lastc + 1 < 9; lastc++) {
        b_A[lastc] *= b_atmp;
      }

      for (lastv = 1; lastv <= knt; lastv++) {
        xnorm *= 1.0020841800044864E-292;
      }

      b_atmp = xnorm;
    } else {
      b_c = (xnorm - b_A[5]) / xnorm;
      b_atmp = 1.0 / (b_A[5] - xnorm);
      for (lastv = 6; lastv + 1 < 9; lastv++) {
        b_A[lastv] *= b_atmp;
      }

      b_atmp = xnorm;
    }
  }

  tau[1] = b_c;
  b_A[5] = b_atmp;
  b_atmp = b_A[5];
  b_A[5] = 1.0;
  knt = 9;
  if (b_c != 0.0) {
    lastv = 3;
    lastc = 7;
    while ((lastv > 0) && (b_A[lastc] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = 2;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      coltop = ((lastc - 1) << 2) + 10;
      ia = coltop;
      do {
        exitg1 = 0;
        if (ia <= (coltop + lastv) - 1) {
          if (b_A[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      for (coltop = 1; coltop <= lastc; coltop++) {
        work[coltop - 1] = 0.0;
      }

      coltop = 0;
      ia = ((lastc - 1) << 2) + 10;
      for (b_ix = 10; b_ix <= ia; b_ix += 4) {
        ix = 5;
        b_c = 0.0;
        g = (b_ix + lastv) - 1;
        for (b_ia = b_ix; b_ia <= g; b_ia++) {
          b_c += b_A[b_ia - 1] * b_A[ix];
          ix++;
        }

        work[coltop] += b_c;
        coltop++;
      }
    }

    if (!(-tau[1] == 0.0)) {
      coltop = 0;
      for (ia = 1; ia <= lastc; ia++) {
        if (work[coltop] != 0.0) {
          b_c = work[coltop] * -tau[1];
          b_ix = 5;
          ix = lastv + knt;
          for (g = knt; g + 1 <= ix; g++) {
            b_A[g] += b_A[b_ix] * b_c;
            b_ix++;
          }
        }

        coltop++;
        knt += 4;
      }
    }
  }

  b_A[5] = b_atmp;
  b_atmp = b_A[10];
  b_c = 0.0;
  xnorm = mpc_doubleint_xnrm2(1, b_A, 12);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(b_A[10], xnorm);
    if (b_A[10] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        for (lastc = 11; lastc + 1 < 13; lastc++) {
          b_A[lastc] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        b_atmp *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(b_atmp, mpc_doubleint_xnrm2(1, b_A, 12));
      if (b_atmp >= 0.0) {
        xnorm = -xnorm;
      }

      b_c = (xnorm - b_atmp) / xnorm;
      b_atmp = 1.0 / (b_atmp - xnorm);
      for (lastc = 11; lastc + 1 < 13; lastc++) {
        b_A[lastc] *= b_atmp;
      }

      for (lastv = 1; lastv <= knt; lastv++) {
        xnorm *= 1.0020841800044864E-292;
      }

      b_atmp = xnorm;
    } else {
      b_c = (xnorm - b_A[10]) / xnorm;
      b_atmp = 1.0 / (b_A[10] - xnorm);
      for (lastv = 11; lastv + 1 < 13; lastv++) {
        b_A[lastv] *= b_atmp;
      }

      b_atmp = xnorm;
    }
  }

  tau[2] = b_c;
  b_A[10] = b_atmp;
  b_atmp = b_A[10];
  b_A[10] = 1.0;
  knt = 14;
  if (b_c != 0.0) {
    lastv = 2;
    lastc = 11;
    while ((lastv > 0) && (b_A[lastc] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = 1;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      ia = 15;
      do {
        exitg1 = 0;
        if (ia <= lastv + 14) {
          if (b_A[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc = 0;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      coltop = 1;
      while (coltop <= 1) {
        work[0] = 0.0;
        coltop = 2;
      }

      coltop = 0;
      b_ix = 15;
      while (b_ix <= 15) {
        ix = 10;
        b_c = 0.0;
        g = lastv + 14;
        for (b_ia = 15; b_ia <= g; b_ia++) {
          b_c += b_A[b_ia - 1] * b_A[ix];
          ix++;
        }

        work[coltop] += b_c;
        coltop++;
        b_ix = 19;
      }
    }

    if (!(-tau[2] == 0.0)) {
      coltop = 0;
      ia = 1;
      while (ia <= lastc) {
        if (work[coltop] != 0.0) {
          b_c = work[coltop] * -tau[2];
          b_ix = 10;
          ix = lastv + knt;
          for (g = knt; g + 1 <= ix; g++) {
            b_A[g] += b_A[b_ix] * b_c;
            b_ix++;
          }
        }

        coltop++;
        knt += 4;
        ia = 2;
      }
    }
  }

  b_A[10] = b_atmp;
  tau[3] = 0.0;
}

/* Function for MATLAB Function: '<S2>/optimizer' */
static void mpc_doubleint_qr(const real_T b_A[16], real_T Q[16], real_T R[16])
{
  real_T c_A[16];
  real_T tau[4];
  int32_T d_i;
  real_T work[4];
  int32_T lastc;
  int32_T coltop;
  int32_T ix;
  real_T c;
  int32_T iac;
  int32_T d;
  int32_T b_ia;
  int32_T jy;
  int32_T exitg1;
  boolean_T exitg2;
  memcpy(&c_A[0], &b_A[0], sizeof(real_T) << 4U);
  mpc_doubleint_xgeqrf(c_A, tau);
  for (d_i = 0; d_i + 1 < 2; d_i++) {
    R[d_i] = c_A[d_i];
  }

  for (d_i = 1; d_i + 1 < 5; d_i++) {
    R[d_i] = 0.0;
  }

  work[0] = 0.0;
  for (d_i = 0; d_i + 1 < 3; d_i++) {
    R[d_i + 4] = c_A[d_i + 4];
  }

  for (d_i = 2; d_i + 1 < 5; d_i++) {
    R[d_i + 4] = 0.0;
  }

  work[1] = 0.0;
  for (d_i = 0; d_i + 1 < 4; d_i++) {
    R[d_i + 8] = c_A[d_i + 8];
  }

  for (d_i = 3; d_i + 1 < 5; d_i++) {
    R[d_i + 8] = 0.0;
  }

  work[2] = 0.0;
  for (d_i = 0; d_i + 1 < 5; d_i++) {
    R[d_i + 12] = c_A[d_i + 12];
  }

  work[3] = 0.0;
  c_A[15] = 1.0 - tau[3];
  for (d_i = 1; d_i < 4; d_i++) {
    c_A[15 - d_i] = 0.0;
  }

  c_A[10] = 1.0;
  if (tau[2] != 0.0) {
    d_i = 2;
    lastc = 11;
    while ((d_i > 0) && (c_A[lastc] == 0.0)) {
      d_i--;
      lastc--;
    }

    lastc = 1;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      jy = 11;
      do {
        exitg1 = 0;
        if (jy + 4 <= d_i + 14) {
          if (c_A[jy + 3] != 0.0) {
            exitg1 = 1;
          } else {
            jy++;
          }
        } else {
          lastc = 0;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    d_i = 0;
    lastc = 0;
  }

  if (d_i > 0) {
    if (lastc != 0) {
      coltop = 1;
      while (coltop <= 1) {
        work[0] = 0.0;
        coltop = 2;
      }

      coltop = 0;
      iac = 15;
      while (iac <= 15) {
        ix = 11;
        c = 0.0;
        d = d_i + 14;
        for (b_ia = 15; b_ia <= d; b_ia++) {
          c += c_A[b_ia - 1] * c_A[ix - 1];
          ix++;
        }

        work[coltop] += c;
        coltop++;
        iac = 19;
      }
    }

    if (!(-tau[2] == 0.0)) {
      coltop = 14;
      jy = 0;
      iac = 1;
      while (iac <= lastc) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau[2];
          ix = 11;
          d = d_i + coltop;
          for (b_ia = coltop; b_ia + 1 <= d; b_ia++) {
            c_A[b_ia] += c_A[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        coltop += 4;
        iac = 2;
      }
    }
  }

  for (lastc = 11; lastc + 1 < 13; lastc++) {
    c_A[lastc] *= -tau[2];
  }

  c_A[10] = 1.0 - tau[2];
  for (d_i = 1; d_i < 3; d_i++) {
    c_A[10 - d_i] = 0.0;
  }

  c_A[5] = 1.0;
  if (tau[1] != 0.0) {
    lastc = 7;
    while ((d_i > 0) && (c_A[lastc] == 0.0)) {
      d_i--;
      lastc--;
    }

    lastc = 2;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      coltop = ((lastc - 1) << 2) + 6;
      jy = coltop;
      do {
        exitg1 = 0;
        if (jy + 4 <= (coltop + d_i) + 3) {
          if (c_A[jy + 3] != 0.0) {
            exitg1 = 1;
          } else {
            jy++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    d_i = 0;
    lastc = 0;
  }

  if (d_i > 0) {
    if (lastc != 0) {
      for (coltop = 1; coltop <= lastc; coltop++) {
        work[coltop - 1] = 0.0;
      }

      coltop = 0;
      jy = ((lastc - 1) << 2) + 10;
      for (iac = 10; iac <= jy; iac += 4) {
        ix = 6;
        c = 0.0;
        d = (iac + d_i) - 1;
        for (b_ia = iac; b_ia <= d; b_ia++) {
          c += c_A[b_ia - 1] * c_A[ix - 1];
          ix++;
        }

        work[coltop] += c;
        coltop++;
      }
    }

    if (!(-tau[1] == 0.0)) {
      coltop = 9;
      jy = 0;
      for (iac = 1; iac <= lastc; iac++) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau[1];
          ix = 6;
          d = d_i + coltop;
          for (b_ia = coltop; b_ia + 1 <= d; b_ia++) {
            c_A[b_ia] += c_A[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        coltop += 4;
      }
    }
  }

  for (lastc = 6; lastc + 1 < 9; lastc++) {
    c_A[lastc] *= -tau[1];
  }

  c_A[5] = 1.0 - tau[1];
  d_i = 1;
  while (d_i <= 1) {
    c_A[4] = 0.0;
    d_i = 2;
  }

  c_A[0] = 1.0;
  if (tau[0] != 0.0) {
    d_i = 4;
    lastc = 3;
    while ((d_i > 0) && (c_A[lastc] == 0.0)) {
      d_i--;
      lastc--;
    }

    lastc = 3;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      coltop = ((lastc - 1) << 2) + 1;
      jy = coltop;
      do {
        exitg1 = 0;
        if (jy + 4 <= (coltop + d_i) + 3) {
          if (c_A[jy + 3] != 0.0) {
            exitg1 = 1;
          } else {
            jy++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    d_i = 0;
    lastc = 0;
  }

  if (d_i > 0) {
    if (lastc != 0) {
      for (coltop = 1; coltop <= lastc; coltop++) {
        work[coltop - 1] = 0.0;
      }

      coltop = 0;
      jy = ((lastc - 1) << 2) + 5;
      for (iac = 5; iac <= jy; iac += 4) {
        ix = 1;
        c = 0.0;
        d = (iac + d_i) - 1;
        for (b_ia = iac; b_ia <= d; b_ia++) {
          c += c_A[b_ia - 1] * c_A[ix - 1];
          ix++;
        }

        work[coltop] += c;
        coltop++;
      }
    }

    if (!(-tau[0] == 0.0)) {
      coltop = 4;
      jy = 0;
      for (iac = 1; iac <= lastc; iac++) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau[0];
          ix = 1;
          d = d_i + coltop;
          for (b_ia = coltop; b_ia + 1 <= d; b_ia++) {
            c_A[b_ia] += c_A[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        coltop += 4;
      }
    }
  }

  for (lastc = 1; lastc + 1 < 5; lastc++) {
    c_A[lastc] *= -tau[0];
  }

  c_A[0] = 1.0 - tau[0];
  for (d_i = 0; d_i < 4; d_i++) {
    Q[d_i << 2] = c_A[d_i << 2];
    Q[1 + (d_i << 2)] = c_A[(d_i << 2) + 1];
    Q[2 + (d_i << 2)] = c_A[(d_i << 2) + 2];
    Q[3 + (d_i << 2)] = c_A[(d_i << 2) + 3];
  }
}

/* Function for MATLAB Function: '<S2>/optimizer' */
static real_T mpc_doubleint_KWIKfactor(const real_T b_Ac[24], const int16_T iC[6],
  int16_T nA, const real_T b_Linv[16], real_T RLinv[16], real_T D[16], real_T
  b_H[16], int16_T n)
{
  real_T Status;
  real_T TL[16];
  real_T QQ[16];
  real_T RR[16];
  int16_T i;
  int16_T f_i;
  int16_T d_k;
  int32_T i_0;
  int32_T iC_0;
  int32_T i_1;
  int32_T exitg1;
  Status = 1.0;
  for (i_0 = 0; i_0 < 16; i_0++) {
    RLinv[i_0] = 0.0;
  }

  for (i = 1; i <= nA; i++) {
    RLinv[(i - 1) << 2] = 0.0;
    RLinv[1 + ((i - 1) << 2)] = 0.0;
    RLinv[2 + ((i - 1) << 2)] = 0.0;
    RLinv[3 + ((i - 1) << 2)] = 0.0;
    iC_0 = iC[i - 1];
    i_1 = i - 1;
    for (i_0 = 0; i_0 < 4; i_0++) {
      RLinv[i_0 + (i_1 << 2)] = 0.0;
      RLinv[i_0 + (i_1 << 2)] += b_Ac[iC_0 - 1] * b_Linv[i_0];
      RLinv[i_0 + (i_1 << 2)] += b_Linv[i_0 + 4] * b_Ac[iC_0 + 5];
      RLinv[i_0 + (i_1 << 2)] += b_Linv[i_0 + 8] * b_Ac[iC_0 + 11];
      RLinv[i_0 + (i_1 << 2)] += b_Linv[i_0 + 12] * b_Ac[iC_0 + 17];
    }
  }

  mpc_doubleint_qr(RLinv, QQ, RR);
  i = 1;
  do {
    exitg1 = 0;
    if (i <= nA) {
      if (fabs(RR[(((i - 1) << 2) + i) - 1]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      for (i = 1; i <= n; i++) {
        for (f_i = 1; f_i <= n; f_i++) {
          TL[(i + ((f_i - 1) << 2)) - 1] = ((b_Linv[((i - 1) << 2) + 1] * QQ
            [((f_i - 1) << 2) + 1] + b_Linv[(i - 1) << 2] * QQ[(f_i - 1) << 2])
            + b_Linv[((i - 1) << 2) + 2] * QQ[((f_i - 1) << 2) + 2]) + b_Linv
            [((i - 1) << 2) + 3] * QQ[((f_i - 1) << 2) + 3];
        }
      }

      for (i_0 = 0; i_0 < 16; i_0++) {
        RLinv[i_0] = 0.0;
      }

      for (i = nA; i > 0; i--) {
        RLinv[(i + ((i - 1) << 2)) - 1] = 1.0;
        for (f_i = i; f_i <= nA; f_i++) {
          RLinv[(i + ((f_i - 1) << 2)) - 1] /= RR[(((i - 1) << 2) + i) - 1];
        }

        if (i > 1) {
          for (f_i = 1; f_i < i; f_i++) {
            for (d_k = i; d_k <= nA; d_k++) {
              RLinv[(f_i + ((d_k - 1) << 2)) - 1] -= RR[(((i - 1) << 2) + f_i) -
                1] * RLinv[(((d_k - 1) << 2) + i) - 1];
            }
          }
        }
      }

      for (i = 1; i <= n; i++) {
        for (f_i = i; f_i <= n; f_i++) {
          b_H[(i + ((f_i - 1) << 2)) - 1] = 0.0;
          for (d_k = (int16_T)(nA + 1); d_k <= n; d_k++) {
            b_H[(i + ((f_i - 1) << 2)) - 1] -= TL[(((d_k - 1) << 2) + i) - 1] *
              TL[(((d_k - 1) << 2) + f_i) - 1];
          }

          b_H[(f_i + ((i - 1) << 2)) - 1] = b_H[(((f_i - 1) << 2) + i) - 1];
        }
      }

      for (i = 1; i <= nA; i++) {
        for (f_i = 1; f_i <= n; f_i++) {
          D[(f_i + ((i - 1) << 2)) - 1] = 0.0;
          for (d_k = i; d_k <= nA; d_k++) {
            D[(f_i + ((i - 1) << 2)) - 1] += TL[(((d_k - 1) << 2) + f_i) - 1] *
              RLinv[(((d_k - 1) << 2) + i) - 1];
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S2>/optimizer' */
static void mpc_doubleint_DropConstraint(int16_T kDrop, int16_T iA[6], int16_T
  *nA, int16_T iC[6])
{
  int16_T i;
  int32_T tmp;
  iA[iC[kDrop - 1] - 1] = 0;
  if (kDrop < *nA) {
    tmp = *nA - 1;
    if (tmp < -32768) {
      tmp = -32768;
    }

    for (i = kDrop; i <= (int16_T)tmp; i++) {
      iC[i - 1] = iC[i];
    }
  }

  iC[*nA - 1] = 0;
  tmp = *nA - 1;
  if (tmp < -32768) {
    tmp = -32768;
  }

  *nA = (int16_T)tmp;
}

/* Function for MATLAB Function: '<S2>/optimizer' */
static void mpc_doubleint_abs(const real_T x[4], real_T y[4])
{
  y[0] = fabs(x[0]);
  y[1] = fabs(x[1]);
  y[2] = fabs(x[2]);
  y[3] = fabs(x[3]);
}

/* Function for MATLAB Function: '<S2>/optimizer' */
static void mpc_doubleint_qpkwik(const real_T b_Linv[16], const real_T b_Hinv[16],
  const real_T f[4], const real_T b_Ac[24], const real_T b[6], int16_T iA[6],
  int16_T b_maxiter, real_T FeasTol, real_T x[4], real_T lambda[6], real_T
  *status)
{
  real_T r[4];
  real_T rMin;
  real_T RLinv[16];
  real_T D[16];
  real_T b_H[16];
  real_T U[16];
  real_T cTol[6];
  boolean_T cTolComputed;
  int16_T iC[6];
  int16_T nA;
  real_T Opt[8];
  real_T Rhs[8];
  boolean_T DualFeasible;
  boolean_T ColdReset;
  int16_T kDrop;
  real_T Xnorm0;
  real_T cMin;
  int16_T kNext;
  real_T AcRow[4];
  real_T z[4];
  real_T zTa;
  real_T t;
  int16_T iSave;
  uint16_T q;
  uint16_T b_x;
  real_T varargin_1[6];
  int32_T ix;
  int32_T i;
  int32_T tmp;
  int32_T exitg1;
  int32_T exitg2;
  int32_T exitg3;
  boolean_T exitg4;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *status = 1.0;
  x[0] = 0.0;
  r[0] = 0.0;
  x[1] = 0.0;
  r[1] = 0.0;
  x[2] = 0.0;
  r[2] = 0.0;
  x[3] = 0.0;
  r[3] = 0.0;
  rMin = 0.0;
  cTolComputed = false;
  for (i = 0; i < 6; i++) {
    lambda[i] = 0.0;
    cTol[i] = 1.0;
    iC[i] = 0;
  }

  nA = 0;
  for (kNext = 0; kNext < 6; kNext++) {
    if (iA[kNext] == 1) {
      i = nA + 1;
      if (i > 32767) {
        i = 32767;
      }

      nA = (int16_T)i;
      iC[(int16_T)i - 1] = (int16_T)(kNext + 1);
    }
  }

  guard1 = false;
  if (nA > 0) {
    for (i = 0; i < 8; i++) {
      Opt[i] = 0.0;
    }

    Rhs[0] = f[0];
    Rhs[4] = 0.0;
    Rhs[1] = f[1];
    Rhs[5] = 0.0;
    Rhs[2] = f[2];
    Rhs[6] = 0.0;
    Rhs[3] = f[3];
    Rhs[7] = 0.0;
    DualFeasible = false;
    i = 3 * nA;
    if (i > 32767) {
      i = 32767;
    }

    if ((int16_T)i > 50) {
      kNext = (int16_T)i;
    } else {
      kNext = 50;
    }

    q = (uint16_T)(kNext / 10U);
    b_x = (uint16_T)((uint32_T)kNext - q * 10);
    if ((b_x > 0) && (b_x >= 5)) {
      q++;
    }

    ColdReset = false;
    do {
      exitg3 = 0;
      if ((!DualFeasible) && (nA > 0) && ((int32_T)*status <= b_maxiter)) {
        Xnorm0 = mpc_doubleint_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, D, b_H, 4);
        if (Xnorm0 < 0.0) {
          if (ColdReset) {
            *status = -2.0;
            exitg3 = 2;
          } else {
            nA = 0;
            for (i = 0; i < 6; i++) {
              iA[i] = 0;
              iC[i] = 0;
            }

            ColdReset = true;
          }
        } else {
          for (kNext = 1; kNext <= nA; kNext++) {
            i = 4 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            Rhs[i - 1] = b[iC[kNext - 1] - 1];
            for (kDrop = kNext; kDrop <= nA; kDrop++) {
              U[(kDrop + ((kNext - 1) << 2)) - 1] = 0.0;
              for (iSave = 1; iSave <= nA; iSave++) {
                U[(kDrop + ((kNext - 1) << 2)) - 1] += RLinv[(((iSave - 1) << 2)
                  + kDrop) - 1] * RLinv[(((iSave - 1) << 2) + kNext) - 1];
              }

              U[(kNext + ((kDrop - 1) << 2)) - 1] = U[(((kNext - 1) << 2) +
                kDrop) - 1];
            }
          }

          for (kNext = 0; kNext < 4; kNext++) {
            i = kNext + 1;
            Opt[kNext] = ((b_H[i - 1] * Rhs[0] + b_H[i + 3] * Rhs[1]) + b_H[i +
                          7] * Rhs[2]) + b_H[i + 11] * Rhs[3];
            for (kDrop = 1; kDrop <= nA; kDrop++) {
              i = 4 + kDrop;
              if (i > 32767) {
                i = 32767;
              }

              Opt[kNext] += D[((kDrop - 1) << 2) + kNext] * Rhs[i - 1];
            }
          }

          for (kNext = 1; kNext <= nA; kNext++) {
            i = 4 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            Opt[i - 1] = ((D[((kNext - 1) << 2) + 1] * Rhs[1] + D[(kNext - 1) <<
                           2] * Rhs[0]) + D[((kNext - 1) << 2) + 2] * Rhs[2]) +
              D[((kNext - 1) << 2) + 3] * Rhs[3];
            for (kDrop = 1; kDrop <= nA; kDrop++) {
              i = 4 + kNext;
              if (i > 32767) {
                i = 32767;
              }

              ix = 4 + kNext;
              if (ix > 32767) {
                ix = 32767;
              }

              tmp = 4 + kDrop;
              if (tmp > 32767) {
                tmp = 32767;
              }

              Opt[i - 1] = U[(((kDrop - 1) << 2) + kNext) - 1] * Rhs[tmp - 1] +
                Opt[ix - 1];
            }
          }

          Xnorm0 = -1.0E-12;
          kDrop = 0;
          for (kNext = 1; kNext <= nA; kNext++) {
            i = 4 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            lambda[iC[kNext - 1] - 1] = Opt[i - 1];
            i = 4 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            if ((Opt[i - 1] < Xnorm0) && (kNext <= nA)) {
              kDrop = kNext;
              i = 4 + kNext;
              if (i > 32767) {
                i = 32767;
              }

              Xnorm0 = Opt[i - 1];
            }
          }

          if (kDrop <= 0) {
            DualFeasible = true;
            x[0] = Opt[0];
            x[1] = Opt[1];
            x[2] = Opt[2];
            x[3] = Opt[3];
          } else {
            (*status)++;
            if ((int32_T)*status > q) {
              nA = 0;
              for (i = 0; i < 6; i++) {
                iA[i] = 0;
                iC[i] = 0;
              }

              ColdReset = true;
            } else {
              lambda[iC[kDrop - 1] - 1] = 0.0;
              mpc_doubleint_DropConstraint(kDrop, iA, &nA, iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          for (i = 0; i < 6; i++) {
            lambda[i] = 0.0;
          }

          mpc_doubleint_Unconstrained(b_Hinv, f, x, 4);
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    mpc_doubleint_Unconstrained(b_Hinv, f, x, 4);
    guard1 = true;
  }

  if (guard1) {
    Xnorm0 = mpc_doubleint_norm(x);
    do {
      exitg2 = 0;
      if ((int32_T)*status <= b_maxiter) {
        cMin = -FeasTol;
        kNext = 0;
        for (kDrop = 0; kDrop < 6; kDrop++) {
          if (!cTolComputed) {
            i = kDrop + 1;
            z[0] = b_Ac[i - 1] * x[0];
            z[1] = b_Ac[i + 5] * x[1];
            z[2] = b_Ac[i + 11] * x[2];
            z[3] = b_Ac[i + 17] * x[3];
            mpc_doubleint_abs(z, AcRow);
            i = 1;
            zTa = AcRow[0];
            if (rtIsNaN(AcRow[0])) {
              ix = 2;
              exitg4 = false;
              while ((!exitg4) && (ix < 5)) {
                i = ix;
                if (!rtIsNaN(AcRow[ix - 1])) {
                  zTa = AcRow[ix - 1];
                  exitg4 = true;
                } else {
                  ix++;
                }
              }
            }

            if (i < 4) {
              while (i + 1 < 5) {
                if (AcRow[i] > zTa) {
                  zTa = AcRow[i];
                }

                i++;
              }
            }

            if (!((cTol[kDrop] > zTa) || rtIsNaN(zTa))) {
              cTol[kDrop] = zTa;
            }
          }

          if (iA[kDrop] == 0) {
            i = kDrop + 1;
            zTa = ((((b_Ac[i - 1] * x[0] + b_Ac[i + 5] * x[1]) + b_Ac[i + 11] *
                     x[2]) + b_Ac[i + 17] * x[3]) - b[kDrop]) / cTol[kDrop];
            if (zTa < cMin) {
              cMin = zTa;
              kNext = (int16_T)(kDrop + 1);
            }
          }
        }

        cTolComputed = true;
        if (kNext <= 0) {
          exitg2 = 1;
        } else {
          do {
            exitg1 = 0;
            if ((kNext > 0) && ((int32_T)*status <= b_maxiter)) {
              guard2 = false;
              if (nA == 0) {
                for (i = 0; i < 4; i++) {
                  cMin = b_Hinv[i + 12] * b_Ac[kNext + 17] + (b_Hinv[i + 8] *
                    b_Ac[kNext + 11] + (b_Hinv[i + 4] * b_Ac[kNext + 5] +
                                        b_Ac[kNext - 1] * b_Hinv[i]));
                  z[i] = cMin;
                }

                guard2 = true;
              } else {
                cMin = mpc_doubleint_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, D,
                  b_H, 4);
                if (cMin <= 0.0) {
                  *status = -2.0;
                  exitg1 = 1;
                } else {
                  for (i = 0; i < 4; i++) {
                    U[i << 2] = -b_H[i << 2];
                    U[1 + (i << 2)] = -b_H[(i << 2) + 1];
                    U[2 + (i << 2)] = -b_H[(i << 2) + 2];
                    U[3 + (i << 2)] = -b_H[(i << 2) + 3];
                  }

                  for (i = 0; i < 4; i++) {
                    cMin = U[i + 12] * b_Ac[kNext + 17] + (U[i + 8] * b_Ac[kNext
                      + 11] + (U[i + 4] * b_Ac[kNext + 5] + b_Ac[kNext - 1] *
                               U[i]));
                    z[i] = cMin;
                  }

                  for (kDrop = 1; kDrop <= nA; kDrop++) {
                    r[kDrop - 1] = ((D[((kDrop - 1) << 2) + 1] * b_Ac[kNext + 5]
                                     + D[(kDrop - 1) << 2] * b_Ac[kNext - 1]) +
                                    D[((kDrop - 1) << 2) + 2] * b_Ac[kNext + 11])
                      + D[((kDrop - 1) << 2) + 3] * b_Ac[kNext + 17];
                  }

                  guard2 = true;
                }
              }

              if (guard2) {
                kDrop = 0;
                cMin = 0.0;
                DualFeasible = true;
                ColdReset = true;
                if (nA > 0) {
                  iSave = 1;
                  exitg4 = false;
                  while ((!exitg4) && (iSave <= nA)) {
                    if (r[iSave - 1] >= 1.0E-12) {
                      ColdReset = false;
                      exitg4 = true;
                    } else {
                      iSave++;
                    }
                  }
                }

                if (!((nA == 0) || ColdReset)) {
                  for (iSave = 1; iSave <= nA; iSave++) {
                    if (r[iSave - 1] > 1.0E-12) {
                      zTa = lambda[iC[iSave - 1] - 1] / r[iSave - 1];
                      if ((kDrop == 0) || (zTa < rMin)) {
                        rMin = zTa;
                        kDrop = iSave;
                      }
                    }
                  }

                  if (kDrop > 0) {
                    cMin = rMin;
                    DualFeasible = false;
                  }
                }

                zTa = ((b_Ac[kNext - 1] * z[0] + b_Ac[kNext + 5] * z[1]) +
                       b_Ac[kNext + 11] * z[2]) + b_Ac[kNext + 17] * z[3];
                if (zTa <= 0.0) {
                  zTa = 0.0;
                  ColdReset = true;
                } else {
                  zTa = (b[kNext - 1] - (((b_Ac[kNext - 1] * x[0] + b_Ac[kNext +
                            5] * x[1]) + b_Ac[kNext + 11] * x[2]) + b_Ac[kNext +
                          17] * x[3])) / zTa;
                  ColdReset = false;
                }

                if (DualFeasible && ColdReset) {
                  *status = -1.0;
                  exitg1 = 1;
                } else {
                  if (ColdReset) {
                    t = cMin;
                  } else if (DualFeasible) {
                    t = zTa;
                  } else if ((cMin < zTa) || rtIsNaN(zTa)) {
                    t = cMin;
                  } else {
                    t = zTa;
                  }

                  for (iSave = 1; iSave <= nA; iSave++) {
                    lambda[iC[iSave - 1] - 1] -= r[iSave - 1] * t;
                    if ((iC[iSave - 1] <= 6) && (lambda[iC[iSave - 1] - 1] < 0.0))
                    {
                      lambda[iC[iSave - 1] - 1] = 0.0;
                    }
                  }

                  lambda[kNext - 1] += t;
                  if (t == cMin) {
                    mpc_doubleint_DropConstraint(kDrop, iA, &nA, iC);
                  }

                  if (!ColdReset) {
                    x[0] += t * z[0];
                    x[1] += t * z[1];
                    x[2] += t * z[2];
                    x[3] += t * z[3];
                    if (t == zTa) {
                      if (nA == 4) {
                        *status = -1.0;
                        exitg1 = 1;
                      } else {
                        i = nA + 1;
                        if (i > 32767) {
                          i = 32767;
                        }

                        nA = (int16_T)i;
                        iC[(int16_T)i - 1] = kNext;
                        kDrop = (int16_T)i;
                        while ((kDrop > 1) && (!(iC[kDrop - 1] > iC[kDrop - 2])))
                        {
                          iSave = iC[kDrop - 1];
                          iC[kDrop - 1] = iC[kDrop - 2];
                          iC[kDrop - 2] = iSave;
                          kDrop--;
                        }

                        iA[kNext - 1] = 1;
                        kNext = 0;
                        (*status)++;
                      }
                    } else {
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                }
              }
            } else {
              cMin = mpc_doubleint_norm(x);
              if (fabs(cMin - Xnorm0) > 0.001) {
                Xnorm0 = cMin;
                mpc_doubleint_abs_e(b, varargin_1);
                for (i = 0; i < 6; i++) {
                  if (varargin_1[i] > 1.0) {
                    cTol[i] = varargin_1[i];
                  } else {
                    cTol[i] = 1.0;
                  }
                }

                cTolComputed = false;
              }

              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = 1;
          }
        }
      } else {
        *status = 0.0;
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
}

/* Model step function */
void mpc_doubleint_step(void)
{
  if (rtmIsMajorTimeStep(mpc_doubleint_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&mpc_doubleint_M->solverInfo,
                          ((mpc_doubleint_M->Timing.clockTick0+1)*
      mpc_doubleint_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(mpc_doubleint_M)) {
    mpc_doubleint_M->Timing.t[0] = rtsiGetT(&mpc_doubleint_M->solverInfo);
  }

  {
    real_T y_innov;
    real_T rseq[10];
    int32_T i;
    real_T f[4];
    real_T zopt[4];
    real_T unusedU0[6];
    int16_T iAnew[6];
    static const real_T b_Linv[16] = { 1.2467655273174882, -5.775405378140368,
      -2.2478221814675226, 0.0, 0.0, 7.5563609210741349, -3.2848129491700413,
      0.0, 0.0, 0.0, 8.2892573300825969, 0.0, 0.0, 0.0, 0.0,
      0.003162277660168379 };

    static const real_T b_Hinv[16] = { 39.962436121457358, -36.257372093625094,
      -18.632776494451914, 0.0, -36.257372093625094, 67.888586480571533,
      -27.228659816858, 0.0, -18.632776494451914, -27.228659816858,
      68.711787084328066, 0.0, 0.0, 0.0, 0.0, 9.9999999999999974E-6 };

    static const real_T b_Ac[24] = { -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, -0.0, -1.0,
      -1.0, 0.0, 1.0, 1.0, -0.0, -0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0 };

    static const real_T b_Ku1[3] = { 0.63332500000000025, 0.49170000000000025,
      0.36930000000000013 };

    static const int8_T b_Mu1[6] = { -1, -1, -1, 1, 1, 1 };

    static const real_T b_Kx[6] = { 1.5125000000000002, 1.9250000000000003,
      1.1550000000000002, 1.4250000000000003, 0.85200000000000009,
      1.0200000000000002 };

    static const real_T b_Kr[30] = { -0.005000000000000001,
      -0.020000000000000004, -0.045000000000000012, -0.080000000000000016,
      -0.12500000000000003, -0.18000000000000005, -0.24500000000000005,
      -0.32000000000000006, -0.40500000000000008, -0.50000000000000011, -0.0,
      -0.005000000000000001, -0.020000000000000004, -0.045000000000000012,
      -0.080000000000000016, -0.12500000000000003, -0.18000000000000005,
      -0.24500000000000005, -0.32000000000000006, -0.40500000000000008, -0.0,
      -0.0, -0.005000000000000001, -0.020000000000000004, -0.045000000000000012,
      -0.080000000000000016, -0.12500000000000003, -0.18000000000000005,
      -0.24500000000000005, -0.32000000000000006 };

    real_T rtb_last_mv;
    real_T tmp[6];
    real_T tmp_0;
    int32_T i_0;
    real_T rtb_xest_idx_0;
    real_T rtb_xest_idx_1;

    /* Outport: '<Root>/out' incorporates:
     *  Integrator: '<Root>/Integrator 2'
     */
    mpc_doubleint_Y.out = mpc_doubleint_X.Integrator2_CSTATE;

    /* Integrator: '<Root>/Integrator 1' */
    mpc_doubleint_B.Integrator1 = mpc_doubleint_X.Integrator1_CSTATE;
    if (rtmIsMajorTimeStep(mpc_doubleint_M)) {
      /* UnitDelay: '<S2>/last_mv' */
      rtb_last_mv = mpc_doubleint_DW.last_mv_DSTATE;

      /* MATLAB Function: '<S2>/optimizer' incorporates:
       *  Inport: '<Root>/ref'
       *  Integrator: '<Root>/Integrator 2'
       *  Memory: '<S2>/Memory'
       *  Memory: '<S2>/last_x'
       */
      /* MATLAB Function 'MPC Controller/MPC/optimizer': '<S17>:1' */
      /* '<S17>:1:13' coder.extrinsic('mpcblock_optimizer_double_mex'); */
      /* '<S17>:1:14' coder.extrinsic('mpcblock_optimizer_single_mex'); */
      /* '<S17>:1:15' coder.extrinsic('mpcblock_refmd_double_mex'); */
      /* '<S17>:1:16' coder.extrinsic('mpcblock_refmd_single_mex'); */
      /*  Parameters */
      /* '<S17>:1:19' isSimulation = coder.target('Sfun') && ~coder.target('RtwForRapid') && ~coder.target('RtwForSim'); */
      /* '<S17>:1:20' isAdaptive = false; */
      /* '<S17>:1:21' isLTV = false; */
      /* '<S17>:1:22' isDouble = isa(ref,'double'); */
      /* '<S17>:1:23' ZERO = zeros('like',ref); */
      /* '<S17>:1:24' ONE = ones('like',ref); */
      /*  Pre-allocate all the MEX block outputs for the simulation mode */
      /* '<S17>:1:29' if isSimulation */
      /*  Get reference and MD signals -- accounting for previewing */
      /* '<S17>:1:43' if isSimulation */
      /* '<S17>:1:50' else */
      /*  When doing code generation, use M code directly */
      /* '<S17>:1:52' [rseq, vseq, v] = mpcblock_refmd(ref,md,nv,ny,p,yoff,voff,no_md,no_ref,openloopflag, Rscale, MDscale); */
      for (i = 0; i < 10; i++) {
        rseq[i] = mpc_doubleint_U.ref;
      }

      /*  External MV override.   */
      /*  NOTE: old_u and ext_mv input signals are dimensionless but include offset */
      /* '<S17>:1:57' old_u = old_u - uoff; */
      /* '<S17>:1:58' if no_mv==ONE */
      /* '<S17>:1:59' delmv = zeros(nu,1,'like',ref); */
      /*  Obtain x[k|k] */
      /* '<S17>:1:67' xk = xk - xoff; */
      /*  Remove offset */
      /* '<S17>:1:68' if CustomEstimation==ONE */
      /* '<S17>:1:71' else */
      /*  Default state estimation.     */
      /*  Scale measured output and remove offset. */
      /* '<S17>:1:74' ym = ym.*Rscale(myindex) - myoff; */
      /*  Correct x(k|k-1) for possible external mv override. */
      /*  NOTE:  Offset was removed from x[k|k-1] at k=0. */
      /* '<S17>:1:77' xk = xk + Bu*delmv; */
      /*  Measurement upate to x(k|k) */
      /* '<S17>:1:79' ym_est = C(myindex,:)*xk + Dv(myindex,:)*v; */
      /* '<S17>:1:80' y_innov = ym - ym_est; */
      y_innov = mpc_doubleint_X.Integrator2_CSTATE - (0.0 *
        mpc_doubleint_DW.last_x_PreviousInput[0] +
        mpc_doubleint_DW.last_x_PreviousInput[1]);

      /* '<S17>:1:81' xest = xk + M*y_innov; */
      rtb_xest_idx_0 = 0.0931745141509576 * y_innov +
        mpc_doubleint_DW.last_x_PreviousInput[0];
      rtb_xest_idx_1 = 0.13185099127330174 * y_innov +
        mpc_doubleint_DW.last_x_PreviousInput[1];

      /*  Real-time MV target override */
      /*  Note: utargetValue is a vector length p*nu.   */
      /* '<S17>:1:86' if no_uref==ONE */
      /*  no external utarget */
      /* '<S17>:1:88' utargetValue = utarget; */
      /* '<S17>:1:96' if isSimulation */
      /* '<S17>:1:121' else */
      /*  When doing code generation, use M code directly */
      /* '<S17>:1:123' [u, cost, useq, status, iAout] = mpcblock_optimizer(... */
      /* '<S17>:1:124'             rseq, vseq, umin, umax, ymin, ymax, switch_in, xest, old_u, iA, ... */
      /* '<S17>:1:125'             isQP, nu, ny, degrees, Hinv, Kx, Ku1, Kut, Kr, Kv, Mlim, ... */
      /* '<S17>:1:126'             Mx, Mu1, Mv, z_degrees, utargetValue, p, uoff, voff, yoff, maxiter, CustomSolver, nxQP, openloopflag, ... */
      /* '<S17>:1:127'             lims_inport, no_umin, no_umax, no_ymin, no_ymax, switch_inport, ... */
      /* '<S17>:1:128'             no_switch, enable_value, return_cost, H, return_sequence, Linv, Ac, ... */
      /* '<S17>:1:129'             ywt, uwt, duwt, rhoeps, no_ywt, no_uwt, no_duwt, no_rhoeps,... */
      /* '<S17>:1:130'             Wy, Wdu, Jm, SuJm, Su1, Sx, Hv, Wu, I1, ... */
      /* '<S17>:1:131'             isAdaptive, isLTV, A, Bu, Bv, C, Dv, ... */
      /* '<S17>:1:132'             Mrows, nCC, Ecc, Fcc, Scc, Gcc); */
      f[0] = 0.0;
      f[1] = 0.0;
      f[2] = 0.0;
      f[3] = 0.0;
      for (i = 0; i < 3; i++) {
        tmp_0 = 0.0;
        for (i_0 = 0; i_0 < 10; i_0++) {
          tmp_0 += b_Kr[10 * i + i_0] * rseq[i_0];
        }

        f[i] = ((b_Kx[(i << 1) + 1] * rtb_xest_idx_1 + b_Kx[i << 1] *
                 rtb_xest_idx_0) + tmp_0) + b_Ku1[i] * rtb_last_mv;
      }

      for (i = 0; i < 6; i++) {
        iAnew[i] = mpc_doubleint_DW.Memory_PreviousInput[i];
        tmp[i] = -(((0.0 * rtb_xest_idx_0 + 0.0 * rtb_xest_idx_1) + 1.0) +
                   (real_T)b_Mu1[i] * rtb_last_mv);
      }

      mpc_doubleint_qpkwik(b_Linv, b_Hinv, f, b_Ac, tmp, iAnew, 120, 1.0E-6,
                           zopt, unusedU0, &rtb_xest_idx_0);
      if (rtb_xest_idx_0 <= 0.0) {
        zopt[0] = 0.0;
      }

      rtb_last_mv += zopt[0];
      mpc_doubleint_B.u = rtb_last_mv;
      for (i = 0; i < 6; i++) {
        mpc_doubleint_B.iAout[i] = (iAnew[i] != 0);
      }

      /* '<S17>:1:135' if CustomEstimation==ONE */
      /* '<S17>:1:137' else */
      /*  update x[k+1|k], assuming that above u and v will be applied. */
      /* '<S17>:1:139' xk1 = A*xk + Bu*(u - uoff) + Bv*v + L*y_innov; */
      /* '<S17>:1:141' xk1 = xk1 + xoff; */
      /*  Updated state must include offset */
      /* '<S17>:1:143' if CustomEstimation==ONE */
      /* '<S17>:1:146' else */
      /* '<S17>:1:147' xest = xest + xoff; */
      mpc_doubleint_B.xk1[0] = ((0.0 * mpc_doubleint_DW.last_x_PreviousInput[1]
        + mpc_doubleint_DW.last_x_PreviousInput[0]) + 0.1 * rtb_last_mv) +
        0.0931745141509576 * y_innov;
      mpc_doubleint_B.xk1[1] = ((0.1 * mpc_doubleint_DW.last_x_PreviousInput[0]
        + mpc_doubleint_DW.last_x_PreviousInput[1]) + 0.005000000000000001 *
        rtb_last_mv) + 0.14116844268839748 * y_innov;

      /* End of MATLAB Function: '<S2>/optimizer' */
    }
  }

  if (rtmIsMajorTimeStep(mpc_doubleint_M)) {
    int32_T i;
    if (rtmIsMajorTimeStep(mpc_doubleint_M)) {
      /* Update for Memory: '<S2>/Memory' */
      for (i = 0; i < 6; i++) {
        mpc_doubleint_DW.Memory_PreviousInput[i] = mpc_doubleint_B.iAout[i];
      }

      /* End of Update for Memory: '<S2>/Memory' */

      /* Update for UnitDelay: '<S2>/last_mv' */
      mpc_doubleint_DW.last_mv_DSTATE = mpc_doubleint_B.u;

      /* Update for Memory: '<S2>/last_x' */
      mpc_doubleint_DW.last_x_PreviousInput[0] = mpc_doubleint_B.xk1[0];
      mpc_doubleint_DW.last_x_PreviousInput[1] = mpc_doubleint_B.xk1[1];
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(mpc_doubleint_M)) {
    rt_ertODEUpdateContinuousStates(&mpc_doubleint_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++mpc_doubleint_M->Timing.clockTick0;
    mpc_doubleint_M->Timing.t[0] = rtsiGetSolverStopTime
      (&mpc_doubleint_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.1s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.1, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      mpc_doubleint_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void mpc_doubleint_derivatives(void)
{
  XDot_mpc_doubleint_T *_rtXdot;
  _rtXdot = ((XDot_mpc_doubleint_T *) mpc_doubleint_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator 2' */
  _rtXdot->Integrator2_CSTATE = mpc_doubleint_B.Integrator1;

  /* Derivatives for Integrator: '<Root>/Integrator 1' */
  _rtXdot->Integrator1_CSTATE = mpc_doubleint_B.u;
}

/* Model initialize function */
void mpc_doubleint_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)mpc_doubleint_M, 0,
                sizeof(RT_MODEL_mpc_doubleint_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&mpc_doubleint_M->solverInfo,
                          &mpc_doubleint_M->Timing.simTimeStep);
    rtsiSetTPtr(&mpc_doubleint_M->solverInfo, &rtmGetTPtr(mpc_doubleint_M));
    rtsiSetStepSizePtr(&mpc_doubleint_M->solverInfo,
                       &mpc_doubleint_M->Timing.stepSize0);
    rtsiSetdXPtr(&mpc_doubleint_M->solverInfo, &mpc_doubleint_M->derivs);
    rtsiSetContStatesPtr(&mpc_doubleint_M->solverInfo, (real_T **)
                         &mpc_doubleint_M->contStates);
    rtsiSetNumContStatesPtr(&mpc_doubleint_M->solverInfo,
      &mpc_doubleint_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&mpc_doubleint_M->solverInfo,
      &mpc_doubleint_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&mpc_doubleint_M->solverInfo,
      &mpc_doubleint_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&mpc_doubleint_M->solverInfo,
      &mpc_doubleint_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&mpc_doubleint_M->solverInfo, (&rtmGetErrorStatus
      (mpc_doubleint_M)));
    rtsiSetRTModelPtr(&mpc_doubleint_M->solverInfo, mpc_doubleint_M);
  }

  rtsiSetSimTimeStep(&mpc_doubleint_M->solverInfo, MAJOR_TIME_STEP);
  mpc_doubleint_M->intgData.y = mpc_doubleint_M->odeY;
  mpc_doubleint_M->intgData.f[0] = mpc_doubleint_M->odeF[0];
  mpc_doubleint_M->intgData.f[1] = mpc_doubleint_M->odeF[1];
  mpc_doubleint_M->intgData.f[2] = mpc_doubleint_M->odeF[2];
  mpc_doubleint_M->intgData.f[3] = mpc_doubleint_M->odeF[3];
  mpc_doubleint_M->contStates = ((X_mpc_doubleint_T *) &mpc_doubleint_X);
  rtsiSetSolverData(&mpc_doubleint_M->solverInfo, (void *)
                    &mpc_doubleint_M->intgData);
  rtsiSetSolverName(&mpc_doubleint_M->solverInfo,"ode4");
  rtmSetTPtr(mpc_doubleint_M, &mpc_doubleint_M->Timing.tArray[0]);
  mpc_doubleint_M->Timing.stepSize0 = 0.1;

  /* block I/O */
  (void) memset(((void *) &mpc_doubleint_B), 0,
                sizeof(B_mpc_doubleint_T));

  {
    mpc_doubleint_B.Integrator1 = 0.0;
    mpc_doubleint_B.xk1[0] = 0.0;
    mpc_doubleint_B.xk1[1] = 0.0;
    mpc_doubleint_B.u = 0.0;
  }

  /* states (continuous) */
  {
    (void) memset((void *)&mpc_doubleint_X, 0,
                  sizeof(X_mpc_doubleint_T));
  }

  /* states (dwork) */
  (void) memset((void *)&mpc_doubleint_DW, 0,
                sizeof(DW_mpc_doubleint_T));
  mpc_doubleint_DW.last_mv_DSTATE = 0.0;
  mpc_doubleint_DW.last_x_PreviousInput[0] = 0.0;
  mpc_doubleint_DW.last_x_PreviousInput[1] = 0.0;

  /* external inputs */
  mpc_doubleint_U.ref = 0.0;

  /* external outputs */
  mpc_doubleint_Y.out = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator 2' */
  mpc_doubleint_X.Integrator2_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator 1' */
  mpc_doubleint_X.Integrator1_CSTATE = 0.0;
}

/* Model terminate function */
void mpc_doubleint_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
