#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ClanSystem {
private:
    // Родительский элемент для каждого пользователя
    vector<int> parent;
    // Размер (ранг) клана для оптимизации объединения
    vector<int> rank;
    // Количество пользователей в системе
    int userCount;

public:
    // Конструктор: создаем систему для n пользователей
    ClanSystem(int n) : userCount(n) {
        parent.resize(n);
        rank.resize(n, 1); // Изначально каждый клан имеет размер 1

        // Изначально каждый пользователь - свой собственный клан
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Каждый пользователь - родитель сам себе
        }
    }

    // Основная операция: найти корень клана для пользователя
    // (определяет, к какому клану принадлежит пользователь)
    int find(int user) {
        // Если пользователь - родитель сам себе, это корень клана
        if (parent[user] == user) {
            return user;
        }
        // Рекурсивно ищем корень с применением сжатия пути
        // (это оптимизация для ускорения будущих запросов)
        return parent[user] = find(parent[user]);
    }

    // Объединение двух кланов (пользователи будут в одном клане)
    void unite(int user1, int user2) {
        int root1 = find(user1);
        int root2 = find(user2);

        // Если пользователи уже в одном клане, ничего не делаем
        if (root1 == root2) {
            cout << "Пользователи " << user1 << " и " << user2
                << " уже в одном клане!" << endl;
            return;
        }

        // Объединение с оптимизацией по рангу
        // Присоединяем меньший клан к большему
        if (rank[root1] < rank[root2]) {
            parent[root1] = root2;
            rank[root2] += rank[root1];
        }
        else {
            parent[root2] = root1;
            rank[root1] += rank[root2];
        }

        cout << "Кланы пользователей " << user1 << " и " << user2
            << " объединены" << endl;
    }

    // Проверка, находятся ли два пользователя в одном клане
    bool areInSameClan(int user1, int user2) {
        bool result = (find(user1) == find(user2));
        cout << "Пользователи " << user1 << " и " << user2
            << (result ? " в одном клане" : " в разных кланах") << endl;
        return result;
    }

    // Получение информации о клане пользователя
    int getClan(int user) {
        int clanId = find(user);
        cout << "Пользователь " << user << " находится в клане " << clanId << endl;
        return clanId;
    }

    // Удаление клана (разделение на отдельные кланы)
    void deleteClan(int user) {
        int clanRoot = find(user);

        // Находим всех пользователей в этом клане
        unordered_set<int> clanMembers;
        for (int i = 0; i < userCount; i++) {
            if (find(i) == clanRoot) {
                clanMembers.insert(i);
            }
        }

        // Каждого пользователя делаем отдельным кланом
        for (int member : clanMembers) {
            parent[member] = member;
            rank[member] = 1;
        }

        cout << "Клан пользователя " << user << " распущен. "
            << clanMembers.size() << " пользователей теперь в отдельных кланах." << endl;
    }

    // Вспомогательная функция для вывода текущего состояния
    void printStatus() {
        cout << "\nТекущее состояние кланов:" << endl;
        unordered_map<int, vector<int>> clans;

        // Группируем пользователей по кланам
        for (int i = 0; i < userCount; i++) {
            int clanId = find(i);
            clans[clanId].push_back(i);
        }

        // Выводим информацию о каждом клане
        for (auto& clan : clans) {
            cout << "Клан " << clan.first << " (размер: " << clan.second.size() << "): ";
            for (int user : clan.second) {
                cout << user << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian");

    // Создаем систему для 6 пользователей 
    ClanSystem clans(6);

    clans.printStatus();

    // Объединяем некоторые кланы
    cout << "Объединение кланов:" << endl;
    clans.unite(0, 1);
    clans.unite(1, 2);
    clans.unite(3, 4);
    clans.printStatus();

    // Проверяем, в одном ли клане пользователи
    cout << "Проверка принадлежности к кланам:" << endl;
    clans.areInSameClan(0, 2);  // true
    clans.areInSameClan(0, 3);  // false

    // Получаем информацию о клане пользователя
    cout << "\nПоиск клана:" << endl;
    clans.getClan(4);

    // Удаляем клан
    cout << "\nУдаление клана:" << endl;
    clans.deleteClan(0);
    clans.printStatus();

    return 0;
}
