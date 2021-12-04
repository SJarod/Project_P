#include "resources/mesh.hpp"

Resources::Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
}

bool Resources::Mesh::loadMesh(const char* filename)
{
    return false;
}

bool Resources::Mesh::loadMesh(Box* b)
{
    if (!b)
        return false;

    b->getAttribs(vertices, indices);

    //VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);

    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    //EBO
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return true;
}

bool Resources::Mesh::loadMesh(Sphere* sph)
{
    if (!sph)
        return false;

    sph->getAttribs(vertices, indices);

    //VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);

    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    //EBO
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return true;
}

void Resources::Mesh::render() const
{
    glBindVertexArray(VAO);
        //using VBO
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //using EBO
        glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}