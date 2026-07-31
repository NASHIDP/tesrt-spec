#include <gui/screen5_screen/Screen5View.hpp>
#include <touchgfx/Color.hpp>

Screen5View::Screen5View() :
    targetTemperature(8), // Safe fallback initial value
    currentTemperature(19.8f) 
{
}

void Screen5View::setupScreen()
{
    Screen5ViewBase::setupScreen();
    topStatusBar5.setScreenTitle("Thermal Stabilization");

    // 1. Link custom RAM text buffers to our wildcard widgets
    textCurrentTemp.setWildcard(currentTempTextBuffer);
    textTargetTemp.setWildcard(targetTempTextBuffer);

    // 2. Fetch the actual running target temperature chosen by the user from the Model
    targetTemperature = presenter->getActiveTargetTemperature();

    // 3. Format the target temperature string display at the bottom (e.g., "10.0")
    Unicode::snprintfFloat(targetTempTextBuffer, 16, "%.1f", (float)targetTemperature);
    textTargetTemp.invalidate();

    // 4. Initial UI rendering
    updateStabilizationUI();
}

void Screen5View::tearDownScreen()
{
    Screen5ViewBase::tearDownScreen();
}

// Automatically runs every frame (~60 times per second)
void Screen5View::handleTickEvent()
{    
    topStatusBar5.handleTickEvent();
    // Simulate gradual cooling if current temperature is above the target
    if (currentTemperature > (float)targetTemperature)
    {
        currentTemperature -= 0.02f; // Tweak this decimal number to speed up/slow down the simulation
        
        // Prevent undershooting the target value
        if (currentTemperature < (float)targetTemperature)
        {
            currentTemperature = (float)targetTemperature;
        }

        // Refresh the UI with the updated current temperature
        updateStabilizationUI();
    }
}

// Core Engine: Updates text digits, progress ring position, and shifts colors dynamically
void Screen5View::updateStabilizationUI()
{
    // 1. Format and write the current temperature decimal string (e.g., "19.8")
    Unicode::snprintfFloat(currentTempTextBuffer, 16, "%.1f", currentTemperature);
    textCurrentTemp.invalidate();

    // 2. Dynamic Color Calculations based on Stabilization Proximity
    uint32_t activeColor = 0;
    
    // Check if fully stabilized at the exact target value
    if (currentTemperature <= (float)targetTemperature)
    {
        // Stabilized Target Reached (Bright Emerald Green)
        activeColor = touchgfx::Color::getColorFromRGB(46, 204, 113);
        if (!ContinueButton.isVisible())
       {
        ContinueButton.setVisible(true);
        ContinueButton.invalidate(); // Force-redraw the screen area to show the button
       } 
    }
    else if (currentTemperature - (float)targetTemperature <= 2.0f)
    {
        // Approaching Target Closely (Warning/Caution Orange)
        activeColor = touchgfx::Color::getColorFromRGB(230, 126, 34);
    }
    else
    {
        // Unstable / Far from Target (High Thermal Red)
        activeColor = touchgfx::Color::getColorFromRGB(231, 76, 60);
    }

    // 3. Apply calculated colors to the text widgets dynamically
    textCurrentTemp.setColor(activeColor);
    textCurrentTemp.invalidate();

    // 4. Update the Circle Progress Widget 
    // Map progress dynamically: 0°C is 0% and 25°C is 100% of the circle ring range
    int16_t progressPercentage = (int16_t)((currentTemperature / 25.0f) * 100.0f);
    
    // Bounds checking for the progress calculation range
    if (progressPercentage > 100) progressPercentage = 100;
    if (progressPercentage < 0)   progressPercentage = 0;

    circleProgress.setValue(progressPercentage);
    
    // Update the visual color of the progress bar arc line itself to match the system state
    circleProgressPainter.setColor(activeColor);
    circleProgress.setPainter(circleProgressPainter);
    circleProgress.invalidate();
}

void Screen5View::btnContinueClicked()
{
    
    application().gotoScreen6ScreenNoTransition(); 
}