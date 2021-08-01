#include <util.hpp>

#include <http.hpp>
#include <progressEvent.hpp>
#include <iostream>

namespace utils
{

std::string getKeyboardInput(KeyboardOptions options)
{
    SwkbdConfig kbd;
    char tmpstr[options.maxCharacters] = {0};
    Result rc = swkbdCreate(&kbd, 0);

    if (R_SUCCEEDED(rc))
    {
        switch (options.preset)
        {
            case KeyboardPreset::DEFAULT:
            swkbdConfigMakePresetDefault(&kbd);
            break;

            case KeyboardPreset::PASSWORD:
            swkbdConfigMakePresetPassword(&kbd);
            break;

            case KeyboardPreset::USERNAME:
            swkbdConfigMakePresetUserName(&kbd);
            break;

            case KeyboardPreset::DOWNLOAD_CODE:
            swkbdConfigMakePresetDownloadCode(&kbd);
            break;
        }

        if (options.okButtonText)
            swkbdConfigSetOkButtonText(&kbd, options.okButtonText);
        if (options.leftSymbolKey)
            swkbdConfigSetLeftOptionalSymbolKey(&kbd, options.leftSymbolKey);
        if (options.rightSymbolKey)
            swkbdConfigSetRightOptionalSymbolKey(&kbd, options.rightSymbolKey);
        if (options.headerText)
            swkbdConfigSetHeaderText(&kbd, options.headerText);
        if (options.subText)
            swkbdConfigSetSubText(&kbd, options.subText);
        if (options.guideText)
            swkbdConfigSetGuideText(&kbd, options.guideText);
        if (options.initalText)
            swkbdConfigSetRightOptionalSymbolKey(&kbd, options.initalText);

        rc = swkbdShow(&kbd, tmpstr, sizeof(tmpstr));

        std::string output = "";
        if (R_SUCCEEDED(rc))
            output = tmpstr;

        swkbdClose(&kbd);
        return output;
    }
    
    return "";
}

namespace
{

int downloadProgress(void *pointer, double dltotal, double dlnow, double ultotal, double ulnow)
{
    if (dltotal <= 0.0) return 0;
    ProgressEvent &pe = ProgressEvent::getInstance();

    double fractionDownloaded = dlnow / dltotal;
    int counter = (int) (fractionDownloaded * pe.getMax());
    ProgressEvent::getInstance().setStep(std::min(pe.getMax(), counter));
    return 0;
}

} // namespace

bool downloadFile(const std::string &url, const std::string &filepath)
{
    return httpDownloadFile(filepath.c_str(), url.c_str(), false, downloadProgress, NULL);
}

} // namespace utils
