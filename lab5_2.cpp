#include <iostream>
#include <fstream>
#include <cstdlib>

struct Node {
    int data;
    Node* next;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

void createListFromFile(Node*& head, const char* filename) {
    head = nullptr;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return;
    }

    int value;
    Node* tail = nullptr;
    while (file >> value) {
        Node* newNode = createNode(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    file.close();
}

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

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int d = 3; d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

bool isComposite(int n) {
    if (n <= 1) return false;
    return !isPrime(n);
}

int countComposite(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        if (isComposite(current->data)) {
            ++count;
        }
        current = current->next;
    }
    return count;
}

int getFirstDigit(int n) {
    n = std::abs(n);
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

void deleteStartingWithTwo(Node*& head) {
    while (head != nullptr && getFirstDigit(head->data) == 2) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    if (head == nullptr) return;

    Node* current = head;
    while (current->next != nullptr) {
        if (getFirstDigit(current->next->data) == 2) {
            Node* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
        } else {
            current = current->next;
        }
    }
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

int main() {
    setlocale(LC_ALL, "Russian");

    const char* filename = "numbers.txt";

    Node* myList = nullptr;

    createListFromFile(myList, filename);
    std::cout << "Список после загрузки из файла:" << std::endl;
    printList(myList);

    int compositeCount = countComposite(myList);
    std::cout << "Количество составных чисел: " << compositeCount << std::endl;

    deleteStartingWithTwo(myList);
    std::cout << "Список после удаления элементов, начинающихся с 2:" << std::endl;
    printList(myList);

    deleteList(myList);
    std::cout << "Список полностью удалён." << std::endl;

    return 0;
}