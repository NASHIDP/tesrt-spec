#ifndef SCREEN12PRESENTER_HPP
#define SCREEN12PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/model/Model.hpp> 

using namespace touchgfx;

class Screen12View;


class Screen12Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen12Presenter(Screen12View& v);

    virtual void activate();
    virtual void deactivate();

    virtual ~Screen12Presenter() {}

   
    int getActiveTargetTemperature()
    {
        return Model::getInstance()->getActiveTargetTemperature();
    }

    int getActiveTargetPressure()
    {
        return Model::getInstance()->getActiveTargetPressure();
    }

private:
    Screen12Presenter();

    Screen12View& view;
};

#endif // SCREEN12PRESENTER_HPP