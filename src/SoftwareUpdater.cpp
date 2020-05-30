#include "SoftwareUpdater.h"

SoftwareUpdater::SoftwareUpdater()
{
  _availableSwManager = std::make_unique<SoftwareInfoManager>();
  _installedSwManager = std::make_unique<SoftwareInfoManager>();
}

SoftwareUpdater::~SoftwareUpdater()
{
  _availableSwManager->WriteSwInfo(AVAILABLE_SOFTWARES_FILE, _availableSoftwareList);
  _availableSwManager->WriteSwInfo(INSTALLED_SOFTWARES_FILE, _installedSoftwareList);
}

void SoftwareUpdater::InitSwList()
{
  _availableSoftwareList = _availableSwManager->ReadSwInfo(AVAILABLE_SOFTWARES_FILE);
  _installedSoftwareList = _installedSwManager->ReadSwInfo(INSTALLED_SOFTWARES_FILE);
}

void SoftwareUpdater::RefreshSwList()
{
  // TODO
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
  return _availableSoftwareList;
}

std::vector<Software> SoftwareUpdater::GetInstalledSwList()
{
  return _installedSoftwareList;
}