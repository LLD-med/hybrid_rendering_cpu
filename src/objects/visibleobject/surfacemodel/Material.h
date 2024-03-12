#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "Vector.hpp"

class Material
{
public:
    Material();

    Material(const Material &material) = default;

    Material &operator=(const Material &material) = default;
    Material &operator=(Material &&material) noexcept;

    ~Material() = default;

    void setMaterialName(std::string &name);

    void setKa(VecD &newKa);
    void setKd(VecD &newKd);
    void setKs(VecD &newKs);

    void setNs(double &newNs);
    void setNi(double &newNi);
    void setDissolve(double &new_dissolve);
    void setIllum(int &new_illum);

    void setMap_Ka(std::string &newMap);
    void setMap_Kd(std::string &newMap);
    void setMap_Ks(std::string &newMap);
    void setMap_Ns(std::string &newMap);

    void setMap_alpha(std::string &newMap);
    void setMap_bump(std::string &newMap);

    std::string getMaterialName();

    VecD getKa();
    VecD getKd();
    VecD getKs();

    double getNs();
    double getNi();
    double getDissolve();
    int getIllum();

    std::string getMap_Ka();
    std::string getMap_Kd();
    std::string getMap_Ks();
    std::string getMap_Ns();

    std::string getMap_alpha();
    std::string getMap_bump();

    void setSpecularity(const double &new_spec);
    void setReflectivity(const double &new_reflect);
    void setRefraction(const double &new_refract);

    double getSpecularity() const;
    double getReflectivity() const;
    double getRefraction() const;

private:
    std::string materialName;

    VecD Ka; // Ambiemt color
    VecD Kd; // Diffuse color
    VecD Ks; // Specular color

    // зеркальность
    double specularity = 0.;
    // отражение
    double reflectivity = 0.;
    // преломление
    double refraction = 0.;

    double Ns;
    double Ni; // Optical density
    double dissolve;
    int illum;

    std::string map_Ka;
    std::string map_Kd;
    std::string map_Ks;
    std::string map_Ns;

    std::string map_alpha;
    std::string map_bump;

};

#endif // MATERIAL_H
