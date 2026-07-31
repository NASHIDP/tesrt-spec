#ifndef SCREEN9VIEW_HPP
#define SCREEN9VIEW_HPP

#include <gui_generated/screen9_screen/Screen9ViewBase.hpp>
#include <gui/screen9_screen/Screen9Presenter.hpp>

class Screen9View : public Screen9ViewBase
{
public:
    Screen9View();
    virtual ~Screen9View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    // Virtual functions created in the Designer interactions
    void btnHypothermicClicked() override;
    void btnDynamicClicked() override;
    void btnStaticClicked() override;
    void btnConfirmContinueClicked() override;

private:
    // Tracking enum to remember preservation mode state cleanly
    enum PreservationMode
    {
        NONE = 0,
        HYPOTHERMIC,
        DYNAMIC,
        STATIC
    };

    PreservationMode currentSelection;

    // Helper function to update button highlight colors cleanly
    void updateButtonVisuals();
};

#endif // SCREEN9VIEW_HPP