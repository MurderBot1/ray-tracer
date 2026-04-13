// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#include "window.h"

ImGuiIO* Window::m_io;
bool Window::m_showing;

void Window::CreateWindow()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    m_io = &ImGui::GetIO();

    unsigned char* pixels;
    int w, h;
    m_io->Fonts->GetTexDataAsRGBA32(&pixels, &w, &h);

    m_showing = true;
}

void Window::DisplayFrame() 
{
    m_io->DisplaySize = ImVec2(800.0f, 600.0f);
    m_io->DeltaTime = 1.0f / 60.0f;

    ImGui::NewFrame();

    ImGui::Begin("No-backend window", &m_showing);
    ImGui::Text("Hello from Dear ImGui core only.");
    ImGui::End();

    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();
}

void Window::DestroyWindow() 
{
    ImGui::DestroyContext();
}
