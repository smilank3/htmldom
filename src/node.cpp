

#include <iostream>
#include "node.h"
#include "attribute.h"

Node::Node() {}
Node::Node(std::string name, std::string nType) : parentElement(nullptr), ownerDocument(nullptr), nodeName(name), parentNode(nullptr), firstChild(nullptr), lastChild(nullptr), nodeType(nType)
{
}
Node::Node(std::string name, Document *doc, std::string nType) : parentElement(nullptr), ownerDocument(doc), nodeName(name), parentNode(nullptr), firstChild(nullptr), lastChild(nullptr), nodeType(nType) {}
Node::Node(std::string name, std::string text, std::string nType) : parentElement(nullptr), ownerDocument(nullptr), nodeName(name), parentNode(nullptr), firstChild(nullptr), lastChild(nullptr), textContent(text), nodeType(nType) {}

Node::Node(std::string name, Element *el, std::string nType) : parentElement(el), ownerDocument(nullptr), nodeName(name), parentNode(nullptr), firstChild(nullptr), lastChild(nullptr), nodeType(nType) {}
Node::~Node()
{
   //std::cout << "NOde destructor called - " << nodeType + " " + "["+nodeName+"]" << std::endl;

    if (firstChild != nullptr)
    {

        delete firstChild;
        firstChild = nullptr;
    }

    if (lastChild != nullptr)
    {

        delete lastChild;
        lastChild = nullptr;
    }
}

bool Node::isSameNode(Node *a, Node *b)
{

    // check nodeName, nodeType
    if (a->nodeType == b->nodeType && a->nodeName == b->nodeName && a->textContent == b->textContent)
    {

        // check their respective attributes
        if (a->getAttributeList().size() == b->getAttributeList().size())
        {
            // loop over a attributes list
            for (unsigned long i = 0; i < a->getAttributeList().size(); i++)
            {
                // loop over b attributes list
                for (unsigned long j = 0; j < b->getAttributeList().size(); j++)
                {
                    if (a->getAttributeList()[i]->name == b->getAttributeList()[j]->name)
                    {
                        if (a->getAttributeList()[i]->value != b->getAttributeList()[j]->value)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        else
        {
            return false;
        }

        // check its childNodes
        if (a->childNodes.size() == b->childNodes.size())
        {
            for (unsigned int i = 0; i < a->childNodes.size(); i++)
            {

                for (unsigned int j = 0; j < b->childNodes.size(); j++)
                {
                    isSameNode(a->childNodes[i], b->childNodes[j]);
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}
void Node::insetBefore(Node *newNode, Node *child)
{
    unsigned index = 0;
    // check if exists
    bool exists = false;
    for (unsigned i = 0; i < childNodes.size(); i++)
    {
        if (isSameNode(child, childNodes[i]))
        {
            index = i;
            exists = true;
            break;
        }
    }
    if (exists)
    {
        newNode->parentNode = this;
        childNodes.insert(index, newNode);
        // update the firstChild and lastchild
        firstChild = childNodes.front();

        if (childNodes.size() > 1)
        {
            lastChild = childNodes.back();
        }
    }
}
Node *Node::appendChild(Node *node)
{
    // use copy constructor. here instead of this.
    //

    node->parentNode = this;
    if (this->childNodes.size() < 1)
    {
        this->firstChild = node;
    }
    else
    {
        this->lastChild = node;
    }

    Node::childNodes.push_back(node);
    return node;
}

Node *Node::replaceChild(Node *newNode, Node *child)
{
    bool exists = false;
    for (unsigned int i = 0; i < childNodes.size(); i++)
    {
        if (isSameNode(childNodes[i], child))
        {

            // parentnode
            newNode->parentNode = this;
            childNodes[i] = newNode;
            exists = true;
            break;
        }
    }
    try
    {
        if (exists)
        {
            // update

            firstChild = childNodes.front();

            if (childNodes.size() > 1)
            { // should have more than one child.
                lastChild = childNodes.back();
            }
            // lastChild = childNodes.back();
            return newNode;
        }
        else
        {
            throw std::invalid_argument("No such child Node.");
        }
    }
    catch (const std::invalid_argument &er)
    {
        std::cout << "Error : " << er.what() << std::endl;
        exit(1);
    }
}

Node *Node::removeChild(Node *child)
{

    Node *n = nullptr;
    for (unsigned int i = 0; i < this->childNodes.size(); i++)
    {
        if (isSameNode(child, childNodes[i]))
        {

            n = childNodes[i];
            childNodes.erase(i);

            return n;
        }
    }

    // update
    firstChild = childNodes.front();
    if (childNodes.size() > 1)
    {
        lastChild = childNodes.back();
    }

    return n;
}

bool Node::hasChildNodes()
{
    if (this->childNodes.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<attribute *> Node::getAttributeList()
{

    return {};
}
