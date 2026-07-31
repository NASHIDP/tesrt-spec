#ifndef SCREEN11VIEW_HPP
#define SCREEN11VIEW_HPP

#include <gui_generated/screen11_screen/Screen11ViewBase.hpp>
#include <gui/screen11_screen/Screen11Presenter.hpp>

class Screen11View : public Screen11ViewBase
{
public:
    Screen11View();
    virtual ~Screen11View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    virtual void handleTickEvent();

private:
    int tickCounter;
    int currentCycle;    
    int totalSeconds;    
    int holdTimer;       //Pause counter for the final success message
    bool isComplete;     //Tracks if the dual-cycle is fully finished

    // Manual Wildcard Character Buffers for Screen 11
    touchgfx::Unicode::UnicodeChar countdownBuffer[10];
    touchgfx::Unicode::UnicodeChar cycleBuffer[15]; 
    touchgfx::Unicode::UnicodeChar progressTextBuffer[40];

    void updateTimerDisplay();
    void updateCycleDisplay();
};

#endif // SCREEN11VIEW_HPP