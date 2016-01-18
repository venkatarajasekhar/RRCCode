#include "FileLoadErrorException.h"

FileLoadErrorException::FileLoadErrorException() {

}

const char *FileLoadErrorException::what() const throw() {
    return "File load error exception thrown!";
}

