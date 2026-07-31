#include <gui/screen16_screen/Screen16View.hpp>
#include <touchgfx/Color.hpp>



Screen16View::Screen16View() :
    isStep1Completed(false),
    isStep2Completed(false),
    isStep3Completed(false)
{
}

void Screen16View::setupScreen()
{
    Screen16ViewBase::setupScreen();
    topStatusBar16.setScreenTitle("Arrival Checklist");

    // Initial state setup: Hide all tickmarks on launch
    imageTickStep1.setVisible(false);
    imageTickStep2.setVisible(false);
    imageTickStep3.setVisible(false);

    // Explicitly make sure the proceed button cannot be clicked yet
    buttonProceed.setTouchable(false);

    // Invalidate everything to apply initial hidden configurations
    imageTickStep1.invalidate();
    imageTickStep2.invalidate();
    imageTickStep3.invalidate();
}

void Screen16View::tearDownScreen()
{
    Screen16ViewBase::tearDownScreen();
}
void Screen16View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar16.handleTickEvent();

    
}
// Click Handler for Step 1: Take Terminal Cardioplegia
void Screen16View::flexButtonStep1Clicked()
{
    // Step 1 can always be clicked to toggle its state
    isStep1Completed = !isStep1Completed;

    // Strict validation rule: If Step 1 is unselected, forcefully reset subsequent steps
    if (!isStep1Completed)
    {
        isStep2Completed = false;
        isStep3Completed = false;
    }

    refreshChecklistUI();
}

// Click Handler for Step 2: Release Clamp
void Screen16View::flexButtonStep2Clicked()
{
    // STRICT ORDER ENFORCEMENT: Only allow selection if Step 1 is active
    if (isStep1Completed)
    {
        isStep2Completed = !isStep2Completed;

        // Strict validation rule: If Step 2 is unselected, forcefully reset Step 3
        if (!isStep2Completed)
        {
            isStep3Completed = false;
        }

        refreshChecklistUI();
    }
}

// Click Handler for Step 3: Stop Motors
void Screen16View::flexButtonStep3Clicked()
{
    // STRICT ORDER ENFORCEMENT: Only allow selection if Step 2 is active
    if (isStep2Completed)
    {
        isStep3Completed = !isStep3Completed;
        
        refreshChecklistUI();
    }
}

// Dynamic state coordinator to update visual layers
void Screen16View::refreshChecklistUI()
{
    
    // 1. Theme Green Accent
    const touchgfx::colortype COLOR_GREEN = touchgfx::Color::getColorFromRGB(0x10, 0xB9, 0x81);
    // 2. Unselected Border Grey Color
    const touchgfx::colortype COLOR_BORDER_GREY = touchgfx::Color::getColorFromRGB(0x33, 0x41, 0x55);
    // 3. Dark Blue/Navy Internal Flex Box Fill Color
    const touchgfx::colortype COLOR_BOX_FILL = touchgfx::Color::getColorFromRGB(0x0F, 0x17, 0x2A);
    // 4. Proceed Muted Grey Button Color
    const touchgfx::colortype COLOR_PROCEED_MUTED = touchgfx::Color::getColorFromRGB(0x33, 0x41, 0x55);
    
    // Text Color States
    const touchgfx::colortype COLOR_UNSELECTED_TXT = touchgfx::Color::getColorFromRGB(0x94, 0xA3, 0xB8);
    const touchgfx::colortype COLOR_SELECTED_TXT = touchgfx::Color::getColorFromRGB(0xFF, 0xFF, 0xFF);

    // --- STEP 1 VISUAL UPDATE ---
    imageTickStep1.setVisible(isStep1Completed);
    if (isStep1Completed)
    {
        // Arguments: normalBackground, pressedBackground, normalBorder, pressedBorder
        flexButtonStep1.setBoxWithBorderColors(COLOR_BOX_FILL, COLOR_BOX_FILL, COLOR_GREEN, COLOR_GREEN);
        textStep1.setColor(COLOR_SELECTED_TXT);
    }
    else
    {
        flexButtonStep1.setBoxWithBorderColors(COLOR_BOX_FILL, COLOR_BOX_FILL, COLOR_BORDER_GREY, COLOR_BORDER_GREY);
        textStep1.setColor(COLOR_UNSELECTED_TXT);
    }
    imageTickStep1.invalidate();
    flexButtonStep1.invalidate();
    textStep1.invalidate();

    // --- STEP 2 VISUAL UPDATE ---
    imageTickStep2.setVisible(isStep2Completed);
    if (isStep2Completed)
    {
        flexButtonStep2.setBoxWithBorderColors(COLOR_BOX_FILL, COLOR_BOX_FILL, COLOR_GREEN, COLOR_GREEN);
        textStep2.setColor(COLOR_SELECTED_TXT);
    }
    else
    {
        flexButtonStep2.setBoxWithBorderColors(COLOR_BOX_FILL, COLOR_BOX_FILL, COLOR_BORDER_GREY, COLOR_BORDER_GREY);
        textStep2.setColor(COLOR_UNSELECTED_TXT);
    }
    imageTickStep2.invalidate();
    flexButtonStep2.invalidate();
    textStep2.invalidate();

    // --- STEP 3 VISUAL UPDATE ---
    imageTickStep3.setVisible(isStep3Completed);
    if (isStep3Completed)
    {
        flexButtonStep3.setBoxWithBorderColors(COLOR_BOX_FILL, COLOR_BOX_FILL, COLOR_GREEN, COLOR_GREEN);
        textStep3.setColor(COLOR_SELECTED_TXT);
    }
    else
    {
        flexButtonStep3.setBoxWithBorderColors(COLOR_BOX_FILL, COLOR_BOX_FILL, COLOR_BORDER_GREY, COLOR_BORDER_GREY);
        textStep3.setColor(COLOR_UNSELECTED_TXT);
    }
    imageTickStep3.invalidate();
    flexButtonStep3.invalidate();
    textStep3.invalidate();

    // --- FINAL PROCEED BUTTON EVALUATION ---
    if (isStep1Completed && isStep2Completed && isStep3Completed)
    {
        // Turn the proceed button green and make it touchable
        buttonProceed.setBoxWithBorderColors(COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
        buttonProceed.setTouchable(true);
    }
    else
    {
        // Revert proceed button back to dark muted grey and disable interactions
        buttonProceed.setBoxWithBorderColors(COLOR_PROCEED_MUTED, COLOR_PROCEED_MUTED, COLOR_BORDER_GREY, COLOR_BORDER_GREY);
        buttonProceed.setTouchable(false);
    }
    buttonProceed.invalidate();
}