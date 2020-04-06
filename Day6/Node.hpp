template<class T> 
class Node
{
public:

    Node(T value): value(value), child(nullptr) {}

    T getValue() const {
        return this->value;
    }

    void setChild(Node<T>* child) {
        this->child = child;
    }

    Node<T>* getChild() {
        return this->child;
    }

private:
    T value;
    Node<T>* child;
};