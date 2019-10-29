/*
 * example_SQProblem.c
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

/* Block signals (auto storage) */
B_example_SQProblem_T example_SQProblem_B;

/* Block states (auto storage) */
DW_example_SQProblem_T example_SQProblem_DW;

/* Real-time model */
RT_MODEL_example_SQProblem_T example_SQProblem_M_;
RT_MODEL_example_SQProblem_T *const example_SQProblem_M = &example_SQProblem_M_;

/* Model output function */
static void example_SQProblem_output(void)
{
  /* Constant: '<Root>/H' */
  example_SQProblem_B.H[0] = example_SQProblem_P.H_Value[0];
  example_SQProblem_B.H[1] = example_SQProblem_P.H_Value[1];
  example_SQProblem_B.H[2] = example_SQProblem_P.H_Value[2];
  example_SQProblem_B.H[3] = example_SQProblem_P.H_Value[3];

  /* Constant: '<Root>/f' */
  example_SQProblem_B.f[0] = example_SQProblem_P.f_Value[0];

  /* Constant: '<Root>/A' */
  example_SQProblem_B.A[0] = example_SQProblem_P.A_Value[0];

  /* Constant: '<Root>/lb' */
  example_SQProblem_B.lb[0] = example_SQProblem_P.lb_Value[0];

  /* Constant: '<Root>/ub' */
  example_SQProblem_B.ub[0] = example_SQProblem_P.ub_Value[0];

  /* Constant: '<Root>/f' */
  example_SQProblem_B.f[1] = example_SQProblem_P.f_Value[1];

  /* Constant: '<Root>/A' */
  example_SQProblem_B.A[1] = example_SQProblem_P.A_Value[1];

  /* Constant: '<Root>/lb' */
  example_SQProblem_B.lb[1] = example_SQProblem_P.lb_Value[1];

  /* Constant: '<Root>/ub' */
  example_SQProblem_B.ub[1] = example_SQProblem_P.ub_Value[1];

  /* Constant: '<Root>/lbA' */
  example_SQProblem_B.lbA = example_SQProblem_P.lbA_Value;

  /* Constant: '<Root>/ubA' */
  example_SQProblem_B.ubA = example_SQProblem_P.ubA_Value;

  /* S-Function (qp_linprog): '<Root>/qpOASES' */

  /* Level2 S-Function Block: '<Root>/qpOASES' (qp_linprog) */
  {
    SimStruct *rts = example_SQProblem_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }
}

/* Model update function */
static void example_SQProblem_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++example_SQProblem_M->Timing.clockTick0)) {
    ++example_SQProblem_M->Timing.clockTickH0;
  }

  example_SQProblem_M->Timing.t[0] = example_SQProblem_M->Timing.clockTick0 *
    example_SQProblem_M->Timing.stepSize0 +
    example_SQProblem_M->Timing.clockTickH0 *
    example_SQProblem_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
static void example_SQProblem_initialize(void)
{
  /* Start for Constant: '<Root>/H' */
  example_SQProblem_B.H[0] = example_SQProblem_P.H_Value[0];
  example_SQProblem_B.H[1] = example_SQProblem_P.H_Value[1];
  example_SQProblem_B.H[2] = example_SQProblem_P.H_Value[2];
  example_SQProblem_B.H[3] = example_SQProblem_P.H_Value[3];

  /* Start for Constant: '<Root>/f' */
  example_SQProblem_B.f[0] = example_SQProblem_P.f_Value[0];

  /* Start for Constant: '<Root>/A' */
  example_SQProblem_B.A[0] = example_SQProblem_P.A_Value[0];

  /* Start for Constant: '<Root>/lb' */
  example_SQProblem_B.lb[0] = example_SQProblem_P.lb_Value[0];

  /* Start for Constant: '<Root>/ub' */
  example_SQProblem_B.ub[0] = example_SQProblem_P.ub_Value[0];

  /* Start for Constant: '<Root>/f' */
  example_SQProblem_B.f[1] = example_SQProblem_P.f_Value[1];

  /* Start for Constant: '<Root>/A' */
  example_SQProblem_B.A[1] = example_SQProblem_P.A_Value[1];

  /* Start for Constant: '<Root>/lb' */
  example_SQProblem_B.lb[1] = example_SQProblem_P.lb_Value[1];

  /* Start for Constant: '<Root>/ub' */
  example_SQProblem_B.ub[1] = example_SQProblem_P.ub_Value[1];

  /* Start for Constant: '<Root>/lbA' */
  example_SQProblem_B.lbA = example_SQProblem_P.lbA_Value;

  /* Start for Constant: '<Root>/ubA' */
  example_SQProblem_B.ubA = example_SQProblem_P.ubA_Value;

  /* Start for S-Function (qp_linprog): '<Root>/qpOASES' */
  /* Level2 S-Function Block: '<Root>/qpOASES' (qp_linprog) */
  {
    SimStruct *rts = example_SQProblem_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }
}

