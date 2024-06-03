//
// Created by redeb on 22.05.2024.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL

#include <string>
#include <gtx/quaternion.hpp>
#include <gtx/matrix_decompose.hpp>

#include "../Mesh.h"
#include "../Texture.h"

//RIGHT
constexpr static glm::vec3 unit_x = {1, 0, 0};

//UP
constexpr static glm::vec3 unit_y = {0, 1, 0};

//FORWARD
constexpr static glm::vec3 unit_z = {0, 0, 1};

#define ID_COL    {1}
#define ID_VEC    {0}
#define ID_VEC1   {1}
#define ID_QUAT   {1, 0, 0, 0}
#define ID_MAT4X4 {1}

const std::string glHasTextureUniform = "has_texture";
const std::string glColorUniform = "color";
const std::string glViewMatrixUniform = "view_matrix";
const std::string glModelMatrixUniform = "model_matrix";
const std::string glProjectionMatrixUniform = "projection_matrix";

#define DEFAULT_TAG "Default"

class Entity final {
    std::string m_tag = DEFAULT_TAG;

    std::vector<Entity*> m_children;
    Entity* m_parent = nullptr;

    glm::vec3 m_localPosition ID_VEC;
    glm::quat m_localOrientation ID_QUAT;
    glm::vec3 m_localScale ID_VEC1;

    glm::vec3 m_worldPosition ID_VEC;
    glm::quat m_worldOrientation ID_QUAT;
    glm::vec3 m_worldScale ID_VEC1;

    glm::mat4 m_localMatrix ID_MAT4X4;
    glm::mat4 m_worldMatrix ID_MAT4X4;

    bool m_isCamera;
    bool m_isActive;

    Mesh* m_mesh = nullptr;
    TextureRgba* m_texture = nullptr;
    glm::vec4 m_color ID_COL;

    void update();
public:
    explicit Entity(bool isCamera);

    ~Entity();

    [[nodiscard]] std::string getTag() const {
        return m_tag;
    }

    void setTag(const std::string& tag) {
        m_tag = tag;
    }

    [[nodiscard]] Mesh* getMesh() const {
        return m_mesh;
    }

    void setMesh(Mesh* mesh) {
        m_mesh = mesh;
    }

    [[nodiscard]] TextureRgba* getTexture() const {
        return m_texture;
    }

    void setTexture(TextureRgba* texture) {
        m_texture = texture;
    }

    [[nodiscard]] glm::vec4 getColor() const {
        return m_color;
    }

    void setColor(const glm::vec4& color) {
        m_color = color;
    }

    [[nodiscard]] glm::vec3 getLocalPosition() const {
        return m_localPosition;
    }

    glm::vec3 setLocalPosition(const glm::vec3& vec) {
        m_localPosition = vec; update();
        return vec;
    }

    [[nodiscard]] glm::quat getLocalOrientation() const {
        return m_localOrientation;
    }

    glm::quat setLocalOrientation(const glm::quat& quat) {
        m_localOrientation = quat; update();
        return quat;
    }

    [[nodiscard]] glm::vec3 getLocalScale() const {
        return m_localScale;
    }

    glm::vec3 setLocalScale(const glm::vec3& vec) {
        m_localScale = vec; update();
        return vec;
    }

    [[nodiscard]] glm::vec3 getWorldPosition() const {
        return m_worldPosition;
    }

    [[nodiscard]] glm::quat getWorldOrientation() const {
        return m_worldOrientation;
    }

    [[nodiscard]] glm::vec3 getWorldScale() const {
        return m_worldScale;
    }

    [[nodiscard]] glm::vec3 forward() const {
        return m_worldOrientation * -unit_z;
    }

    [[nodiscard]] glm::vec3 up() const {
        return m_worldOrientation * -unit_y;
    }

    [[nodiscard]] glm::vec3 right() const {
        return m_worldOrientation * -unit_x;
    }

    [[nodiscard]] size_t getChildCount() const {
        return m_children.size();
    }

    [[nodiscard]] Entity* getChild(const int32_t index) const {
        return m_children[index];
    }

    [[nodiscard]] Entity* getParent() const {
        return m_parent;
    }

    [[nodiscard]] glm::mat4 getLocalMatrix() const {
        return m_localMatrix;
    }

    [[nodiscard]] glm::mat4 getWorldMatrix() const {
        return m_worldMatrix;
    }

    [[nodiscard]] glm::vec3 worldToLocal(const glm::vec3 &vec) const;
    [[nodiscard]] glm::vec3 localToWorld(const glm::vec3 &vec) const;

    [[nodiscard]] bool active() const {
        return m_isActive;
    }

    void setActive(const bool activeState) {
        m_isActive = activeState;
    }

    void setParent(Entity* parent);

    void addChild(Entity* child);
    void removeChild(Entity* child);
};



#endif //ENTITY_H
