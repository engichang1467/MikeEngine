#include "window.h"

namespace torpo {
    namespace graphics {

        void window_resize(GLFWwindow *window, int width, int height);
        
        Window::Window(const char *title, int width, int height)
        {
            m_Title = title;
            m_Width = width;
            m_Height = height;
            if (!init())
                glfwTerminate();

            for (int i  = 0; i < MAX_KEYS; i++)
                m_Keys[i] = false;

            for (int i = 0 ; i < MAX_BUTTONS; i++)
                m_MouseButtons[i] = false;
        }

        Window::~Window()
        {
            glfwTerminate();
        }
        
        void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            Window *win = (Window*) glfwGetWindowUserPointer(window);
            win->m_Keys[key] = action != GLFW_RELEASE;
            // printf("callback work!");
        }

        void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
        {
            Window *win = (Window*) glfwGetWindowUserPointer(window);
            win->m_MouseButtons[button] = action != GLFW_RELEASE;
        }
        void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
        {
            Window *win = (Window*) glfwGetWindowUserPointer(window);
            win->mx = xpos;
            win->my = ypos;
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
            glfwSetWindowUserPointer(m_Window, this);
            glfwSetWindowSizeCallback(m_Window, window_resize);
            glfwSetKeyCallback(m_Window, key_callback);
            glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
            glfwSetCursorPosCallback(m_Window, cursor_position_callback);


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

        bool Window::isKeyPressed(unsigned int keycode) const
        {
            if (keycode >= MAX_KEYS)
                return false;

            return m_Keys[keycode];
        }

        bool Window::isMouseButtonPressed(unsigned int button) const
        {
            if (button >= MAX_BUTTONS)
                return false;

            return m_MouseButtons[button];
        }

        void Window::getMousePosition(double &x, double &y) const
        {
            x = mx;
            y = my;
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

        void window_resize(GLFWwindow *window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
    }
}
