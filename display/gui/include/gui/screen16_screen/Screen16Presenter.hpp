#ifndef SCREEN16PRESENTER_HPP
#define SCREEN16PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen16View;

class Screen16Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen16Presenter(Screen16View& v);

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

    virtual ~Screen16Presenter() {}

private:
    Screen16Presenter();

    Screen16View& view;
};

#endif // SCREEN16PRESENTER_HPP
