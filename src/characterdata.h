
#ifndef CHARATERDATA_H
#define CHARATERDATA_H

#include "node.h"
class CharacterData : public Node
{
private:
    std::string data;

public:
    CharacterData();
    CharacterData(std::string text);

    void appendData(std::string text);
    ~CharacterData() override;
};

#endif
