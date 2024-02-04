# 433Project

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
