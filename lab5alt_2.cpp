#include <iostream>
#include <fstream>
#include <cstdlib>  // для abs
#include <cstring>  // для strerror

using namespace std;

// Узел односвязного списка
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Создание списка из текстового файла
void createListFromFile(const char* filename, Node** head) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл '" << filename << "'\n";
        exit(1);
    }
    int value;
    while (file >> value) {
        Node* newNode = new Node(value);
        if (*head == nullptr) {
            *head = newNode;
        } else {
            Node* temp = *head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }
    file.close();
}

// Вывод списка на экран
void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    cout << "Список: ";
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Проверка, является ли число симметричным (палиндромом)
bool isSymmetric(int n) {
    int absN = abs(n);
    if (absN < 0) return false; // для полноты, но abs всегда неотрицателен
    int reversed = 0;
    int original = absN;
    while (original > 0) {
        reversed = reversed * 10 + original % 10;
        original /= 10;
    }
    return absN == reversed;
}

// Количество элементов списка, обладающих свойством Q (симметричные)
int countQ(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp) {
        if (isSymmetric(temp->data)) {
            ++count;
        }
        temp = temp->next;
    }
    return count;
}

// Проверка, является ли число трёхзначным
bool isThreeDigit(int n) {
    int absN = abs(n);
    return absN >= 100 && absN <= 999;
}

// Удаление всех элементов списка, обладающих свойством T (трёхзначные)
void deleteT(Node** head) {
    // Удаление в начале списка
    while (*head != nullptr && isThreeDigit((*head)->data)) {
        Node* toDelete = *head;
        *head = (*head)->next;
        delete toDelete;
    }
    if (*head == nullptr) return;
    // Удаление в середине и конце
    Node* prev = *head;
    Node* curr = (*head)->next;
    while (curr) {
        if (isThreeDigit(curr->data)) {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

// Удаление всего списка
void deleteList(Node** head) {
    Node* temp;
    while (*head) {
        temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    char filename[256];
    cout << "Введите имя файла с целыми числами: ";
    cin >> filename;
    Node* list = nullptr;
    createListFromFile(filename, &list);
    cout << "\nПосле заполнения из файла:\n";
    printList(list);
    int qCount = countQ(list);
    cout << "Количество симметричных чисел (Q): " << qCount << endl;
    cout << "\nУдаление трёхзначных чисел (T)\n";
    deleteT(&list);
    cout << "После удаления:\n";
    printList(list);
    deleteList(&list);
    return 0;
}