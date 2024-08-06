#include <stdio.h>
#include "pico/stdlib.h"

// TODO: Split into .hpp files...
#include "sdcard/include.cpp"
#include "pwm/include.cpp"
#include "lcd/include.cpp"
#include "networking/include.cpp"
#include "midi/include.cpp"

#pragma region printf macros

// source: https://stackoverflow.com/a/25108449/13294196
/* --- PRINTF_BYTE_TO_BINARY macro's --- */
#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c"
#define PRINTF_BYTE_TO_BINARY_INT8(i)    \
    (((i) & 0x80ll) ? '1' : '0'), \
    (((i) & 0x40ll) ? '1' : '0'), \
    (((i) & 0x20ll) ? '1' : '0'), \
    (((i) & 0x10ll) ? '1' : '0'), \
    (((i) & 0x08ll) ? '1' : '0'), \
    (((i) & 0x04ll) ? '1' : '0'), \
    (((i) & 0x02ll) ? '1' : '0'), \
    (((i) & 0x01ll) ? '1' : '0')

#define PRINTF_BINARY_PATTERN_INT16 \
    PRINTF_BINARY_PATTERN_INT8              PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i) \
    PRINTF_BYTE_TO_BINARY_INT8((i) >> 8),   PRINTF_BYTE_TO_BINARY_INT8(i)
#define PRINTF_BINARY_PATTERN_INT32 \
    PRINTF_BINARY_PATTERN_INT16             PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i) \
    PRINTF_BYTE_TO_BINARY_INT16((i) >> 16), PRINTF_BYTE_TO_BINARY_INT16(i)
#define PRINTF_BINARY_PATTERN_INT64    \
    PRINTF_BINARY_PATTERN_INT32             PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i) \
    PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)
/* --- end macros --- */

#pragma endregion

/*
 *  PINS USED:
 *      - GP0-15    Buzzers (PWM+PIO)
 *      - GP16-19   SD Card (SPI0)
 *      - GP20-21   LCD     (I2C0)
 *      - GP22      Select  Button
 *      - GP26      Play    Button
 *  UNUSED:
 *      - GP27-28
*/

int main()
{
    stdio_init_all();

    // Just a little debug message print
    // printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
    // printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
    // For more examples of clocks use see https://github.com/raspberrypi/pico-examples/tree/master/clocks

    /* 
        App behaviour layout:
        
        0. init lcd, to display current state in init, init buttons
        1. init sdcard, read wifi.conf for SSID, PASS
        2. init wifi, connect to ftp, copy .mid files in /midi to sdcard if not already present (filename+hash check)
            optional fallback to ram, display a separate file select menu for remote files, might not implement,
        3. deinit wifi, cyw43 calls pio_remove_program and pio_sm_unclaim
        4. display file select
            IO: NEXT (Select Button), PLAY (Play Button)
        5. play selected track, goto 4. file select
     */

    while (true)
    {
    }
}
