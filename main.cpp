/* 
 * File:   main.cpp
 * Author: ameliza
 *
 * Created on 9 de Novembro de 2019, 19:07
 */

#include <avr/interrupt.h>
#include "Counter.h"
#include "GPIO.h"
#include "GPIO_Port.h"
#include "uart.h"

//GPIO botao(48, GPIO::INPUT); // ICP5
GPIO botao(47, GPIO::INPUT); // T5
GPIO led(54, GPIO::OUTPUT); // A0

void Contador();

Counter counter = Counter(Counter::OUTPUT, &Contador);

void Contador(){
    led.toggle(); // acende ou apaga o LED
    counter.clear();
}

int main() {
    
    counter.set_out('1', '3', Counter::FALLING);
    counter.enable_out();

    sei();

    while(1){
    
    }

    return 0;
}

/*
Counter counter = Counter(Counter::INPUT, &Contador);
UART serial(9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);

void Contador(){
    led.toggle(); // acende ou apaga o LED
    serial.put(TCNT5);
    counter.clear();
}

int main() {
    
    counter.set_in('0', Counter::FALLING);
    counter.enable_in();

    sei();

    while(1){
    
    }

    return 0;
}
*/