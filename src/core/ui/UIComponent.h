#ifndef CGAME_UICOMPONENT_H
#define CGAME_UICOMPONENT_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>

#include "../../util/registry.h"
#include "../../components/Shader.h"
#include "../../components/Transform.h"
#include "../../components/Render.h"
#include "../../util/Maths.h"

namespace UI {
    class ComponentCore {
    public:
        std::vector<Vertex2D> vertices;
        float width = 50.0f;
        float height = 50.0f;
        glm::vec3 Position;
        glm::vec3 Scale;
        glm::vec3 Rotation;
        Entity entity;

        ComponentCore() {
            setupVertices();
        }

        void setWidth(float w) {
            width = w;
        }

        float getWidth() {
            return width;
        }

        void setHeight(float h) {
            height = h;
        }

        float getHeight() {
            return height;
        }

        void setPosition(glm::vec3 p) {
            Position = p;
        }

        glm::vec3 getPosition() {
            return Position;
        }

        void setScale(glm::vec3 s) {
            Scale = s;
        }

        glm::vec3 getScale() {
            return Scale;
        }

        void setRotation(glm::vec3 r) {
            Rotation = r;
        }

        glm::vec3 getRotation() {
            return Rotation;
        }

        void setVertices(std::vector<Vertex2D> v) {
            vertices = v;
        }

        std::vector<Vertex2D> getVertices() {
            return vertices;
        }

        void setEntity(Entity e) {
            entity = e;
        }

        const Entity getEntity() {
            return entity;
        }

        glm::mat4 getModelMatrix() {
            return Maths::createTransformationMatrix(Position, Scale, Rotation);
        }

        void setupVertices() {
            Vertex2D v0 = { glm::vec2(-1.0f, -1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
            Vertex2D v1 = { glm::vec2(1.0f, -1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
            Vertex2D v2 = { glm::vec2(-1.0f, 1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
            Vertex2D v3 = { glm::vec2(-1.0f, 1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
            Vertex2D v4 = { glm::vec2(1.0f, -1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };
            Vertex2D v5 = { glm::vec2(1.0f, 1.0f), glm::vec3(0.498039f, 0.596078f, 0.729412f) };

            vertices = { v0, v1, v2, v3, v4, v5 };
            Position = glm::vec3(0.0f, 0.0f, 0.0f);
            Scale = glm::vec3(1.0f, 1.0f, 1.0f);
            Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        }
    };

    class Component : public ComponentCore {
        std::vector<ComponentCore> children;

    public:
        void addChildren(ComponentCore& component);
        std::vector<ComponentCore> getChildrens();
    };
}

#endif // CGAME_UICOMPONENT_H