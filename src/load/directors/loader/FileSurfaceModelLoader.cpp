#include "FileSurfaceModelLoader.h"
#include <istream>
#include "exceptions/Exceptions.hpp"

#define EPS 1e-6
#define RAD_TO_DEGR (180 / M_PI)

std::string getToken(const std::string str)
{
    std::string res = "";
    if (! str.empty())
        res = str.substr(0, str.find(" "));
    return res;
}

void trimStr(std::string &str)
{
    std::string res = "";
    if (! str.empty())
        str = str.substr(str.find(" "), str.length() - 1);
}


inline std::string firstToken(std::string &str)
{
    std::string res = "";
    if (! str.empty())
    {
        size_t token_start = str.find_first_not_of(" \t");
        size_t token_end = str.find_first_of(" \t", token_start);
        if (token_start != std::string::npos && token_end != std::string::npos)
            res = str.substr(token_start, token_end - token_start);
        else if (token_start != std::string::npos)
            return str.substr(token_start);
    }
    return res;
}

inline std::string tail(const std::string &in)
{
    size_t token_start = in.find_first_not_of(" \t");
    size_t space_start = in.find_first_of(" \t", token_start);
    size_t tail_start = in.find_first_not_of(" \t", space_start);
    size_t tail_end = in.find_last_not_of(" \t");
    if (tail_start != std::string::npos && tail_end != std::string::npos)
        return in.substr(tail_start, tail_end - tail_start + 1);
    else if (tail_start != std::string::npos)
        return in.substr(tail_start);
    return "";
}


std::vector<std::string> splitBySymb(const std::string in, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = in.find(delimiter, pos_start)) != std::string::npos)
    {
        token = in.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (token.length())
            res.push_back(token);
    }

    std::string lastToken = in.substr(pos_start);
    if (!lastToken.empty())
        res.push_back(lastToken);
    return res;
}

std::vector<double> splitStringTriple(const std::string in, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<double> res;

    while ((pos_end = in.find(delimiter, pos_start)) != std::string::npos)
    {
        token = in.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (token.length())
            res.push_back(std::stod(token));
//        res.push_back(std::stod(token));
    }
    std::string lastToken = in.substr(pos_start);
    if (!lastToken.empty())
        res.push_back(std::stod(lastToken));

    return res;
}

//std::vector<double> splitStringToDouble(const std::string& input, const std::string& delimiter)
//{
//    std::vector<double> result;
//    size_t startPos = 0;
//    size_t endPos = input.find(delimiter);
//    while (endPos != std::string::npos)
//    {
//        std::string token = input.substr(startPos, endPos - startPos);
//        if (token.length())
//            result.push_back(std::stod(token));
//        startPos = endPos + delimiter.length();
//        endPos = input.find(delimiter, startPos);
//    }

//    std::string lastToken = input.substr(startPos);
//    if (!lastToken.empty())
//        result.push_back(std::stod(lastToken));

//    return result;
//}


bool checkSide(VecD &point, VecD &a, VecD &b, VecD &c)
{
    // a, b, c - triangle vertices
    bool res = false;

    VecD vec1 = (c - b).VectorProd(point - b);
    VecD vec2 = (c - b).VectorProd(a - b);
    if (vec1.ScalarProd(vec2) >= 0)
        res = true;

    return res;
}

VecD getNormal(VecD &point1, VecD &point2, VecD &point3)
{
    VecD vec1 = point2 - point1;
    VecD vec2 = point3 - point1;

    // векторное произведение двух сторон
    VecD norm = vec1.VectorProd(vec2);
    return norm;
}

bool checkInsideTriangle(VecD point, VecD a, VecD b, VecD c)
{
    bool res = false;

    bool inside_prism = checkSide(point, a, b, c) && checkSide(point, b, a, c) && checkSide(point, c, a, b);

    if (! inside_prism)
        res = false;
    else
    {
        VecD norm = getNormal(a, b, c);
        VecD projection = point.VecProjection(norm);
        if (projection.getLength() < EPS)
            res = true;
    }

    return res;
}

template <typename T>
const T& getElemByInd(const std::vector<T>& elems, int ind)
{
    if (ind < 0)
        ind = (int)elems.size() + ind;
    else
        --ind;
    return elems[ind];
}

FileSurfaceModelLoader::FileSurfaceModelLoader()
{
    _file = std::make_shared<std::ifstream>();
}

FileSurfaceModelLoader::FileSurfaceModelLoader(std::shared_ptr<std::ifstream> &file)
{
    _file = file;
}

