/* 
 * File:   Counter.cpp
 * Author: ameliza
 * 
 * Created on 6 de Novembro de 2019, 09:18
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include "Counter.h"

CALLBACK_t Counter::_pCallback;

/**
 * Construtor onde s�o esperados par�metros
 * necess�rios para iniciar uma classe
 * @param modo - pode-se escolher o tipo de interrup��o a ser
 * utilizada, output compare ou input capture
 * @param pCallback - fun��o feita pelo usu�rio
 */
Counter::Counter(Modo_t modo, CALLBACK_t pCallback) {
    
    _pCallback = pCallback;
    
    if(modo){ // OUTPUT
        DDRL = ~(1 << PL2); // pin T5
    }
    else{ // INPUT
        DDRL = ~(1 << PL1); // pin ICP5        
    }
}

/**
 * Obt�m o valor contido no registrador TCNT,
 * que � o valor inicial do contador
 * @return 
 */
uint16_t Counter::get(){
    return start;
}

/**
 * Define os par�metros necess�rios para que a interrup��o
 * do tipo input capture aconte�a
 * @param start - valor inicial do contador
 * @param edge - borda de clock
 */
void Counter::set_in(uint16_t start, CS_t edge){
    this->start = start;
    TCNT5 = start;
    
    if(edge){ // rising
        TCCR5B = (1<<ICES5) | (1<<CS50) | (1<<CS52); // 0100 0101 -> clk/1024
    }
    else{ // falling
        TCCR5B = (1<<CS50) | (1<<CS52); // 0000 0101 -> clk/1024
    }
}

/**
 * Define os par�metros necess�rios para que a interrup��o
 * do tipo output compare aconte�a
 * @param start - valor inicial do contador
 * @param end - valor final do contador
 * @param edge - borda de clock
 */
void Counter::set_out(uint16_t start, uint16_t end, CS_t edge){
    this->start = start;
    this->end = end;
    TCNT5 = start;
    OCR5A = end;
    
    if(edge){ // rising
        TCCR5B = (1<<CS50) | (1<<CS51) | (1<<CS52); // 111 
    }
    else{ // falling
        TCCR5B = (1<<CS51) | (1<<CS52); // 110
    }
}

/**
 * Limpa o buffer do contador, voltando o
 * registrador TCNT para o valor start
 */
void Counter::clear(){
    TCNT5 = start;
}

/**
 * Habilita a interrup��o do tipo input capture
 */
void Counter::enable_in(){
    TIMSK5 = (1 << ICIE5);
}

/**
 * Habilita a interrup��o do tipo output compare
 */
void Counter::enable_out(){
    TIMSK5 = (1 << OCIE5A);
}

/**
 * Essa fun��o chama o callback criado pelo usu�rio
 */
void Counter::isr_handler(){
    (*_pCallback)();
}

/**
 * Esse vetor de interrup��o chama a fun��o isr_handler
 * quando acontecer uma interrup��o do tipo output compare
 */
ISR(TIMER5_COMPA_vect){
Counter::isr_handler();}

/**
 * Esse vetor de interrup��o chama a fun��o isr_handler
 * quando acontecer uma interrup��o do tipo input capture
 */
ISR(TIMER5_CAPT_vect){
Counter::isr_handler();}