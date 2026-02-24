#include "index.cpp"
#include <iostream>
#include <sstream>
#include <string>

/**
 * - Считываем строку с консоли (пр preorder формату с #).
 * - Парсим дерево.
 * - Проверяем корректность (isValid()).
 * - Если некорректно, выводим сообщение об ошибке.
 * - Иначе печатаем все требуемые характеристики:
 *    1) Общее количество узлов
 *    2) Минимальный ID
 *    3) Максимальный ID
 *    4) Высота дерева
 *    5) Количество листьев
 */
int main()

{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string inputLine;
    std::getline(std::cin, inputLine);

    // Парсим строку
    std::istringstream iss(inputLine);
    CompositeIndex index;

    try
    {
        index.parseIndex(iss);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка при разборе входных данных: " << e.what() << "\n";
        return 1;
    }

    // Проверяем корректность структуры (BST)
    if (!index.isValid())
    {
        std::cout << "Неверное бинарное дерево!\n";
        return 1;
    }

    // Выводим результаты
    std::cout << "Общее количество узлов: " << index.totalNodes() << "\n";
    std::cout << "Минимальный ID: " << index.minID() << "\n";
    std::cout << "Максимальный ID: " << index.maxID() << "\n";
    std::cout << "Высота дерева: " << index.height() << "\n";
    std::cout << "Количество листьев: " << index.leaves() << "\n";

    return 0;
}
