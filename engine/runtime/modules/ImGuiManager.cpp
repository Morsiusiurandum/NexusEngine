#include "ImGuiManager.h"
#include "imgui.h"

ImguiManager::ImguiManager()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

ImguiManager::~ImguiManager()
{
    ImGui::DestroyContext();
}
