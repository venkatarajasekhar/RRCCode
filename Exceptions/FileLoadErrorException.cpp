#include "FileLoadErrorException.h"

FileLoadErrorException::FileLoadErrorException() {

}

const char *FileLoadErrorException::what() const noexcept {
    return "File load error exception thrown!";
}

