#ifndef SOFTWARE_UPDATER_H_
#define SOFTWARE_UPDATER_H_

#include <memory>
#include <mutex>
#include <future>

#include "SoftwareInfoManager.h"

class SoftwareUpdater
{
public:
  SoftwareUpdater();
  ~SoftwareUpdater();

  void InitSwList();
  void RefreshSwList();
  void InstallSofware(std::size_t index);
  void RemoveSoftware(std::size_t index);

  std::vector<Software> GetAvailSwList();
  std::vector<Software> GetInstalledSwList();

private:
  std::unique_ptr<SoftwareInfoManager> _availableSwManager;
  std::unique_ptr<SoftwareInfoManager> _installedSwManager;
  
  std::vector<Software> _availableSoftwareList;
  std::vector<Software> _installedSoftwareList;

  std::mutex              _mutex;
};

#endif /* SOFTWARE_UPDATER_H_ */