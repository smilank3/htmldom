
#include "HTMLDOM/nodeList.h"


NodeList::~NodeList()
{
}
Node *&NodeList::operator[](size_t index)
{

    return nodes.at(index);
}

void NodeList::push_back(Node *e)
{
    nodes.push_back(e);
}

