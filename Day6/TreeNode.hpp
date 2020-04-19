#include <string>

#include "List.hpp"

class TreeNode
{
public:

    TreeNode(int id, std::string value, int level) : 
        id(id), value(value), level(level), children(new List<TreeNode*>()) {}

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
};
