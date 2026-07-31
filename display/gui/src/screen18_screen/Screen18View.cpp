#include <gui/screen18_screen/Screen18View.hpp>

Screen18View::Screen18View()
{

}

void Screen18View::setupScreen()
{
    Screen18ViewBase::setupScreen();
}

void Screen18View::tearDownScreen()
{
    Screen18ViewBase::tearDownScreen();
}
void Screen18View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar18.handleTickEvent();

    
}