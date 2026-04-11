#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Узел списка
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Класс линейного списка
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Деструктор - удаление всего списка
    ~LinkedList() {
        clear();
    }

    // Добавление элемента в конец
    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    // Создание списка: случайные числа или ручной ввод
    void create() {
        int choice, n, value;
        cout << "Выберите способ заполнения:\n1. Случайные числа\n2. Ручной ввод\nВаш выбор: ";
        cin >> choice;
        cout << "Введите количество элементов: ";
        cin >> n;
        if (n <= 0) return;

        if (choice == 1) {
            srand(time(0));
            for (int i = 0; i < n; ++i) {
                value = rand() % 100; // числа от 0 до 99
                append(value);
            }
        } else {
            for (int i = 0; i < n; ++i) {
                cout << "Элемент " << i + 1 << ": ";
                cin >> value;
                append(value);
            }
        }
    }

    // Вывод списка на экран
    void print() const {
        if (!head) {
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

    // Удаление всего списка (освобождение памяти)
    void clear() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Подсчёт элементов, больших предыдущего и меньших последующего
    int countSpecial() const {
        if (!head || !head->next || !head->next->next) return 0;
        int count = 0;
        Node* prev = head;
        Node* curr = head->next;
        Node* next = curr->next;
        while (next) {
            if (curr->data > prev->data && curr->data < next->data)
                ++count;
            prev = curr;
            curr = next;
            next = next->next;
        }
        return count;
    }
};

int main() {
    LinkedList list;
    list.create();
    list.print();
    cout << "Количество элементов, больших предыдущего и меньших последующего: "
         << list.countSpecial() << endl;
    // Список автоматически удалится в деструкторе
    return 0;
}