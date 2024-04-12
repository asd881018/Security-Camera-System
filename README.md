# Security Camera System

<img width="315" alt="image" src="https://github.com/asd881018/Security-Camera-System/assets/84098790/605c1c48-64f7-4bfd-b6a0-c77787ccd39b">
<img width="316" alt="image" src="https://github.com/asd881018/Security-Camera-System/assets/84098790/b113cdcc-4e1e-499c-8c60-2c05eca52b62">


## System Overview
Our home security solution integrates a webcam with a microphone and a PIR motion sensor to provide a comprehensive monitoring system. Users can remotely monitor any location through a live video and audio feed accessed via our website.

### Key Features
- **Webcam Integration**: Streams live video in MJpeg format via UDP.
- **Microphone Input**: Captures and streams live audio to enhance monitoring capabilities.
- **Motion Detection**: Uses a PIR motion sensor to trigger video recording, capturing 3 to 5 seconds of video when motion is detected.
- **Video Playback**: Allows users to playback recorded clips directly from the webpage.
- **One-Way Communication**: Ensures secure monitoring with one-way communication from the webcam to the viewing device.

### Technical Challenges
- **Synchronous Audio Playback**: Achieving sync between audio and video streams has been challenging due to their separate transmission paths.
- **Audio in Recorded Videos**: Integrating audio into recorded video clips has presented difficulties.
- **Latency Issues**: We've optimized video size and reduced processing on the Beaglebone board to minimize latency.



## Before start, using makefile to install the package
`make all`

## To run the website

`npm start` or `sudo npm start`

### Integration Hell
Integrating the different components of this project together in one simple, cohesive, and functional product.
#### Getting Started
*IMPORTANT!! - CHANGE ALL OCCURANCES (index.js and bbg.js) OF `195.168.6.1` TO `192.168.7.1` IF YOU ARE USING A VM* 

In BeagleBone:
- Install v4l-utils: `sudo apt-get install v4l-utils libv4l-dev`
- Install FFmpeg: `sudo apt-get install ffmpeg`
- Create a new directory `mkdir /mnt/remote/v4l2_lib_BB` or `mkdir ~/cmpt433/public/v4l2_lib_BB`(in host machine)
- Copy libv4l2.so from: `cp /usr/lib/arm-linux-gnueabihf/libv4l2.so /mnt/remote/v4l2_lib_BB/libv4l2.so`

In root project directory:
- `make install`
- `make all`

In BeagleBone:
- `cd /mnt/remote/myApps && ./bbg_exec | ffmpeg -i pipe:0 -vcodec copy -f mjpeg udp://192.168.6.1:1234`

go to localhost:3000
