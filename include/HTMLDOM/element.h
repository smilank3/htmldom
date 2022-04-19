

#ifndef ELEMENT_H
#define ELEMENT_H

#include "../../src/attribute.h"
#include "htmlCollection.h"

class Node;//

class Element : public Node
{
private:
    std::string r_id;
    std::string r_class;

public:
    std::vector<attribute *> attributes;
    std::string localName;
    std::string tagName;
    const std::string &id = r_id;
    const std::string &className = r_class;
    HTMLCollection children;

    //Element();
    Element(std::string name);
    Element(std::string name, Document *doc);

    virtual ~Element() override;
    bool hasAttributes();

    bool hasAttribute(std::string name);

    std::vector<std::string> getAttributeName();

    std::string getAttribute(std::string name);

    void setAttribute(std::string name, std::string value);

    void removeAttribute(std::string name);

    using Node::appendChild;
    Element *appendChild(Element *element);

    HTMLCollection getElementByTagName(std::string tagName);

    HTMLCollection getElementByClassName(std::string className);

    Element *querySelector(std::string query);

    HTMLCollection querySelectorAll(std::string query);

    std::vector<attribute *> getAttributeList() override
    {
        return attributes;
    }
};

#endif

