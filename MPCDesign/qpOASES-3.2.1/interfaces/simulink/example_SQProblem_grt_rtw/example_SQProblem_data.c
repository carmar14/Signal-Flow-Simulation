/*
 * example_SQProblem_data.c
 *
 * Code generation for model "example_SQProblem".
 *
 * Model version              : 1.73
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Mon Jun 18 17:09:16 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "example_SQProblem.h"
#include "example_SQProblem_private.h"

/* Block parameters (auto storage) */
P_example_SQProblem_T example_SQProblem_P = {
  /*  Expression: zeros(1, 4)
   * Referenced by: '<Root>/H'
   */
  { 0.0, 0.0, 0.0, 0.0 },

  /*  Expression: [1 10]
   * Referenced by: '<Root>/f'
   */
  { 1.0, 10.0 },

  /*  Expression: [1 1]
   * Referenced by: '<Root>/A'
   */
  { 1.0, 1.0 },

  /*  Expression: [0 0]
   * Referenced by: '<Root>/lb'
   */
  { 0.0, 0.0 },

  /*  Expression: [3500 3500]
   * Referenced by: '<Root>/ub'
   */
  { 3500.0, 3500.0 },
  4000.0,                              /* Expression: [4000]
                                        * Referenced by: '<Root>/lbA'
                                        */
  7000.0                               /* Expression: [7000]
                                        * Referenced by: '<Root>/ubA'
                                        */
};
