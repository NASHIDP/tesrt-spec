#ifndef SCREEN6VIEW_HPP
#define SCREEN6VIEW_HPP

#include <gui_generated/screen6_screen/Screen6ViewBase.hpp>
#include <gui/screen6_screen/Screen6Presenter.hpp>

class Screen6View : public Screen6ViewBase
{
public:
    Screen6View();
    virtual ~Screen6View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Automatically called by TouchGFX framework every frame (~60Hz)
    virtual void handleTickEvent();

    // The virtual function linked to Continue Button interaction
    virtual void btnContinueClicked();

protected:
    // Tracks the current liquid level during simulation
    int16_t currentVolume;
    const int16_t targetVolume = 1000; // Static goal volume

    // RAM text buffers required for 3 wildcard fields
    Unicode::UnicodeChar currentVolumeBuffer[16];
    Unicode::UnicodeChar tankStatusBuffer[32];
    Unicode::UnicodeChar centerStatusBuffer[32];

    // Central function to update all numbers, progress, and text/color transitions
    void updateReservoirUI();
};

#endif // SCREEN6VIEW_HPP