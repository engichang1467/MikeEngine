#include <time.h>
#include <typeinfo>
#include "src/graphics/window.h"
#include "src/maths/vec2.h"
#include "src/maths/vec3.h"
#include "src/maths/vec4.h"

int main()
{
    clock_t begin = clock();

    using namespace torpo;
    using namespace graphics;
    using namespace maths;

    Window window("Torpo!", 960, 540);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

//     printf("Working\n");
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
//     printf("working\n");

    // vec2 vector(1.0f, 2.0f);
    // vector.add(vec2(5, 2)).subtract(vec2(1, 1));

    // vec2 a(1.0f, 2.0f);
    // vec2 b(2, 4);
    

    // vec2 c = a + b;

    // a += b;
    // a -= b;
    // a *= b;
    // a /= b;

    // // 3d vector
    // vec3 a(1.0f, 2.0f, 5.0f);
    // vec3 b(2, 4, 6);

    // vec3 c = a + b;

    // 4d vector
    vec4 a(0.2f, 0.3f, 0.8f, 1.0f);
    vec4 b(0.5f, 0.2f, 0.1f, 1.0f);

    vec4 c = a + b;


    while (!window.closed())
    {
        // printf("%d, %d\n", window.getWidth(), window.getHeight());
        window.clear();
        std::cout << c << std::endl;

        // if (window.isKeyPressed(GLFW_KEY_A))
        //     printf("PRESSED!\n");

        // if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        //     printf("PRESSED!\n");
        
        double x, y;
        window.getMousePosition(x, y);
        // printf("%d, %d\n", static_cast<int>(x), static_cast<int>(y));
    

#if 1
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f,  0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();
#else
        glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif
        window.update();
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time: %lf\n", time_spent);

    // system("PAUSE");    
    return 0;
}