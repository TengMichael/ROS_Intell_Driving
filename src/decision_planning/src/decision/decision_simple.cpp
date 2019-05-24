//
// File: decision_simple.cpp
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
#include "include/decision/decision_simple.h"
#include "include/decision/decision_simple_private.h"

// Includes for objects with custom storage classes.
#include "include/decision/decision_simple.h"

// Named constants for Chart: '<Root>/Chart'
#define IN_Braking                     ((uint8_T)1U)
#define IN_Following                   ((uint8_T)2U)
#define IN_Free_driving                ((uint8_T)3U)
#define IN_Intersection                ((uint8_T)1U)
#define IN_Lane_change                 ((uint8_T)4U)
#define IN_Lane_driving                ((uint8_T)2U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_Pass                        ((uint8_T)1U)
#define IN_Stop                        ((uint8_T)3U)
#define IN_Stop_or_Following           ((uint8_T)2U)

// Block states (default storage)
glt1_D_Work glv1_DWork;

// Model step function
void decision_simple_step(void)
{
  // Chart: '<Root>/Chart' incorporates:
  //   Inport: '<Root>/C1'
  //   Inport: '<Root>/E1'
  //   Inport: '<Root>/E2'
  //   Inport: '<Root>/E3'
  //   Inport: '<Root>/intersection_C1'
  //   Inport: '<Root>/lane_driving_C1'
  //   Inport: '<Root>/lane_driving_C2'
  //   Inport: '<Root>/lane_driving_C3'
  //   Inport: '<Root>/lane_driving_C4'
  //   Inport: '<Root>/lane_driving_E1'
  //   Inport: '<Root>/lane_driving_E2'
  //   Inport: '<Root>/lane_driving_F'

  // Gateway: Chart
  // During: Chart
  if (glv1_DWork.bitsForTID0.is_active_c3_decision_simple == 0U) {
    // Entry: Chart
    glv1_DWork.bitsForTID0.is_active_c3_decision_simple = 1;

    // Entry Internal: Chart
    // Transition: '<S1>:67'
    glv1_DWork.bitsForTID0.is_c3_decision_simple = IN_Stop;

    // Entry 'Stop': '<S1>:58'
    upper_state = 1;
  } else {
    switch (glv1_DWork.bitsForTID0.is_c3_decision_simple) {
     case IN_Intersection:
      upper_state = 3;

      // During 'Intersection': '<S1>:122'
      if ((!(C1 != 0)) && (E3 != 0)) {
        // Transition: '<S1>:120'
        // Exit Internal 'Intersection': '<S1>:122'
        glv1_DWork.bitsForTID0.is_Intersection = IN_NO_ACTIVE_CHILD;
        glv1_DWork.bitsForTID0.is_c3_decision_simple = IN_Lane_driving;

        // Entry 'Lane_driving': '<S1>:44'
        upper_state = 2;

        // Entry Internal 'Lane_driving': '<S1>:44'
        // Transition: '<S1>:41'
        glv1_DWork.bitsForTID0.is_Lane_driving = IN_Free_driving;

        // Entry 'Free_driving': '<S1>:35'
        lane_driving_state = 1;
      } else if (glv1_DWork.bitsForTID0.is_Intersection == IN_Pass) {
        intersection_state = 1;

        // During 'Pass': '<S1>:128'
        if (intersection_C1 != 0) {
          // Transition: '<S1>:126'
          glv1_DWork.bitsForTID0.is_Intersection = IN_Stop_or_Following;

          // Entry 'Stop_or_Following': '<S1>:127'
          intersection_state = 2;
        }
      } else {
        intersection_state = 2;

        // During 'Stop_or_Following': '<S1>:127'
        if (!(intersection_C1 != 0)) {
          // Transition: '<S1>:125'
          glv1_DWork.bitsForTID0.is_Intersection = IN_Pass;

          // Entry 'Pass': '<S1>:128'
          intersection_state = 1;
        }
      }
      break;

     case IN_Lane_driving:
      upper_state = 2;

      // During 'Lane_driving': '<S1>:44'
      if ((!(E1 != 0)) && (E2 != 0)) {
        // Transition: '<S1>:115'
        // Exit Internal 'Lane_driving': '<S1>:44'
        glv1_DWork.bitsForTID0.is_Lane_driving = IN_NO_ACTIVE_CHILD;
        glv1_DWork.bitsForTID0.is_c3_decision_simple = IN_Stop;

        // Entry 'Stop': '<S1>:58'
        upper_state = 1;
      } else if (C1 != 0) {
        // Transition: '<S1>:129'
        // Exit Internal 'Lane_driving': '<S1>:44'
        glv1_DWork.bitsForTID0.is_Lane_driving = IN_NO_ACTIVE_CHILD;
        glv1_DWork.bitsForTID0.is_c3_decision_simple = IN_Intersection;

        // Entry 'Intersection': '<S1>:122'
        upper_state = 3;

        // Entry Internal 'Intersection': '<S1>:122'
        // Transition: '<S1>:124'
        glv1_DWork.bitsForTID0.is_Intersection = IN_Pass;

        // Entry 'Pass': '<S1>:128'
        intersection_state = 1;
      } else {
        switch (glv1_DWork.bitsForTID0.is_Lane_driving) {
         case IN_Braking:
          lane_driving_state = 4;

          // During 'Braking': '<S1>:89'
          if ((!(lane_driving_C3 != 0)) && (!(lane_driving_C1 != 0))) {
            // Transition: '<S1>:91'
            glv1_DWork.bitsForTID0.is_Lane_driving = IN_Following;

            // Entry 'Following': '<S1>:33'
            lane_driving_state = 2;
          } else {
            if ((lane_driving_C4 != 0) && ((lane_driving_E1 != 0) ||
                 (lane_driving_C1 != 0)) && (lane_driving_F != 0)) {
              // Transition: '<S1>:117'
              glv1_DWork.bitsForTID0.is_Lane_driving = IN_Lane_change;

              // Entry 'Lane_change': '<S1>:36'
              lane_driving_state = 3;
            }
          }
          break;

         case IN_Following:
          lane_driving_state = 2;

          // During 'Following': '<S1>:33'
          if ((lane_driving_C3 != 0) && (!(lane_driving_C4 != 0))) {
            // Transition: '<S1>:93'
            glv1_DWork.bitsForTID0.is_Lane_driving = IN_Braking;

            // Entry 'Braking': '<S1>:89'
            lane_driving_state = 4;
          } else if (!(lane_driving_C2 != 0)) {
            // Transition: '<S1>:39'
            glv1_DWork.bitsForTID0.is_Lane_driving = IN_Free_driving;

            // Entry 'Free_driving': '<S1>:35'
            lane_driving_state = 1;
          } else {
            if (((lane_driving_E1 != 0) || (lane_driving_C1 != 0)) &&
                (lane_driving_F != 0)) {
              // Transition: '<S1>:37'
              glv1_DWork.bitsForTID0.is_Lane_driving = IN_Lane_change;

              // Entry 'Lane_change': '<S1>:36'
              lane_driving_state = 3;
            }
          }
          break;

         case IN_Free_driving:
          lane_driving_state = 1;

          // During 'Free_driving': '<S1>:35'
          if (lane_driving_C2 != 0) {
            // Transition: '<S1>:43'
            glv1_DWork.bitsForTID0.is_Lane_driving = IN_Following;

            // Entry 'Following': '<S1>:33'
            lane_driving_state = 2;
          } else {
            if ((lane_driving_E1 != 0) && (lane_driving_F != 0)) {
              // Transition: '<S1>:40'
              glv1_DWork.bitsForTID0.is_Lane_driving = IN_Lane_change;

              // Entry 'Lane_change': '<S1>:36'
              lane_driving_state = 3;
            }
          }
          break;

         default:
          lane_driving_state = 3;

          // During 'Lane_change': '<S1>:36'
          if ((lane_driving_C3 != 0) && (!(lane_driving_C4 != 0))) {
            // Transition: '<S1>:94'
            glv1_DWork.bitsForTID0.is_Lane_driving = IN_Braking;

            // Entry 'Braking': '<S1>:89'
            lane_driving_state = 4;
          } else if (((lane_driving_E2 != 0) && (lane_driving_C2 != 0)) ||
                     (!(lane_driving_F != 0))) {
            // Transition: '<S1>:42'
            glv1_DWork.bitsForTID0.is_Lane_driving = IN_Following;

            // Entry 'Following': '<S1>:33'
            lane_driving_state = 2;
          } else {
            if ((lane_driving_E2 != 0) && (!(lane_driving_C2 != 0))) {
              // Transition: '<S1>:34'
              glv1_DWork.bitsForTID0.is_Lane_driving = IN_Free_driving;

              // Entry 'Free_driving': '<S1>:35'
              lane_driving_state = 1;
            }
          }
          break;
        }
      }
      break;

     default:
      upper_state = 1;

      // During 'Stop': '<S1>:58'
      if ((E1 != 0) && (!(E2 != 0))) {
        // Transition: '<S1>:62'
        glv1_DWork.bitsForTID0.is_c3_decision_simple = IN_Lane_driving;

        // Entry 'Lane_driving': '<S1>:44'
        upper_state = 2;

        // Entry Internal 'Lane_driving': '<S1>:44'
        // Transition: '<S1>:41'
        glv1_DWork.bitsForTID0.is_Lane_driving = IN_Free_driving;

        // Entry 'Free_driving': '<S1>:35'
        lane_driving_state = 1;
      }
      break;
    }
  }

  // End of Chart: '<Root>/Chart'
}

// Model initialize function
void decision_simple_initialize(void)
{
  // (no initialization code required)
}

//
// File trailer for generated code.
//
// [EOF]
//
