pthread_mutex_t g_Mutex = PTHREAD_MUTEX_INITIALIZER;
void *MyThreadProc(void *pvData)
{
int n = 2;
// ...
pthread_mutex_lock(&g_Mutex);
g_Numbers.push_front(n);
pthread_mutex_unlock(&g_Mutex);
// ...
return 0;
}

int main()
{
pthread_t hThread;
int nRet = pthread_create(
&hThread, NULL, MyThreadProc, NULL);
// ...
pthread_mutex_lock(&g_Mutex);
print(g_Numbers);
pthread_mutex_unlock(&g_Mutex);
// ...
pthread_join(hThread, NULL);
pthread_mutex_destroy(&g_Mutex);
}