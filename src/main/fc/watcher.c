#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "platform.h"

#include "blackbox/blackbox.h"

#include "build/debug.h"

#include "fc/watcher.h"

static bool takeMotorsControl = false;

static uint32_t last_heartbeat_time_jetson = 0;
static uint32_t last_heartbeat_time_px4 = 0;
#define HEARTBEAT_TIMEOUT 2000000 // 2 sec

static float arming_status;
static VEHICLE_STATE vehicle_state;

static bool isPXConnected = false;

void setPXStatus(bool connected){
    isPXConnected = connected;
}

bool getPXStatus(void){
    return isPXConnected;
}

static bool isPX4Connected(timeUs_t current_time){
    return (current_time - last_heartbeat_time_px4) < HEARTBEAT_TIMEOUT;
}

static bool isJetsonConnected(timeUs_t current_time){
    return (current_time - last_heartbeat_time_jetson) < HEARTBEAT_TIMEOUT;
}

void watcherUpdate(timeUs_t current_time){
    bool timeout_flag = isPX4Connected(current_time) || isJetsonConnected(current_time);
    if (timeout_flag && arming_status == 1.0)
    {
        takeMotorsControl = true;
    }
}

bool getTakeMotorsControl(void) {
    return takeMotorsControl;
}

void setPX4Time(timeUs_t current_time) {
    last_heartbeat_time_px4 = current_time;
}

void setJetsonTime(timeUs_t current_time) {
    last_heartbeat_time_jetson = current_time;
}

void setPixhawkArmingStatus(float status){
    arming_status = status;
}

void setVehicleState(int state){
    vehicle_state = state;
}