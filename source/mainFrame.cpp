#include <mainFrame.hpp>

#include <workerPage.hpp>
#include <progressEvent.hpp>

MainFrame::MainFrame() : TabFrame()
{
    this->setTitle("Downloader-NX");
    this->setFooterText(fmt::format("v{0} | {1}", APP_VERSION, STABLE));

    this->addTab("Home", nullptr);
    this->addTab("About Downloader-NX", nullptr);
    this->addTab("Settings", nullptr);
}