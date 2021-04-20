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

#include <string>
#include <filesystem>
#include <iostream>
#include <switch.h>

// The goal of the downloader-forwarder is to delete an older version of the app when the user wants to update it.
// This cannot be done while the app is running for obvious reasons.
// For Switch only. PC will use a different approach that is easier to do.

#define PATH "/switch/Downloader/"
#define FULL_PATH "/switch/Downloader/Downloader.nro"
#define POSSIBLE_PATH "/switch/Downloader.nro"
#define DOWNLOAD_CONFIG_PATH "/config/Downloader/Downloader.nro"
#define CONFIG_PATH "/config/Downloader/"

void moveToFullPath(const std::string& path)
{
    std::filesystem::path currentNroPath{path};

    std::filesystem::copy_file(currentNroPath, std::string(FULL_PATH));
    std::filesystem::remove(currentNroPath);

    if (!std::filesystem::exists(currentNroPath.parent_path()))
        std::filesystem::create_directories(currentNroPath.parent_path());
}

void showText(const std::string& msg) // Shows text (i.e. an error message if something went wrong)
{
    // Init the app with the text console
    consoleInit(NULL);

    // Set controller input layout to the standard one
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initalize the default gamepad
    PadState pad;
    padInitializeDefault(&pad);

    std::cout << msg << '\n';
    std::cout << "Press + to exit into the HBMenu." << '\n';

    while(appletMainLoop())
    {
        // Update the pad to any new input
        padUpdate(&pad);

        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus) // If the button is equal to the Plus (+) button, 
            break; // we exit the loop.

        // Otherwise, we wait for the user to exit the app.

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
}

int main(int argc, char *argv[])
{
    if (std::filesystem::exists(POSSIBLE_PATH) || std::filesystem::exists(FULL_PATH))
    {
        std::string currentPath = "";

        if (std::filesystem::exists(POSSIBLE_PATH))
            currentPath = POSSIBLE_PATH;

        else if (std::filesystem::exists(FULL_PATH))
            currentPath = FULL_PATH;

        std::filesystem::remove(currentPath);

        if (!std::filesystem::exists(PATH))
            std::filesystem::create_directory(PATH);

        std::filesystem::copy_file(DOWNLOAD_CONFIG_PATH, FULL_PATH);
        std::filesystem::remove(DOWNLOAD_CONFIG_PATH);

        if (!std::filesystem::exists(CONFIG_PATH))
            std::filesystem::create_directories(CONFIG_PATH);
        
        envSetNextLoad(FULL_PATH, ("\"" + std::string(FULL_PATH) + "\"").c_str());
        return EXIT_SUCCESS;
    }
    else
        showText("Error: Downloader NRO file does not exist in perfered path (" + std::string(FULL_PATH) + ") or possible path (" + std::string(POSSIBLE_PATH) + ").");
    
    return EXIT_FAILURE;
}