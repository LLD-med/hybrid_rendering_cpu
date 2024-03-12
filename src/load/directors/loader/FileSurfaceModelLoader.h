#ifndef FILESURFACEMODELLOADER_H
#define FILESURFACEMODELLOADER_H

#include <fstream>
#include <BaseLoader.h>

class FileSurfaceModelLoader : public BaseLoader
{
public:
    FileSurfaceModelLoader();
    FileSurfaceModelLoader(std::shared_ptr<std::ifstream> &file);

    virtual void open() override;
    virtual void close() override;
    void setFileName(std::string &fileName) override;

    virtual std::size_t loadCount() override;
    virtual VecD loadVec() override;

    virtual std::string loadMeshName() override;
    std::vector<Vertex> loadVertices(std::vector<unsigned int> &indices) override;
//    virtual std::vector<Vertex> loadVertices() override;
    virtual std::vector<unsigned int> loadIndices(std::vector<Vertex> &vertices) override;
    virtual Material loadMaterial() override;
    virtual std::vector<Face> loadFaces(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) override;
private:
    std::vector<VecD> loadPositions();
    std::vector<VecD> loadTextureCoord();
    std::vector<VecD> loadNormals();
    std::vector<VecD> loadStuff(const std::string &stuff); // чтобы не было повтора

    void resetFile();

private:
    std::shared_ptr<std::ifstream> _file;
    std::string _fileName;
};

#endif // FILESURFACEMODELLOADER_H
