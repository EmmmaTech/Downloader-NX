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

#include <borealis.hpp>
#include <download.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#ifndef _DOWNLOADER_SWITCH
#include <zipper/unzipper.h>
#else
#include <unzipper.h>
#endif

namespace utilities {

bool is_zip_file(const std::string& str) {
  std::filesystem::path p(str);

  if (!p.has_extension())
    return false;

  if (p.extension() == ".zip")
    return true;

  return false;
}

std::string extract_filename(const std::string& str) {
  std::filesystem::path p(str);

  if (!p.has_filename())
    return "";
  
  return p.filename().string();
}

void downloadFile(const char *url, const char *filename) {
  std::cout << filename << '\n';

  cpr::Response r = cpr::Get(cpr::Url{url});

  if (r.error.code != cpr::ErrorCode::OK)
  {
    std::string error = "Something went wrong when attemping to download file from ";
    error += url;
    error += ".";
    throw std::runtime_error(error.c_str());
  }

  std::fstream file;
  file.open(filename, std::ios::in|std::ios::out|std::ios::trunc);

  if (file.good())
    file << r.text;

  else
  {
    std::string error = "Something went wrong when attemping to save downloaded file from ";
    error += url;
    error += ".";
    throw std::runtime_error(error.c_str());
  }

  file.close();
}

void downloadFiles(std::unordered_map<std::string, std::string> &files) {
  for (const auto &e : files) {
    try {
      downloadFile(e.first.c_str(), e.second.c_str());
    } catch (std::runtime_error& e) {
      brls::Logger::error("Error: {}", e.what());
    }
  }
}

std::string getLatestTag(const std::string url) {
  const char *download_path =
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

  try {
    return api_data["tag_name"].get<std::string>();
  } catch (...) { }

  return "";
}

std::string getLatestDownload(const std::string url) {
  const char *download_path =
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

  try {
    for (auto &array : api_data["assets"])
      downloadURL = array["browser_download_url"].get<std::string>();
  } catch (...) { }

  return downloadURL;
}
} // namespace utilities