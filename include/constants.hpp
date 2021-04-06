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

#include <string>

#ifndef _DOWNLOADER_SWITCH
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define _DOWNLOADER_WINDOWS
#else
#define _DOWNLOADER_UNIX
#endif
#endif

/*
 * Adds two const char *'s together. Next time I should use the built-in function for this...
 */
const char *add(const char *__str1, const char *__str2);

const char *const CONFIG_PATH_SWITCH = "/config/Downloader/";
const char *const CONFIG_PATH_GLFW = "./config/Downloader/";

const char *const DOWNLOAD_PATH_SWITCH = add(CONFIG_PATH_SWITCH, "download/");
const char *const DOWNLOAD_PATH_GLFW = "./download/";

const char *const API_URL = "https://api.github.com/repos/EmreTech/Downloader/releases/latest";
const char *const API_AGENT = "EmreTech";
const char *const APP_VERSION = "v0.0.1";
