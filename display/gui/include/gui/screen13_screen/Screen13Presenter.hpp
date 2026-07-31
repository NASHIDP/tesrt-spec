#ifndef SCREEN13PRESENTER_HPP
#define SCREEN13PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/model/Model.hpp>

using namespace touchgfx;

class Screen13View;

class Screen13Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen13Presenter(Screen13View& v);

    virtual void activate();
    virtual void deactivate();

    virtual ~Screen13Presenter() {}

    // Save both parameters to the model
    void saveManualConfiguration(int temp, int press)
    {
        Model::getInstance()->setActiveTargetTemperature(temp);
        Model::getInstance()->setActiveTargetPressure(press);
    }

    // Recover current running targets from model to populate screen on startup
    int getInitialTemperature()
    {
        return Model::getInstance()->getActiveTargetTemperature();
    }

    int getInitialPressure()
    {
        return Model::getInstance()->getActiveTargetPressure();
    }

private:
    Screen13Presenter();

    Screen13View& view;
};

#endif // SCREEN13PRESENTER_HPP