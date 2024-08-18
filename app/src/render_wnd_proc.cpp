#include "render_wnd_proc.h"

void GenQuadMesh(GLuint &quadVAO, GLuint &quadVBO)
{
    float quadVertices[] = {
        // позиции       // текстурные координаты
        -1.0f,  1.0f,    0.0f, 1.0f, //
        -1.0f, -1.0f,    0.0f, 0.0f, // 1 треугольник
         1.0f, -1.0f,    1.0f, 0.0f, //

        -1.0f,  1.0f,    0.0f, 1.0f, //
         1.0f, -1.0f,    1.0f, 0.0f, // 2 треугольник
         1.0f,  1.0f,    1.0f, 1.0f  //
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GenPlaneMesh(GLuint &planeVAO, GLuint &planeVBO, GLuint &planeEBO)
{   
    const float size = 20;

    float planeVertices[] = {
        // Позиции                         // Нормали
        -0.5f * size, 0.0f, -0.5f * size,  0.0f, 1.0f, 0.0f,
         0.5f * size, 0.0f, -0.5f * size,  0.0f, 1.0f, 0.0f,
         0.5f * size, 0.0f,  0.5f * size,  0.0f, 1.0f, 0.0f,
        -0.5f * size, 0.0f,  0.5f * size,  0.0f, 1.0f, 0.0f,
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

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

    static ShadowAlg shadowAlg = NO_SHADOW_LIGHT;

    static ShadowMapOrthogonalRenderData RenderDataSMO;
    static ShadowMapPerspectiveRenderData RenderDataSMP;

    static CameraMode camera_mode = ORBITTING;
    static float orbitting_x_rot = 0.0f;
    static float orbitting_y_rot = 0.0f;
    static float orbitting_radius = 5.0f;
    static vec3 viewPos = {0.f, 3.f, -orbitting_radius};
    static vec3 viewDst = {0.0f, 0.5f, 0.0f};
    static vec3 viewUp = {0.0f, 1.0f, 0.0f};
    static Matrix4D view;

    static Matrix4D projection;
    static float projNear = 1.f;
    static float projFar = 50.f;
    static float projFov = degrees_to_radians(60.0f);

    static GLuint quadVAO = 0;
    static GLuint quadVBO = 0;
    static Matrix4D quadModel;

    static GLuint planeVAO = 0;
    static GLuint planeVBO = 0;
    static GLuint planeEBO = 0;
    static Matrix4D planeModel;

    static GLuint modelVAO = 0;
    static GLuint modelVBO = 0;
    static GLuint modelEBO = 0;
    static GLsizei modelIndexCount = 0;
    static Matrix4D modelModel;

    static vec3 lightPos = {0, 5, 3};
    static vec3 lightDir = {0, -1, 0};
    static vec3 lightDst;
    static vec3 lightUp = {0, 1, 0};
    static mat4 lightView;
    static mat4 lightProjectionPerspective;
    static mat4 lightProjectionOrthogonal;
    static float lightProjNear = 0.1f;
    static float lightProjFar = 50.0f;
    static float lightProjFov = degrees_to_radians(60.0f);

    static DepthBuffer depthBuffer = {0, 0, 0, 0};

    static Shader shader;

    static Shader shader_DBD; // Depth Buffer Debug

    static Shader shader_SM_O_DP; // ShadowMap Ortogonal Depth Pass
    static Shader shader_SM_O_RP; // ShadowMap Ortogonal Render Pass

    static Shader shader_SM_P_DP; // ShadowMap Perspective Depth Pass
    static Shader shader_SM_P_RP; // ShadowMap Perspective Render Pass

    switch (message)
    {

    case WM_INIT_GL_OPTIONS:
    {
        ZeroMemory(&RenderDataSMP, sizeof(ShadowMapPerspectiveRenderData));

        mat4_set_look_at(&view, &viewPos, &viewDst, &viewUp);
        mat4_set_perspective_projection(&projection, 800, 600, projNear, projFar, projFov); // изначально перспектива наугад

        GenQuadMesh(quadVAO, quadVBO);
        mat4_set_ordinary(&quadModel);

        GenPlaneMesh(planeVAO, planeVBO, planeEBO);
        mat4_set_ordinary(&planeModel);

        GenModelMesh("Models/Rabbit.obj", modelVAO, modelVBO, modelEBO, modelIndexCount, true);
        mat4_set_translate(&modelModel, 0, 2, 0);

        // vec3_sum(&lightPos, &lightDir, &lightDst);
        lightDst = {0, 2, 0};
        mat4_set_look_at(&lightView, &lightPos, &lightDst, &lightUp);
        mat4_set_perspective_projection(&lightProjectionPerspective, 1920, 1080, lightProjNear, lightProjFar, lightProjFov);
        mat4_set_ortho_projection_with_aspect(&lightProjectionOrthogonal, -2, 2, -2, 2, 0.1f, 50, 1920, 1080);

        GenDepthFrameBuffer(depthBuffer, 1920, 1080);

        SetupOpenGLServices();

        shader.set_shader_name("Shaders/");
        shader.create_from_file("Shaders/vertex.glsl", GL_VERTEX_SHADER);
        shader.create_from_file("Shaders/fragment.glsl", GL_FRAGMENT_SHADER);
        shader.link_program();
        shader.init_uniforms_and_attribs();
        shader.print_uniforms_and_attribs();
        shader.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader.delete_shader(GL_VERTEX_SHADER);
        shader.delete_shader(GL_FRAGMENT_SHADER);

        shader_DBD.set_shader_name("Shaders/DepthBufferDebug/");
        shader_DBD.create_from_file("Shaders/DepthBufferDebug/vert.glsl", GL_VERTEX_SHADER);
        shader_DBD.create_from_file("Shaders/DepthBufferDebug/frag.glsl", GL_FRAGMENT_SHADER);
        shader_DBD.link_program();
        shader_DBD.init_uniforms_and_attribs();
        shader_DBD.print_uniforms_and_attribs();
        shader_DBD.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_DBD.delete_shader(GL_VERTEX_SHADER);
        shader_DBD.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_O_DP.set_shader_name("Shaders/ShadowMap (orthogonal)/DepthPass");
        shader_SM_O_DP.create_from_file("Shaders/ShadowMap (orthogonal)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_O_DP.create_from_file("Shaders/ShadowMap (orthogonal)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_O_DP.link_program();
        shader_SM_O_DP.init_uniforms_and_attribs();
        shader_SM_O_DP.print_uniforms_and_attribs();
        shader_SM_O_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_O_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_O_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_O_RP.set_shader_name("Shaders/ShadowMap (orthogonal)/RenderPass");
        shader_SM_O_RP.create_from_file("Shaders/ShadowMap (orthogonal)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_O_RP.create_from_file("Shaders/ShadowMap (orthogonal)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_O_RP.link_program();
        shader_SM_O_RP.init_uniforms_and_attribs();
        shader_SM_O_RP.print_uniforms_and_attribs();
        shader_SM_O_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_O_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_O_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_P_DP.set_shader_name("Shaders/ShadowMap (perspective)/DepthPass");
        shader_SM_P_DP.create_from_file("Shaders/ShadowMap (perspective)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_P_DP.create_from_file("Shaders/ShadowMap (perspective)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_P_DP.link_program();
        shader_SM_P_DP.init_uniforms_and_attribs();
        shader_SM_P_DP.print_uniforms_and_attribs();
        shader_SM_P_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_P_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_P_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_P_RP.set_shader_name("Shaders/ShadowMap (perspective)/RenderPass");
        shader_SM_P_RP.create_from_file("Shaders/ShadowMap (perspective)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_P_RP.create_from_file("Shaders/ShadowMap (perspective)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_P_RP.link_program();
        shader_SM_P_RP.init_uniforms_and_attribs();
        shader_SM_P_RP.print_uniforms_and_attribs();
        shader_SM_P_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_P_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_P_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader.use();
        uniform_matrix4f(shader.get_uniform_location("model"), &planeModel);
        uniform_matrix4f(shader.get_uniform_location("view"), &view);
        uniform_matrix4f(shader.get_uniform_location("projection"), &projection);

        shader_DBD.use();
        glUniform1i(shader_DBD.get_uniform_location("depthMap"), 0);

        shader_SM_P_RP.use();
        glUniform1i(shader_SM_P_RP.get_uniform_location("shadowMap"), 0);
        uniform_vec3f(shader_SM_P_RP.get_uniform_location("lightPos"), &lightPos);

        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_PERSPECTIVE, (LPARAM)0);
        SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_ORTHOGONAL, (LPARAM)0);

        return EXIT_SUCCESS;
    }

    case WM_LOAD_MODEL:
    {
        std::string path;
        std::wstring wpath = (WCHAR*)wParam;
        bool CCW = (bool)lParam;

        wchar_to_char(&wpath, &path);

        return GenModelMesh(path, modelVAO, modelVBO, modelEBO, modelIndexCount, CCW);
    }

    case WM_SIZE:
    {
        GetClientRect(hWnd, &client_rect);
        client_width = get_rect_width(client_rect);
        client_height = get_rect_height(client_rect);

        if (glUniformMatrix4fv != nullptr && glUseProgram != nullptr)
        {
            shader.use();
            mat4_set_perspective_projection(&projection, client_width, client_height, projNear, projFar, projFov);
            uniform_matrix4f(shader.get_uniform_location("projection"), &projection);
        }
        else
        {
            mat4_set_ordinary(&projection);
        }

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

                viewPos = pos;
            }
            else if (camera_mode == MOVING)
            {

            }

            shader.use();
            mat4_set_look_at(&view, &viewPos, &viewDst, &viewUp);
            uniform_matrix4f(shader.get_uniform_location("view"), &view);
        }

        return EXIT_SUCCESS;
    }

    case WM_SET_WIREFRAME:
    {
        bool wireframe = (WPARAM)wParam;

        if (wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOW_ALG:
    {
        ShadowAlg newShadowAlg = (ShadowAlg)wParam;

        if (newShadowAlg != shadowAlg)
        {
            switch (newShadowAlg)
            {
                case NO_SHADOW:
                {
                    break;
                }

                case NO_SHADOW_LIGHT:
                {
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL:
                case SHADOW_MAP_ORTHOGONAL_LIGHT:
                case SHADOW_MAP_ORTHOGONAL_DEBUG:
                {
                    RenderDataSMO.depthBuffer = &depthBuffer;
                    RenderDataSMO.client_width = &client_width;
                    RenderDataSMO.client_height = &client_height;
                    RenderDataSMO.shaderDepthPass = &shader_SM_P_DP;
                    RenderDataSMO.shaderRenderPass = &shader_SM_P_RP;
                    RenderDataSMO.shaderDepthDebug = &shader_DBD;
                    RenderDataSMO.view = &view;
                    RenderDataSMO.projection = &projection;
                    RenderDataSMO.lightView = &lightView;
                    RenderDataSMO.lightProjection = &lightProjectionOrthogonal;
                    RenderDataSMO.quadVAO = &quadVAO;
                    RenderDataSMO.planeVAO = &planeVAO;
                    RenderDataSMO.planeModel = &planeModel;
                    RenderDataSMO.modelVAO = &modelVAO;
                    RenderDataSMO.modelIndexCount = &modelIndexCount;
                    RenderDataSMO.modelModel =  &modelModel;
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE:
                case SHADOW_MAP_PERSPECTIVE_LIGHT:
                case SHADOW_MAP_PERSPECTIVE_DEBUG:
                {
                    RenderDataSMP.depthBuffer = &depthBuffer;
                    RenderDataSMP.client_width = &client_width;
                    RenderDataSMP.client_height = &client_height;
                    RenderDataSMP.shaderDepthPass = &shader_SM_P_DP;
                    RenderDataSMP.shaderRenderPass = &shader_SM_P_RP;
                    RenderDataSMP.shaderDepthDebug = &shader_DBD;
                    RenderDataSMP.view = &view;
                    RenderDataSMP.projection = &projection;
                    RenderDataSMP.lightView = &lightView;
                    RenderDataSMP.lightProjection = &lightProjectionPerspective;
                    RenderDataSMP.quadVAO = &quadVAO;
                    RenderDataSMP.planeVAO = &planeVAO;
                    RenderDataSMP.planeModel = &planeModel;
                    RenderDataSMP.modelVAO = &modelVAO;
                    RenderDataSMP.modelIndexCount = &modelIndexCount;
                    RenderDataSMP.modelModel =  &modelModel;
                    break;
                }
                
                default:
                    break;
            }

            shadowAlg = newShadowAlg;
        }

        return EXIT_SUCCESS;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        switch (shadowAlg)
        {
            case NO_SHADOW:
            {
                break;
            }

            case NO_SHADOW_LIGHT:
            {
                break;
            }

            case SHADOW_MAP_ORTHOGONAL:
            {
                ShadowMapOrthogonal(RenderDataSMO);
                break;
            }

            case SHADOW_MAP_ORTHOGONAL_LIGHT:
            {
                break;
            }

            case SHADOW_MAP_ORTHOGONAL_DEBUG:
            {
                ShadowMapOrthogonalDebug(RenderDataSMO);
                break;
            }

            case SHADOW_MAP_PERSPECTIVE:
            {
                ShadowMapPerspective(RenderDataSMP);
                break;
            }

            case SHADOW_MAP_PERSPECTIVE_LIGHT:
            {
                break;
            }

            case SHADOW_MAP_PERSPECTIVE_DEBUG:
            {
                ShadowMapPerspectiveDebug(RenderDataSMP);
                break;
            }

            default:
                break;
        }

        SwapBuffers(hdc);

        EndPaint(hWnd, &ps);
        return EXIT_SUCCESS;
    }

    case WM_DESTROY:
    {
        if (quadVAO) glDeleteVertexArrays(1, &quadVAO);
        if (quadVBO) glDeleteBuffers(1, &quadVBO);

        if (planeVAO) glDeleteVertexArrays(1, &planeVAO);
        if (planeVBO) glDeleteBuffers(1, &planeVBO);
        if (planeEBO) glDeleteBuffers(1, &planeEBO);

        if (modelVAO) glDeleteVertexArrays(1, &modelVAO);
        if (modelVBO) glDeleteBuffers(1, &modelVBO);
        if (modelEBO) glDeleteBuffers(1, &modelEBO);

        if (depthBuffer.Texture) glDeleteTextures(1, &depthBuffer.Texture);
        if (depthBuffer.FBO) glDeleteFramebuffers(1, &depthBuffer.FBO);

        shader.delete_program();
        shader_DBD.delete_program();
        shader_SM_O_DP.delete_program();
        shader_SM_O_RP.delete_program();
        shader_SM_P_DP.delete_program();
        shader_SM_P_RP.delete_program();

        PostQuitMessage(0);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}