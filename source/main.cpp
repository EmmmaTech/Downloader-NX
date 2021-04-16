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

void initFolders() {
  const char *config_path =
#ifdef _DOWNLOADER_SWITCH
      CONFIG_PATH_SWITCH;
#else
      CONFIG_PATH_GLFW;
#endif

  const char *download_path =
#ifdef _DOWNLOADER_SWITCH
      DOWNLOAD_PATH_SWITCH;
#else
      DOWNLOAD_PATH_GLFW;
#endif

  try {
    if (!std::filesystem::exists(config_path))
      std::filesystem::create_directories(config_path);

    else if (!std::filesystem::is_directory(config_path)) {
      std::filesystem::remove(config_path);
      std::filesystem::create_directories(config_path);
    }

    if (!std::filesystem::exists(download_path))
      std::filesystem::create_directories(download_path);

    else if (!std::filesystem::is_directory(download_path)) {
      std::filesystem::remove(download_path);
      std::filesystem::create_directories(download_path);
    }
  } catch (std::filesystem::filesystem_error &e) {
    brls::Logger::error("{}", e.what());
  }
}

int main(int argc, char *argv[]) {
#ifdef _DOWNLOADER_SWITCH
  socketInitializeDefault();
#endif
  initFolders();

  if (!brls::Application::init()) {
    brls::Logger::error("Unable to init the Downloader app");
    return EXIT_FAILURE;
  }

  brls::Application::createWindow("main/title"_i18n);
  brls::Application::setGlobalQuit(true);

  brls::Application::registerXMLView("HomeTab", HomeTab::create);
  brls::Application::registerXMLView("UpdaterTab", UpdaterTab::create);

  brls::Application::pushActivity(new MainActivity());

  while (brls::Application::mainLoop()) // BUG: Segementation fault when the user quits the app.
    ;

#ifdef _DOWNLOADER_SWITCH
  socketExit();
#endif

  return EXIT_SUCCESS;
}