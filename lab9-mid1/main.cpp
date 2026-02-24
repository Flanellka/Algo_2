#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

// Структура для описания товара
struct Product {
    std::string name;
    double cost;          
    double price;         
    int warehouse_days;   
    double return_rate;   
    int quantity_in_stock;
};

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian");
    // Настройка параметров
    // Стартовый капитал 
    double cash = 10000.0;

    // Определяем наши товары
    std::vector<Product> products = {
        {"Ежедневник", 150.0, 400.0, 10, 0.15, 0},
        {"Зубная нить", 50.0, 150.0, 20, 0.01, 0},
        {"Носки",       30.0, 100.0, 5,  0.05, 0}
    };

    std::cout << "Расчет прибыли ИП" << std::endl;
    std::cout << "Стартовый капитал: " << cash << " руб." << std::endl << std::endl;

    // Цикл по месяцам
    for (int month = 1; month <= 12; ++month) {

        // Выбор лучшего товара
        int best_product_index = -1;
        double max_roi = -1.0;

        for (int i = 0; i < products.size(); ++i) {
            double expected_revenue = products[i].price * (1.0 - products[i].return_rate);
            double roi = (expected_revenue - products[i].cost) / products[i].cost;

            if (roi > max_roi) {
                max_roi = roi;
                best_product_index = i;
            }
        }

        // Закупка
        Product& best = products[best_product_index];

        int can_buy = (int)(cash / best.cost);

        cash -= can_buy * best.cost;

        best.quantity_in_stock += can_buy;

        // Продажа и возвраты
        int total_items = best.quantity_in_stock;

        int returns = (int)std::ceil(total_items * best.return_rate);
        int sold = total_items - returns;

        double revenue = sold * best.price;
        cash += revenue;

        best.quantity_in_stock = returns;

        // Обнуляем стоки остальных товаров
        for (int i = 0; i < products.size(); ++i) {
            if (i != best_product_index) products[i].quantity_in_stock = 0;
        }

        // Вывод результатов
        if (month == 3 || month == 6 || month == 12) {
            std::cout << "Месяц " << month << ":" << std::endl;
            std::cout << "  Выбранная стратегия: " << best.name << std::endl;
            std::cout << "  Было продано: " << sold << " шт." << std::endl;
            std::cout << "  Вернулось на склад: " << returns << " шт." << std::endl;
            std::cout << "  Текущий капитал: " << std::fixed << std::setprecision(2) << cash << " руб." << std::endl;
        }
    }

    return 0;
}
