#include <iostream>
#include <deque>
#include <utility>
#include <cstdint>
#include <algorithm>

using Value = uint64_t;
using Quantity = uint64_t;

int main() {
    int backpack_capacity;
    
    std::cin >> backpack_capacity;
    
    uint64_t n_gold_piles;
    
    std::cin >> n_gold_piles;
    
    std::deque<std::pair<Value, Quantity>> piles;
    
    for (uint64_t i = 0; i < n_gold_piles; ++i) {
        auto& pile = piles.emplace_back();
        
        std::cin >> pile.first >> pile.second;
    }
    
    std::sort(piles.begin(), piles.end());
    
    uint64_t output{};
    
    while (backpack_capacity > 0) {
        if (piles.empty()) {
            break;
        }
        
        auto [value, quantity] = piles.back();
        piles.pop_back();
        
        if (quantity < backpack_capacity) {
            backpack_capacity -= quantity;
            
            output += quantity * value;
            
            continue;
        } else {
            output += backpack_capacity * value;
            
            break;
        }
    }
    
    std::cout << output << '\n';
    
    return 0;
}
