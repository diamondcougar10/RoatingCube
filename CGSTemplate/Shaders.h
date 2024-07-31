#ifndef SHADERS_H
#define SHADERS_H

#include "MathEq.h"

void (*VertexShader)(Vertex&) = 0;
void (*PixelShader)(unsigned&) = 0;

Matrix4x4 SV_WorldMatrix;
Matrix4x4 SV_ViewMatrix;
Matrix4x4 SV_ProjectionMatrix;

void VS_WVP(Vertex& v) {
    // Transform the vertex by the world, view, and projection matrices
    v = SV_WorldMatrix * v;
    v = SV_ViewMatrix * v;
    v = SV_ProjectionMatrix * v;

    // Perform perspective division
    v.xyzw[0] /= v.xyzw[3];
    v.xyzw[1] /= v.xyzw[3];
    v.xyzw[2] /= v.xyzw[3];
}

void PS_White(unsigned& color) {
    color = 0xFFFFFFFF;
}

#endif 
