#include <iostream>
#include <vector>
#include <cstdint>

int64_t TotalWays(int n, int k) {
    if (k == 1 || n < 3) {
        return 1;
    }

    std::vector<int64_t> memo(n + 1);

    memo[1] = 1;
    memo[2] = 1;
    memo[3] = 2;

    for (int i = 4; i < memo.size(); ++i) {
        for (int j = 1; j <= k && (i - j) >= 0; ++j) {
            memo[i] += memo[i - j];
            memo[i] %= 1'000'000'007;
        }
    }

    return memo[n];
}

int main(int argc, const char * argv[]) {
    int n, k;

    std::cin >> n >> k;

    std::cout << TotalWays(n, k) << '\n';
    return 0;
}
