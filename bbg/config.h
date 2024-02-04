// config.h
// A configurations module for the application. Currently has the microphone configurations.
#ifndef CONFIG_H_
#define CONFIG_H_

// microphone configurations
// PCM device name for the microphone. Use `arecord -L` to find all connected devices
#define RECORDING_DEVICE_PCM "default:CARD=WEBCAM" 
// Recording rate in Hz, recording format, and number of channels
#define RECORD_RATE 44100
#define DEFAULT_DURATION 10
#define HOST "192.168.7.1"
#define PORT 10001
#endif 
