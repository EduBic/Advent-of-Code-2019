#include <iostream>
#include <sstream>
#include <fstream>

#include "TreeNode.hpp"

using namespace std;

// fill arrays with left items and right items from file
void fillElements(int argc, char *argv[], string* leftItems, string* rightItems) {
    if (argc != 2)
    {
        cerr << "Insert file name as input" << endl;
        exit(1);
    }

    ifstream inputList;
    inputList.open(argv[1]);

    if (!inputList)
    {
        cerr << "Unable to open file " << argv[1];
        exit(1);   // call system to stop
    }

    // 1) iterate over line of entire file
    string line;
    for (int i = 0; getline(inputList, line); i++)
    {
        // 2) iterate over a single line split by ')' symbol
        stringstream ssLine(line);
        string item;
        for (int k = 0; getline(ssLine, item, ')'); k++)
        {
            if (k == 0)
            {
                leftItems[i] = item;
                // cout << item << ")";
            }
            else 
            {
                rightItems[i] = item;
                // cout << item << endl;
            }
        }
    }
}

int linesCounter(int argc, char *argv[]) {
    if (argc != 2)
    {
        cerr << "Insert file name as input" << endl;
        exit(1);
    }

    ifstream inputList;
    inputList.open(argv[1]);

    if (!inputList)
    {
        cerr << "Unable to open file " << argv[1];
        exit(1);   // call system to stop
    }

    int counter = 0;
    string line;
    while (getline(inputList, line))
    {
        counter++;
    }
    return counter;
}

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

string findRoot(const int inputExampleCount, const string* leftItems, const string* rightItems) 
{
    string rootId;
    for (int i = 0; i < inputExampleCount; i++)
    {
        bool isRoot = true;
        for (int k = 0; k < inputExampleCount; k++)
        {
            if (leftItems[i] == rightItems[k])
            {
                isRoot = false;
                break;
            }
        }

        if (isRoot)
        {
            return leftItems[i];
        }
    }

    return "";
}


int main(int argc, char *argv[])
{
    int inputExampleCount = linesCounter(argc, argv);
    string* leftItems = new string[inputExampleCount];
    string* rightItems = new string[inputExampleCount];

    cout << "Total lines count: " << inputExampleCount << endl;

    fillElements(argc, argv, leftItems, rightItems);

    // Find root
    TreeNode* root = new TreeNode(0, "COM", 0);
    //TreeNode* root = new TreeNode("COM");

    // Build the TREE
    List<TreeNode*>* buildSupportList = new List<TreeNode*>();
    buildSupportList->push_back(root); // first node
    int nodesCounter = 1;

    while (!buildSupportList->is_empty())
    {
        TreeNode* currNode = buildSupportList->pop_front();

        for (int i = 0; i < inputExampleCount; i++)
        {
            // read one line "left)right"
            string left = leftItems[i];
            string right = rightItems[i];

            if (left == currNode->getValue()) {
                TreeNode* rightNode = new TreeNode(nodesCounter, right, currNode->getLevel() + 1);
                nodesCounter++;

                currNode->push_child(rightNode);
                buildSupportList->push_back(rightNode);
            }
        }
    }

    // nodesCounter == N of nodes in the tree

    // cout all nodes
    List<TreeNode*>* supportList = new List<TreeNode*>();
    supportList->push_back(root); // first node
    int totLevelCounter = 0;
    
    Node<TreeNode*>* iter = supportList->next();
    while (!supportList->is_empty())
    {
        TreeNode* currentTreeNode = supportList->pop_front();
        // use the value of node
        // cout << currentTreeNode->getId() << "-" 
        //     << currentTreeNode->getValue() << " (" 
        //     << currentTreeNode->getLevel() << ")" << endl;
        totLevelCounter += currentTreeNode->getLevel();

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

    cout << "Nodes count: " << nodesCounter << endl;
    cout << "Direct relations: " << nodesCounter - 1 << endl;
    cout << "Total Relations: " << totLevelCounter << endl;
}
