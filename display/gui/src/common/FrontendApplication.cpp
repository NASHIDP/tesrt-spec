#include <gui/common/FrontendApplication.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap),
      frameCounter(0),
      batteryTickCounter(0),
      gpsToggleCounter(0),
      simHours(10),          // Starts clock at 10 AM
      simMinutes(23),        // Starts clock at 23 minutes
      simSeconds(33),        // Starts clock at 33 seconds
      simBatteryLevel(100),  // Starts battery at full 100%
      isGpsActive(false)     // Starts with GPS inactive (showing the red/grey inactive state)
{

}