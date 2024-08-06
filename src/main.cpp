#include <stdio.h>
#include <daly_bms_mod.h>

extern "C" {
    #include <cssl.h>
}

uint8_t TxBuffer[XFER_BUFFER_LENGTH];
uint8_t RxBuffer[XFER_BUFFER_LENGTH];

int maint(int argc, char **argv){

    return 0;
}