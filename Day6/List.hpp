#include "Node.hpp"


template<class T> 
class List
{
public:
    List(): first(nullptr), size(0) {}

    void push_back(T newItem) {
        // assert child != nullptr
        if (first == nullptr) 
        {
            first = new Node<T>(newItem);
        }
        else 
        {
            for (Node<T>* iter = first; iter != nullptr; iter = iter->getChild()) 
            {
                if (iter->getChild() == nullptr) {
                    // end of list
                    iter->setChild(new Node<T>(newItem));
                    break;
                }
            }
        }
        size++;
    }

    T pop_front() {
        Node<T>* oldFirst = first;
        first = oldFirst->getChild();
        T frontValue = oldFirst->getValue();
        delete oldFirst;

        size--;
        return frontValue;
    }

    Node<T>* next() {
        return first;
    }

    bool is_empty() const
    {
        return first == nullptr;
    }

private:
    Node<T>* first;
    int size;
};