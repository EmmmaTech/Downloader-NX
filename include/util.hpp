#pragma once

#include <string>
#include <switch.h>
#include <cstring>

namespace utils
{

enum class KeyboardPreset
{
    DEFAULT = 0,
    PASSWORD,
    USERNAME,
    DOWNLOAD_CODE,
};

struct KeyboardOptions
{
    KeyboardPreset preset = KeyboardPreset::DEFAULT;
    char *okButtonText    = NULL;
    char *leftSymbolKey   = NULL;
    char *rightSymbolKey  = NULL;
    char *headerText      = NULL;
    char *subText         = NULL;
    char *guideText       = NULL;
    char *initalText      = NULL;
    int maxCharacters     = 32;
};

std::string getKeyboardInput(KeyboardOptions options);
bool downloadFile(const std::string &url, const std::string &filepath);

} // namespace utils
