//
// Created by cod3r on 10/28/19.
//

#ifndef CGAME_CORECOMPONENT_H
#define CGAME_CORECOMPONENT_H

#include <GL/glew.h>

#include "../../components/Render.h"
#include "../../util/registry.h"

namespace UI {
    class CoreComponent {
    protected:
        Mesh2D mesh;
        float width = 50.0f;
        float height = 50.0f;
        glm::vec3 position;
        GLfloat rotate = 0.0f;
        Entity entity;
        bool interactive = false;
    public:
        CoreComponent();
        ~CoreComponent();

        const Mesh2D &getMesh() const;

        void setMesh(const Mesh2D &mesh);

        float getWidth() const;

        void setWidth(float width);

        float getHeight() const;

        void setHeight(float height);

        const glm::vec3 &getPosition() const;

        void setPosition(const glm::vec3 &position);

        GLfloat getRotate() const;

        void setRotate(GLfloat rotate);

        Entity getEntity() const;

        void setEntity(Entity entity);

        bool isInteractive() const;

        void setInteractive(bool interactive);

        const glm::mat4 getModelMatrix() const;

        void setColorMesh(const glm::vec4 &color);

        virtual void update(double mouseX, double mouseY, bool isMousePressed) = 0;
    private:
        void setup();
    };
}


#endif //CGAME_CORECOMPONENT_H
