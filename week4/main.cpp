#include <cstdio>
#include <cstdint>
#include <chrono>

#pragma STDC FENV_ACCESS ON

static inline double calculate_fast(uint64_t iterations, double p1, double p2) {
    double result = 1.0;
    double j1 = p1 - p2;  // for i = 1
    double j2 = p1 + p2;

    const uint64_t blocks = iterations / 16;
    const uint64_t rem = iterations % 16;

    #pragma clang fp reassociate(off)
    #pragma clang fp contract(off)
    #pragma clang loop vectorize(disable)
    for (uint64_t b = 0; b < blocks; ++b) {
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
        result -= 1.0 / j1; result += 1.0 / j2; j1 += p1; j2 += p1;
    }

    #pragma clang fp reassociate(off)
    #pragma clang fp contract(off)
    #pragma clang loop vectorize(disable)
    for (uint64_t r = 0; r < rem; ++r) {
        result -= 1.0 / j1;
        result += 1.0 / j2;
        j1 += p1;
        j2 += p1;
    }

    return result;
}

int main() {
    using clock = std::chrono::steady_clock;
    auto start_time = clock::now();

    double result = calculate_fast(200000000ULL, 4.0, 1.0) * 4.0;

    auto end_time = clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::printf("Result: %.12f\n", result);
    std::printf("Execution Time: %.6f seconds\n", elapsed.count());
    return 0;
}