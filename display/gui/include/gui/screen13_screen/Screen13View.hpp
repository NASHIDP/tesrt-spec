#ifndef SCREEN13VIEW_HPP
#define SCREEN13VIEW_HPP

#include <gui_generated/screen13_screen/Screen13ViewBase.hpp>
#include <gui/screen13_screen/Screen13Presenter.hpp>

class Screen13View : public Screen13ViewBase
{
public:
    Screen13View();
    virtual ~Screen13View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    
    virtual void btnTempMinusClicked();
    virtual void btnTempPlusClicked();
    virtual void btnPressMinusClicked();
    virtual void btnPressPlusClicked();
    virtual void btnConfirmClicked();

private:
    // Core helper method to rewrite numbers to wildcards and repaint screen elements
    void updateConfigurationUI();

    // Variable counters to manage selections locally before submitting
    int currentTemperature;
    int currentPressure;
};

#endif // SCREEN13VIEW_HPP