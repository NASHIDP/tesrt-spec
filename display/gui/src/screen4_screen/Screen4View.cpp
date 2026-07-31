#include <gui/screen4_screen/Screen4View.hpp>
#include <touchgfx/Color.hpp>

Screen4View::Screen4View() :
    currentTemperature(8) // Initialize at a default safe zone value 
{
}

void Screen4View::setupScreen()
{
    Screen4ViewBase::setupScreen();
    topStatusBar4.setScreenTitle("Manual Override");

    // 1. Link custom RAM text buffers to both of wildcard widgets
    textTemp.setWildcard(tempTextBuffer);
    textStatus.setWildcard(statusTextBuffer);

    // 2. Run UI engine to format the initial text and colors on startup
    updateTemperatureUI();
}

void Screen4View::tearDownScreen()
{
    Screen4ViewBase::tearDownScreen();
}
void Screen4View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar4.handleTickEvent();

    
}

// Plus Button Logic
void Screen4View::btnPlusClicked()
{
    // Increase temperature but cap it at 15 max
    if (currentTemperature < 15)
    {
        currentTemperature++;
        updateTemperatureUI(); // Refresh the screen text and colors
    }
}

// Minus Button Logic
void Screen4View::btnMinusClicked()
{
    // Decrease temperature but cap it at 0 min
    if (currentTemperature > 0)
    {
        currentTemperature--;
        updateTemperatureUI(); // Refresh the screen text and colors
    }
}

// Core Logic Engine: Updates values, words, and hex colors dynamically
void Screen4View::updateTemperatureUI()
{
    // 1. Update the temperature digits inside the temp wildcard buffer
    Unicode::snprintf(tempTextBuffer, 10, "%d", currentTemperature);
    textTemp.invalidate(); // Force redraw of the numbers

    // 2. Evaluate ranges to pick the right text word and RGB color scheme
    uint32_t textColor = 0; // Temporary color storage holder

    if (currentTemperature >= 0 && currentTemperature <= 2)
    {
        // Critical Cold Range (Red)
        Unicode::snprintf(statusTextBuffer, 20, "Critical Cold");
        textColor = touchgfx::Color::getColorFromRGB(231, 76, 60); // Flat Red
    }
    else if (currentTemperature == 3)
    {
        // Caution Low Range (Orange)
        Unicode::snprintf(statusTextBuffer, 20, "Caution");
        textColor = touchgfx::Color::getColorFromRGB(230, 126, 34); // Flat Orange
    }
    else if (currentTemperature >= 4 && currentTemperature <= 10)
    {
        // Safe Zone Range (Green)
        Unicode::snprintf(statusTextBuffer, 20, "Safe Zone");
        textColor = touchgfx::Color::getColorFromRGB(46, 204, 113); // Flat Green
    }
    else if (currentTemperature >= 11 && currentTemperature <= 12)
    {
        // Caution High Range (Orange)
        Unicode::snprintf(statusTextBuffer, 20, "Caution");
        textColor = touchgfx::Color::getColorFromRGB(230, 126, 34); // Flat Orange
    }
    else if (currentTemperature >= 13 && currentTemperature <= 15)
    {
        // Critical Warm Range (Red)
        Unicode::snprintf(statusTextBuffer, 20, "Critical Warm");
        textColor = touchgfx::Color::getColorFromRGB(231, 76, 60); // Flat Red
    }

    // 3. Apply the chosen color to both widgets dynamically
    textTemp.setColor(textColor);
    textStatus.setColor(textColor);

    // 4. Force TouchGFX to redraw the modified text layouts
    textTemp.invalidate();
    textStatus.invalidate();
}


// Confirm Button Action
void Screen4View::btnConfirmClicked()
{
    // 1. Pass temporary screen value down to the system brain via the presenter
    presenter->saveManualTemperature(currentTemperature);
    
    // 2. Transition to Screen 5 (Thermal Stabilization)
    application().gotoScreen5ScreenNoTransition();
}