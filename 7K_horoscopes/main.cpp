#include <iostream>
#include <utility>
#include <algorithm>
#include <deque>
#include <vector>

std::pair<std::deque<int>, std::deque<int>> ReadInput(std::istream& input_stream) {
    int size_of_first_vector;
    
    input_stream >> size_of_first_vector;
    
    std::deque<int> first_vector;
    
    for (int i = 0; i < size_of_first_vector; ++i) {
        input_stream >> first_vector.emplace_back();
    }
    
    int size_of_second_vector;
    
    input_stream >> size_of_second_vector;
    
    std::deque<int> second_vector;
    
    for (int i = 0; i < size_of_second_vector; ++i) {
        input_stream >> second_vector.emplace_back();
    }
    
    return {std::move(first_vector), std::move(second_vector)};
}

template<typename Container>
void PrintContainer(Container container) {
    for (auto element : container) {
        std::cout << element << ' ';
    }
    
    if (!container.empty()) {
        std::cout << '\n';
    }
}

int main(int argc, const char * argv[]) {
    auto [first_sequence, second_sequence] = ReadInput(std::cin);
    
    // dp contains sizes of both arrays that is why size is +1 so size can be from 0 to the size which includes every element
    std::vector<std::vector<int>> dp(first_sequence.size() + 1, std::vector<int>(second_sequence.size() + 1));
    
    for (int first_sequence_size = 1; first_sequence_size <= first_sequence.size(); ++first_sequence_size) {
        for (int second_sequence_size = 1; second_sequence_size <= second_sequence.size(); ++second_sequence_size) {
            if (first_sequence[first_sequence_size - 1] == second_sequence[second_sequence_size - 1]) {
                dp[first_sequence_size][second_sequence_size] = dp[first_sequence_size - 1][second_sequence_size - 1] + 1;
                
            } else {
                dp[first_sequence_size][second_sequence_size] = std::max(dp[first_sequence_size - 1][second_sequence_size], dp[first_sequence_size][second_sequence_size - 1]);
            }
        }
    }
    
    std::cout << dp.back().back() << '\n';
    
    std::deque<int> common_elements_of_first_vector;
    
    std::deque<int> common_elements_of_second_vector;
    
    while (dp[first_sequence.size()][second_sequence.size()] != 0) {
        if (first_sequence.back() == second_sequence.back()) {
            common_elements_of_first_vector.push_front(static_cast<int>(first_sequence.size()));
            common_elements_of_second_vector.push_front(static_cast<int>(second_sequence.size()));
            
            first_sequence.pop_back();
            second_sequence.pop_back();
        } else {
            if (dp[first_sequence.size()][second_sequence.size()] == dp[first_sequence.size() - 1][second_sequence.size()]) {
                first_sequence.pop_back();
            } else {
                second_sequence.pop_back();
            }
        }
    }
    
    PrintContainer(common_elements_of_first_vector);
    PrintContainer(common_elements_of_second_vector);
    
    return 0;
}
