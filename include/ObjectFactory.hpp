#ifndef OBJECT_FACTORY_HPP
#define OBJECT_FACTORY_HPP

#include "Physics2D.hpp"
#include "Util/Logger.hpp"


#include "BigBird.hpp"
#include "BlackBird.hpp"
#include "BlueBird.hpp"
#include "RedBird.hpp"
#include "WhiteBird.hpp"
#include "YellowBird.hpp"

#include <memory>
#include <string>
#include <glm/glm.hpp>

class ObjectFactory {
public:
    ObjectFactory(b2WorldId worldId)
        : m_WorldId(worldId) {}

    std::shared_ptr<Birds> CreateBird(BirdType birdType, const glm::vec2& position);
    std::shared_ptr<Physics2D> CreatePig(PigType pigType, const glm::vec2& position);
    std::shared_ptr<Physics2D> CreateStructure(EntityType material, StructureType shape,
                                               const glm::vec2& position, float rotation);

private:
    b2WorldId m_WorldId;

    std::shared_ptr<Physics2D> CreateObject(const std::string& imagePath,
                                            const glm::vec2& position,
                                            int health,
                                            EntityType type,
                                            const glm::vec2& size,
                                            float scale,
                                            float rotation,
                                            float density,
                                            float friction,
                                            bool isAwake);
};

#endif // OBJECT_FACTORY_HPP
