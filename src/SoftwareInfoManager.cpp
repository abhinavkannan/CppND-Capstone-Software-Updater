#include <sstream>
#include "SoftwareInfoManager.h"

SoftwareInfoManager::SoftwareInfoManager()
{
}

SoftwareInfoManager::~SoftwareInfoManager()
{
  if (_stream.is_open())
  {
    _stream.close();
  }
}

std::vector<std::string> tokenizer_helper(std::string line, char delim) {
  std::vector<std::string> tokens{};
  std::string token;

  std::stringstream ss(line);
  while (std::getline(ss, token, delim)) {
	tokens.push_back(token);
  }

  return tokens;
}

std::vector<Software> SoftwareInfoManager::ReadSwInfo(std::string path)
{
  std::vector<Software> list;
  std::string line;

  _stream.open(path);
  if (!_stream.is_open())
  {
	throw std::system_error(errno, std::system_category(), "failed to open " + path);
  }
  else
  {
	while (std::getline(_stream, line))
	{
	  std::vector<std::string> tokens = tokenizer_helper(line, ',');
	  Software sw(tokens[0], tokens[1], tokens[2]);
	  list.push_back(std::move(sw));
	}
  }

  return list;
}

void SoftwareInfoManager::WriteSwInfo(std::string path, std::vector<Software> swList)
{
  if (!_stream.is_open())
  {
	// TODO: throw exception
  }
  else
  {
	for (std::size_t i = 0; i < swList.size(); i++)
	{
	  _stream << swList[i].GetName() << "," << swList[i].GetVersion() << "," << swList[i].GetDate() << std::endl;
	}
  }
}

