#include <string>

#include "shader_program.h"
#include "painter.h"

Painter::Painter()
{
    std::string vShaderPath = "./assets/shaders/color.vert";
    std::string fShaderPath = "./assets/shaders/color.frag";
    m_program = createShaderProgram(vShaderPath, fShaderPath);

    initCircleVertexPositionBuffer();
    initSquareVertexPositionBuffer();

    m_aPositionLocation = glGetAttribLocation(m_program, "aPosition");
    m_uColorLocation = glGetUniformLocation(m_program, "uColor");
    m_uMvpMatrixLocation = glGetUniformLocation(m_program, "uMvpMatrix");

    // Projection matrix
    glm::mat4 projMatrix = glm::ortho(0.f, 200.f, 200.f, 0.f, -5.f, 5.f);
    // View matrix
    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(0.f, 0.f, 1.f),  // Camera position
        glm::vec3(0.f, 0.f, 0.f),  // Target position,
        glm::vec3(0.f, 1.f, 0.f)); // Camera up vector
    m_projViewMatrix = projMatrix * viewMatrix;
}

void Painter::initCircleVertexPositionBuffer()
{
    const int angleStep = 360 / m_amountOfCircleVertices;

    float vertPositions[m_amountOfCircleVertices * 2 + 2 + 2]; // + center + end
    float radius = 0.5f;
    float angle = 0.f;
    int index = 0;

    // Center of the circle
    vertPositions[index++] = 0.f;
    vertPositions[index++] = 0.f;

    for (int i = 0; i < m_amountOfCircleVertices; i++)
    {
        float radians = glm::radians(angle);
        float x = radius * std::cos(radians);
        float y = radius * std::sin(radians);
        vertPositions[index++] = x;
        vertPositions[index++] = y;
        angle += angleStep;
    }

    // End of the circle
    vertPositions[index++] = radius;
    vertPositions[index++] = 0.f;

    glGenBuffers(1, &circleVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, circleVertexPositionBuffer);
    int amount = sizeof(vertPositions) / sizeof(vertPositions[0]);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(GLfloat),
        vertPositions, GL_STATIC_DRAW);
}

void Painter::initSquareVertexPositionBuffer(const glm::vec2 &pivot)
{
    float vertPositions[] = {
        0.f - pivot.x, 0.f - pivot.y,
        0.f - pivot.x, 1.f - pivot.y,
        1.f - pivot.x, 0.f - pivot.y,
        1.f - pivot.x, 1.f - pivot.y
    };
    glGenBuffers(1, &squareVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, squareVertexPositionBuffer);
    int amount = sizeof(vertPositions) / sizeof(vertPositions[0]);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(GLfloat),
        vertPositions, GL_STATIC_DRAW);
    GLint m_aPositionLocation = glGetAttribLocation(m_program, "aPosition");
}

void Painter::circle(float x, float y, float radius, const glm::vec3 &color)
{
    glBindBuffer(GL_ARRAY_BUFFER, circleVertexPositionBuffer);
    glVertexAttribPointer(m_aPositionLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(m_aPositionLocation);

    // Model matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(radius * 2.f, radius * 2.f, 1.f));
    // MVP matrix
    glm::mat4 mvpMatrix = m_projViewMatrix * modelMatrix;
    glUniformMatrix4fv(m_uMvpMatrixLocation, 1, false, glm::value_ptr(mvpMatrix));
    glUniform3fv(m_uColorLocation, 1, glm::value_ptr(color));
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_amountOfCircleVertices + 1 + 1); // + center + end
}

void Painter::rectangle(float x, float y, float width, float height, const glm::vec3 &color)
{
    glBindBuffer(GL_ARRAY_BUFFER, squareVertexPositionBuffer);
    glVertexAttribPointer(m_aPositionLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(m_aPositionLocation);

    // Model matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0.f));
    // modelMatrix = glm::rotate(modelMatrix, glm::radians(20.f), glm::vec3(0.f, 0.f, 1.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(width, height, 1.f));
    // MVP matrix
    glm::mat4 mvpMatrix = m_projViewMatrix * modelMatrix;
    glUniformMatrix4fv(m_uMvpMatrixLocation, 1, false, glm::value_ptr(mvpMatrix));
    glUniform3fv(m_uColorLocation, 1, glm::value_ptr(color));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
