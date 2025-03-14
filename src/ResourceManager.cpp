
#include "ResourceManager.hpp"

#include "Util/Logger.hpp"

ResourceManager::ResourceManager() {
    // m_TaskText = std::make_shared<TaskText>();
    m_Background = std::make_shared<BackgroundImage>();
}

void ResourceManager::EnterLevel(const int level) {
    m_level = level;
    LOG_DEBUG("Current level: {}", m_level);
    m_Background->SetPhase(m_level);
    // m_TaskText->NextPhase(m_Phase++);
}
