#ifndef FILELOADERROREXCEPTION_H
#define FILELOADERROREXCEPTION_H
#include <exception>

class FileLoadErrorException : public std::exception
{
public:
  FileLoadErrorException();
  virtual const char* what() const noexcept;
};

#endif // FILELOADERROREXCEPTION_H
