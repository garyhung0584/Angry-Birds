#include "ResourceManager.hpp"
#include "Util/Logger.hpp"

ResourceManager::ResourceManager() {
    m_Background = std::make_shared<BackgroundImage>();
}

void ResourceManager::EnterLevel(const int level) {
    m_level = level;
    m_Background->SetPhase(m_level);
}
