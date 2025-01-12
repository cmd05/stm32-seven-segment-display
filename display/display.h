/**
 * display.h
 * 
 * Author: cmd05
 */

#pragma once

#include "stm32f4xx.h"
#include "stdint.h"

typedef enum SevenSegmentDisplay_info {
    SevenSegmentDisplay_NUM_PINS = 10
} SevenSegmentDisplay_info;

typedef enum SevenSegmentDisplay_common_electrode_type {
    SevenSegmentDisplay_COMMON_ANODE = 0,
    SevenSegmentDisplay_COMMON_CATHODE = 1
} SevenSegmentDisplay_common_electrode_type;

typedef enum SevenSegmentDisplay_LED_states {
    SevenSegmentDisplay_LED_LOW = 0,
    SevenSegmentDisplay_LED_HIGH = 1
} SevenSegmentDisplay_LED_states;

typedef enum SevenSegmentDisplay_LED_flags {
    SevenSegmentDisplay_FLAG_A = 1,
    SevenSegmentDisplay_FLAG_B = 2,
    SevenSegmentDisplay_FLAG_C = 4,
    SevenSegmentDisplay_FLAG_D = 8,
    SevenSegmentDisplay_FLAG_E = 16,
    SevenSegmentDisplay_FLAG_F = 32,
    SevenSegmentDisplay_FLAG_G = 64,
    SevenSegmentDisplay_FLAG_DP = 128,
    SevenSegmentDisplay_FLAG_UNKNOWN = 256,
} SevenSegmentDisplay_LED_flags;

// 7-segment display pinout
static SevenSegmentDisplay_LED_flags SevenSegmentDisplay_LED_pin_map[SevenSegmentDisplay_NUM_PINS] = {
    SevenSegmentDisplay_FLAG_E,         // Pin 1
    SevenSegmentDisplay_FLAG_D,         // Pin 2
    SevenSegmentDisplay_FLAG_UNKNOWN,   // Pin 3 - Common Electrode
    SevenSegmentDisplay_FLAG_C,         // Pin 4
    SevenSegmentDisplay_FLAG_DP,        // Pin 5
    SevenSegmentDisplay_FLAG_B,         // Pin 6
    SevenSegmentDisplay_FLAG_A,         // Pin 7
    SevenSegmentDisplay_FLAG_UNKNOWN,   // Pin 8 - Common Electrode
    SevenSegmentDisplay_FLAG_F,         // Pin 9
    SevenSegmentDisplay_FLAG_G,         // Pin 10
};

typedef enum SevenSegmentDisplay_digit_flags {
    SevenSegmentDisplay_FLAGS_ALL = (SevenSegmentDisplay_FLAG_A | SevenSegmentDisplay_FLAG_B |
        SevenSegmentDisplay_FLAG_C | SevenSegmentDisplay_FLAG_D | SevenSegmentDisplay_FLAG_E |
        SevenSegmentDisplay_FLAG_F | SevenSegmentDisplay_FLAG_G | SevenSegmentDisplay_FLAG_DP),
    SevenSegmentDisplay_FLAGS_ALL_NODP = (SevenSegmentDisplay_FLAGS_ALL & ~SevenSegmentDisplay_FLAG_DP),

    SevenSegmentDisplay_DIGIT_0 = (SevenSegmentDisplay_FLAGS_ALL_NODP & ~SevenSegmentDisplay_FLAG_G),
    SevenSegmentDisplay_DIGIT_1 = (SevenSegmentDisplay_FLAG_B | SevenSegmentDisplay_FLAG_C),
    SevenSegmentDisplay_DIGIT_2 = (SevenSegmentDisplay_FLAGS_ALL_NODP & ~(SevenSegmentDisplay_FLAG_C | SevenSegmentDisplay_FLAG_F)),
    SevenSegmentDisplay_DIGIT_3 = (SevenSegmentDisplay_FLAGS_ALL_NODP & ~(SevenSegmentDisplay_FLAG_E | SevenSegmentDisplay_FLAG_F)),
    SevenSegmentDisplay_DIGIT_4 = (SevenSegmentDisplay_FLAGS_ALL_NODP & ~(SevenSegmentDisplay_FLAG_A | SevenSegmentDisplay_FLAG_E | SevenSegmentDisplay_FLAG_D)),
    SevenSegmentDisplay_DIGIT_5 = (SevenSegmentDisplay_FLAGS_ALL_NODP & ~(SevenSegmentDisplay_FLAG_B | SevenSegmentDisplay_FLAG_E)),
    SevenSegmentDisplay_DIGIT_6 = (SevenSegmentDisplay_FLAGS_ALL_NODP & ~(SevenSegmentDisplay_FLAG_B)),
    SevenSegmentDisplay_DIGIT_7 = (SevenSegmentDisplay_FLAG_A | SevenSegmentDisplay_FLAG_B | SevenSegmentDisplay_FLAG_C),
    SevenSegmentDisplay_DIGIT_8 = (SevenSegmentDisplay_FLAGS_ALL_NODP),
    SevenSegmentDisplay_DIGIT_9 = (SevenSegmentDisplay_FLAGS_ALL_NODP & ~SevenSegmentDisplay_FLAG_E),
} SevenSegmentDisplay_digit_flags;

typedef struct SevenSegmentDisplay {
    uint32_t pins[SevenSegmentDisplay_NUM_PINS];
    GPIO_TypeDef* gpio;
    SevenSegmentDisplay_common_electrode_type common_electrode_type;
} SevenSegmentDisplay;

void SevenSegmentDisplay_init_gpio(SevenSegmentDisplay* display, GPIO_TypeDef* gpio_module);
void SevenSegmentDisplay_init_pins(SevenSegmentDisplay* display, 
    SevenSegmentDisplay_common_electrode_type common_electrode_type, uint32_t pin1, uint32_t pin2,
    uint32_t pin4, uint32_t pin5, uint32_t pin6, uint32_t pin7, uint32_t pin9, uint32_t pin10);

void SevenSegmentDisplay_set_leds(SevenSegmentDisplay* display, SevenSegmentDisplay_LED_flags leds, int state);
void SevenSegmentDisplay_show_leds(SevenSegmentDisplay* display, SevenSegmentDisplay_LED_flags leds);
void SevenSegmentDisplay_show_digit(SevenSegmentDisplay* display, uint8_t digit);