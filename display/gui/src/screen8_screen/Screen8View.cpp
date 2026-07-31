#include <gui/screen8_screen/Screen8View.hpp>
#include <iostream>

Screen8View::Screen8View() :
    editOrganID(Editable(btnOrganID, btnOrganIDBuffer)),
    editOrganWeight(Editable(btnOrganWeight, btnOrganWeightBuffer)),
    editHarvestHospital(Editable(btnHarvestHospital, btnHarvestHospitalBuffer)),
    editDestinationInstitution(Editable(btnDestinationInstitution, btnDestinationInstitutionBuffer)),
    editBloodType(Editable(btnBloodType, btnBloodTypeBuffer)),
    editCrossClampTime(Editable(btnCrossClampTime, btnCrossClampTimeBuffer)),
    valOrganID(), valOrganWeight(), valHarvestHospital(), valDestinationInstitution(), valBloodType(), valCrossClampTime()
{
}

void Screen8View::setupScreen()
{
    Screen8ViewBase::setupScreen();
    topStatusBar8.setScreenTitle("Organ Details");
    validateInputs();
}

void Screen8View::tearDownScreen()
{
    Screen8ViewBase::tearDownScreen();
}

void Screen8View::handleTickEvent()
{
    // 1. Pass the tick down to your custom container so its animation code runs!
    topStatusBar8.handleTickEvent();

    
}

// Click Triggers opening the keyboard targeted to the specific input area
void Screen8View::btnOrganIDClicked() { keyboard1.edit(editOrganID); }
void Screen8View::btnOrganWeightClicked() { keyboard1.edit(editOrganWeight); }
void Screen8View::btnHarvestHospitalClicked() { keyboard1.edit(editHarvestHospital); }
void Screen8View::btnDestinationInstitutionClicked() { keyboard1.edit(editDestinationInstitution); }
void Screen8View::btnBloodTypeClicked() { keyboard1.edit(editBloodType); }
void Screen8View::btnCrossClampTimeClicked() { keyboard1.edit(editCrossClampTime); }

void Screen8View::editCancel()
{
    keyboard1.setVisible(false);
    keyboard1.invalidate();
}

void Screen8View::editApply()
{
    keyboard1.setVisible(false);
    keyboard1.invalidate();

    // Saves the text safely to the correct variable array when hitting apply
    if (keyboard1.targets(editOrganID))                  editOrganID.toUTF8(valOrganID);
    else if (keyboard1.targets(editOrganWeight))          editOrganWeight.toUTF8(valOrganWeight);
    else if (keyboard1.targets(editHarvestHospital))      editHarvestHospital.toUTF8(valHarvestHospital);
    else if (keyboard1.targets(editDestinationInstitution)) editDestinationInstitution.toUTF8(valDestinationInstitution);
    else if (keyboard1.targets(editBloodType))            editBloodType.toUTF8(valBloodType);
    else if (keyboard1.targets(editCrossClampTime))       editCrossClampTime.toUTF8(valCrossClampTime);

    validateInputs();

   
}



void Screen8View::onContinueButtonClicked()
{
    // 1. Extract the text directly from the Flex Button Wildcard Buffers with explicit type casts
    Unicode::toUTF8(btnOrganIDBuffer, reinterpret_cast<uint8_t*>(valOrganID), BTNORGANID_SIZE);
    Unicode::toUTF8(btnOrganWeightBuffer, reinterpret_cast<uint8_t*>(valOrganWeight), BTNORGANWEIGHT_SIZE);
    Unicode::toUTF8(btnHarvestHospitalBuffer, reinterpret_cast<uint8_t*>(valHarvestHospital), BTNHARVESTHOSPITAL_SIZE);
    Unicode::toUTF8(btnDestinationInstitutionBuffer, reinterpret_cast<uint8_t*>(valDestinationInstitution), BTNDESTINATIONINSTITUTION_SIZE);
    Unicode::toUTF8(btnBloodTypeBuffer, reinterpret_cast<uint8_t*>(valBloodType), BTNBLOODTYPE_SIZE);
    Unicode::toUTF8(btnCrossClampTimeBuffer, reinterpret_cast<uint8_t*>(valCrossClampTime), BTNCROSSCLAMPTIME_SIZE);

    // 2. Send the freshly extracted details directly to the Presenter
    presenter->saveOrganDataToModel(
        valOrganID,
        valOrganWeight,
        valHarvestHospital,
        valDestinationInstitution,
        valBloodType,
        valCrossClampTime
    );

    
    application().gotoScreen9ScreenNoTransition();
}

void Screen8View::keyPressed() {
    
}
void Screen8View::characterTyped(Unicode::UnicodeChar character) {
    
}
void Screen8View::validateInputs()
{
    // Create a Unicode representation of the placeholder to compare against
    Unicode::UnicodeChar placeholder[6];
    // Added explicit reinterpret_cast to match TouchGFX API types
    Unicode::fromUTF8(reinterpret_cast<const uint8_t*>("HH:MM"), placeholder, 6);

    // Check if clamp time buffer is empty OR if it matches the placeholder text exactly
    bool isClampTimeValid = (Unicode::strlen(btnCrossClampTimeBuffer) > 0) && 
                            (Unicode::strncmp(btnCrossClampTimeBuffer, placeholder, 6) != 0);

    // Check all fields together
    bool isValid = (Unicode::strlen(btnOrganIDBuffer) > 0) &&
                   (Unicode::strlen(btnOrganWeightBuffer) > 0) &&
                   (Unicode::strlen(btnHarvestHospitalBuffer) > 0) &&
                   (Unicode::strlen(btnBloodTypeBuffer) > 0) &&
                   isClampTimeValid;

    // Toggle button interactivity
    ContinueButton.setTouchable(isValid);

    // Set opacity: 100 if faded/inactive, 255 if fully active
    ContinueButton.setAlpha(isValid ? 255 : 100);

    // Force the button area to re-render visually
    ContinueButton.invalidate();
}