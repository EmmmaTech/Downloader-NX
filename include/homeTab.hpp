#pragma once

#include <borealis.hpp>

#include <vector>
#include <utility>

typedef std::vector<std::pair<std::string, std::string>> DownloadsBuffer;

struct HomeTab : public brls::List
{
    HomeTab();

    private:
    brls::ListItem *addNewDownload;
    brls::ListItem *showAllDownloads;
    brls::ListItem *downloadEverything;

    DownloadsBuffer buffer;
};