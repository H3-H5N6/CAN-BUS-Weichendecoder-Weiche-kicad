#ifndef CAN_COMMUNICATOR_H
#define CAN_COMMUNICATOR_H

#include <Arduino.h>
#include <ACAN2515.h>
#include "CanConfiguration.h"
#include "Weiche.h"
#include "Signal.h"

typedef void (*ChangeWeiche)(uint16_t);

class CanComm {
    public:
        CanComm(CAN_CONFIGURATION &_conf, Weiche *weiche, Signal *signal, ChangeWeiche _cw);
        void sendDetailWeichenStatus();
        void processCanMessageGetStatus();
        void processCanMessageChangeState();
        void processCanMessage(); 
        void init();
    private:
        CAN_CONFIGURATION can_configuration;
        CANMessage frame;
        Weiche *weiche;
        Signal *signal;
        boolean send_mode = 0;
        ChangeWeiche changeWeicheCallback = {};
        


};


#endif