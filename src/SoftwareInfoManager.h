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
  SoftwareInfoManager();
  ~SoftwareInfoManager();

  std::vector<Software> ReadSwInfo(std::string path);
  void WriteSwInfo(std::string path, std::vector<Software> swList);

private:
  std::fstream _stream;
  std::fstream _tempStream;
};

#endif /* SOFTWARE_INFO_MANAGER_H_ */