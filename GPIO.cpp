/* 
 * File:   GPIO.cpp
 * Author: natalia
 * 
 * Created on 30 de Setembro de 2019, 00:03
 */

#include <avr/io.h>
#include "GPIO.h"

GPIO::GPIO(uint8_t id, PortDirection_t dir){
	_bit = GPIO_PORT::id_to_bit[id];
	_px = GPIO_PORT::AllPorts[GPIO_PORT::id_to_port[id]];
	_px->dir(_bit, dir);
}
GPIO::~GPIO() {}

bool GPIO::get() {
	return _px->GPIO_Port::get(_bit);
}

void GPIO::set(bool val) {
	return _px->GPIO_Port::set(_bit, val);
}

void GPIO::clear() {
    return _px->GPIO_Port::clear(_bit);
}

void GPIO::toggle() {
	return _px->GPIO_Port::toggle(_bit);
}