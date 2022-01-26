#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stb_image.h"

#include "utils/memleaks.hpp"
#include "lowrenderer/gameobject.hpp"

#include "resources/scene.hpp"

void assembleVertices(std::vector<Vertex>& vertices,
                      const std::vector<float3>& rawV,
                      const std::vector<uint3>& rawI,
                      const std::vector<float2>& rawVt = std::vector<float2>(),
                      const std::vector<float3>& rawVn = std::vector<float3>())
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

std::vector<Vertex> Resources::Scene::loadMesh(const char* mesh) const
{
    std::string filename = mesh;
    filename = "assets/" + filename;

    //raw information about vertex, uv, normal
    std::vector<float3>	rawV;
    std::vector<float2>	rawVt;
    std::vector<float3>	rawVn;
    //raw information about indices
    std::vector<uint3>	rawI;

    std::ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        std::cout << "could not open obj file : " << filename << std::endl;
        return { {} };
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

    std::vector<Vertex> vx;
    assembleVertices(vx, rawV, rawI, rawVt, rawVn);

    std::cout << "successfully loaded obj file : " << filename << std::endl;

    return vx;
}

std::vector<Vertex> Resources::Scene::loadMesh(const Primitives3::Box& b) const
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

    std::vector<Vertex> vx;
    assembleVertices(vx, rawV, rawI);

    return vx;
}

std::vector<Vertex> Resources::Scene::loadMesh(const Primitives3::Sphere& sph) const
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

    std::vector<Vertex> vx;
    assembleVertices(vx, rawV, rawI);

    return vx;
}

unsigned char* Resources::Scene::loadTexture(const char* texture, TextureDim& dim) const
{
    std::string filename = texture;
    filename = "assets/" + filename;

    int nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = new unsigned char();
    data = stbi_load(filename.c_str(), &dim.width, &dim.height, &nrChannels, 0);

    if (data)
    {
        std::cout << "successfully loaded texture file : " << filename << std::endl;
        return data;
    }
    else
    {
        std::cout << "could not load texture file : " << filename << std::endl;
        return nullptr;
    }
}

Resources::Scene::Scene(const char* sn, Interface::RendererI& rdr)
    : sceneName(sn), rdr(rdr)
{
    debugCam = new Camera;
    viewCam = debugCam;
    dynamicObjs.push_back(debugCam);

    staticObjs.push_back(new GameObject);
}

Resources::Scene::~Scene()
{
    for (Interface::ObjectI* obj : staticObjs)
        delete obj;

    for (Interface::ObjectI* obj : dynamicObjs)
        delete obj;

    staticObjs.clear();
    dynamicObjs.clear();

    delete &rdr;
}

void Resources::Scene::startScene()
{
    for (Interface::ObjectI* obj : staticObjs)
    {
        obj->start();
    }

    for (Interface::ObjectI* obj : dynamicObjs)
    {
        obj->start();
    }
}

void Resources::Scene::updateScene()
{
    for (Interface::ObjectI* obj : dynamicObjs)
    {
        obj->update();
    }
}

void Resources::Scene::renderScene() const
{
    for (Interface::ObjectI* obj : staticObjs)
    {
        obj->render();
    }

    for (Interface::ObjectI* obj : dynamicObjs)
    {
        obj->render();
    }

    rdr.render();
}