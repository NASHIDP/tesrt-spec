#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View() : pinLength(0)
{
    // Initialize empty buffer array mapping
    for(int i = 0; i < 6; i++) {
        pinBuffer[i] = 0;
    }
}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    updateCircleIndicators();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}
void Screen2View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar2.handleTickEvent();

    
}
// Route UI interactions into a single processing controller
void Screen2View::btn1Clicked() { handleNumberPressed(1); }
void Screen2View::btn2Clicked() { handleNumberPressed(2); }
void Screen2View::btn3Clicked() { handleNumberPressed(3); }
void Screen2View::btn4Clicked() { handleNumberPressed(4); }
void Screen2View::btn5Clicked() { handleNumberPressed(5); }
void Screen2View::btn6Clicked() { handleNumberPressed(6); }
void Screen2View::btn7Clicked() { handleNumberPressed(7); }
void Screen2View::btn8Clicked() { handleNumberPressed(8); }
void Screen2View::btn9Clicked() { handleNumberPressed(9); }
void Screen2View::btn0Clicked() { handleNumberPressed(0); }

void Screen2View::handleNumberPressed(uint8_t value)
{
    if (pinLength < 6)
    {
        pinBuffer[pinLength] = value;
        pinLength++;
        updateCircleIndicators();
    }
}

void Screen2View::handleDelPressed()
{
    if (pinLength > 0)
    {
        pinLength--;
        updateCircleIndicators();
    }
}

void Screen2View::handleOkPressed()
{
    if (pinLength == 6)
    {
        
         application().gotoScreen3ScreenNoTransition();
    }
}

void Screen2View::updateCircleIndicators()
{
    // Define Color Painters (TouchGFX colortype)
    touchgfx::colortype activeGreen = touchgfx::Color::getColorFromRGB(0x10, 0xB9, 0x81);
    touchgfx::colortype defaultGray = touchgfx::Color::getColorFromRGB(0x37, 0x41, 0x51);

    // Update Circle colors based on current input depth level
    pinCircle1Painter.setColor(pinLength >= 1 ? activeGreen : defaultGray);
    pinCircle2Painter.setColor(pinLength >= 2 ? activeGreen : defaultGray);
    pinCircle3Painter.setColor(pinLength >= 3 ? activeGreen : defaultGray);
    pinCircle4Painter.setColor(pinLength >= 4 ? activeGreen : defaultGray);
    pinCircle5Painter.setColor(pinLength >= 5 ? activeGreen : defaultGray);
    pinCircle6Painter.setColor(pinLength >= 6 ? activeGreen : defaultGray);

    // Force redraw refresh command for circles on current invalid frame window
    pinCircle1.invalidate();
    pinCircle2.invalidate();
    pinCircle3.invalidate();
    pinCircle4.invalidate();
    pinCircle5.invalidate();
    pinCircle6.invalidate();
}