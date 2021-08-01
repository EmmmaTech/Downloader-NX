#include <borealis.hpp>
#include <switch.h>
#include <http.hpp>

#include <mainFrame.hpp>

namespace i18n = brls::i18n;
using namespace i18n::literals;

int main(int argc, char *argv[])
{
    brls::Logger::setLogLevel(brls::LogLevel::DEBUG);

    if (!brls::Application::init("Downloader-NX"))
    {
        brls::Logger::error("Unable to init the Borealis application");
        return EXIT_FAILURE;
    }
    i18n::loadTranslations();

    if (!httpInitialize())
    {
        brls::Logger::error("Failed to initalize CURL. Quitting...");
        return EXIT_FAILURE;
    }



    brls::Application::pushView(new MainFrame());
    while (brls::Application::mainLoop());

    return EXIT_SUCCESS;
}