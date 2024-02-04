#include "MotionSensor.h"
#include <stdio.h>

int main() {
    MotionSensor_init();
    while (1) {
        int v = MotionSensor_getValue();
        printf("%d\n", v);
    }
    MotionSensor_cleanup();
    return 0;
}