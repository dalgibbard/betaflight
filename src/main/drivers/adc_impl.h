/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "io.h"
#include "rcc.h"

#if defined(STM32F4)
#define ADC_TAG_MAP_COUNT 16
#elif defined(STM32F3)
#define ADC_TAG_MAP_COUNT 39
#else 
#define ADC_TAG_MAP_COUNT 10
#endif 

typedef enum ADCDevice {
    ADCINVALID = -1,
    ADCDEV_1   = 0,
#if defined(STM32F3) 
    ADCDEV_2,
    ADCDEV_MAX = ADCDEV_2,
#elif defined(STM32F4)
    ADCDEV_2,
    ADCDEV_3,
    ADCDEV_MAX = ADCDEV_3,    
#else
    ADCDEV_MAX = ADCDEV_1,
#endif
} ADCDevice;

typedef struct adcTagMap_s {
    ioTag_t tag;
    uint8_t channel;
} adcTagMap_t;
    
typedef struct adcDevice_s {
    ADC_TypeDef* ADCx;
    rccPeriphTag_t rccADC;
    rccPeriphTag_t rccDMA;
#if defined(STM32F4)
    DMA_Stream_TypeDef* DMAy_Streamx;
    uint32_t channel;
#else
    DMA_Channel_TypeDef* DMAy_Channelx;
#endif
} adcDevice_t;

extern const adcDevice_t adcHardware[];
extern const adcTagMap_t adcTagMap[ADC_TAG_MAP_COUNT];
extern adc_config_t adcConfig[ADC_CHANNEL_COUNT];
extern volatile uint16_t adcValues[ADC_CHANNEL_COUNT];

uint8_t adcChannelByTag(ioTag_t ioTag);