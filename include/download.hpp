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

#pragma once

#include "constants.hpp"

#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <string>
#include <unordered_map>
#include <mutex>
#include <condition_variable>

namespace utilities
{
/*
 * Downloads a file using curl.
 * This function enables follow location, disabled verify peer and verify host,
 * and uses a custom write function (for Windows only).
 */
void downloadFile(const char* url, const char* filename);

/*
 * Downloads mulitiple files that are contained in an unordered_map.
 */
void downloadFiles(std::unordered_map<std::string, std::string>& files);

/*
 * Gets the latest tag from an api.github.com url.
 */
std::string getLatestTag(const std::string url);

/*
 * Gets the latest download link from an api.github.com url.
 */
std::string getLatestDownload(const std::string url);

inline std::mutex mtx;
inline std::condition_variable meterAvaliable;
inline bool ready = false; // Tells the main thread it's ready for it to extract the progress meter
inline bool done  = false; // Tells the main thread it's done downloading, so it should stop the loop.

} // namespace utilities