void FileSurfaceModelLoader::open()
{
    if (!_file)
    {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }

    _file->open(_fileName);
}

void FileSurfaceModelLoader::close()
{
    if (!_file)
    {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }

    _file->close();
}

std::size_t FileSurfaceModelLoader::loadCount()
{
    int count;

    *_file >> count;

    return count;
}

VecD FileSurfaceModelLoader::loadVec()
{
    double x, y, z;
    *_file >> x >> y >> z;

    return VecD({ x, y, z });
}

std::string FileSurfaceModelLoader::loadMeshName()
{
    bool alreadyRead = false;
    std::string curline, token;
    std::string meshname = "unnamed";

    while (! alreadyRead &&  std::getline(*_file, curline))
    {
        token = firstToken(curline);
        if (token == "o" || token == "g")
        {
            alreadyRead = true;
            trimStr(curline);
            meshname = curline;
        }
    }
    resetFile();
    return meshname;
}

std::vector<VecD> FileSurfaceModelLoader::loadPositions()
{
    std::vector<VecD> Positions;
    bool alreadyRead = false, stop = false;

    std::string curline, token;
    while (! stop && std::getline(*_file, curline))
    {
        token = firstToken(curline);
        if (token == "v")
        {
            alreadyRead = true;
            trimStr(curline);
            std::vector<double> values = splitStringTriple(curline, " ");
            Positions.push_back(VecD({values.at(0), values.at(1), values.at(2)}));
        }
        else if (alreadyRead)
            stop = true;
    }
    resetFile();
    return Positions;
}

std::vector<VecD> FileSurfaceModelLoader::loadTextureCoord()
{
    std::vector<VecD> Coords;
    bool alreadyRead = false, stop = false;

    std::string curline, token;
    while (! stop && std::getline(*_file, curline))
    {
        token = firstToken(curline);
        if (token == "vt")
        {
            alreadyRead = true;
            trimStr(curline);
            std::vector<double> values = splitStringTriple(curline, " ");
            Coords.push_back(VecD({values.at(0), values.at(1)}));
        }
        else if (alreadyRead)
            stop = true;
    }
    resetFile();
    return Coords;
}

std::vector<VecD> FileSurfaceModelLoader::loadNormals()
{
    std::vector<VecD> Normals;
    bool alreadyRead = false, stop = false;

    std::string curline, token;
    while (! stop && std::getline(*_file, curline))
    {
        token = firstToken(curline);
        if (token == "vn")
        {
            alreadyRead = true;
            trimStr(curline);
            std::vector<double> values = splitStringTriple(curline, " ");
            Normals.push_back(VecD({values.at(0), values.at(1), values.at(2)}));
        }
        else if (alreadyRead)
            stop = true;
    }
    resetFile();
    return Normals;
}

inline std::vector<Vertex> getVertices(const std::vector<VecD> &positions, const std::vector<VecD> &texCoords,
                                       const std::vector<VecD> &normals, std::string &curline)
{
    std::vector<std::string> faces = splitBySymb(curline, " ");
    std::vector<Vertex> vertices;
    bool hasNormal = true;

    for (int i = 0; i < (int)faces.size(); i++)
    {
        std::vector<std::string> indices = splitBySymb(faces[i], "/");


        if (indices.size() < 0 || indices.size() > 4)
        {
            std::string msg = "Ошибка модели OBJ файла";
            throw ModelException(msg);
        }

        Vertex curVertex;
        curVertex.setPosition(getElemByInd(positions, std::stod(indices[0]))); // !! ТАК КАК В OBJ НАЧИНАЕТСЯ С 1
        curVertex.setColor(VecD{0.5, 0.5, 0.5});
        curVertex.setU(0);
        curVertex.setV(0);

        if (indices.size() == 1) // P
            hasNormal = false;
        else if (indices.size() == 2) // P/T
        {
            auto tmp = getElemByInd(texCoords, std::stod(indices[1]));
            curVertex.setU(tmp.getX());
            curVertex.setV(tmp.getY());
//            curVertex.setColor();
            hasNormal = false;
        }
        else if (indices.size() == 3) // P//N
        {
            curVertex.setNormal(getElemByInd(normals, std::stod(indices[2])));
            if (indices[1] == "") // P/T/N
            {
                auto tmp = getElemByInd(texCoords, std::stod(indices[1]));
                curVertex.setU(tmp.getX());
                curVertex.setV(tmp.getY());
            }
        }
        vertices.push_back(curVertex);
    }

    if (! hasNormal)
    {
        for (int i = 0; i < (int)vertices.size() / 3; i++)
        {

            VecD side1 = vertices[(3 * i + 1) % 3].getPosition() - vertices[(3 * i) % 3].getPosition();
            VecD side2 = vertices[(3 * i + 2) % 3].getPosition() - vertices[(3 * i) % 3].getPosition();

            VecD normal = side1.VectorProd(side2);

            for (int j = i ; j < i + 3; j++)
                vertices[j].setNormal(normal);
        }

    }

    return vertices;
}

