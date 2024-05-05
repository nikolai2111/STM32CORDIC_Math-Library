/**
 ******************************************************************************
 * Header		: CORDIC Math
 ******************************************************************************
 * @file		: cordic_math.h
 * @brief		: Header for cordic_math.c file.
 * @author		: N. Zoller (NZ)
 * @date		: 20.12.2023
 ******************************************************************************
 * @remark		: Last Modifications:
 * 				- none
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef CORDIC_MATH_H_
#define CORDIC_MATH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include "main.h"

/* Libraries */
#include <math.h>

/* Hardware */
#include "stm32g4xx_ll_cordic.h"
#include "cordic.h"

/* Exported types -----------------------------------------------------------*/

/* Exported constants -------------------------------------------------------*/
enum Cordic_Func {
	COS,
	SIN,
	PHASE,
	MODULUS,
	ATAN,
	COSH,
	SINH,
	ATANH,
	LN,
	SQRT,
};

/* Exported macro -----------------------------------------------------------*/
#define Q31_SCALAR 		( (float) M_PI )
#define F32_TO_Q31(F)	( (int32_t) ((fmodf((F) + Q31_SCALAR, 2.f * Q31_SCALAR) + ((F) < -Q31_SCALAR ? Q31_SCALAR : -Q31_SCALAR)) * ((float)(INT32_MAX + 1u) / Q31_SCALAR)) )
#define Q31_TO_F32(Q)	( (int32_t) (Q) / (float)(INT32_MAX + 1u) )

/* Exported variables -------------------------------------------------------*/

/* Exported functions prototypes --------------------------------------------*/
extern float sinf_c(float x);

/* Private defines ----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CORDIC_MATH_H_ */

/**
 ******************************************************************************
 * End Header	: GPIO Configuration
 ******************************************************************************
 */


