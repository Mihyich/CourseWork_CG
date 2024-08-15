#include "render_wnd_proc.h"

void GenPlaneMesh(GLuint &planeVAO, GLuint &planeVBO, GLuint &planeEBO)
{   
    const float size = 20;

    float planeVertices[] = {
        -0.5f * size, 0.0f, -0.5f * size,
        0.5f * size, 0.0f, -0.5f * size,
        0.5f * size, 0.0f,  0.5f * size,
        -0.5f * size, 0.0f,  0.5f * size,
    };

    unsigned int planeIndices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glGenBuffers(1, &planeEBO);

    glBindVertexArray(planeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SetupOpenGLServices()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

LRESULT RenderWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT client_rect = {0, 0, 0, 0};
    static int client_width = 0;
    static int client_height = 0;

    static WinApiMouse mouse;
    static vec2 mouse_delta = {0, 0};

    static CameraMode camera_mode = ORBITTING;
    static Matrix4D view;
    static vec3 view_pos = {5.0f, 0.5f, 0.0f};
    static vec3 view_dst = {0.0f, 0.5f, 0.0f};
    static vec3 view_up = {0.0f, 1.0f, 0.0f};
    static float orbitting_x_rot = 0.0f;
    static float orbitting_y_rot = 0.0f;
    static float orbitting_radius = 5.0f;

    static Matrix4D projection;
    static float proj_near = 0.01f;
    static float proj_far = 50.0f;
    static float proj_fov = degrees_to_radians(60.0f);

    static GLuint planeVAO = 0;
    static GLuint planeVBO = 0;
    static GLuint planeEBO = 0;
    static Matrix4D planeModel;

    static Shader shader;

    static float v = 0.0f;

    switch (message)
    {

    case WM_INIT_GL_OPTIONS:
    {
        shader.set_shader_name("shader");
        shader.create_from_file("Shaders/vertex.glsl", GL_VERTEX_SHADER);
        shader.create_from_file("Shaders/fragment.glsl", GL_FRAGMENT_SHADER);
        shader.link_program();
        shader.init_attribs_and_uniforms();
        shader.print_uniforms();
        shader.print_attribs();

        mat4_set_look_at(&view, &view_pos, &view_dst, &view_up);
        mat4_set_perspective_projection(&projection, 800, 600, proj_near, proj_far, proj_fov);

        GenPlaneMesh(planeVAO, planeVBO, planeEBO);
        // mat4_set_translate(&planeModel, 0.f, -0.5f, 0.0f);
        mat4_set_ordinary(&planeModel);

        SetupOpenGLServices();
        return EXIT_SUCCESS;
    }

    case WM_SIZE:
    {
        GetClientRect(hWnd, &client_rect);
        client_width = get_rect_width(client_rect);
        client_height = get_rect_height(client_rect);
        mat4_set_perspective_projection(&projection, client_width, client_height, proj_near, proj_far, proj_fov);
        glViewport(0, 0, client_width, client_height);
        return EXIT_SUCCESS;
    }

    case WM_LBUTTONDOWN:
    {
        mouse.l_button_down();
        return EXIT_SUCCESS;
    }

    case WM_LBUTTONUP:
    {
        mouse.l_button_up();
        return EXIT_SUCCESS;
    }

    case WM_MOUSEMOVE:
    {
        mouse.move();

        if (mouse.l_tracking)
        {
            mouse_delta.x = (float)mouse.l_delta_pos.x;
            mouse_delta.y = (float)mouse.l_delta_pos.y;

            if (camera_mode == ORBITTING)
            {
                vec3 pos = {0.f, 3.f, -orbitting_radius};
                Quaternion quat_x;
                Quaternion quat_y;
                Quaternion quat_res;

                orbitting_x_rot += (float)(mouse_delta.y / client_height) * 180.f;
                orbitting_y_rot += (float)(mouse_delta.x / client_width) * 360.f;

                quat_set_rotate_degrees(&quat_x, 1.f, 0.f, 0.f, orbitting_x_rot);
                quat_set_rotate_degrees(&quat_y, 0.f, 1.f, 0.f, orbitting_y_rot);
                quat_compose_res(&quat_y, &quat_x, &quat_res);

                quat_rotate_vec(&pos, &quat_res);

                view_pos = pos;
            }
            else if (camera_mode == MOVING)
            {

            }

            mat4_set_look_at(&view, &view_pos, &view_dst, &view_up);
        }

        return EXIT_SUCCESS;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        v += 0.2f;
        glClearColor(sinf(v), cosf(v), 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        uniform_matrix4f(shader.get_uniform_location("model"), &planeModel);
        uniform_matrix4f(shader.get_uniform_location("view"), &view);
        uniform_matrix4f(shader.get_uniform_location("projection"), &projection);

        glBindVertexArray(planeVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        SwapBuffers(hdc);

        EndPaint(hWnd, &ps);
        return EXIT_SUCCESS;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}