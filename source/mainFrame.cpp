#include <mainFrame.hpp>

#include <homeTab.hpp>

MainFrame::MainFrame() : TabFrame()
{
    this->setTitle("Downloader-NX");
    this->setFooterText(fmt::format("v{0} | {1}", APP_VERSION, STABLE));
    this->setIcon(BOREALIS_ASSET("icon/Downloader_NX_Icon_Alt.jpeg"));

    this->addTab("Home", new HomeTab());
    this->addTab("About Downloader-NX", nullptr);
    this->addTab("Settings", nullptr);
}