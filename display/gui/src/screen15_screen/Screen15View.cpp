#include <gui/screen15_screen/Screen15View.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>  

// Color definitions 
#define COLOR_GREEN     touchgfx::Color::getColorFromRGB(0x10, 0xB9, 0x81) // Running
#define COLOR_GREY      touchgfx::Color::getColorFromRGB(0x94, 0xA3, 0xB8) // Idle / Muted
#define COLOR_RED       touchgfx::Color::getColorFromRGB(0xEF, 0x44, 0x44) // Critical
#define COLOR_ORANGE    touchgfx::Color::getColorFromRGB(0xF9, 0x73, 0x16) // Warning


Screen15View::Screen15View() :
    tickCounter(0),
    elapsedSeconds(0),
    elapsedMinutes(0),
    elapsedHours(0),
    flushMinutes(55),    // Flushing cycle starts counting down from 55 mins
    flushSeconds(0),
    currentCycles(0),    // Initial count template match
    simulatedBatteryLevel(100), // Initial 12% matches screen capture
    isBatteryOverlayOpen(false),
    isCriticalStateActive(false),
    totalAlarmsSpawnedCount(0),
    alertSimulationTickCounter(0),
    activeAlertCount(0)
    
{
    isTimerActive = true;
    for (int i = 0; i < MAX_SIMULATED_ALARMS; i++)
    {
        isAlarmSlotActive[i] = false;
    }
}

void Screen15View::setupScreen()
{
    Screen15ViewBase::setupScreen();
    topStatusBar15.setScreenTitle("Active Preservation");
    FrontendApplication* app = static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    if (app != nullptr)
    {
        loadHours = app->getSimulatedHours();
        loadMinutes = app->getSimulatedMinutes();
        loadSeconds = app->getSimulatedSeconds();
        simulatedBatteryLevel = app->getSimulatedBattery();
    }

    // Bind custom text wildcard arrays into each respective widget pointer layout
    textTempVal.setWildcard(bufferTemp);
    textPressVal.setWildcard(bufferPress);
    textLoadTime.setWildcard(bufferLoadTime);
    textElapsedTime.setWildcard(bufferElapsedTime);
    textCycleNumber.setWildcard(bufferCycleNumber);
    textMotorStatus.setWildcard(bufferMotorStatus);
    textNextFlash.setWildcard(bufferNextFlash);
    
    // Bind main screen battery tracker text wildcard
    
    textPercentage.setWildcard(bufferMainPercentage);

    // Bind battery popup panel tracking wildcards
    textBatteryStatus.setWildcard(bufferPopupStatusStr);
    textBatteryLevel.setWildcard(bufferPopupLevelTxt);
    textRemainingRuntime.setWildcard(bufferPopupRuntimeTxt);

    txtAlertCount.setWildcard(bufferAlertCount);
    updateAlertCountUI();

    // Initial state hides battery pop-up overlay elements on launch
    containerBattery.setVisible(false);
    buttongoback.setVisible(false);
    
    containerBattery.invalidate();
    buttongoback.invalidate();

    for (int i = 0; i < MAX_SIMULATED_ALARMS; i++)
    {
        dynamicAlarmCards[i].initialize();
    }

    containerCritical.setVisible(false);
    containerCritical.invalidate();
    

    // Synchronize initial configuration parameters from system core storage memory
    updateDashboardUI();
}

void Screen15View::tearDownScreen()
{
    Screen15ViewBase::tearDownScreen();
}

