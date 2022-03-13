#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int main() {
    int n_days;

    std::cin >> n_days;

    std::vector<int> prices(n_days);

    for (int i = 0; i < n_days; ++i) {
        std::cin >> prices[i];
    }

    std::vector<int> positions_of_price_decreases;

    for (int i = 1; i < prices.size(); ++i) {
        if (prices[i] < prices[i - 1]) {
            positions_of_price_decreases.push_back(i - 1);
        }
    }
    
    positions_of_price_decreases.push_back(static_cast<int>(prices.size()) - 1);

    int prev_position = 0;

    auto prices_begin = prices.begin();

    int output{};

    for (int index_of_price_before_decrease : positions_of_price_decreases) {
        std::sort(prices_begin + prev_position, prices_begin + index_of_price_before_decrease);
        
        output += prices[index_of_price_before_decrease] - prices[prev_position];
        
        prev_position = index_of_price_before_decrease + 1;
    }
    
    std::cout << output;

    return 0;
}
