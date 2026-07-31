#include <gui/screen9_screen/Screen9View.hpp>
#include <touchgfx/Color.hpp>


#define COLOR_CHARCOAL_GRAY touchgfx::Color::getColorFromRGB(0x1F, 0x29, 0x37)
#define COLOR_GREEN     touchgfx::Color::getColorFromRGB(0x10, 0xB9, 0x81)
#define COLOR_MUTED     touchgfx::Color::getColorFromRGB(0x94, 0xA3, 0xB8)
#define COLOR_WHITE     touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF)

Screen9View::Screen9View() :
    currentSelection(NONE)
{
}

void Screen9View::setupScreen()
{
    Screen9ViewBase::setupScreen();
    topStatusBar9.setScreenTitle("Preservation Mode");
    updateButtonVisuals();
}

void Screen9View::tearDownScreen()
{
    Screen9ViewBase::tearDownScreen();
}

void Screen9View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar9.handleTickEvent();

    
}

void Screen9View::btnHypothermicClicked()
{
    currentSelection = HYPOTHERMIC;
    updateButtonVisuals();
}

void Screen9View::btnDynamicClicked()
{
    currentSelection = DYNAMIC;
    updateButtonVisuals();
}

void Screen9View::btnStaticClicked()
{
    currentSelection = STATIC;
    updateButtonVisuals();
}

// --- Visual Toggling Logic via Color Swapping ---
void Screen9View::updateButtonVisuals()
{
    // 1. Hypothermic Button Styles
    if (currentSelection == HYPOTHERMIC) {
        btnHypothermic.setBoxWithBorderColors(COLOR_GREEN, COLOR_GREEN, 0, 0);
        btnHypothermic.setTextColors(COLOR_WHITE, COLOR_WHITE);
    } else {
        btnHypothermic.setBoxWithBorderColors(COLOR_CHARCOAL_GRAY, COLOR_GREEN, 0, 0);
        btnHypothermic.setTextColors(COLOR_MUTED, COLOR_WHITE);
    }

    // 2. Dynamic Button Styles
    if (currentSelection == DYNAMIC) {
        btnDynamic.setBoxWithBorderColors(COLOR_GREEN, COLOR_GREEN, 0, 0);
        btnDynamic.setTextColors(COLOR_WHITE, COLOR_WHITE);
    } else {
        btnDynamic.setBoxWithBorderColors(COLOR_CHARCOAL_GRAY, COLOR_GREEN, 0, 0);
        btnDynamic.setTextColors(COLOR_MUTED, COLOR_WHITE);
    }

    // 3. Static Button Styles
    if (currentSelection == STATIC) {
        btnStatic.setBoxWithBorderColors(COLOR_GREEN, COLOR_GREEN, 0, 0);
        btnStatic.setTextColors(COLOR_WHITE, COLOR_WHITE);
    } else {
        btnStatic.setBoxWithBorderColors(COLOR_CHARCOAL_GRAY, COLOR_GREEN, 0, 0);
        btnStatic.setTextColors(COLOR_MUTED, COLOR_WHITE);
    }

    // Force a redraw of the buttons
    btnHypothermic.invalidate();
    btnDynamic.invalidate();
    btnStatic.invalidate();
}

void Screen9View::btnConfirmContinueClicked()
{
    // Save the selection to the model before navigating away
    switch (currentSelection)
    {
        case HYPOTHERMIC:
            presenter->savePreservationMode(PRESERVATION_HYPOTHERMIC);
            application().gotoScreen10ScreenNoTransition(); 
            break;
        case DYNAMIC:
            presenter->savePreservationMode(PRESERVATION_DYNAMIC);
            application().gotoScreen12ScreenNoTransition();
            break;
        case STATIC:
            presenter->savePreservationMode(PRESERVATION_STATIC);
            application().gotoScreen12ScreenNoTransition();
            break;
        default:
            presenter->savePreservationMode(PRESERVATION_NONE);
            break;
    }
}