#ifndef RAY_TRACE_BUFFER_GENERATOR_H
#define RAY_TRACE_BUFFER_GENERATOR_H

#include <vector>

#include "Matrix4D.h"
#include "RayTraceTriangleStruct.h"
#include "RayTraceBvhStruct.h"

#include "winapi_GLextensions.h"

bool genRayTraceVertexSSBO(const std::vector<RayTraceVertexTringle>& verteces, GLuint& SSBO);

bool genRayTraceMatrixSSBO(const std::vector<mat4>& matrices, GLuint& SSBO);

bool genRayTraceBvhSSBO(const std::vector<RayTraceBVHNode>& bvh, GLuint& SSBO);

#endif // RAY_TRACE_BUFFER_GENERATOR_H