#pragma once

#include "log.h"

#include "model.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace k3::graphics {

    struct TransformComponent {

        glm::vec3 translation{};  // (position offset)

        glm::vec3 scale{1.f, 1.f, 1.f};

        glm::vec3 rotation{};

        // Matrix corresponds to translate * Ry * Rx * Rz * scale transformation
        // Tait-bryan with axis order Y, X, Z
        glm::mat4 mat4() {
            //auto transform = glm::translate(glm::mat4{1.f}, translation);
            /*
            transform = glm::rotate(transform, rotation.y, {0.f, 1.f, 0.f});
            transform = glm::rotate(transform, rotation.x, {1.f, 0.f, 0.f});
            transform = glm::rotate(transform, rotation.z, {0.f, 0.f, 1.f});
            */
            //transform = glm::scale(transform, scale);
            //return transform;

            // Faster version based on wikipedia
            const float c3 = glm::cos(rotation.z);
            const float s3 = glm::sin(rotation.z);
            const float c2 = glm::cos(rotation.x);
            const float s2 = glm::sin(rotation.x);
            const float c1 = glm::cos(rotation.y);
            const float s1 = glm::sin(rotation.y);
            return glm::mat4{
                {
                    scale.x * (c1 * c3 + s1 * s2 * s3),
                    scale.x * (c2 * s3),
                    scale.x * (c1 * s2 * s3 - c3 * s1),
                    0.0f,
                },
                {
                    scale.y * (c3 * s1 * s2 - c1 * s3),
                    scale.y * (c2 * c3),
                    scale.y * (c1 * c3 * s2 + s1 * s3),
                    0.0f,
                },
                {
                    scale.z * (c2 * s1),
                    scale.z * (-s2),
                    scale.z * (c1 * c2),
                    0.0f,
                },
                {translation.x, translation.y, translation.z, 1.0f}};
        }

    };

    class KeGameObject {

        public:
            using id_t = unsigned int;

            static KeGameObject createGameObject() {
                static id_t currentId = 0;
                return KeGameObject(currentId++);
            };

            KeGameObject();

            ~KeGameObject();

            KeGameObject(const KeGameObject &) = delete;
            KeGameObject &operator=(const KeGameObject &) = delete;
            KeGameObject(KeGameObject &&) = default;
            KeGameObject &operator=(KeGameObject &&) = default;

            id_t getId() { return m_id; };

            std::shared_ptr<KeModel> model;

            glm::vec3 color{};

            TransformComponent transform{};
        
        private:

            KeGameObject(id_t objId) : m_id{objId} {};
            
            id_t m_id;
    };
}