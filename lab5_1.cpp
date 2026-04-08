#include <iostream>
#include <cstdlib>   // для rand(), srand()
#include <ctime>     // для time()

// Узел односвязного списка
struct Node {
    int data;        // целое число
    Node* next;      // указатель на следующий узел
};

// Функция создания нового узла
Node* createNode(int value) {
    Node* newNode = new Node;   // выделяем память
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

void createList(Node*& head, int n, int choice) {
    head = nullptr;
    if (n <= 0) return;

    Node* tail = nullptr;   // для быстрого добавления в конец

    for (int i = 0; i < n; ++i) {
        int value;
        if (choice == 0) {          
            value = rand() % 100;    // диапазон 0..99
            std::cout << "Сгенерировано: " << value << std::endl;
        } else {                     // ручной ввод
            std::cout << "Введите элемент " << i+1 << ": ";
            std::cin >> value;
        }

        Node* newNode = createNode(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void printList(Node* head) {
    if (head == nullptr) {
        std::cout << "Список пуст." << std::endl;
        return;
    }
    std::cout << "Список: ";
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void deleteList(Node*& head) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

int countGreaterThanPrevious(Node* head) {
    if (head == nullptr) return 0;   // пустой список

    int count = 0;
    int maxSoFar = head->data;       // первый элемент - текущий максимум
    // Начинаем со второго узла, т.к. у первого нет предыдущих
    Node* current = head->next;

    while (current != nullptr) {
        if (current->data > maxSoFar) {
            ++count;
            maxSoFar = current->data;   // обновляем максимум
        }
        current = current->next;
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned>(time(nullptr))); // инициализация ГСЧ

    int n, choice;
    std::cout << "Введите количество элементов: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Некорректное количество." << std::endl;
        return 1;
    }

    std::cout << "Способ заполнения:\n0 - случайные числа\n1 - ручной ввод\nВыбор: ";
    std::cin >> choice;

    Node* myList = nullptr;

    createList(myList, n, choice);

    printList(myList);

    int result = countGreaterThanPrevious(myList);
    std::cout << "Количество элементов, больших всех предыдущих: " << result+1 << std::endl;

    deleteList(myList);
    std::cout << "Список удалён." << std::endl;

    return 0;
}