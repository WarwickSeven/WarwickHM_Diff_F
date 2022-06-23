#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

class PrimeNumber {
    int m_last;                         //номер искомого числа
    int m_cur;                          //текущее простое число
    int m_result;                       //n-ное простое число
    int m_prog;                         //текущий прогресс в %
    std::vector<int> m_vec;             //вектор найденных простых чисел
    std::vector<char> v_prog;           //вектор шкалы прогресса
public:
    PrimeNumber(const int &last) : m_last(last) {
        v_prog.resize(10);
        for (int i = 0; i < 10; i++)
            v_prog[i] = '_';
    }
    bool isPrime(const int & x) {
        if (x%2 == 0) {
            return false;
        } else {
            for (int i = 3; i < x; i+=2) {
                if (x % i == 0) {
                    return false;
                }
            }
        }
        return true;
    }
    int searchPM() {
        m_vec.reserve(m_last);
        m_vec.push_back(2);
        m_cur = 3;
        for (int k = 1; k < m_last; k++) {
            if (isPrime(m_cur)) {
                m_vec.push_back(m_cur);
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); //замедление вычислений
                m_prog = static_cast<int>((m_vec.size()*100)/m_vec.capacity());
            } else {
                k--;
            }
            m_cur++;
        }
        m_result = m_vec[m_vec.size()-1];
        return m_result;
    }
    int getProg() {
        return m_prog;
    }
    int getResult() {
        return m_result;
    }
    void printProgress() {
        for (int i = 1; (i*10) <= m_prog; i++ ) {
            if ((i*10) <= m_prog)
                v_prog[i-1] = 'X';
        }
        for (auto j : v_prog) {
            std::cout << j;
        }
        std::cout << "  " << m_prog << "%" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //замедление отображения
    }
};

int main() {
    int numPN = 0;
    while (numPN <= 1) {
        std::cout << "Enter the № of the prime number ( > 1 ): ";
        std::cin >> numPN;
    }
    PrimeNumber pn1(numPN);
    std::thread th1(&PrimeNumber::searchPM, &pn1);
    th1.detach();
    while (pn1.getProg() < 100) {
        pn1.printProgress();
    }
    if (pn1.getProg() == 100) {
        std::cout << "Complete! " << numPN << " Primal number is: " << pn1.getResult() << std::endl;
    }
    return 0;
}
