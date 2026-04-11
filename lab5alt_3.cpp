#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <climits>

using namespace std;

// Структура узла двусвязного списка
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Создание списка из текстового файла
Node* createListFromFile(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл '" << filename << "'\n";
        return nullptr;
    }
    Node* head = nullptr;
    Node* tail = nullptr;
    int value;
    while (file >> value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    file.close();
    return head;
}

// Вывод списка на экран
void printList(Node* head) {
    if (!head) {
        cout << "Список пуст.\n";
        return;
    }
    cout << "Список: ";
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Проверка, является ли число двузначным (свойство Q)
bool isTwoDigit(int n) {
    int absN = abs(n);
    return absN >= 10 && absN <= 99;
}

// Удаление всех элементов, обладающих свойством Q (двузначные)
void deleteQ(Node** head) {
    if (!*head) return;
    Node* current = *head;
    while (current) {
        Node* nextNode = current->next;
        if (isTwoDigit(current->data)) {
            // Удаляем текущий узел
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                *head = current->next; // удаляем голову
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            delete current;
        }
        current = nextNode;
    }
}

// Проверка, является ли число чётным (свойство R)
bool isEven(int n) {
    return n % 2 == 0;
}

// Дублирование всех элементов, обладающих свойством R (чётные)
void duplicateR(Node** head) {
    if (!*head) return;
    Node* current = *head;
    while (current) {
        Node* nextNode = current->next;
        if (isEven(current->data)) {
            // Создаём копию
            Node* duplicate = new Node(current->data);
            // Вставляем после current
            duplicate->prev = current;
            duplicate->next = current->next;
            if (current->next) {
                current->next->prev = duplicate;
            }
            current->next = duplicate;
            // Переходим к узлу после дубликата, чтобы не дублировать его
            current = duplicate->next;
        } else {
            current = nextNode;
        }
    }
}

// Проверка, содержит ли число цифру 7 (вспомогательная для T)
bool containsDigit7(int n) {
    int absN = abs(n);
    if (absN == 0) return false;
    while (absN > 0) {
        if (absN % 10 == 7) return true;
        absN /= 10;
    }
    return false;
}

// Проверка, что число не содержит цифру 7 (свойство T)
bool noDigit7(int n) {
    return !containsDigit7(n);
}

// Упорядочивание (сортировка по возрастанию) элементов, обладающих свойством T
void sortT(Node* head) {
    if (!head) return;
    // Собрать значения элементов, удовлетворяющих T
    vector<int> values;
    Node* current = head;
    while (current) {
        if (noDigit7(current->data)) {
            values.push_back(current->data);
        }
        current = current->next;
    }
    // Сортировка по возрастанию
    sort(values.begin(), values.end());
    // Записать отсортированные значения обратно в узлы (в порядке следования)
    current = head;
    size_t idx = 0;
    while (current && idx < values.size()) {
        if (noDigit7(current->data)) {
            current->data = values[idx];
            ++idx;
        }
        current = current->next;
    }
}

// Удаление всего списка
void deleteList(Node** head) {
    Node* current = *head;
    while (current) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    *head = nullptr;
}

int main() {
    setlocale(LC_ALL, "Russian");

    char filename[256];
    cout << "Введите имя файла с целыми числами: ";
    cin >> filename;

    Node* list = createListFromFile(filename);
    if (!list) {
        cerr << "Не удалось создать список (файл пуст или не существует).\n";
        return 1;
    }

    cout << "\n=== Исходный список ===" << endl;
    printList(list);

    // 1. Удаление двузначных чисел (Q)
    cout << "\n=== Удаление элементов, обладающих свойством Q (двузначные) ===" << endl;
    deleteQ(&list);
    printList(list);

    // 2. Дублирование чётных чисел (R)
    cout << "\n=== Дублирование элементов, обладающих свойством R (чётные) ===" << endl;
    duplicateR(&list);
    printList(list);

    // 3. Сортировка элементов, не содержащих цифру 7 (T)
    cout << "\n=== Упорядочивание элементов, обладающих свойством T (без цифры 7) ===" << endl;
    sortT(list);
    printList(list);

    // 4. Удаление всего списка
    deleteList(&list);
    cout << "\nПамять освобождена. Программа завершена." << endl;

    return 0;
}