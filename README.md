# Overview 
This lab explores the operation of an eight-channel infrared reflectance sensor array using the MSP432 microcontroller. The sensor array distinguishes between light and dark surfaces by measuring differences in reflected infrared light. GPIO pins control the infrared emitters and read the sensor outputs. The program charges the sensor outputs, allows them to discharge for a specified time, and reads their digital states. These readings are displayed as an eight-bit binary value to indicate the location of a dark line beneath the array.

# Components Used
- MSP432
- Reflectance Sensor 8 bit
- Ti-RSLK Chassis
- USB-A to Micro USB Cable

# Analysis and Results
The eight-bit sensor reading represents the state of each sensor at the selected sampling time. Light surfaces reflect more infrared light, causing the sensor outputs to discharge faster. Dark surfaces absorb more infrared light, causing the outputs to remain high longer. With an appropriate sampling delay, a binary 1 therefore indicates a dark surface, while a binary 0 indicates a light surface.

Expected readings include 00000000 when all sensors are above a white surface and 11111111 when all sensors are above a black surface. A reading such as 00011000 indicates that the two center sensors detect the dark line. Moving the line across the array should shift the corresponding high bits. The sampling delay, sensor height, and ambient lighting can affect these readings and should remain consistent during testing.

# Known Issues
No issues were discovered, the sensor read all values correctly and verified through LEDs and serial terminal.

# References
- MSP432P4xx SimpleLink Microcontrollers Technical Reference Manual
- 8-Channel QTRX Sensor Array Product Page


# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Reflectance Sensor Lab
The Reflectance Sensor lab interfaces with the following:

* User LEDs of the TI MSP432 LaunchPad
* 8-Channel QTRX Sensor Array - [Product Link](https://www.pololu.com/product/3672)

# Question 1
The 8-Channel QTRX Sensor Array consists of 8 reflectance sensors where each have a dimmable IR emitter together with a phototransistor. Besides the main 8 sensors there are also 8 sensor outputs with VIN, GND, CTRL ODD, and CTRL EVEN. The minimum operating voltage is 2.9V and the maximum is 5.5V. 

# Question 2
CTRL EVEN and CTRL ODD pins on the sensor array are responsible for enabling the sensors if both are set. Both when active have a logic HIGH by default. For the MSP432, they connect to P5.3 and P9.2.

# Question 3 5.0 9.7
void P5_0_and_P9_7_Init(void){
    P5SEL0 &= ~0x01;
    P5SEL1 &= ~0x01;
    P9SEL0 &= ~0x80;
    P9SEL1 &= ~0x80;
    P5OUT  &= ~0x01;
    P9OUT  &= ~0x80;
    P5DIR  |= 0x01;
    P9DIR  |= 0x80;
}

# Question 4 
/**
* @file print_binary.c
*
* @brief Main source code for Print_Binary *program.
*
* This file contains the main entry point and * the implementation of the Print_Binary function that takes in a uint8_t value and
* prints the value in binary format.
*
* @author Daniel Khrlobian
*/

#include <stdio.h>
#include <stdint.h>
void Print_Binary(uint8_t value_to_convert);
int main()
{
    uint8_t value_to_convert = 170;
    printf("Decimal: %d\n", value_to_convert);
    Print_Binary(value_to_convert);
    return 0;
}

void Print_Binary(uint8_t value_to_convert)
{
    printf("Binary: ");
    for (int bit = 7; bit >= 0; bit--){
        if(bit == 3){
            printf("_");
        }
        printf("%u", (unsigned)((value_to_convert >> bit) & 1u));
    }
    putchar('\n');
}
// REFERENCE: https://sqlpey.com/c/c-cpp-integer-to-binary-printf/