// record.h
// Module records audio from the attached usb webcam asysnchronously. It uses
// the device name specified in the config.h file. Change RECORDING_DEVICE_PCM
// macro when changing the devie. Can find the PCM of available devices using
// `arecord -L` command
#ifndef RECORD_H_
#define RECORD_H_

#include <stdbool.h>

// Initializes the Microphone module. Starts a thread in the background.
void Microphone_init(void);

// Cleans up the module. The caller will need to manually delete any recording
// files created.
void Microphone_cleanup(void);

// Records audio and stores it at the provided fileName.
void Microphone_recordAudio(char *fileName, int durationInS);

// Blocking call that Returns true if the previous recording was recorded. False
// otherwise.
bool Microphone_wasRecorded();
#endif