std::vector<unsigned int> FileSurfaceModelLoader::loadIndices(std::vector<Vertex> &vertices)
{
    bool err = 0;
    std::vector<unsigned int> indices;
    if (vertices.size() < 3)
        err = 1;
    if (! err && vertices.size() == 3)
    {
        err = 1;
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
    }

    if (! err)
    {
        std::vector<Vertex> tmpVerts = vertices;
        while (tmpVerts.size() > 0)
        {
            for (unsigned long i = 0; i < tmpVerts.size(); i++)
            {
                Vertex prevVert;
                Vertex nextVert = tmpVerts[i + 1];
                Vertex curVert = tmpVerts[i];
                if (i == 0)
                    prevVert = tmpVerts[tmpVerts.size() - 1];
                else
                {
                    prevVert = tmpVerts[i - 1];
                    if (i == tmpVerts.size() - 1)
                        nextVert = tmpVerts[0];
                }

                VecD curPos = curVert.getPosition();
                VecD prevPos = prevVert.getPosition();
                VecD nextPos = nextVert.getPosition();

                if (tmpVerts.size() == 3 || tmpVerts.size() == 4)
                {
                    int arrSize = tmpVerts.size();
                    if (tmpVerts.size() == 4)
                        arrSize = vertices.size();

                    for (int j = 0; j < arrSize; j++)
                    {
                        if (vertices[j].getPosition() == curPos)
                            indices.push_back(j);
                        if (vertices[j].getPosition() == prevPos)
                            indices.push_back(j);
                        if (vertices[j].getPosition() == nextPos)
                            indices.push_back(j);
                    }

                    if (tmpVerts.size() == 4)
                    {
                        VecD tmpVec = {0, 0, 0};
                        for (int j = 0; j < int(tmpVerts.size()); j++)
                        {
                            auto tmp = tmpVerts[j].getPosition();
                            if (tmpVerts[j].getPosition() != curPos && tmpVerts[j].getPosition() != prevPos && tmpVerts[j].getPosition() != nextPos)
                            if (tmp != curPos)
                            {
                                tmpVec = tmpVerts[j].getPosition();
                                break;
                            }
                        }

                        for (int j = 0; j < int(vertices.size()); j++)
                        {
                            if (vertices[j].getPosition() == prevPos)
                                indices.push_back(j);
                            if (vertices[j].getPosition() == nextPos)
                                indices.push_back(j);
                            if (vertices[j].getPosition() == tmpVec)
                                indices.push_back(j);
                        }
                    }

                    tmpVerts.clear();
                    break;
                }

                double angle = (prevPos - curPos).AngleBetweenVecs(nextPos - curPos);
                angle *= RAD_TO_DEGR;
                if (angle >= 180 && angle <= 0)
                    continue;

                bool inTriangle = false;
                for (unsigned long j = 0; j < vertices.size(); j++)
                {
                    if (checkInsideTriangle(vertices[j].getPosition(), prevPos,
                                            curPos, nextPos) &&
                        vertices[j].getPosition() != prevPos &&
                        vertices[j].getPosition() != curPos &&
                        vertices[j].getPosition() != nextPos)
                    {
                        inTriangle = true;
                        break;
                    }
                }
                if (inTriangle)
                    continue;

                for (unsigned long j = 0; j < vertices.size(); j++)
                {
                    if (vertices[j].getPosition() != prevPos)
                        indices.push_back(j);
                    if (vertices[j].getPosition() != curPos)
                        indices.push_back(j);
                    if (vertices[j].getPosition() != nextPos)
                        indices.push_back(j);
                }

                for (unsigned long j = 0; j < vertices.size(); j++)
                {
                    if (tmpVerts[j].getPosition() == curPos)
                    {
                        tmpVerts.erase(tmpVerts.begin() + j);
                        break;
                    }
                }

                i = -1;
            }
            if (indices.size() == 0)
                break;
        }
    }

    return indices;
}

