#include "pch.h"
#include "DebugManager.h"

void DebugManager::CreateConsoleWindow()
{
    // 콘솔 할당
    AllocConsole();

    // 콘솔 입출력을 C++ 스트림에 바인딩
    FILE* fileStream;
    freopen_s(&fileStream, "CONOUT$", "w", stdout); // 표준 출력 연결
    freopen_s(&fileStream, "CONIN$", "r", stdin);  // 표준 입력 연결
    freopen_s(&fileStream, "CONERR$", "w", stderr); // 표준 에러 연결

    std::cout << "Console window created!" << std::endl;
}

void DebugManager::LogVec3ToConsole(const Vec3& vec, const std::string& label)
{
    std::cout << label << ": (" << vec.x << ", " << vec.y << ", " << vec.z << ")\n";
}
// 예제 코드
// LogVec3ToConsole(moveDir, "moveDir");