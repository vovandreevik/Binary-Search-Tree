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
        return "Wrong queue size_!";
    }
};

template <class T>
class QueueArray : public Queue<T> {
private:
    int size_ = 0;
    int head_ = -1;
    int tail_ = -1;
    T* queueArray_;

public:
    QueueArray(int size_) : size_(size_), head_(-1), tail_(-1) {
        if (size_ <= 0) {
            throw WrongQueueSize();
        }
        queueArray_ = new T[size_];
    }

    QueueArray(const QueueArray<T>& src) = delete;
    QueueArray(QueueArray<T>&& src) = delete;
    QueueArray& operator=(const QueueArray<T>& src) = delete;
    QueueArray& operator=(QueueArray<T>&& src) = delete;

    ~QueueArray() {
        delete[] queueArray_;
    }

    void enQueue(const T& element) {
        if (head_ == -1) {
            head_ = 0;
        }
        if (tail_ == size_ - 1) {
            throw QueueOverflow();
        }
        tail_++;
        queueArray_[tail_] = element;
    }

    T deQueue() {
        if (isEmpty()) {
            throw QueueUnderflow();
        }
        T item = queueArray_[head_];
        head_++;
        if (head_ > tail_) {
            head_ = tail_ = -1;
        }
        return item;
    }

    bool isEmpty() {
        return head_ == -1 and tail_ == -1;
    }

};