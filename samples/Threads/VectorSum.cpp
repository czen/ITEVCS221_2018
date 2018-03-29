#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void get_data(size_t *puDataSize, double **ppdData)
{
    const size_t cuDataSize = 1000013;
    size_t i;
    *puDataSize = cuDataSize;
    *ppdData = (double *) calloc(cuDataSize, sizeof (double));
    for (i = 0; i < cuDataSize; ++ i)
       (*ppdData)[i] = 1;
}

void free_data(double *pdData)
{
 free(pdData);
}

double sum(double *pdData, size_t uStart, size_t uEnd)
{
    size_t i;
    double dResult = 0;
    //
    for (i = uStart; i < uEnd; ++ i)
    dResult += pdData[i];
    //
    return dResult;
}

typedef struct
{
    size_t m_uStart, m_uEnd;
    double *m_pdData;
    double m_dResult;
} ThreadParams;

void *thread_proc(void *pvParam)
{
    ThreadParams *pParams = (ThreadParams *) pvParam;
    pParams->m_dResult = sum(
    pParams->m_pdData, pParams->m_uStart, pParams->m_uEnd);
    return NULL;
}

int main()
{
    size_t i, uDataSize;
    const size_t cuNumThreads = 8;
    pthread_t ahThreads[cuNumThreads - 1];
    ThreadParams aParams[cuNumThreads];
    double *pdData;
    double dResult = 0;
    //
    get_data(&uDataSize, &pdData);
    //
    size_t uChunkSize = uDataSize / cuNumThreads;
    size_t uIndex = 0, uPrev = 0;
    for (i = 0; i < cuNumThreads; ++ i)
    {
    if (i == cuNumThreads - 1)
    uIndex = uDataSize;
    else
    uIndex += uChunkSize;
    //
    aParams[i].m_uStart = uPrev;
    aParams[i].m_uEnd = uIndex;
    aParams[i].m_pdData = pdData;
    uPrev = uIndex;
    //
    if (i < cuNumThreads - 1)
    pthread_create(&ahThreads[i], NULL, &thread_proc, &aParams[i]);
    } // for (i = 0; i < cuNumThreads; ++ i)
    //
    thread_proc(&aParams[cuNumThreads - 1]);
    //
    for (i = 0; i < cuNumThreads - 1; ++ i)
    pthread_join(ahThreads[i], NULL);
    //
    for (i = 0; i < cuNumThreads; ++ i)
    dResult += aParams[i].m_dResult;
    //
    printf("Result: %lf\n", dResult);
    //
    free_data(pdData);
    //
} // main()
