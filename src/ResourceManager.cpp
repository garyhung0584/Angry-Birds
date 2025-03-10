
#include "ResourceManager.hpp"

#include "Util/Logger.hpp"

ResourceManager::ResourceManager() {
    // m_TaskText = std::make_shared<TaskText>();
    m_Background = std::make_shared<BackgroundImage>();
}

void ResourceManager::NextPhase() {
    if (m_Phase == 7) return;
    LOG_DEBUG("Passed! Next phase: {}", m_Phase);
    // m_Background->NextPhase(m_Phase);
    // m_TaskText->NextPhase(m_Phase++);
}
