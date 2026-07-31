#include <gui/screen14_screen/Screen14View.hpp>

Screen14View::Screen14View()
{

}

void Screen14View::setupScreen()
{
    Screen14ViewBase::setupScreen();
}

void Screen14View::tearDownScreen()
{
    Screen14ViewBase::tearDownScreen();
}
void Screen14View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar14.handleTickEvent();

    
}