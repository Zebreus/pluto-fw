#pragma once
#include "hal.h"

#define HAL_LCD_DIG_OTHERS 0xf

#define HAL_LCD_SEG_BARS  HAL_LCD_SEG(HAL_LCD_DIG_OTHERS, 0)
#define HAL_LCD_SEG_PM    HAL_LCD_SEG(HAL_LCD_DIG_OTHERS, 1)
#define HAL_LCD_SEG_BELL  HAL_LCD_SEG(HAL_LCD_DIG_OTHERS, 2)
#define HAL_LCD_SEG_24H   HAL_LCD_SEG(HAL_LCD_DIG_OTHERS, 3)
#define HAL_LCD_SEG_LAP   HAL_LCD_SEG(HAL_LCD_DIG_OTHERS, 4)
#define HAL_LCD_SEG_COLON HAL_LCD_SEG(HAL_LCD_DIG_OTHERS, 5)