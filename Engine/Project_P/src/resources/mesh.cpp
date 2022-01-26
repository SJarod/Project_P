#include "resources/mesh.hpp"

#include <fstream>
#include <sstream>

#include <iostream>

void Resources::Mesh::assembleVertices(const std::vector<float3>& rawV,
                                       const std::vector<uint3>&  rawI,
                                       const std::vector<float2>& rawVt,
                                       const std::vector<float3>& rawVn)
{
    for (int i = 0; i < rawI.size(); ++i)
    {
        uint v = rawI[i].e[0], t = rawI[i].e[1], n = rawI[i].e[2];

        Vertex vertex;
        vertex.pos = rawV[v];
        vertex.uv = rawVt.size() == 0 ? vec2{ 0.f, 0.f } : vec2(rawVt[t]);
        vertex.n = rawVn.size() == 0 ? vec3{ 0.f, 0.f, 0.f } : vec3(rawVn[n]);

        vertices.push_back(vertex);
    }
}

void Resources::Mesh::generateMeshVAO()
{
    //VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);

    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		//vertex position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		//texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//vertex normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
}

Resources::Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
}

bool Resources::Mesh::loadMesh(const std::string& filename)
{
    //raw information about vertex, uv, normal
    std::vector<float3>	rawV;
    std::vector<float2>	rawVt;
    std::vector<float3>	rawVn;
    //raw information about indices
    std::vector<uint3>	rawI;

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

                float3 pos;
                for (int i = 0; i < 3; ++i)
                    iss >> pos.e[i];
                
                rawV.push_back(pos);

                break;
            }
            //texture uv
            case 't':
            {
                std::istringstream iss(line.substr(2));

                float2 uv;
                for (int i = 0; i < 2; ++i)
                    iss >> uv.e[i];

                rawVt.push_back(uv);

                break;
            }
            //vertex normal
            case 'n':
            {
                std::istringstream iss(line.substr(2));

                float3 n;
                for (int i = 0; i < 3; ++i)
                    iss >> n.e[i];

                rawVn.push_back(n);

                break;
            }
            default:
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
                    uint3 indices;

                    //indices v, t, n
                    iss >> indices.e[0];
                    --indices.e[0];
                    iss.ignore();

                    iss >> indices.e[1];
                    --indices.e[1];
                    iss.ignore();

                    iss >> indices.e[2];
                    --indices.e[2];
                    iss.ignore();

                    rawI.push_back(indices);
                }
            }

            break;
        }
        default:
            break;
        }
    }

    assembleVertices(rawV, rawI, rawVt, rawVn);
    generateMeshVAO();

    std::cout << "successfully loaded obj file : " << filename << std::endl;

    return true;
}

bool Resources::Mesh::loadMesh(const Primitives3::Box& b)
{
    std::vector<float>  vertices;
    std::vector<uint>   indices;
    //vertex position, vertex index
    b.getAttribs(vertices, indices);

    std::vector<float3> rawV;
    for (int i = 0; i < vertices.size(); i += 3)
    {
        float3 vv;
        vv.e[0] = vertices[i];
        vv.e[1] = vertices[i + 1];
        vv.e[2] = vertices[i + 2];
        rawV.push_back(vv);
    }

    std::vector<uint3> rawI;
    for (int i = 0; i < indices.size(); ++i)
    {
        uint3 vi;
        vi.e[0] = indices[i];
        vi.e[1] = 0;
        vi.e[2] = 0;
        rawI.push_back(vi);
    }

    assembleVertices(rawV, rawI);

    generateMeshVAO();

    return true;
}

bool Resources::Mesh::loadMesh(const Primitives3::Sphere& sph)
{
    std::vector<float>  vertices;
    std::vector<uint>   indices;
    //vertex position, vertex index
    sph.getAttribs(vertices, indices);

    std::vector<float3> rawV;
    for (int i = 0; i < vertices.size(); i += 3)
    {
        float3 vv;
        vv.e[0] = vertices[i];
        vv.e[1] = vertices[i + 1];
        vv.e[2] = vertices[i + 2];
        rawV.push_back(vv);
    }

    std::vector<uint3> rawI;
    for (int i = 0; i < indices.size(); ++i)
    {
        uint3 vi;
        vi.e[0] = indices[i];
        vi.e[1] = 0;
        vi.e[2] = 0;
        rawI.push_back(vi);
    }

    assembleVertices(rawV, rawI);

    generateMeshVAO();

    return true;
}

void Resources::Mesh::render() const
{
    glBindVertexArray(VAO);
        //using VBO
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
        //using EBO
        //glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}