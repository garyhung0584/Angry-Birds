#include "Birds.hpp"

void Birds::AddPositionToTrail(const glm::vec2& position) {
    m_TrailPositions.push_back(position);
    // Optional: Limit the size of the trail
    if (m_TrailPositions.size() > 50) { // Keep last 50 positions
        m_TrailPositions.erase(m_TrailPositions.begin());
    }
}

const std::vector<glm::vec2>& Birds::GetTrailPositions() const {
    return m_TrailPositions;
}


