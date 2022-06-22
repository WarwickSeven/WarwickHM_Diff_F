#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex m;

template <typename T> void pcout(const T & Info) {
    std::lock_guard<std::mutex> lg(m);
    std::cout << Info << " ";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void protContPrint(const std::vector<int> & Cont) {
    for (int i = 0; i<Cont.size(); i++) {
        pcout(Cont[i]);
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> v1 = {0,1,2,3,4};
    std::vector<int> v2 = {5,6,7,8,9};
    std::thread th1 (protContPrint, v1);
    std::thread th2 (protContPrint, v2);
    th1.join();
    th2.join();
    return 0;
}
