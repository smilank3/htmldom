

#ifndef node_h
#define node_h
#include <string>
#include "HTMLDOM/nodeList.h"

class Element;
class attribute;
class Document;

class Node
{
private:
public:
    Element *parentElement;
    Document *ownerDocument;
    std::string const nodeName; // readonly
    Node *parentNode;
    NodeList childNodes;
    Node *firstChild;
    Node *lastChild;
    std::string textContent;
    std::string const nodeType; // readonly

protected:
    Node();
    Node(std::string name, std::string nType);
    Node(std::string name, Document *doc, std::string nType);
    Node(std::string name, std::string text, std::string nType);
    Node(std::string name, Element *el, std::string nType);

public:
    virtual ~Node();

    virtual void insetBefore(Node *newNode, Node *child);

    virtual Node *appendChild(Node *newNode);

    virtual Node *replaceChild(Node *newNode, Node *child);

    virtual Node *removeChild(Node *child);

    virtual bool isSameNode(Node *a, Node *b);

    virtual bool hasChildNodes();

    virtual std::vector<attribute *> getAttributeList();
};

#endif 
