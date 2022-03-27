#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> GetChanges(std::vector<int> values) {
    assert(values.size() > 1);
    
    std::vector<int> output(values.size() - 1);
    
    for (int i = 0; i < output.size(); ++i) {
        output[i] = values.at(i + 1) - values.at(i);
    }
    
    return output;
}

std::vector<int> ReadArray(std::istream& input_stream, int n_values) {
    assert(n_values > 0);
    
    std::vector<int> output;
    output.reserve(n_values);
    
    int value;
    while (n_values--) {
        std::cin >> value;
        output.push_back(value);
    }
    
    return output;
}

int Find(const std::vector<int>& values, const std::vector<int>& pattern, int start) {
    
}

int main(int argc, const char * argv[]) {
    assert(false);

    return 0;
}
