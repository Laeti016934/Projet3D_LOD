#include "objectfileformathandler.h"

#include <iostream>
#include <fstream>
#include <sstream>

bool saveOFF( const std::string& filename ,
              std::vector<glm::vec3>& i_vertices ,
              std::vector<glm::vec3>& i_normals ,
              std::vector<Triangle>& i_triangles,
              bool save_normals) {
    std::ofstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open()) {
        std::cout << filename << " cannot be opened" << std::endl;
        return false;
    }

    myfile << "OFF" << std::endl ;

    unsigned int n_vertices = i_vertices.size() , n_triangles = i_triangles.size();
    myfile << n_vertices << " " << n_triangles << " 0" << std::endl;

    for( unsigned int v = 0 ; v < n_vertices ; ++v ) {
        myfile << i_vertices[v][0] << " " << i_vertices[v][1] << " " << i_vertices[v][2] << " ";
        if (save_normals) myfile << i_normals[v][0] << " " << i_normals[v][1] << " " << i_normals[v][2] << std::endl;
        else myfile << std::endl;
    }
    for( unsigned int f = 0 ; f < n_triangles ; ++f ) {
        myfile << 3 << " " << i_triangles[f][0] << " " << i_triangles[f][1] << " " << i_triangles[f][2];
        myfile << std::endl;
    }
    myfile.close();
    return true;
}

static void computeNormals(
    const std::vector<glm::vec3>& vertices,
    const std::vector<Triangle>& triangles,
    std::vector<glm::vec3>& normals)
{
    normals.assign(vertices.size(), glm::vec3(0.0f));

    for(const Triangle& t : triangles)
    {
        const glm::vec3& p0 = vertices[t[0]];
        const glm::vec3& p1 = vertices[t[1]];
        const glm::vec3& p2 = vertices[t[2]];

        glm::vec3 n =
            glm::cross(p1 - p0,
                       p2 - p0);

        normals[t[0]] += n;
        normals[t[1]] += n;
        normals[t[2]] += n;
    }

    for(glm::vec3& n : normals)
    {
        float l = glm::length(n);

        if(l > 1e-8f)
            n /= l;
        else
            n = glm::vec3(0.f, 1.f, 0.f);
    }
}

static bool readNextUsefulLine(
    std::istream& is,
    std::string& line)
{
    while(std::getline(is, line))
    {
        if(line.empty())
            continue;

        if(line[0] == '#')
            continue;

        return true;
    }

    return false;
}

//Oui celui-là il est vibe codé avec le style horrible de copilot j'avoue mais promis le reste c'est fait maison
bool openOFF(
    const std::string& filename,
    std::vector<glm::vec3>& vertices,
    std::vector<glm::vec3>& normals,
    std::vector<Triangle>& triangles,
    bool loadNormals)
{
    std::ifstream file(filename);

    if(!file)
    {
        std::cerr << filename
                  << " cannot be opened"
                  << std::endl;
        return false;
    }

    std::string line;

    if(!readNextUsefulLine(file, line))
        return false;

    if(line != "OFF" && line != "COFF")
    {
        std::cerr   << "Unsupported format: "
                    << line
                    << std::endl;

        return false;
    }

    if(!readNextUsefulLine(file, line))
        return false;

    std::stringstream header(line);

    size_t vertexCount;
    size_t faceCount;
    size_t edgeCount;

    header >> vertexCount >> faceCount >> edgeCount;

    vertices.clear();
    normals.clear();
    triangles.clear();

    vertices.reserve(vertexCount);
    triangles.reserve(faceCount * 2);

    for(size_t i = 0; i < vertexCount; ++i)
    {
        if(!readNextUsefulLine(file, line))
            return false;

        std::stringstream vertexStream(line);

        float x, y, z;

        vertexStream >> x >> y >> z;

        vertices.emplace_back(x, y, z);

        if(loadNormals)
        {
            float nx, ny, nz;

            if(vertexStream >> nx >> ny >> nz)
            {
                normals.emplace_back(nx, ny, nz);
            }
        }
    }

    for(size_t f = 0; f < faceCount; ++f)
    {
        if(!readNextUsefulLine(file, line))
            return false;

        std::stringstream faceStream(line);

        unsigned int n;

        faceStream >> n;

        std::vector<unsigned int> indices(n);

        for(unsigned int i = 0; i < n; ++i)
        {
            faceStream >> indices[i];
        }

        for(unsigned int i = 1; i + 1 < n; ++i)
        {
            triangles.emplace_back(
                indices[0],
                indices[i],
                indices[i + 1]
            );
        }
    }

    if(normals.size() != vertices.size())
    {
        computeNormals(
            vertices,
            triangles,
            normals
        );
    }

    return true;
}
