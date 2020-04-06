#include <iostream>
#include <sstream>

#include "TreeNode.hpp"

using namespace std;

TreeNode* findTreeNode(const string& key, TreeNode* root) {
    List<TreeNode*>* supportList = new List<TreeNode*>();
    supportList->push_back(root); // first node

    Node<TreeNode*>* iter = supportList->next();
    while (!supportList->is_empty())
    {
        TreeNode* currentTreeNode = supportList->pop_front();
        // use the value of node
        if (currentTreeNode->getValue() == key) {
            cout << "Found" << currentTreeNode->getValue() << endl;
            return currentTreeNode;
        }

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

    return nullptr;
}


int main()
{
    string inputExample[] = {
        "Sun)Mercury",
        "Sun)Venus",
        "Sun)Earth",
        "Sun)Mars",
        "Earth)Moon",
        "Mars)Deimos",
        "Mars)Phobos",
    };
    int inputExampleCount = 7;

    // Find and create the root
    // The root will never appear to the right position in the strings
    TreeNode* root = nullptr;
    for (int i = 0; i < inputExampleCount; i++)
    {
        stringstream ss(inputExample[i]);
        string item;

        for (int k = 0; getline(ss, item, ')'); k++)
        {
            
        }
    }

    // Build the TREE
    for (int i = 0; i < inputExampleCount; i++)
    {
        string curr = inputExample[i];

        stringstream ss(curr);
        string item;
        TreeNode* left = nullptr;
        // if k == 0 // left item, right otherwise
        for (int k = 0; getline(ss, item, ')'); k++)
        {
            TreeNode* nodeFound = findTreeNode(item, root);


            if (k == 0) {
                left = new TreeNode(item);
            }
            else {
                TreeNode* right = new TreeNode(item);
                left->push_child(right);
            }
        }

        if (root == nullptr) {
            root = left;
        }
    }


    /*
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
    } */
}
