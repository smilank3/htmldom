
#ifndef DOCUMENT_H
#define DOCUMENT_H


#include "element.h"
#include "../../src/text.h"
#include "../../src/utils.h"
class Node;
class attribute;
class Document : public Node
{
public:
    HTMLCollection children;
    Element *documentElement = children[0];
    Element *head;
    Element *body;

public:
    Document();
    //Document(Document *d);
    virtual ~Document() override;

    using Node::appendChild;
    Element *appendChild(Element *el);

    attribute createAttribute(std::string key); 

    Element *createElement(std::string name);

    Text *createTextNode(std::string data);

    HTMLCollection getElementById(std::string id);

    HTMLCollection getElementByClassName(std::string className);

    Element *querySelector(std::string query);

    HTMLCollection querySelectorAll(std::string query);

    HTMLCollection getElementByTagName(std::string tagName);
};

#endif
