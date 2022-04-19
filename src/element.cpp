

#include "HTMLDOM/element.h"
#include "HTMLDOM/document.h"
#include "utils.h"
#include <regex>
#include <iostream>
//#include "exception.h"

//Element::Element() : Node("null", "ELEMENT_NODE") {}

Element::Element(std::string name) : Node(name, "ELEMENT_NODE"), localName(name), tagName(name)
{
}

Element::Element(std::string name, Document *doc) : Node(name, doc, "ELEMENT_NODE"), localName(name), tagName(name)
{
}
Element::~Element() {}
Element *Element::appendChild(Element *element)
{

    if (element->ownerDocument != nullptr)
    {

        if (element->ownerDocument->children[0] != nullptr)
        {

            if (element->ownerDocument->children[0]->tagName == "html" && element->tagName == "head")
            {

                element->parentElement = element->ownerDocument->children[0];
                element->ownerDocument->head = element;
                element->ownerDocument->children[0]->children.push_back(element);
            }
            else if (element->ownerDocument->children[0]->tagName == "html" && element->tagName == "body" && element->ownerDocument->children[0]->children[0]->tagName == "head")
            {
                // element must be child of "html" and it's first child must be "head".
                element->parentElement = element->ownerDocument->children[0];
                element->ownerDocument->body = element;
                element->ownerDocument->children[0]->children.push_back(element);
            }
            else
            {

                element->parentElement = this;
                children.push_back(element);
                // childNodes.
                Node::appendChild(element);
                /*
                                try
                                {
                                    if (this != nullptr)
                                    {
                                        children.push_back(element);
                                        // childNodes.
                                        Node::appendChild(element);
                                    }
                                    else
                                    {
                                        throw std::runtime_error(" Element is not defined");
                                    }
                                }
                                catch (const std::runtime_error &er)
                                {
                                    std::cout << "Uncaught ReferenceError:: " << er.what() << std::endl;
                                    exit(1);
                                }

                                */
            }
        }
        else
        {

            element->parentElement = this;

            this->children.push_back(element);
            // childNodes.
            Node::appendChild(element);
        }
    }
    else
    {

        element->parentElement = this;

        this->children.push_back(element);
        // childNodes.
        Node::appendChild(element);
    }

    return element;
}

HTMLCollection Element::getElementByTagName(std::string tag)
{
    HTMLCollection elements;

    for (unsigned int i = 0; i < children.size(); i++)
    {
        searchByTagName(children[i], elements, tag);
    }

    return elements;
}
HTMLCollection Element::getElementByClassName(std::string _className)
{
    HTMLCollection elements;

    for (unsigned int i = 0; i < children.size(); i++)
    {
        searchByClassName(children[i], elements, _className);
    }

    return elements;
}

Element *Element::querySelector(std::string query)
{
    HTMLCollection elements;
    // lookup on children with the tagName
    // return new array with the tagName similar.
    std::string &_query = query;
    if (std::regex_search(query, std::regex("^\\.")))
    {

        _query.erase(0, 1);
        for (unsigned int i = 0; i < children.size(); i++)
        {

            searchByClassName(children[i], elements, _query);
        }
    }
    else if (std::regex_search(query, std::regex("^#")))
    {
           // if start wit "#" search by Id.
        _query.erase(0, 1);
        for (unsigned int i = 0; i < children.size(); i++)
        {

            searchById(children[i], elements, _query);
        }
    }
    
    else if (std::regex_search(query, std::regex("^\\[+.+\\]$")))
    {

        _query.erase(0, 1);
        _query.erase(query.size() - 1);

        for (unsigned int i = 0; i < children.size(); i++)
        {

            searchByAttribute(children[i], elements, _query);
        }
    }else /*if (include_(query, htmlTags())) it must be tag*/
    {

        for (unsigned int i = 0; i < children.size(); i++)
        {

            searchByTagName(children[i], elements, query);
        }
    }

    if (elements.size())
    {
        return elements[0];
    }
    else
    {
        return nullptr;
    }
}

HTMLCollection Element::querySelectorAll(std::string query)
{
    HTMLCollection elements;
    // lookup on children with the tagName
    // return new array with the tagName similar.
    std::string &_query = query;
    if (std::regex_search(query, std::regex("^\\.")))
    {

        _query.erase(0, 1);
        for (unsigned int i = 0; i < children.size(); i++)
        {

            searchByClassName(children[i], elements, _query);
        }
    }
    else if (std::regex_search(query, std::regex("^#")))
    {

        _query.erase(0, 1);
        for (unsigned int i = 0; i < children.size(); i++)
        {

            searchById(children[i], elements, _query);
        }
    }
   
    else if (std::regex_search(query, std::regex("^\\[+.+\\]$")))
    {
        _query.erase(0, 1);
        _query.erase(query.size() - 1);

        for (unsigned int i = 0; i < children.size(); i++)
        {

            searchByAttribute(children[i], elements, _query);
        }
    } else/* if (include_(query, htmlTags()))*/
    {

        for (unsigned int i = 0; i < children.size(); i++)
        {

            searchByTagName(children[i], elements, query);
        }
    }

    return elements;
}
bool Element::hasAttributes()
{
    // lokk for attribute in attributes
    if (attributes.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Element::hasAttribute(std::string name)
{
    for (unsigned long i = 0; i < attributes.size(); i++)
    {
        if (attributes[i]->name == name)
        {
            return true;
        }
    }

    return false;
}

std::vector<std::string> Element::getAttributeName()
{
    std::vector<std::string> t;

    return t;
}

std::string Element::getAttribute(std::string name)
{

    if (name == "id")
    {
        return id;
    }
    else if (name == "class")
    {
        return className;
    }
    else
    {
        bool exists = false;
        unsigned long index = 0;
        for (unsigned int i = 0; i < attributes.size(); i++)
        {
            if (attributes[i]->name == name)
            {
                exists = true;
                index = i;
            }
        }
        if (exists)
        {
            return attributes[index]->value;
        }
        else
        {
            return "null";
        }
    }
}

void Element::setAttribute(std::string name, std::string value)
{

    bool exists = false;

    try
    {
        if (std::regex_search(name, std::regex("^[0-9]")))
        {
            throw std::invalid_argument(" Failed to execute 'setAttribute' on 'Element'. Not a valid attribute name: ");
        }
    }
    catch (const std::invalid_argument &er)
    {
        std::cout << "Error: " << er.what() << std::endl;
        exit(1);
    }

    for (unsigned int i = 0; i < attributes.size(); i++)
    {
        if (attributes[i]->name == name)
        {
            exists = true;
            std::cout << "existss" << std::endl;
            attributes[i]->value = value;
        }
    }
    if (!exists)
    {
        if (name == "id")
        {
            r_id = value;
        }
        else if (name == "class")
        {
            r_class = value;
        }
        attributes.push_back(new attribute(name, value));
    }
}
void Element::removeAttribute(std::string name)
{

    bool exists = false;
    unsigned index = 0;
    for (unsigned int i = 0; i < attributes.size(); i++)
    {
        if (attributes[i]->name == name)
        {
            exists = true;
            index = i;
        }
    }
    if (exists)
    {
        if (name == "id")
        {
            r_id = " ";
        }
        else if (name == "className")
        {
            r_class = " ";
        }

        attributes.erase(attributes.begin() + index);
    }
}
