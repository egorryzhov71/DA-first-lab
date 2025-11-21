#include <iostream>
#include "/workspaces/C++/Lab5/include/dynamic_array.h"

int main() {
    std::cout << "=== ПРОСТАЯ ДЕМОНСТРАЦИЯ ===\n\n";
    

    MemoryResource my_memory;
    std::pmr::polymorphic_allocator<int> alloc(&my_memory);
    std::cout << "\n--- Тест с int ---\n";
    
    DynamicArray<int> numbers(3, alloc);
    
    for (int i = 1; i <= 10; i++) {
        numbers.push_back(i * 10);
    }
    
    std::cout << "Через operator[]: ";
    for (size_t i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n";
    
    std::cout << "Через итераторы: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    std::cout << "\n--- Тест со структурой ---\n";
    
    struct Student {
        int id;
        int age;
        const char* name;
        
        Student(int i = 0, int a = 0, const char* n = "") : id(i), age(a), name(n) {}
    };
    
    std::pmr::polymorphic_allocator<Student> student_alloc(&my_memory);
    DynamicArray<Student> students(2, student_alloc);
    
    students.push_back(Student(1, 20, "Иван"));
    students.push_back(Student(2, 21, "Мария"));
    students.push_back(Student(3, 19, "Петр"));

    std::cout << "Студенты:\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << "ID: " << students[i].id << ", Возраст: " << students[i].age 
                  << ", Имя: " << students[i].name << "\n";
    }
    
    std::cout << "\n--- Статистика ---\n";
    std::cout << "Размер numbers: " << numbers.size() << "\n";
    std::cout << "Емкость numbers: " << numbers.capacity() << "\n";
    std::cout << "Размер students: " << students.size() << "\n";
    std::cout << "Емкость students: " << students.capacity() << "\n";
    
    std::cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===\n";
    return 0;
}