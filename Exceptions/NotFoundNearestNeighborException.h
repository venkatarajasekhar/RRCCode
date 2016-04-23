#ifndef NOTFOUNDNEARESTNEIGHBOREXCEPTION_H
#define NOTFOUNDNEARESTNEIGHBOREXCEPTION_H

#include <stdexcept>

class NotFoundNearestNeighborException : public std::exception
{
public:
    NotFoundNearestNeighborException();
    virtual const char *what() const noexcept;
};

#endif // NOTFOUNDNEARESTNEIGHBOREXCEPTION_H
