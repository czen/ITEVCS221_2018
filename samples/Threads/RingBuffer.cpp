#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#define NUM_BLOCKS 10
#define BLOCK_SIZE 8
#define AMPLITUDE 100
#define PERIOD 30
#define INTERVAL (3*PERIOD)
#define BUFFER_SIZE (NUM_BLOCKS*BLOCK_SIZE)

int g_anBuffer[BUFFER_SIZE];
sem_t g_FreeSpace, g_UsedSpace;
int divides(int n1, int n2)
{
    return (n1 % n2 == 0);
}

void *thread_proc(void *pvData)
{
int t;
for (t = 0; t <= INTERVAL; ++ t)
{
int i = t % BUFFER_SIZE;
if (divides(i, BLOCK_SIZE))
sem_wait(&g_FreeSpace);
g_anBuffer[i] =
t == INTERVAL ?
AMPLITUDE + 1 :
AMPLITUDE *
sin(1.0 * t / PERIOD);
//
if (t == INTERVAL ||
divides(i + 1, BLOCK_SIZE))
sem_post(&g_UsedSpace);
}
// for (t = 0; ...)
}
// thread_proc()
int main()
{
int i = 0, nData;
pthread_t hThread;
//
sem_init(&g_FreeSpace, 0, NUM_BLOCKS);
sem_init(&g_UsedSpace, 0, 0);
//
pthread_create(&hThread, NULL, &thread_proc, NULL);
do
{
if (divides(i, BLOCK_SIZE))
sem_wait(&g_UsedSpace);
//
nData = g_anBuffer[i];
printf(" (%d, %d)", i, nData);
fflush(stdout);
//
i = (i + 1) % BUFFER_SIZE;
//
if (nData > AMPLITUDE ||
divides(i, BLOCK_SIZE))
{
sem_post(&g_FreeSpace);
printf(" |");
fflush(stdout);
}
}
while (nData <= AMPLITUDE);
//
pthread_join(hThread, NULL);
//
printf("\n");
//
sem_destroy(&g_FreeSpace);
sem_destroy(&g_UsedSpace);
}
// main()




