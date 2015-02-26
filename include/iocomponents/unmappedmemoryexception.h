#ifndef UNMAPPEDMEMORYEXCEPION_H
#define UNMAPPEDMEMORYEXCEPTION_H

#include <exception>

class UnmappedMemoryException : public std::exception
{
public:
  const char* what();
private:
};

#endif /* UNMAPPEDMEMORYEXCEPTION_H */
