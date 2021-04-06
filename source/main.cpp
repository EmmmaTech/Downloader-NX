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

#ifdef __SWITCH__
#include <switch.h>
#endif

#include <borealis.hpp>
#include <string>
#include <unordered_map>

#include "main_activity.hpp"
#include "home_tab.hpp"
#include "download.hpp"

using namespace brls::literals;

int main(int argc, char *argv[])
{
    brls::Logger::setLogLevel(brls::LogLevel::DEBUG);

    if (!brls::Application::init())
    {
        brls::Logger::error("Unable to init the Downloader app");
        return EXIT_FAILURE;
    }

    brls::Application::createWindow("main/title"_i18n);

    brls::Application::setGlobalQuit(true);
    brls::Application::registerXMLView("HomeTab", HomeTab::create);
    brls::Application::pushActivity(new MainActivity());

    while (brls::Application::mainLoop())
        ;
    
    return EXIT_SUCCESS;
}