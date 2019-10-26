#ifndef CGAME_CORE_WINDOW_H
#define CGAME_CORE_WINDOW_H

#include <GLFW/glfw3.h>

namespace Core {
    class Window {
        GLFWwindow* mainWindow;
        int width;
        int height;
    public:
        void setWindow(GLFWwindow* windo);
        GLFWwindow* getWindow();
        void setWidth(int w);
        int getWidth();
        void setHeight (int h);
        int getHeight();
    };
}

#endif // CGAME_CORE_WINDOW_H
