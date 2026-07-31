#include <gui/screen6_screen/Screen6View.hpp>
#include <touchgfx/Color.hpp>

Screen6View::Screen6View() :
    currentVolume(0) // Start empty at 0 mL
{
}

void Screen6View::setupScreen()
{
    Screen6ViewBase::setupScreen();
    topStatusBar6.setScreenTitle("Reservoir Fill");

    // 1. Link custom text RAM buffers to the 3 wildcard widgets
    textCurrentVolume.setWildcard(currentVolumeBuffer);
    textTankStatus.setWildcard(tankStatusBuffer);
    textCenterStatus.setWildcard(centerStatusBuffer);

    // 2. Setup initial text strings for the filling phase
    Unicode::snprintf(tankStatusBuffer, 32, "Filling in Progress...");
    Unicode::snprintf(centerStatusBuffer, 32, "Filling in Progress...");

    // 3. Initial UI Draw
    updateReservoirUI();
}

void Screen6View::tearDownScreen()
{
    Screen6ViewBase::tearDownScreen();
}

// Automatically runs ~60 times per second
void Screen6View::handleTickEvent()
{    
    topStatusBar6.handleTickEvent();
    // Simulate water filling up until it hits the target (500 mL)
    if (currentVolume < targetVolume)
    {
        currentVolume += 2; // Adjust this number to speed up or slow down the fill speed
        
        if (currentVolume > targetVolume)
        {
            currentVolume = targetVolume;
        }

        // Refresh numbers, colors, and progress positions
        updateReservoirUI();
    }
}

// The core rendering engine for Screen 6
void Screen6View::updateReservoirUI()
{
    // 1. Continually update the dynamic "Current Volume" box number
    Unicode::snprintf(currentVolumeBuffer, 16, "%d", currentVolume);
    textCurrentVolume.invalidate();

    // 2. Check if filling is complete to shift colors and update text strings
    if (currentVolume >= targetVolume)
    {
        // TARGET REACHED: Switch UI theme to Emerald Green
        uint32_t greenColor = touchgfx::Color::getColorFromRGB(46, 204, 113);

        // Change Text colors
        textCurrentVolume.setColor(greenColor);
        textTankStatus.setColor(greenColor);
        textCenterStatus.setColor(greenColor);

        // Update the 2 status texts to their final strings
        Unicode::snprintf(tankStatusBuffer, 32, "Fill Complete");
        Unicode::snprintf(centerStatusBuffer, 32, "Reservoir Fill Complete");

        // Make the Continue Button pop up
        if (!ContinueButton.isVisible())
        {
            ContinueButton.setVisible(true);
            ContinueButton.invalidate();
        }
    }
    else
    {
        // STILL FILLING: Keep UI theme Blue
        uint32_t blueColor = touchgfx::Color::getColorFromRGB(52, 152, 219); // Tweak RGB to match your exact Figma blue

        textCurrentVolume.setColor(blueColor);
        textTankStatus.setColor(blueColor);
        textCenterStatus.setColor(blueColor);
    }

    // 3. Update the Circle Progress Ring Position (0 to 100%)
    int16_t progressPercentage = (int16_t)(((float)currentVolume / (float)targetVolume) * 100.0f);
    reservoirProgress.setValue(progressPercentage);

    // 4. Force TouchGFX to redraw all modified elements
    textCurrentVolume.invalidate();
    textTankStatus.invalidate();
    textCenterStatus.invalidate();
    reservoirProgress.invalidate();
}

// Called automatically when the user taps the newly visible Continue Button
void Screen6View::btnContinueClicked()
{
    
    application().gotoScreen7ScreenNoTransition(); 
}