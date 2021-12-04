#include "resources/mesh.hpp"

#include <fstream>
#include <sstream>

#include <iostream>

void Resources::Mesh::generateMesh()
{
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
}

Resources::Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
}

bool Resources::Mesh::loadMesh(const std::string& filename)
{
    std::ifstream file;
    file.open("assets/" + filename);
    if (!file.is_open())
    {
        std::cout << "could not open obj file : " << filename << std::endl;
        return false;
    }

    while (file)
    {
        std::string line;
        std::getline(file, line);

        switch (line[0])
        {
        //submesh
        case 'o':
            break;
        //vertex
        case 'v':
        {
            switch (line[1])
            {
            //vertex pos
            case ' ':
            {
                std::istringstream iss(line.substr(2));

                for (int i = 0; i < 3; ++i)
                {
                    float pos;
                    iss >> pos;
                    vertices.push_back(pos);
                }

                break;
            }
            //texture uv
            case 't':
                break;
            //vertex normal
            case 'n':
                break;
            }

            break;
        }
        //mtl
        case 'u':
        {
            if (line.substr(0, 7) == "usemtl")
            {

            }

            break;
        }
        //face
        case 'f':
        {
            if (line[1] == ' ')
            {
                std::istringstream iss(line.substr(2));

                for (int i = 0; i < 3; ++i)
                {
                    //indices
                    uint v, t, n;
                    iss >> v;
                    iss.ignore();
                    iss >> t;
                    iss.ignore();
                    iss >> n;
                    iss.ignore();

                    indices.push_back(v - 1);
                }
            }

            break;
        }
        default:
            break;
        }
    }

    generateMesh();

    std::cout << "successfully loaded obj file : " << filename << std::endl;

    return true;
}

bool Resources::Mesh::loadMesh(Box* b)
{
    if (!b)
        return false;

    b->getAttribs(vertices, indices);

    generateMesh();

    return true;
}

bool Resources::Mesh::loadMesh(Sphere* sph)
{
    if (!sph)
        return false;

    sph->getAttribs(vertices, indices);

    generateMesh();

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