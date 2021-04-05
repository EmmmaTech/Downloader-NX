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

    // A test to see if the functions work (will be removed)
    std::unordered_map<std::string, std::string> fileToDownload;
    fileToDownload["http://www.gecif.net/articles/mathematiques/pi/pi_1_million.txt"] = "./download/text.txt";
    fileToDownload["https://raw.githubusercontent.com/natinusala/borealis/main/meson.build"] = "./download/meson.build"; // Not downloading???
    utilities::downloadFiles(fileToDownload);

    while (brls::Application::mainLoop())
        ;
    
    return EXIT_SUCCESS;
}