#ifndef PAINTER_H
#define PAINTER_H

#include <SDL3/SDL_opengles2.h>

#define GLM_FORCE_PURE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Painter
{

public:
    Painter();

    void rectangle(float x, float y, float width, float height, const glm::vec3 &color);
    void circle(float x, float y, float radius, const glm::vec3 &color);

private:
    void initCircleVertexPositionBuffer();
    void initSquareVertexPositionBuffer(const glm::vec2 &pivot = glm::vec2(0.f, 0.f));

    GLuint m_program;
    GLint m_aPositionLocation;
    GLint m_uColorLocation;
    GLint m_uMvpMatrixLocation;
    const int m_amountOfCircleVertices = 20;
    // Vertex buffers
    GLuint circleVertexPositionBuffer;
    GLuint squareVertexPositionBuffer;
    // ProjView matrix
    glm::mat4 m_projViewMatrix;
};

#endif // PAINTER_H
