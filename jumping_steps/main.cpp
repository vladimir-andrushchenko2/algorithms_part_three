#include <iostream>

int totalWays(int n, int m) {
    // base case: invalid input
    if (n <= 0) {
        return 0;
    }

    // base case: 1 way (with no steps)
    if (n == 1) {
        return 1;
    }

    int count = 0;

    for (int i = 1; i <= m; i++) {
        count += totalWays(n - i, m);
    }

    return count;
}

int main(int argc, const char * argv[]) {
    int n, k;

    std::cin >> n >> k;

    std::cout << totalWays(n, k) << '\n';
    return 0;
}
