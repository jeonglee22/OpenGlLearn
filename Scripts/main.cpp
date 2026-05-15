#include "pch.h"
#include "Game.h"

// using namespace glm;
using namespace std;

int main() {
    // 테스트 라인

    // game line
    Game::GetInstance().Init();
    Game::GetInstance().Do();
    Game::GetInstance().Release();
    
    return 0;
}