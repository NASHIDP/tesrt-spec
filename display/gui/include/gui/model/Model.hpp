#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstring> // Required for std::strncpy

class ModelListener;

enum OrganType {
    ORGAN_NONE,
    ORGAN_HEART,
    ORGAN_LIVER,
    ORGAN_KIDNEY
};

enum PreservationMode {
    PRESERVATION_NONE,
    PRESERVATION_HYPOTHERMIC,
    PRESERVATION_DYNAMIC,
    PRESERVATION_STATIC
};

struct OrganData {
    int temperature;
    int pressure;
};

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    // Static getter method to let presenters find the active model
    static Model* getInstance() { return modelInstance; }

    void setSelectedOrgan(OrganType o) { selectedOrgan = o; }
    OrganType getSelectedOrgan() { return selectedOrgan; }
    
    static OrganData getOrganDefaults(OrganType o) {
        switch(o) {
            case ORGAN_HEART:  return { 8, 20 }; 
            case ORGAN_LIVER:  return { 8, 3 };  
            case ORGAN_KIDNEY: return { 8, 20 }; 
            case ORGAN_NONE:  
            default:           return { 0, 0 }; 
        }
    }

    void setActiveTargetTemperature(int temp) { activeTargetTemperature = temp; }
    int getActiveTargetTemperature() { return activeTargetTemperature; }

    void setActiveTargetPressure(int press) { activeTargetPressure = press; }
    int getActiveTargetPressure() { return activeTargetPressure; }

    void setPreservationMode(PreservationMode mode) { preservationMode = mode; }
    PreservationMode getPreservationMode() { return preservationMode; }

    // Getters & Setters utilizing standard C++ string manipulation
    void setOrganID(const char* id) { std::strncpy(storedOrganID, id, 32); storedOrganID[31] = '\0'; }
    void setOrganWeight(const char* weight) { std::strncpy(storedOrganWeight, weight, 16); storedOrganWeight[15] = '\0'; }
    void setHarvestHospital(const char* hospital) { std::strncpy(storedHarvestHospital, hospital, 64); storedHarvestHospital[63] = '\0'; }
    void setDestinationInstitution(const char* dest) { std::strncpy(storedDestinationInstitution, dest, 64); storedDestinationInstitution[63] = '\0'; }
    void setBloodType(const char* blood) { std::strncpy(storedBloodType, blood, 8); storedBloodType[7] = '\0'; }
    void setCrossClampTime(const char* time) { std::strncpy(storedCrossClampTime, time, 16); storedCrossClampTime[15] = '\0'; }

    // getters to retrieve the values on other screens
    const char* getOrganID() const { return storedOrganID; }
    const char* getOrganWeight() const { return storedOrganWeight; }
    const char* getHarvestHospital() const { return storedHarvestHospital; }
    const char* getDestinationInstitution() const { return storedDestinationInstitution; }
    const char* getBloodType() const { return storedBloodType; }
    const char* getCrossClampTime() const { return storedCrossClampTime; }

    void saveFinalElapsedTime(int hours, int minutes, int seconds)
    {
        finalHours = hours;
        finalMinutes = minutes;
        finalSeconds = seconds;
    }

    int getFinalHours() const { return finalHours; }
    int getFinalMinutes() const { return finalMinutes; }
    int getFinalSeconds() const { return finalSeconds; }

protected:
    ModelListener* modelListener;
    OrganType selectedOrgan; 
    int activeTargetTemperature; 
    int activeTargetPressure; 
    PreservationMode preservationMode;
    char storedOrganID[32];
    char storedOrganWeight[16];
    char storedHarvestHospital[64];
    char storedDestinationInstitution[64];
    char storedBloodType[8];
    char storedCrossClampTime[16];
    int finalHours;
    int finalMinutes;
    int finalSeconds;

private:
    // Static instance pointer tracking
    static Model* modelInstance;
};

#endif // MODEL_HPP