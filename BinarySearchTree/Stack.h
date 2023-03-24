#pragma once
#include <exception>

template <class T>
class Stack
{
public:
	virtual ~Stack() {}
	virtual void push(const T& e) = 0;
	virtual T pop() = 0;
	virtual bool isEmpty() = 0;
};

class StackOverflow : public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Stack overflow";
    }
};

class StackUnderflow : public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Stack underflow";
    }
};

class WrongStackSize : public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Wrong stack size_";
    }
};

template <class T>
class StackArray : public Stack<T>
{
private:
    T* arr_;
    int size_ = 0;
    int top_ = -1;

public:
    StackArray(int s) : size_(s), top_(-1)
    {
        if (s <= 0)
        {
            throw WrongStackSize();
        }
        arr_ = new T[size_];
    }

    StackArray(const StackArray<T>& src) : size_(src.size_), top_(src.top_) {
  
        if (src.size_ < 0) {
            throw WrongStackSize();
        }
        arr_ = new T[src.size_ + 1];
        for (size_t i = 1; i < src.top_; i++) {
            arr_[i] = src.arr_[i];
        }
    }

    StackArray(StackArray<T>&& src) = delete;
    StackArray& operator=(const StackArray<T>& src) = delete;
    StackArray& operator=(StackArray<T>&& src) = delete;

    ~StackArray()
    {
        delete[] arr_;
    }

    void push(const T& element)
    {
        if (top_ == size_ - 1)
        {
            throw StackOverflow();
        }
        top_++;
        arr_[top_] = element;
    }

    T pop()
    {
        if (top_ == -1)
        {
            throw StackUnderflow();
        }
        T element = arr_[top_];
        top_--;
        return element;
    }

    bool isEmpty()
    {
        return top_ == -1;
    }

    T top() {
        if (isEmpty()) {
            throw StackUnderflow();
        }
        return arr_[top_];
    }

};