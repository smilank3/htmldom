
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class DomException : public std::runtime_error
{
public:
    const std::string type;
    const std::string message;

    DomException(const std::string &_type, const std::string &_message)
        : std::runtime_error("DOMException."), type(_type), message(_message) {}

    ~DomException() override;
};

#endif
