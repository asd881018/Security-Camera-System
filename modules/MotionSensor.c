#include "MotionSensor.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define GPIO "/sys/class/gpio/gpio%d"
#define GPIO_EXPORT "/sys/class/gpio/export"

static void* MS_runner();
static char* valuePath;
static int value;
static int threadrunning = 0; // TODO: replace with proper external shutdown
static pthread_t tid;

void MotionSensor_init() {
    // Singleton
    if (threadrunning) {
        return;
    }

    // Wrote in such a way it would be easy to swap GPIO pins ...
    int len = snprintf(NULL, 0, GPIO, 49);
    char gpio_path[len];
    snprintf(gpio_path, len+1, GPIO, 49);

    // ...except this line
    runCommand("config-pin p9.23 default"); // for some reason it only works at default?

    // Check if GPIO pin is exported. if not, export it
    DIR *checkExported = opendir(gpio_path);
    if (checkExported == NULL) {
        FILE *fExport = fopen(GPIO_EXPORT, "w");
        if (fExport == NULL) {
            printf("Failed to open export file at %s\n", GPIO_EXPORT);
            exit(-1);
        }
        fprintf(fExport, "%d", 49);
        fclose(fExport);
    }

    // Set pin direction to "in"
    char directionPath[len + strlen("/direction")+1];
    strcpy(directionPath, gpio_path);
    strcat(directionPath, "/direction");
    // printf("%s\n", directionPath);

    FILE *fDir = fopen(directionPath, "w");
    if (fDir == NULL) {
        printf("Unable to open %s\n", directionPath);
        exit(-1);
    }

    fprintf(fDir, "in");
    fclose(fDir);

    char *temp = malloc(sizeof(char)*(len + strlen("/value")+1));
    strcpy(temp, gpio_path);
    strcat(temp, "/value");
    valuePath = temp;

    threadrunning = 1;
    pthread_create(&tid, NULL, &MS_runner, NULL);
}

void MotionSensor_cleanup() {
    threadrunning = 0;
    pthread_join(tid, NULL);
    free(valuePath);
}

int MotionSensor_getValue() {
    return value;
}

void readValue() {
    FILE *fRead = fopen(valuePath, "r");
    if (fRead == NULL) {
        printf("Can't open file: %s\n", valuePath);
        exit(-1);
    }
    const int MAX_VALUE = 1024;
    char buff[MAX_VALUE];
    fgets(buff, MAX_VALUE, fRead);
    fclose(fRead);
    int currentReading = atoi(buff);
    value = currentReading;
}

static void* MS_runner() {
    while (threadrunning) {
        readValue();
    }
    return NULL;
}