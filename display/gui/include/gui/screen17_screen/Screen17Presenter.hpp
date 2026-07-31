#ifndef SCREEN17PRESENTER_HPP
#define SCREEN17PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen17View;

class Screen17Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen17Presenter(Screen17View& v);

    /**
     * The activate function is called automatically when this screen is entered
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is left
     */
    virtual void deactivate();

    virtual ~Screen17Presenter() {}
    // --- Getters to fetch saved Organ Details from Model ---
    const char* getOrganID() const { return Model::getInstance()->getOrganID(); }
    const char* getOrganWeight() const { return Model::getInstance()->getOrganWeight(); }
    const char* getHarvestHospital() const { return Model::getInstance()->getHarvestHospital(); }
    const char* getBloodType() const { return Model::getInstance()->getBloodType(); }

    // --- Getters to fetch final frozen Preservation Time from Model ---
    int getFinalHours() const { return Model::getInstance()->getFinalHours(); }
    int getFinalMinutes() const { return Model::getInstance()->getFinalMinutes(); }
    int getFinalSeconds() const { return Model::getInstance()->getFinalSeconds(); }

private:
    Screen17Presenter();

    Screen17View& view;
};

#endif // SCREEN17PRESENTER_HPP