#include <sstream>
#include <stdio.h>
#include <wx/log.h>
#include "SoftwareInfoManager.h"

SoftwareInfoManager::SoftwareInfoManager(std::string path, std::string tempPath)
  : _readStream(path, std::ifstream::in),
	_writeStream(tempPath, std::ofstream::out | std::ofstream::trunc),
	_readPath(path),
	_writePath(tempPath)
{
  if (!_readStream.is_open())
  {
	throw std::system_error(errno, std::system_category(), "failed to open " + path);
  }

  if (!_writeStream.is_open())
  {
	throw std::system_error(errno, std::system_category(), "failed to open " + tempPath);
  }

  _shouldRename = false;
}

SoftwareInfoManager::~SoftwareInfoManager()
{
}

void SoftwareInfoManager::Close()
{
  if (_readStream.is_open())
  {
	_readStream.close();
  }

  if (_writeStream.is_open())
  {
	_writeStream.close();
  }

  if (_shouldRename)
  {
	// Remove read file
	remove(_readPath.c_str());

	// Rename write file as read file
	rename(_writePath.c_str(), _readPath.c_str());
  }
}

std::vector<std::string> tokenizer_helper(std::string line, char delim)
{
  std::vector<std::string> tokens{};
  std::string token;

  std::stringstream ss(line);
  while (std::getline(ss, token, delim)) {
	tokens.push_back(token);
  }

  return tokens;
}

void SoftwareInfoManager::ReadSwInfo(std::vector<Software> &list)
{
  std::string line;
 
  while (std::getline(_readStream, line))
  {
	std::vector<std::string> tokens = tokenizer_helper(line, ',');
	Software sw(tokens[0], tokens[1], tokens[2]);
	list.push_back(std::move(sw));
  }
}

void SoftwareInfoManager::WriteSwInfo(std::vector<Software> swList)
{
  if (swList.size() == 0)
  {
	return;
  }

  for (std::size_t i = 0; i < swList.size(); i++)
  {
	_writeStream << swList[i].GetName() << "," << swList[i].GetVersion() << "," << swList[i].GetDate() << std::endl;
  }

  _shouldRename = true;
}

