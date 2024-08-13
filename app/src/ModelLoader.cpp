#include "ModelLoader.h"

bool LoadModel(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

    if (!scene)
    {
        std::cerr << "Error: " << importer.GetErrorString() << std::endl;
        return false;
    }

    if (scene->mNumMeshes == 0)
    {
        std::cerr << "Error: No meshes found in file " << filePath << std::endl;
        return false;
    }

    aiMesh* mesh = scene->mMeshes[0]; // Предполагаем, что есть хотя бы одна меша

    // Извлечение вершин и нормалей
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        vertex.position = mesh->mVertices[i];
        vertex.normal = mesh->mNormals[i];
        vertices.push_back(vertex);
    }

    // Извлечение индексов
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace& face = mesh->mFaces[i];
        if (face.mNumIndices == 3)
        { // Убедимся, что это треугольник
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }
    }

    return true;
}