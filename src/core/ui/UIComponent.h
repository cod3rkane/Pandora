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
        Mesh2D mesh;
        float width = 50.0f;
        float height = 50.0f;
        glm::vec3 Position;
        glm::vec3 Scale;
        glm::vec3 Rotation;
        Entity entity;
    public:

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
            mesh.vertices = v;
        }

        std::vector<Vertex2D> getVertices() {
            return mesh.vertices;
        }

        void setMesh(Mesh2D m) {
            mesh = m;
        }

        Mesh2D getMesh() {
            return mesh;
        }

        glm::vec4 getColorMesh() {
            return mesh.color;
        }

        void setColorMesh(glm::vec4 c) {
            mesh.color = c;
        }

        void setEntity(Entity e) {
            entity = e;
        }

        const Entity getEntity() {
            return entity;
        }

        glm::mat4 getModelMatrix(int windowWidth, int windowHeight) {
            // resize GUI
            float xScale = width / windowWidth;
            float yScale = height / windowHeight;
            float xOffset = (Position.x / windowWidth) * 2.0f -1.0f;
            float yOffset = (Position.y / windowHeight) * 2.0f -1.0f;

            // @TODO: dummy logic, fix that later
            if (xOffset < 0) {
                xOffset += xScale;
            } else {
                xOffset -= xScale;
            }

            if (yOffset < 0) {
                yOffset += yScale;
            } else {
                yOffset -= yScale;
            }

            float inverseYOffset = yOffset * -1.0f;

            return Maths::createTransformationMatrix(
                glm::vec3(xOffset, inverseYOffset, 0.0f),
                glm::vec3(xScale, yScale, 0.0f),
                Rotation
            );
        }

        void setupVertices() {
            Vertex2D v0 = { glm::vec2(-1.0f, -1.0f) };
            Vertex2D v1 = { glm::vec2(1.0f, -1.0f) };
            Vertex2D v2 = { glm::vec2(-1.0f, 1.0f) };
            Vertex2D v3 = { glm::vec2(-1.0f, 1.0f) };
            Vertex2D v4 = { glm::vec2(1.0f, -1.0f) };
            Vertex2D v5 = { glm::vec2(1.0f, 1.0f) };

            mesh.vertices = { v0, v1, v2, v3, v4, v5 };
            mesh.color = glm::vec4(0.498039f, 0.596078f, 0.729412f, 1.0f);
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
