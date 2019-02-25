/*
 * File: MPC.c
 *
 * Code generated for Simulink model 'MPC'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Fri Feb 02 10:54:17 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MPC.h"
#include "MPC_private.h"
#include <stddef.h>
#include <stdlib.h> 
#include <stdio.h> 



/* Named constants for MATLAB Function: '<S7>/optimizer' */
#define MPC_ny                         (2.0)

/* Block states (auto storage) */
DW_MPC_T MPC_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_MPC_T MPC_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_MPC_T MPC_Y;

/* Real-time model */
RT_MODEL_MPC_T MPC_M_;
RT_MODEL_MPC_T *const MPC_M = &MPC_M_;

//Variabls de salida
double U1;
double U2;

/* Forward declaration for local functions */
static void MPC_Unconstrained(const real_T b_Hinv[9], const real_T f[3], real_T
  x[3], int16_T n);
static real_T MPC_norm(const real_T x[3]);
static void MPC_abs_h(const real_T x[6], real_T y[6]);
static real_T MPC_xnrm2(int32_T n, const real_T x[9], int32_T ix0);
static void MPC_xgeqrf(real_T b_A[9], real_T tau[3]);
static void MPC_qr(const real_T b_A[9], real_T Q[9], real_T R[9]);
static real_T MPC_KWIKfactor(const real_T b_Ac[18], const int16_T iC[6], int16_T
  nA, const real_T b_Linv[9], real_T RLinv[9], real_T D[9], real_T b_H[9],
  int16_T n);
static void MPC_DropConstraint(int16_T kDrop, int16_T iA[6], int16_T *nA,
  int16_T iC[6]);
static void MPC_abs(const real_T x[3], real_T y[3]);
static void MPC_qpkwik(const real_T b_Linv[9], const real_T b_Hinv[9], const
  real_T f[3], const real_T b_Ac[18], const real_T b[6], int16_T iA[6], int16_T
  b_maxiter, real_T FeasTol, real_T x[3], real_T lambda[6], real_T *status);
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (MPC_M->Timing.TaskCounters.TID[1])++;
  if ((MPC_M->Timing.TaskCounters.TID[1]) > 59999) {/* Sample time: [0.1s, 0.0s] */
    MPC_M->Timing.TaskCounters.TID[1] = 0;
  }
}

void guardoU(double u1){
	U1=u1;
}	

void guardoU2(double u2){
	U2=u2;
}

double getU(){
	return U1;
}

double getU2(){
	return U2;
} 

/* Function for MATLAB Function: '<S7>/optimizer' */
static void MPC_Unconstrained(const real_T b_Hinv[9], const real_T f[3], real_T
  x[3], int16_T n)
{
  int16_T i;
  for (i = 1; i <= n; i++) {
    x[i - 1] = (-b_Hinv[i - 1] * f[0] + -b_Hinv[i + 2] * f[1]) + -b_Hinv[i + 5] *
      f[2];
  }
}

/* Function for MATLAB Function: '<S7>/optimizer' */
static real_T MPC_norm(const real_T x[3])
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

  return scale * sqrt(y);
}

/* Function for MATLAB Function: '<S7>/optimizer' */
static void MPC_abs_h(const real_T x[6], real_T y[6])
{
  int32_T k;
  for (k = 0; k < 6; k++) {
    y[k] = fabs(x[k]);
  }
}

/* Function for MATLAB Function: '<S7>/optimizer' */
static real_T MPC_xnrm2(int32_T n, const real_T x[9], int32_T ix0)
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

