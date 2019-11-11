/* 
 * File:   GPIO.h
 * Author: natalia
 *
 * Created on 30 de Setembro de 2019, 00:03
 */

#ifndef GPIO_H
#define	GPIO_H

#include "GPIO_Port.h"


class GPIO {
public:
    
    enum PortDirection_t {
        INPUT = 0,
        OUTPUT = 1
    };
    
    GPIO(uint8_t id, PortDirection_t dir);
    ~GPIO();
    
    bool get();
    void set(bool val = 1);
    void clear();
    void toggle();
    
private:
    uint8_t _bit;
    GPIO_PORT::GPIO_Port * _px; //Ponteiro para a Porta 
};

#endif	/* GPIO_H */