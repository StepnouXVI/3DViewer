#include <Domain/Scene.h>
#include <Domain/Transform.h>

using namespace Domain;

void Scene::AddModel(ISceneObjectPtr obj)
{
    _objects.push_back(obj);
}

void Scene::Draw(ISceneDrawer &drawer)
{
    for (auto &obj : _objects)
    {
        obj->Draw(drawer);
    }
}

void Scene::ApplyTransform(Transform &trans)
{
    trans.Apply(_model);
    for (auto &obj : _objects)
    {
        obj->ApplyTransform(trans);
    }
}

