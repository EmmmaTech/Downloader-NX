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

#include <borealis.hpp>
#include <string>

struct UpdaterTab : public brls::Box
{
    UpdaterTab();

    static brls::View* create();

  private:
    bool onUpdateButtonPressed(brls::View* view);
    bool onYesButtonPressed(brls::View* view);
    bool onNoButtonPressed(brls::View* view);

    bool updateApp(const std::string& url);

    BRLS_BIND(brls::Label, info_label, "info");
    BRLS_BIND(brls::Button, yes_button, "yes");
    BRLS_BIND(brls::Button, no_button, "no");
};