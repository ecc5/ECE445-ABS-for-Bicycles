/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BrakeSimProto.h
 *
 * Code generated for Simulink model 'BrakeSimProto'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Thu Apr 18 17:26:33 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_BrakeSimProto_h_
#define RTW_HEADER_BrakeSimProto_h_
#ifndef BrakeSimProto_COMMON_INCLUDES_
#define BrakeSimProto_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* BrakeSimProto_COMMON_INCLUDES_ */

#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T slp;                          /* '<Root>/Relative Slip Estimation' */
  real_T Sum;                          /* '<S2>/Sum' */
  real_T MotorActuationLag;            /* '<S1>/Motor Actuation Lag' */
  real_T WheelRadius;                  /* '<Root>/Wheel Radius' */
} DW;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Brakepressure_CSTATE;         /* '<S1>/Brake pressure' */
  real_T MotorActuationLag_CSTATE;     /* '<S1>/Motor Actuation Lag' */
} X;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Brakepressure_CSTATE;         /* '<S1>/Brake pressure' */
  real_T MotorActuationLag_CSTATE;     /* '<S1>/Motor Actuation Lag' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T Brakepressure_CSTATE;      /* '<S1>/Brake pressure' */
  boolean_T MotorActuationLag_CSTATE;  /* '<S1>/Motor Actuation Lag' */
} XDis;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T _w;                           /* '<Root>/&#x3C9;_w' */
  real_T _v;                           /* '<Root>/&#x3C9;_v' */
  real_T DesiredRelativeSlip;          /* '<Root>/Desired Relative Slip' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T MotorInput;                   /* '<Root>/Motor Input' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[3];
  real_T odeF[4][3];
  ODE4_IntgData intgData;

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
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Continuous states (default storage) */
extern X rtX;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void BrakeSimProto_initialize(void);
extern void BrakeSimProto_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Effective Wheel Weight' : Unused code path elimination
 * Block '<Root>/mu-slip friction curve' : Unused code path elimination
 * Block '<Root>/Control Toggle' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'BrakeSimProto'
 * '<S1>'   : 'BrakeSimProto/Motor Controller'
 * '<S2>'   : 'BrakeSimProto/Motor Controller/Bang-bang controller'
 * '<S3>'   : 'BrakeSimProto/Motor Controller/Brake Force Estimation'
 */
#endif                                 /* RTW_HEADER_BrakeSimProto_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
