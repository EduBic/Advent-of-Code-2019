#include <string>
#include <iostream>

using namespace std;

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


class TreeNode
{
public:

    TreeNode(string value): value(value), children(new List<TreeNode*>()) {}

    string getValue() const {
        return this->value;
    }

    void push_child(TreeNode* newChild) {
        children->push_back(newChild);
    }

    List<TreeNode*>* get_children() {
        return this->children;
    }

    bool has_children() {
        return !children->is_empty();
    }

private:
    string value;
    List<TreeNode*>* children;
};


int main()
{
    TreeNode* sun = new TreeNode("1-Sun");

    TreeNode* mercury = new TreeNode("2-Mercury");

    TreeNode* venus = new TreeNode("3-Venus");

    TreeNode* earth = new TreeNode("4-Earth");
    TreeNode* moon = new TreeNode("6-Moon");
    earth->push_child(moon);

    TreeNode* mars = new TreeNode("5-Mars");
    TreeNode* deimos = new TreeNode("7-Deimos");
    TreeNode* phobos = new TreeNode("8-Phobos");
    mars->push_child(deimos);
    mars->push_child(phobos);
    TreeNode* I1 = new TreeNode("9-I1");
    moon->push_child(I1);
    TreeNode* I2 = new TreeNode("10-I2");
    phobos->push_child(I2);
    
    sun->push_child(mercury);
    sun->push_child(venus);
    sun->push_child(earth);
    sun->push_child(mars);

    // cout all nodes
    List<TreeNode*>* supportList = new List<TreeNode*>();
    supportList->push_back(sun); // first node

    Node<TreeNode*>* iter = supportList->next();
    while (!supportList->is_empty())
    {
        TreeNode* currentTreeNode = supportList->pop_front();
        // use the value of node
        cout << currentTreeNode->getValue() << endl;

        if (currentTreeNode->has_children()) {
            List<TreeNode*>* children = currentTreeNode->get_children();
            for (Node<TreeNode*>* childIter = children->next(); 
                childIter != nullptr; 
                childIter = childIter->getChild())
            {
                supportList->push_back(childIter->getValue());
            }
        }
    }
}
