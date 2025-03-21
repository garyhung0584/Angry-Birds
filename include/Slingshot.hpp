#ifndef SLINGSHOT_HPP
#define SLINGSHOT_HPP

#include <string>

#include "Util/Logger.hpp"

#include "Util/GameObject.hpp"

class Slingshot : public Util::GameObject {
public:
    explicit Slingshot(const std::string& ImagePath);

    Slingshot(const Slingshot&) = delete;

    Slingshot(Slingshot&&) = delete;

    Slingshot& operator=(const Slingshot&) = delete;

    Slingshot& operator=(Slingshot&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }


private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};

#endif //SLINGSHOT_HPP
