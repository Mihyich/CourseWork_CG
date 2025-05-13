#ifndef PLANE_MESH_GENERATOR_H
#define PLANE_MESH_GENERATOR_H

#include <vector>

#include "winapi_GLextensions.h"
#include "Vector3D.h"

void genPlaneMeshVertices(std::vector<vec3>& vertices, float size);

void genPlaneMeshNormales(std::vector<vec3>& normales);

void genPlaneMeshIndeces(std::vector<unsigned int>& indeces);

void genPlaneMeshVNI(std::vector<vec3>& vertices, std::vector<vec3>& normales, std::vector<unsigned int>& indeces, float size);

bool GenPlaneMesh(GLuint &planeVAO, GLuint &planeVBO, GLuint &planeEBO, float size);

#endif // PLANE_MESH_GENERATOR_H