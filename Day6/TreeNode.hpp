#include <string>

#include "List.hpp"

class TreeNode
{
public:

    TreeNode(std::string value): value(value), children(new List<TreeNode*>()) {}

    std::string getValue() const {
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
    std::string value;
    List<TreeNode*>* children;
};