/* Model terminate function */
static void example_SQProblem_terminate(void)
{
  /* Terminate for S-Function (qp_linprog): '<Root>/qpOASES' */
  /* Level2 S-Function Block: '<Root>/qpOASES' (qp_linprog) */
  {
    SimStruct *rts = example_SQProblem_M->childSfunctions[0];
    sfcnTerminate(rts);
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  example_SQProblem_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  example_SQProblem_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  example_SQProblem_initialize();
}

void MdlTerminate(void)
{
  example_SQProblem_terminate();
}

/* Registration function */
RT_MODEL_example_SQProblem_T *example_SQProblem(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)example_SQProblem_M, 0,
                sizeof(RT_MODEL_example_SQProblem_T));
  rtsiSetSolverName(&example_SQProblem_M->solverInfo,"FixedStepDiscrete");
  example_SQProblem_M->solverInfoPtr = (&example_SQProblem_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = example_SQProblem_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    example_SQProblem_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    example_SQProblem_M->Timing.sampleTimes =
      (&example_SQProblem_M->Timing.sampleTimesArray[0]);
    example_SQProblem_M->Timing.offsetTimes =
      (&example_SQProblem_M->Timing.offsetTimesArray[0]);

    /* task periods */
    example_SQProblem_M->Timing.sampleTimes[0] = (0.1);

    /* task offsets */
    example_SQProblem_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(example_SQProblem_M, &example_SQProblem_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = example_SQProblem_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    example_SQProblem_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(example_SQProblem_M, 0.5);
  example_SQProblem_M->Timing.stepSize0 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    example_SQProblem_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(example_SQProblem_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(example_SQProblem_M->rtwLogInfo, (NULL));
    rtliSetLogT(example_SQProblem_M->rtwLogInfo, "tout");
    rtliSetLogX(example_SQProblem_M->rtwLogInfo, "");
    rtliSetLogXFinal(example_SQProblem_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(example_SQProblem_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(example_SQProblem_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(example_SQProblem_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(example_SQProblem_M->rtwLogInfo, 1);
    rtliSetLogY(example_SQProblem_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(example_SQProblem_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(example_SQProblem_M->rtwLogInfo, (NULL));
  }

  example_SQProblem_M->solverInfoPtr = (&example_SQProblem_M->solverInfo);
  example_SQProblem_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&example_SQProblem_M->solverInfo, 0.1);
  rtsiSetSolverMode(&example_SQProblem_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  example_SQProblem_M->blockIO = ((void *) &example_SQProblem_B);

  {
    example_SQProblem_B.H[0] = 0.0;
    example_SQProblem_B.H[1] = 0.0;
    example_SQProblem_B.H[2] = 0.0;
    example_SQProblem_B.H[3] = 0.0;
    example_SQProblem_B.f[0] = 0.0;
    example_SQProblem_B.f[1] = 0.0;
    example_SQProblem_B.A[0] = 0.0;
    example_SQProblem_B.A[1] = 0.0;
    example_SQProblem_B.lb[0] = 0.0;
    example_SQProblem_B.lb[1] = 0.0;
    example_SQProblem_B.ub[0] = 0.0;
    example_SQProblem_B.ub[1] = 0.0;
    example_SQProblem_B.lbA = 0.0;
    example_SQProblem_B.ubA = 0.0;
    example_SQProblem_B.qpOASES_o1[0] = 0.0;
    example_SQProblem_B.qpOASES_o1[1] = 0.0;
    example_SQProblem_B.qpOASES_o2 = 0.0;
    example_SQProblem_B.qpOASES_o3 = 0.0;
    example_SQProblem_B.qpOASES_o4 = 0.0;
  }

  /* parameters */
  example_SQProblem_M->defaultParam = ((real_T *)&example_SQProblem_P);

  /* states (dwork) */
  example_SQProblem_M->dwork = ((void *) &example_SQProblem_DW);
  (void) memset((void *)&example_SQProblem_DW, 0,
                sizeof(DW_example_SQProblem_T));

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &example_SQProblem_M->NonInlinedSFcns.sfcnInfo;
    example_SQProblem_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(example_SQProblem_M)));
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &example_SQProblem_M->Sizes.numSampTimes);
    example_SQProblem_M->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr
      (example_SQProblem_M)[0]);
    rtssSetTPtrPtr(sfcnInfo,example_SQProblem_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(example_SQProblem_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(example_SQProblem_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (example_SQProblem_M));
    rtssSetStepSizePtr(sfcnInfo, &example_SQProblem_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(example_SQProblem_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &example_SQProblem_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &example_SQProblem_M->zCCacheNeedsReset);
    rtssSetBlkStateChangePtr(sfcnInfo, &example_SQProblem_M->blkStateChange);
    rtssSetSampleHitsPtr(sfcnInfo, &example_SQProblem_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &example_SQProblem_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &example_SQProblem_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &example_SQProblem_M->solverInfoPtr);
  }

  example_SQProblem_M->Sizes.numSFcns = (1);

  /* register each child */
  {
    (void) memset((void *)&example_SQProblem_M->NonInlinedSFcns.childSFunctions
                  [0], 0,
                  1*sizeof(SimStruct));
    example_SQProblem_M->childSfunctions =
      (&example_SQProblem_M->NonInlinedSFcns.childSFunctionPtrs[0]);
    example_SQProblem_M->childSfunctions[0] =
      (&example_SQProblem_M->NonInlinedSFcns.childSFunctions[0]);

    /* Level2 S-Function Block: example_SQProblem/<Root>/qpOASES (qp_linprog) */
    {
      SimStruct *rts = example_SQProblem_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = example_SQProblem_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = example_SQProblem_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = example_SQProblem_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts, &example_SQProblem_M->NonInlinedSFcns.blkInfo2[0]);
      }

      ssSetRTWSfcnInfo(rts, example_SQProblem_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &example_SQProblem_M->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &example_SQProblem_M->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &example_SQProblem_M->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &example_SQProblem_M->NonInlinedSFcns.statesInfo2
                         [0]);
        ssSetPeriodicStatesInfo(rts,
          &example_SQProblem_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 7);
        ssSetPortInfoForInputs(rts,
          &example_SQProblem_M->NonInlinedSFcns.Sfcn0.inputPortInfo[0]);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &example_SQProblem_M->NonInlinedSFcns.Sfcn0.UPtrs0;
          sfcnUPtrs[0] = example_SQProblem_B.H;
          sfcnUPtrs[1] = &example_SQProblem_B.H[1];
          sfcnUPtrs[2] = &example_SQProblem_B.H[2];
          sfcnUPtrs[3] = &example_SQProblem_B.H[3];
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 4);
        }

        /* port 1 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &example_SQProblem_M->NonInlinedSFcns.Sfcn0.UPtrs1;
          sfcnUPtrs[0] = example_SQProblem_B.f;
          sfcnUPtrs[1] = &example_SQProblem_B.f[1];
          ssSetInputPortSignalPtrs(rts, 1, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidth(rts, 1, 2);
        }

        /* port 2 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &example_SQProblem_M->NonInlinedSFcns.Sfcn0.UPtrs2;
          sfcnUPtrs[0] = example_SQProblem_B.A;
          sfcnUPtrs[1] = &example_SQProblem_B.A[1];
          ssSetInputPortSignalPtrs(rts, 2, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 2, 1);
          ssSetInputPortWidth(rts, 2, 2);
        }

        /* port 3 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &example_SQProblem_M->NonInlinedSFcns.Sfcn0.UPtrs3;
          sfcnUPtrs[0] = example_SQProblem_B.lb;
          sfcnUPtrs[1] = &example_SQProblem_B.lb[1];
          ssSetInputPortSignalPtrs(rts, 3, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 3, 1);
          ssSetInputPortWidth(rts, 3, 2);
        }

        /* port 4 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &example_SQProblem_M->NonInlinedSFcns.Sfcn0.UPtrs4;
          sfcnUPtrs[0] = example_SQProblem_B.ub;
          sfcnUPtrs[1] = &example_SQProblem_B.ub[1];
          ssSetInputPortSignalPtrs(rts, 4, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 4, 1);
          ssSetInputPortWidth(rts, 4, 2);
        }

        /* port 5 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &example_SQProblem_M->NonInlinedSFcns.Sfcn0.UPtrs5;
          sfcnUPtrs[0] = &example_SQProblem_B.lbA;
          ssSetInputPortSignalPtrs(rts, 5, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 5, 1);
          ssSetInputPortWidth(rts, 5, 1);
        }

        /* port 6 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &example_SQProblem_M->NonInlinedSFcns.Sfcn0.UPtrs6;
          sfcnUPtrs[0] = &example_SQProblem_B.ubA;
          ssSetInputPortSignalPtrs(rts, 6, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 6, 1);
          ssSetInputPortWidth(rts, 6, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &example_SQProblem_M->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 4);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 2);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            example_SQProblem_B.qpOASES_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 1);
          ssSetOutputPortSignal(rts, 1, ((real_T *)
            &example_SQProblem_B.qpOASES_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidth(rts, 2, 1);
          ssSetOutputPortSignal(rts, 2, ((real_T *)
            &example_SQProblem_B.qpOASES_o3));
        }

        /* port 3 */
        {
          _ssSetOutputPortNumDimensions(rts, 3, 1);
          ssSetOutputPortWidth(rts, 3, 1);
          ssSetOutputPortSignal(rts, 3, ((real_T *)
            &example_SQProblem_B.qpOASES_o4));
        }
      }

      /* path info */
      ssSetModelName(rts, "qpOASES");
      ssSetPath(rts, "example_SQProblem/qpOASES");
      ssSetRTModel(rts,example_SQProblem_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* work vectors */
      ssSetPWork(rts, (void **) &example_SQProblem_DW.qpOASES_PWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &example_SQProblem_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &example_SQProblem_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* PWORK */
        ssSetDWorkWidth(rts, 0, 8);
        ssSetDWorkDataType(rts, 0,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &example_SQProblem_DW.qpOASES_PWORK[0]);
      }

      /* registration */
      qp_linprog(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.1);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetInputPortWidth(rts, 0, 4);
      ssSetInputPortDataType(rts, 0, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 0, 0);
      ssSetInputPortFrameData(rts, 0, 0);
      ssSetInputPortWidth(rts, 1, 2);
      ssSetInputPortDataType(rts, 1, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 1, 0);
      ssSetInputPortFrameData(rts, 1, 0);
      ssSetInputPortWidth(rts, 2, 2);
      ssSetInputPortDataType(rts, 2, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 2, 0);
      ssSetInputPortFrameData(rts, 2, 0);
      ssSetInputPortWidth(rts, 3, 2);
      ssSetInputPortDataType(rts, 3, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 3, 0);
      ssSetInputPortFrameData(rts, 3, 0);
      ssSetInputPortWidth(rts, 4, 2);
      ssSetInputPortDataType(rts, 4, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 4, 0);
      ssSetInputPortFrameData(rts, 4, 0);
      ssSetInputPortWidth(rts, 5, 1);
      ssSetInputPortDataType(rts, 5, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 5, 0);
      ssSetInputPortFrameData(rts, 5, 0);
      ssSetInputPortWidth(rts, 6, 1);
      ssSetInputPortDataType(rts, 6, SS_DOUBLE);
      ssSetInputPortComplexSignal(rts, 6, 0);
      ssSetInputPortFrameData(rts, 6, 0);
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetInputPortConnected(rts, 2, 1);
      _ssSetInputPortConnected(rts, 3, 1);
      _ssSetInputPortConnected(rts, 4, 1);
      _ssSetInputPortConnected(rts, 5, 1);
      _ssSetInputPortConnected(rts, 6, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 2, 1);
      _ssSetOutputPortConnected(rts, 3, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);
      _ssSetOutputPortBeingMerged(rts, 3, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
      ssSetInputPortBufferDstPort(rts, 2, -1);
      ssSetInputPortBufferDstPort(rts, 3, -1);
      ssSetInputPortBufferDstPort(rts, 4, -1);
      ssSetInputPortBufferDstPort(rts, 5, -1);
      ssSetInputPortBufferDstPort(rts, 6, -1);
    }
  }

  /* Initialize Sizes */
  example_SQProblem_M->Sizes.numContStates = (0);/* Number of continuous states */
  example_SQProblem_M->Sizes.numY = (0);/* Number of model outputs */
  example_SQProblem_M->Sizes.numU = (0);/* Number of model inputs */
  example_SQProblem_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  example_SQProblem_M->Sizes.numSampTimes = (1);/* Number of sample times */
  example_SQProblem_M->Sizes.numBlocks = (10);/* Number of blocks */
  example_SQProblem_M->Sizes.numBlockIO = (11);/* Number of block outputs */
  example_SQProblem_M->Sizes.numBlockPrms = (14);/* Sum of parameter "widths" */
  return example_SQProblem_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
