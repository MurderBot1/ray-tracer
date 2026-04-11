// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#include "window.h"

ImGuiIO* Window::io;
bool Window::show;

void Window::CreateWindow()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    io = &ImGui::GetIO();

    unsigned char* pixels;
    int w, h;
    io->Fonts->GetTexDataAsRGBA32(&pixels, &w, &h);

    show = true;
}

void Window::DisplayFrame() 
{
    // Renders the frame and displays it
    DisplayFrame(Renderer::Render());
}

void Window::DisplayFrame(const RendererOutput& input) 
{
    io->DisplaySize = ImVec2(800.0f, 600.0f);
    io->DeltaTime = 1.0f / 60.0f;

    ImGui::NewFrame();

    ImGui::Begin("No-backend window", &show);
    ImGui::Text("Hello from Dear ImGui core only.");
    ImGui::End();

    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();
}

void Window::DestroyWindow() 
{
    ImGui::DestroyContext();
}
