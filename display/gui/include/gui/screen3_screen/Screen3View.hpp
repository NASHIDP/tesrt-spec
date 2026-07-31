#ifndef SCREEN3VIEW_HPP
#define SCREEN3VIEW_HPP

#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

class Screen3View : public Screen3ViewBase
{
public:
    Screen3View();
    virtual ~Screen3View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    // 1. Matches the exact virtual functions from  base header file
    virtual void function1(); // Confirm Button
    virtual void changeConfigurationClicked();
    

protected:
    // 2. Custom Click Listener Callback Engine
    Callback<Screen3View, const Container&, const ClickEvent&> organCardClickedCallback;
    void organCardClickedHandler(const Container& c, const ClickEvent& e);
    void updateButtonStates(OrganType organ);

    // 3. Dedicated RAM buffers to safely hold  dynamic numbers (size 10 characters)
    Unicode::UnicodeChar tempBuffer[10];
    Unicode::UnicodeChar pressureBuffer[10];
};

#endif // SCREEN3VIEW_HPP