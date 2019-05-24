//
// File: decision_simple.h
//
// Code generated for Simulink model 'decision_simple'.
//
// Model version                  : 1.770
// Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
// C/C++ source code generated on : Tue May 14 19:44:10 2019
//
// Target selection: ert.tlc
// Embedded hardware selection: Freescale->S12x
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_decision_simple_h_
#define RTW_HEADER_decision_simple_h_
#ifndef decision_simple_COMMON_INCLUDES_
# define decision_simple_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // decision_simple_COMMON_INCLUDES_

#include "decision_simple_types.h"

// Macros for accessing real-time model data structure

// Block states (default storage) for system '<Root>'
typedef struct {
  struct {
    uint_T is_Lane_driving:3;          // '<Root>/Chart'
    uint_T is_c3_decision_simple:2;    // '<Root>/Chart'
    uint_T is_Intersection:2;          // '<Root>/Chart'
    uint_T is_active_c3_decision_simple:1;// '<Root>/Chart'
  } bitsForTID0;
} glt1_D_Work;

// Block states (default storage)
extern glt1_D_Work glv1_DWork;

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void decision_simple_initialize(void);
  extern void decision_simple_step(void);

#ifdef __cplusplus

}
#endif

// Exported data declaration

// Declaration for custom storage class: Global
extern uint8_T C1;
extern uint8_T E1;
extern uint8_T E2;
extern uint8_T E3;
extern uint8_T intersection_C1;
extern uint8_T intersection_state;
extern uint8_T lane_driving_C1;
extern uint8_T lane_driving_C2;
extern uint8_T lane_driving_C3;
extern uint8_T lane_driving_C4;
extern uint8_T lane_driving_E1;
extern uint8_T lane_driving_E2;
extern uint8_T lane_driving_F;
extern uint8_T lane_driving_state;
extern uint8_T upper_state;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'decision_simple'
//  '<S1>'   : 'decision_simple/Chart'


//-
//  Requirements for '<Root>': decision_simple

#endif                                 // RTW_HEADER_decision_simple_h_

//
// File trailer for generated code.
//
// [EOF]
//
