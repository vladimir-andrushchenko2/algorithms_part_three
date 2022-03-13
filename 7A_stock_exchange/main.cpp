#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int main() {
    int n_days;

    std::cin >> n_days;

    std::vector<int> prices(n_days);

    for (int& price : prices) {
        std::cin >> price;
    }

    std::vector<int> positions_of_price_decreases;

    for (int i = 1; i < prices.size(); ++i) {
        if (prices[i] < prices[i - 1]) {
            positions_of_price_decreases.push_back(i - 1);
        }
    }

    int prev_position = 0;

    auto prices_begin = prices.begin();

    int output{};

    for (int index_of_price_before_decrease : positions_of_price_decreases) {
        std::sort(prices_begin + prev_position, prices_begin + index_of_price_before_decrease);

    }

    return 0;
}
