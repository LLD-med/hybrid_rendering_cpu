#ifndef BASELOADER_H
#define BASELOADER_H

#include "Material.h"
#include "Face.h"
#include "Vertex.h"
#include <string>
#include <vector>

class BaseLoader
{
public:
    BaseLoader() = default;
    virtual ~BaseLoader() = default;

    virtual void open() = 0;
    virtual void close() = 0;

    virtual std::size_t loadCount() = 0;
    virtual VecD loadVec() = 0;

    virtual std::string  loadMeshName() = 0;
    virtual std::vector<Vertex> loadVertices(std::vector<unsigned int> &indices) = 0;
    virtual std::vector<unsigned int> loadIndices(std::vector<Vertex> &vertices) = 0;
    virtual Material loadMaterial() = 0;
    virtual std::vector<Face> loadFaces(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) = 0;

    virtual void setFileName(std::string &fileName) = 0;
};

#endif // BASELOADER_H
