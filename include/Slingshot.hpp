#ifndef SLINGSHOT_HPP
#define SLINGSHOT_HPP

#include <string>

#include "Util/Logger.hpp"

#include "Util/GameObject.hpp"

class Slingshot {
public:
    explicit Slingshot(const glm::vec2 &pos);

    Slingshot(const Slingshot&) = delete;

    Slingshot(Slingshot&&) = delete;

    Slingshot& operator=(const Slingshot&) = delete;

    Slingshot& operator=(Slingshot&&) = delete;

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_slingshot.back()->m_Transform.translation; }

    void SetVisible(bool Visible);

    void SetPosition(const glm::vec2& Position);

    void Pull(const glm::vec2& pos);

    void Release();

    std::vector<std::shared_ptr<Util::GameObject>> GetSlingshot() { return m_slingshot; }
    std::vector<std::shared_ptr<Util::GameObject>> GetWire() { return m_wires; }


private:
    std::vector<std::shared_ptr<Util::GameObject>> m_slingshot;
    std::vector<std::shared_ptr<Util::GameObject>> m_wires;
};

#endif //SLINGSHOT_HPP
