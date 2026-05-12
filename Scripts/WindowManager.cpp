#include "WindowManager.h"

void WindowManager::Init()
{
    InitializeGl(SCR_WIDTH, SCR_HEIGHT, "GameWindow");
}

void WindowManager::InitializeGl(int width, int height, const char* title)
{
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패\n";
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    currentWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!currentWindow) {
        std::cerr << "윈도우 생성 실패\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(currentWindow);
    SetCallBacks();

    windowHeight = height;
    windowWidth = width;

    // GLAD 초기화
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD 초기화 실패\n";
        return ;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(currentWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return;
}

void WindowManager::SetCallBacks()
{
    glfwSetFramebufferSizeCallback(currentWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(currentWindow, mouse_callback);
    glfwSetScrollCallback(currentWindow, scroll_callback);
}

void WindowManager::mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    Game::GetInstance().MouseCallback(xposIn, yposIn);
}

void WindowManager::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    Game::GetInstance().ScrollCallback(xoffset, yoffset);
}

void WindowManager::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
