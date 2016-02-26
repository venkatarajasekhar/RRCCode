#include "NotImplementedException.h"

NotImplementedException::NotImplementedException()
{

}

const char *NotImplementedException::what() const noexcept
{
    return "Not implemented exception thrown!";
}

