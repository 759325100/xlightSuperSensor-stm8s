#ifndef __GLOBAL_H
#define __GLOBAL_H

#include <stm8s.h> //Required for the stdint typedefs
#include "stdio.h"
#include "string.h"
#include "stm8s_conf.h"

/* Exported types ------------------------------------------------------------*/
// Include Sensors
/// Comment off line to disable sensor
//#define EN_SENSOR_ALS
//#define EN_SENSOR_MIC
//#define EN_SENSOR_PIR
#define EN_SENSOR_DHT
#define EN_SENSOR_PM25
//#define EN_SENSOR_MQ135
//#define EN_SENSOR_MQ2
//#define EN_SENSOR_MQ7

// Common Data Type
#define UC                        uint8_t
#define US                        uint16_t
#define UL                        uint32_t
#define SHORT                     int16_t
#define LONG                      int32_t

// Switch value for set power command
#define DEVICE_SW_OFF               0       // Turn Off
#define DEVICE_SW_ON                1       // Turn On
#define DEVICE_SW_TOGGLE            2       // Toggle
#define DEVICE_SW_DUMMY             3       // Detail followed

// Node type
#define NODE_TYP_GW               'g'
#define NODE_TYP_LAMP             'l'
#define NODE_TYP_REMOTE           'r'
#define NODE_TYP_SYSTEM           's'
#define NODE_TYP_THIRDPARTY       't'

// NodeID Convention
#define NODEID_GATEWAY          0
#define NODEID_MAINDEVICE       1
#define NODEID_MIN_DEVCIE       8
#define NODEID_MAX_DEVCIE       63
#define NODEID_MIN_REMOTE       64
#define NODEID_MAX_REMOTE       127
#define NODEID_PROJECTOR        128
#define NODEID_KEYSIMULATOR     129
#define NODEID_SUPERSENSOR      130
#define NODEID_SMARTPHONE       139
#define NODEID_MIN_GROUP        192
#define NODEID_MAX_GROUP        223
#define NODEID_DUMMY            255
#define BASESERVICE_ADDRESS     0xFE
#define BROADCAST_ADDRESS       0xFF

#define UNIQUE_ID_LEN           8

typedef struct
{
  UC version                  :8;           // Data version, other than 0xFF
  UC nodeID;                                // Node ID for this device
  UC NetworkID[6];
  UC present                  :1;           // 0 - not present; 1 - present
  UC state                    :1;           // SuperSensor On/Off
  UC reserved                 :6;
  UC subID;                                 // SubID
  UC type;                                  // Type of SuperSensor
  US token;
  //char Organization[24];                    // Organization name
  //char ProductName[24];                     // Product name
  UC rfPowerLevel             :2;           // RF Power Level 0..3
  UC swTimes                  :3;           // On/Off times
  UC rptTimes                 :2;           // Sending message max repeat times [0..3]
  UC reserved1                :1;
  US senMap                   :16;          // Sensor Map
} Config_t;

extern Config_t gConfig;
extern bool gIsChanged;
extern uint8_t _uniqueID[UNIQUE_ID_LEN];

bool isIdentityEqual(const UC *pId1, const UC *pId2, UC nLen);
void GotNodeID();
void GotPresented();

#define IS_MINE_SUBID(nSID)        ((nSID) == 0 || ((nSID) & gConfig.subID))

#endif /* __GLOBAL_H */