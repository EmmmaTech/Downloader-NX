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
#include <string>
#include <string.h>
#include <filesystem>

const char * add(const char* __str1, const char* __str2)
{
    static std::string str1(__str1);
    str1 = str1 + __str2;
    return str1.c_str();
}

const char *correctSeperators(const char *__str)
{
    static std::filesystem::path p{ __str };
    p.make_preferred();
    const char *output = p.c_str();
    return output;
}