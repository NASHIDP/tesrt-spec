#include <gui/screen11_screen/Screen11View.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/utils.hpp> 

#define COLOR_GREEN touchgfx::Color::getColorFromRGB(0x10, 0xB9, 0x81)

Screen11View::Screen11View() :
    tickCounter(0),
    currentCycle(1),
    totalSeconds(60),
    holdTimer(0),
    isComplete(false)
{
}

void Screen11View::setupScreen()
{
    Screen11ViewBase::setupScreen();
    topStatusBar11.setScreenTitle("Oxygenator Priming");

    // Link manual wildcard buffers up to the widgets safely
    textPurgeCountdown.setWildcard(countdownBuffer);
    textPurgeCycle.setWildcard(cycleBuffer);
    textprogress.setWildcard(progressTextBuffer);

    // Initial state setup for the progress indicator
    Primingprogress.setValue(0);
    
    // Set text to green instantly on start and assign the status text string
    textprogress.setColor(COLOR_GREEN);
    Unicode::snprintf(progressTextBuffer, 40, "Deairing in Progress...");
    textprogress.invalidate();

    updateTimerDisplay();
    updateCycleDisplay();
}

void Screen11View::tearDownScreen()
{
    Screen11ViewBase::tearDownScreen();
}

void Screen11View::handleTickEvent()
{  
    topStatusBar11.handleTickEvent();
   // If everything is done, run our brief 1.5-second visual pause before switching screens
    if (isComplete)
    {
        holdTimer++;
        if (holdTimer >= 90) // 90 ticks = Exactly 1.5 seconds at 60fps
        {
            application().gotoScreen12ScreenNoTransition();
        }
        return; 
    }

    tickCounter++;

    if (tickCounter >= 60)
    {
        tickCounter = 0; 

        if (totalSeconds > 0)
        {
            totalSeconds--;
            updateTimerDisplay();

            // Progress tracking equation inside individual 60s windows
            int currentProgress = ((60 - totalSeconds) * 100) / 60;
            Primingprogress.setValue(currentProgress);
            Primingprogress.invalidate();
        }

        // Handle cycle rollover conditions safely
        if (totalSeconds == 0)
        {
            if (currentCycle == 1)
            {
                currentCycle = 2;
                totalSeconds = 60; 
                Primingprogress.setValue(0); 
                
                updateCycleDisplay();
                updateTimerDisplay();
                Primingprogress.invalidate();
            }
            else if (currentCycle == 2)
            {
                // Trigger the completion state sequence
                isComplete = true;

                // Update text area message dynamically
                Unicode::snprintf(progressTextBuffer, 40, "Priming Complete");
                textprogress.invalidate();
            }
        }
    }
}

void Screen11View::updateTimerDisplay()
{
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    Unicode::snprintf(countdownBuffer, 10, "%02d:%02d", minutes, seconds);
    textPurgeCountdown.invalidate();
}

void Screen11View::updateCycleDisplay()
{
  
    Unicode::snprintf(cycleBuffer, 15, "%d / 2", currentCycle);
    textPurgeCycle.invalidate();
}