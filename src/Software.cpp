#include "Software.h"

Software::Software(std::string name, std::string version, std::string date)
{

}

Software::~Software()
{

}

std::string Software::GetName()
{
  return _name;
}
  
std::string Software::GetVersion()
{
  return _version;
}

std::string Software::GetDate()
{
  return _date;
}