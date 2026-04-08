#include <iostream>
#include <fstream>
#include <cstdlib>   // для abs

// Узел двусвязного списка
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// 1. Создание списка из файла
void createListFromFile(Node*& head, Node*& tail, const char* filename) {
    head = nullptr;
    tail = nullptr;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла " << filename << std::endl;
        return;
    }
    int value;
    while (file >> value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    file.close();
}

// 2. Вывод списка на экран
void printList(Node* head) {
    if (head == nullptr) {
        std::cout << "Список пуст." << std::endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Свойство Q: число является двузначным (|n| от 10 до 99)
bool isTwoDigit(int n) {
    int absN = std::abs(n);
    return absN >= 10 && absN <= 99;
}

// 3. Удаление всех элементов, обладающих свойством Q
void deleteElementsWithQ(Node*& head, Node*& tail) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        if (isTwoDigit(current->data)) {
            // Удаляем текущий узел
            if (current->prev != nullptr)
                current->prev->next = current->next;
            else
                head = current->next;   // удаляем голову
            
            if (current->next != nullptr)
                current->next->prev = current->prev;
            else
                tail = current->prev;   // удаляем хвост
            
            delete current;
        }
        current = nextNode;
    }
}

// Свойство R: число четное
bool isEven(int n) {
    return n % 2 == 0;
}

// 4. Дублирование всех элементов, обладающих свойством R
void duplicateElementsWithR(Node*& head, Node*& tail) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        if (isEven(current->data)) {
            // Создаём копию узла
            Node* duplicate = new Node(current->data);
            // Вставляем после current
            duplicate->prev = current;
            duplicate->next = current->next;
            if (current->next != nullptr)
                current->next->prev = duplicate;
            else
                tail = duplicate;
            current->next = duplicate;
            // Переходим к следующему оригинальному узлу (пропускаем дубликат)
            current = nextNode;
        } else {
            current = nextNode;
        }
    }
}

// Свойство T: число не содержит в своей записи цифру 7 (по модулю)
bool hasNoDigit7(int n) {
    int absN = std::abs(n);
    if (absN == 0) return true;   // 0 не содержит 7
    while (absN > 0) {
        if (absN % 10 == 7) return false;
        absN /= 10;
    }
    return true;
}

// 5. Упорядочивание элементов с T, остальные остаются на местах
void sortElementsWithT(Node* head) {
    // 1. Подсчёт количества элементов с T
    int countT = 0;
    Node* current = head;
    while (current != nullptr) {
        if (hasNoDigit7(current->data)) countT++;
        current = current->next;
    }
    if (countT <= 1) return; // нечего сортировать

    // 2. Выделяем массив указателей на узлы с T
    Node** tNodes = new Node*[countT];
    int idx = 0;
    current = head;
    while (current != nullptr) {
        if (hasNoDigit7(current->data)) {
            tNodes[idx++] = current;
        }
        current = current->next;
    }

    // 3. Извлекаем значения и сортируем их (пузырьком для простоты)
    int* values = new int[countT];
    for (int i = 0; i < countT; ++i) {
        values[i] = tNodes[i]->data;
    }
    // Сортировка вставками по возрастанию
    for (int i = 1; i < countT; ++i) {
        int key = values[i];
        int j = i - 1;
        while (j >= 0 && values[j] > key) {
            values[j + 1] = values[j];
            j--;
        }
        values[j + 1] = key;
    }

    // 4. Записываем отсортированные значения обратно в узлы
    for (int i = 0; i < countT; ++i) {
        tNodes[i]->data = values[i];
    }

    delete[] tNodes;
    delete[] values;
}

// 6. Удаление всего списка
void deleteList(Node*& head, Node*& tail) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

int main() {
    setlocale(LC_ALL, "Russian");
    const char* filename = "numbers.txt";

    Node* head = nullptr;
    Node* tail = nullptr;

    // Создание списка из файла
    createListFromFile(head, tail, filename);
    std::cout << "Исходный список из файла:" << std::endl;
    printList(head);

    // Удаление элементов с Q (двузначные)
    deleteElementsWithQ(head, tail);
    std::cout << "После удаления двузначных чисел:" << std::endl;
    printList(head);

    // Дублирование элементов с R (чётные)
    duplicateElementsWithR(head, tail);
    std::cout << "После дублирования чётных чисел:" << std::endl;
    printList(head);

    // Упорядочивание элементов с T (не содержат 7)
    sortElementsWithT(head);
    std::cout << "После сортировки чисел без цифры 7:" << std::endl;
    printList(head);

    // Удаление всего списка
    deleteList(head, tail);
    std::cout << "Список удалён." << std::endl;

    return 0;
}