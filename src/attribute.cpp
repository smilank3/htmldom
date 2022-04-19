
#include "attribute.h"

attribute::attribute(std::string n, std::string v) : Node("#attribute", "ATTRIBUTE_NODE"), localName(n), name(n), value(v), ownerElement(nullptr) {}

attribute::~attribute()
{
}
