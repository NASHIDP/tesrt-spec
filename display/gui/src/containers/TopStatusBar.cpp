#include <gui/containers/TopStatusBar.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/Color.hpp>

TopStatusBar::TopStatusBar()
{
}

void TopStatusBar::initialize()
{
    TopStatusBarBase::initialize();
}
void TopStatusBar::setScreenTitle(const char* titleStr)
{
    
    touchgfx::Unicode::strncpy(textScreenTitleBuffer, titleStr, TEXTSCREENTITLE_SIZE);
    textScreenTitle.invalidate();
}
void TopStatusBar::handleTickEvent()
{
    // Access the central FrontendApplication controller
    FrontendApplication* app = static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    if (app == nullptr)
    {
        return;
    }

    // ----------------------------------------------------
    // 1. GPS VISIBILITY LOGIC
    // ----------------------------------------------------
    bool isGpsActive = app->isGpsModuleActive();
    
    // Toggle visibilities based on requirements
    gpsactive.setVisible(isGpsActive);
    gpsinactive.setVisible(!isGpsActive);
    
    gpsactive.invalidate();
    gpsinactive.invalidate();

    // ----------------------------------------------------
    // 2. REAL-WORLD TIME LOGIC (hh:mm:ss)
    // ----------------------------------------------------
    int hours = app->getSimulatedHours();
    int minutes = app->getSimulatedMinutes();
    int seconds = app->getSimulatedSeconds();

    // Format the time string directly into the text wildcard buffer
    touchgfx::Unicode::snprintf(txtTimeBuffer, TXTTIME_SIZE, "%02d:%02d:%02d", hours, minutes, seconds);
    txtTime.invalidate();

    // ----------------------------------------------------
    // 3. BATTERY METER & COLOR RANGE LOGIC
    // ----------------------------------------------------
    int batteryLevel = app->getSimulatedBattery();

    // Update numeric text layout wildcard buffer
    touchgfx::Unicode::snprintf(txtBatteryBuffer, TXTBATTERY_SIZE, "%d%", batteryLevel);

    // Dynamic Range Color Codes for text
    if (batteryLevel > 50)
    {
        // High Battery: Crisp White/Greenish White
        txtBattery.setColor(touchgfx::Color::getColorFromRGB(0xF8, 0xFA, 0xFC));
    }
    else if (batteryLevel > 20)
    {
        // Medium Battery: Warning Orange
        txtBattery.setColor(touchgfx::Color::getColorFromRGB(0xF5, 0x9E, 0x0B));
    }
    else
    {
        // Low Battery: Critical Alert Red
        txtBattery.setColor(touchgfx::Color::getColorFromRGB(0xEF, 0x44, 0x44));
    }
    txtBattery.invalidate();

    // Update Image Progress Widget value
    BatteryProgress.setValue(batteryLevel);
    BatteryProgress.invalidate();
}