#include <fstream>
#include <random>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]){
    int count = std::atoi(argv[1]);

    std::default_random_engine en;
    std::uniform_int_distribution<uint32_t> dist;
    std::vector<uint32_t> datas(count);

    std::ofstream output_file("data.txt");
    for(int i = 0; i < count; ++i){
        uint32_t data = dist(en);
        output_file << data << std::endl;
        datas.push_back(data);
    }
    output_file.close();

    std::ranges::sort(datas);

    std::ofstream golden_file("expected.txt");
    for(uint32_t data : datas){
        golden_file << data << std::endl;
    }
    golden_file.close();
    return 0;
}