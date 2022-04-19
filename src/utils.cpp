
#include "utils.h"
#include <iostream>
#include "text.h"
bool include_(std::string s, const std::vector<std::string> arr)
{

    for (unsigned int i = 0; i < arr.size(); i++)
    {

        if (arr[i] == s)
        {

            return true;
        }
    }

    return false;
}

void join_(const std::vector<std::string> &htmlArray, std::string &htmlString)
{

    htmlString.clear();

    for (std::vector<std::string>::const_iterator p = htmlArray.begin();
         p != htmlArray.end(); ++p)
    {
        htmlString += *p;
        if (p != htmlArray.end() - 1)
            htmlString += ' ';
    }
}

// check if its null tree, node, doc

void searchByTagName(Element *el, HTMLCollection &elArray, std::string tag)
{

    if (el->tagName == tag)
    {
        elArray.push_back(el);
    }
    else
    {

        if (el->children.size())
        {
            for (unsigned int i = 0; i < el->children.size(); i++)
            {
                searchByTagName(el->children[i], elArray, tag);
            }
        }
    }
}
void searchById(Element *el, HTMLCollection &elArray, std::string id)
{

    if (el->getAttribute("id") == id)
    {
        elArray.push_back(el);
    }
    else
    {
        if (el->children.size())
        {
            for (unsigned int i = 0; i < el->children.size(); i++)
            {
                searchById(el->children[i], elArray, id);
            }
        }
    }
}
void searchByClassName(Element *el, HTMLCollection &elArray, std::string className)
{

    if (el->getAttribute("class") == className)
    {

        elArray.push_back(el);
    }
    else
    {
        if (el->children.size())
        {
            for (unsigned int i = 0; i < el->children.size(); i++)
            {
                searchByClassName(el->children[i], elArray, className);
            }
        }
    }
}

void searchByAttribute(Element *el, HTMLCollection &elArray, std::string attribute)
{

    if (el->hasAttribute(attribute))
    {

        elArray.push_back(el);
    }
    else
    {
        if (el->children.size())
        {

            for (unsigned int i = 0; i < el->children.size(); i++)
            {
                searchByAttribute(el->children[i], elArray, attribute);
            }
        }
    }
}


// html
static void _html(Node *node, std::vector<std::string> &htmlArray, std::vector<std::string> &position, std::string &currentTag)
{

    // opening Tag.
     if (node->nodeType=="ELEMENT_NODE")// must be a ELEMENT_NODE, if TEXT_NODE ignore,(#text)
    {
    htmlArray.push_back("\n");
    for (unsigned int k = 0; k < position.size(); k++)
    {

        htmlArray.push_back(" ");
    }
    htmlArray.push_back("<" + node->nodeName);

    for (unsigned int j = 0; j < node->getAttributeList().size(); j++)
    {

        htmlArray.push_back(" " + node->getAttributeList()[j]->name + "=" + "\"" + node->getAttributeList()[j]->value + "\"");
    }

    htmlArray.push_back(">");
    }
    if (!node->textContent.empty() && node->nodeType == "TEXT_NODE")
    {
        htmlArray.push_back("\n");
        for (auto i : position)
        {
            htmlArray.push_back(" ");
        }
        htmlArray.push_back(node->textContent);
        position.pop_back();
    }
    else if (!node->textContent.empty())
    {
        // create textnode, #text: for display
        Node *t = new Text(node->textContent);
        position.push_back(" ");
        _html(t, htmlArray, position, currentTag);
        position.pop_back();
        // position.pop_back();
        delete t;
    }

    // loop over the children

    for (unsigned int i = 0; i < node->childNodes.size(); i++)
    {
        position.push_back(" ");
        _html(node->childNodes[i], htmlArray, position, currentTag);

        if (node->childNodes[i]->parentElement)
        {
            currentTag = node->childNodes[i]->parentNode->nodeName;
        }

        if (node->childNodes[i]->parentElement)
        {
            if (node->childNodes[i]->parentNode->nodeName == currentTag)
            {
                if (position.size())
                {
                    position.pop_back();
                }
            }
        }
    }

    // closing Tag
    if (node->nodeType=="ELEMENT_NODE")  // must be a ELEMENT_NODE, 
    {
        htmlArray.push_back("\n");
        for (unsigned int k = 0; k < position.size(); k++)
        {

            htmlArray.push_back(" ");
        }
        htmlArray.push_back("</" + node->nodeName + ">");
    }
}

