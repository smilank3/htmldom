

#ifndef UTILS_H
#define UTILS_H


#include "HTMLDOM/element.h"
#include "node.h"

extern bool include_(std::string s, const std::vector<std::string> arr);

extern void join_(const std::vector<std::string> &htmlArray, std::string &htmlString);

extern void searchByTagName(Element *el, HTMLCollection &elArray, std::string tag);

extern void searchById(Element *el, HTMLCollection &elArray, std::string id);

extern void searchByClassName(Element *el, HTMLCollection &elArray, std::string className);
extern void searchByAttribute(Element *el, HTMLCollection &elArray, std::string attribute);


//extern std::vector<std::string> htmlTags();
extern std::string HTML(Node *node);
extern void DOMTREE(Node *node);

#endif /* utils_hpp */
