/* 
 * File:   Counter.h
 * Author: ameliza
 *
 * Created on 6 de Novembro de 2019, 09:18
 */

#ifndef COUNTER_H
#define	COUNTER_H

typedef void (*CALLBACK_t) (void);

class Counter {
public:
    
    enum Modo_t {
        INPUT = 0, // INPUT CAPTURE
        OUTPUT = 1 // OUTPUT COMPARE
    };
    
    enum CS_t { // clock select
        FALLING = 0, // borda de descida
        RISING = 1 // borda de subida
    };
    
    Counter(Modo_t modo, CALLBACK_t pCallback);
    
    uint16_t get();
    void set_in(uint16_t start, CS_t edge);
    void set_out(uint16_t start, uint16_t end, CS_t edge);
    void enable_in();
    void enable_out();
    void clear();
    
    static void isr_handler();
    
private:
    uint16_t start;
    uint16_t end;
    static CALLBACK_t _pCallback;
};

#endif	/* COUNTER_H */