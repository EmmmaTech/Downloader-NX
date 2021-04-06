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
}