/**
 * display.c
 * 
 * Author: cmd05
 */

#include "string.h"
#include "display.h"

void SevenSegmentDisplay_init_gpio(SevenSegmentDisplay* display, GPIO_TypeDef* gpio_module) {
    // enable peripheral clock to bus
    if(gpio_module == GPIOA)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if(gpio_module == GPIOB)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if(gpio_module == GPIOC)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if(gpio_module == GPIOD)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    else if(gpio_module == GPIOE)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    else if(gpio_module == GPIOH)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;

    // store GPIO module pointer
    display->gpio = gpio_module;
}

void SevenSegmentDisplay_init_pins(SevenSegmentDisplay* display, 
    SevenSegmentDisplay_common_electrode_type common_electrode_type, uint32_t pin1, uint32_t pin2, 
    uint32_t pin4, uint32_t pin5, uint32_t pin6, uint32_t pin7, uint32_t pin9, uint32_t pin10) {
    
    // set common electrode type
    display->common_electrode_type = common_electrode_type;

    // store pins
    uint32_t tmp_pins[SevenSegmentDisplay_NUM_PINS] = {pin1, pin2, 0, pin4, pin5, pin6, pin7, 0, pin9, pin10};
    memcpy(display->pins, tmp_pins, sizeof(uint32_t) * SevenSegmentDisplay_NUM_PINS);

    // set pins as output pins
    for(uint32_t i = 0; i < SevenSegmentDisplay_NUM_PINS; i++) {
        if(SevenSegmentDisplay_LED_pin_map[i] != SevenSegmentDisplay_FLAG_UNKNOWN) // ignore common electrode pins
            display->gpio->MODER |= (1U << (display->pins[i] * 2));
    }
}

// Set a single, or multiple LEDs to specific state
// LED is ON if `state` is any non zero value, else OFF
void SevenSegmentDisplay_set_leds(SevenSegmentDisplay* display, SevenSegmentDisplay_LED_flags leds, int state) {
    // state will have to be converted to a binary digit, since we are performing XNOR operation
    state = (state != 0);

    for(uint32_t i = 0; i < SevenSegmentDisplay_NUM_PINS; i++) {
        if(SevenSegmentDisplay_LED_pin_map[i] != SevenSegmentDisplay_FLAG_UNKNOWN &&
            (leds & SevenSegmentDisplay_LED_pin_map[i])) {

            // CA(0)/CC(1) | state | output
            // 0           | 0     | 1
            // 0           | 1     | 0
            // 1           | 0     | 0
            // 1           | 1     | 1
            uint8_t output = !(display->common_electrode_type ^ state);

            if(output == 1)
                display->gpio->BSRR |= (1U << display->pins[i]); // set bit
            else
                display->gpio->BSRR |= (1U << (display->pins[i] + 16)); // reset bit
        }
    }
}

// Turn ON LEDs part of `leds` and turn others OFF
void SevenSegmentDisplay_show_leds(SevenSegmentDisplay* display, SevenSegmentDisplay_LED_flags leds) {
    for(uint32_t i = 0; i < SevenSegmentDisplay_NUM_PINS; i++) {
        if(SevenSegmentDisplay_LED_pin_map[i] != SevenSegmentDisplay_FLAG_UNKNOWN) {
            int state = (leds & SevenSegmentDisplay_LED_pin_map[i]) ? SevenSegmentDisplay_LED_HIGH : SevenSegmentDisplay_LED_LOW;
            SevenSegmentDisplay_set_leds(display, SevenSegmentDisplay_LED_pin_map[i], state);
        }
    }
}

// display digits 0 to 9
void SevenSegmentDisplay_show_digit(SevenSegmentDisplay* display, uint8_t digit) {
    if(digit > 9)
        return;
    
    SevenSegmentDisplay_digit_flags tmp[10] = {
        SevenSegmentDisplay_DIGIT_0,
        SevenSegmentDisplay_DIGIT_1,
        SevenSegmentDisplay_DIGIT_2,
        SevenSegmentDisplay_DIGIT_3,
        SevenSegmentDisplay_DIGIT_4,
        SevenSegmentDisplay_DIGIT_5,
        SevenSegmentDisplay_DIGIT_6,
        SevenSegmentDisplay_DIGIT_7,
        SevenSegmentDisplay_DIGIT_8,
        SevenSegmentDisplay_DIGIT_9,
    };

    SevenSegmentDisplay_show_leds(display, tmp[digit]);
}