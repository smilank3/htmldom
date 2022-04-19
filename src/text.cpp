#include "text.h"

Text::Text(std::string text) : CharacterData(text), wholeText(text) {}
Text::~Text()
{
}
