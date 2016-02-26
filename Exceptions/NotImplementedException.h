#ifndef NOTIMPLEMENTEDEXCEPTION_H
#define NOTIMPLEMENTEDEXCEPTION_H

#include <exception>

class NotImplementedException : public std::exception
{
public:
    NotImplementedException();
    virtual const char *what() const noexcept;
};

#endif // NOTIMPLEMENTEDEXCEPTION_H
