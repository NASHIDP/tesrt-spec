#include <gui/screen17_screen/Screen17View.hpp>

Screen17View::Screen17View() :
    progressCounter(0)
{
}

void Screen17View::setupScreen()
{
    Screen17ViewBase::setupScreen();
    topStatusBar17.setScreenTitle("Transport Summary");

    // 1. Assign custom RAM buffers to the TouchGFX Text widgets
    organIdValueText.setWildcard(organIdBuffer);
    organWeightValueText.setWildcard(organWeightBuffer);
    bloodTypeValueText.setWildcard(bloodTypeBuffer);
    harvestHospitalValueText.setWildcard(harvestHospitalBuffer);

    totalPreservationTimeValueText.setWildcard(totalPreservationTimeBuffer);

    minTempValueText.setWildcard(minTempBuffer);
    maxTempValueText.setWildcard(maxTempBuffer);
    avgTempValueText.setWildcard(avgTempBuffer);

    minPressureValueText.setWildcard(minPressureBuffer);
    maxPressureValueText.setWildcard(maxPressureBuffer);
    avgPressureValueText.setWildcard(avgPressureBuffer);

    totalAlarmsCountText.setWildcard(totalAlarmsCountBuffer);
    alarmLogText.setWildcard(alarmLogBuffer);

    batterySwapsCountText.setWildcard(batterySwapsCountBuffer);
    batteryLogText.setWildcard(batteryLogBuffer);

    // 2. Initial Visibility Setup
    loadingContainer.setVisible(true);
    summaryScrollContainer.setVisible(false);
    
    shutdownButton.setVisible(false);

    savingCircleProgress.setValue(0);
    invalidate();
}

void Screen17View::tearDownScreen()
{
    Screen17ViewBase::tearDownScreen();
}

void Screen17View::handleTickEvent()
{   
    topStatusBar17.handleTickEvent();
    if (progressCounter < 100)
    {
        progressCounter++;
        savingCircleProgress.setValue(progressCounter);
        savingCircleProgress.invalidate();

        if (progressCounter == 100)
        {
            showSummaryDashboard();
        }
    }
}

void Screen17View::showSummaryDashboard()
{
    loadingContainer.setVisible(false);
    summaryScrollContainer.setVisible(true);
    
    shutdownButton.setVisible(true);

    populateMockData();
    invalidate();
}

void Screen17View::populateMockData()
{
    // --- 1. Organ Details (Fetched Dynamically from Model via UTF-8 Conversion) ---
    Unicode::fromUTF8(reinterpret_cast<const uint8_t*>(presenter->getOrganID()), organIdBuffer, STANDARD_BUFFER_SIZE);
    
    // Correctly declare a UnicodeChar temporary buffer for the weight
    Unicode::UnicodeChar weightTempUnicodeBuffer[STANDARD_BUFFER_SIZE];
    Unicode::fromUTF8(reinterpret_cast<const uint8_t*>(presenter->getOrganWeight()), weightTempUnicodeBuffer, STANDARD_BUFFER_SIZE);
    
    // Format the weight using %s to combine the Unicode weight string and " g"
    Unicode::snprintf(organWeightBuffer, STANDARD_BUFFER_SIZE, "%s g", weightTempUnicodeBuffer);

    Unicode::fromUTF8(reinterpret_cast<const uint8_t*>(presenter->getBloodType()), bloodTypeBuffer, STANDARD_BUFFER_SIZE);
    Unicode::fromUTF8(reinterpret_cast<const uint8_t*>(presenter->getHarvestHospital()), harvestHospitalBuffer, STANDARD_BUFFER_SIZE);

    Unicode::snprintf(totalPreservationTimeBuffer, STANDARD_BUFFER_SIZE, "%d h %d min %d sec",presenter->getFinalHours(),presenter->getFinalMinutes(),presenter->getFinalSeconds());

    // --- 3. Temperature Summary ---
    Unicode::snprintf(minTempBuffer, STANDARD_BUFFER_SIZE, "4.2 C");
    Unicode::snprintf(maxTempBuffer, STANDARD_BUFFER_SIZE, "7.8 C");
    Unicode::snprintf(avgTempBuffer, STANDARD_BUFFER_SIZE, "5.5 C");

    // --- 4. Pressure Summary ---
    Unicode::snprintf(minPressureBuffer, STANDARD_BUFFER_SIZE, "14 mmHg");
    Unicode::snprintf(maxPressureBuffer, STANDARD_BUFFER_SIZE, "20 mmHg");
    Unicode::snprintf(avgPressureBuffer, STANDARD_BUFFER_SIZE, "17 mmHg");

    // --- 5. Alarm Events ---
    Unicode::snprintf(totalAlarmsCountBuffer, STANDARD_BUFFER_SIZE, "2");
    Unicode::snprintf(alarmLogBuffer, LOG_BUFFER_SIZE, "Pressure High - 02:14:30\nTemp Deviation - 03:44:12");

    // --- 6. Battery Events ---
    Unicode::snprintf(batterySwapsCountBuffer, STANDARD_BUFFER_SIZE, "1");
    Unicode::snprintf(batteryLogBuffer, LOG_BUFFER_SIZE, "Battery replaced at 01:48:22");

    // Force components to visual update
    organDetailsContainer.invalidate();
    preservationTimeContainer.invalidate();
    temperatureSummaryContainer.invalidate();
    pressureSummaryContainer.invalidate();
    alarmEventsContainer.invalidate();
    batteryEventsContainer.invalidate();
}