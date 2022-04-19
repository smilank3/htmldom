#ifndef TEXT_H
#define TEXT_H

#include "characterdata.h"
class Text : public CharacterData
{

public:
    std::string wholeText;
    Text();
    Text(std::string text);
    ~Text() override;
};

#endif
