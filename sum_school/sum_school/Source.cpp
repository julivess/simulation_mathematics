#pragma once
#include <algorithm>
#include <math.h>
#include <iostream>
#include <vector>
#include <random>

typedef std::pair<double, double> dd;
const long double EulMas = 0.577215664901532860606;

double F(int n, int NumTr) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, n-1); 

    int ans = 0;

    for (int tr = 0; tr < NumTr; tr++) {
        std::vector<bool> was(n, false);
        int UnCol = 0;
        int operation = 0;

        while (UnCol < n) {
            int color = dis(gen);
            if (!was[color]) ++UnCol;

            was[color] = true;

            ++operation;
        }
        ans += operation;
    }

    double quantity = static_cast<double>(ans) / NumTr;
    return quantity;
}

long double MomentsMethod(long long n) {
    long double result = 0;
    for (long long i = 1; i <= n; i++) {
        result += 1.0 / i;
    }
    return result * n;
}

long double AsymptoticApproximation(long long N) {
    long double result = (log(N) + EulMas) * N;
    return result;
}

dd lineSegment(int n, int NumTr, int len) {
    
    std::vector<double> trials(len + 1);
    for (int i = 0; i <= len; i++) {
        trials[i] = F(n, NumTr);
    }

    auto L = std::min_element(trials.begin(), trials.end());
    auto R = std::max_element(trials.begin(), trials.end());
    dd res = { *L, *R };
    return res;
}

int main() {
   

    long long n = 5;
    std::cout << "Evaluation f(" << n << ") for N <= 10: " << F(n, 1000) << std::endl;

    n = 100;
    std::cout << "Evaluation f(" << n << ") for 10 < N < 1000: " << MomentsMethod(n) << std::endl;

    n = 500;
    std::cout << "Evaluation f(" << n << ") for 10 < N < 1000: " << MomentsMethod(n) << std::endl;


    n = 100000;
    std::cout << "Evaluation f(" << n << ") for 1000 < N < 10^6: " << MomentsMethod(n) << std::endl;

    
    n = 1000000000; 
    std::cout << "Evaluation f(" << n << ") for 10^6 < N < 10^18: " << AsymptoticApproximation(n) << std::endl;

  
    n = 1e18;
    std::cout << "Evaluation f(" << n << ") for 10^6 < N < 10^18: " << AsymptoticApproximation(n) << std::endl;

    dd interval = lineSegment(100, 1000, 7);
    std::cout << "N = 100, hit interval [L, R]: [" << interval.first << ", " << interval.second << "]" << std::endl;

}
