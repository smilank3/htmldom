/*
   ATTRIBUTE
*/
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "node.h"

class attribute : public Node
{
public:
    std::string localName;
    std::string name;
    std::string value;
    Element *ownerElement;

    attribute(std::string n, std::string v);

    ~attribute() override;
};

#endif /* attribute_h */
