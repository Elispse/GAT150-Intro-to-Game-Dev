#include "ModelManager.h"

namespace Jackster {
    ModelManager g_modelManager;

    std::shared_ptr<Model> Jackster::ModelManager::get(const std::string& fileName)
    {
        if (m_models.find(fileName) == m_models.end())
        {
            std::shared_ptr<Model> model = std::make_shared<Model>();
            model->Load(fileName);

            m_models[fileName] = model;
        }
        return m_models[fileName];
    }

}