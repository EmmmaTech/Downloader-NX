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

#include <input.hpp>


#ifdef _DOWNLOADER_SWITCH
#include <switch.h>
#else
#include <iostream>
#endif

namespace input {
#ifdef _DOWNLOADER_PC
std::string terminalInput(const std::string& printText)
{
    std::string output;
    std::cout << printText << '\n' << "> ";
    std::getline(std::cin, output);
    std::cout << "Please return to the Downloader window." << '\n';
    return output;
}
#else
std::string swkdInput(const std::string& printText, size_t max)
{
    // TODO: Implement getting input from SKWD (Software Keyboard).
    return "Unimplemented.";
}
#endif

std::string getKeyboardInput(const std::string& printText, size_t max_characters)
{
    std::string input;
#ifdef _DOWNLOADER_PC
    input = terminalInput(printText);
#else
    input = swkdInput(printText, max_characters);
#endif
    return input;
}
} // namespace input
