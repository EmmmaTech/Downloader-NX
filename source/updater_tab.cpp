/*
    Downloader, a cross-platform download manager for Nintendo Switch and PC
    Copyright (C) 2021 EmreTech

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <constants.hpp>
#include <download.hpp>
#include <updater_tab.hpp>

#ifdef _DOWNLOADER_SWITCH
#include <switch.h>
#endif

using namespace brls::literals;

UpdaterTab::UpdaterTab() {
  this->inflateFromXMLRes("xml/tabs/updater.xml");

  this->yes_button->hide([] {});
  this->no_button->hide([] {});

  BRLS_REGISTER_CLICK_BY_ID("update_button", this->onUpdateButtonPressed);
  BRLS_REGISTER_CLICK_BY_ID("yes", this->onYesButtonPressed);
  BRLS_REGISTER_CLICK_BY_ID("no", this->onNoButtonPressed);
}

brls::View *UpdaterTab::create() { return new UpdaterTab(); }

bool UpdaterTab::onUpdateButtonPressed(brls::View *view) {
  if (canUpdate) {
    std::string newTag = "v1.0.1" /*utilities::getLatestTag(API_URL)*/;

    if (newTag == std::string(APP_VERSION))
      this->info_label->setText("main/update/update_not_found"_i18n);
    else {
      this->info_label->setText("main/update/update_found"_i18n);
      this->yes_button->show([] {});
      this->no_button->show([] {});
    }
  } else
    this->info_label->setText("main/update/update_cannot_check"_i18n);
  

  return true;
}

bool UpdaterTab::onYesButtonPressed(brls::View *view) {
  std::string downloadURL = utilities::getLatestDownload(API_URL);
  brls::Logger::debug("Download URL: {}", downloadURL);
  bool res = this->updateApp(downloadURL);
  if (res)
    return true;
  else
    return false;
}

bool UpdaterTab::updateApp(const std::string &url) {
#ifdef _DOWNLOADER_SWITCH
  utilities::downloadFile(url.c_str(), UPDATE_PATH_SWITCH);
  envSetNextLoad(FORWARDER_PATH_SWITCH,
                 ("\"" + std::string(FORWARDER_PATH_SWITCH) + "\"").c_str());
#else
  utilities::downloadFile(url.c_str(), UPDATE_PATH_GLFW);
// TODO: Extract and copy all the files to the project root
#endif

  return false;
}

bool UpdaterTab::onNoButtonPressed(brls::View *view) {
  // TODO: Add a file to skip an update
  this->info_label->setText("Please exit the tab now.");

  return true;
}