#include <gui/screen17_screen/Screen17View.hpp>
#include <gui/screen17_screen/Screen17Presenter.hpp>

Screen17Presenter::Screen17Presenter(Screen17View& v)
    : view(v)
{
}

void Screen17Presenter::activate()
{
    // Logic to run right as the screen transitions in can be added here
}

void Screen17Presenter::deactivate()
{
    // Cleanup logic when leaving the screen can be added here
}