#include "stm32f4xx.h"
#include "stdint.h"

#include "systick.h"
#include "display.h"

int main() {
    SevenSegmentDisplay display;

    // Use GPIOA pins to control the display
    SevenSegmentDisplay_init_gpio(&display, GPIOA);

    // Pinout:
    // PA0 (display pin 1)
    // PA1 (display pin 2)
    // Common Anode (display pin 3)
    // PA8 (display pin 4)
    // PA9 (display pin 5)
    // PA4 (display pin 6)
    // PA4 (display pin 7)
    // Common Anode (display pin 8)
    // PA4 (display pin 9)
    // PA4 (display pin 10)

    // Allowed values for common electrode: SevenSegmentDisplay_COMMON_ANODE, SevenSegmentDisplay_COMMON_CATHODE
    SevenSegmentDisplay_init_pins(&display, SevenSegmentDisplay_COMMON_ANODE, 0, 1, 8, 9, 4, 5, 6, 7);

    // SevenSegmentDisplay_LED_flags flags = (SevenSegmentDisplay_FLAG_A | SevenSegmentDisplay_FLAG_F);
    // int state = 0;
    uint8_t dig = 0;

    // Display digits from 0-9
    while(1) {
        SevenSegmentDisplay_show_digit(&display, dig);
        
        // show decimal point on odd digits
        // SevenSegmentDisplay_set_leds(&display, SevenSegmentDisplay_FLAG_DP, state); 
        // state = !state;

        dig++;
        if(dig > 9) dig = 0;

        systickDelayMs(1000);
    }
}