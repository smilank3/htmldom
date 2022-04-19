
#include "HTMLDOM/document.h"
#include <regex>
#include <iostream>

Document::Document() : Node("#document", this, "DOCUMENT_NODE"), documentElement(nullptr), head(nullptr), body(nullptr)
{

    children.push_back(nullptr);
}

// Document::Document(Document *d) : Node("#document", d, "DOCUMENT_NODE") {}

Document::~Document()
{

    // delete head;
    //  delete body;
}
Element *Document::createElement(std::string name)
{

    Element *el = new Element(name, this);

    return el;
}

Text *Document::createTextNode(std::string data)
{
    Text *newText = new Text(data);
    return newText;
}
Element *Document::appendChild(Element *el)
{

    try
    {
        if (children[0] != nullptr)
        {
            throw std::invalid_argument("Uncaught DOMException: Failed to execute 'append' on 'Document': Only one element on document allowed.");
        }
        else
        {

            delete children[0];
            children[0] = el;
            delete documentElement;
            documentElement = el;

            if (el->children.size())
            {
                for (unsigned int i = 0; i < el->children.size(); i++)
                {

                    // inorder to access head directly from document level
                    // "head" must be the child of "html"
                    // in fact "head" must be first child of "html"
                    // and "body" must be second child of "html"
                    // else "head" or "body" cannot be access directly from document level.
                    if (el->children[i]->tagName == "head" && i == 0 && el->tagName == "html")
                    {

                        delete head;
                        head = el->children[i];
                    }

                    if (el->children[i]->tagName == "body" && i == 1 && el->tagName == "html")
                    {

                        delete body;
                        body = el->children[i];
                    }
                }
            }
            Node::appendChild(el);
        }
        return el;
    }
    catch (const std::invalid_argument &er)
    {
        std::cout << "Error: " << er.what() << std::endl;
        exit(1);
    }
}

HTMLCollection Document::getElementById(std::string id)
{
    HTMLCollection elements;

    searchById(children[0], elements, id);

    return elements;
}

HTMLCollection Document::getElementByTagName(std::string tagName)
{
    HTMLCollection elements;

    std::cout << children[0]->tagName << std::endl;
    searchByTagName(children[0], elements, tagName);

    return elements;
}
HTMLCollection Document::getElementByClassName(std::string className)
{
    HTMLCollection elements;

    searchByClassName(children[0], elements, className);

    return elements;
}

Element *Document::querySelector(std::string query)
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
    }
    else /*if (include_(query, htmlTags()))*/
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
        return new Element("null");
    }
}

HTMLCollection Document::querySelectorAll(std::string query)
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
    }
    else /*if (include_(query, htmlTags()))*/
    {

        for (unsigned int i = 0; i < children.size(); i++)
        {

            searchByTagName(children[i], elements, query);
        }
    }

    return elements;
}
