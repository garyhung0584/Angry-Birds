#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP



#include "Util/GameObject.hpp"
// #include "TaskText.hpp"
// #include "Character.hpp"
#include "BackgroundImage.hpp"

class ResourceManager {
public:
    ResourceManager();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return { m_Background };
    }

    void EnterLevel(const int level);

private:
    // std::shared_ptr<TaskText> m_TaskText;
    std::shared_ptr<BackgroundImage> m_Background;

    int m_level = 0;
};

#endif //RESOURCEMANAGER_HPP
