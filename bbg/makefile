TARGET= bbg_exec
SOURCES= main.c camera.c utils.c motionsensor.c network.c microphone.c

PUBDIR = $(HOME)/cmpt433/public/myApps
OUTDIR = $(PUBDIR)
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow

LFLAGS = -L$(HOME)/cmpt433/public/v4l2_lib_BB

app:
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET) $(LFLAGS) -lv4l2 -lpthread

clean:
	rm -f $(OUTDIR)/$(TARGET)
