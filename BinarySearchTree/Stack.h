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
        return "Wrong stack size";
    }
};

template <class T>
class StackArray : public Stack<T>
{
private:
    T* arr;
    int size = 0;
    int top = -1;

public:
    StackArray(int s) : size(s), top(-1)
    {
        if (s <= 0)
        {
            throw WrongStackSize();
        }
        arr = new T[size];
    }

    StackArray(const StackArray<T>& src) : size(src.size), top(src.top) {
  
        if (src.size < 0) {
            throw WrongStackSize();
        }
        arr = new T[src.size + 1];
        for (size_t i = 1; i < src.top; i++) {
            arr[i] = src.arr[i];
        }
    }

    StackArray(StackArray<T>&& src) = delete;
    StackArray& operator=(const StackArray<T>& src) = delete;
    StackArray& operator=(StackArray<T>&& src) = delete;

    ~StackArray()
    {
        delete[] arr;
    }

    void push(const T& element)
    {
        if (top == size - 1)
        {
            throw StackOverflow();
        }
        top++;
        arr[top] = element;
    }

    T pop()
    {
        if (top == -1)
        {
            throw StackUnderflow();
        }
        T element = arr[top];
        top--;
        return element;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    T length() {
        if (isEmpty()) {
            throw StackUnderflow();
        }
        return arr[top];
    }

};