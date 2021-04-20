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

// A reimplementation of borealis' swkd wrapper.
// Instead of the developer providing a function to handle the provided string from input, it returns it.
namespace input
{
#ifdef _DOWNLOADER_PC
/*
 * Gets input from the user if the platform is PC.
 */
std::string terminalInput(const std::string& printText);
#else
/*
 * Gets input from the user if the platform is Switch.
 */
std::string swkdInput(const std::string& printText, size_t max);
#endif

/*
 * Gets input from both PC and Switch platforms.
 * If the user is on PC, the provided max_characters will be ignored.
 */
std::string getKeyboardInput(const std::string& printText, size_t max_characters);
} // namespace input
