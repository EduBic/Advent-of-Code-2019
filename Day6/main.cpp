#include <string>
#include <iostream>

using namespace std;

class Node
{
public:

    Node(string value): value(value), child(nullptr) {}

    string getValue() const {
        return this->value;
    }

    void setChild(Node* child) {
        this->child = child;
    }

    Node* getChild() {
        return this->child;
    }

private:
    string value;
    Node* child;
};

template<class T> 
class List
{
public:
    List(): first(nullptr) {}

    void push_back(T* newItem) {
        // assert child != nullptr
        if (first == nullptr) 
        {
            first = newItem;
        }
        else 
        {
            for (T* iter = first; iter != nullptr; iter = iter->getChild()) 
            {
                if (iter->getChild() == nullptr) {
                    // end of list
                    iter->setChild(newItem);
                    break;
                }
            }
        }
    }

    T* next() {
        return this->first;
    }

private:
    T* first;
};


class TreeNode
{
public:

    TreeNode(string value): value(value), children(new List<TreeNode>()) {}

    string getValue() const {
        return this->value;
    }

    void push_child(TreeNode* newChild) {
        children->push_back(newChild);
    }

    List<TreeNode>* get_children() {
        return this->children;
    }

private:
    string value;
    List<TreeNode>* children;
};


int main()
{
    TreeNode* sun = new TreeNode("Sun");

    TreeNode* mercury = new TreeNode("Mercury");

    TreeNode* venus = new TreeNode("Venus");

    TreeNode* earth = new TreeNode("Earth");
    TreeNode* moon = new TreeNode("Moon");
    earth->push_child(moon);

    TreeNode* mars = new TreeNode("Mars");
    TreeNode* deimos = new TreeNode("Deimos");
    TreeNode* phobos = new TreeNode("Phobos");
    mars->push_child(deimos);
    mars->push_child(phobos);

    sun->push_child(mercury);
    sun->push_child(venus);
    sun->push_child(earth);
    sun->push_child(mars);

    
    cout << sun->getValue() << endl;
    List<TreeNode>* sunChildren = sun->get_children();
    TreeNode* iter = sunChildren->next();

    // support list <- children of Sun
    // iter = supportList->next()
    while (iter != nullptr)
    {
        // use the value of node
        cout << sun->getValue() << endl;

        // if iter->children is not empty()
        // add these children to the support list
        // iter = iter->next();
    }
}
