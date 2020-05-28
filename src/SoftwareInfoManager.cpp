#include "SoftwareInfoManager.h"

SoftwareInfoManager::SoftwareInfoManager(std::string path)
{
  _stream.open(path);
  if (!_stream.is_open())
  {
    // TODO: throw exception
  }
}

SoftwareInfoManager::~SoftwareInfoManager()
{
  if (_stream.is_open())
  {
    _stream.close();
  }
}

std::vector<Software> SoftwareInfoManager::ReadSwInfo()
{
  std::vector<Software> list;

  return list;
}

void SoftwareInfoManager::WriteSwInfo(std::vector<Software> _swList)
{
  
}

