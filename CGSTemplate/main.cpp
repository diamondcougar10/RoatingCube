#include <iostream>
#include <cmath>
#include "RasterSurface.h"
#include "RasterHelper.h"
#include "MathEq.h"
#include "Defines.h"
#include "Shaders.h"
#include "XTime.h"

unsigned SCREEN_ARRAY[NUM_PIXELS];

// Define vertices for a 3D cube and grid
Vertex cubeVerts[8];
Vertex gridVerts[44];
Vertex cube2Verts[8];
Vertex cube3Verts[8];
Vertex cube4Verts[8];

// Function to initialize vertices
void InitializeVertices() {
    // Cube vertices
    cubeVerts[0] = { -0.25f, 0.25f, -0.25f, 1.0f, 0xFF00FF00 };
    cubeVerts[1] = { 0.25f, 0.25f, -0.25f, 1.0f, 0xFF00FF00 };
    cubeVerts[2] = { -0.25f, -0.25f, -0.25f, 1.0f, 0xFF00FF00 };
    cubeVerts[3] = { 0.25f, -0.25f, -0.25f, 1.0f, 0xFF00FF00 };
    cubeVerts[4] = { -0.25f, 0.25f, 0.25f, 1.0f, 0xFF00FF00 };
    cubeVerts[5] = { 0.25f, 0.25f, 0.25f, 1.0f, 0xFF00FF00 };
    cubeVerts[6] = { -0.25f, -0.25f, 0.25f, 1.0f, 0xFF00FF00 };
    cubeVerts[7] = { 0.25f, -0.25f, 0.25f, 1.0f, 0xFF00FF00 };

    // Grid vertices (10x10 grid, 11 lines each direction)
    int idx = 0;
    for (int i = 0; i <= 10; ++i) {
        float pos = -0.5f + i * 0.1f;
        gridVerts[idx++] = { -0.5f, 0.0f, pos, 1.0f, 0xFFFFFFFF };
        gridVerts[idx++] = { 0.5f, 0.0f, pos, 1.0f, 0xFFFFFFFF };
        gridVerts[idx++] = { pos, 0.0f, -0.5f, 1.0f, 0xFFFFFFFF };
        gridVerts[idx++] = { pos, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF };
    }


}

// Function to draw the grid
void DrawGrid() {
    for (int i = 0; i < 44; i += 2) {
        ParametricDrawLine(gridVerts[i], gridVerts[i + 1]);
    }
}

// Function to draw the cube
void DrawCube() {
    // Draw the edges of the cube
    ParametricDrawLine(cubeVerts[0], cubeVerts[1]);
    ParametricDrawLine(cubeVerts[1], cubeVerts[3]);
    ParametricDrawLine(cubeVerts[3], cubeVerts[2]);
    ParametricDrawLine(cubeVerts[2], cubeVerts[0]);

    ParametricDrawLine(cubeVerts[4], cubeVerts[5]);
    ParametricDrawLine(cubeVerts[5], cubeVerts[7]);
    ParametricDrawLine(cubeVerts[7], cubeVerts[6]);
    ParametricDrawLine(cubeVerts[6], cubeVerts[4]);

    ParametricDrawLine(cubeVerts[0], cubeVerts[4]);
    ParametricDrawLine(cubeVerts[1], cubeVerts[5]);
    ParametricDrawLine(cubeVerts[2], cubeVerts[6]);
    ParametricDrawLine(cubeVerts[3], cubeVerts[7]);
}

// Function to draw Cube 2
void DrawCube2() {
    // Draw the edges of Cube 2
    ParametricDrawLine(cube2Verts[0], cube2Verts[1]);
    ParametricDrawLine(cube2Verts[1], cube2Verts[3]);
    ParametricDrawLine(cube2Verts[3], cube2Verts[2]);
    ParametricDrawLine(cube2Verts[2], cube2Verts[0]);

    ParametricDrawLine(cube2Verts[4], cube2Verts[5]);
    ParametricDrawLine(cube2Verts[5], cube2Verts[7]);
    ParametricDrawLine(cube2Verts[7], cube2Verts[6]);
    ParametricDrawLine(cube2Verts[6], cube2Verts[4]);

    ParametricDrawLine(cube2Verts[0], cube2Verts[4]);
    ParametricDrawLine(cube2Verts[1], cube2Verts[5]);
    ParametricDrawLine(cube2Verts[2], cube2Verts[6]);
    ParametricDrawLine(cube2Verts[3], cube2Verts[7]);
}

