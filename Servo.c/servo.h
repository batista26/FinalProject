#ifndef SERVO_H
#define SERVO_H

// Initializes the servo by configuring Timer B2 and P2.1 pin
void initServo(void);

// Sets the servo pulse width in microseconds (1000 to 2000 typical)
void setServo(unsigned int pulseWidth);

#endif // SERVO_H
