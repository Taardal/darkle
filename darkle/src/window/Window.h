#pragma once

#include "graphics/GraphicsContext.h"
#include "events/Event.h"
#include <GLFW/glfw3.h>
#include <functional>

namespace Darkle {

    class Window {
    public:
        struct Config {
            const char* title;
            int width;
            int height;
        };

    private:
        struct GlfwCallbackData {
            std::function<void(const Event&)> onEvent;
            int width;
            int height;
        };

    private:
        GlfwCallbackData glfwCallbackData;
        GLFWwindow* glfwWindow;

    public:
        Window(const Config& config, GraphicsContext* graphicsContext);

        ~Window();

        void setOnEventListener(const std::function<void(const Event&)>& onEvent);

        void onUpdate() const;

    private:
        void initGlfw() const;

        void setGlfwWindowHints(GraphicsContext* graphicsContext) const;

        [[nodiscard]] GLFWwindow* createGlfwWindow(const Config& config) const;

        void setGlfwCallbacks();

        void setGlfwWindowCallbacks() const;

        void setGlfwKeyCallbacks() const;

        void setGlfwMouseCallbacks() const;

        void destroyGlfwWindow() const;

        void terminateGlfw() const;
    };

}

