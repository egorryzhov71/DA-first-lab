#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main() {
    int pipefd[2];
    pid_t pid;
    std::string filename;
    
    std::cout << "Введите имя файла: ";
    std::cin >> filename;
    
    if (pipe(pipefd) == -1) {
        std::cerr << "Ошибка создания pipe" << std::endl;
        return 1;
    }
    
    pid = fork();
    if (pid == -1) {
        std::cerr << "Ошибка создания процесса" << std::endl;
        return 1;
    }
    
    if (pid == 0) {
       
        close(pipefd[0]); 
        
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        execl("./child", "child", filename.c_str(), NULL);
        std::cerr << "Ошибка запуска дочерней программы" << std::endl;
        return 1;
    } else {
        close(pipefd[1]);
        
        char buffer[1024];
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer)-1)) > 0) {
            buffer[bytes_read] = '\0';
            std::cout << buffer;
        }
        
        close(pipefd[0]);
        wait(NULL);
        std::cout << "Программа завершена." << std::endl;
    }
    
    return 0;
}