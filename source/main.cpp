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

#ifdef _DOWNLOADER_SWITCH
#include <switch.h>
#endif

#include <borealis.hpp>
#include <filesystem>

#include "constants.hpp"
#include "home_tab.hpp"
#include "main_activity.hpp"
#include "updater_tab.hpp"

using namespace brls::literals;

#ifdef _DOWNLOADER_SWITCH
const char *config_path = CONFIG_PATH_SWITCH;
#endif

const char *download_path =
#ifdef _DOWNLOADER_SWITCH
      DOWNLOAD_PATH_SWITCH;
#else
      DOWNLOAD_PATH_GLFW;
#endif

void initFolders() {
#ifdef _DOWNLOADER_SWITCH
    if (!std::filesystem::exists(config_path))
      std::filesystem::create_directories(config_path);

    else if (!std::filesystem::is_directory(config_path)) {
      std::filesystem::remove(config_path);
      std::filesystem::create_directories(config_path);
    }
#endif

    if (!std::filesystem::exists(download_path))
      std::filesystem::create_directories(download_path);

    else if (!std::filesystem::is_directory(download_path)) {
      std::filesystem::remove(download_path);
      std::filesystem::create_directories(download_path);
    }
}

int main(int argc, char *argv[]) {
#ifdef _DOWNLOADER_SWITCH
  socketInitializeDefault();
#endif
  initFolders();

#ifdef _DOWNLOADER_SWITCH
if (!std::filesystem::exists(ROMFS_FORWARDER_PATH_SWITCH))
{
  brls::Logger::error("Romfs Forwarder Path does not exist, updates are disabled.");
  // TODO: Disable updates
}

else if (!std::filesystem::exists(FORWARDER_PATH_SWITCH))
  std::filesystem::copy_file(ROMFS_FORWARDER_PATH_SWITCH, FORWARDER_PATH_SWITCH); // This is REQUIRED in order to update the app.
#endif

  if (!brls::Application::init()) {
    brls::Logger::error("Unable to init the Downloader app");
    return EXIT_FAILURE;
  }

  brls::Application::createWindow("main/title"_i18n);
  brls::Application::setGlobalQuit(true);

  brls::Application::registerXMLView("HomeTab", HomeTab::create);
  brls::Application::registerXMLView("UpdaterTab", UpdaterTab::create);

  brls::Application::pushActivity(new MainActivity());

  while (brls::Application::mainLoop())
    ;

#ifdef _DOWNLOADER_SWITCH
  socketExit();
#endif

  return EXIT_SUCCESS;
}