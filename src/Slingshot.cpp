#include "Slingshot.hpp"
#include "Util/Image.hpp"


Slingshot::Slingshot(const glm::vec2 &pos) {
    const auto m_slingshot_front = std::make_shared<Util::GameObject>(
        std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/Slingshot.png"), 5);
    const auto m_slingshot_back = std::make_shared<Util::GameObject>(
        std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/Slingshot1.png"), 3);
    for (int i = 0; i < 3; i++) {
        auto m_wire = std::make_shared<Util::GameObject>(
            std::make_shared<Util::Image>(RESOURCE_DIR"/Slingshot/wire.png"), i);
        m_wire->SetVisible(false);
        m_wires.push_back(m_wire);
    }
    m_slingshot.push_back(m_slingshot_front);
    m_slingshot.push_back(m_slingshot_back);
    SetPosition(pos);
}

void Slingshot::SetVisible(const bool visible) const {
    for (const auto &slingshot: m_slingshot) {
        slingshot->SetVisible(visible);
    }
}

void Slingshot::Pull(const glm::vec2 &pos) const {
    constexpr float WIRE_OFFSET_FACTOR = 2.8f;
    constexpr auto WIRE_OFFSET = glm::vec2(-15, -55.f);
    const auto slingshotPos = GetPosition() - WIRE_OFFSET;
    const auto posBias = pos - slingshotPos;
    const auto posOffset = posBias/WIRE_OFFSET_FACTOR;
    const auto rotation = atan2(-posBias.y, -posBias.x);
    for (int i = 0; i < 3; i++) {
        m_wires[i]->SetVisible(true);
        m_wires[i]->m_Transform.translation = pos - posOffset*glm::vec2(i, i);
        m_wires[i]->m_Transform.rotation = rotation;
    }
}

void Slingshot::Release() const {
    for (const auto &wire: m_wires) {
        wire->SetVisible(false);
    }
}

void Slingshot::SetPosition(const glm::vec2 &Position) const {
    for (const auto &slingshot: m_slingshot) {
        slingshot->m_Transform.translation = Position;
    }
}
