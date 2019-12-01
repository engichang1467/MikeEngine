#include "window.h"

namespace mikey {
    namespace graphics {

        void windowResize(GLFWwindow *window, int width, int height);
        
        Window::Window(const char *title, int width, int height)
        {
            m_Title = title;
            m_Width = width;
            m_Height = height;
            if (!init())
                glfwTerminate();
        }

        Window::~Window()
        {
            glfwTerminate();
        }

        bool Window::init()
        {
            if (!glfwInit())
            {
                std::cout << "Fail to initialize GLFW!" << std::endl;
                return false;
            }

            m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
            if (!m_Window)
            {
                std::cout << "Failed to create GLFW window!" << std::endl;
                return false;
            }

            glfwMakeContextCurrent(m_Window);
            glfwSetWindowSizeCallback(m_Window, windowResize);


            // Warning: Make sure we check glewInit after we create the context, or else it won't work
            glewExperimental = GL_TRUE; // Need this so it will not seg fault 11 on MACOS
            if (glewInit() != GLEW_OK)
            {
                std::cout << "Could not initialize GLEW!" << std::endl;
                return false;
            }

            std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
            return true;
        }

        void Window::clear() const
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Window::update()
        {
            glfwPollEvents();
            glfwSwapBuffers(m_Window);
        }

        bool Window::closed() const
        {
            return glfwWindowShouldClose(m_Window);
        }

        void windowResize(GLFWwindow *window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
    }
}
