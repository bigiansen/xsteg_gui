#include "imgui_ctx.hpp"

imgui_ctx::imgui_ctx(window* wnd)
{
    _wnd = wnd;

    const std::string glsl_version = "#version 130";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(_wnd->wnd_ptr(), true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void imgui_ctx::start(std::function<void(void)> main_loop)
{
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!_wnd->should_close())
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        main_loop();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(_wnd->wnd_ptr(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(_wnd->wnd_ptr());
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(_wnd->wnd_ptr());
    glfwTerminate();
}