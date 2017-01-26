#include "mbed.h"
#include "Led.hpp"

Led myLed;

// serial init
Serial pc(SERIAL_TX, SERIAL_RX);

int main() {
    
    myLed.doK2000Light();
    
}
