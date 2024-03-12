#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"

class Mesh
{
public:
    Mesh() = default;
    Mesh(std::string meshName, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
    {
        _meshName = meshName;
        _vertices = vertices;
        _indices = indices;
    }

    std::vector<Vertex> getVertices() { return _vertices; };

private:
    std::string _meshName;
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;

};

#endif // MESH_H
