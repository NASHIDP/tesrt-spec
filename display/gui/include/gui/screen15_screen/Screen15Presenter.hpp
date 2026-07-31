#ifndef SCREEN15PRESENTER_HPP
#define SCREEN15PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/model/Model.hpp>

using namespace touchgfx;

class Screen15View;

class Screen15Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen15Presenter(Screen15View& v);

    virtual void activate();
    virtual void deactivate();

    virtual ~Screen15Presenter() {}

    // Fetch the active target temperature from the model
    int getTargetTemperature()
    {
        return Model::getInstance()->getActiveTargetTemperature();
    }

    // Fetch the active target pressure from the model
    int getTargetPressure()
    {
        return Model::getInstance()->getActiveTargetPressure();
    }

    // Fetch the preservation mode selected on Screen 9
    PreservationMode getPreservationMode()
    {
        return Model::getInstance()->getPreservationMode();
    }

    void storeProcedureDuration(int h, int m, int s)
    {
        Model::getInstance()->saveFinalElapsedTime(h, m, s);
    }

private:
    Screen15Presenter();

    Screen15View& view;
    
};

#endif // SCREEN15PRESENTER_HPP