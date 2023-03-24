#pragma once
#include <exception>

template <class T>
class Queue
{
public:
    virtual ~Queue() {}
    virtual void enQueue(const T& e) = 0; // Adding an item to the queue
    virtual T deQueue() = 0; // Removing the top element
    virtual bool isEmpty() = 0; // Checking the queue for emptiness
};

class QueueOverflow : public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Queue is full!";
    }
};

class QueueUnderflow : public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Queue is empty!";
    }
};

class WrongQueueSize : public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Wrong queue size!";
    }
};

template <class T>
class QueueArray : public Queue<T> {
private:
    int size = 0;
    int head = -1;
    int tail = -1;
    T* queueArray;

public:
    QueueArray(int size) : size(size), head(-1), tail(-1) {
        if (size <= 0) {
            throw WrongQueueSize();
        }
        queueArray = new T[size];
    }

    QueueArray(const QueueArray<T>& src) = delete;
    QueueArray(QueueArray<T>&& src) = delete;
    QueueArray& operator=(const QueueArray<T>& src) = delete;
    QueueArray& operator=(QueueArray<T>&& src) = delete;

    ~QueueArray() {
        delete[] queueArray;
    }

    void enQueue(const T& element) {
        if (head == -1) {
            head = 0;
        }
        if (tail == size - 1) {
            throw QueueOverflow();
        }
        tail++;
        queueArray[tail] = element;
    }

    T deQueue() {
        if (isEmpty()) {
            throw QueueUnderflow();
        }
        T item = queueArray[head];
        head++;
        if (head > tail) {
            head = tail = -1;
        }
        return item;
    }

    bool isEmpty() {
        return head == -1 and tail == -1;
    }

};