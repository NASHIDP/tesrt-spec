#ifndef SCREEN8VIEW_HPP
#define SCREEN8VIEW_HPP

#include <gui_generated/screen8_screen/Screen8ViewBase.hpp>
#include <gui/screen8_screen/Screen8Presenter.hpp>
#include <gui/common/Editable.hpp>

class Screen8View : public Screen8ViewBase
{
public:
    Screen8View();
    virtual ~Screen8View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    // These override functions match designer button click triggers perfectly
    void btnOrganIDClicked() override;
    void btnOrganWeightClicked() override;
    void btnHarvestHospitalClicked() override;
    void btnDestinationInstitutionClicked() override;
    void btnBloodTypeClicked() override;
    void btnCrossClampTimeClicked() override;
    
    // continue button function
    void onContinueButtonClicked();

    
    void editCancel();
    void editApply();
    void keyPressed();
    void characterTyped(Unicode::UnicodeChar character);

private:
    Editable editOrganID;
    Editable editOrganWeight;
    Editable editHarvestHospital;
    Editable editDestinationInstitution;
    Editable editBloodType;
    Editable editCrossClampTime;

    char valOrganID[BTNORGANID_SIZE];
    char valOrganWeight[BTNORGANWEIGHT_SIZE];
    char valHarvestHospital[BTNHARVESTHOSPITAL_SIZE];
    char valDestinationInstitution[BTNDESTINATIONINSTITUTION_SIZE];
    char valBloodType[BTNBLOODTYPE_SIZE];
    char valCrossClampTime[BTNCROSSCLAMPTIME_SIZE];
    
    void validateInputs();
};

#endif // SCREEN8VIEW_HPP