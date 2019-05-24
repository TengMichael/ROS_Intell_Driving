//
// File: rtwtypes.h
//
// Code generated for Simulink model 'decision_simple'.
//
// Model version                  : 1.759
// Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
// C/C++ source code generated on : Tue Apr  9 19:39:39 2019
//
#ifndef RTWTYPES_H
#define RTWTYPES_H

// Logical type definitions
#if (!defined(__cplusplus))
#  ifndef false
#   define false                       (0U)
#  endif

#  ifndef true
#   define true                        (1U)
#  endif
#endif

//=======================================================================*
//  Target hardware information
//    Device type: Freescale->S12x
//    Number of bits:     char:   8    short:   16    int:  16
//                        long:  32
//                        native word size:  16
//    Byte ordering: BigEndian
//    Signed integer division rounds to: Zero
//    Shift right on a signed integer as arithmetic shift: on
// =======================================================================

//=======================================================================*
//  Fixed width word size data types:                                     *
//    int8_T, int16_T, int32_T     - signed 8, 16, or 32 bit integers     *
//    uint8_T, uint16_T, uint32_T  - unsigned 8, 16, or 32 bit integers   *
// =======================================================================
typedef signed char int8_T;
typedef unsigned char uint8_T;
typedef int int16_T;
typedef unsigned int uint16_T;
typedef long int32_T;
typedef unsigned long uint32_T;

//===========================================================================*
//  Generic type definitions: boolean_T, char_T, byte_T, int_T, uint_T,       *
//                            ulong_T.                                        *
// ===========================================================================
typedef unsigned char boolean_T;
typedef int int_T;
typedef unsigned int uint_T;
typedef unsigned long ulong_T;
typedef char char_T;
typedef unsigned char uchar_T;
typedef char_T byte_T;

//=======================================================================*
//  Min and Max:                                                          *
//    int8_T, int16_T, int32_T     - signed 8, 16, or 32 bit integers     *
//    uint8_T, uint16_T, uint32_T  - unsigned 8, 16, or 32 bit integers   *
// =======================================================================
#define MAX_int8_T                     ((int8_T)(127))
#define MIN_int8_T                     ((int8_T)(-128))
#define MAX_uint8_T                    ((uint8_T)(255U))
#define MAX_int16_T                    ((int16_T)(32767))
#define MIN_int16_T                    ((int16_T)(-32768))
#define MAX_uint16_T                   ((uint16_T)(65535U))
#define MAX_int32_T                    ((int32_T)(2147483647L))
#define MIN_int32_T                    ((int32_T)(-2147483647L-1L))
#define MAX_uint32_T                   ((uint32_T)(0xFFFFFFFFUL))

// Block D-Work pointer type
typedef void * pointer_T;

#endif                                 // RTWTYPES_H

//
// File trailer for generated code.
//
// [EOF]
//
