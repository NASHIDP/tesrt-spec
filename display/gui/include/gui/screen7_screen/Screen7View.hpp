#ifndef SCREEN7VIEW_HPP
#define SCREEN7VIEW_HPP

#include <gui_generated/screen7_screen/Screen7ViewBase.hpp>
#include <gui/screen7_screen/Screen7Presenter.hpp>

class Screen7View : public Screen7ViewBase
{
public:
    Screen7View();
    virtual ~Screen7View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    // Automatically runs every single frame (~60 FPS) to execute countdown clock
    virtual void handleTickEvent();

    // Triggered automatically when the continue button on stage 3 is clicked
    virtual void btnContinueClicked();

protected:
    // Enumeration to track exactly which virtual window layout state is currently active
    enum ValidationStage
    {
        STAGE_1_PRIMING,
        STAGE_2_BUBBLE_DETECTION,
        STAGE_3_SUCCESS
    };
    ValidationStage currentStage;

    // Timer & Flow Tracking Variables
    int16_t currentCycle;     // Tracks either Cycle 1 or Cycle 2
    int16_t secondsRemaining; // Tracks remaining seconds in active countdown
    int16_t tickCounter;      // Ticks up to 60 to calculate a true 1-second interval

    // RAM Character Buffers for Wildcard Displays
    Unicode::UnicodeChar cycleBuffer[8];
    Unicode::UnicodeChar countdownBuffer[12];

    // Core internal helper engines
    void initStage(ValidationStage newStage);
    void handleStageTimers();
    void updateStageUI();
};

#endif // SCREEN7VIEW_HPP