#ifndef TOPSTATUSBAR_HPP
#define TOPSTATUSBAR_HPP

#include <gui_generated/containers/TopStatusBarBase.hpp>

class TopStatusBar : public TopStatusBarBase
{
public:
    TopStatusBar();
    virtual ~TopStatusBar() {}

    virtual void initialize();
    void setScreenTitle(const char* titleStr);

    // Hook into the frame tick event to update time, battery, and GPS UI states
    virtual void handleTickEvent();
};

#endif // TOPSTATUSBAR_HPP