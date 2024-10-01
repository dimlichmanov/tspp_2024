#include <iostream>
#include <sched.h>
#include <pthread.h>
#include <chrono>

using namespace std;

int n_ret = 0;

using chrmicro = std::chrono::microseconds;

void littleSleep(int us) {
    auto tpStart =  std::chrono::system_clock::now();
    auto tpEnd = tpStart + chrmicro(us);

    int ret = 0;

    do {
        ret = sched_yield();
        n_ret++;
    }
    while (std::chrono::system_clock::now() < tpEnd);
}

void noSleep(int us) {
    auto tpStart =  std::chrono::system_clock::now();
    auto tpEnd = tpStart + chrmicro(us);

    int ret = 0;

    do {
        n_ret++;
    }
    while (std::chrono::system_clock::now() < tpEnd);
}


int main() {
    auto tpStartMeasure = std::chrono::system_clock::now();

    littleSleep(130);

    auto timeElapsed = std::chrono::system_clock::now() - tpStartMeasure; // OK

    cout << "littleSleep Elapsed time: " << timeElapsed.count() << " microseonds, yielded " << n_ret << " times" << endl;
    

    tpStartMeasure = std::chrono::system_clock::now();

    noSleep(130);

    timeElapsed = std::chrono::system_clock::now() - tpStartMeasure; // OK


    cout << "NoSleep Elapsed time: " << timeElapsed.count() << " microseonds, yielded " << n_ret << " times" << endl;
    
    
    return 0;
}