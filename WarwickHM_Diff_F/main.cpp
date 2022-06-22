#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

//глобальные переменные это плохо
int prog = 0;
int result = 0;

void findPN(const int &numPN) {
    std::vector<int> PNs;
    PNs.reserve(numPN);
    PNs.push_back(2);
    int n = 3;
    bool isPrime;
    for (int k = 1; k < numPN; k++) {
        isPrime = true;
        for (int i = 2; i < n; i++) {
                if (n % i == 0) {
                    isPrime = false;
                    k--;
                    break;
                }
        }
        if (isPrime == true) {
            PNs.push_back(n);
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); //замедлитель вычислений
            prog = static_cast<int>((PNs.size()*100)/PNs.capacity());
        }
        n++;
    }
    result = PNs[PNs.size()-1];
}

int main() {
    std::cout << "Enter the № of the prime number ( > 3 ): ";
    int numPN;
    std::cin >> numPN;
    std::thread th1(findPN, numPN);
    th1.detach();
    while (prog < 100) {
        std::cout << prog << "%" <<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //замедлитель отображения
    }
    if (prog == 100) {
        std::cout << "Complete! " << numPN <<" Primal number is: " << result << std::endl;
    }
    return 0;
}
