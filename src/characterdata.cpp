#include "characterdata.h"

CharacterData::CharacterData(std::string text) : Node("#text", text, "TEXT_NODE"), data(text) {}
void CharacterData::appendData(std::string text)
{
    data.append(text);
}
CharacterData::~CharacterData()
{
}
