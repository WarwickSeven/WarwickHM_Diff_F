#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>

int32_t getRandomNum(const int32_t min, const int32_t max) {
    const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}

class OwnerThief {
    int m_slots;
    std::vector<int> home;
public:
    OwnerThief(const int &slots) : m_slots(slots) {
        home.reserve(slots);
    }
    void ownerWork() {
        while (home.size() < home.capacity()) {
        home.push_back(getRandomNum(1, 100));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    void thiefWork() {
        while (home.size() < home.capacity()) {
            if (home.empty()) {
            std::this_thread::sleep_for(std::chrono::seconds(10)); //дать фору если в доме пусто
            }
            home.erase(max_element(home.begin(), home.end()));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    int getSize() {
        return static_cast<int>(home.size());
    }
    void printHome() {
        std::cout << "Home: " << home.size() << "/" << home.capacity() << " - ";
        for (auto i : home) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int houseSize = 15;
    OwnerThief ot1(houseSize);
    std::thread th1(&OwnerThief::ownerWork, &ot1);
    std::thread th2(&OwnerThief::thiefWork, &ot1);
    th1.detach();
    th2.detach();
    while (ot1.getSize() < houseSize) {
        ot1.printHome();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
 }
