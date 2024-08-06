#include <stdbool.h>
#include <string.h>
#include <cssl.h>
#include <FIFO.h>

#ifndef DALY_BMS_MOD_H
#define DALY_BMS_MOD_H

#define XFER_BUFFER_LENGTH 13
#define MIN_NUMBER_CELLS 1
#define MAX_NUMBER_CELLS 48
#define MIN_NUMBER_TEMP_SENSORS 1
#define MAX_NUMBER_TEMP_SENSORS 16

typedef enum {
    Parse_Succ,
    Parse_Failed
}ParserResult;

typedef enum {
    VOUT_IOUT_SOC = 0x90,
    MIN_MAX_CELL_VOLTAGE = 0x91,
    MIN_MAX_TEMPERATURE = 0x92,
    DISCHARGE_CHARGE_MOS_STATUS = 0x93,
    STATUS_INFO = 0x94,
    CELL_VOLTAGES = 0x95,
    CELL_TEMPERATURE = 0x96,
    CELL_BALANCE_STATE = 0x97,
    FAILURE_CODES = 0x98,
    DISCHRG_FET = 0xD9,
    CHRG_FET = 0xDA,
    BMS_RESET = 0x00,
} BmsCommand;

typedef struct {
    // data from 0x90
    float packVoltage;   // pressure (0.1 V)
    float packCurrent;   // acquisition (0.1 V)
    float packSOC;       // State Of Charge

    // data from 0x91
    float maxCellmV;     // maximum monomer voltage (mV)
    int maxCellVNum;     // Maximum Unit Voltage cell No.
    float minCellmV;     // minimum monomer voltage (mV)
    int minCellVNum;     // Minimum Unit Voltage cell No.
    float cellDiff;      // difference between cells

    // data from 0x92
    int tempMax;         // maximum monomer temperature (40 Offset,°C)
    int tempMin;         // Maximum monomer temperature cell No.
    float tempAverage;   // Average Temperature

    // data from 0x93
    char chargeDischargeStatus[50];  // charge/discharge status (0 stationary ,1 charge ,2 discharge)
    bool chargeFetState;             // charging MOS tube status
    bool disChargeFetState;          // discharge MOS tube state
    int bmsHeartBeat;                // BMS life(0~255 cycles)
    int resCapacitymAh;              // residual capacity mAH

    // data from 0x94
    int numberOfCells;               // amount of cells
    int numOfTempSensors;            // amount of temp sensors
    bool chargeState;                // charger status 0=disconnected 1=connected
    bool loadState;                  // Load Status 0=disconnected 1=connected
    bool dIO[8];                     // No information about this
    int bmsCycles;                   // charge / discharge cycles

    // data from 0x95
    float cellVmV[48];               // Store Cell Voltages in mV

    // data from 0x96
    int cellTemperature[16];         // array of cell Temperature sensors

    // data from 0x97
    bool cellBalanceState[48];       // bool array of cell balance states
    bool cellBalanceActive;          // bool is cell balance active

    // debug data string
    char aDebug[100];
} BmsData;

typedef struct {
    // data from 0x98
    /* 0x00 */
    bool levelOneCellVoltageTooHigh;
    bool levelTwoCellVoltageTooHigh;
    bool levelOneCellVoltageTooLow;
    bool levelTwoCellVoltageTooLow;
    bool levelOnePackVoltageTooHigh;
    bool levelTwoPackVoltageTooHigh;
    bool levelOnePackVoltageTooLow;
    bool levelTwoPackVoltageTooLow;

    /* 0x01 */
    bool levelOneChargeTempTooHigh;
    bool levelTwoChargeTempTooHigh;
    bool levelOneChargeTempTooLow;
    bool levelTwoChargeTempTooLow;
    bool levelOneDischargeTempTooHigh;
    bool levelTwoDischargeTempTooHigh;
    bool levelOneDischargeTempTooLow;
    bool levelTwoDischargeTempTooLow;

    /* 0x02 */
    bool levelOneChargeCurrentTooHigh;
    bool levelTwoChargeCurrentTooHigh;
    bool levelOneDischargeCurrentTooHigh;
    bool levelTwoDischargeCurrentTooHigh;
    bool levelOneStateOfChargeTooHigh;
    bool levelTwoStateOfChargeTooHigh;
    bool levelOneStateOfChargeTooLow;
    bool levelTwoStateOfChargeTooLow;

    /* 0x03 */
    bool levelOneCellVoltageDifferenceTooHigh;
    bool levelTwoCellVoltageDifferenceTooHigh;
    bool levelOneTempSensorDifferenceTooHigh;
    bool levelTwoTempSensorDifferenceTooHigh;

    /* 0x04 */
    bool chargeFETTemperatureTooHigh;
    bool dischargeFETTemperatureTooHigh;
    bool failureOfChargeFETTemperatureSensor;
    bool failureOfDischargeFETTemperatureSensor;
    bool failureOfChargeFETAdhesion;
    bool failureOfDischargeFETAdhesion;
    bool failureOfChargeFETBreaker;
    bool failureOfDischargeFETBreaker;

    /* 0x05 */
    bool failureOfAFEAcquisitionModule;
    bool failureOfVoltageSensorModule;
    bool failureOfTemperatureSensorModule;
    bool failureOfEEPROMStorageModule;
    bool failureOfRealtimeClockModule;
    bool failureOfPrechargeModule;
    bool failureOfVehicleCommunicationModule;
    bool failureOfIntranetCommunicationModule;

    /* 0x06 */
    bool failureOfCurrentSensorModule;
    bool failureOfMainVoltageSensorModule;
    bool failureOfShortCircuitProtection;
    bool failureOfLowVoltageNoCharging;
} AlarmData;

void InitBmsData(BmsData* data);
void DestroyBmsData(BmsData* data);
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

void RegisterRequestBMSData(BmsCommand CurrentCommand, cssl_t *serial);






#endif // DALY_BMS_MOD_H
