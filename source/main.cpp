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