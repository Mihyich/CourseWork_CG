#include "ModelLoader.h"

bool LoadModel(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, bool CCW)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);
    aiMesh* mesh = nullptr;
    Vertex vertex;

    if (!scene)
    {
        std::cout << "Error: " << importer.GetErrorString() << std::endl;
        return false;
    }

    if (scene->mNumMeshes == 0)
    {
        std::cout << "Error: No meshes found in file " << filePath << std::endl;
        return false;
    }

    if (scene && scene->mNumMeshes)
    {
        mesh = scene->mMeshes[0];

        // Извлечение вершин и нормалей
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            vec3_set(&vertex.position, mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vec3_set(&vertex.normal, mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            vertices.push_back(vertex);
        }

        // Извлечение индексов
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace& face = mesh->mFaces[i];
            if (face.mNumIndices == 3)
            {
                if (CCW)
                {
                    indices.push_back(face.mIndices[2]);
                    indices.push_back(face.mIndices[1]);
                    indices.push_back(face.mIndices[0]);
                }
                else
                {
                    indices.push_back(face.mIndices[0]);
                    indices.push_back(face.mIndices[1]);
                    indices.push_back(face.mIndices[2]);
                }
            }
        }

        return true;
    }

    return false;
}

bool GenModelMesh(const std::string& filePath, GLuint &VAO, GLuint &VBO, GLuint &EBO, GLsizei &index_count, bool CCW)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    if (!LoadModel(filePath, vertices, indices, CCW))
        return false;

    if (VAO)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    if (VBO)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if (EBO)
    {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }

    index_count = indices.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return VAO && VBO && EBO;
}