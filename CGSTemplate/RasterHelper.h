#ifndef RASTER_HELPER_H
#define RASTER_HELPER_H

#include "RasterSurface.h"
#include "MathEq.h"
#include "Shaders.h"
#include <algorithm>

#define RASTER_WIDTH 500
#define RASTER_HEIGHT 500
#define NUM_PIXELS (RASTER_WIDTH * RASTER_HEIGHT)

extern unsigned SCREEN_ARRAY[NUM_PIXELS];

// Function to convert 2D coordinates to a 1D coordinate
inline int Convert2Dto1D(int x, int y) {
    return y * RASTER_WIDTH + x;
}

// Function to plot a pixel
inline void PlotPixel(int x, int y, unsigned color) {
    if (x >= 0 && x < RASTER_WIDTH && y >= 0 && y < RASTER_HEIGHT) {
        SCREEN_ARRAY[Convert2Dto1D(x, y)] = color;
    }
}

// Function to clear the screen
inline void ClearScreen(unsigned color) {
    std::fill_n(SCREEN_ARRAY, NUM_PIXELS, color);
}

// Parametric line drawing function using linear interpolation
void DrawLine(int x1, int y1, int x2, int y2, unsigned color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = std::max(abs(dx), abs(dy));

    for (int i = 0; i <= steps; ++i) {
        float ratio = static_cast<float>(i) / steps;
        int x = static_cast<int>(x1 + ratio * dx + 0.5f);
        int y = static_cast<int>(y1 + ratio * dy + 0.5f);
        PlotPixel(x, y, color);
    }
}

void ParametricDrawLine(const Vertex& v1, const Vertex& v2) {
    Vertex v1Transformed = v1;
    Vertex v2Transformed = v2;

    // Apply vertex shader
    VertexShader(v1Transformed);
    VertexShader(v2Transformed);

    // Convert to screen coordinates
    Vertex v1Screen = NDCtoScreen(v1Transformed);
    Vertex v2Screen = NDCtoScreen(v2Transformed);

    // Draw line
    DrawLine(static_cast<int>(v1Screen.xyzw[0]), static_cast<int>(v1Screen.xyzw[1]),
        static_cast<int>(v2Screen.xyzw[0]), static_cast<int>(v2Screen.xyzw[1]), v1.color);
}

#endif 
