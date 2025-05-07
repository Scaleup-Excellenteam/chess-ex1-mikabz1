#pragma once

#include <list>

/// @brief Default comparator for priority queue elements.
/// @tparam T Type of elements stored in the queue. Assumes operator- is defined.
template <typename T>
struct MyComparator{
    /// @brief Compares two elements by subtracting one from the other.
    /// @return A negative number if a < b, zero if equal, positive if a > b.
    int operator()(const T& a, const T& b){return a - b;}
};

/// @brief A custom priority queue that keeps the top 5 highest-priority elements.
/// @tparam T The type of the elements stored in the queue.
template <typename T>
class PriorityQueue{
public:
    /// @brief Inserts an element into the queue while maintaining order.
    ///        Keeps only the top 5 elements (based on comparator).
    /// @param t The element to insert.
    void push(const T&);
    /// @brief Removes and returns the highest-priority element.
    /// @return The element with the highest priority (from the end of the list).
    T pull();
    /// @brief Assignment operator.
    /// @param other Another priority queue to copy from.
    /// @return Reference to this priority queue.
    PriorityQueue<T>& operator=(const PriorityQueue<T>& other);
    /// @brief Prints up to 3 best recommended elements (from highest to lower priority).
    void print(){

        int count = 0;
        auto it = _data.end();
        while(it-- != _data.begin()){
            std::cout << "Recommended move: ";
            std::cout << *it;
            count++;
            if(count > 2)break;
        }
    }
private:
    std::list<T> _data;
    MyComparator<T> _comparator;
};

template<typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(const PriorityQueue<T> &other) {
    _data = other._data;
    return *this;
}

template<typename T>
void PriorityQueue<T>::push(const T &t) {
    for (auto it = _data.begin(); it != _data.end(); ++it) {
        if (_comparator(t, *it) < 0) {
            _data.insert(it, t);
            if(_data.size() > 5)_data.pop_front();
            return;
        }
    }
    _data.push_back(t);
    if(_data.size() > 5)_data.pop_front();
}

template<typename T>
T PriorityQueue<T>::pull(){
    T result = _data.back();
    _data.pop_back();
    return result;
}