std::vector<Vertex> FileSurfaceModelLoader::loadVertices(std::vector<unsigned int> &indices)
{
    bool alreadyRead = false, stop = false;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> tmpIndices;

    const std::vector<VecD> &positions = loadPositions();
    const std::vector<VecD> &texCoords = loadTextureCoord();
    const std::vector<VecD> &normals = loadNormals();

    std::vector<Vertex> tmpVerts;
    std::string curline, token;
    while (! stop && std::getline(*_file, curline))
    {
        token = firstToken(curline);
        if (token == "f")
        {
            trimStr(curline);
            alreadyRead = true;
            tmpVerts = getVertices(positions, texCoords, normals, curline);
            for (int i = 0; i < int(tmpVerts.size()); i++)
                vertices.push_back(tmpVerts[i]);

           tmpIndices = loadIndices(tmpVerts);

           for (int i = 0; i < int(tmpIndices.size()); i++)
           {
               unsigned int indnum = (unsigned int)((vertices.size()) - tmpVerts.size()) + tmpIndices[i];
               indices.push_back(indnum);
           }
        }
        else if (alreadyRead)
            stop = true;
    }
    resetFile();
    return vertices;
}

void setKValues(Material &material, std::string &token, VecD &Values)
{
    if (token == "Ka")
        material.setKa(Values);
    if (token == "Kd")
        material.setKd(Values);
    if (token == "Ks")
        material.setKs(Values);
}

void setNdValue(Material &material, std::string &token, std::string &val)
{
    if (token == "illum")
    {
        int res = std::stoi(val);
        material.setIllum(res);
    }
    else
    {
        double res = std::stod(val);
        if (token == "Ns")
            material.setNs(res);
        if (token == "Ni")
            material.setNi(res);
        if (token == "d")
            material.setDissolve(res);
    }
}

Material FileSurfaceModelLoader::loadMaterial()
{
    std::string curline, token;
    std::string path;
    Material new_mat;

    if (std::getline(*_file, curline))
    {
        token = firstToken(curline);
        if (token == "mtllib")
        {
            std::vector<std::string> temp = splitBySymb(_fileName, "/");
            if (temp.size() != 1)
            {
                path += "/";
                for (int i = 0; i < (int) temp.size() - 1; i++)
                    path += temp[i] + "/";
            }
            path += tail(curline);
        }
    }

    std::ifstream material_file;
    material_file.open(path);
    while (std::getline(material_file, curline))
    {
        token = firstToken(curline);
        trimStr(curline);
        if (token == "newmtl")
            new_mat.setMaterialName(curline);
        if (token == "Ka" || token == "Kd" || token == "Ks")
        {
            std::vector<std::string> tmp = splitBySymb(curline, " ");
            VecD resVec = {std::stod(tmp[0]), std::stod(tmp[1]), std::stod(tmp[2])};
            setKValues(new_mat, token, resVec);
        }
        if (token == "Ns" || token == "Ni" || token == "d" || token == "illum")
            setNdValue(new_mat, token, curline);
        if (token == "map_Ka")
            new_mat.setMap_Ka(curline);
        if (token == "map_Kd")
            new_mat.setMap_Kd(curline);
        if (token == "map_Ks")
            new_mat.setMap_Ks(curline);
        if (token == "map_Ns")
            new_mat.setMap_Ns(curline);
        if (token == "map_d")
            new_mat.setMap_alpha(curline);
        if (token == "map_bump")
            new_mat.setMap_bump(curline);
    }
    resetFile();
    material_file.close();
    return new_mat;
}

std::vector<Face> FileSurfaceModelLoader::loadFaces(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
    std::vector<Face> faces;

    for (int i = 0; i < (int) indices.size() / 3; i++)
    {
        int ind = i * 3;
        faces.push_back(Face(vertices[indices[ind]],
                        vertices[indices[ind + 1]],
                        vertices[indices[ind + 2]]));
        auto& f = faces.back();
        f.setNormal((f.getB().getPosition() - f.getA().getPosition()).VectorProd(f.getC().getPosition() - f.getA().getPosition()));

    }
    return faces;
}


void FileSurfaceModelLoader::setFileName(std::string &fileName)
{
    _fileName = fileName;
}

//
std::vector<VecD> FileSurfaceModelLoader::loadStuff(const std::string &token)
{
    std::vector<VecD> Stuff;
    float x, y, z;

    std::string curline, cer_token;
    while (std::getline(*_file, curline) && getToken(curline) == token) // заменить на gettoken
    {
        *_file >> cer_token >> x >> y >> z;
        Stuff.push_back(VecD({x, y, z}));
    }
    resetFile();
    return Stuff;
}
//

void FileSurfaceModelLoader::resetFile()
{
    _file->clear();
    _file->seekg(0, _file->beg);
}
