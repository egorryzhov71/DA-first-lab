#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <fcntl.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " <имя_файла>" << std::endl;
        return 1;
    }
    
    std::string filename = argv[1];
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return 1;
    }
    
    close(STDIN_FILENO);
    int new_stdin = open(filename.c_str(), O_RDONLY);
    if (new_stdin == -1) {
        std::cerr << "Ошибка перенаправления stdin" << std::endl;
        return 1;
    }
    
    std::string line;
    int number;
    
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        if (!(ss >> number)) {
            continue;
        }
        
        if (number < 0) {
            break;
        }
        
        if (is_prime(number)) {
            break;
        }
        
        std::cout << number << std::endl;
    }
    
    file.close();
    return 0;
}
