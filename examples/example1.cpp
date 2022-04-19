


#include <iostream>

#include <HTMLDOM/document.h>
#include <HTMLDOM/element.h>
#include <HTMLDOM/htmlCollection.h>



int main()
{


  Document *document = new Document();
  Element *html = document->createElement("html");

  Element *head = document->createElement("head");
  Element *title = document->createElement("title");

  title->appendChild(document->createTextNode("HTML Title"));

  head->appendChild(title);
  html->appendChild(head);

  html->appendChild(document->createElement("body"));
  // append html root;
  document->appendChild(html);

  // create new Element;
  Element *main = document->createElement("div");
  main->setAttribute("id", "_main");
  main->setAttribute("onclick", "()=>alert('hello')");
  // append main to body.
  document->body->appendChild(main);
  // append new element div to body
  document->body->appendChild(document->createElement("div"));
  // append <p> to body.
  document->body->appendChild(document->createElement("p"));
  // assign textcontent to p
  document->body->children[2]->textContent = "This is Paragraph inside BODY.";

  // append child to main Element.
  main->appendChild(document->createElement("p"));
  // append textNode to p;
  main->children[0]->appendChild(document->createTextNode("This is paragraph inside main div of BODY."));
  main->appendChild(document->createElement("div"));
  main->appendChild(document->createElement("p"));
  

  // replace child.
  Element *strongP = document->createElement("strong");
  strongP->appendChild(document->createTextNode("This is strong Text."));
  strongP->setAttribute("class", "_strong");

// main->replaceChild(strongP, main->childNodes[1]);


  //-------------- print html string --------------//
  std::string outputHtml = HTML(document);
  std::cout << outputHtml <<std::endl;


  // ----------------Print DOM Tree document-------------------------------//
  DOMTREE(document);


  // ----- DOM TREE of Element ------//
  DOMTREE(main);
 
 // main element list "P"
 HTMLCollection main_p=main->querySelectorAll("p");

 for(size_t i=0;i<main_p.size();i++){
   std::cout<<"elment list : "+ main_p[i]->tagName<<std::endl;
 }
// set attribute to first child of main
main_p[1]->setAttribute("class","_p_class_test");


// querySelector 
// get first element;
Element * main_firstChild = main->querySelector("p");
// set attribute to first "p" of "main"
main_firstChild->setAttribute("id","_first_p");

// view modified DOM Tree.
 DOMTREE(main);




 delete document;


  return 0;
}
