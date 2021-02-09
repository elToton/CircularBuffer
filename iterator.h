#ifndef CIRCULARBUFFER_ITERATOR_H
#define CIRCULARBUFFER_ITERATOR_H

#pragma once
#include<iterator>
#include "buffer.h"

using namespace std;

template<typename Ti>
class Iterator
        : public iterator<random_access_iterator_tag, Ti>{
private:
    Ti* position;
    Ti* bufferItself;
    Ti* dataBegin;
    Ti* dataEnd;
    size_t capacity;
public:
    Iterator() : bufferItself(nullptr), capacity(0), dataBegin(nullptr), dataEnd(nullptr), position(nullptr) {}

    Iterator(Ti* data, size_t capacity, Ti* dataBegin, Ti* dataEnd, Ti* position)
            : bufferItself(data), capacity(capacity), dataBegin(dataBegin), dataEnd(dataEnd), position(position) {}

    bool operator!=(Iterator const& right) const{
        return this->position != right.position;
    }

    bool operator==(Iterator const& right) const{
        return (this->bufferItself - this->position) % capacity == (bufferItself - right.position) % capacity;
    }

    bool operator>(Iterator const& right) const{
        if (dataEnd > dataBegin){
            return this->position - right.position > 0;
        }
        else{
            if ((right.position >= dataEnd) && (this->position >= dataEnd))
                return this->position - right.position > 0;
            else if (right.position >= dataEnd)
                return (bufferItself - position + (capacity - (dataBegin - bufferItself))) > (right.position - dataBegin);
            else if (this->position >= dataEnd)
                return (position - dataBegin) > (right.position - bufferItself + (capacity - (dataBegin - bufferItself)));
            else
                return this->position - position > 0;
        }
    }

    bool operator>=(Iterator const& right) const{
        if (dataEnd > dataBegin){
            return this->position - right.position >= 0;
        }
        else{
            if ((right.position >= dataEnd) && (this->position >= dataEnd))
                return this->position - right.position > 0;
            else if (right.position >= dataEnd)
                return (bufferItself - position + (capacity - (dataBegin - bufferItself))) >= (right.position - dataBegin);
            else if (this->position >= dataEnd)
                return (position - dataBegin) >= (right.position - bufferItself + (capacity - (dataBegin - bufferItself)));
            else
                return this->position - position >= 0;
        }
    }

    bool operator<(Iterator const& right) const{
        return !(*this >= right);
    }

    bool operator<=(Iterator const& right) const{
        return !(*this > right);
    }

    Iterator operator+ (const int& N){
        position = bufferItself + (position + N - bufferItself) % capacity;
        return *this;
    }
    Iterator operator+ (const int& N) const{
        Iterator temp{bufferItself, capacity, dataBegin, dataEnd, bufferItself + (position + N - bufferItself) % capacity };
        return temp;
    }

    Iterator operator- (const int& N){
        position = bufferItself + (position - N - bufferItself + capacity) % capacity;
        return *this;
    }

    Iterator& operator++(int){
        ++position;
        if (position - bufferItself >= capacity + 1)
            position = bufferItself + ((position - bufferItself) % capacity);
        return *this;
    }
    Iterator& operator++(){
        ++position;
        if (position - bufferItself >= capacity + 1)
            position = bufferItself + ((position - bufferItself) % capacity);
        return *this;
    }
    Iterator operator--(int){
        --position;
        if (position < bufferItself)
            position = bufferItself + capacity;
        return *this;
    }
    Iterator operator--(){
        --position;
        if (position < bufferItself)
            position = bufferItself + capacity;
        return *this;
    }

    Ti& operator[](typename iterator<random_access_iterator_tag, Ti>::difference_type diff){
        return bufferItself[(position - bufferItself + diff + capacity) % capacity];
    }

    typename Iterator::reference operator*() const{
        return bufferItself[(position - bufferItself + capacity) % capacity];
    }

    typename iterator<random_access_iterator_tag, Ti>::difference_type operator- (const Iterator& It) const{
        if (dataEnd > dataBegin)
        {
            return abs((int)(this->position - It.position));
        }
        else
        {
            if ((It.position >= dataEnd) && (this->position >= dataEnd))
                return abs((int)(this->position - It.position));
            else if (It.position >= dataEnd)
                return abs((int)((bufferItself - position + (capacity - (dataBegin - bufferItself))) - (It.position - dataBegin)));
            else if (this->position >= dataEnd)
                return  abs((int)((position - dataBegin) - (It.position - bufferItself + (capacity - (dataBegin - bufferItself)))));
            else
                return abs((int)(this->position - It.position));
        }
    }
};


#endif