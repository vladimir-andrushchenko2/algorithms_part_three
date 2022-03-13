#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <tuple>

int main(int argc, const char * argv[]) {
    int n;
    
    std::cin >> n;
    
    std::vector<std::pair<double, double>> classes;
    
    double start, end;
    
    for (int i = 0; i < n; ++i) {
        std::cin >> start >> end;
        
        classes.push_back({start, end});
    }
    
    std::sort(classes.begin(), classes.end(), [](auto left, auto right){
        return std::tuple{left.second, left.first} < std::tuple{right.second, right.first};
    });
    
    std::vector<std::pair<double, double>> output_schedule;
    
    double last_class_end_time{};
    
    for (auto [start, end] : classes) {
        if (last_class_end_time <= start) {
            output_schedule.push_back({start, end});
            last_class_end_time = end;
        }
    }
    
    std::cout << output_schedule.size() << '\n';
    
    for (auto [start, end] : output_schedule) {
        std::cout << start << ' ' << end << '\n';
    }
    
    return 0;
}