/* Function for MATLAB Function: '<S7>/optimizer' */
static void MPC_xgeqrf(real_T b_A[9], real_T tau[3])
{
  real_T work[3];
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
  b_atmp = b_A[0];
  b_c = 0.0;
  xnorm = MPC_xnrm2(2, b_A, 2);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(b_A[0], xnorm);
    if (b_A[0] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        for (lastc = 1; lastc + 1 < 4; lastc++) {
          b_A[lastc] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        b_atmp *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(b_atmp, MPC_xnrm2(2, b_A, 2));
      if (b_atmp >= 0.0) {
        xnorm = -xnorm;
      }

      b_c = (xnorm - b_atmp) / xnorm;
      b_atmp = 1.0 / (b_atmp - xnorm);
      for (lastc = 1; lastc + 1 < 4; lastc++) {
        b_A[lastc] *= b_atmp;
      }

      for (lastv = 1; lastv <= knt; lastv++) {
        xnorm *= 1.0020841800044864E-292;
      }

      b_atmp = xnorm;
    } else {
      b_c = (xnorm - b_A[0]) / xnorm;
      b_atmp = 1.0 / (b_A[0] - xnorm);
      for (lastv = 1; lastv + 1 < 4; lastv++) {
        b_A[lastv] *= b_atmp;
      }

      b_atmp = xnorm;
    }
  }

  tau[0] = b_c;
  b_A[0] = b_atmp;
  b_atmp = b_A[0];
  b_A[0] = 1.0;
  knt = 3;
  if (b_c != 0.0) {
    lastv = 3;
    lastc = 2;
    while ((lastv > 0) && (b_A[lastc] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = 2;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      coltop = (lastc - 1) * 3 + 4;
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
      ia = (lastc - 1) * 3 + 4;
      for (b_ix = 4; b_ix <= ia; b_ix += 3) {
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
        knt += 3;
      }
    }
  }

  b_A[0] = b_atmp;
  b_atmp = b_A[4];
  b_c = 0.0;
  xnorm = MPC_xnrm2(1, b_A, 6);
  if (xnorm != 0.0) {
    xnorm = rt_hypotd_snf(b_A[4], xnorm);
    if (b_A[4] >= 0.0) {
      xnorm = -xnorm;
    }

    if (fabs(xnorm) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        for (lastc = 5; lastc + 1 < 7; lastc++) {
          b_A[lastc] *= 9.9792015476736E+291;
        }

        xnorm *= 9.9792015476736E+291;
        b_atmp *= 9.9792015476736E+291;
      } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

      xnorm = rt_hypotd_snf(b_atmp, MPC_xnrm2(1, b_A, 6));
      if (b_atmp >= 0.0) {
        xnorm = -xnorm;
      }

      b_c = (xnorm - b_atmp) / xnorm;
      b_atmp = 1.0 / (b_atmp - xnorm);
      for (lastc = 5; lastc + 1 < 7; lastc++) {
        b_A[lastc] *= b_atmp;
      }

      for (lastv = 1; lastv <= knt; lastv++) {
        xnorm *= 1.0020841800044864E-292;
      }

      b_atmp = xnorm;
    } else {
      b_c = (xnorm - b_A[4]) / xnorm;
      b_atmp = 1.0 / (b_A[4] - xnorm);
      for (lastv = 5; lastv + 1 < 7; lastv++) {
        b_A[lastv] *= b_atmp;
      }

      b_atmp = xnorm;
    }
  }

  tau[1] = b_c;
  b_A[4] = b_atmp;
  b_atmp = b_A[4];
  b_A[4] = 1.0;
  knt = 7;
  if (b_c != 0.0) {
    lastv = 2;
    lastc = 5;
    while ((lastv > 0) && (b_A[lastc] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = 1;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      ia = 8;
      do {
        exitg1 = 0;
        if (ia <= lastv + 7) {
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
      b_ix = 8;
      while (b_ix <= 8) {
        ix = 4;
        b_c = 0.0;
        g = lastv + 7;
        for (b_ia = 8; b_ia <= g; b_ia++) {
          b_c += b_A[b_ia - 1] * b_A[ix];
          ix++;
        }

        work[coltop] += b_c;
        coltop++;
        b_ix = 11;
      }
    }

    if (!(-tau[1] == 0.0)) {
      coltop = 0;
      ia = 1;
      while (ia <= lastc) {
        if (work[coltop] != 0.0) {
          b_c = work[coltop] * -tau[1];
          b_ix = 4;
          ix = lastv + knt;
          for (g = knt; g + 1 <= ix; g++) {
            b_A[g] += b_A[b_ix] * b_c;
            b_ix++;
          }
        }

        coltop++;
        knt += 3;
        ia = 2;
      }
    }
  }

  b_A[4] = b_atmp;
  tau[2] = 0.0;
}

/* Function for MATLAB Function: '<S7>/optimizer' */
static void MPC_qr(const real_T b_A[9], real_T Q[9], real_T R[9])
{
  real_T c_A[9];
  real_T tau[3];
  int32_T d_i;
  real_T work[3];
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
  memcpy(&c_A[0], &b_A[0], 9U * sizeof(real_T));
  MPC_xgeqrf(c_A, tau);
  for (d_i = 0; d_i + 1 < 2; d_i++) {
    R[d_i] = c_A[d_i];
  }

  for (d_i = 1; d_i + 1 < 4; d_i++) {
    R[d_i] = 0.0;
  }

  work[0] = 0.0;
  for (d_i = 0; d_i + 1 < 3; d_i++) {
    R[d_i + 3] = c_A[d_i + 3];
  }

  for (d_i = 2; d_i + 1 < 4; d_i++) {
    R[d_i + 3] = 0.0;
  }

  work[1] = 0.0;
  for (d_i = 0; d_i + 1 < 4; d_i++) {
    R[d_i + 6] = c_A[d_i + 6];
  }

  work[2] = 0.0;
  c_A[8] = 1.0 - tau[2];
  for (d_i = 1; d_i < 3; d_i++) {
    c_A[8 - d_i] = 0.0;
  }

  c_A[4] = 1.0;
  if (tau[1] != 0.0) {
    d_i = 2;
    lastc = 5;
    while ((d_i > 0) && (c_A[lastc] == 0.0)) {
      d_i--;
      lastc--;
    }

    lastc = 1;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      jy = 5;
      do {
        exitg1 = 0;
        if (jy + 3 <= d_i + 7) {
          if (c_A[jy + 2] != 0.0) {
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
      iac = 8;
      while (iac <= 8) {
        ix = 5;
        c = 0.0;
        d = d_i + 7;
        for (b_ia = 8; b_ia <= d; b_ia++) {
          c += c_A[b_ia - 1] * c_A[ix - 1];
          ix++;
        }

        work[coltop] += c;
        coltop++;
        iac = 11;
      }
    }

    if (!(-tau[1] == 0.0)) {
      coltop = 7;
      jy = 0;
      iac = 1;
      while (iac <= lastc) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau[1];
          ix = 5;
          d = d_i + coltop;
          for (b_ia = coltop; b_ia + 1 <= d; b_ia++) {
            c_A[b_ia] += c_A[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        coltop += 3;
        iac = 2;
      }
    }
  }

  for (lastc = 5; lastc + 1 < 7; lastc++) {
    c_A[lastc] *= -tau[1];
  }

  c_A[4] = 1.0 - tau[1];
  d_i = 1;
  while (d_i <= 1) {
    c_A[3] = 0.0;
    d_i = 2;
  }

  c_A[0] = 1.0;
  if (tau[0] != 0.0) {
    d_i = 3;
    lastc = 2;
    while ((d_i > 0) && (c_A[lastc] == 0.0)) {
      d_i--;
      lastc--;
    }

    lastc = 2;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      coltop = (lastc - 1) * 3 + 1;
      jy = coltop;
      do {
        exitg1 = 0;
        if (jy + 3 <= (coltop + d_i) + 2) {
          if (c_A[jy + 2] != 0.0) {
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
      jy = (lastc - 1) * 3 + 4;
      for (iac = 4; iac <= jy; iac += 3) {
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
      coltop = 3;
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
        coltop += 3;
      }
    }
  }

  for (lastc = 1; lastc + 1 < 4; lastc++) {
    c_A[lastc] *= -tau[0];
  }

  c_A[0] = 1.0 - tau[0];
  for (d_i = 0; d_i < 3; d_i++) {
    Q[3 * d_i] = c_A[3 * d_i];
    Q[1 + 3 * d_i] = c_A[3 * d_i + 1];
    Q[2 + 3 * d_i] = c_A[3 * d_i + 2];
  }
}

/* Function for MATLAB Function: '<S7>/optimizer' */
static real_T MPC_KWIKfactor(const real_T b_Ac[18], const int16_T iC[6], int16_T
  nA, const real_T b_Linv[9], real_T RLinv[9], real_T D[9], real_T b_H[9],
  int16_T n)
{
  real_T Status;
  real_T TL[9];
  real_T QQ[9];
  real_T RR[9];
  int16_T i;
  int16_T f_i;
  int16_T d_k;
  int32_T iC_0;
  int32_T i_0;
  int32_T i_1;
  int32_T exitg1;
  Status = 1.0;
  memset(&RLinv[0], 0, 9U * sizeof(real_T));
  for (i = 1; i <= nA; i++) {
    RLinv[3 * (i - 1)] = 0.0;
    RLinv[1 + 3 * (i - 1)] = 0.0;
    RLinv[2 + 3 * (i - 1)] = 0.0;
    iC_0 = iC[i - 1];
    i_0 = i - 1;
    for (i_1 = 0; i_1 < 3; i_1++) {
      RLinv[i_1 + 3 * i_0] = 0.0;
      RLinv[i_1 + 3 * i_0] += b_Ac[iC_0 - 1] * b_Linv[i_1];
      RLinv[i_1 + 3 * i_0] += b_Linv[i_1 + 3] * b_Ac[iC_0 + 5];
      RLinv[i_1 + 3 * i_0] += b_Linv[i_1 + 6] * b_Ac[iC_0 + 11];
    }
  }

  MPC_qr(RLinv, QQ, RR);
  i = 1;
  do {
    exitg1 = 0;
    if (i <= nA) {
      if (fabs(RR[((i - 1) * 3 + i) - 1]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      for (i = 1; i <= n; i++) {
        for (f_i = 1; f_i <= n; f_i++) {
          TL[(i + 3 * (f_i - 1)) - 1] = (b_Linv[(i - 1) * 3 + 1] * QQ[(f_i - 1) *
            3 + 1] + b_Linv[(i - 1) * 3] * QQ[(f_i - 1) * 3]) + b_Linv[(i - 1) *
            3 + 2] * QQ[(f_i - 1) * 3 + 2];
        }
      }

      memset(&RLinv[0], 0, 9U * sizeof(real_T));
      for (i = nA; i > 0; i--) {
        RLinv[(i + 3 * (i - 1)) - 1] = 1.0;
        for (f_i = i; f_i <= nA; f_i++) {
          RLinv[(i + 3 * (f_i - 1)) - 1] /= RR[((i - 1) * 3 + i) - 1];
        }

        if (i > 1) {
          for (f_i = 1; f_i < i; f_i++) {
            for (d_k = i; d_k <= nA; d_k++) {
              RLinv[(f_i + 3 * (d_k - 1)) - 1] -= RR[((i - 1) * 3 + f_i) - 1] *
                RLinv[((d_k - 1) * 3 + i) - 1];
            }
          }
        }
      }

      for (i = 1; i <= n; i++) {
        for (f_i = i; f_i <= n; f_i++) {
          b_H[(i + 3 * (f_i - 1)) - 1] = 0.0;
          for (d_k = (int16_T)(nA + 1); d_k <= n; d_k++) {
            b_H[(i + 3 * (f_i - 1)) - 1] -= TL[((d_k - 1) * 3 + i) - 1] * TL
              [((d_k - 1) * 3 + f_i) - 1];
          }

          b_H[(f_i + 3 * (i - 1)) - 1] = b_H[((f_i - 1) * 3 + i) - 1];
        }
      }

      for (i = 1; i <= nA; i++) {
        for (f_i = 1; f_i <= n; f_i++) {
          D[(f_i + 3 * (i - 1)) - 1] = 0.0;
          for (d_k = i; d_k <= nA; d_k++) {
            D[(f_i + 3 * (i - 1)) - 1] += TL[((d_k - 1) * 3 + f_i) - 1] * RLinv
              [((d_k - 1) * 3 + i) - 1];
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S7>/optimizer' */
static void MPC_DropConstraint(int16_T kDrop, int16_T iA[6], int16_T *nA,
  int16_T iC[6])
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

/* Function for MATLAB Function: '<S7>/optimizer' */
static void MPC_abs(const real_T x[3], real_T y[3])
{
  y[0] = fabs(x[0]);
  y[1] = fabs(x[1]);
  y[2] = fabs(x[2]);
}

/* Function for MATLAB Function: '<S7>/optimizer' */
static void MPC_qpkwik(const real_T b_Linv[9], const real_T b_Hinv[9], const
  real_T f[3], const real_T b_Ac[18], const real_T b[6], int16_T iA[6], int16_T
  b_maxiter, real_T FeasTol, real_T x[3], real_T lambda[6], real_T *status)
{
  real_T r[3];
  real_T rMin;
  real_T RLinv[9];
  real_T D[9];
  real_T b_H[9];
  real_T U[9];
  real_T cTol[6];
  boolean_T cTolComputed;
  int16_T iC[6];
  int16_T nA;
  real_T Opt[6];
  real_T Rhs[6];
  boolean_T DualFeasible;
  boolean_T ColdReset;
  int16_T kDrop;
  real_T Xnorm0;
  real_T cMin;
  int16_T kNext;
  real_T AcRow[3];
  real_T z[3];
  real_T zTa;
  real_T t;
  int16_T iSave;
  uint16_T q;
  uint16_T b_x;
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
    for (i = 0; i < 6; i++) {
      Opt[i] = 0.0;
    }

    Rhs[0] = f[0];
    Rhs[3] = 0.0;
    Rhs[1] = f[1];
    Rhs[4] = 0.0;
    Rhs[2] = f[2];
    Rhs[5] = 0.0;
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
        Xnorm0 = MPC_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, D, b_H, 3);
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
            i = 3 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            Rhs[i - 1] = b[iC[kNext - 1] - 1];
            for (kDrop = kNext; kDrop <= nA; kDrop++) {
              U[(kDrop + 3 * (kNext - 1)) - 1] = 0.0;
              for (iSave = 1; iSave <= nA; iSave++) {
                U[(kDrop + 3 * (kNext - 1)) - 1] += RLinv[((iSave - 1) * 3 +
                  kDrop) - 1] * RLinv[((iSave - 1) * 3 + kNext) - 1];
              }

              U[(kNext + 3 * (kDrop - 1)) - 1] = U[((kNext - 1) * 3 + kDrop) - 1];
            }
          }

          for (kNext = 0; kNext < 3; kNext++) {
            i = kNext + 1;
            Opt[kNext] = (b_H[i - 1] * Rhs[0] + b_H[i + 2] * Rhs[1]) + b_H[i + 5]
              * Rhs[2];
            for (kDrop = 1; kDrop <= nA; kDrop++) {
              i = 3 + kDrop;
              if (i > 32767) {
                i = 32767;
              }

              Opt[kNext] += D[(kDrop - 1) * 3 + kNext] * Rhs[i - 1];
            }
          }

          for (kNext = 1; kNext <= nA; kNext++) {
            i = 3 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            Opt[i - 1] = (D[(kNext - 1) * 3 + 1] * Rhs[1] + D[(kNext - 1) * 3] *
                          Rhs[0]) + D[(kNext - 1) * 3 + 2] * Rhs[2];
            for (kDrop = 1; kDrop <= nA; kDrop++) {
              i = 3 + kNext;
              if (i > 32767) {
                i = 32767;
              }

              ix = 3 + kNext;
              if (ix > 32767) {
                ix = 32767;
              }

              tmp = 3 + kDrop;
              if (tmp > 32767) {
                tmp = 32767;
              }

              Opt[i - 1] = U[((kDrop - 1) * 3 + kNext) - 1] * Rhs[tmp - 1] +
                Opt[ix - 1];
            }
          }

          Xnorm0 = -1.0E-12;
          kDrop = 0;
          for (kNext = 1; kNext <= nA; kNext++) {
            i = 3 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            lambda[iC[kNext - 1] - 1] = Opt[i - 1];
            i = 3 + kNext;
            if (i > 32767) {
              i = 32767;
            }

            if ((Opt[i - 1] < Xnorm0) && (kNext <= nA)) {
              kDrop = kNext;
              i = 3 + kNext;
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
              MPC_DropConstraint(kDrop, iA, &nA, iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          for (i = 0; i < 6; i++) {
            lambda[i] = 0.0;
          }

          MPC_Unconstrained(b_Hinv, f, x, 3);
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    MPC_Unconstrained(b_Hinv, f, x, 3);
    guard1 = true;
  }

  if (guard1) {
    Xnorm0 = MPC_norm(x);
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
            MPC_abs(z, AcRow);
            i = 1;
            zTa = AcRow[0];
            if (rtIsNaN(AcRow[0])) {
              ix = 2;
              exitg4 = false;
              while ((!exitg4) && (ix < 4)) {
                i = ix;
                if (!rtIsNaN(AcRow[ix - 1])) {
                  zTa = AcRow[ix - 1];
                  exitg4 = true;
                } else {
                  ix++;
                }
              }
            }

            if (i < 3) {
              while (i + 1 < 4) {
                if (AcRow[i] > zTa) {
                  zTa = AcRow[i];
                }

                i++;
              }
            }

            cTol[kDrop] = fmax(cTol[kDrop], zTa);
          }

          if (iA[kDrop] == 0) {
            i = kDrop + 1;
            zTa = (((b_Ac[i - 1] * x[0] + b_Ac[i + 5] * x[1]) + b_Ac[i + 11] *
                    x[2]) - b[kDrop]) / cTol[kDrop];
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
                for (i = 0; i < 3; i++) {
                  z[i] = b_Hinv[i + 6] * b_Ac[kNext + 11] + (b_Hinv[i + 3] *
                    b_Ac[kNext + 5] + b_Ac[kNext - 1] * b_Hinv[i]);
                }

                guard2 = true;
              } else {
                cMin = MPC_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, D, b_H, 3);
                if (cMin <= 0.0) {
                  *status = -2.0;
                  exitg1 = 1;
                } else {
                  for (i = 0; i < 3; i++) {
                    U[3 * i] = -b_H[3 * i];
                    U[1 + 3 * i] = -b_H[3 * i + 1];
                    U[2 + 3 * i] = -b_H[3 * i + 2];
                  }

                  for (i = 0; i < 3; i++) {
                    z[i] = U[i + 6] * b_Ac[kNext + 11] + (U[i + 3] * b_Ac[kNext
                      + 5] + b_Ac[kNext - 1] * U[i]);
                  }

                  for (kDrop = 1; kDrop <= nA; kDrop++) {
                    r[kDrop - 1] = (D[(kDrop - 1) * 3 + 1] * b_Ac[kNext + 5] +
                                    D[(kDrop - 1) * 3] * b_Ac[kNext - 1]) + D
                      [(kDrop - 1) * 3 + 2] * b_Ac[kNext + 11];
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

                zTa = (b_Ac[kNext - 1] * z[0] + b_Ac[kNext + 5] * z[1]) +
                  b_Ac[kNext + 11] * z[2];
                if (zTa <= 0.0) {
                  zTa = 0.0;
                  ColdReset = true;
                } else {
                  zTa = (b[kNext - 1] - ((b_Ac[kNext - 1] * x[0] + b_Ac[kNext +
                           5] * x[1]) + b_Ac[kNext + 11] * x[2])) / zTa;
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
                  } else {
                    t = fmin(cMin, zTa);
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
                    MPC_DropConstraint(kDrop, iA, &nA, iC);
                  }

                  if (!ColdReset) {
                    x[0] += t * z[0];
                    x[1] += t * z[1];
                    x[2] += t * z[2];
                    if (t == zTa) {
                      if (nA == 3) {
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
              cMin = MPC_norm(x);
              if (fabs(cMin - Xnorm0) > 0.001) {
                Xnorm0 = cMin;
                MPC_abs_h(b, Opt);
                for (i = 0; i < 6; i++) {
                  cTol[i] = fmax(Opt[i], 1.0);
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
void MPC_step(double corriente1,double corriente2,double ref1,double ref2)
{
  //double* accionC=(double*)malloc(8*sizeof(double));	
  real_T xk[6];
  real_T y_innov[2];
  real_T rseq[6];
  real_T f[3];
  real_T zopt[3];
  real_T status;
  int16_T iAnew[6];
  static const real_T b_Linv[9] = { 0.576390417704235, 1.082644094031286E-18,
    0.0, 0.0, 0.57639041770423483, 0.0, 0.0, 0.0, 0.003162277660168379 };

  static const real_T b_Hinv[9] = { 0.33222591362126258, 6.2402568158371586E-19,
    0.0, 6.2402568158371586E-19, 0.3322259136212623, 0.0, 0.0, 0.0,
    9.9999999999999974E-6 };

  static const real_T b_Ac[18] = { -1.0, -0.0, 1.0, 0.0, 1.0, 0.0, -0.0, -1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T a[12] = { 0.46587257075478766, -5.3074673088437147E+37,
    -4.1527397320835594E-17, -5.9505912958277258E+37, 0.068254858490424675,
    9.598535600650316E-17, -4.1527397320835594E-17, 2.1066830431907355E+37,
    0.46587257075478777, 5.1969495894995853E+37, 9.5985356006503111E-17,
    0.068254858490424661 };

  static const int8_T b_a[12] = { 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1 };

  static const int8_T b_Mlim[6] = { 20, 20, 20, 20, 100, 100 };

  static const int8_T b_Mu1[12] = { -1, 0, 1, 0, 0, 0, 0, -1, 0, 1, 0, 0 };

  static const real_T b_Kx[12] = { 2.1417677256498697E-108,
    -4.5498998166004214E-110, -7.940051874482339E-108, 1.6867580986889367E-109,
    2.9999999999999996, -1.1996136967492359E-16, -7.9400518744823436E-108,
    1.6867580986889379E-109, 2.9435696044182925E-107, -6.2532209459032658E-109,
    1.1430763459720701E-16, 3.0000000000000009 };

  static const real_T b_Kr[12] = { -0.99999999999999989, 3.9987123224974528E-17,
    -0.99999999999999989, 3.9987123224974528E-17, -0.99999999999999989,
    3.9987123224974528E-17, -3.8102544865735674E-17, -1.0000000000000002,
    -3.8102544865735674E-17, -1.0000000000000002, -3.8102544865735674E-17,
    -1.0000000000000002 };

  static const real_T b_Ku1[4] = { 2.9999999999999991, -5.6537350777166251E-18,
    -5.6537350777166251E-18, 3.0000000000000013 };

  static const real_T c_a[36] = { 2.1417677256498697E-108,
    1.8613226522456278E-106, -7.9400518744823421E-108, -6.900374040091109E-106,
    0.0, 0.0, -4.5498998166004214E-110, 1.1393600860926635E-108,
    1.6867580986889374E-109, -4.2238838875702256E-108, 0.0, 0.0,
    -7.940051874482339E-108, -6.9003740400911051E-106, 2.9435696044182919E-107,
    2.5581358415058804E-105, 0.0, 0.0, 1.6867580986889367E-109,
    -4.22388388757023E-108, -6.2532209459032649E-109, 1.5658960949615331E-107,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  static const real_T d_a[12] = { 0.99999999999999989, 128.80000000000004,
    -3.9987123224974528E-17, 28.8, 0.0, 0.0, 3.8102544865735674E-17, 28.8,
    1.0000000000000002, 29.800000000000015, 0.0, 0.0 };

  static const real_T e_a[12] = { -7.6223636067132357E-72,
    1.9087490286024214E-70, 2.825794866486067E-71, -7.0761951078856582E-70,
    0.068254858490424675, 9.5985356006503148E-17, 7.8074771293816959E-72,
    -1.9551041062142269E-70, -2.8944209343389549E-71, 7.2480446116742668E-70,
    9.5985356006503111E-17, 0.068254858490424661 };

  real_T rtb_xest[6];
  int32_T i;
  real_T b_Mlim_0[6];
  real_T tmp[2];
  int32_T i_0;
  real_T tmp_0;
  real_T rtb_u_idx_0;
  real_T rtb_u_idx_1;
  if (MPC_M->Timing.TaskCounters.TID[1] == 0) {
    /* MATLAB Function: '<S7>/optimizer' incorporates:
     *  Memory: '<S7>/last_x'
     *  UnitDelay: '<S7>/last_mv'
     */
    /* MATLAB Function 'MPC Controller/MPC/optimizer': '<S22>:1' */
    /* '<S22>:1:13' coder.extrinsic('mpcblock_optimizer_double_mex'); */
    /* '<S22>:1:14' coder.extrinsic('mpcblock_optimizer_single_mex'); */
    /* '<S22>:1:15' coder.extrinsic('mpcblock_refmd_double_mex'); */
    /* '<S22>:1:16' coder.extrinsic('mpcblock_refmd_single_mex'); */
    /*  Parameters */
    /* '<S22>:1:19' isSimulation = coder.target('Sfun') && ~coder.target('RtwForRapid') && ~coder.target('RtwForSim'); */
    /* '<S22>:1:20' isAdaptive = false; */
    /* '<S22>:1:21' isLTV = false; */
    /* '<S22>:1:22' isDouble = isa(ref,'double'); */
    /* '<S22>:1:23' ZERO = zeros('like',ref); */
    /* '<S22>:1:24' ONE = ones('like',ref); */
    /*  Pre-allocate all the MEX block outputs for the simulation mode */
    /* '<S22>:1:29' if isSimulation */
    /*  Get reference and MD signals -- accounting for previewing */
    /* '<S22>:1:43' if isSimulation *
    /* '<S22>:1:50' else */
    /*  When doing code generation, use M code directly */
    /* '<S22>:1:52' [rseq, vseq, v] = mpcblock_refmd(ref,md,nv,ny,p,yoff,voff,no_md,no_ref,openloopflag, Rscale, MDscale); */
    for (i = 0; i < 6; i++) {
      rseq[i] = 0.0;
    }

    for (i = 0; i < 3; i++) {
      rseq[i * (int32_T)MPC_ny] = ref1;//1.17;
      rseq[1 + i * (int32_T)MPC_ny] = ref2;//3.0;
    }

    /*  External MV override.   */
    /*  NOTE: old_u and ext_mv input signals are dimensionless but include offset */
    /* '<S22>:1:57' old_u = old_u - uoff; */
    rtb_u_idx_0 = MPC_DW.last_mv_DSTATE[0];
    rtb_u_idx_1 = MPC_DW.last_mv_DSTATE[1];

    /* '<S22>:1:58' if no_mv==ONE */
    /* '<S22>:1:59' delmv = zeros(nu,1,'like',ref); */
    /*  Obtain x[k|k] */
    /* '<S22>:1:67' xk = xk - xoff; */
    /*  Remove offset */
    /* '<S22>:1:68' if CustomEstimation==ONE */
    /* '<S22>:1:71' else */
    /*  Default state estimation.     */
    /*  Scale measured output and remove offset. */
    /* '<S22>:1:74' ym = ym.*Rscale(myindex) - myoff; */
    /*  Correct x(k|k-1) for possible external mv override. */
    /*  NOTE:  Offset was removed from x[k|k-1] at k=0. */
    /* '<S22>:1:77' xk = xk + Bu*delmv; */
    for (i = 0; i < 6; i++) {
      xk[i] = MPC_DW.last_x_PreviousInput[i];
    }

    /* SignalConversion: '<S22>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  Inport: '<Root>/Corriente 1'
     *  Inport: '<Root>/Corriente 2'
     *  MATLAB Function: '<S7>/optimizer'
     */
    /*  Measurement upate to x(k|k) */
    /* '<S22>:1:79' ym_est = C(myindex,:)*xk + Dv(myindex,:)*v; */
    /* '<S22>:1:80' y_innov = ym - ym_est; */
    tmp[0] = corriente1;//MPC_U.Corriente1;
    tmp[1] = corriente2;//MPC_U.Corriente2;

    /* MATLAB Function: '<S7>/optimizer' incorporates:
     *  Memory: '<S7>/Memory'
     */
    for (i_0 = 0; i_0 < 2; i_0++) {
      status = 0.0;
      for (i = 0; i < 6; i++) {
        status += (real_T)b_a[(i << 1) + i_0] * xk[i];
      }

      y_innov[i_0] = tmp[i_0] - status;
    }

    /* '<S22>:1:81' xest = xk + M*y_innov; */
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_xest[i_0] = (a[i_0 + 6] * y_innov[1] + a[i_0] * y_innov[0]) + xk[i_0];
    }

    /*  Real-time MV target override */
    /*  Note: utargetValue is a vector length p*nu.   */
    /* '<S22>:1:86' if no_uref==ONE */
    /*  no external utarget */
    /* '<S22>:1:88' utargetValue = utarget; */
    /* '<S22>:1:96' if isSimulation */
    /* '<S22>:1:121' else */
    /*  When doing code generation, use M code directly */
    /* '<S22>:1:123' [u, cost, useq, status, iAout] = mpcblock_optimizer(... */
    /* '<S22>:1:124'             rseq, vseq, umin, umax, ymin, ymax, switch_in, xest, old_u, iA, ... */
    /* '<S22>:1:125'             isQP, nu, ny, degrees, Hinv, Kx, Ku1, Kut, Kr, Kv, Mlim, ... */
    /* '<S22>:1:126'             Mx, Mu1, Mv, z_degrees, utargetValue, p, uoff, voff, yoff, maxiter, CustomSolver, nxQP, openloopflag, ... */
    /* '<S22>:1:127'             lims_inport, no_umin, no_umax, no_ymin, no_ymax, switch_inport, ... */
    /* '<S22>:1:128'             no_switch, enable_value, return_cost, H, return_sequence, Linv, Ac, ... */
    /* '<S22>:1:129'             ywt, uwt, duwt, rhoeps, no_ywt, no_uwt, no_duwt, no_rhoeps,... */
    /* '<S22>:1:130'             Wy, Wdu, Jm, SuJm, Su1, Sx, Hv, Wu, I1, ... */
    /* '<S22>:1:131'             isAdaptive, isLTV, A, Bu, Bv, C, Dv, ... */
    /* '<S22>:1:132'             Mrows, nCC, Ecc, Fcc, Scc, Gcc); */
    f[0] = 0.0;
    f[1] = 0.0;
    f[2] = 0.0;
    for (i = 0; i < 2; i++) {
      status = 0.0;
      tmp_0 = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        status += b_Kx[6 * i + i_0] * rtb_xest[i_0];
        tmp_0 += b_Kr[6 * i + i_0] * rseq[i_0];
      }

      f[i] = (b_Ku1[(i << 1) + 1] * rtb_u_idx_1 + b_Ku1[i << 1] * rtb_u_idx_0) +
        (status + tmp_0);
    }

    for (i = 0; i < 6; i++) {
      iAnew[i] = MPC_DW.Memory_PreviousInput[i];
      status = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        status += 0.0 * rtb_xest[i_0];
      }

      b_Mlim_0[i] = -(((real_T)b_Mlim[i] + status) + ((real_T)b_Mu1[i + 6] *
        rtb_u_idx_1 + (real_T)b_Mu1[i] * rtb_u_idx_0));
    }

    MPC_qpkwik(b_Linv, b_Hinv, f, b_Ac, b_Mlim_0, iAnew, 120, 1.0E-6, zopt, rseq,
               &status);
    if (status <= 0.0) {
      zopt[0] = 0.0;
      zopt[1] = 0.0;
    }

    rtb_u_idx_0 += zopt[0];
    rtb_u_idx_1 += zopt[1];

    /* Outport: '<Root>/u1' */
    /* '<S22>:1:135' if CustomEstimation==ONE */
    /* '<S22>:1:137' else */
    /*  update x[k+1|k], assuming that above u and v will be applied. */
    /* '<S22>:1:139' xk1 = A*xk + Bu*(u - uoff) + Bv*v + L*y_innov; */
    /* '<S22>:1:141' xk1 = xk1 + xoff; */
    /*  Updated state must include offset */
    /* '<S22>:1:143' if CustomEstimation==ONE */
    /* '<S22>:1:146' else */
    /* '<S22>:1:147' xest = xest + xoff; */
    MPC_Y.u1 = rtb_u_idx_0;
	//accionC[0]=MPC_Y.u1;
	printf("La accionC 1 es: %3.2f \n",MPC_Y.u1 );
    /* Outport: '<Root>/u2' */
    MPC_Y.u2 = rtb_u_idx_1;
    //accionC[1]=MPC_Y.u2;
    printf("La accionC 2 es: %3.2f \n",MPC_Y.u2);
    
    //Guardo informacion
    
    guardoU(MPC_Y.u1);
    guardoU2(MPC_Y.u2); 

    /* Update for UnitDelay: '<S7>/last_mv' */
    MPC_DW.last_mv_DSTATE[0] = rtb_u_idx_0;
    MPC_DW.last_mv_DSTATE[1] = rtb_u_idx_1;
    for (i = 0; i < 6; i++) {
      /* MATLAB Function: '<S7>/optimizer' */
      rseq[i] = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        rseq[i] += c_a[6 * i_0 + i] * xk[i_0];
      }

      rtb_xest[i] = 0.0;
      rtb_xest[i] += d_a[i] * rtb_u_idx_0;
      rtb_xest[i] += d_a[i + 6] * rtb_u_idx_1;

      /* Update for Memory: '<S7>/last_x' incorporates:
       *  MATLAB Function: '<S7>/optimizer'
       */
      MPC_DW.last_x_PreviousInput[i] = (e_a[i + 6] * y_innov[1] + e_a[i] *
        y_innov[0]) + (rseq[i] + rtb_xest[i]);

      /* Update for Memory: '<S7>/Memory' incorporates:
       *  MATLAB Function: '<S7>/optimizer'
       */
      MPC_DW.Memory_PreviousInput[i] = (iAnew[i] != 0);
    }
  }

  rate_scheduler();
  //return accionC;
}

/* Model initialize function */
void MPC_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)MPC_M, 0,
                sizeof(RT_MODEL_MPC_T));

  /* states (dwork) */
  (void) memset((void *)&MPC_DW, 0,
                sizeof(DW_MPC_T));

  /* external inputs */
  (void)memset((void *)&MPC_U, 0, sizeof(ExtU_MPC_T));

  /* external outputs */
  (void) memset((void *)&MPC_Y, 0,
                sizeof(ExtY_MPC_T));
}

/* Model terminate function */
void MPC_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
