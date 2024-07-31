#ifndef MATH_EQ_H
#define MATH_EQ_H

#include <cmath>
#include "Defines.h"

const float PI = 3.14159265358979323846f;


// Structure for 4x4 matrix
struct Matrix4x4 {
    float m[4][4];

    Matrix4x4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = 0.0f;
    }

    static Matrix4x4 Identity() {
        Matrix4x4 matrix;
        for (int i = 0; i < 4; ++i)
            matrix.m[i][i] = 1.0f;
        return matrix;
    }

    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }

    struct Vertex operator*(const struct Vertex& v) const;
};

// Structure for vertices
struct Vertex {
    float xyzw[4];
    unsigned color;

    Vertex() {
        xyzw[0] = xyzw[1] = xyzw[2] = 0.0f;
        xyzw[3] = 1.0f;
        color = 0xFFFFFFFF;
    }

    Vertex(float x, float y, float z, float w, unsigned c) {
        xyzw[0] = x;
        xyzw[1] = y;
        xyzw[2] = z;
        xyzw[3] = w;
        color = c;
    }
};

// Define multiplication of Matrix4x4 and Vertex
inline Vertex Matrix4x4::operator*(const Vertex& v) const {
    Vertex result;
    for (int i = 0; i < 4; ++i) {
        result.xyzw[i] = m[i][0] * v.xyzw[0] + m[i][1] * v.xyzw[1] + m[i][2] * v.xyzw[2] + m[i][3] * v.xyzw[3];
    }
    result.color = v.color;
    return result;
}

// Rotation matrices
Matrix4x4 CreateXRotationMatrix(float angle) {
    Matrix4x4 matrix = Matrix4x4::Identity();
    matrix.m[1][1] = cosf(angle);
    matrix.m[1][2] = -sinf(angle);
    matrix.m[2][1] = sinf(angle);
    matrix.m[2][2] = cosf(angle);
    return matrix;
}

Matrix4x4 CreateYRotationMatrix(float angle) {
    Matrix4x4 matrix = Matrix4x4::Identity();
    matrix.m[0][0] = cosf(angle);
    matrix.m[0][2] = sinf(angle);
    matrix.m[2][0] = -sinf(angle);
    matrix.m[2][2] = cosf(angle);
    return matrix;
}

Matrix4x4 CreateZRotationMatrix(float angle) {
    Matrix4x4 matrix = Matrix4x4::Identity();
    matrix.m[0][0] = cosf(angle);
    matrix.m[0][1] = -sinf(angle);
    matrix.m[1][0] = sinf(angle);
    matrix.m[1][1] = cosf(angle);
    return matrix;
}

// Translation matrix
Matrix4x4 CreateTranslationMatrix(float x, float y, float z) {
    Matrix4x4 matrix = Matrix4x4::Identity();
    matrix.m[0][3] = x;
    matrix.m[1][3] = y;
    matrix.m[2][3] = z;
    return matrix;
}

// Function to create a projection matrix
Matrix4x4 MakeProjectionMatrix(float fovY, float aspect, float zNear, float zFar) {
    Matrix4x4 projectionMatrix = {};
    float tanHalfFovY = tan(fovY / 2.0f);
    projectionMatrix.m[0][0] = 1.0f / (aspect * tanHalfFovY);
    projectionMatrix.m[1][1] = 1.0f / tanHalfFovY;
    projectionMatrix.m[2][2] = -(zFar + zNear) / (zFar - zNear);
    projectionMatrix.m[2][3] = -(2.0f * zFar * zNear) / (zFar - zNear);
    projectionMatrix.m[3][2] = -1.0f;  // This value should be in the 4th row and 3rd column
    projectionMatrix.m[3][3] = 0.0f;
    return projectionMatrix;
}


// Function to calculate dot product for 4-component vectors
float DotProduct(const float v1[4], const float v2[4]) {
    return (v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]) + (v1[3] * v2[3]);
}

Matrix4x4 OrthonormalInverse(const Matrix4x4& mIn) {
    Matrix4x4 m;

    // Transpose the 3x3 rotation part
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m.m[i][j] = mIn.m[j][i];

    // Set the default 0.0s and 1.0s for the .w components
    for (int i = 0; i < 3; ++i) {
        m.m[i][3] = 0.0f;
        m.m[3][i] = 0.0f;
    }
    m.m[3][3] = 1.0f;

    // Calculate the new position
    float axisW[4] = { mIn.m[0][3], mIn.m[1][3], mIn.m[2][3], 0.0f };
    m.m[0][3] = -DotProduct(m.m[0], axisW);  // Swapped mIn with m
    m.m[1][3] = -DotProduct(m.m[1], axisW);  // Swapped mIn with m
    m.m[2][3] = -DotProduct(m.m[2], axisW);  // Swapped mIn with m

    return m;
}


// Convert from NDC (Normalized Device Coordinates) to screen coordinates
Vertex NDCtoScreen(const Vertex& v) {
    Vertex result = v;
    result.xyzw[0] = (v.xyzw[0] + 1.0f) * 0.5f * RASTER_WIDTH;
    result.xyzw[1] = (1.0f - v.xyzw[1]) * 0.5f * RASTER_HEIGHT;
    return result;
}

#endif 