// Function to draw Cube 3
void DrawCube3() {
    // Draw the edges of Cube 3
    ParametricDrawLine(cube3Verts[0], cube3Verts[1]);
    ParametricDrawLine(cube3Verts[1], cube3Verts[3]);
    ParametricDrawLine(cube3Verts[3], cube3Verts[2]);
    ParametricDrawLine(cube3Verts[2], cube3Verts[0]);

    ParametricDrawLine(cube3Verts[4], cube3Verts[5]);
    ParametricDrawLine(cube3Verts[5], cube3Verts[7]);
    ParametricDrawLine(cube3Verts[7], cube3Verts[6]);
    ParametricDrawLine(cube3Verts[6], cube3Verts[4]);

    ParametricDrawLine(cube3Verts[0], cube3Verts[4]);
    ParametricDrawLine(cube3Verts[1], cube3Verts[5]);
    ParametricDrawLine(cube3Verts[2], cube3Verts[6]);
    ParametricDrawLine(cube3Verts[3], cube3Verts[7]);
}

// Function to draw Cube 4
void DrawCube4() {
    // Draw the edges of Cube 4
    ParametricDrawLine(cube4Verts[0], cube4Verts[1]);
    ParametricDrawLine(cube4Verts[1], cube4Verts[3]);
    ParametricDrawLine(cube4Verts[3], cube4Verts[2]);
    ParametricDrawLine(cube4Verts[2], cube4Verts[0]);

    ParametricDrawLine(cube4Verts[4], cube4Verts[5]);
    ParametricDrawLine(cube4Verts[5], cube4Verts[7]);
    ParametricDrawLine(cube4Verts[7], cube4Verts[6]);
    ParametricDrawLine(cube4Verts[6], cube4Verts[4]);

    ParametricDrawLine(cube4Verts[0], cube4Verts[4]);
    ParametricDrawLine(cube4Verts[1], cube4Verts[5]);
    ParametricDrawLine(cube4Verts[2], cube4Verts[6]);
    ParametricDrawLine(cube4Verts[3], cube4Verts[7]);
}

int main() {
    RS_Initialize("Ryan Curphey", RASTER_WIDTH, RASTER_HEIGHT);

    // Initialize vertices for all objects
    InitializeVertices();

    // Create world matrices for each object
    Matrix4x4 GridWorldMatrix = Matrix4x4::Identity();
    Matrix4x4 CubeWorldMatrix = CreateTranslationMatrix(0, -0.25, 0);
    Matrix4x4 Cube2WorldMatrix = CreateTranslationMatrix(0.5f, 0.0f, 0.5f);
    Matrix4x4 Cube3WorldMatrix = CreateTranslationMatrix(-0.5f, 0.0f, 0.5f);
    Matrix4x4 Cube4WorldMatrix = CreateTranslationMatrix(0.0f, 0.5f, -0.5f);

    // Set initial camera position and rotation
    Matrix4x4 CameraMatrix = CreateXRotationMatrix(-18 * (PI / 180.0f)) * CreateTranslationMatrix(0, 0, -1);
    Matrix4x4 ViewMatrix = OrthonormalInverse(CameraMatrix);

    // Create projection matrix
    float fovY = 90.0f * (PI / 180.0f); // Field of view in radians
    float aspectRatio = static_cast<float>(RASTER_WIDTH) / RASTER_HEIGHT;
    float zNear = 0.1f;
    float zFar = 10.0f;
    Matrix4x4 ProjectionMatrix = MakeProjectionMatrix(fovY, aspectRatio, zNear, zFar);

    XTime Timer(10, 0.75); // Initialize XTime with 10 samples and a smooth factor of 0.75
    Timer.Restart();

    do {
        Timer.Signal();

        // Clear the screen with a black color
        ClearScreen(0xFF000000);

        // Update central cube rotation
        double deltaTime = Timer.SmoothDelta();
        CubeWorldMatrix = CreateYRotationMatrix(deltaTime) * CubeWorldMatrix;

        // Update rotation for cubes around the central cylinder
        Cube2WorldMatrix = CreateYRotationMatrix(-deltaTime) * CreateTranslationMatrix(0.5f, 0.0f, 0.5f);
        Cube3WorldMatrix = CreateYRotationMatrix(deltaTime) * CreateTranslationMatrix(-0.5f, 0.0f, 0.5f);
        Cube4WorldMatrix = CreateYRotationMatrix(-deltaTime) * CreateTranslationMatrix(0.0f, 0.5f, -0.5f);

        // Set shaders for all objects
        VertexShader = VS_WVP;
        PixelShader = PS_White;

        // Set matrices for the grid
        SV_WorldMatrix = GridWorldMatrix;
        SV_ViewMatrix = ViewMatrix;
        SV_ProjectionMatrix = ProjectionMatrix;

        // Draw the grid
        DrawGrid();

        // Set matrices for the central cube
        SV_WorldMatrix = CubeWorldMatrix;
        DrawCube();

        // Set matrices for Cube 2
        SV_WorldMatrix = Cube2WorldMatrix;
        DrawCube2();

        // Set matrices for Cube 3
        SV_WorldMatrix = Cube3WorldMatrix;
        DrawCube3();

        // Set matrices for Cube 4
        SV_WorldMatrix = Cube4WorldMatrix;
        DrawCube4();

    } while (RS_Update(SCREEN_ARRAY, NUM_PIXELS));

    RS_Shutdown();

    return 0;
}
