// config.h
// A configurations module for the application. Currently has the microphone configurations.
#ifndef CONFIG_H_
#define CONFIG_H_

// microphone configurations
// PCM device name for the microphone. Use `arecord -L` to find all connected devices
#define RECORDING_DEVICE_PCM "plughw:CARD=C615,DEV=0" 
// Recording rate in Hz, recording format, and number of channels
#define RECORD_RATE 88200
#define FORMAT "S16_LE"
#define NUM_CHANNELS 4

#endif 
