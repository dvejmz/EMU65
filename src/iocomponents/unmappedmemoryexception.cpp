#include "../../include/iocomponents/unmappedmemoryexception.h"

const char* UnmappedMemoryException::what()
{
  return "The virtual memory address cannot be accessed because it is unmapped.";
}
