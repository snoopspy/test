#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <exception>

class MyException : public std::exception
{
    const char* m_what;
public:
    MyException(const char* what) { m_what = what; }
    virtual const char* what() const throw() { return m_what; }
};

void sighandler(int signum)
{
    printf("%lx sighandler signum=%d\n", pthread_self(), signum);
    throw MyException("sighandler!!!");
}

typedef struct
{
    int i;
    int j;
} divide_t;

void divide(divide_t* t)
{
    int k = t->i / t->j;
    printf("%lx %d / %d = %d\n", pthread_self(), t->i, t->j, k);
}

void* thread_func(void* p)
{
    divide_t* t = (divide_t*)p;

    printf("%lx beg thread\n", pthread_self());
    try {
        divide(t);
    } catch (const std::exception& e)
    {
        const char* what = e.what();
        printf("%lx std::exception %s\n", pthread_self(), what);
    } catch (...)
    {
        printf("%lx ... exception\n", pthread_self());
    }
    printf("%lx end thread\n", pthread_self());
    return NULL;
}

static const int THREAD_CNT = 2;
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    divide_t t[THREAD_CNT];
    for (int i = 0; i < THREAD_CNT; i++)
    {
        scanf("%d %d", &t[i].i, &t[i].j);
    }

    signal(SIGFPE, sighandler);

    pthread_t thread[THREAD_CNT];
    for (int i = 0; i < THREAD_CNT; i++)
    {
        pthread_create(&thread[i], NULL, thread_func, &t[i]);
    }

    for (int i = 0; i < THREAD_CNT; i++)
    {
        pthread_join(thread[i], NULL);
    }

    return 0;
}
