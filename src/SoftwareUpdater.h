#ifndef SOFTWARE_UPDATER_H_
#define SOFTWARE_UPDATER_H_

#include <memory>
#include <mutex>
#include <condition_variable>

#include "SoftwareInfoManager.h"

class SoftwareUpdater
{
  SoftwareUpdater();
  ~SoftwareUpdater();

  void RefreshSwList();
  void InstallSofware(Software sw);
  void RemoveSoftware(Software sw);

  std::vector<Software> GetAvailSwList();
  std::vector<Software> GetInstalledSwList();

private:
  std::unique_ptr<SoftwareInfoManager> _availableSwManager;
  std::unique_ptr<SoftwareInfoManager> _installedSwManager;
  
  std::vector<Software> _availableSoftwareList;
  std::vector<Software> _installedSoftwareList;

  std::condition_variable _cond;
  std::mutex _mutex;
};

#endif /* SOFTWARE_UPDATER_H_ */