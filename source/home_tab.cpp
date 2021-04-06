#include <home_tab.hpp>
#include <borealis/platforms/switch/swkbd.hpp>
#include <download.hpp>
#include <thread>
#include <filesystem>

HomeTab::HomeTab() 
{
    this->inflateFromXMLRes("xml/tabs/home.xml");
    BRLS_REGISTER_CLICK_BY_ID("url_button", this->onURLButtonPressed);
    BRLS_REGISTER_CLICK_BY_ID("fname_button", this->onFNameButtonPressed);
    BRLS_REGISTER_CLICK_BY_ID("download_button", this->onDownloadButtonPressed);
}

bool HomeTab::onURLButtonPressed(brls::View* view)
{
    brls::Swkbd::openForText([this](std::string str){
        this->current_url = str;
        #ifdef _DOWNLOADER_PC
        brls::Logger::info("Please return to the Downloader window.");
        #endif
    }, "", "", FILENAME_MAX, "Enter URL here");
    
    return true;
}

bool HomeTab::onFNameButtonPressed(brls::View* view)
{
    brls::Swkbd::openForText([this](std::string str){
        this->current_fname = str;
        #ifdef _DOWNLOADER_PC
        brls::Logger::info("Please return to the Downloader window.");
        #endif
    }, "", "", FILENAME_MAX, "Enter filename here");
    return true;
}

bool HomeTab::onDownloadButtonPressed(brls::View* view)
{
    // Function cannot run if current_url and current_fname are empty
    if (this->current_url.empty() || this->current_fname.empty())
    {
        brls::Logger::warning("Current URL and/or current filename are empty. Please use their buttons to set them.");
        return true;
    }

    #ifdef _DOWNLOADER_PC
    if (!std::filesystem::exists(DOWNLOAD_PATH_GLFW))
        std::filesystem::create_directories(DOWNLOAD_PATH_GLFW);

    else if (!std::filesystem::is_directory(DOWNLOAD_PATH_GLFW))
    {
        brls::Logger::error("Download path for PC (GLFW) already exists, but it's not a directory.");
        return true;
    }
    #else
    if (!std::filesystem::exists(DOWNLOAD_PATH_SWITCH))
        std::filesystem::create_directories(DOWNLOAD_PATH_SWITCH);

    else if (!std::filesystem::is_directory(DOWNLOAD_PATH_SWITCH))
    {
        brls::Logger::error("Download path for Switch already exists, but it's not a directory.");
        return true;
    }
    #endif

    // Initalize some variables for later use
    std::istringstream iss_1(this->current_url);
    std::istringstream iss_2(this->current_fname);
    std::string url, fname;

    // Add elements to the requestedDownloads map
    while (iss_1 >> url && iss_2 >> fname) {
        #ifdef _DOWNLOADER_PC
        fname = DOWNLOAD_PATH_GLFW + fname;
        #else
        fname = DOWNLOAD_PATH_SWITCH + fname;
        #endif
        this->requestedDownloads[url] = fname;
    }

    // Start download(s) on a different thread
    std::thread downloadThread = std::thread(&utilities::downloadFiles, std::ref(this->requestedDownloads));
    this->progressLabel->setText(std::to_string(utilities::currentProgress) + "% done downloading..."); // TODO: Get the progress meter to work properly.
    if (downloadThread.joinable())
        downloadThread.join();

    // Cleanup
    this->requestedDownloads.clear();

    this->current_url.clear();
    this->current_url.shrink_to_fit();

    this->current_fname.clear();
    this->current_fname.shrink_to_fit();

    return true;
}

brls::View* HomeTab::create()
{
    return new HomeTab();
}