#ifndef NOTFOUNDNEARESTNEIGHBOREXCEPTION_H
#define NOTFOUNDNEARESTNEIGHBOREXCEPTION_H

#include <stdexcept>

class NotFoundNearestNeighborException : public std::exception
{
public:
    NotFoundNearestNeighborException();
    const char *what();
};

#endif // NOTFOUNDNEARESTNEIGHBOREXCEPTION_H
