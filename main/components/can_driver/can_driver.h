#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

// --- CAN Definitions ---
/* IDs */
#define BUFFER_SIZE     50
#define THROTTLE_MID    0x00
#define THROTTLE_RUN    0x01
#define THROTTLE_CHOKE  0x02

#define SYNC_ID         0x001       // message for bus sync
#define THROTTLE_ID     0x100       // 1by = throttle state (0x00, 0x01 or 0x02)
#define FLAGS_ID        0x101       // 1by
#define IMU_ACC_ID      0x200       // 6by           
#define IMU_DPS_ID      0x201       // 6by          
#define ANGLE_ID        0X205       // 4by
#define SPEED_ID        0x300       // 2by          
#define SOC_ID          0x302       // 1by
#define RPM_ID          0x304       // 2by           
#define SOT_ID          0x305       // 1by
#define TEMPERATURE_ID  0x400       // 1by     
#define CVT_ID          0x401       // 1by
#define FUEL_ID         0x500       // 2by           
#define VOLTAGE_ID      0x502       // 4by
#define CURRENT_ID      0x505       // 4by
#define LAT_ID          0x600       // 8by
#define LNG_ID          0x700       // 8by

#define MMI_ID          0x306
#define TCU_ID          0x307
#define SCU_ID          0x308
#define MPU_ID          0x309

// --- Public Function Prototypes ---
void can_driver_start(void);

#endif // CAN_DRIVER_H
