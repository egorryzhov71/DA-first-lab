#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>



struct Item{
    double key;
    std::string value;
};



void bucketSort(std::vector<Item>& data){
    int n = data.size();
    if (n <= 1) return;

    std::vector<std::vector<Item>> buckets(n);

    double min_range = -100;
    double max_range = 100;
    double range =  max_range - min_range;

    for (const auto& item: data ) {
        int bucketIndex = static_cast<int>((item.key - min_range) / range * (n - 1));
        if (bucketIndex < 0) bucketIndex = 0;
        if (bucketIndex >= n) bucketIndex = n - 1;

        buckets[bucketIndex].push_back(item);
    }


    data.clear();

    for (int i = 0; i < n; i++){
        std::stable_sort(buckets[i].begin(), buckets[i].end(), [](const Item &a, const Item &b){
            return a.key - b.key;
        });

        for(const auto& item : buckets[i]){
            data.push_back(item);
        }
    }
}


int main(){

    std::vector<Item> items;
    double k;
    std::string v;

    while (std::cin >> k){
        std::getline(std::cin>> std::ws, v);
        items.push_back({k, v});
    }

    bucketSort(items);

    for (const auto& item : items){
        std::cout << item.key << "\t" << item.value << "\n";
    }
}