// print html
std::string HTML(Node *node)
{
    std::vector<std::string> position;
    std::string currentTag;

    std::vector<std::string> htmlArray;
    std::string htmlString;

    _html(node, htmlArray, position, currentTag);

    join_(htmlArray, htmlString);

    return htmlString;
}

// print tree
static void printTree(Node *node, std::vector<std::string> &position, std::string &currentTag)
{
    std::cout << "\n ";

    for (unsigned int k = 0; k < position.size(); k++)
    {

        std::cout << " |-";
    }
    std::cout << node->nodeName;

    for (unsigned int j = 0; j < node->getAttributeList().size(); j++)
    {
        std::cout << " " + node->getAttributeList()[j]->name + "=" + "\"" + node->getAttributeList()[j]->value + "\"";
    }

    if (!node->textContent.empty() && node->nodeType == "TEXT_NODE")
    {

        std::cout << " : " + node->textContent;
        position.pop_back();
    }
    else if (!node->textContent.empty())
    {
        // create textnode, #text: for display
        Node *t = new Text(node->textContent);
        position.push_back(" ");
        printTree(t, position, currentTag);
        position.pop_back();
        // position.pop_back();
        delete t;
    }

    for (unsigned int i = 0; i < node->childNodes.size(); i++)
    {

        position.push_back(" ");
        printTree(node->childNodes[i], position, currentTag);

        if (node->childNodes[i]->parentElement)
        {
            currentTag = node->childNodes[i]->parentNode->nodeName;
        }

        if (node->childNodes[i]->parentElement)
        {
            if (node->childNodes[i]->parentNode->nodeName == currentTag)
            {
                if (position.size())
                {
                    position.pop_back();
                }
            }
        }
    }
}

// Print DOMTREE
void DOMTREE(Node *node)
{
    std::vector<std::string> position;
    std::string currentTag;

    printTree(node, position, currentTag);
    std::cout << "\n\n\n";
}

/*
std::vector<std::string> htmlTags()
{
    std::vector<std::string> tag = {
        "a",
        "abbr",
        "acronym",
        "address",
        "applet",
        "area",
        "article",
        "aside",
        "audio",
        "b", "base", "basefont", "bdi", "bdo",
        "bgsound",
        "big",
        "blink",
        "blockquote",
        "body",
        "br",
        "button",
        "canvas",
        "caption",
        "center",
        "cite",
        "code",
        "col",
        "colgroup",
        "content",
        "data",
        "datalist",
        "dd",
        "decorator",
        "del",
        "details",
        "dfn",
        "dir",
        "div",
        "dl",
        "dt",
        "element",
        "em",
        "embed",
        "fieldset",
        "figcaption",
        "figure",
        "font",
        "footer",
        "form",
        "frame",
        "frameset",
        "h1",
        "h2",
        "h3",
        "h4",
        "h5",
        "h6",
        "head",
        "header",
        "hgroup",
        "hr",
        "html",
        "i",
        "iframe",
        "img",
        "input",
        "ins",
        "isindex",
        "kbd",
        "keygen",
        "label",
        "legend",
        "li",
        "link",
        "listing",
        "main",
        "map",
        "mark",
        "marquee",
        "menu",
        "menuitem",
        "meta",
        "meter",
        "nav",
        "nobr",
        "noframes",
        "noscript",
        "object",
        "ol",
        "optgroup",
        "option",
        "output",
        "p",
        "param",
        "plaintext",
        "pre",
        "progress",
        "q",
        "rp",
        "rt",
        "ruby",
        "s",
        "samp",
        "script",
        "section",
        "select",
        "shadow",
        "small",
        "source",
        "spacer",
        "span",
        "strike",
        "strong",
        "style",
        "sub",
        "summary",
        "sup",
        "table",
        "tbody",
        "td",
        "template",
        "textarea",
        "tfoot",
        "th",
        "thead",
        "time",
        "title",
        "tr",
        "track",
        "tt",
        "u",
        "ul",
        "var",
        "video",
        "wbr",
        "xmp"};
    return tag;
}
*/

