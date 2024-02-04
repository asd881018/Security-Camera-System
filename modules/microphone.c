// Impelementation of the Micorphone module
#include "microphone.h"
#include "config.h"
#include "utils.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

#define BUFFER_SIZE 1024
static pthread_t microphoneTid;
static pthread_mutex_t microphoneMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t canRecord;
static bool threadRunning;

static char *recordingFileName = NULL;
static int recordingDuration = 0;
static bool success = false;

static void *runner();

// Initializes the Microphone module. Starts a thread in the background.
void Microphone_init(void) {

    if (!threadRunning) {
        threadRunning = true;
        pthread_cond_init(&canRecord, NULL);
        pthread_create(&microphoneTid, NULL, &runner, NULL);
    }
}

// Cleans up the module. The caller will need to manually delete any recording
// files created.
void Microphone_cleanup(void) {
    pthread_join(microphoneTid, NULL);
    pthread_cond_destroy(&canRecord);
    pthread_mutex_destroy(&microphoneMutex);
    threadRunning = false;
}

// Non-blocking call that  signals to records audio and stores it at the
// provided fileName. Use Microphone_wasRecorded() to check whether the file was
// recorded (which is a blocking call)
void Microphone_recordAudio(char *fileName, int durationInS) {
    pthread_mutex_lock(&microphoneMutex);
    recordingFileName = fileName;
    recordingDuration = durationInS;
    pthread_cond_signal(&canRecord);
    pthread_mutex_unlock(&microphoneMutex);
}

// Blocking call that Returns true if the previous recording was recorded. False
// otherwise.
bool Microphone_wasRecorded() {
    pthread_mutex_lock(&microphoneMutex);
    bool wasRecorded = success;
    pthread_mutex_unlock(&microphoneMutex);

    return wasRecorded;
}

static void *runner() {
    while (threadRunning) {
        pthread_mutex_lock(&microphoneMutex);
        pthread_cond_wait(&canRecord, &microphoneMutex);
        success = false;
        char buff[BUFFER_SIZE];
        char *formatString = "arecord -r %d -f %s -D %s -d %d -c %d %s";

        snprintf(buff, BUFFER_SIZE, formatString, RECORD_RATE, FORMAT,
                 RECORDING_DEVICE_PCM, recordingDuration, NUM_CHANNELS,
                 recordingFileName);

        success = runCommand(buff);

        pthread_mutex_unlock(&microphoneMutex);
    }
    return NULL;
}
