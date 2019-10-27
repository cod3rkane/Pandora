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
    protected:
        Mesh2D mesh;
        float width = 50.0f;
        float height = 50.0f;
        glm::vec3 Position;
        GLfloat rotate = 0.0f;
        Entity entity;
        bool isInteractive = false;
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

        void setVertices(std::vector<Vertex2D> v) {
            mesh.vertices = v;
        }

        const std::vector<Vertex2D> getVertices() {
            return mesh.vertices;
        }

        void setMesh(Mesh2D m) {
            mesh = m;
        }

        const Mesh2D getMesh() {
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

        void setRotate(GLfloat r) {
            rotate = r;
        }

        GLfloat getRotate() {
            return rotate;
        }

        const glm::mat4 getModelMatrix(int windowWidth, int windowHeight) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, Position);  

            model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f)); 
            model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); 
            model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));

            model = glm::scale(model, glm::vec3(width, height, 1.0f));

            return model;
        }

        void setupVertices() {
            Vertex2D v0 = { glm::vec2(0.0f, 1.0f) };
            Vertex2D v1 = { glm::vec2(1.0f, 0.0f) };
            Vertex2D v2 = { glm::vec2(0.0f, 0.0f) };
            Vertex2D v3 = { glm::vec2(0.0f, 1.0f) };
            Vertex2D v4 = { glm::vec2(1.0f, 1.0f) };
            Vertex2D v5 = { glm::vec2(1.0f, 0.0f) };

            mesh.vertices = { v0, v1, v2, v3, v4, v5 };
            mesh.color = glm::vec4(0.498039f, 0.596078f, 0.729412f, 1.0f);
            Position = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        virtual void update(int windowWidth, int windowHeight, double mouseX, double mouseY, bool isMousePressed) {};

        void setInteractive(bool in) {
            isInteractive = in;
        }
    };

    class Component : public ComponentCore {
        std::vector<ComponentCore> children;
    public:
        ~Component() {};

        void addChildren(ComponentCore& component);

        std::vector<ComponentCore> getChildrens();

        void update(int windowWidth, int windowHeight, double mouseX, double mouseY, bool isMousePressed);

        bool getIsInteractive() {
            return isInteractive;
        }
    };
}

#endif // CGAME_UICOMPONENT_H
