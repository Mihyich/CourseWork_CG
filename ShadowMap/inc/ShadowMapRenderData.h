#ifndef SHADOW_MAP_RENDER_DATA_H
#define SHADOW_MAP_RENDER_DATA_H

#include "ShadowMapMainRenderData.h"
#include "ShadowMapPcfRenderData.h"
#include "ShadowMapEsmRenderData.h"
#include "ShadowMapVsmRenderData.h"

union ShadowMapRenderData
{
    ShadowMapMainRenderData main;
    ShadowMapPcfRenderData pcf;
    ShadowMapEsmRenderData esm;
    ShadowMapVsmRenderData vsm;
};

#endif // SHADOW_MAP_RENDER_DATA_H