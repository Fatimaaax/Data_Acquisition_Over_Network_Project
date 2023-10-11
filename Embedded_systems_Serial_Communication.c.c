#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include <string.h>

// Function prototypes
void initButton();
void initLED();


int main() {
    // Initialize UART communication at a specific baud rate
    uart_init(9600);

    // Initialize button and LED
    initButton();
    initLED();

    char receivedChars[10];
    char charIndex = 0;
    
   // **Button code**
   while (1) {
        // Check for button press
        if ((PIND & (1 << PD2)) == 0) {
//          for (int i = 0; i < 17; i++) {
//            uart_transmit('\b'); // Move cursor back
//            uart_transmit(' ');  // Overwrite with space
//            uart_transmit('\b'); // Move cursor back again
            /*
           * Clear message by sending('\b') to move cursor back and space (' ') to overwrite the text
           * the loop will run as long as i is less than 17 (total number of chars). It starts with i at 0 and increments it by 1 with each iteration.
           */
          //}
          uart_print("Button is pressed\n",19);
        }
        // Send "Button is pressed" message char by char
    
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
                    PORTB |= (1 << PB5);
                } else if (charIndex = 7 && strncmp(receivedChars, "led off", 7) == 0) {
                    //It compares char by char then it makes PB5 "LOW"
                    PORTB &= ~(1 << PB5);
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
    
        

/*
 * This part is for functions responsible for initializing and controlling the button and the LED
 * placed at the end for readablility and organization purposes only.
 */
void initButton() {
    // Button pin as an input 
    
    DDRD &= ~(1 << PD2); // PD2 is connected to button
    PORTD |= (1 << PD2);
}
/*
 * FOR ME: The registers operation
 * AND operation  
 * clears (sets to 0) the bit specified by PD2 in the variable while leaving all other bits unchanged.
 */


void initLED() {
    // LED pin as an output
    DDRB |= (1 << PB5); // PB5 is connected to built-in LED
}
