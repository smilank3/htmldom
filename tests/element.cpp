#include "doctest/doctest.h"

#include "HTMLDOM/element.h"

TEST_CASE("Element")
{
    Element *el = new Element("div");

    el->appendChild(new Element("p"));
    el->appendChild(new Element("span"));
    el->appendChild(new Element("strong"));

    CHECK(el->hasAttributes() == false);
    CHECK(el->hasAttribute("_fakeId") == false);
    CHECK(el->firstChild->nodeName == "p");
    CHECK(el->lastChild->nodeName == "strong");
    CHECK(el->childNodes.size() == 3);
    CHECK(el->children.size() == 3);
    CHECK(el->querySelectorAll("p").size() == 1);

    delete el;
}
