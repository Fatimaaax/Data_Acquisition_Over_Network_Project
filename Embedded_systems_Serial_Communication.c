#include <avr/io.h>
#include <string.h>
#include "uart.h"
#include "dio.h"


// Function prototypes
void initButton();
void initLED();


int main() {
    // Initialize UART communication at a specific baud rate
    

    // Initialize button and LED
    init();

    char receivedChars[10];
    char charIndex = 0;
    
   // **Button code**
 while (1) {
    // Check for button press
    if (dio_Read('d', 2) == 0) {
        if (buttonPressed == 0) {
            uart_print("Button is pressed\n", 19);
            buttonPressed = 1; // Set the flag to 1 to indicate that the button has been pressed
        }
    }
    else {
        buttonPressed = 0; // Reset the flag when the button is not pressed
    }

/* the "Button is pressed" message will be printed only once when the button is pressed, 
 * and the code will continue running without being blocked by the while loop. 
 * The flag variable helps control whether the message should be printed or not.
 */

        if (uart_recieve_ready()) {
            char receivedChar = uart_recieve();
            if (receivedChar == '\n') {
                /* 
                 *  End of line, process the received command
                 *  for me remove later: int strncmp(const char *str1, const char *str2, size_t n) compares at most the first n bytes of str1 and str2.
                 *  this library compares two strings character by character up to a specified number of characters or until a null terminator
                */
                if (charIndex = 6 && strncmp(receivedChars, "led on", 6) == 0) {
                    //It compares char by char then it makes PB5 "HIGH"
                    dio_Set('b', 5, 1);
                } else if (charIndex = 7 && strncmp(receivedChars, "led off", 7) == 0) {
                    //It compares char by char then it makes PB5 "LOW"
                    dio_Set('b', 5, 0);
                }
                // Clear the receivedChars array for the next command
                memset(receivedChars, 0, sizeof(receivedChars));
                charIndex = 0;
            } else {
                // Store the received character in the array
                receivedChars[charIndex++] = receivedChar;
                if(charIndex >= sizeof(receivedChars)){
                  charIndex = 0;
                }
            }
        }
    }

    return 0;
}

void init() { 
    uart_init(9600);
    //DDRD &= ~(1 << PD2); // PD2 is connected to button
    dio_SetDirection('d', 2, INPUT);
    //PORTD |= (1 << PD2);
    dio_Set('d', 2, 1);
    dio_SetDirection('b', 5, OUTPUT);
}




