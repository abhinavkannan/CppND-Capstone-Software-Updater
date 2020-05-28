#ifndef SOFTWARE_INFO_MANAGER_H_
#define SOFTWARE_INFO_MANAGER_H_

#include <fstream>
#include <vector>
#include "Software.h"

constexpr auto AVAILABLE_SOFTWARES_FILE = "AvailableSoftwaresList.txt";
constexpr auto TEMP_AVAILABLE_SOFTWARES_FILE = "AvailableSoftwaresListTemp.txt";
constexpr auto INSTALLED_SOFTWARES_FILE = "InstalledSoftwaresList.txt";
constexpr auto TEMP_INSTALLED_SOFTWARES_FILE = "InstalledSoftwaresListTemp.txt";

class SoftwareInfoManager
{
public:
  SoftwareInfoManager(std::string path);
  ~SoftwareInfoManager();

  std::vector<Software> ReadSwInfo();
  void WriteSwInfo(std::vector<Software> _swList);

private:
  std::fstream _stream;
  std::fstream _tempStream;
};

#endif /* SOFTWARE_INFO_MANAGER_H_ */