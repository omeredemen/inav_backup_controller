#ifndef WATCHER
#define WATCHER

#include "common/time.h"

typedef enum VEHICLE_STATE
{
   VEHICLE_STATE_UNINIT=0, /* Uninitialized system, state is unknown. | */
   VEHICLE_STATE_BOOT=1, /* System is booting up. | */
   VEHICLE_STATE_CALIBRATING=2, /* System is calibrating and not flight-ready. | */
   VEHICLE_STATE_STANDBY=3, /* System is grounded and on standby. It can be launched any time. | */
   VEHICLE_STATE_ACTIVE=4, /* System is active and might be already airborne. Motors are engaged. | */
   VEHICLE_STATE_CRITICAL=5, /* System is in a non-normal flight mode (failsafe). It can however still navigate. | */
   VEHICLE_STATE_EMERGENCY=6, /* System is in a non-normal flight mode (failsafe). It lost control over parts or over the whole airframe. It is in mayday and going down. | */
   VEHICLE_STATE_POWEROFF=7, /* System just initialized its power-down sequence, will shut down now. | */
   VEHICLE_STATE_FLIGHT_TERMINATION=8, /* System is terminating itself (failsafe or commanded). | */
   VEHICLE_STATE_ENUM_END=9, /*  | */
} VEHICLE_STATE;

void watcherUpdate(timeUs_t current_time);
bool getTakeMotorsControl(void);

void setPXStatus(bool connected);
bool getPXStatus(void);
void setPX4Time(timeUs_t current_time);
void setJetsonTime(timeUs_t current_time);
void setPixhawkArmingStatus(float status);

void setVehicleState(int state);

#endif