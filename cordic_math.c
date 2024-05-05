/**
 ******************************************************************************
 * Source		: CORDIC Math
 ******************************************************************************
 * @file		: cordic_math.c
 * @brief		: Contains the STM32 CORDIC math library.
 * @detail		: This library implements the following math function in
 *				hardware on the CORDIC co-processor:
 *				- sine
 *				- cosine
 *				- sinh
 *				- cosh
 *				- atan
 *				- atan2
 *				- atanh
 *				- modulus
 *				- square root
 *				- natural logarithm
 *
 *				This co-processor is only present in the following MCUs:
 * 				- STM32G4 and STM32U5 series
 * 				- STM32H563/573 product line
 * 				- STM32H723/733 product line
 * 				- STM32H725/735 product line
 * 				- STM32H730 Value line.
 *
 * @attention	So the use of this library on other MCUs is not recommend.
 * @author		: N. Zoller (NZ)
 * @date		: 18.09.2023
 ******************************************************************************
 * @remark		: Last Modifications:
 * 				- 12.12.23	NZ	Mod: Cleaned up file.
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

/* Includes -----------------------------------------------------------------*/
#include "cordic_math.h"

/* Private typedef ----------------------------------------------------------*/

/* Private define -----------------------------------------------------------*/

/* Private macro ------------------------------------------------------------*/

/* Private variables --------------------------------------------------------*/

/* Private function prototypes ----------------------------------------------*/
static void restrictAngle(float *angle);

/* External functions -------------------------------------------------------*/

/* Private user code --------------------------------------------------------*/

/**
 * @brief		Sine of x
 *
 * @param  		x:		Argument x.
 * @return 		float	Sine of x.
 *
 * @details		Computes the sine of the argument x. Angles are specified in
 * 				radians. Functions like the sinf() function form libm, but used
 * 				the hardware of the CORDIC co-processor.
 *
 * @author		N. Zoller (NZ)
 * @date		20.12.2023
 * @remark		Last Modifications:
 * 				- none
 *****************************************************************************/
float sinf_c(float x)
{
	/* Configure the CORDIC */
	LL_CORDIC_Config(CORDIC,
		LL_CORDIC_FUNCTION_SINE,		/* sine function */
		LL_CORDIC_PRECISION_6CYCLES,	/* max precision for q1.31 sine */
		LL_CORDIC_SCALE_0,				/* no scale */
		LL_CORDIC_NBWRITE_1,			/* One input data: angle */
		LL_CORDIC_NBREAD_1,				/* One output data: sine */
		LL_CORDIC_INSIZE_32BITS,		/* q1.31 format for input data */
		LL_CORDIC_OUTSIZE_32BITS);		/* q1.31 format for output data */

	/* Limit the angle to the boundaries of the CORDIC */
	restrictAngle(&x);

	/* Write angle */
	LL_CORDIC_WriteData(CORDIC, F32_TO_Q31(x));

	/* Read sine */
	return Q31_TO_F32((int32_t) LL_CORDIC_ReadData(CORDIC));
}

/**
 * @brief		Restrict the angle to [-M_PI, M_PI]
 *
 * @param  		angle:	Pointer to the angle to restrict
 * @return 		None
 *
 * @details		Restrict the angle to [-M_PI, M_PI] for all angles between
 * 				(-inf, inf) so the function maps all the angles to the limits
 * 				of the CORDIC co-processor.
 *
 * @author		N. Zoller (NZ)
 * @date		20.12.2023
 * @remark		Last Modifications:
 * 				- none
 * @TODO		- Create a macro for this function.
 *****************************************************************************/
static void restrictAngle(float *angle)
{
	/* Normalize angle to be in the range [-2*M_PI, 2*M_PI] */
	*angle = fmodf(*angle, 2.0f * M_PI);

	/* Correct angle, if negative */
	if (*angle < 0)
	{
		*angle = *angle + 2.0f * M_PI;
	}

	/* Move angle from [0, 2*M_PI] to [-M_PI, M_PI] and flip sign */
	*angle = -1.0f * (*angle - M_PI);
}

/**
 ******************************************************************************
 * End Source	: CORDIC Math
 ******************************************************************************
 */

