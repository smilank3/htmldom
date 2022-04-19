

#ifndef HTMLCOLLECTION_H
#define HTMLCOLLECTION_H

class Element;
class HTMLCollection
{
private:
    std::vector<Element *> elements;

public:
    Element *&operator[](size_t index)
    {
        return elements.at(index);
    }

    void push_back(Element *e)
    {

        elements.push_back(e);
    }
    void insert(int index, Element *element)
    {

        elements.insert(elements.begin() + index, element);
    }
    void erase(int index)
    {
        elements.erase(elements.begin() + index);
    }

    Element *front()
    {
        return elements.front();
    }
    Element *back()
    {
        return elements.back();
    }

    void clear()
    {
        elements.clear();
    }

    size_t size()
    {
        return static_cast<size_t>(elements.size());
    }
};

#endif 
