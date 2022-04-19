

#ifndef NODELIST_H
#define NODELIST_H


#include <vector>

class Node;
class NodeList
{
private:
    std::vector<Node *> nodes;

public:
    NodeList() {}

    ~NodeList();
    Node *&operator[](size_t index);

    void push_back(Node *e);
    void insert(unsigned int index, Node *node)
    {

        nodes.insert(nodes.begin() + index, node);
    }
    void erase(unsigned int  index)
    {
        nodes.erase(nodes.begin() + index);
    }

    Node *front()
    {
        return nodes.front();
    }
    Node *back()
    {
        return nodes.back();
    }

    void clear()
    {
        nodes.clear();
    }

   size_t size()
    {
        return static_cast<size_t>(nodes.size());
    }
};

#endif /* nodeList_h */
