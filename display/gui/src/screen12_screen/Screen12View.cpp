#include <gui/screen12_screen/Screen12View.hpp>
#include <touchgfx/utils.hpp> // Required for Unicode::snprintf

Screen12View::Screen12View()
{
}

void Screen12View::setupScreen()
{
    Screen12ViewBase::setupScreen();
    topStatusBar12.setScreenTitle("Recommended Configuration");

    // 1. Manually assign local buffers to the text area wildcards
    textTemperatureVal.setWildcard(tempBuffer);
    textPressureVal.setWildcard(pressBuffer);

    // 2. Fetch the stored active target data straight from the permanent Model via the Presenter
    int currentTemp = presenter->getActiveTargetTemperature();
    int currentPress = presenter->getActiveTargetPressure();

    // 3. Format the Temperature value into a float representation layout
    Unicode::snprintf(tempBuffer, 10, "%d.0", currentTemp);
    textTemperatureVal.invalidate();

    // 4. Format the Pressure value into an integer layout (e.g., 20)
    Unicode::snprintf(pressBuffer, 10, "%d", currentPress);
    textPressureVal.invalidate();
}

void Screen12View::tearDownScreen()
{
    Screen12ViewBase::tearDownScreen();
}
void Screen12View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar12.handleTickEvent();

    
}