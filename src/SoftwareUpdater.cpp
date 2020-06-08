#include "SoftwareUpdater.h"
#include <wx/log.h>

SoftwareUpdater::SoftwareUpdater()
{
  _availableSwManager = std::make_unique<SoftwareInfoManager>(AVAILABLE_SOFTWARES_FILE, TEMP_AVAILABLE_SOFTWARES_FILE);
  _installedSwManager = std::make_unique<SoftwareInfoManager>(INSTALLED_SOFTWARES_FILE, TEMP_INSTALLED_SOFTWARES_FILE);
}

SoftwareUpdater::~SoftwareUpdater()
{
  _availableSwManager->WriteSwInfo(_availableSoftwareList);
  _availableSwManager->Close();

  _installedSwManager->WriteSwInfo(_installedSoftwareList);
  _installedSwManager->Close();
}

void SoftwareUpdater::InitSwList()
{
  std::lock_guard<std::mutex> lock(_mutex);
  _availableSoftwareList = _availableSwManager->ReadSwInfo();
  _installedSoftwareList = _installedSwManager->ReadSwInfo();
}

void SoftwareUpdater::RefreshSwList()
{
  // TODO
  std::lock_guard<std::mutex> lock(_mutex);
}

bool Software::operator==(Software &sw)
{
  bool nameCompare = this->GetName().compare(sw.GetName());
  bool versionCompare = this->GetVersion().compare(sw.GetVersion());
  bool dateCompare = this->GetDate().compare(sw.GetDate());

  return (nameCompare && versionCompare && dateCompare);
}

void SoftwareUpdater::InstallSofware(std::size_t index)
{
  std::lock_guard<std::mutex> lock(_mutex);

  if (index < 0 || index > _availableSoftwareList.size())
  {
	return;
  }

  Software installSw = _availableSoftwareList[index];
  _availableSoftwareList.erase(_availableSoftwareList.begin() + index);
  _installedSoftwareList.push_back(std::move(installSw));
}

void SoftwareUpdater::RemoveSoftware(std::size_t index)
{
  std::lock_guard<std::mutex> lock(_mutex);

  if (index < 0 || index > _installedSoftwareList.size())
  {
	return;
  }

  Software removeSw = _installedSoftwareList[index];
  _installedSoftwareList.erase(_installedSoftwareList.begin() + index);
  _availableSoftwareList.push_back(std::move(removeSw));
}

std::vector<Software> SoftwareUpdater::GetAvailSwList()
{
  std::lock_guard<std::mutex> lock(_mutex);
  return _availableSoftwareList;
}

std::vector<Software> SoftwareUpdater::GetInstalledSwList()
{
  std::lock_guard<std::mutex> lock(_mutex);
  return _installedSoftwareList;
}