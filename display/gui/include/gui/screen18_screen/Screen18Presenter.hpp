#ifndef SCREEN18PRESENTER_HPP
#define SCREEN18PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen18View;

class Screen18Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen18Presenter(Screen18View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Screen18Presenter() {}

private:
    Screen18Presenter();

    Screen18View& view;
};

#endif // SCREEN18PRESENTER_HPP
