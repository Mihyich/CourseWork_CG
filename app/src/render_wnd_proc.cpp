#include "render_wnd_proc.h"

void GenPlaneMesh(GLuint &planeVAO, GLuint &planeVBO, GLuint &planeEBO)
{
    float planeVertices[] = {
        -0.5f, 0.0f, -0.5f,
        0.5f, 0.0f, -0.5f,
        0.5f, 0.0f,  0.5f,
        -0.5f, 0.0f,  0.5f,
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SetupOpenGLServices()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
}

LRESULT RenderWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT client_rect = {0, 0, 0, 0};

    static Matrix4D view;

    static GLuint planeVAO = 0;
    static GLuint planeVBO = 0;
    static GLuint planeEBO = 0;

    static Shader shader;

    static float v = 0.0f;

    switch (message)
    {

    case WM_INIT_GL_OPTIONS:
    {
        GenPlaneMesh(planeVAO, planeVBO, planeEBO);
        SetupOpenGLServices();
        return EXIT_SUCCESS;
    }

    case WM_SIZE:
    {
        GetClientRect(hWnd, &client_rect);
        glViewport(0, 0, get_rect_width(client_rect), get_rect_height(client_rect));
        return EXIT_SUCCESS;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        v += 0.2f;
        glClearColor(sinf(v), cosf(v), 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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