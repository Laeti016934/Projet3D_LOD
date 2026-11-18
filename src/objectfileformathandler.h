#pragma once

//Saves or loads an Object File Format (.off) file.
//OFF files are used to store meshes.

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "triangle.h"

bool saveOFF( const std::string& filename ,
              std::vector<glm::vec3>& i_vertices ,
              std::vector<glm::vec3>& i_normals ,
              std::vector<Triangle>& i_triangles,
              bool save_normals = true );


bool openOFF( const std::string& filename,
              std::vector<glm::vec3>& vertices,
              std::vector<glm::vec3>& normals,
              std::vector<Triangle>& triangles,
              bool loadNormals=true);
