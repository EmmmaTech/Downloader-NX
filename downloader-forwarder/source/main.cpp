#include <string>
#include <filesystem>
#include <switch.h>

// The goal of the downloader-forwarder is to delete an older version of the app when the user wants to update it.
// This cannot be done while the app is running for obvious reasons.
// For Switch only. PC uses a different approach that is easier to do.

#define PATH "/switch/Downloader/"
#define FULL_PATH "/switch/Downloader/Downloader.nro"
#define DOWNLOAD_CONFIG_PATH "/config/Downloader/switch/Downloader/Downloader.nro"
#define DOWNLOAD_CONFIG_SWITCH "/config/Downloader/switch/"
#define CONFIG_PATH "/config/Downloader/"

int main(int argc, char *argv[])
{
    std::filesystem::remove(FULL_PATH);

    if (!std::filesystem::exists(PATH))
        std::filesystem::create_directory(PATH);

    std::filesystem::copy_file(DOWNLOAD_CONFIG_PATH, FULL_PATH);
    std::filesystem::remove(DOWNLOAD_CONFIG_SWITCH);
    
    envSetNextLoad(FULL_PATH, ("\"" + std::string(FULL_PATH) + "\"").c_str());
    return EXIT_SUCCESS;
}