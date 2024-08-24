#ifndef RAY_TRACING_RENDER_DATA_H
#define RAY_TRACING_RENDER_DATA_H

#include "RayTracingDebugRenderData.h"
#include "RayTracingHardRenderData.h"

union RayTracingRenderData
{
    RayTracingDebugRenderData debug;
    RayTracingHardRenderData hard;
};

#endif // RAY_TRACING_HARD_RENDER_DATA_H