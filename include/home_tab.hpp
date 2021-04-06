#pragma once

#include <sstream>
#include <string>
#include <unordered_map>
#include <borealis.hpp>

struct HomeTab : public brls::Box
{
    HomeTab();

    static brls::View* create();

    private:

    bool onURLButtonPressed(brls::View* view);
    bool onFNameButtonPressed(brls::View* view);
    bool onDownloadButtonPressed(brls::View* view);

    BRLS_BIND(brls::Label, progressLabel, "download_progress");

    std::string current_url;
    std::string current_fname;

    std::unordered_map<std::string, std::string> requestedDownloads;
};