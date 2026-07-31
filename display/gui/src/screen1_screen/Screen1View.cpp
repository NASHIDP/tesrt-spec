#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View() :
    isValidating(false),
    tickCounter(0)
{
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

// Called when the continue flex button is pushed
void Screen1View::continueButtonClicked()
{
    isValidating = true;
    tickCounter = 0;
    
    // Reveal hidden overlay container and refresh screen context
    validationModal.setVisible(true);
    validationModal.invalidate();
    flexButton1.setVisible(false);
    flexButton1.invalidate();
}

// Automatically runs at 60 frames per second
void Screen1View::handleTickEvent()
{   
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar1.handleTickEvent();
    if (isValidating)
    {
        tickCounter++;
        
        // Calculate dynamic progress scaling up to 100
        int16_t progressValue = (tickCounter * 100) / TOTAL_TICKS;
        
        if (progressValue <= 100)
        {
            circleProgress1.setValue(progressValue);
            circleProgress1.invalidate();
        }
        
        // The moment the window 2 progress loader hits 100%
        if (tickCounter >= TOTAL_TICKS)
        {
            isValidating = false;
            
            
            application().gotoScreen2ScreenNoTransition();
        }
    }
}