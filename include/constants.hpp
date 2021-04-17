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

#ifdef _DOWNLOADER_PC
#if defined(WIN32) || defined(_WIN32) ||                                       \
    defined(__WIN32) && !defined(__CYGWIN__)
#define _DOWNLOADER_WINDOWS
#else
#define _DOWNLOADER_UNIX
#endif
#endif

/*
 * Adds two const char *'s together. Next time I should use the built-in
 * function for this...
 */
const char *add(const char *__str1, const char *__str2);

const char *correctSeperators(const char *__str);

#define CONFIG_PATH_SWITCH "/config/Downloader/"

#define PATH_SWITCH "/switch/Downloader/"
#define FULL_PATH_SWITCH add(PATH_SWITCH, "Downloader.nro")

#define FORWARDER_PATH_SWITCH add(CONFIG_PATH_SWITCH, "downloader-forwarder.nro")
#define ROMFS_FORWARDER_PATH_SWITCH add(BRLS_RESOURCES, "downloader-forwarder.nro")

#define DOWNLOAD_PATH_SWITCH add(CONFIG_PATH_SWITCH, "download/")
#define DOWNLOAD_PATH_GLFW correctSeperators("./download/")

#define UPDATE_PATH_SWITCH add(CONFIG_PATH_SWITCH, "Downloader.nro")
#define UPDATE_PATH_GLFW add(DOWNLOAD_PATH_GLFW, "Downloader-PC.zip")

#define API_URL                                                                \
  "https://api.github.com/repos/EmreTech/Downloader/releases/latest"
#define API_AGENT "EmreTech"

static bool canUpdate = true;