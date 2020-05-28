#include "SoftwareUpdater.h"

SoftwareUpdater::SoftwareUpdater()
{
  _availableSwManager = std::make_unique<SoftwareInfoManager>(AVAILABLE_SOFTWARES_FILE);
  _installedSwManager = std::make_unique<SoftwareInfoManager>(INSTALLED_SOFTWARES_FILE);
}

SoftwareUpdater::~SoftwareUpdater()
{

}

void SoftwareUpdater::RefreshSwList()
{

}

void SoftwareUpdater::InstallSofware(Software sw)
{

}

void SoftwareUpdater::RemoveSoftware(Software sw)
{

}

std::vector<Software> SoftwareUpdater::GetAvailSwList()
{
  return _availableSoftwareList;
}

std::vector<Software> SoftwareUpdater::GetInstalledSwList()
{
  return _installedSoftwareList;
}