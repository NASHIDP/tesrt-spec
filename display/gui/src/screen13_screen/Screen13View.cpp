#include <gui/screen13_screen/Screen13View.hpp>
#include <touchgfx/Color.hpp>

Screen13View::Screen13View() :
    currentTemperature(8), // Safe initial values fallback
    currentPressure(20)
{
}

void Screen13View::setupScreen()
{
    Screen13ViewBase::setupScreen();
    topStatusBar13.setScreenTitle("Advanced Manual Override");

    // 1. Recover whatever configurations are currently active inside the model
    currentTemperature = presenter->getInitialTemperature();
    currentPressure = presenter->getInitialPressure();

  
    textTempAdjustVal.setWildcard(textTempAdjustValBuffer); 
    textPressAdjustVal.setWildcard(textPressAdjustValBuffer); 

    // 3. Format and paint the initial display values onto the screen
    updateConfigurationUI();
}

void Screen13View::tearDownScreen()
{
    Screen13ViewBase::tearDownScreen();
}
void Screen13View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar13.handleTickEvent();

    
}
// Temperature Minus Interaction
void Screen13View::btnTempMinusClicked()
{
    // Lower boundary limit checking at 0°C
    if (currentTemperature > 0)
    {
        currentTemperature--;
        updateConfigurationUI();
    }
}

// Temperature Plus Interaction
void Screen13View::btnTempPlusClicked()
{
    // Upper boundary limit checking at 20°C
    if (currentTemperature < 20)
    {
        currentTemperature++;
        updateConfigurationUI();
    }
}

// Pressure Minus Interaction
void Screen13View::btnPressMinusClicked()
{
    // Lower boundary limit checking at 0 mmHg
    if (currentPressure > 0)
    {
        currentPressure--;
        updateConfigurationUI();
    }
}

// Pressure Plus Interaction
void Screen13View::btnPressPlusClicked()
{
    // Upper boundary limit checking at 100 mmHg
    if (currentPressure < 100)
    {
        currentPressure++;
        updateConfigurationUI();
    }
}

// Formats numbers cleanly into text strings and pushes them to the LCD screen
void Screen13View::updateConfigurationUI()
{
    //  Using the auto-generated buffer names for Screen 13
    Unicode::snprintf(textTempAdjustValBuffer, TEXTTEMPADJUSTVAL_SIZE, "%d", currentTemperature);
    Unicode::snprintf(textPressAdjustValBuffer, TEXTPRESSADJUSTVAL_SIZE, "%d", currentPressure);

    textTempAdjustVal.invalidate();
    textPressAdjustVal.invalidate();
}

// Confirm Configuration Button Interaction (btnCnfrmConfig)
void Screen13View::btnConfirmClicked()
{
    // 1. Permanently update the system brain with both modified parameters
    presenter->saveManualConfiguration(currentTemperature, currentPressure);
    
    // 2. Direct screen change transition straight onto Screen 14
    application().gotoScreen14ScreenNoTransition();
}