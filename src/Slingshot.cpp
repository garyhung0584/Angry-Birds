#include "Slingshot.hpp"
#include "Util/Image.hpp"


Slingshot::Slingshot(const glm::vec2 &pos) {
    const auto m_Slingshot0 = std::make_shared<Util::GameObject>(std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/Slingshot.png"), 5);
    const auto m_slingshot1 = std::make_shared<Util::GameObject>(std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/Slingshot1.png"), 0);
    const auto m_wire = std::make_shared<Util::GameObject>(std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/wire.png"), 0);
    for (int i; i < 2; i++) {
        const auto m_wire = std::make_shared<Util::GameObject>(std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/wireSmall.png"), 0);
        m_wire->SetVisible(false);
        m_wires.push_back(m_wire);
    }
    m_slingshot.push_back(m_Slingshot0);
    m_slingshot.push_back(m_slingshot1);
    m_wires.push_back(m_wire);
    SetPosition(pos);
}
void Slingshot::SetVisible(bool Visible) {
    for (const auto &slingshot: m_slingshot) {
        slingshot->SetVisible(Visible);
    }
}
void Slingshot::Pull(const glm::vec2& pos) {
    for (const auto &wire: m_wires) {
        wire->m_Transform.translation = pos;
        wire->SetVisible(true);
    }
}

void Slingshot::Release() {
    for (const auto &wire: m_wires) {
        wire->SetVisible(false);
    }
}

void Slingshot::SetPosition(const glm::vec2& Position) {
    for (const auto &slingshot: m_slingshot) {
        slingshot->m_Transform.translation = Position;
    }
}

