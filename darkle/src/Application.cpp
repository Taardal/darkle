#include "Log.h"
#include "Application.h"
#include "window/events/KeyEvent.h"
#include "window/input/KeyCodes.h"

namespace Darkle {

    Application::Application(Window* window, Renderer* renderer) : window(window), renderer(renderer), running(false) {
        LOG_TRACE(TAG, "Creating");
        window->setOnEventListener([this](const Event& event) {
            onEvent(event);
        });
        LOG_TRACE(TAG, "Created");
    }

    Application::~Application() {
        LOG_TRACE(TAG, "Destroyed");
    }

    void Application::pushLayer(Layer* layer) {
        layerStack.pushLayer(layer);
    }

    void Application::run() {
        LOG_INFO(TAG, "Running...");
        running = true;
        while (running) {
            for (Layer* layer : layerStack) {
                layer->onUpdate(renderer);
            }
            window->onUpdate();
        }
    }

    void Application::onEvent(const Event& event) {
        LOG_DEBUG(TAG, "Received event [{0}]", event.toString());
        if (event.getType() == EventType::KeyPressed) {
            auto* keyEvent = (KeyEvent*) &event;
            if (keyEvent->getKeyCode() == KeyCode::KEY_ESCAPE) {
                LOG_INFO(TAG, "Stopping...");
                running = false;
            }
        }
        if (event.getType() == EventType::MouseButtonPressed) {
            for (auto iterator = layerStack.end(); iterator != layerStack.begin();) {
                Layer* layer = *--iterator;
                layer->onEvent(event);
            }
        }
    }

}
