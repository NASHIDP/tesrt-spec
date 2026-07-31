#include <gui/screen10_screen/Screen10View.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/utils.hpp> 

#define COLOR_GREEN touchgfx::Color::getColorFromRGB(0x10, 0xB9, 0x81)

Screen10View::Screen10View() :
    tickCounter(0),
    progressValue(0),
    isDetectionComplete(false)
{
}

void Screen10View::setupScreen()
{
    Screen10ViewBase::setupScreen();
    topStatusBar10.setScreenTitle("Oxygenator Connection");
    
    // Initial state: hide the button, reset the loader
    progressOxygenator.setValue(0);
    btnContinueNext.setVisible(false);
    btnContinueNext.invalidate();
}

void Screen10View::tearDownScreen()
{
    Screen10ViewBase::tearDownScreen();
}

void Screen10View::handleTickEvent()
{   
    topStatusBar10.handleTickEvent();
    if (isDetectionComplete)
    {
        return; // Progress hit 100%, freeze the logic here
    }

    tickCounter++;

    // Smoothly advances the progress bar
    if (tickCounter % 2 == 0)
    {
        progressValue++;
        
        if (progressValue <= 100)
        {
            progressOxygenator.setValue(progressValue);
            progressOxygenator.invalidate();
        }

        
        // Action sequence at 100% completion
        if (progressValue >= 100)
        {
            isDetectionComplete = true;

           
            progressOxygenatorPainter.setColor(COLOR_GREEN); 
            progressOxygenator.invalidate();

            // 1. Swap the wildcard text buffer contents directly to new string
            Unicode::snprintf(textStatusMessageBuffer, TEXTSTATUSMESSAGE_SIZE, "Oxygenator Module Detected");
            
            // 2. Change text color to green and update visually
            textStatusMessage.setColor(COLOR_GREEN);
            textStatusMessage.invalidate();

            // 3. Make the designer-configured Continue button appear
            btnContinueNext.setVisible(true);
            btnContinueNext.invalidate();
        }
    }
}