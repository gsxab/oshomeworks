#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t full, empty;
const int MAX = 10;
int inventory = 0;
int flag = 50;

void* produce(void*) {
    int inv;
    while (flag) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        inventory ++;
        std::printf("Producer produces: 1 (%2d)\n", inventory);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* consume(void*) {
    int inv;
    while(flag) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if (flag) flag --;
        inventory --;
        std::printf("Consumer consumes: 1 (%2d)\n", inventory);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    std::srand((unsigned)std::time(NULL));
    pthread_t thr1, thr2, thr3, thr4, thr5;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 10);
    pthread_create(&thr1, NULL, produce, NULL);
    pthread_create(&thr4, NULL, produce, NULL);
    pthread_create(&thr5, NULL, produce, NULL);
    pthread_create(&thr2, NULL, consume, NULL);
    pthread_create(&thr3, NULL, consume, NULL);
    usleep(10000);
    return 0;
}

