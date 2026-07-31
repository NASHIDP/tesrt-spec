#include <gui/screen8_screen/Screen8View.hpp>
#include <gui/screen8_screen/Screen8Presenter.hpp>

Screen8Presenter::Screen8Presenter(Screen8View& v)
    : view(v)
{

}

void Screen8Presenter::activate()
{

}

void Screen8Presenter::deactivate()
{

}


void Screen8Presenter::saveOrganDataToModel(
    const char* id, 
    const char* weight, 
    const char* hospital, 
    const char* dest, 
    const char* blood, 
    const char* clampTime)
{
    // Write directly into the core Model framework structures via the static instance
    Model::getInstance()->setOrganID(id);
    Model::getInstance()->setOrganWeight(weight);
    Model::getInstance()->setHarvestHospital(hospital);
    Model::getInstance()->setDestinationInstitution(dest);
    Model::getInstance()->setBloodType(blood);
    Model::getInstance()->setCrossClampTime(clampTime);
}