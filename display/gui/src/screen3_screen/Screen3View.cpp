#include <gui/screen3_screen/Screen3View.hpp>
#include <touchgfx/Color.hpp>

Screen3View::Screen3View() :
    organCardClickedCallback(this, &Screen3View::organCardClickedHandler)
{
}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
    topStatusBar3.setScreenTitle("Select Organ Type");

    // 1. Assign touch listener callbacks to card containers
    cardHeart.setClickAction(organCardClickedCallback);
    cardLiver.setClickAction(organCardClickedCallback);
    cardKidney.setClickAction(organCardClickedCallback);

    // 2. Safely link custom RAM buffers to the screen text elements
    textTemp.setWildcard(tempBuffer);
    textPressure.setWildcard(pressureBuffer);

    // 3. Fetch the saved organ type from memory
    OrganType savedOrgan = presenter->getSavedOrgan();
    // Add this line right after fetching the saved organ:
    updateButtonStates(savedOrgan);

    // 4. Set initial border highlight box visibility states
    borderHeart.setVisible(savedOrgan == ORGAN_HEART);
    borderLiver.setVisible(savedOrgan == ORGAN_LIVER);
    borderKidney.setVisible(savedOrgan == ORGAN_KIDNEY);

    // 5. Look up the defaults for this organ from Model and update text boxes
    OrganData data = Model::getOrganDefaults(savedOrgan);
    Unicode::snprintf(tempBuffer, 10, "%d", data.temperature);
    Unicode::snprintf(pressureBuffer, 10, "%d", data.pressure);

    // Refresh everything visually
    textTemp.invalidate();
    textPressure.invalidate();
    borderHeart.invalidate();
    borderLiver.invalidate();
    borderKidney.invalidate();
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}
void Screen3View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar3.handleTickEvent();

    
}
void Screen3View::organCardClickedHandler(const Container& c, const ClickEvent& e)
{
    // Only respond when the user lifts their finger off the screen
    if (e.getType() == ClickEvent::RELEASED)
    {
        OrganType selectedOrgan = ORGAN_NONE;

        if (&c == &cardHeart)
        {
            selectedOrgan = ORGAN_HEART;
        }
        else if (&c == &cardLiver)
        {
            selectedOrgan = ORGAN_LIVER;
        }
        else if (&c == &cardKidney)
        {
            selectedOrgan = ORGAN_KIDNEY;
        }

        // Save selection directly into system memory 
        presenter->saveOrganSelection(selectedOrgan);
        updateButtonStates(selectedOrgan);

        // Update borders seamlessly
        borderHeart.setVisible(selectedOrgan == ORGAN_HEART);
        borderLiver.setVisible(selectedOrgan == ORGAN_LIVER);
        borderKidney.setVisible(selectedOrgan == ORGAN_KIDNEY);

        // Fetch new target specs instantly for the clicked organ!
        OrganData data = Model::getOrganDefaults(selectedOrgan);
        Unicode::snprintf(tempBuffer, 10, "%d", data.temperature);
        Unicode::snprintf(pressureBuffer, 10, "%d", data.pressure);

        // Force a UI repaint of text data and borders
        textTemp.invalidate();
        textPressure.invalidate();
        borderHeart.invalidate();
        borderLiver.invalidate();
        borderKidney.invalidate();
    }
}

// Confirm Button Action (Triggered by Screen Interaction)
// Confirm Button Action (Triggered by Screen Interaction)
void Screen3View::function1()
{
    // 1. Fetch the currently selected organ from the presenter
    OrganType savedOrgan = presenter->getSavedOrgan();

    if (savedOrgan != ORGAN_NONE)
    {
        // 2. Lock in the defaults to the active targets directly via the presenter
        presenter->saveOrganSelection(savedOrgan); 
    }

    // 3. Transition to Screen 5
    application().gotoScreen5ScreenNoTransition();
}

void Screen3View::updateButtonStates(OrganType organ)
{
    bool hasSelection = (organ != ORGAN_NONE);

    // Enable or disable touch interactions
    btnConfirmSelection.setTouchable(hasSelection);
    btnChangeConfiguration.setTouchable(hasSelection);

    // Visually fade out buttons if disabled (alpha 100), full opacity if enabled (alpha 255)
    btnConfirmSelection.setAlpha(hasSelection ? 255 : 100);
    btnChangeConfiguration.setAlpha(hasSelection ? 255 : 100);

    // FORCE THE BUTTONS AND CURRENT VIEW TO RE-RENDER IMMEDIATELY
    btnConfirmSelection.invalidate();
    btnChangeConfiguration.invalidate();
    
    
}

void Screen3View::changeConfigurationClicked()
{
    // Check if an organ is selected before allowing screen transition
    if (presenter->getSavedOrgan() != ORGAN_NONE)
    {
        application().gotoScreen4ScreenNoTransition();
    }
}