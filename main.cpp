#include "/workspaces/C++/include/TRS.h"
#include <iostream>

int main() {
    Array figures;
    int choice;
    
    std::cout << "=== СИСТЕМА УПРАВЛЕНИЯ ФИГУРАМИ ===" << std::endl;
    
    do {
        std::cout << "\nМЕНЮ:" << std::endl;
        std::cout << "1. Добавить квадрат" << std::endl;
        std::cout << "2. Добавить прямоугольник" << std::endl;
        std::cout << "3. Добавить трапецию" << std::endl;
        std::cout << "4. Показать информацию о всех фигурах" << std::endl;
        std::cout << "5. Вычислить общую площадь" << std::endl;
        std::cout << "6. Удалить фигуру по индексу" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                Square* square = new Square();
                std::cout << "Введите данные квадрата:" << std::endl;
                std::cin >> *square;
                figures.push_back(square);
                std::cout << "Квадрат добавлен!" << std::endl;
                break;
            }
            case 2: {
                Rectangle* rect = new Rectangle();
                std::cout << "Введите данные прямоугольника:" << std::endl;
                std::cin >> *rect;
                figures.push_back(rect);
                std::cout << "Прямоугольник добавлен!" << std::endl;
                break;
            }
            case 3: {
                Trapezoid* trap = new Trapezoid();
                std::cout << "Введите данные трапеции:" << std::endl;
                std::cin >> *trap;
                figures.push_back(trap);
                std::cout << "Трапеция добавлена!" << std::endl;
                break;
            }
            case 4: {
                if (figures.empty()) {
                    std::cout << "Нет фигур для отображения." << std::endl;
                } else {
                    std::cout << "\n=== ИНФОРМАЦИЯ О ФИГУРАХ ===" << std::endl;
                    for (int i = 0; i < figures.getSize(); i++) {
                        std::cout << "\n--- Фигура " << i << " ---" << std::endl;
                        auto center = figures[i]->getCenter();
                        std::cout << "Геометрический центр: (" << center.first << ", " << center.second << ")" << std::endl;
                        std::cout << "Площадь: " << figures[i]->area() << std::endl;
                        std::cout << "Вершины: " << *figures[i] << std::endl;
                    }
                }
                break;
            }
            case 5: {
                if (figures.empty()) {
                    std::cout << "Нет фигур для вычисления площади." << std::endl;
                } else {
                    double total = 0;
                    for (int i = 0; i < figures.getSize(); i++) {
                        total += figures[i]->area();
                    }
                    std::cout << "Общая площадь всех фигур: " << total << std::endl;
                }
                break;
            }
            case 6: {
                if (figures.empty()) {
                    std::cout << "Нет фигур для удаления." << std::endl;
                } else {
                    int index;
                    std::cout << "Введите индекс фигуры для удаления (0-" << figures.getSize()-1 << "): ";
                    std::cin >> index;
                    if (index >= 0 && index < figures.getSize()) {
                        figures.erase(index);
                        std::cout << "Фигура удалена!" << std::endl;
                    } else {
                        std::cout << "Неверный индекс!" << std::endl;
                    }
                }
                break;
            }
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор!" << std::endl;
        }
    } while (choice != 0);
    
    return 0;
}