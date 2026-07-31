#ifndef SCREEN17VIEW_HPP
#define SCREEN17VIEW_HPP

#include <gui_generated/screen17_screen/Screen17ViewBase.hpp>
#include <gui/screen17_screen/Screen17Presenter.hpp>
#include <touchgfx/Utils.hpp>

class Screen17View : public Screen17ViewBase
{
public:
    Screen17View();
    virtual ~Screen17View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

private:
    void showSummaryDashboard();
    void populateMockData();

    int progressCounter;

    // --- Manually Declared Buffer Sizes ---
    static const uint16_t STANDARD_BUFFER_SIZE = 32;
    static const uint16_t LOG_BUFFER_SIZE = 128;

    // --- Manually Declared RAM Buffers ---
    Unicode::UnicodeChar organIdBuffer[STANDARD_BUFFER_SIZE];
    Unicode::UnicodeChar organWeightBuffer[STANDARD_BUFFER_SIZE];
    Unicode::UnicodeChar bloodTypeBuffer[STANDARD_BUFFER_SIZE];
    Unicode::UnicodeChar harvestHospitalBuffer[STANDARD_BUFFER_SIZE];
    
    Unicode::UnicodeChar totalPreservationTimeBuffer[STANDARD_BUFFER_SIZE];

    Unicode::UnicodeChar minTempBuffer[STANDARD_BUFFER_SIZE];
    Unicode::UnicodeChar maxTempBuffer[STANDARD_BUFFER_SIZE];
    Unicode::UnicodeChar avgTempBuffer[STANDARD_BUFFER_SIZE];

    Unicode::UnicodeChar minPressureBuffer[STANDARD_BUFFER_SIZE];
    Unicode::UnicodeChar maxPressureBuffer[STANDARD_BUFFER_SIZE];
    Unicode::UnicodeChar avgPressureBuffer[STANDARD_BUFFER_SIZE];

    Unicode::UnicodeChar totalAlarmsCountBuffer[STANDARD_BUFFER_SIZE];
    Unicode::UnicodeChar alarmLogBuffer[LOG_BUFFER_SIZE];

    Unicode::UnicodeChar batterySwapsCountBuffer[STANDARD_BUFFER_SIZE];
    Unicode::UnicodeChar batteryLogBuffer[LOG_BUFFER_SIZE];
};

#endif // SCREEN17VIEW_HPP