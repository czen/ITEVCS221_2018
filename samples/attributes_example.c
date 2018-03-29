#include <stdio.h>

int main(int nArgC, char *apszArgV[], char *apszEnvP[])
{
    printf("%d", *apszEnvP[0]);
}