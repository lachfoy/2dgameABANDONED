#include "ui_manager.h"

#include "input_manager.h"
#include "resource_manager.h"
#include "BaseUiObject.h"
#include "resource_bar.h"
//#include "DynamicHealthbar.h"
#include "BaseTextObject.h"

UiManager::UiManager(InputManagerPtr input_manager, ResourceManagerPtr resource_manager, int window_width, int window_height)
{
    input_manager_ = input_manager;
    resource_manager_ = resource_manager;
    window_width_ = window_width;
    window_height_ = window_height;
}

UiManager::~UiManager()
{
    ui_objects_.clear();
}

// void UiManager::addHealthbar(int x, int y, int length, int height, BaseCharacter* damageable)
// {
//     ui_objects_.push_back(std::make_unique<HealthBar>(x, y, length, height, damageable));
// }

// void UiManager::addDynamicHealthbar(int length, int height, BaseCharacter* damageable)
// {
//     ui_objects_.push_back(std::make_unique<DynamicHealthbar>(length, height, damageable));
// }

// void UiManager::addTextObject(int x, int y, std::string text)
// {
//     ui_objects_.push_back(std::make_unique<BaseTextObject>(x, y, text, resource_manager_->GetFont("ArialHeader")));
// }

ResourceBar* UiManager::AddResourceBar(int x, int y, int width, int height)
{
    std::unique_ptr<BaseUiObject> ui_object = std::make_unique<ResourceBar>(x, y, width, height, resource_manager_->GetTexture("fireball_texture"));
    ResourceBar* copy = (ResourceBar*)ui_object.get();
    ui_objects_.push_back(std::move(ui_object));
    return copy;
}

void UiManager::UpdateUiObjects(float dt)
{
    for (const auto& uiObject : ui_objects_)
    {
        uiObject->Update(dt);
    }
}

void UiManager::CleanUpUnusedUiObjects()
{
    for (int i = 0; i < ui_objects_.size(); i++)
    {
        if (ui_objects_[i]->removable)
        {
            //uiObjects[i]->destroy(*this);
            ui_objects_.erase(ui_objects_.begin() + i);
            i--;
        }
    }
}

void UiManager::RenderUiObjects(SDL_Renderer* renderer)
{
    // render UiObjects
    for (const auto& uiObject : ui_objects_)
    {
        uiObject->Render(renderer);
    }
}