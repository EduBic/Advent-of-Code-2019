#include <string>

#include "List.hpp"

class TreeNode
{
public:

    TreeNode(int id, std::string value, int level, TreeNode* parent) : 
        id(id), value(value), level(level), children(new List<TreeNode*>()), parent(parent) {}

    std::string getValue() const {
        return this->value;
    }

    int getId() const {
        return this->id;
    }

    int getLevel() const {
        return this->level;
    }

    void push_child(TreeNode* newChild) {
        children->push_back(newChild);
    }

    TreeNode* get_parent()
    {
        return this->parent;
    }

    List<TreeNode*>* get_children() {
        return this->children;
    }

    bool has_children() {
        return !children->is_empty();
    }

private:
    int id;
    std::string value;
    int level;
    List<TreeNode*>* children;
    TreeNode* parent;
};
