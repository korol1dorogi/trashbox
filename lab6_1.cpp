#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

struct StackNode {
    int data;
    StackNode* next;
    StackNode(int d) : data(d), next(nullptr) {}
};

struct ListStack {
    StackNode* top;
    ListStack() : top(nullptr) {}
    ListStack(const ListStack&) = delete;
    ListStack& operator=(const ListStack&) = delete;
    ~ListStack() {
        while (top) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
    void push(int val) {
        StackNode* newNode = new StackNode(val);
        newNode->next = top;
        top = newNode;
    }
    int pop() {
        if (!top) return INT_MIN;
        int val = top->data;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        return val;
    }
    void print() {
        if (!top) { cout << "Стек пуст\n"; return; }
        StackNode* cur = top;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
    bool isEmpty() { return top == nullptr; }
    void copyTo(ListStack& dest) {
        if (!top) return;
        int arr[1000];
        int n = 0;
        StackNode* cur = top;
        while (cur) {
            arr[n++] = cur->data;
            cur = cur->next;
        }
        for (int i = n-1; i >= 0; i--)
            dest.push(arr[i]);
    }
};

void sortStackByData(ListStack& s) {
    if (s.isEmpty()) return;
    bool swapped;
    do {
        swapped = false;
        StackNode* cur = s.top;
        while (cur && cur->next) {
            if (cur->data > cur->next->data) {
                int t = cur->data;
                cur->data = cur->next->data;
                cur->next->data = t;
                swapped = true;
            }
            cur = cur->next;
        }
    } while (swapped);
}

void sortStackByAddress(ListStack& s) {
    if (s.isEmpty() || !s.top->next) return;
    StackNode dummy(0);
    dummy.next = s.top;
    bool swapped;
    do {
        swapped = false;
        StackNode* prev = &dummy;
        while (prev->next && prev->next->next) {
            StackNode* cur = prev->next;
            StackNode* nxt = cur->next;
            if (cur->data > nxt->data) {
                cur->next = nxt->next;
                nxt->next = cur;
                prev->next = nxt;
                swapped = true;
            } else {
                prev = prev->next;
            }
        }
    } while (swapped);
    s.top = dummy.next;
}

struct QueueNode {
    int data;
    QueueNode* prev;
    QueueNode* next;
    QueueNode(int d) : data(d), prev(nullptr), next(nullptr) {}
};

struct ListQueue {
    QueueNode* front;
    QueueNode* rear;
    ListQueue() : front(nullptr), rear(nullptr) {}
    ListQueue(const ListQueue&) = delete;
    ListQueue& operator=(const ListQueue&) = delete;
    ~ListQueue() {
        while (front) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
    void pushBack(int val) {
        QueueNode* newNode = new QueueNode(val);
        if (!front) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
    }
    void pushFront(int val) {
        QueueNode* newNode = new QueueNode(val);
        if (!front) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }
    int popFront() {
        if (!front) return INT_MIN;
        int val = front->data;
        QueueNode* temp = front;
        front = front->next;
        if (front) front->prev = nullptr;
        else rear = nullptr;
        delete temp;
        return val;
    }
    int popBack() {
        if (!rear) return INT_MIN;
        int val = rear->data;
        QueueNode* temp = rear;
        rear = rear->prev;
        if (rear) rear->next = nullptr;
        else front = nullptr;
        delete temp;
        return val;
    }
    void printFromFront() {
        if (!front) { cout << "Очередь пуста\n"; return; }
        QueueNode* cur = front;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
    void printFromBack() {
        if (!rear) { cout << "Очередь пуста\n"; return; }
        QueueNode* cur = rear;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->prev;
        }
        cout << endl;
    }
    double average() {
        if (!front) return 0;
        double sum = 0;
        int count = 0;
        QueueNode* cur = front;
        while (cur) {
            sum += cur->data;
            count++;
            cur = cur->next;
        }
        return sum / count;
    }
    void replaceEvenWithAvg() {
        double avg = average();
        if (!front) return;
        QueueNode* cur = front;
        while (cur) {
            if (cur->data % 2 == 0)
                cur->data = static_cast<int>(avg+0.5);
            cur = cur->next;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned>(time(nullptr)));

    const int N = 10;
    int numbers[N];
    cout << "Случайные числа: ";
    for (int i = 0; i < N; i++) {
        numbers[i] = rand() % 201 - 100;
        cout << numbers[i] << " ";
    }
    cout << endl;

    cout << "\nСТЕК\n";
    ListStack stack;
    for (int i = 0; i < N; i++) stack.push(numbers[i]);
    cout << "Исходный стек (сверху вниз): ";
    stack.print();

    ListStack stackForData;
    stack.copyTo(stackForData);
    sortStackByData(stackForData);
    cout << "Сортировка обменом информацией: ";
    stackForData.print();

    ListStack stackForAddr;
    stack.copyTo(stackForAddr);
    sortStackByAddress(stackForAddr);
    cout << "Сортировка обменом адресами: ";
    stackForAddr.print();

    cout << "\nОЧЕРЕДЬ\n";
    ListQueue queue;
    for (int i = 0; i < N; i++) queue.pushBack(numbers[i]);
    cout << "Исходная очередь (с начала): ";
    queue.printFromFront();

    int extra1 = rand() % 201 - 100;
    queue.pushFront(extra1);
    cout << "Добавили в начало " << extra1 << ": ";
    queue.printFromFront();

    int extra2 = rand() % 201 - 100;
    queue.pushBack(extra2);
    cout << "Добавили в конец " << extra2 << ": ";
    queue.printFromFront();

    cout << "Просмотр с начала: ";
    queue.printFromFront();
    cout << "Просмотр с конца: ";
    queue.printFromBack();

    double avg = queue.average();
    cout << "Среднее арифметическое: " << avg << endl;
    queue.replaceEvenWithAvg();
    cout << "После замены чётных чисел на среднее: ";
    queue.printFromFront();

    return 0;
}