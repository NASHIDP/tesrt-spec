#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    virtual void handleTickEvent()
    {
        // --- Continuous Simulation Engine Updates ---
        frameCounter++;
        
        // 1. Time Simulation (60 frames = 1 second)
        if (frameCounter >= 60)
        {
            frameCounter = 0;
            simSeconds++;
            if (simSeconds >= 60)
            {
                simSeconds = 0;
                simMinutes++;
                if (simMinutes >= 60)
                {
                    simMinutes = 0;
                    simHours++;
                    if (simHours >= 24)
                    {
                        simHours = 0;
                    }
                }
            }
        }

        // 2. Battery Simulation Loop (Drains 1% roughly every 15 seconds)
        batteryTickCounter++;
        if (batteryTickCounter >= 900) 
        {
            batteryTickCounter = 0;
            if (simBatteryLevel > 0)
            {
                simBatteryLevel--;
            }
            else
            {
                simBatteryLevel = 100; // Reset back to full for endless loop simulation
            }
        }

        // 3. GPS State Simulation Loop (Toggles Active status every 30 seconds)
        gpsToggleCounter++;
        if (gpsToggleCounter >= 1800)
        {
            gpsToggleCounter = 0;
            isGpsActive = !isGpsActive;
        }

        // --- Original Boilerplate Code Preserved ---
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }

    // Global Getters for TopStatusBar components to pull metrics
    int getSimulatedHours() const { return simHours; }
    int getSimulatedMinutes() const { return simMinutes; }
    int getSimulatedSeconds() const { return simSeconds; }
    int getSimulatedBattery() const { return simBatteryLevel; }
    bool isGpsModuleActive() const { return isGpsActive; }

private:
    // Simulation state tracking variables
    int frameCounter;
    int batteryTickCounter;
    int gpsToggleCounter;

    // Universal values accessed by the status bar across screens
    int simHours;
    int simMinutes;
    int simSeconds;
    int simBatteryLevel;
    bool isGpsActive;
};

#endif // FRONTENDAPPLICATION_HPP
