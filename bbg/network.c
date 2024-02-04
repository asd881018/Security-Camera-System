#include "network.h"
#include "motionsensor.h"
#include <pthread.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 12345
#define MAX_LEN 1024

static bool threadRunning = false;
static pthread_t tid;

static int socketDescriptor;
static struct sockaddr_in sinRemote;
static unsigned int sin_len = sizeof(sinRemote);

static void *networkRunner(void *args);
static void sendUserReply(char *messageRx);

void Network_startThread(void)
{
    if (threadRunning)
    {
        return;
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);

    bind(socketDescriptor, (struct sockaddr *)&sin, sizeof(sin));

    pthread_create(&tid, NULL, &networkRunner, NULL);
    threadRunning = true;
}

void Network_stopThread(void)
{
    threadRunning = false;
    pthread_join(tid, NULL);
}

static void getUserInput(char *messageRx)
{
    recvfrom(socketDescriptor, messageRx, MAX_LEN - 1, 0,
             (struct sockaddr *)&sinRemote, &sin_len);

    messageRx[MAX_LEN - 1] = 0;
}

static void *networkRunner(void *args)
{
    while (threadRunning)
    {
        char messageRx[MAX_LEN];
        getUserInput(messageRx);

        sendUserReply(messageRx);
    }

    close(socketDescriptor);
    return NULL;
}

static void sendUserReply(char *messageRx)
{
    char messageTx[MAX_LEN];

    if (strncmp(messageRx, "motion", strlen("motion")) == 0) {
        snprintf(messageTx, MAX_LEN, "%d", MotionSensor_getValue());
        sendto(socketDescriptor, messageTx, strlen(messageTx),
                0, (struct sockaddr *)&sinRemote, sin_len);
    }

}
