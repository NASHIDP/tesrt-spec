#ifndef SCREEN18VIEW_HPP
#define SCREEN18VIEW_HPP

#include <gui_generated/screen18_screen/Screen18ViewBase.hpp>
#include <gui/screen18_screen/Screen18Presenter.hpp>

class Screen18View : public Screen18ViewBase
{
public:
    Screen18View();
    virtual ~Screen18View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
protected:
};

#endif // SCREEN18VIEW_HPP
