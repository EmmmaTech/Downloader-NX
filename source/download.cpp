/*
    Downloader, a cross-platform download manager for Nintendo Switch and PC
    Copyright (C) 2021 EmreTech

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <download.hpp>
#include <borealis.hpp>
#include <vector>
#include <math.h>
#include <iostream>

namespace utilities
{
#ifdef _DOWNLOADER_WINDOWS
    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
    {
        size_t written = fwrite(ptr, size, nmemb, stream);
        return written;
    }
#endif

    int progress_func(void *ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
        if (TotalToDownload <= 0.0)
            return 0;
        
        double fractionDownloaded = NowDownloaded / TotalToDownload;
        currentProgress = (int) round(fractionDownloaded * 100);

        std::cout << '\r';
        std::cout << currentProgress << "% done!";
        fflush(stdout);

        return 0;
    }

    void downloadFile(const char *url, const char *filename)
    {
        CURL *curl;
        FILE *fp;
        CURLcode res;

        curl = curl_easy_init();
        if (curl)
        {
            fp = fopen(filename, "wb");

            curl_easy_setopt(curl, CURLOPT_URL, url);

            // In case the website the program is downloading from requires a USERAGENT
            curl_easy_setopt(curl, CURLOPT_USERAGENT, API_AGENT);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

#ifdef _DOWNLOADER_WINDOWS
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
#else
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
#endif
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);

            res = curl_easy_perform(curl);
            if (res)
            {
                brls::Logger::error("Error while trying to download the file. curl_easy_perform failed.");
            }
            curl_easy_cleanup(curl);

            fclose(fp);
        }
        else
            brls::Logger::error("Error while trying to download the file. curl_easy_init failed.");
        
        std::cout << '\n';
    }

    void downloadFiles(std::unordered_map<std::string, std::string> &files)
    {
        for (const auto &e : files)
            downloadFile(e.first.c_str(), e.second.c_str());
    }

    std::string getLatestTag(const std::string url) 
    {
        const char* download_path =
        #ifdef _DOWNLOADER_SWITCH
        add(DOWNLOAD_PATH_SWITCH, "latest-tag.json");
        #else
        add(DOWNLOAD_PATH_GLFW, "latest-tag.json");
        #endif

        downloadFile(url.c_str(), download_path);

        nlohmann::json api_data;
        std::ifstream api_file(download_path);

        api_file >> api_data;
        api_file.close();

        return api_data["tag_name"].get<std::string>();
    }

    std::string getLatestDownload(const std::string url) 
    {
        const char* download_path =
        #ifdef _DOWNLOADER_SWITCH
        add(DOWNLOAD_PATH_SWITCH, "latest-tag.json");
        #else
        add(DOWNLOAD_PATH_GLFW, "latest-tag.json");
        #endif

        downloadFile(url.c_str(), download_path);

        nlohmann::json api_data;
        std::ifstream api_file(download_path);

        api_file >> api_data;
        api_file.close();

        std::string downloadURL;

        for (auto& array : api_data["assets"])
            downloadURL = array["browser_download_url"].get<std::string>();
        return downloadURL;
    }
}