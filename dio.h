#ifndef _dio_
#define _dio_


#define INPUT 0x0
#define OUTPUT 0x1

int dio_Read(char port, char pin);
void dio_Set(char port, char pin, char val);

void dio_SetDirection(char port, char pin, char dir);

#endif // DIO_H
