#ifndef SOFTWARE_INFO_MANAGER_H_
#define SOFTWARE_INFO_MANAGER_H_

#include <fstream>
#include <vector>
#include "Software.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
constexpr auto AVAILABLE_SOFTWARES_FILE = "..\\files\\available_sw_list.txt";
constexpr auto TEMP_AVAILABLE_SOFTWARES_FILE = "..\\files\\available_sw_list_temp.txt";
constexpr auto INSTALLED_SOFTWARES_FILE = "..\\files\\installed_sw_list.txt";
constexpr auto TEMP_INSTALLED_SOFTWARES_FILE = "..\\files\\installed_sw_list_temp.txt";
#else
constexpr auto AVAILABLE_SOFTWARES_FILE = "../files/available_sw_list.txt";
constexpr auto TEMP_AVAILABLE_SOFTWARES_FILE = "../files/available_sw_list_temp.txt";
constexpr auto INSTALLED_SOFTWARES_FILE = "../files/installed_sw_list.txt";
constexpr auto TEMP_INSTALLED_SOFTWARES_FILE = "../files/installed_sw_list_temp.txt";
#endif

class SoftwareInfoManager
{
public:
  SoftwareInfoManager(std::string path, std::string tempPath);
  ~SoftwareInfoManager();

  std::vector<Software> ReadSwInfo();
  void WriteSwInfo(std::vector<Software> swList);
  void Close();

private:
  std::ifstream _readStream;
  std::ofstream _writeStream;
  std::string   _readPath;
  std::string   _writePath;
  bool          _shouldRename;
};

#endif /* SOFTWARE_INFO_MANAGER_H_ */