// Automatically triggers at 60Hz frame loops
void Screen15View::handleTickEvent()
{   
    topStatusBar15.handleTickEvent();
    FrontendApplication* app = static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    if (app != nullptr)
    {
        simulatedBatteryLevel = app->getSimulatedBattery();
    }
    // ONLY count up time if the procedure is actively running
    if (!isTimerActive)
    {
        return; 
    }
    tickCounter++;

    // --- ALERT RUNTIME SIMULATION COUNTER ---
    // This master switch completely bypasses the alert generator once a critical state is active!
    if (!isCriticalStateActive)
    {
        alertSimulationTickCounter++;

        // Trigger a potential new alarm event roughly every 5 seconds (300 frames)
        if (alertSimulationTickCounter >= 300)
        {
            alertSimulationTickCounter = 0;

            // Find the first empty room slot in the custom container array
            int freeSlot = -1;
            for (int i = 0; i < MAX_SIMULATED_ALARMS; i++)
            {
                if (!isAlarmSlotActive[i])
                {
                    freeSlot = i;
                    break;
                }
            }

            
            // If a free slot is available, spawn our sequential simulated alarms
            if (freeSlot != -1)
            {
                isAlarmSlotActive[freeSlot] = true;
                dynamicAlarmCards[freeSlot].setID(freeSlot);

                // ADD THIS SEQUENTIAL STATE LOGIC:
                if (totalAlarmsSpawnedCount < 3)
                {
                    // First 3 generated alarms will strictly be Warnings
                    dynamicAlarmCards[freeSlot].setupAlarmCard("Battery Low Warning", "System backup battery power level has dropped below 15%!", COLOR_ORANGE);
                }
                else
                {
                    // The 4th alarm will trigger the Critical overlay
                    dynamicAlarmCards[freeSlot].setupAlarmCard("Pressure Critical", "Perfusion pressure has exceeded safe threshold limit!", COLOR_RED);

                    touchgfx::Unicode::strncpy(textCriticalTitleBuffer, "Pressure Critical", 32);
                    touchgfx::Unicode::strncpy(textCriticalDescriptionBuffer, "Perfusion pressure has exceeded safe threshold limit!", 128);
                    
                    textCriticalTitle.invalidate();
                    textCriticalDescription.invalidate();
                    
                    containerCritical.setVisible(true);
                    containerCritical.invalidate();

                    isCriticalStateActive = true; 
                }
                
                // Increment our sequential tracker counter
                totalAlarmsSpawnedCount++; 

                // Drop the card right into the dynamic layout list layout container
                listAlarmMessages.add(dynamicAlarmCards[freeSlot]);

                activeAlertCount++;
                
                // Refresh the elements
                listAlarmMessages.invalidate();
                scrollAlarmBox.invalidate();
                updateAlertCountUI();
            }
        }
    }

 
    
    // Once exactly 60 ticks have elapsed, 1 full second has passed
    if (tickCounter >= 60)
    {
        tickCounter = 0;
        elapsedSeconds++;

        // --- 1. Increment Elapsed Time System ---
        if (elapsedSeconds >= 60)
        {
            elapsedSeconds = 0;
            elapsedMinutes++;

            if (elapsedMinutes >= 60)
            {
                elapsedMinutes = 0;
                elapsedHours++;

                // Trigger Cycle Increment every hour ONLY if preservation mode is Dynamic
                if (presenter->getPreservationMode() == PRESERVATION_DYNAMIC)
                {
                    currentCycles++;
                }
            }
        }

        // --- 2. Decrement Flushing Countdown System (Dynamic Only) ---
        if (presenter->getPreservationMode() == PRESERVATION_DYNAMIC)
        {
            if (flushSeconds == 0)
            {
                if (flushMinutes > 0)
                {
                    flushMinutes--;
                    flushSeconds = 59;
                }
                else
                {
                    // Reset back to 55 minutes once the countdown fully hits zero
                    flushMinutes = 55;
                    flushSeconds = 0;
                }
            }
            else
            {
                flushSeconds--;
            }
        }

        

        // Repaint all updated counters to screen canvas layout
        updateDashboardUI();
    }
}

