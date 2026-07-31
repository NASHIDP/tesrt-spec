#ifndef SCREEN5VIEW_HPP
#define SCREEN5VIEW_HPP

#include <gui_generated/screen5_screen/Screen5ViewBase.hpp>
#include <gui/screen5_screen/Screen5Presenter.hpp>

class Screen5View : public Screen5ViewBase
{
public:
    Screen5View();
    virtual ~Screen5View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    

    // Virtual function called by TouchGFX framework every frame (~60Hz)
    virtual void handleTickEvent();
    virtual void btnContinueClicked();

protected:
    // 1. Storage for tracking temperature values locally
    int16_t targetTemperature;
    float currentTemperature;

    // 2. RAM buffers for the dynamic text wildcards
    Unicode::UnicodeChar currentTempTextBuffer[16];
    Unicode::UnicodeChar targetTempTextBuffer[16];

    // 3. Central engine to calculate progress arc position and dynamic text/circle colors
    void updateStabilizationUI();
};

#endif // SCREEN5VIEW_HPP