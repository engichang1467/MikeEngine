#include "window.h"

namespace torpo {
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
                printf("Fail to initialize GLFW!\n");
                return false;
            }

            m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
            if (!m_Window)
            {
                printf("Failed to create GLFW window!\n");
                return false;
            }

            glfwMakeContextCurrent(m_Window);
            glfwSetWindowSizeCallback(m_Window, windowResize);


            // Warning: Make sure we check glewInit after we create the context, or else it won't work
            glewExperimental = GL_TRUE; // Need this so it will not seg fault 11 on MACOS
            if (glewInit() != GLEW_OK)
            {
                printf("Could not initialize GLEW!\n");
                return false;
            }

            printf("OpenGL %s\n", glGetString(GL_VERSION));
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
