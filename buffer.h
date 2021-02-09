#pragma once
#include <iostream>
#include <exception>
#include <algorithm>
#include "iterator.h"

using namespace std;

template<typename T> class RingBuffer {
private:
    size_t CurrentSize;
    T* head;
    T* tail;
    T* BufferSize;
    size_t capacity;
public:
    RingBuffer() :
            CurrentSize(0), head(nullptr), tail(nullptr), BufferSize(nullptr), capacity(0) {};

    RingBuffer(const size_t& size){
        BufferSize = new T[size];
        fill(BufferSize, BufferSize + size, 0);
        capacity = size;
        head = BufferSize;
        tail = BufferSize;
        CurrentSize = 0;
    }

    ~RingBuffer() {
        delete[] BufferSize;
    }

    void ChangeCapacity(const size_t& newSize){
        T* NewBuffer;
        if (newSize < capacity){
            NewBuffer = new T[newSize];
            for (int i = 0; i < newSize; i++)
                NewBuffer[i] = BufferSize[(head - BufferSize + i) % capacity];
            delete[] BufferSize;
            BufferSize = NewBuffer;
            capacity = newSize;
            head = BufferSize;
            tail = head + newSize;
        }
        else{
            NewBuffer = new T[newSize];
            for (int i = 0; i < capacity; i++)
                NewBuffer[i] = BufferSize[(head - BufferSize + i) % capacity];
            delete[] BufferSize;
            BufferSize = NewBuffer;
            head = NewBuffer;
            tail = NewBuffer + capacity;
            capacity = newSize;
        }
    }

    Iterator<T> end(){
        return Iterator<T>{BufferSize, capacity, head, tail, tail};
    }

    Iterator<T> begin(){
        return Iterator<T>{BufferSize, capacity, head, tail, head};
    }

    void push_back(const T& value){
        if (tail == head){
            if (tail != BufferSize)
                head++;
            if (head > BufferSize + capacity)
                head = BufferSize;
            if (tail == BufferSize)
                CurrentSize++;
        }
        else{
            if (tail - BufferSize != capacity)
                CurrentSize++;
        }

        if (tail - BufferSize == capacity){
            *BufferSize = value;
            tail = BufferSize + 1;
            head++;
            if (head > BufferSize + capacity)
                head = BufferSize;
        }
        else{
            *tail = value;
            tail++;
        }
    }

    size_t size(){
        return CurrentSize;
    }

    T& top() const{
        return *(tail - 1);
    }

    T& bottom() const{
        return *(head);
    }

    void pop_back(){
        if (CurrentSize == 0)
            throw runtime_error("Empty buffer");
        head++;
        if (head > BufferSize + capacity)
            head = BufferSize;
        CurrentSize--;
    }

    void pop_front(){
        if (CurrentSize == 0)
            throw runtime_error("Empty buffer");
        tail--;
        if (tail < BufferSize)
            tail = BufferSize + capacity + 1;
        CurrentSize--;
    }

    void push_front(const T& value){
        if (CurrentSize == capacity)
            *head = value;
        else{
            head--;
            if (head < BufferSize)
                head = BufferSize + capacity - 1;
            *head = value;
            CurrentSize++;
        }
    }

    T& operator[](const size_t& position) const{
        return BufferSize[(head - BufferSize + position) % capacity];
    }

    Iterator<T> insert(const Iterator<T>& position, const T& value){
        if (position == this->end()){
            this->push_back(value);
            return this->end();
        }
        else if (position == this->begin()){
            this->push_front(value);
            return this->begin();
        }
        else{
            T* NewBuffer = new T[capacity];
            int flag = 0, toreturn;
            Iterator<T> iter = this->begin();
            for (int i = 0; i <= CurrentSize; i++){
                if (iter == position){
                    toreturn = i % capacity;
                    NewBuffer[i] = value;
                    i++;
                    flag = -1;
                }
                NewBuffer[i % capacity] = BufferSize[(head - BufferSize + i + flag) % capacity];
                iter++;
            }
            delete[] BufferSize;
            BufferSize = NewBuffer;
            head = BufferSize;
            if (CurrentSize < capacity)
                CurrentSize++;
            tail = BufferSize + CurrentSize;
            if (tail - BufferSize > capacity + 1)
                tail = BufferSize;
            return Iterator<T>{BufferSize, capacity, head, tail, BufferSize + toreturn};
        }
    }

    Iterator<T> erase(const Iterator<T> position){
        if (CurrentSize == 0)
            throw runtime_error("Empty buffer");
        if (position == this->begin()){
            this->pop_back();
            return this->begin();
        }
        else if (position == this->begin()){
            this->pop_front();
            return this->end();
        }
        else{
            T* NewBuffer = new T[capacity];
            int flag = 0, toreturn;
            Iterator<T> iter = this->begin();
            CurrentSize--;
            for (int i = 0; i <= CurrentSize; i++){
                if (iter == position){
                    toreturn = i;
                    flag = 1;
                }
                NewBuffer[i % capacity] = BufferSize[(head - BufferSize + i + flag) % capacity];
                iter++;
            }
            delete[] BufferSize;
            BufferSize = NewBuffer;
            head = BufferSize;
            tail = BufferSize + CurrentSize;
            if (tail - BufferSize > capacity + 1)
                tail = BufferSize;
            return Iterator<T>{BufferSize, capacity, head, tail, BufferSize + toreturn};
        }
    }

    void printAll() {
        cout << '\t';
        for (int i = 0; i < capacity; i++){
            cout << *(BufferSize + i) << ", ";
        }
        cout << "\n\t";
        for (int i = 0; i <= capacity; i++){
            if ((BufferSize + i != head) && (BufferSize + i != tail))
                cout << "M   ";
            else if (BufferSize + i == head){
                if (head != tail)
                    cout << "B   ";
                else
                    cout << "BE  ";
            }
            else
                cout << "E   ";
        }
        cout << '\n';
    }

    void spin(){
        T* NewBuffer = new T[capacity];
        for (int i = 0; i < CurrentSize; i++)
            NewBuffer[i % capacity] = BufferSize[(head - BufferSize + i) % capacity];
        delete[] BufferSize;
        BufferSize = NewBuffer;
        head = BufferSize;
        tail = BufferSize + CurrentSize;
        if (tail - BufferSize > capacity + 1)
            tail = BufferSize;
    }
};
