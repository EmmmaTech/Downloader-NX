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

#include <constants.hpp>
#include <filesystem>
#include <iostream>
#include <string.h>

const char* add(const char* __str1, const char* __str2)
{
    std::string str1 = __str1;
    str1             = str1 + __str2;
    char* output     = new char[sizeof(str1.c_str()) + 1];
    strcpy(output, str1.c_str());
    return output;
}

const char* correctSeperators(const char* __str)
{
    std::filesystem::path p { __str };
    p.make_preferred();

    std::string tmp_output = p.string();
    char* output           = new char[sizeof(tmp_output.c_str()) + 1];
    strcpy(output, tmp_output.c_str());
    return output;
}