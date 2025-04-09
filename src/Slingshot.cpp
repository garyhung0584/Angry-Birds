#include "Slingshot.hpp"
#include "Util/Image.hpp"


Slingshot::Slingshot(const glm::vec2 &pos) {
    const auto m_Slingshot0 = std::make_shared<Util::GameObject>(std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/Slingshot.png"), 5);
    const auto m_slingshot1 = std::make_shared<Util::GameObject>(std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/Slingshot1.png"), 0);
    m_slingshot.push_back(m_Slingshot0);
    m_slingshot.push_back(m_slingshot1);
    SetPosition(pos);
}
void Slingshot::SetVisible(bool Visible) {
    for (const auto &slingshot: m_slingshot) {
        slingshot->SetVisible(Visible);
    }
}

void Slingshot::SetPosition(const glm::vec2& Position) {
    for (const auto &slingshot: m_slingshot) {
        slingshot->m_Transform.translation = Position;
    }
}

