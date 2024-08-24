#ifndef RAY_TRACING_RENDER_DATA_H
#define RAY_TRACING_RENDER_DATA_H

#include "RayTracingDebugRenderData.h"
#include "RayTracingHardRenderData.h"
#include "RayTracingSoftRenderData.h"

union RayTracingRenderData
{
    RayTracingDebugRenderData debug;
    RayTracingHardRenderData hard;
    RayTracingSoftRenderData soft;
};

#endif // RAY_TRACING_HARD_RENDER_DATA_H