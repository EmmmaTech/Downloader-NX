#include <home_tab.hpp>

HomeTab::HomeTab() 
{
    this->inflateFromXMLRes("xml/tabs/home.xml");
}

brls::View* HomeTab::create()
{
    return new HomeTab();
}