// Central processing function to format string buffers and paint pixels
void Screen15View::updateDashboardUI()
{
    // A. Fetch raw Target bounds from Model storage
    int currentTempSetting = presenter->getTargetTemperature();
    int currentPressSetting = presenter->getTargetPressure();

    // B. Write digits into primitive widget wildcard buffers
    Unicode::snprintf(bufferTemp, 10, "%d", currentTempSetting);
    Unicode::snprintf(bufferPress, 10, "%d", currentPressSetting);

    // C. Format Time Wildcards (HH:MM:SS format)
    Unicode::snprintf(bufferLoadTime, 12, "%02d:%02d:%02d", loadHours, loadMinutes, loadSeconds);
    Unicode::snprintf(bufferElapsedTime, 12, "%02d:%02d:%02d", elapsedHours, elapsedMinutes, elapsedSeconds);

    // D. Fetch Mode Check for Cycle Number / Next Flushing layout display conditions
    PreservationMode currentMode = presenter->getPreservationMode();

    // If a critical alarm is active, force dashboard variables to mimic Static Cold Storage Mode!
    if (isCriticalStateActive || currentMode != PRESERVATION_DYNAMIC)
    {
        // Non-dynamic profiles (or active critical override states) print clean dash markers
        Unicode::strncpy(bufferCycleNumber, "--", 10);
        Unicode::strncpy(bufferNextFlash, "--:--", 12);
    }
    else
    {
        Unicode::snprintf(bufferCycleNumber, 10, "%d", currentCycles);
        Unicode::snprintf(bufferNextFlash, 12, "%02d:%02d", flushMinutes, flushSeconds);
    }

    // E. Dynamic Motor Status Evaluation
    if (isCriticalStateActive)
    {
        // Force motor to stop running and display "Idle"
        Unicode::strncpy(bufferMotorStatus, "Idle", 15);
        textMotorStatus.setColor(COLOR_GREY);
    }
    else if (currentMode == PRESERVATION_HYPOTHERMIC)
    {
        Unicode::strncpy(bufferMotorStatus, "Running", 15);
        textMotorStatus.setColor(COLOR_GREEN);
    }
    else if (currentMode == PRESERVATION_DYNAMIC)
    {
        // Runs specifically on the 55th minute block of each hour cycle
        if (elapsedMinutes == 55)
        {
            Unicode::strncpy(bufferMotorStatus, "Running", 15);
            textMotorStatus.setColor(COLOR_GREEN);
        }
        else
        {
            Unicode::strncpy(bufferMotorStatus, "Idle", 15);
            textMotorStatus.setColor(COLOR_GREY);
        }
    }
    else // PRESERVATION_STATIC or PRESERVATION_NONE
    {
        Unicode::strncpy(bufferMotorStatus, "Idle", 15);
        textMotorStatus.setColor(COLOR_GREY);
    }

    // F. Main Dashboard Battery Readout Indicator
    Unicode::snprintf(bufferMainPercentage, 10, "%d%", simulatedBatteryLevel);

   // G. Pop-up Panel Inner Overlay Sub-system Information Mapping
    Unicode::snprintf(bufferPopupLevelTxt, 10, "%d %", simulatedBatteryLevel);

    // Calculate dynamic runtime hours and minutes based on battery level
    int remainingHours = (simulatedBatteryLevel * 8) / 100; // Scales up to ~8 hours maximum
    int remainingMinutes = (simulatedBatteryLevel * 45 / 100) % 60;

    // Standardize runtime text format across all battery percentages (e.g., "8 hr 15 mnt")
    Unicode::snprintf(bufferPopupRuntimeTxt, 20, "%d hr %d mnt", remainingHours, remainingMinutes);

    // Only update the status header string based on thresholds
    if (simulatedBatteryLevel >= 95)
    {
        Unicode::strncpy(bufferPopupStatusStr, "Fully Charged", 20);
    }
    else if (simulatedBatteryLevel <= 15)
    {
        Unicode::strncpy(bufferPopupStatusStr, "Battery Low", 20);
    }
    else
    {
        Unicode::strncpy(bufferPopupStatusStr, "Discharging", 20);
    }

    // H. Direct update to Built-in Image Progress Indicator value
    PercentageProgress.setValue(simulatedBatteryLevel);

    // Invalidate widgets across the panel to trigger layout repaints
    textTempVal.invalidate();
    textPressVal.invalidate();
    textLoadTime.invalidate();
    textElapsedTime.invalidate();
    textCycleNumber.invalidate();
    textMotorStatus.invalidate();
    textNextFlash.invalidate();
    PercentageProgress.invalidate();
    textPercentage.invalidate();
    
    if (isBatteryOverlayOpen)
    {
        textBatteryStatus.invalidate();
        textBatteryLevel.invalidate();
        textRemainingRuntime.invalidate();
    }
}

// Interaction 1: User clicks main panel battery status block button
void Screen15View::buttonBatteryClicked()
{
    isBatteryOverlayOpen = true;

    // Show pop-up panel container layout details cleanly
    containerBattery.setVisible(true);
    buttongoback.setVisible(true); // Makes invisible touch target interceptor block ready

    containerBattery.invalidate();
    buttongoback.invalidate();
    
    updateDashboardUI();
}

// Interaction 2: User clicks outside layout box onto full screen transparent button
void Screen15View::buttongobackClicked()
{
    isBatteryOverlayOpen = false;

    // Hide pop-up layer structures instantly from rendering frame bounds
    containerBattery.setVisible(false);
    buttongoback.setVisible(false); // Turn off invisible capture target so user can touch main elements again

    containerBattery.invalidate();
    buttongoback.invalidate();
}


void Screen15View::endProcedureClicked()
{
    // 1. Instantly stop the local tick execution
    isTimerActive = false;

    // 2. Transmit the frozen time snapshots down to the model layer
    presenter->storeProcedureDuration(elapsedHours, elapsedMinutes, elapsedSeconds);

   
    application().gotoScreen16ScreenNoTransition(); 
}

void Screen15View::updateAlertCountUI()
{
    // Format the number string into the text container
    touchgfx::Unicode::snprintf(bufferAlertCount, 10, "%d", activeAlertCount);
    txtAlertCount.invalidate();
}

void Screen15View::btnAcknowledgeCrClicked()
{
    // 1. Hide the critical popup overlay
    containerCritical.setVisible(false);
    containerCritical.invalidate();

    // 2. leave isCriticalStateActive = true so the dashboard remains locked 
    // in its "Static Cold Storage" visual state, even after closing the alert!
    updateDashboardUI();
}