#include "camera.h"
#include "motionsensor.h"
#include "network.h"
#include "microphone.h"

int main() {
    MotionSensor_init();
    Network_startThread();
    Microphone_init();
    Camera_init();
    Camera_on();
    Camera_mainloop();
    Camera_off();
    Camera_cleanup();
    Network_stopThread();
    MotionSensor_cleanup();
    Microphone_cleanup();
    return 0;
}
