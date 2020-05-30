#include "Software.h"

Software::Software() : _name(""), _version(""), _date("")
{
}

Software::Software(std::string name, std::string version, std::string date)
  : _name(name), _version(version), _date(date)
{
}

Software::Software(const Software &source)
{
  _name = source._name;
  _version = source._version;
  _date = source._date;
}

Software& Software::operator=(const Software &source)
{
  if (this == &source)
  {
	return *this;
  }

  _name = source._name;
  _version = source._version;
  _date = source._date;

  return *this;
}

Software::Software(Software &&source)
{
  _name = source._name;
  _version = source._version;
  _date = source._date;

  source._name.clear();
  source._version.clear();
  source._date.clear();
}

Software& Software::operator=(Software &&source)
{
  if (this == &source)
  {
	return *this;
  }

  _name = source._name;
  _version = source._version;
  _date = source._date;

  source._name.clear();
  source._version.clear();
  source._date.clear();

  return *this;
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