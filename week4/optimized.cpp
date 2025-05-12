#include <iostream>
#include <vector>
#include <chrono>
#include <limits>

class LCG {
public:
    LCG(unsigned long seed, unsigned long a = 1664525, unsigned long c = 1013904223, unsigned long m = 1ULL << 32)
        : value(seed), a(a), c(c), m(m) {}

    unsigned long next() {
        value = (a * value + c) % m;
        return value;
    }

private:
    unsigned long value, a, c, m;
};

long long max_subarray_sum(int n, unsigned long seed, int min_val, int max_val) {
    LCG lcg(seed);
    std::vector<int> random_numbers(n);
    for (int i = 0; i < n; ++i) {
        random_numbers[i] = lcg.next() % (max_val - min_val + 1) + min_val;
    }

    long long max_sum = std::numeric_limits<long long>::min();
    for (int i = 0; i < n; ++i) {
        long long current_sum = 0;
        for (int j = i; j < n; ++j) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
}

long long total_max_subarray_sum(int n, unsigned long initial_seed, int min_val, int max_val) {
    long long total_sum = 0;
    LCG lcg(initial_seed);
    for (int i = 0; i < 20; ++i) {
        unsigned long seed = lcg.next();
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    // Parameters
    int n = 10000;              // Number of random numbers
    unsigned long initial_seed = 42; // Initial seed for the LCG
    int min_val = -10;         // Minimum value of random numbers
    int max_val = 10;          // Maximum value of random numbers

    auto start_time = std::chrono::high_resolution_clock::now();
    long long result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
