#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    // Virtual function overrides from TouchGFX Designer interactions
    virtual void btn1Clicked() override;
    virtual void btn2Clicked() override;
    virtual void btn3Clicked() override;
    virtual void btn4Clicked() override;
    virtual void btn5Clicked() override;
    virtual void btn6Clicked() override;
    virtual void btn7Clicked() override;
    virtual void btn8Clicked() override;
    virtual void btn9Clicked() override;
    virtual void btn0Clicked() override;
    virtual void handleDelPressed() override;
    virtual void handleOkPressed() override;

protected:
    // Dynamic tracking variables
    uint8_t pinBuffer[6];
    uint8_t pinLength;

    // Helper functions
    void handleNumberPressed(uint8_t value);
    void updateCircleIndicators();
};

#endif // SCREEN2VIEW_HPP