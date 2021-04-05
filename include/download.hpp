#pragma once

//#include <json.hpp> Unused for now
#ifdef _DOWNLOADER_SWITCH
#include <sys/select.h>
#endif
#include <curl/curl.h>

#include <fstream>
#include <filesystem>
#include <string>

#include <stdio.h>
#include "constants.hpp"

#include <unordered_map>

namespace utilities
{
#ifdef _DOWNLOADER_WINDOWS
    /*
     * Re-implementation of curl's built-in write function.
     * This function is for Windows32 platforms only since a NULL write function will crash the application.
     * See this for more details: https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html
     */
    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
#endif

    /*
     * Downloads a file using curl. 
     * This function enables follow location, disabled verify peer and verify host, and uses a custom write function (for Windows only).
     */
    void downloadFile(const char *url, const char *filename);

    /*
     * Downloads mulitiple files that are contained in an unordered_map.
     */
    void downloadFiles(std::unordered_map<std::string, std::string> &files);
}