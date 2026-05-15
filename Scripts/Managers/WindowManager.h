#pragma once
#include "pch.h"
#include "Singleton.h"
#include "Game.h"

class WindowManager : public Singleton<WindowManager>
{
    friend Singleton<WindowManager>;

protected:
    WindowManager() = default;
    ~WindowManager() override = default;
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

private:
    GLFWwindow* currentWindow;

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    float windowWidth;
    float windowHeight;

    void InitializeGl(int width, int height, const char *title);
    void SetCallBacks();

    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    void Init();

    GLFWwindow* GetWindow() { return currentWindow; }
    float GetWindowHeight() { return windowHeight; }
    float GetWindowWidth() { return windowWidth; }

};