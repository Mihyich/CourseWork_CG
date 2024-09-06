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

    if (quadVAO) glDeleteVertexArrays(1, &quadVAO);
    if (quadVBO) glDeleteBuffers(1, &quadVBO);

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

void SetupOpenGLServices()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

bool RebuildBVHTree(
    RayTraceBVHTree& BVH,
    const std::string& modelPath,
    bool CCW,
    const mat4& modelModel,
    const std::string& modelName,
    GLuint& VertexSSBO, GLuint& MatrixSSBO, GLuint& BvhSSBO
)
{
    mat4 m;
    std::vector<vec3> vertices;
    std::vector<vec3> normales;
    std::vector<unsigned int> indeces;
    RayTraceBVHTree newBVH;
    bool rs = true;
    
    mat4_set_ordinary(&m);
    genPlaneMeshVNI(vertices, normales, indeces, 20.f);
    newBVH.addMesh(vertices, normales, indeces, m, "Plane");

    rs = rs && LoadModel(modelPath, vertices, normales, indeces, CCW);
    newBVH.addMesh(vertices, normales, indeces, modelModel, modelName);

    if (rs)
    {
        if (!newBVH.checkLinkRanges())
        {
            printf("!!!\nBVH tree has error linking ranges\n!!!\n");
        }
        
        if (!newBVH.checkCycles())
        {
            printf("!!!\nBVH tree has cycles\n!!!\n");
        }

        if (!newBVH.checkBoundingSpheres())
        {
            printf("!!!\nBVH tree has incorrect bounding spheres\n!!!\n");
        }

        // newBVH.writeBVHTreeToDot("BVHtree.dot");

        BVH = newBVH;
        genRayTraceVertexSSBO(BVH.getVerteces(), VertexSSBO);
        genRayTraceMatrixSSBO(BVH.getMatrices(), MatrixSSBO);
        genRayTraceBvhSSBO(BVH.getBvh(), BvhSSBO);
    }

    return rs;
}

void BuildPresentationBVHTree(
    RayTraceBVHTree& BVH,
    GLuint& VertexSSBO, GLuint& MatrixSSBO, GLuint& BvhSSBO
)
{
    mat4 m;
    vec3 rot;
    vec3 pos;
    vec3 scale = {1, 1, 1};
    std::vector<vec3> vertices;
    std::vector<vec3> normales;
    std::vector<unsigned int> indeces;
    
    mat4_set_ordinary(&m);
    genPlaneMeshVNI(vertices, normales, indeces, 50.f);
    BVH.addMesh(vertices, normales, indeces, m, "Plane");

    LoadModel("Models/monkey.obj", vertices, normales, indeces, true);

    pos = {0, 2, -2};
    rot = {-45, 0, 0};
    mat4_set_TRS_degrees(&m, &rot, &pos, &scale);
    BVH.addMesh(vertices, normales, indeces, m, "monkey1");

    pos = {2, 2, 0};
    rot = {-45, 90, 0};
    mat4_set_TRS_degrees(&m, &rot, &pos, &scale);
    BVH.addMesh(vertices, normales, indeces, m, "monkey2");

    pos = {0, 2, 2};
    rot = {-45, 180, 0};
    mat4_set_TRS_degrees(&m, &rot, &pos, &scale);
    BVH.addMesh(vertices, normales, indeces, m, "monkey3");

    pos = {-2, 2, 0};
    rot = {-45, -90, 0};
    mat4_set_TRS_degrees(&m, &rot, &pos, &scale);
    BVH.addMesh(vertices, normales, indeces, m, "monkey4");

    if (!BVH.checkLinkRanges())
    {
        printf("!!!\nBVH tree has error linking ranges\n!!!\n");
    }
    
    if (!BVH.checkCycles())
    {
        printf("!!!\nBVH tree has cycles\n!!!\n");
    }

    if (!BVH.checkBoundingSpheres())
    {
        printf("!!!\nBVH tree has incorrect bounding spheres\n!!!\n");
    }

    BVH.writeBVHTreeToDot("BVHtree.dot");

    genRayTraceVertexSSBO(BVH.getVerteces(), VertexSSBO);
    genRayTraceMatrixSSBO(BVH.getMatrices(), MatrixSSBO);
    genRayTraceBvhSSBO(BVH.getBvh(), BvhSSBO);
}

