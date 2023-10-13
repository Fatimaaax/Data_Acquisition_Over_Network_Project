#include "dio.h"
//Setting a general function
int dio_Read(char port, char pin){
  if( port == 'b'){
    return PINB & (1 << pin);
   }
  if( port == 'c'){
    return PINC & (1 << pin);
    }
  if( port == 'd'){
    return PIND & (1 << pin);
    }
 }
 
void dio_Set(char port, char pin, char val){
  if( port == 'b'){
    if(val == 0) PORTB &= ~(1<<pin);
    else PORTB |= 1<<pin;
    }
  if( port == 'c'){
    if(val == 0) PORTC &= ~(1<<pin);
    else PORTC |= 1<<pin;
    }
  if( port == 'd'){
    if(val == 0) PORTD &= ~(1<<pin);
    else PORTD |= 1<<pin;
    }
}

void dio_SetDirection(char port, char pin, char dir){
  if( port == 'b'){
    if(dir == INPUT) DDRB &= ~(1<<pin);
    else DDRB |= 1<<pin;
    }
  if( port == 'c'){
    if(dir == INPUT) DDRC &= ~(1<<pin);
    else DDRC |= 1<<pin;
    }
  if( port == 'd'){
    if(dir == INPUT) DDRD &= ~(1<<pin);
    else DDRD |= 1<<pin;
    }
}
