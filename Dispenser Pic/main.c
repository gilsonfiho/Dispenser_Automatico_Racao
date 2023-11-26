/*
 * File:   main.c
 * Author: Jose Icaro e Francisco Gilson
 *
 * Created on 3 de Fevereiro de 2022, 16:41
 */


#include <xc.h>

#define  _XTAL_FREQ 20000000
#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1
#define IN3 PORTCbits.RC2
#define IN4 PORTCbits.RC4

int delay_quantity = 125;
int ACIONA = 0;


//Rotacionar no sentido anti-horário.
void stepMotor_anticlockwise_90degrees(){
    
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 1;
    __delay_ms(delay_quantity);
  
}

//Rotacionar no sentido horário. 
void stepMotor_clockwise_90degrees(){
    
    IN1 = 0; IN2 = 1; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
   
}


void init(){
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    PORTD = 0b00000000;
    
    TRISA = 0b01000000;
    TRISB = 0b00000000;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
   
    RCONbits.IPEN = 0;
    INTCON = 0b10100000;
    
    T0CON =  0b10000110;

}

void __interrupt() myIsr(){
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        ACIONA = 1;
    }
}

void main(void) {
    init();
    while(1){
        if(ACIONA){
            stepMotor_clockwise_90degrees();
            PORTDbits.RD0 = 1; //Aciona o Buzzer
            stepMotor_anticlockwise_90degrees();
            stepMotor_clockwise_90degrees();
            PORTDbits.RD0 = 0; //Desliga o Buzzer
            ACIONA = 0;
        }
    }
    return;
}
