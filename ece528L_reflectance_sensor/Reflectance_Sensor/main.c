/**
 * @file main.c
 * @brief Main source code for the Reflectance Sensor program.
 *
 * This file contains the main entry point and function definitions for the Reflectance Sensor program.
 * It interfaces with the following:
 *  - User LEDs of the TI MSP432 LaunchPad
 *  - 8-Channel QTRX Sensor Array module
 *
 * To verify the pinout of the user buttons and LEDs, refer to the MSP432P401R SimpleLink Microcontroller LaunchPad Development Kit User's Guide
 * Link: https://docs.rs-online.com/3934/A700000006811369.pdf
 *
 * @author
 */

#include <stdint.h>
#include "msp.h"
#include "inc/Clock.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/GPIO.h"
#include "inc/Reflectance_Sensor.h"
#include "inc/Print_Binary.h"

enum Possibility {
    CENTER = 0x18,
    SLIGHTLY_LEFT_FROM_CENTER = 0x1C,
    SLIGHTLY_RIGHT_FROM_CENTER = 0x38,
    FAR_LEFT_FROM_CENTER = 0x01,
    FAR_RIGHT_FROM_CENTER = 0x80,
    LEFT_TURN = 0xF8,
    RIGHT_TURN = 0x1F,
    T_INTERSECTION = 0xFF,
    DEAD_END = 0x00
};

void Detect_Line_Position(uint8_t reflectance_sensor_data){
    switch(reflectance_sensor_data){
        case CENTER:
           LED1_Output(RED_LED_OFF);
           LED2_Output(RGB_LED_GREEN);
           break;
        case SLIGHTLY_LEFT_FROM_CENTER:
           LED1_Output(RED_LED_OFF);
           LED2_Output(RGB_LED_YELLOW);
           break;
        case SLIGHTLY_RIGHT_FROM_CENTER:
           LED1_Output(RED_LED_OFF);
           LED2_Output(RGB_LED_PINK);
           break;
        case FAR_LEFT_FROM_CENTER:
           LED1_Output(RED_LED_OFF);
           LED2_Output(RGB_LED_WHITE);
           break;
        case FAR_RIGHT_FROM_CENTER:
           LED1_Output(RED_LED_OFF);
           LED2_Output(RGB_LED_SKY_BLUE);
           break;
        case LEFT_TURN:
           LED1_Output(RED_LED_ON);
           LED2_Output(RGB_LED_WHITE);
           break;
        case RIGHT_TURN:
           LED1_Output(RED_LED_ON);
           LED2_Output(RGB_LED_SKY_BLUE);
           break;
        case T_INTERSECTION:
           LED1_Output(RED_LED_OFF);
           LED2_Output(RGB_LED_BLUE);
           break;
        case DEAD_END:
           LED1_Output(RED_LED_OFF);
           LED2_Output(RGB_LED_RED);
           break;
        default:
           LED1_Output(RED_LED_OFF);
           LED2_Output(RGB_LED_OFF);
    }
}

int main(void)
{
    // Initialize the 48 MHz Clock
    Clock_Init48MHz();

    // Initialize the built-in red LED and the RGB LEDs
    LED1_Init();
    LED2_Init();

    // Initialize the reflectance sensor
    Reflectance_Sensor_Init();

    // Initialize EUSCI_A0_UART
    EUSCI_A0_UART_Init_Printf();

    // Initialize a local variable to store the data read from the reflectance sensor
    uint8_t reflectance_sensor_data = 0;

    while(1)
    {
        reflectance_sensor_data = Reflectance_Sensor_Read(1000);
        Detect_Line_Position(reflectance_sensor_data);
        Print_Binary(reflectance_sensor_data);
        Clock_Delay1ms(10);
    }
}
