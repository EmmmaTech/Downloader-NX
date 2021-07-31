#include <borealis.hpp>
#include <switch.h>

#include <mainFrame.hpp>

namespace i18n = brls::i18n;
using namespace i18n::literals;

int main(int argc, char *argv[])
{
    if (!brls::Application::init("Downloader-NX"))
    {
        brls::Logger::error("Unable to init the Borealis application");
        return EXIT_FAILURE;
    }
    i18n::loadTranslations();

    brls::Application::pushView(new MainFrame());
    while (brls::Application::mainLoop());

    return EXIT_SUCCESS;
}