#include <homeTab.hpp>

#include <util.hpp>
#include <workerPage.hpp>

using namespace brls::i18n::literals;

HomeTab::HomeTab() : brls::List()
{
    addNewDownload = new brls::ListItem("text/home/add_download"_i18n);
    addNewDownload->getClickEvent()->subscribe([this](brls::View *view) {
        utils::KeyboardOptions urlOptions;
        urlOptions.guideText = "Enter the url to download from:";
        urlOptions.maxCharacters = FILENAME_MAX;

        utils::KeyboardOptions pathOptions;
        pathOptions.guideText = "Enter the filename to download the url to:";
        pathOptions.maxCharacters = FILENAME_MAX;

        std::string downloadUrl = utils::getKeyboardInput(urlOptions), 
        path = utils::getKeyboardInput(pathOptions);
        
        this->buffer.push_back(std::make_pair(path, downloadUrl));
    });
    this->addView(addNewDownload);

    showAllDownloads = new brls::ListItem("text/home/show_downloads"_i18n, " ");
    showAllDownloads->getClickEvent()->subscribe([this](brls::View *view) {
        brls::AppletFrame *popupFrame = new brls::AppletFrame(true, true);
        brls::List *listOfDownloads = new brls::List();

        brls::ListItem *currentItem;
        for (auto &e : this->buffer)
        {
            std::string title = fmt::format("text/home/download_item_base"_i18n, e.first, e.second);
            currentItem = new brls::ListItem(title);
            listOfDownloads->addView(currentItem);
        }

        popupFrame->setContentView(listOfDownloads);
        popupFrame->registerAction("", brls::Key::PLUS, []{return true;});

        brls::PopupFrame::open("text/home/all_downloads_title"_i18n, popupFrame);
    });
    this->addView(showAllDownloads);

    downloadEverything = new brls::ListItem("text/home/download_everything"_i18n);
    downloadEverything->getClickEvent()->subscribe([this](brls::View *view) {
        brls::StagedAppletFrame *stagedFrame = new brls::StagedAppletFrame();
        stagedFrame->setTitle("Downloading Files");

        for (size_t i{0}; i < this->buffer.size(); i++)
        {
            const auto &e = this->buffer.at(i);

            stagedFrame->addStage(new WorkerPage(
                stagedFrame,
                fmt::format("Downloading file {0} out of {1}...", i, this->buffer.size()),
                [e]{utils::downloadFile(e.second, "/" + e.first);}
            ));
        }

        brls::Application::pushView(stagedFrame);
    });
    this->addView(downloadEverything);
}