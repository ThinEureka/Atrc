#include <iostream>
#include <vector>

#include <AGZUtils/Utils/Exception.h>
#include <Atrc/Editor/GL.h>

void InitImGui(GLFWwindow *window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window);
    ImGui_ImplOpenGL3_Init();

    ImGui::StyleColorsDark();

    ImGui::GetStyle().WindowRounding = 0;
    ImGui::GetStyle().FrameBorderSize = 1;

    ImFontConfig fontConfig;
    fontConfig.SizePixels = 16;
    ImGui::GetIO().Fonts->AddFontDefault(&fontConfig);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::EndFrame();
}

void Run(GLFWwindow *window)
{
    using namespace GL;
    using namespace AGZ::Input;

    // 初始化IMGUI

    InitImGui(window);

    // 准备输入category

    KeyboardManager<GLFWKeyboardCapturer> keyboardMgr;
    keyboardMgr.GetCapturer().Initialize(window);
    auto &keyboard = keyboardMgr.GetKeyboard();

    MouseManager<GLFWMouseCapturer> mouseMgr;
    mouseMgr.GetCapturer().Initialize(window);
    auto &mouse = mouseMgr.GetMouse();

    WindowManager<GLFWWindowCapturer> winMgr;
    winMgr.GetCapturer().Initialize(window);
    auto &win = winMgr.GetWindow();

    AGZ::ObjArena<> arena;
    win.AttachHandler(arena.Create<FramebufferSizeHandler>(
        [&](const FramebufferSize &param)
    {

    }));
    keyboard.AttachHandler(arena.Create<KeyDownHandler>(
        [&](const KeyDown &param)
    {
        ImGui_ImplGlfw_KeyDown(param.key);
    }));
    keyboard.AttachHandler(arena.Create<KeyUpHandler>(
        [&](const KeyUp &param)
    {
        ImGui_ImplGlfw_KeyUp(param.key);
    }));
    keyboard.AttachHandler(arena.Create<CharEnterHandler>(
        [&](const CharEnter &param)
    {
        ImGui_ImplGlfw_Char(param.ch);
    }));
    mouse.AttachHandler(arena.Create<MouseButtonDownHandler>(
        [&](const MouseButtonDown &param)
    {
        ImGui_ImplGlfw_MouseButtonDown(param.button);
    }));
    mouse.AttachHandler(arena.Create<WheelScrollHandler>(
        [&](const WheelScroll &param)
    {
        ImGui_ImplGlfw_WheelScroll(param.offset);
    }));

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        keyboardMgr.Capture();
        mouseMgr.Capture();
        winMgr.Capture();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderContext::ClearColorAndDepth();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
}

int main()
{
    if(!glfwInit())
    {
        std::cout << "Failed to initialize glfw" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(640, 480, "Editor", nullptr, nullptr);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize glew" << std::endl;
        return -1;
    }

    glfwSwapInterval(1);

    try
    {
        Run(window);
    }
    catch(const std::exception &err)
    {
        std::vector<std::string> errMsgs;
        AGZ::ExtractHierarchyExceptions(err, std::back_inserter(errMsgs));
        for(auto &m : errMsgs)
            std::cout << m << std::endl;
    }
    catch(...)
    {
        std::cout << "An unknown error occurred..." << std::endl;
    }
}
