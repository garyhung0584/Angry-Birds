#include "Slingshot.hpp"
#include "Util/Image.hpp"


Slingshot::Slingshot(const glm::vec2 &pos) {
    const auto m_Slingshot0 = std::make_shared<Util::GameObject>(
        std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/Slingshot.png"), 5);
    const auto m_slingshot1 = std::make_shared<Util::GameObject>(
        std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/Slingshot1.png"), 3);
    for (int i = 0; i < 3; i++) {
        auto m_wire = std::make_shared<Util::GameObject>(
            std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/wire.png"), i);
        m_wires.push_back(m_wire);
    }
    m_slingshot.push_back(m_Slingshot0);
    m_slingshot.push_back(m_slingshot1);
    SetPosition(pos);
}

void Slingshot::SetVisible(bool Visible) {
    for (const auto &slingshot: m_slingshot) {
        slingshot->SetVisible(Visible);
    }
}

void Slingshot::Pull(const glm::vec2 &pos) {
    auto slingshotPos = GetPosition() - glm::vec2(-15, -55.f);
    auto posBias = pos - slingshotPos;
    auto posOffset = posBias/2.8f;
    auto rotation = atan2(-posBias.y, -posBias.x);
    for (int i = 0; i < 3; i++) {
        m_wires[i]->SetVisible(true);
        m_wires[i]->m_Transform.translation = pos - posOffset*glm::vec2(i, i);
        m_wires[i]->m_Transform.rotation = rotation;
    }
}

void Slingshot::Release() {
    for (const auto &wire: m_wires) {
        wire->SetVisible(false);
    }
}

void Slingshot::SetPosition(const glm::vec2 &Position) {
    for (const auto &slingshot: m_slingshot) {
        slingshot->m_Transform.translation = Position;
    }
}