LRESULT RenderWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT client_rect = {0, 0, 0, 0};
    static int client_width = 0;
    static int client_height = 0;

    static WinApiMouse mouse;
    static vec2 mouse_delta = {0, 0};

    static ShadowAlg shadowAlg = NO_SHADOW_LIGHT;

    static ShadowMapRenderData RenderDataSM;
    static GLfloat shadowBias = 0.005f;
    static GLfloat pcfRadius = 1.5f;
    static GLfloat expK = 1.f;

    static RayTracingRenderData RenderDataRT;

    static CameraMode camera_mode = ORBITTING;
    static bool camera_moved = false;
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

    static std::string modelPath = "Models/Monkey.obj";
    static std::string modelName = "Monkey";
    static GLuint modelVAO = 0;
    static GLuint modelVBO = 0;
    static GLuint modelEBO = 0;
    static GLsizei modelIndexCount = 0;
    static Matrix4D modelModel;

    static GLuint lightUBO = 0;
    static Light light =
    {
        // Кратность 16 =========================================================================
        { 0.f, 5.f, 3.f }, // Позиция (12 байт)
        0.f,               // Выравнивание для GLSL vec3 (еще 4 байта)
        // Кратность 16 =========================================================================
        { 0.f, -1.f, -1.f }, // Направление (12 байт)
        0.f,               // Выравнивание для GLSL vec3 (еще 4 байта)
        // Кратность 16 =========================================================================
        { 1.f, 1.f, 1.f }, // Цвет (12 байт)
        0.f,               // Выравнивание для GLSL vec3 (еще 4 байта)
        // Кратность 16 =========================================================================
        20.f,              // Радиус действия (4 байта)
        2.f,               // Интенсивность (4 байта)
        degrees_to_radians(30), // Угол (в радианах) внутреннего конуса (4 байта)
        degrees_to_radians(45), // Угол (в радианах) внешнего конуса (4 байта)
        // Кратность 16 =========================================================================
        0,                 // Тип источника света: 0 - PointLight; 1 - SpotLight (4 байта)
        0.f,               // Дополнительные паддинги,
        0.f,               // чтобы сделать размер структуры
        0.f                // кратным 16 (3 * 4 = 12 байт)
        // Кратность 16 =========================================================================
    };

    static mat4 lightView;
    static mat4 lightProjectionPerspective;
    static mat4 lightProjectionOrthogonal;
    static float lightProjLeft = -2.f;
    static float lightProjRight = 2.f;
    static float lightProjBottom = -2.f;
    static float lightProjTop = 2.f;
    static float lightProjNear = 0.1f;
    static float lightProjFar = 50.0f;
    static float lightProjFov = degrees_to_radians(60.0f);

    static DepthBuffer depthBuffer = {0, 0, 0, 0};
    static DepthBufferExp depthBufferExp = {0, 0, 0, 0, 0};

    static RayTraceBVHTree BVH;
    static GLuint VertexSSBO = 0;
    static GLuint MatrixSSBO = 0;
    static GLuint BvhSSBO = 0;
    static GLuint rayTracedTexture = 0;
    static GLsizei rayTracingTextureWidth = 1920;
    static GLsizei rayTracingTextureHeight = 1080;

    static int shadowRayCount = 9;

    static Shader shader;

    static Shader shader_DBD; // Depth Buffer Debug

    static Shader shader_SM_O_DP; // ShadowMap Orthogonal Depth Pass
    static Shader shader_SM_O_RP; // ShadowMap Orthogonal Render Pass

    static Shader shader_SM_P_DP; // ShadowMap Perspective Depth Pass
    static Shader shader_SM_P_RP; // ShadowMap Perspective Render Pass

    static Shader shader_SM_PCF_O_DP; // ShadowMap (PCF) Orthogonal Depth Pass
    static Shader shader_SM_PCF_O_RP; // ShadowMap (PCF) Orthogonal Render Pass

    static Shader shader_SM_PCF_P_DP; // ShadowMap (PCF) Perspective Depth Pass
    static Shader shader_SM_PCF_P_RP; // ShadowMap (PCF) Perspective Render Pass

    static Shader shader_SM_ESM_O_DP; // ShadowMap (ESM) Orthogonal Depth Pass
    static Shader shader_SM_ESM_O_RP; // ShadowMap (ESM) Orthogonal Render Pass

    static Shader shader_SM_ESM_P_DP; // ShadowMap (ESM) Perspective Depth Pass
    static Shader shader_SM_ESM_P_RP; // ShadowMap (ESM) Perspective Render Pass

    static Shader shader_SM_VSM_O_DP; // ShadowMap (VSM) Orthogonal Depth Pass
    static Shader shader_SM_VSM_O_RP; // ShadowMap (VSM) Orthogonal Render Pass

    static Shader shader_SM_VSM_P_DP; // ShadowMap (VSM) Perspective Depth Pass
    static Shader shader_SM_VSM_P_RP; // ShadowMap (VSM) Perspective Render Pass

    static Shader shader_SM_NOISE_O_DP; // ShadowMap (Noise) Orthogonal Depth Pass
    static Shader shader_SM_NOISE_O_RP; // ShadowMap (Noise) Orthogonal Render Pass

    static Shader shader_SM_NOISE_P_DP; // ShadowMap (Noise) Perspective Depth Pass
    static Shader shader_SM_NOISE_P_RP; // ShadowMap (Noise) Perspective Render Pass

    static Shader shader_SM_PCSS_O_DP; // ShadowMap (PCSS) Orthogonal Depth Pass
    static Shader shader_SM_PCSS_O_RP; // ShadowMap (PCSS) Orthogonal Render Pass

    static Shader shader_SM_PCSS_P_DP; // ShadowMap (PCSS) Perspective Depth Pass
    static Shader shader_SM_PCSS_P_RP; // ShadowMap (PCSS) Perspective Render Pass

    static Shader shader_RT_BVH; // RayTracing BVH Debug

    static Shader shader_IO; // ImageOut

    static Shader shader_RT_HARD; // RayTracing Hard
    static Shader shader_RT_P_SOFT; // RayTracing Soft Perspective

    static bool ForbidDrawing = false;

    switch (message)
    {
    case WM_INIT_GL_OPTIONS:
    {
        mat4_set_look_at(&view, &viewPos, &viewDst, &viewUp);
        mat4_set_perspective_projection(&projection, 800, 600, projNear, projFar, projFov); // изначально перспектива наугад

        GenQuadMesh(quadVAO, quadVBO);
        mat4_set_ordinary(&quadModel);

        GenPlaneMesh(planeVAO, planeVBO, planeEBO, 40.f);
        mat4_set_ordinary(&planeModel);

        GenModelMesh(modelPath, modelVAO, modelVBO, modelEBO, modelIndexCount, true);
        mat4_set_translate(&modelModel, 0, 2, 0);

        genLightUBO(light, lightUBO);

        mat4_set_look_to(&lightView, &light.position, &light.direction, &viewUp);
        mat4_set_perspective_projection(&lightProjectionPerspective, 1920, 1080, lightProjNear, lightProjFar, lightProjFov);
        mat4_set_ortho_projection_with_aspect(
            &lightProjectionOrthogonal, 
            lightProjLeft, lightProjRight,
            lightProjBottom, lightProjTop,
            lightProjNear, lightProjFar,
            1920, 1080);

        GenDepthFrameBuffer(depthBuffer, 1920, 1080);
        GenExpDepthFrameBuffer(depthBufferExp, 1920, 1080);

        // Вау-эффект, для первого RayTracing дерева, потом автоматически дерево перестроится
        // по желанию пользователя загрузить новую модель
        // BuildPresentationBVHTree(BVH, VertexSSBO, MatrixSSBO, BvhSSBO);
        RebuildBVHTree(BVH, modelPath, true, modelModel, modelName, VertexSSBO, MatrixSSBO, BvhSSBO);
        genRayTracedTexture(rayTracedTexture, rayTracingTextureWidth, rayTracingTextureHeight);

        SetupOpenGLServices();

        shader.set_shader_name("Shaders/");
        shader.create_from_file("Shaders/vertex.glsl", GL_VERTEX_SHADER);
        shader.create_from_file("Shaders/fragment.glsl", GL_FRAGMENT_SHADER);
        shader.link_program();
        shader.init_uniforms_blocks_attribs();
        shader.print_uniforms_blocks_attribs();
        shader.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader.delete_shader(GL_VERTEX_SHADER);
        shader.delete_shader(GL_FRAGMENT_SHADER);

        shader_DBD.set_shader_name("Shaders/DepthBufferDebug/");
        shader_DBD.create_from_file("Shaders/DepthBufferDebug/vert.glsl", GL_VERTEX_SHADER);
        shader_DBD.create_from_file("Shaders/DepthBufferDebug/frag.glsl", GL_FRAGMENT_SHADER);
        shader_DBD.link_program();
        shader_DBD.init_uniforms_blocks_attribs();
        shader_DBD.print_uniforms_blocks_attribs();
        shader_DBD.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_DBD.delete_shader(GL_VERTEX_SHADER);
        shader_DBD.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_O_DP.set_shader_name("Shaders/ShadowMap (orthogonal)/DepthPass");
        shader_SM_O_DP.create_from_file("Shaders/ShadowMap (orthogonal)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_O_DP.create_from_file("Shaders/ShadowMap (orthogonal)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_O_DP.link_program();
        shader_SM_O_DP.init_uniforms_blocks_attribs();
        shader_SM_O_DP.print_uniforms_blocks_attribs();
        shader_SM_O_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_O_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_O_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_O_RP.set_shader_name("Shaders/ShadowMap (orthogonal)/RenderPass");
        shader_SM_O_RP.create_from_file("Shaders/ShadowMap (orthogonal)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_O_RP.create_from_file("Shaders/ShadowMap (orthogonal)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_O_RP.link_program();
        shader_SM_O_RP.init_uniforms_blocks_attribs();
        shader_SM_O_RP.print_uniforms_blocks_attribs();
        shader_SM_O_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_O_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_O_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_P_DP.set_shader_name("Shaders/ShadowMap (perspective)/DepthPass");
        shader_SM_P_DP.create_from_file("Shaders/ShadowMap (perspective)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_P_DP.create_from_file("Shaders/ShadowMap (perspective)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_P_DP.link_program();
        shader_SM_P_DP.init_uniforms_blocks_attribs();
        shader_SM_P_DP.print_uniforms_blocks_attribs();
        shader_SM_P_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_P_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_P_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_P_RP.set_shader_name("Shaders/ShadowMap (perspective)/RenderPass");
        shader_SM_P_RP.create_from_file("Shaders/ShadowMap (perspective)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_P_RP.create_from_file("Shaders/ShadowMap (perspective)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_P_RP.link_program();
        shader_SM_P_RP.init_uniforms_blocks_attribs();
        shader_SM_P_RP.print_uniforms_blocks_attribs();
        shader_SM_P_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_P_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_P_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_PCF_O_DP.set_shader_name("Shaders/ShadowMapPCF (orthogonal)/DepthPass");
        shader_SM_PCF_O_DP.create_from_file("Shaders/ShadowMapPCF (orthogonal)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_PCF_O_DP.create_from_file("Shaders/ShadowMapPCF (orthogonal)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_PCF_O_DP.link_program();
        shader_SM_PCF_O_DP.init_uniforms_blocks_attribs();
        shader_SM_PCF_O_DP.print_uniforms_blocks_attribs();
        shader_SM_PCF_O_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_PCF_O_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_PCF_O_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_PCF_O_RP.set_shader_name("Shaders/ShadowMapPCF (orthogonal)/RenderPass");
        shader_SM_PCF_O_RP.create_from_file("Shaders/ShadowMapPCF (orthogonal)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_PCF_O_RP.create_from_file("Shaders/ShadowMapPCF (orthogonal)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_PCF_O_RP.link_program();
        shader_SM_PCF_O_RP.init_uniforms_blocks_attribs();
        shader_SM_PCF_O_RP.print_uniforms_blocks_attribs();
        shader_SM_PCF_O_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_PCF_O_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_PCF_O_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_PCF_P_DP.set_shader_name("Shaders/ShadowMapPCF (perspective)/DepthPass");
        shader_SM_PCF_P_DP.create_from_file("Shaders/ShadowMapPCF (perspective)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_PCF_P_DP.create_from_file("Shaders/ShadowMapPCF (perspective)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_PCF_P_DP.link_program();
        shader_SM_PCF_P_DP.init_uniforms_blocks_attribs();
        shader_SM_PCF_P_DP.print_uniforms_blocks_attribs();
        shader_SM_PCF_P_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_PCF_P_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_PCF_P_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_PCF_P_RP.set_shader_name("Shaders/ShadowMapPCF (perspective)/RenderPass");
        shader_SM_PCF_P_RP.create_from_file("Shaders/ShadowMapPCF (perspective)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_PCF_P_RP.create_from_file("Shaders/ShadowMapPCF (perspective)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_PCF_P_RP.link_program();
        shader_SM_PCF_P_RP.init_uniforms_blocks_attribs();
        shader_SM_PCF_P_RP.print_uniforms_blocks_attribs();
        shader_SM_PCF_P_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_PCF_P_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_PCF_P_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_ESM_O_DP.set_shader_name("Shaders/ShadowMapESM (orthogonal)/DepthPass");
        shader_SM_ESM_O_DP.create_from_file("Shaders/ShadowMapESM (orthogonal)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_ESM_O_DP.create_from_file("Shaders/ShadowMapESM (orthogonal)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_ESM_O_DP.link_program();
        shader_SM_ESM_O_DP.init_uniforms_blocks_attribs();
        shader_SM_ESM_O_DP.print_uniforms_blocks_attribs();
        shader_SM_ESM_O_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_ESM_O_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_ESM_O_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_ESM_O_RP.set_shader_name("Shaders/ShadowMapESM (orthogonal)/RenderPass");
        shader_SM_ESM_O_RP.create_from_file("Shaders/ShadowMapESM (orthogonal)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_ESM_O_RP.create_from_file("Shaders/ShadowMapESM (orthogonal)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_ESM_O_RP.link_program();
        shader_SM_ESM_O_RP.init_uniforms_blocks_attribs();
        shader_SM_ESM_O_RP.print_uniforms_blocks_attribs();
        shader_SM_ESM_O_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_ESM_O_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_ESM_O_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_ESM_P_DP.set_shader_name("Shaders/ShadowMapESM (perspective)/DepthPass");
        shader_SM_ESM_P_DP.create_from_file("Shaders/ShadowMapESM (perspective)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_ESM_P_DP.create_from_file("Shaders/ShadowMapESM (perspective)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_ESM_P_DP.link_program();
        shader_SM_ESM_P_DP.init_uniforms_blocks_attribs();
        shader_SM_ESM_P_DP.print_uniforms_blocks_attribs();
        shader_SM_ESM_P_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_ESM_P_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_ESM_P_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_ESM_P_RP.set_shader_name("Shaders/ShadowMapESM (perspective)/RenderPass");
        shader_SM_ESM_P_RP.create_from_file("Shaders/ShadowMapESM (perspective)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_ESM_P_RP.create_from_file("Shaders/ShadowMapESM (perspective)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_ESM_P_RP.link_program();
        shader_SM_ESM_P_RP.init_uniforms_blocks_attribs();
        shader_SM_ESM_P_RP.print_uniforms_blocks_attribs();
        shader_SM_ESM_P_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_ESM_P_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_ESM_P_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_VSM_O_DP.set_shader_name("Shaders/ShadowMapVSM (orthogonal)/DepthPass");
        shader_SM_VSM_O_DP.create_from_file("Shaders/ShadowMapVSM (orthogonal)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_VSM_O_DP.create_from_file("Shaders/ShadowMapVSM (orthogonal)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_VSM_O_DP.link_program();
        shader_SM_VSM_O_DP.init_uniforms_blocks_attribs();
        shader_SM_VSM_O_DP.print_uniforms_blocks_attribs();
        shader_SM_VSM_O_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_VSM_O_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_VSM_O_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_VSM_O_RP.set_shader_name("Shaders/ShadowMapVSM (orthogonal)/RenderPass");
        shader_SM_VSM_O_RP.create_from_file("Shaders/ShadowMapVSM (orthogonal)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_VSM_O_RP.create_from_file("Shaders/ShadowMapVSM (orthogonal)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_VSM_O_RP.link_program();
        shader_SM_VSM_O_RP.init_uniforms_blocks_attribs();
        shader_SM_VSM_O_RP.print_uniforms_blocks_attribs();
        shader_SM_VSM_O_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_VSM_O_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_VSM_O_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_VSM_P_DP.set_shader_name("Shaders/ShadowMapVSM (perspective)/DepthPass");
        shader_SM_VSM_P_DP.create_from_file("Shaders/ShadowMapVSM (perspective)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_VSM_P_DP.create_from_file("Shaders/ShadowMapVSM (perspective)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_VSM_P_DP.link_program();
        shader_SM_VSM_P_DP.init_uniforms_blocks_attribs();
        shader_SM_VSM_P_DP.print_uniforms_blocks_attribs();
        shader_SM_VSM_P_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_VSM_P_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_VSM_P_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_VSM_P_RP.set_shader_name("Shaders/ShadowMapVSM (perspective)/RenderPass");
        shader_SM_VSM_P_RP.create_from_file("Shaders/ShadowMapVSM (perspective)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_VSM_P_RP.create_from_file("Shaders/ShadowMapVSM (perspective)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_VSM_P_RP.link_program();
        shader_SM_VSM_P_RP.init_uniforms_blocks_attribs();
        shader_SM_VSM_P_RP.print_uniforms_blocks_attribs();
        shader_SM_VSM_P_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_VSM_P_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_VSM_P_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_NOISE_O_DP.set_shader_name("Shaders/ShadowMapNoise (orthogonal)/DepthPass");
        shader_SM_NOISE_O_DP.create_from_file("Shaders/ShadowMapNoise (orthogonal)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_NOISE_O_DP.create_from_file("Shaders/ShadowMapNoise (orthogonal)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_NOISE_O_DP.link_program();
        shader_SM_NOISE_O_DP.init_uniforms_blocks_attribs();
        shader_SM_NOISE_O_DP.print_uniforms_blocks_attribs();
        shader_SM_NOISE_O_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_NOISE_O_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_NOISE_O_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_NOISE_O_RP.set_shader_name("Shaders/ShadowMapNoise (orthogonal)/RenderPass");
        shader_SM_NOISE_O_RP.create_from_file("Shaders/ShadowMapNoise (orthogonal)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_NOISE_O_RP.create_from_file("Shaders/ShadowMapNoise (orthogonal)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_NOISE_O_RP.link_program();
        shader_SM_NOISE_O_RP.init_uniforms_blocks_attribs();
        shader_SM_NOISE_O_RP.print_uniforms_blocks_attribs();
        shader_SM_NOISE_O_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_NOISE_O_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_NOISE_O_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_NOISE_P_DP.set_shader_name("Shaders/ShadowMapNoise (perspective)/DepthPass");
        shader_SM_NOISE_P_DP.create_from_file("Shaders/ShadowMapNoise (perspective)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_NOISE_P_DP.create_from_file("Shaders/ShadowMapNoise (perspective)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_NOISE_P_DP.link_program();
        shader_SM_NOISE_P_DP.init_uniforms_blocks_attribs();
        shader_SM_NOISE_P_DP.print_uniforms_blocks_attribs();
        shader_SM_NOISE_P_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_NOISE_P_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_NOISE_P_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_NOISE_P_RP.set_shader_name("Shaders/ShadowMapNoise (perspective)/RenderPass");
        shader_SM_NOISE_P_RP.create_from_file("Shaders/ShadowMapNoise (perspective)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_NOISE_P_RP.create_from_file("Shaders/ShadowMapNoise (perspective)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_NOISE_P_RP.link_program();
        shader_SM_NOISE_P_RP.init_uniforms_blocks_attribs();
        shader_SM_NOISE_P_RP.print_uniforms_blocks_attribs();
        shader_SM_NOISE_P_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_NOISE_P_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_NOISE_P_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_PCSS_P_DP.set_shader_name("Shaders/ShadowMapPCSS (perspective)/DepthPass");
        shader_SM_PCSS_P_DP.create_from_file("Shaders/ShadowMapPCSS (perspective)/DepthPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_PCSS_P_DP.create_from_file("Shaders/ShadowMapPCSS (perspective)/DepthPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_PCSS_P_DP.link_program();
        shader_SM_PCSS_P_DP.init_uniforms_blocks_attribs();
        shader_SM_PCSS_P_DP.print_uniforms_blocks_attribs();
        shader_SM_PCSS_P_DP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_PCSS_P_DP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_PCSS_P_DP.delete_shader(GL_FRAGMENT_SHADER);

        shader_SM_PCSS_P_RP.set_shader_name("Shaders/ShadowMapPCSS (perspective)/RenderPass");
        shader_SM_PCSS_P_RP.create_from_file("Shaders/ShadowMapPCSS (perspective)/RenderPass/vert.glsl", GL_VERTEX_SHADER);
        shader_SM_PCSS_P_RP.create_from_file("Shaders/ShadowMapPCSS (perspective)/RenderPass/frag.glsl", GL_FRAGMENT_SHADER);
        shader_SM_PCSS_P_RP.link_program();
        shader_SM_PCSS_P_RP.init_uniforms_blocks_attribs();
        shader_SM_PCSS_P_RP.print_uniforms_blocks_attribs();
        shader_SM_PCSS_P_RP.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_SM_PCSS_P_RP.delete_shader(GL_VERTEX_SHADER);
        shader_SM_PCSS_P_RP.delete_shader(GL_FRAGMENT_SHADER);

        shader_RT_BVH.set_shader_name("Shaders/RayTraceBvhDebug");
        shader_RT_BVH.create_from_file("Shaders/RayTraceBvhDebug/vert.glsl", GL_VERTEX_SHADER);
        shader_RT_BVH.create_from_file("Shaders/RayTraceBvhDebug/geom.glsl", GL_GEOMETRY_SHADER);
        shader_RT_BVH.create_from_file("Shaders/RayTraceBvhDebug/frag.glsl", GL_FRAGMENT_SHADER);
        shader_RT_BVH.link_program();
        shader_RT_BVH.init_uniforms_blocks_attribs();
        shader_RT_BVH.print_uniforms_blocks_attribs();
        shader_RT_BVH.report(REPORT_VS | REPORT_GS | REPORT_FS | REPORT_PROG);
        shader_RT_BVH.delete_shader(GL_VERTEX_SHADER);
        shader_RT_BVH.delete_shader(GL_GEOMETRY_SHADER);
        shader_RT_BVH.delete_shader(GL_FRAGMENT_SHADER);

        shader_IO.set_shader_name("Shaders/ImageOut");
        shader_IO.create_from_file("Shaders/ImageOut/vert.glsl", GL_VERTEX_SHADER);
        shader_IO.create_from_file("Shaders/ImageOut/frag.glsl", GL_FRAGMENT_SHADER);
        shader_IO.link_program();
        shader_IO.init_uniforms_blocks_attribs();
        shader_IO.print_uniforms_blocks_attribs();
        shader_IO.report(REPORT_VS | REPORT_FS | REPORT_PROG);
        shader_IO.delete_shader(GL_VERTEX_SHADER);
        shader_IO.delete_shader(GL_FRAGMENT_SHADER);

        shader_RT_HARD.set_shader_name("Shaders/RayTraceHard (perspective)");
        shader_RT_HARD.create_from_file("Shaders/RayTraceHard (perspective)/comp.glsl", GL_COMPUTE_SHADER);
        shader_RT_HARD.link_program();
        shader_RT_HARD.init_uniforms_blocks_attribs();
        shader_RT_HARD.print_uniforms_blocks_attribs();
        shader_RT_HARD.report(REPORT_CS | REPORT_PROG);
        shader_RT_HARD.delete_shader(GL_COMPUTE_SHADER);

        shader_RT_P_SOFT.set_shader_name("Shaders/RayTraceSoft (perspective)");
        shader_RT_P_SOFT.create_from_file("Shaders/RayTraceSoft (perspective)/TracingPath/comp.glsl", GL_COMPUTE_SHADER);
        shader_RT_P_SOFT.link_program();
        shader_RT_P_SOFT.init_uniforms_blocks_attribs();
        shader_RT_P_SOFT.print_uniforms_blocks_attribs();
        shader_RT_P_SOFT.report(REPORT_CS | REPORT_PROG);
        shader_RT_P_SOFT.delete_shader(GL_COMPUTE_SHADER);

        shader.use();
        uniform_matrix4f(shader.get_uniform_location("model"), &planeModel);
        uniform_matrix4f(shader.get_uniform_location("view"), &view);
        uniform_matrix4f(shader.get_uniform_location("projection"), &projection);

        shader_DBD.use();
        glUniform1i(shader_DBD.get_uniform_location("depthMap"), 0);

        shader_SM_O_RP.use();
        glUniform1i(shader_SM_P_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_P_RP.use();
        glUniform1i(shader_SM_P_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_PCF_O_RP.use();
        glUniform1i(shader_SM_PCF_O_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_PCF_P_RP.use();
        glUniform1i(shader_SM_PCF_P_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_ESM_O_RP.use();
        glUniform1i(shader_SM_ESM_O_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_ESM_P_RP.use();
        glUniform1i(shader_SM_ESM_P_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_VSM_O_RP.use();
        glUniform1i(shader_SM_VSM_O_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_VSM_P_RP.use();
        glUniform1i(shader_SM_VSM_P_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_NOISE_O_RP.use();
        glUniform1i(shader_SM_NOISE_P_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_NOISE_P_RP.use();
        glUniform1i(shader_SM_NOISE_P_RP.get_uniform_location("shadowMap"), 0);

        shader_SM_PCSS_P_RP.use();
        glUniform1i(shader_SM_PCSS_P_RP.get_uniform_location("shadowMap"), 0);

        shader_IO.use();
        glUniform1i(shader_IO.get_uniform_location("colorImage"), 0);

        // Подключить UBO буфер ко всем шейдером его поддерживающих
        GLuint blockIndex;
        GLuint ProgrammId;

        ProgrammId = shader_SM_O_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_P_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_PCF_O_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_PCF_P_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_ESM_O_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_ESM_P_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_VSM_O_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_VSM_P_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_NOISE_O_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_NOISE_P_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_SM_PCSS_P_RP.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_RT_HARD.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        ProgrammId = shader_RT_P_SOFT.getProgramId();
        blockIndex = glGetUniformBlockIndex(ProgrammId, "Lighting");
        glUniformBlockBinding(ProgrammId, blockIndex, 0);

        glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightUBO);
        glBindBufferRange(GL_UNIFORM_BUFFER, 0, lightUBO, 0, sizeof(Light));

        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_PERSPECTIVE, (LPARAM)0);
        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_ORTHOGONAL, (LPARAM)0);
        SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_PERSPECTIVE_PCF, (LPARAM)0);
        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_ORTHOGONAL_PCF, (LPARAM)0);
        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_PERSPECTIVE_ESM, (LPARAM)0);
        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_ORTHOGONAL_ESM, (LPARAM)0);
        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_PERSPECTIVE_VSM, (LPARAM)0);
        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)SHADOW_MAP_ORTHOGONAL_VSM, (LPARAM)0);

        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)RAY_TRACING_DEBUG, (LPARAM)0);
        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)RAY_TRACING_HARD_PERSPECTIVE, (LPARAM)0);
        // SendMessage(hWnd, WM_SET_SHADOW_ALG, (WPARAM)RAY_TRACING_SOFT_PERSPECTIVE, (LPARAM)0);

        std::cout << sizeof(Light) << std::endl;
        std::cout << alignof(Light) << std::endl;

        return EXIT_SUCCESS;
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

        if (camera_mode == ORBITTING)
            camera_moved = false;

        return EXIT_SUCCESS;
    }

    case WM_MOUSEMOVE:
    {
        mouse.move();

        mouse_delta.x = (float)mouse.l_delta_pos.x;
        mouse_delta.y = (float)mouse.l_delta_pos.y;

        if (mouse.l_tracking && (mouse_delta.x != 0 || mouse_delta.y != 0))
        {
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

            camera_moved = true;

            shader.use();
            mat4_set_look_at(&view, &viewPos, &viewDst, &viewUp);
            uniform_matrix4f(shader.get_uniform_location("view"), &view);
        }

        return EXIT_SUCCESS;
    }

    case WM_LOAD_MODEL:
    {
        ForbidDrawing = true;
        std::string path;
        std::wstring wpath = (WCHAR*)wParam;
        bool CCW = (bool)lParam;
        bool rs;

        wchar_to_char(&wpath, &path);
        rs = GenModelMesh(path, modelVAO, modelVBO, modelEBO, modelIndexCount, CCW);
        rs = rs && RebuildBVHTree(BVH, path, CCW, modelModel, modelName, VertexSSBO, MatrixSSBO, BvhSSBO);

        // Обновить этот важный параметр (очень-очень)
        if (shadowAlg == RAY_TRACING_DEBUG) RenderDataRT.debug.nodeCount = (int)BVH.getBvh().size();

        // Пока что грубый способ
        glFlush();
        glFinish();
        
        ForbidDrawing = false;
        return rs;
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
                case SHADOW_MAP_ORTHOGONAL_DEBUG:
                {
                    RenderDataSM.main.depthBuffer = &depthBuffer;
                    RenderDataSM.main.client_width = &client_width;
                    RenderDataSM.main.client_height = &client_height;
                    RenderDataSM.main.shaderDepthPass = &shader_SM_O_DP;
                    RenderDataSM.main.shaderRenderPass = &shader_SM_O_RP;
                    RenderDataSM.main.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.main.view = &view;
                    RenderDataSM.main.projection = &projection;
                    RenderDataSM.main.lightView = &lightView;
                    RenderDataSM.main.lightProjection = &lightProjectionOrthogonal;
                    RenderDataSM.main.shadowBias = &shadowBias;
                    RenderDataSM.main.quadVAO = &quadVAO;
                    RenderDataSM.main.planeVAO = &planeVAO;
                    RenderDataSM.main.planeModel = &planeModel;
                    RenderDataSM.main.modelVAO = &modelVAO;
                    RenderDataSM.main.modelIndexCount = &modelIndexCount;
                    RenderDataSM.main.modelModel = &modelModel;
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE:
                case SHADOW_MAP_PERSPECTIVE_DEBUG:
                {
                    RenderDataSM.main.depthBuffer = &depthBuffer;
                    RenderDataSM.main.client_width = &client_width;
                    RenderDataSM.main.client_height = &client_height;
                    RenderDataSM.main.shaderDepthPass = &shader_SM_P_DP;
                    RenderDataSM.main.shaderRenderPass = &shader_SM_P_RP;
                    RenderDataSM.main.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.main.view = &view;
                    RenderDataSM.main.projection = &projection;
                    RenderDataSM.main.lightView = &lightView;
                    RenderDataSM.main.lightProjection = &lightProjectionPerspective;
                    RenderDataSM.main.shadowBias = &shadowBias;
                    RenderDataSM.main.quadVAO = &quadVAO;
                    RenderDataSM.main.planeVAO = &planeVAO;
                    RenderDataSM.main.planeModel = &planeModel;
                    RenderDataSM.main.modelVAO = &modelVAO;
                    RenderDataSM.main.modelIndexCount = &modelIndexCount;
                    RenderDataSM.main.modelModel = &modelModel;
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_PCF:
                case SHADOW_MAP_ORTHOGONAL_PCF_DEBUG:
                {
                    RenderDataSM.pcf.depthBuffer = &depthBuffer;
                    RenderDataSM.pcf.client_width = &client_width;
                    RenderDataSM.pcf.client_height = &client_height;
                    RenderDataSM.pcf.shaderDepthPass = &shader_SM_PCF_O_DP;
                    RenderDataSM.pcf.shaderRenderPass = &shader_SM_PCF_O_RP;
                    RenderDataSM.pcf.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.pcf.view = &view;
                    RenderDataSM.pcf.projection = &projection;
                    RenderDataSM.pcf.lightView = &lightView;
                    RenderDataSM.pcf.lightProjection = &lightProjectionOrthogonal;
                    RenderDataSM.pcf.shadowBias = &shadowBias;
                    RenderDataSM.pcf.pcfRadius = &pcfRadius;
                    RenderDataSM.pcf.quadVAO = &quadVAO;
                    RenderDataSM.pcf.planeVAO = &planeVAO;
                    RenderDataSM.pcf.planeModel = &planeModel;
                    RenderDataSM.pcf.modelVAO = &modelVAO;
                    RenderDataSM.pcf.modelIndexCount = &modelIndexCount;
                    RenderDataSM.pcf.modelModel = &modelModel;
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_PCF:
                case SHADOW_MAP_PERSPECTIVE_PCF_DEBUG:
                {
                    RenderDataSM.pcf.depthBuffer = &depthBuffer;
                    RenderDataSM.pcf.client_width = &client_width;
                    RenderDataSM.pcf.client_height = &client_height;
                    RenderDataSM.pcf.shaderDepthPass = &shader_SM_PCF_P_DP;
                    RenderDataSM.pcf.shaderRenderPass = &shader_SM_PCF_P_RP;
                    RenderDataSM.pcf.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.pcf.view = &view;
                    RenderDataSM.pcf.projection = &projection;
                    RenderDataSM.pcf.lightView = &lightView;
                    RenderDataSM.pcf.lightProjection = &lightProjectionPerspective;
                    RenderDataSM.pcf.shadowBias = &shadowBias;
                    RenderDataSM.pcf.pcfRadius = &pcfRadius;
                    RenderDataSM.pcf.quadVAO = &quadVAO;
                    RenderDataSM.pcf.planeVAO = &planeVAO;
                    RenderDataSM.pcf.planeModel = &planeModel;
                    RenderDataSM.pcf.modelVAO = &modelVAO;
                    RenderDataSM.pcf.modelIndexCount = &modelIndexCount;
                    RenderDataSM.pcf.modelModel = &modelModel;
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_NOISE:
                case SHADOW_MAP_ORTHOGONAL_NOISE_DEBUG:
                {
                    RenderDataSM.noise.depthBuffer = &depthBuffer;
                    RenderDataSM.noise.client_width = &client_width;
                    RenderDataSM.noise.client_height = &client_height;
                    RenderDataSM.noise.shaderDepthPass = &shader_SM_NOISE_O_DP;
                    RenderDataSM.noise.shaderRenderPass = &shader_SM_NOISE_O_RP;
                    RenderDataSM.noise.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.noise.view = &view;
                    RenderDataSM.noise.projection = &projection;
                    RenderDataSM.noise.lightView = &lightView;
                    RenderDataSM.noise.lightProjection = &lightProjectionOrthogonal;
                    RenderDataSM.noise.shadowBias = &shadowBias;
                    RenderDataSM.noise.pcfRadius = &pcfRadius;
                    RenderDataSM.noise.quadVAO = &quadVAO;
                    RenderDataSM.noise.planeVAO = &planeVAO;
                    RenderDataSM.noise.planeModel = &planeModel;
                    RenderDataSM.noise.modelVAO = &modelVAO;
                    RenderDataSM.noise.modelIndexCount = &modelIndexCount;
                    RenderDataSM.noise.modelModel = &modelModel;
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_NOISE:
                case SHADOW_MAP_PERSPECTIVE_NOISE_DEBUG:
                {
                    RenderDataSM.noise.depthBuffer = &depthBuffer;
                    RenderDataSM.noise.client_width = &client_width;
                    RenderDataSM.noise.client_height = &client_height;
                    RenderDataSM.noise.shaderDepthPass = &shader_SM_NOISE_P_DP;
                    RenderDataSM.noise.shaderRenderPass = &shader_SM_NOISE_P_RP;
                    RenderDataSM.noise.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.noise.view = &view;
                    RenderDataSM.noise.projection = &projection;
                    RenderDataSM.noise.lightView = &lightView;
                    RenderDataSM.noise.lightProjection = &lightProjectionPerspective;
                    RenderDataSM.noise.shadowBias = &shadowBias;
                    RenderDataSM.noise.pcfRadius = &pcfRadius;
                    RenderDataSM.noise.quadVAO = &quadVAO;
                    RenderDataSM.noise.planeVAO = &planeVAO;
                    RenderDataSM.noise.planeModel = &planeModel;
                    RenderDataSM.noise.modelVAO = &modelVAO;
                    RenderDataSM.noise.modelIndexCount = &modelIndexCount;
                    RenderDataSM.noise.modelModel = &modelModel;
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_PCSS:
                case SHADOW_MAP_ORTHOGONAL_PCSS_DEBUG:
                {
                    RenderDataSM.pcss.depthBuffer = &depthBuffer;
                    RenderDataSM.pcss.client_width = &client_width;
                    RenderDataSM.pcss.client_height = &client_height;
                    // RenderDataSM.pcss.shaderDepthPass = &shader_SM_PCSS_O_DP;
                    // RenderDataSM.pcss.shaderRenderPass = &shader_SM_PCSS_O_RP;
                    RenderDataSM.pcss.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.pcss.view = &view;
                    RenderDataSM.pcss.projection = &projection;
                    RenderDataSM.pcss.lightView = &lightView;
                    RenderDataSM.pcss.lightProjection = &lightProjectionOrthogonal;
                    RenderDataSM.pcss.shadowBias = &shadowBias;
                    RenderDataSM.pcss.pcfRadius = &pcfRadius;
                    RenderDataSM.pcss.quadVAO = &quadVAO;
                    RenderDataSM.pcss.planeVAO = &planeVAO;
                    RenderDataSM.pcss.planeModel = &planeModel;
                    RenderDataSM.pcss.modelVAO = &modelVAO;
                    RenderDataSM.pcss.modelIndexCount = &modelIndexCount;
                    RenderDataSM.pcss.modelModel = &modelModel;
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_PCSS:
                case SHADOW_MAP_PERSPECTIVE_PCSS_DEBUG:
                {
                    RenderDataSM.pcss.depthBuffer = &depthBuffer;
                    RenderDataSM.pcss.client_width = &client_width;
                    RenderDataSM.pcss.client_height = &client_height;
                    RenderDataSM.pcss.shaderDepthPass = &shader_SM_PCSS_P_DP;
                    RenderDataSM.pcss.shaderRenderPass = &shader_SM_PCSS_P_RP;
                    RenderDataSM.pcss.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.pcss.view = &view;
                    RenderDataSM.pcss.projection = &projection;
                    RenderDataSM.pcss.lightView = &lightView;
                    RenderDataSM.pcss.lightProjection = &lightProjectionPerspective;
                    RenderDataSM.pcss.shadowBias = &shadowBias;
                    RenderDataSM.pcss.pcfRadius = &pcfRadius;
                    RenderDataSM.pcss.quadVAO = &quadVAO;
                    RenderDataSM.pcss.planeVAO = &planeVAO;
                    RenderDataSM.pcss.planeModel = &planeModel;
                    RenderDataSM.pcss.modelVAO = &modelVAO;
                    RenderDataSM.pcss.modelIndexCount = &modelIndexCount;
                    RenderDataSM.pcss.modelModel = &modelModel;
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_ESM:
                case SHADOW_MAP_ORTHOGONAL_ESM_DEBUG:
                {
                    RenderDataSM.esm.depthBuffer = &depthBufferExp;
                    RenderDataSM.esm.client_width = &client_width;
                    RenderDataSM.esm.client_height = &client_height;
                    RenderDataSM.esm.shaderDepthPass = &shader_SM_ESM_O_DP;
                    RenderDataSM.esm.shaderRenderPass = &shader_SM_ESM_O_RP;
                    RenderDataSM.esm.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.esm.view = &view;
                    RenderDataSM.esm.projection = &projection;
                    RenderDataSM.esm.lightView = &lightView;
                    RenderDataSM.esm.lightProjection = &lightProjectionOrthogonal;
                    RenderDataSM.esm.shadowBias = &shadowBias;
                    RenderDataSM.esm.expK = &expK;
                    RenderDataSM.esm.quadVAO = &quadVAO;
                    RenderDataSM.esm.planeVAO = &planeVAO;
                    RenderDataSM.esm.planeModel = &planeModel;
                    RenderDataSM.esm.modelVAO = &modelVAO;
                    RenderDataSM.esm.modelIndexCount = &modelIndexCount;
                    RenderDataSM.esm.modelModel =  &modelModel;
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_ESM:
                case SHADOW_MAP_PERSPECTIVE_ESM_DEBUG:
                {
                    RenderDataSM.esm.depthBuffer = &depthBufferExp;
                    RenderDataSM.esm.client_width = &client_width;
                    RenderDataSM.esm.client_height = &client_height;
                    RenderDataSM.esm.shaderDepthPass = &shader_SM_ESM_P_DP;
                    RenderDataSM.esm.shaderRenderPass = &shader_SM_ESM_P_RP;
                    RenderDataSM.esm.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.esm.view = &view;
                    RenderDataSM.esm.projection = &projection;
                    RenderDataSM.esm.lightView = &lightView;
                    RenderDataSM.esm.lightProjection = &lightProjectionPerspective;
                    RenderDataSM.esm.shadowBias = &shadowBias;
                    RenderDataSM.esm.expK = &expK;
                    RenderDataSM.esm.quadVAO = &quadVAO;
                    RenderDataSM.esm.planeVAO = &planeVAO;
                    RenderDataSM.esm.planeModel = &planeModel;
                    RenderDataSM.esm.modelVAO = &modelVAO;
                    RenderDataSM.esm.modelIndexCount = &modelIndexCount;
                    RenderDataSM.esm.modelModel =  &modelModel;
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_VSM:
                case SHADOW_MAP_ORTHOGONAL_VSM_DEBUG:
                {
                    RenderDataSM.vsm.depthBuffer = &depthBuffer;
                    RenderDataSM.vsm.client_width = &client_width;
                    RenderDataSM.vsm.client_height = &client_height;
                    RenderDataSM.vsm.shaderDepthPass = &shader_SM_VSM_O_DP;
                    RenderDataSM.vsm.shaderRenderPass = &shader_SM_VSM_O_RP;
                    RenderDataSM.vsm.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.vsm.view = &view;
                    RenderDataSM.vsm.projection = &projection;
                    RenderDataSM.vsm.lightView = &lightView;
                    RenderDataSM.vsm.lightProjection = &lightProjectionOrthogonal;
                    RenderDataSM.vsm.quadVAO = &quadVAO;
                    RenderDataSM.vsm.planeVAO = &planeVAO;
                    RenderDataSM.vsm.planeModel = &planeModel;
                    RenderDataSM.vsm.modelVAO = &modelVAO;
                    RenderDataSM.vsm.modelIndexCount = &modelIndexCount;
                    RenderDataSM.vsm.modelModel =  &modelModel;
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_VSM:
                case SHADOW_MAP_PERSPECTIVE_VSM_DEBUG:
                {
                    RenderDataSM.vsm.depthBuffer = &depthBuffer;
                    RenderDataSM.vsm.client_width = &client_width;
                    RenderDataSM.vsm.client_height = &client_height;
                    RenderDataSM.vsm.shaderDepthPass = &shader_SM_VSM_P_DP;
                    RenderDataSM.vsm.shaderRenderPass = &shader_SM_VSM_P_RP;
                    RenderDataSM.vsm.shaderDepthDebug = &shader_DBD;
                    RenderDataSM.vsm.view = &view;
                    RenderDataSM.vsm.projection = &projection;
                    RenderDataSM.vsm.lightView = &lightView;
                    RenderDataSM.vsm.lightProjection = &lightProjectionPerspective;
                    RenderDataSM.vsm.quadVAO = &quadVAO;
                    RenderDataSM.vsm.planeVAO = &planeVAO;
                    RenderDataSM.vsm.planeModel = &planeModel;
                    RenderDataSM.vsm.modelVAO = &modelVAO;
                    RenderDataSM.vsm.modelIndexCount = &modelIndexCount;
                    RenderDataSM.vsm.modelModel =  &modelModel;
                    break;
                }

                case RAY_TRACING_DEBUG:
                {
                    RenderDataRT.debug.VertexSSBO = &VertexSSBO;
                    RenderDataRT.debug.MatrixSSBO = &MatrixSSBO;
                    RenderDataRT.debug.BvhSSBO = &BvhSSBO;
                    RenderDataRT.debug.nodeCount = (int)BVH.getBvh().size();
                    RenderDataRT.debug.client_width = &client_width;
                    RenderDataRT.debug.client_height = &client_height;
                    RenderDataRT.debug.shaderDebugBvh = &shader_RT_BVH;
                    RenderDataRT.debug.view = &view;
                    RenderDataRT.debug.projection = &projection;
                    break;
                }
                case RAY_TRACING_HARD_PERSPECTIVE:
                {
                    RenderDataRT.hard.VertexSSBO = &VertexSSBO;
                    RenderDataRT.hard.MatrixSSBO = &MatrixSSBO;
                    RenderDataRT.hard.BvhSSBO = &BvhSSBO;
                    RenderDataRT.hard.rayTracedTexture = &rayTracedTexture;
                    RenderDataRT.hard.texture_width = &rayTracingTextureWidth;
                    RenderDataRT.hard.texture_height = &rayTracingTextureHeight;
                    RenderDataRT.hard.client_width = &client_width;
                    RenderDataRT.hard.client_height = &client_height;
                    RenderDataRT.hard.shaderRayTracing = &shader_RT_HARD;
                    RenderDataRT.hard.shaderImageOut = &shader_IO;
                    RenderDataRT.hard.viewPos = &viewPos;
                    RenderDataRT.hard.view = &view;
                    RenderDataRT.hard.projection = &projection;
                    RenderDataRT.hard.quadVAO = &quadVAO;
                    break;
                }
                case RAY_TRACING_SOFT_PERSPECTIVE:
                {
                    RenderDataRT.soft.VertexSSBO = &VertexSSBO;
                    RenderDataRT.soft.MatrixSSBO = &MatrixSSBO;
                    RenderDataRT.soft.BvhSSBO = &BvhSSBO;
                    RenderDataRT.soft.rayTracedTexture = &rayTracedTexture;
                    RenderDataRT.soft.texture_width = &rayTracingTextureWidth;
                    RenderDataRT.soft.texture_height = &rayTracingTextureHeight;
                    RenderDataRT.soft.client_width = &client_width;
                    RenderDataRT.soft.client_height = &client_height;
                    RenderDataRT.soft.shaderRayTracing = &shader_RT_P_SOFT;
                    RenderDataRT.soft.shaderImageOut = &shader_IO;
                    RenderDataRT.soft.curFrameIndex = 0;
                    RenderDataRT.soft.shadowRayCount = shadowRayCount;
                    RenderDataRT.soft.viewPos = &viewPos;
                    RenderDataRT.soft.view = &view;
                    RenderDataRT.soft.projection = &projection;
                    RenderDataRT.soft.quadVAO = &quadVAO;
                    break;
                }
                
                default:
                    break;
            }

            shadowAlg = newShadowAlg;
        }

        return EXIT_SUCCESS;
    }

    case WM_SET_LIGHT_POSITION:
    {
        cpvec3 pos = reinterpret_cast<cpvec3>(wParam);
        setLightUBO_position(lightUBO, *pos);

        vec3_set(&light.position, pos->x, pos->y, pos->z);

        if (light.type == LIGHT_POINT)
        {
            vec3 tmpPos = {0, 0, 0};
            mat4_transform_vec3(&modelModel, &tmpPos);
            mat4_set_look_at(&lightView, &light.position, &tmpPos, &viewUp);
        }
        else if (light.type == LIGHT_SPOT)
        {
            mat4_set_look_to(&lightView, &light.position, &light.direction, &viewUp);
        }

        return EXIT_SUCCESS;
    }

    case WM_SET_LIGHT_DIRECTION:
    {
        cpvec3 dir = reinterpret_cast<cpvec3>(wParam);
        setLightUBO_direction(lightUBO, *dir);

        vec3_set(&light.direction, dir->x, dir->y, dir->z);

        if (light.type == LIGHT_SPOT)
        {
            mat4_set_look_to(&lightView, &light.position, &light.direction, &viewUp);
        }

        return EXIT_SUCCESS;
    }

    case WM_SET_LIGHT_COLOR:
    {
        cpvec3 col = reinterpret_cast<cpvec3>(wParam);
        setLightUBO_color(lightUBO, *col);

        vec3_set(&light.color, col->x, col->y, col->z);

        return EXIT_SUCCESS;
    }

    case WM_SET_LIGHT_RADIUS:
    {
        const float* radius = reinterpret_cast<const float*>(wParam);
        setLightUBO_radius(lightUBO, *radius);

        light.radius = *radius;

        return EXIT_SUCCESS;
    }

    case WM_SET_LIGHT_INTENSITY:
    {
        const float* intensity = reinterpret_cast<const float*>(wParam);
        setLightUBO_intensity(lightUBO, *intensity);

        light.intensity = *intensity;

        return EXIT_SUCCESS;
    }

    case WM_SET_LIGHT_INNER_CUTOFF:
    {
        const float* innerCutoff = reinterpret_cast<const float*>(wParam);
        setLightUBO_innerCutoff(lightUBO, *innerCutoff);

        light.innerCutoff = *innerCutoff;

        return EXIT_SUCCESS;
    }

    case WM_SET_LIGHT_OUTER_CUTOFF:
    {
        const float* outerCutoff = reinterpret_cast<const float*>(wParam);
        setLightUBO_outerCutoff(lightUBO, *outerCutoff);
        
        light.outerCutoff = *outerCutoff;

        return EXIT_SUCCESS;
    }

    case WM_SET_LIGHT_TYPE:
    {
        const int* type = reinterpret_cast<const int*>(wParam);
        setLightUBO_type(lightUBO, *type);

        light.type = (float)*type;

        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_ALGORITM:
    {
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_RESOLUTION:
    {
        const int* val1 = reinterpret_cast<const int*>(wParam);
        const int* val2 = reinterpret_cast<const int*>(lParam);

        if (*val1 >= 0 && *val1 <= RESOLUTION_MAP_MAX_X &&
            *val2 >= 0 && *val2 <= RESOLUTION_MAP_MAX_Y)
        {
            ForbidDrawing = true;
            glFlush();
            glFinish();

            GenDepthFrameBuffer(depthBuffer, *val1, *val2);
            GenExpDepthFrameBuffer(depthBufferExp, *val1, *val2);

            glFlush();
            glFinish();
            ForbidDrawing = false;
        }

        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_BIAS:
    {
        const float* val = reinterpret_cast<const float*>(wParam);
        if (*val > 0.f) shadowBias = *val;
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_PCF_RADIUS:
    {
        const float* val = reinterpret_cast<const float*>(wParam);
        if (*val > 0.f) pcfRadius = *val;
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_EXP_K:
    {
        const float* val = reinterpret_cast<const float*>(wParam);
        if (*val > 0.f) expK = *val;
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_RENDER_MODE:
    {
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_SIDE_LEFT:
    {
        lightProjLeft = *reinterpret_cast<float*>(wParam);

        mat4_set_perspective_projection(
            &lightProjectionPerspective,
            depthBuffer.width, depthBuffer.height,
            lightProjNear, lightProjFar,
            lightProjFov);

        mat4_set_ortho_projection_with_aspect(
            &lightProjectionOrthogonal, 
            lightProjLeft, lightProjRight,
            lightProjBottom, lightProjTop,
            lightProjNear, lightProjFar,
            depthBuffer.width, depthBuffer.height);
        
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_SIDE_RIGHT:
    {
        lightProjRight = *reinterpret_cast<float*>(wParam);

        mat4_set_perspective_projection(
            &lightProjectionPerspective,
            depthBuffer.width, depthBuffer.height,
            lightProjNear, lightProjFar,
            lightProjFov);

        mat4_set_ortho_projection_with_aspect(
            &lightProjectionOrthogonal, 
            lightProjLeft, lightProjRight,
            lightProjBottom, lightProjTop,
            lightProjNear, lightProjFar,
            depthBuffer.width, depthBuffer.height);
        
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_SIDE_BOTTOM:
    {
        lightProjBottom = *reinterpret_cast<float*>(wParam);

        mat4_set_perspective_projection(
            &lightProjectionPerspective,
            depthBuffer.width, depthBuffer.height,
            lightProjNear, lightProjFar,
            lightProjFov);

        mat4_set_ortho_projection_with_aspect(
            &lightProjectionOrthogonal, 
            lightProjLeft, lightProjRight,
            lightProjBottom, lightProjTop,
            lightProjNear, lightProjFar,
            depthBuffer.width, depthBuffer.height);
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_SIDE_TOP:
    {
        lightProjTop = *reinterpret_cast<float*>(wParam);

        mat4_set_perspective_projection(
            &lightProjectionPerspective,
            depthBuffer.width, depthBuffer.height,
            lightProjNear, lightProjFar,
            lightProjFov);

        mat4_set_ortho_projection_with_aspect(
            &lightProjectionOrthogonal, 
            lightProjLeft, lightProjRight,
            lightProjBottom, lightProjTop,
            lightProjNear, lightProjFar,
            depthBuffer.width, depthBuffer.height);
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_SIDE_NEAR:
    {
        lightProjNear = *reinterpret_cast<float*>(wParam);

        mat4_set_perspective_projection(
            &lightProjectionPerspective,
            depthBuffer.width, depthBuffer.height,
            lightProjNear, lightProjFar,
            lightProjFov);

        mat4_set_ortho_projection_with_aspect(
            &lightProjectionOrthogonal, 
            lightProjLeft, lightProjRight,
            lightProjBottom, lightProjTop,
            lightProjNear, lightProjFar,
            depthBuffer.width, depthBuffer.height);
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_SIDE_FAR:
    {
        lightProjFar = *reinterpret_cast<float*>(wParam);

        mat4_set_perspective_projection(
            &lightProjectionPerspective,
            depthBuffer.width, depthBuffer.height,
            lightProjNear, lightProjFar,
            lightProjFov);

        mat4_set_ortho_projection_with_aspect(
            &lightProjectionOrthogonal, 
            lightProjLeft, lightProjRight,
            lightProjBottom, lightProjTop,
            lightProjNear, lightProjFar,
            depthBuffer.width, depthBuffer.height);
        return EXIT_SUCCESS;
    }

    case WM_SET_SHADOWMAP_FOV:
    {
        lightProjFov = degrees_to_radians(*reinterpret_cast<float*>(wParam));

        mat4_set_perspective_projection(
            &lightProjectionPerspective,
            depthBuffer.width, depthBuffer.height,
            lightProjNear, lightProjFar,
            lightProjFov);

        return EXIT_SUCCESS;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        if (!ForbidDrawing)
        {
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
                    ShadowMap(RenderDataSM.main);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_DEBUG:
                {
                    ShadowMapDebug(RenderDataSM.main);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE:
                {
                    ShadowMap(RenderDataSM.main);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_DEBUG:
                {
                    ShadowMapDebug(RenderDataSM.main);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_PCF:
                {
                    ShadowMapPcf(RenderDataSM.pcf);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_PCF_DEBUG:
                {
                    ShadowMapPcfDebug(RenderDataSM.pcf);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_PCF:
                {
                    ShadowMapPcf(RenderDataSM.pcf);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_PCF_DEBUG:
                {
                    ShadowMapPcfDebug(RenderDataSM.pcf);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_NOISE:
                {
                    ShadowMapNoise(RenderDataSM.noise);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_NOISE_DEBUG:
                {
                    ShadowMapNoiseDebug(RenderDataSM.noise);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_NOISE:
                {
                    ShadowMapNoise(RenderDataSM.noise);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_NOISE_DEBUG:
                {
                    ShadowMapNoiseDebug(RenderDataSM.noise);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_PCSS:
                {
                    ShadowMapPcss(RenderDataSM.pcss);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_PCSS_DEBUG:
                {
                    ShadowMapPcssDebug(RenderDataSM.pcss);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_PCSS:
                {
                    ShadowMapPcss(RenderDataSM.pcss);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_PCSS_DEBUG:
                {
                    ShadowMapPcssDebug(RenderDataSM.pcss);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_ESM:
                {
                    ShadowMapEsm(RenderDataSM.esm);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_ESM_DEBUG:
                {
                    ShadowMapEsmDebug(RenderDataSM.esm);
                    break;
                }
                
                case SHADOW_MAP_PERSPECTIVE_ESM:
                {
                    ShadowMapEsm(RenderDataSM.esm);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_ESM_DEBUG:
                {
                    ShadowMapEsmDebug(RenderDataSM.esm);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_VSM:
                {
                    ShadowMapVsm(RenderDataSM.vsm);
                    break;
                }

                case SHADOW_MAP_ORTHOGONAL_VSM_DEBUG:
                {
                    ShadowMapVsmDebug(RenderDataSM.vsm);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_VSM:
                {
                    ShadowMapVsm(RenderDataSM.vsm);
                    break;
                }

                case SHADOW_MAP_PERSPECTIVE_VSM_DEBUG:
                {
                    ShadowMapVsmDebug(RenderDataSM.vsm);
                    break;
                }

                case RAY_TRACING_DEBUG:
                {
                    RayTracingDrawBvh(RenderDataRT.debug);
                    break;
                }

                case RAY_TRACING_HARD_PERSPECTIVE:
                {
                    RayTracingHard(RenderDataRT.hard);
                    break;
                }

                case RAY_TRACING_SOFT_PERSPECTIVE:
                {
                    if (camera_moved) RenderDataRT.soft.curFrameIndex = 0;
                    RayTracingSoft(RenderDataRT.soft);
                    break;
                }
                
                default:
                    break;
            }
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

        if (lightUBO) glDeleteBuffers(1, &lightUBO);

        if (depthBuffer.Texture) glDeleteTextures(1, &depthBuffer.Texture);
        if (depthBuffer.FBO) glDeleteFramebuffers(1, &depthBuffer.FBO);

        if (depthBufferExp.Texture) glDeleteTextures(1, &depthBufferExp.Texture);
        if (depthBufferExp.RBO) glDeleteRenderbuffers(1, &depthBufferExp.RBO);
        if (depthBufferExp.FBO) glDeleteFramebuffers(1, &depthBufferExp.FBO);

        if (VertexSSBO) glDeleteBuffers(1, &VertexSSBO);
        if (MatrixSSBO) glDeleteBuffers(1, &MatrixSSBO);
        if (BvhSSBO) glDeleteBuffers(1, &BvhSSBO);
        if (rayTracedTexture) glDeleteTextures(1, &rayTracedTexture);

        shader.delete_program();
        shader_DBD.delete_program();
        shader_SM_O_DP.delete_program();
        shader_SM_O_RP.delete_program();
        shader_SM_P_DP.delete_program();
        shader_SM_P_RP.delete_program();
        shader_SM_PCF_O_DP.delete_program();
        shader_SM_PCF_O_RP.delete_program();
        shader_SM_PCF_P_DP.delete_program();
        shader_SM_PCF_P_RP.delete_program();
        shader_SM_ESM_O_DP.delete_program();
        shader_SM_ESM_O_RP.delete_program();
        shader_SM_ESM_P_DP.delete_program();
        shader_SM_ESM_P_RP.delete_program();
        shader_SM_VSM_O_DP.delete_program();
        shader_SM_VSM_O_RP.delete_program();
        shader_SM_VSM_P_DP.delete_program();
        shader_SM_VSM_P_RP.delete_program();
        shader_SM_NOISE_O_DP.delete_program();
        shader_SM_NOISE_O_RP.delete_program();
        shader_SM_NOISE_P_DP.delete_program();
        shader_SM_NOISE_P_RP.delete_program();
        shader_SM_PCSS_P_DP.delete_program();
        shader_SM_PCSS_P_RP.delete_program();
        shader_RT_BVH.delete_program();
        shader_IO.delete_program();
        shader_RT_HARD.delete_program();
        shader_RT_P_SOFT.delete_program();

        PostQuitMessage(0);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}