// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#include "rt-window.h"

std::unique_ptr<Window> Window::ref = nullptr;

void Window::Init()
{    
    ref = std::make_unique<Window>();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ref->m_io = &ImGui::GetIO();

    unsigned char* pixels;
    int w, h;
    ref->m_io->Fonts->GetTexDataAsRGBA32(&pixels, &w, &h);

    ref->m_showing = true;
}

void Window::DisplayFrame() 
{
    ref->m_io->DisplaySize = ImVec2(800.0f, 600.0f);
    ref->m_io->DeltaTime = 1.0f / 60.0f;

    ImGui::NewFrame();

    ImGui::Begin("No-backend window", &ref->m_showing);
    ImGui::Text("Hello from Dear ImGui core only.");
    ImGui::End();

    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();
}

void Window::DestroyWindow() 
{
    ImGui::DestroyContext();
}

GLFWwindow *Window::GetGLFWWindow()
{
    return ref->m_window.GetWindow();
}
