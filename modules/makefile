OUTFILE = msTest
OUTDIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow -pthread

all:
	make app
app:
	$(CC_C) $(CFLAGS) main.c utils.c MotionSensor.c -o $(OUTDIR)/$(OUTFILE)
clean:
	rm $(OUTDIR)/$(OUTFILE)