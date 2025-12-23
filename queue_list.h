#ifndef QUEUE
#define QUEUE
#include <stdio.h>
#include <stdexcept>

template <class T>
class Queue {
private:
    // Узел односвязного списка
    struct Node {
        T data;
        Node* next;

        Node(const T& value, Node* nextNode = nullptr)
            : data(value), next(nextNode) {
        }
    };

    Node* _head;     // Указатель на начало очереди (для извлечения)
    Node* _tail;     // Указатель на конец очереди (для добавления)
    int _count;      // Текущее количество элементов
    int _maxSize;    // Максимальный размер очереди

public:
    // Конструктор
    Queue(int maxSize = 20)
        : _head(nullptr), _tail(nullptr), _count(0), _maxSize(maxSize) {
    }

    // Деструктор
    ~Queue() {
        clear();
    }

    // Конструктор копирования
    Queue(const Queue& other)
        : _head(nullptr), _tail(nullptr), _count(0), _maxSize(other._maxSize) {
        if (other._head != nullptr) {
            Node* current = other._head;
            while (current != nullptr) {
                push(current->data);
                current = current->next;
            }
        }
    }

    // Оператор присваивания
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clear();
            _maxSize = other._maxSize;

            if (other._head != nullptr) {
                Node* current = other._head;
                while (current != nullptr) {
                    push(current->data);
                    current = current->next;
                }
            }
        }
        return *this;
    }

    // Добавить элемент в конец очереди
    void push(const T& value) {
        if (isFull()) {
            throw std::logic_error("Queue is full");
        }

        Node* newNode = new Node(value);

        if (isEmpty()) {
            // Если очередь пуста, новый узел становится и головой, и хвостом
            _head = _tail = newNode;
        }
        else {
            // Добавляем в конец
            _tail->next = newNode;
            _tail = newNode;
        }

        _count++;
    }

    // Удалить элемент из начала очереди
    void pop() {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }

        Node* temp = _head;
        _head = _head->next;

        // Если очередь стала пустой, обнуляем и tail
        if (_head == nullptr) {
            _tail = nullptr;
        }

        delete temp;
        _count--;
    }

    // Получить ссылку на первый элемент
    T& front() {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        return _head->data;
    }

    // Получить константную ссылку на первый элемент
    const T& front() const {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        return _head->data;
    }

    // Получить ссылку на последний элемент
    T& back() {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        return _tail->data;
    }

    // Получить константную ссылку на последний элемент
    const T& back() const {
        if (isEmpty()) {
            throw std::logic_error("Queue is empty");
        }
        return _tail->data;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return _head == nullptr;
    }

    // Проверка на заполненность
    bool isFull() const {
        return _count == _maxSize;
    }

    // Получить текущий размер очереди
    int size() const {
        return _count;
    }

    // Получить максимальный размер очереди
    int maxSize() const {
        return _maxSize;
    }

    // Очистить очередь
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

#endif