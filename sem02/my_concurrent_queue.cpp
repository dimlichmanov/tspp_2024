#include "pthread.h"
#include <queue>
#include <cassert>

class MyConcurrentQueue {

public:
    void reserve (int n) {
        queue_limit = n;
    }

    void put (int value) {
        // реализация логики с записью значения
    }

    int get() {
        // реализация логики с чтением значения  
    }

private:
    int queue_limit;
    std::queue<int> queue;
    
    // ?
};


MyConcurrentQueue my_queue;


void* producer_func (void* params) {

    for (int i = 0; i < 100000; i++) {
        my_queue.put(0); //для реальных тестов нужно что-то хитрее нуля
    }

    return NULL;

}

void *consumer_func(void *params) {
    for (int i = 0; i < 100000; i++) {
        int a = my_queue.get();
        assert(a == 0);
    }

    return NULL;

}


int main () {

    my_queue.reserve(100); 

    // Базовый тест {1 - 1}

    pthread_t thread_producer;
    pthread_t thread_consumer;

    pthread_create(&thread_producer, NULL, &producer_func, NULL); 
    pthread_create(&thread_consumer, NULL, &producer_func, NULL); 

    pthread_join(thread_producer, NULL);
    pthread_join(thread_consumer, NULL);    

    // Добавьте свои тесты
}