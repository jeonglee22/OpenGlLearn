#pragma once
#include "pch.h"
#include "Camera.h"
#include "Singleton.h"
#include "SceneManager.h"
#include "WindowManager.h"
#include "ShaderManager.h"

class Game : public Singleton<Game>
{
    friend Singleton<Game>;

protected:
    Game() = default;
    ~Game() override = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

private:
    // Input management

    // scene management

    // Time management
    // float timeScale;
    float lastFrame = 0.f;
    float deltaTime = 0.f;
    // float fixedDeltaTime;
    // float unscaledTime;
    // float fixedUnscaledTime;

    Camera camera;
    void ProcessInput();
    bool firstMouse = true;
    float lastX;
    float lastY;

public:
    void Init();
    void Do();
    void Release();

    void MouseCallback(double xposIn, double yposIn);
    void ScrollCallback(double xOffset, double yOffset);

    // float GetTimeScale() const { return timeScale; }
    // float GetDeltaTime() const { return deltaTime; }
    // float GetFixedDeltaTime() const { return fixedDeltaTime; }
    // float GetUnscaledTime() const { return unscaledTime; }
    // float GetFixedUnscaledTime() const { return fixedUnscaledTime; }

    // setters
    // void SetTimeScale(float newTimeScale) { timeScale = newTimeScale; }

};