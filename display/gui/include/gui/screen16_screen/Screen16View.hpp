#ifndef SCREEN16VIEW_HPP
#define SCREEN16VIEW_HPP

#include <gui_generated/screen16_screen/Screen16ViewBase.hpp>
#include <gui/screen16_screen/Screen16Presenter.hpp>

class Screen16View : public Screen16ViewBase
{
public:
    Screen16View();
    virtual ~Screen16View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    // Virtual interaction function overrides from TouchGFX Designer
    virtual void flexButtonStep1Clicked();
    virtual void flexButtonStep2Clicked();
    virtual void flexButtonStep3Clicked();

private:
    // Tracks completion state of each sequential step
    bool isStep1Completed;
    bool isStep2Completed;
    bool isStep3Completed;

    // Helper method to look at state and update colors/visibilities safely
    void refreshChecklistUI();
};

#endif // SCREEN16VIEW_HPP