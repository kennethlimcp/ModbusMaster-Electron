// Test code
SYSTEM_MODE(MANUAL);

#include "ModbusMaster-Particle.h"

#define LED_DEBUG D7

//42482d3d
SerialLogHandler logHandler(9600,LOG_LEVEL_WARN, {
    {"app", LOG_LEVEL_TRACE},
    {"system", LOG_LEVEL_INFO}
});

ModbusMaster slave;

void preTransmission() {
    // set interface to TX
}

void postTransmission() {
    // set interface to RX
}

void idle() {
    delay(10); // in case slave only replies after 10ms
    Particle.process(); // avoids letting the connection close if open
}

void setup() {
    pinMode(LED_DEBUG, OUTPUT);
    digitalWrite(LED_DEBUG, LOW);
    slave.begin(1,Serial1); // slaveID=1, serial=Serial1
    slave.setSpeed(19200,SERIAL_8E1);
    // slave.setSpeed(9600); // same as above
    slave.enableDebug(); // to catch the logs
    slave.preTransmission(preTransmission);
    slave.postTransmission(postTransmission);
    slave.idle(idle);
/*
    uint8_t result = slave.readHoldingRegisters(3918,2);

    if (!result) {
        uint16_t value = slave.getResponseBuffer(0);
        Log.info("Received: %0x",value);
    } else {
        Log.warn("Read error");
    } */
}

void loop() {
    uint8_t result = slave.readHoldingRegisters(3914,4);

    if (!result) {
        uint16_t value = slave.getResponseBuffer(0);
        Log.info("Received: %0x",value);
    } else {
        Log.warn("Read error");
    }

    delay(5000);
    digitalWrite(LED_DEBUG, !digitalRead(LED_DEBUG));
}
