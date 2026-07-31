#ifndef SCREEN3PRESENTER_HPP
#define SCREEN3PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/model/Model.hpp> 

using namespace touchgfx;

class Screen3View;

class Screen3Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen3Presenter(Screen3View& v);

    virtual void activate();
    virtual void deactivate();

    virtual ~Screen3Presenter() {}

    // 1. Tell the view what organ is currently saved in the brain
    OrganType getSavedOrgan()
    {
        return model->getSelectedOrgan();
    }

    // 2. Tell the brain to save a new organ selection AND its defaults
    void saveOrganSelection(OrganType o)
    {
        model->setSelectedOrgan(o);
        
        // Fetch the factory default data for this organ
        OrganData defaults = Model::getOrganDefaults(o);
        
        // Save BOTH parameters into  running session variables
        model->setActiveTargetTemperature(defaults.temperature);
        model->setActiveTargetPressure(defaults.pressure); // <-- ADDED THIS LINE TO FIX THE BUG!
    }
    
private:
    Screen3Presenter();

    Screen3View& view;
};

#endif // SCREEN3PRESENTER_HPP