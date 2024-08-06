#include <stdbool.h>
#include <string.h>
#include <cssl.h>
#include <FIFO.h>
#include <daly_bms_mod.h>

void InitBmsData(BmsData* data) {
    if (data == NULL) {
        return;
    }

    data->packVoltage = 0.0f;
    data->packCurrent = 0.0f;
    data->packSOC = 0.0f;

    data->maxCellmV = 0.0f;
    data->maxCellVNum = 0;
    data->minCellmV = 0.0f;
    data->minCellVNum = 0;
    data->cellDiff = 0.0f;

    data->tempMax = 0;
    data->tempMin = 0;
    data->tempAverage = 0.0f;

    strcpy(data->chargeDischargeStatus, "");
    data->chargeFetState = false;
    data->disChargeFetState = false;
    data->bmsHeartBeat = 0;
    data->resCapacitymAh = 0;

    data->numberOfCells = 0;
    data->numOfTempSensors = 0;
    data->chargeState = false;
    data->loadState = false;
    memset(data->dIO, 0, sizeof(data->dIO));
    data->bmsCycles = 0;

    memset(data->cellVmV, 0, sizeof(data->cellVmV));
    memset(data->cellTemperature, 0, sizeof(data->cellTemperature));
    memset(data->cellBalanceState, 0, sizeof(data->cellBalanceState));
    data->cellBalanceActive = false;

    strcpy(data->aDebug, "");
}

void DestroyBmsData(BmsData* data) {
    if (data == NULL) {
        return;
    }
    memset(data, 0, sizeof(BmsData));
}

void UpdateBmsData(uint8_t* rx_buffer);
void GetPackTemp(uint8_t* rx_buffer,BmsData* CurrentHandler);
void GetPackMesurements(uint8_t* rx_buffer,BmsData* CurrentHandler);
void GetMinMaxCellVoltage(uint8_t* rx_buffer,BmsData* CurrentHandler);
void StatusInfo(uint8_t* rx_buffer,BmsData* CurrentHandler);
void GetCellVoltage(uint8_t* rx_buffer,BmsData* CurrentHandler);
void GetCellTemperature(uint8_t* rx_buffer,BmsData* CurrentHandler);
void GetCellBalanceState(uint8_t* rx_buffer,BmsData* CurrentHandler);
void GetFailureCodes(uint8_t* rx_buffer,BmsData* CurrentHandler);

void GetDischargeChargeMosStates(uint8_t* rx_buffer,BmsData* CurrentHandler);
void RequestBMSData(BmsCommand CurrentCommand, cssl_t *serial);
