#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    // 1. Declare the button click function
    virtual void continueButtonClicked();

    // 2. Declare the continuous engine frame tick function
    virtual void handleTickEvent();

protected:
    bool isValidating;
    int16_t tickCounter;
    const int16_t TOTAL_TICKS = 156; // 156 frames at 60Hz = ~2.6 seconds
};

#endif // SCREEN1VIEW_HPP