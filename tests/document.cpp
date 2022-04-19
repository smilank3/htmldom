
#include "doctest/doctest.h"
#include "HTMLDOM/document.h"
#include "HTMLDOM/element.h"

TEST_CASE("Document")
{
    Document* document=new Document();

    CHECK(document->createElement("div")->tagName=="div");
    CHECK(document->head==nullptr);
    CHECK(document->body==nullptr);

    document->appendChild(document->createElement("html"));
    
    CHECK(document->children.size()==1);
    document->children[0]->appendChild(document->createElement("head"));
    document->children[0]->appendChild(document->createElement("body"));

    CHECK(document->head->tagName=="head");
    CHECK(document->body->tagName=="body");
    CHECK(document->head->children.size()==0);
    CHECK(document->body->children.size()==0);


    Element * element_1= document->createElement("div");
    element_1->setAttribute("id","element_1");

    Element* element_2 =document->createElement("p");

    element_1->appendChild(element_2);

    document->body->appendChild(element_1);

    CHECK(document->body->children.size()==1);

    CHECK(document->body->children[0]->tagName=="div");

    CHECK(document->body->children[0]->hasAttribute("id")==true);
    
    CHECK(element_1->hasAttribute("id")==true);
    CHECK(document->body->children[0]->getAttribute("id")=="element_1");

    CHECK(document->body->children[0]->hasAttribute("class")==false);



    element_2->appendChild(document->createTextNode("This is text."));

    CHECK(document->body->children[0]->children[0]->hasChildNodes()==true);

     CHECK(document->body->children[0]->children[0]->childNodes[0]->textContent=="This is text.");

   
    




    delete document;
}
