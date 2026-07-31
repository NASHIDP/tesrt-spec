#ifndef SCREEN15VIEW_HPP
#define SCREEN15VIEW_HPP

#include <gui_generated/screen15_screen/Screen15ViewBase.hpp>
#include <gui/screen15_screen/Screen15Presenter.hpp>
#include <touchgfx/Utils.hpp>
#include <gui/containers/AlarmMessageTemplate.hpp>

class Screen15View : public Screen15ViewBase
{
public:
    Screen15View();
    virtual ~Screen15View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Automatically called by TouchGFX on every single frame loop
    virtual void handleTickEvent();

    // Virtual interaction function overrides from TouchGFX Designer
    virtual void buttonBatteryClicked();
    virtual void buttongobackClicked();
    virtual void endProcedureClicked();
    virtual void btnAcknowledgeCrClicked();
   

private:
    // Helper function to re-format all numbers into the text widgets
    void updateDashboardUI();

    // Local Tracking Counters for Timers
    int tickCounter;          // Counts frame ticks (60 ticks = 1 second)
    
    // Elapsed Time (Starts at 00:00:00 on screen load)
    int elapsedSeconds;
    int elapsedMinutes;
    int elapsedHours;

    // Loading Time (Fixed placeholder timestamp)
    int loadSeconds;
    int loadMinutes;
    int loadHours;

    // Flushing Countdown (Dynamic Mode only)
    int flushMinutes;
    int flushSeconds;

    // Running Logic State Metrics
    int currentCycles;
    int simulatedBatteryLevel;
    bool isBatteryOverlayOpen;
    bool isTimerActive;
    bool isCriticalStateActive;

    int totalAlarmsSpawnedCount;



    // Custom RAM Wildcard Character Buffers (since Designer buffers are disabled)
    touchgfx::Unicode::UnicodeChar bufferTemp[10];
    touchgfx::Unicode::UnicodeChar bufferPress[10];
    touchgfx::Unicode::UnicodeChar bufferLoadTime[12];
    touchgfx::Unicode::UnicodeChar bufferElapsedTime[12];
    touchgfx::Unicode::UnicodeChar bufferCycleNumber[10];
    touchgfx::Unicode::UnicodeChar bufferMotorStatus[15];
    touchgfx::Unicode::UnicodeChar bufferNextFlash[12];
    
    
    // Main Panel Battery Percentage Wildcard Buffer
    touchgfx::Unicode::UnicodeChar bufferMainPercentage[10];

    // Inside Pop-up Container Overlay Buffers
    touchgfx::Unicode::UnicodeChar bufferPopupStatusStr[20];
    touchgfx::Unicode::UnicodeChar bufferPopupLevelTxt[10];
    touchgfx::Unicode::UnicodeChar bufferPopupRuntimeTxt[20];

     // --- ALERT SYSTEM SIMULATION EXTENSIONS ---
    
    // Updates the visual text counter at the top of the dashboard
    void updateAlertCountUI();

    // Secondary timer to control how often new alerts dynamically appear
    int alertSimulationTickCounter; 

    // Tracks the current active number of alarms shown on screen
    int activeAlertCount;

    // Buffer memory for the text object 'txtAlertCount' on the main dashboard
    touchgfx::Unicode::UnicodeChar bufferAlertCount[10];

    // Array pool of pre-allocated custom alarm rows (adjust size as maximum limit needed)
    static const int MAX_SIMULATED_ALARMS = 5;
    AlarmMessageTemplate dynamicAlarmCards[MAX_SIMULATED_ALARMS];
    
    // Tracks whether a particular slot in array is currently active on screen
    bool isAlarmSlotActive[MAX_SIMULATED_ALARMS];
};

#endif // SCREEN15VIEW_HPP