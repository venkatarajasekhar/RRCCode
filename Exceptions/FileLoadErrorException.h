#ifndef FILELOADERROREXCEPTION_H
#define FILELOADERROREXCEPTION_H
#include <exception>

class FileLoadErrorException : public std::exception
{
public:
  FileLoadErrorException();
  virtual const char* what() const throw();
};

#endif // FILELOADERROREXCEPTION_H
