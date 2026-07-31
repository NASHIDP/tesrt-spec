#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>


// Initialize the static pointer to null
Model* Model::modelInstance = nullptr;

Model::Model() : modelListener(0), selectedOrgan(ORGAN_NONE), activeTargetTemperature(8), activeTargetPressure(0), preservationMode(PRESERVATION_NONE)
{
    
    modelInstance = this;
    storedOrganID[0] = '\0';
    storedOrganWeight[0] = '\0';
    storedHarvestHospital[0] = '\0';
    storedDestinationInstitution[0] = '\0';
    storedBloodType[0] = '\0';
    storedCrossClampTime[0] = '\0';
    
    finalHours = 0;
    finalMinutes = 0;
    finalSeconds = 0;
}

void Model::tick()
{
}