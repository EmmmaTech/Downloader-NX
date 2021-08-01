#include <mainFrame.hpp>

#include <homeTab.hpp>

MainFrame::MainFrame() : TabFrame()
{
    this->setTitle("Downloader-NX");
    this->setFooterText(fmt::format("v{0} | {1}", APP_VERSION, STABLE));

    this->addTab("Home", new HomeTab());
    this->addTab("About Downloader-NX", nullptr);
    this->addTab("Settings", nullptr);
}