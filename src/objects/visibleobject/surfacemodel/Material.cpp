#include "Material.h"

Material::Material()
{
    Ns = 0.f;
    Ni = 0.f;
    dissolve = 0.f;
    illum = 0;
}

Material &Material::operator=(Material &&material) noexcept
{
    setMaterialName(material.materialName);
    setKa(material.Ka);
    setKd(material.Kd);
    setKs(material.Ks);

    setNs(material.Ns);
    setNi(material.Ni);

    setDissolve(material.dissolve);
    setIllum(material.illum);

    setMap_Ka(material.map_Ka);
    setMap_Kd(material.map_Kd);
    setMap_Ks(material.map_Ks);
    setMap_Ns(material.map_Ns);
    setMap_alpha(material.map_alpha);
    setMap_bump(material.map_bump);

    material.~Material();

    return *this;
}

void Material::setMaterialName(std::string &name)
{
    materialName = name;
}

void Material::setKa(VecD &newKa)
{
    Ka = newKa;
}
void Material::setKd(VecD &newKd)
{
    Kd = newKd;
}
void Material::setKs(VecD &newKs)
{
    Ks = newKs;
}

void Material::setNs(double &newNs)
{
    Ns = newNs;
}

void Material::setNi(double &newNi)
{
    Ni = newNi;
}

void Material::setDissolve(double &new_dissolve)
{
    dissolve = new_dissolve;
}

void Material::setIllum(int &new_illum)
{
    illum = new_illum;
}

void Material::setMap_Ka(std::string &newMap)
{
    map_Ka = newMap;
}

void Material::setMap_Kd(std::string &newMap)
{
    map_Kd = newMap;
}

void Material::setMap_Ks(std::string &newMap)
{
    map_Ks = newMap;
}

void Material::setMap_Ns(std::string &newMap)
{
    map_Ns = newMap;
}

void Material::setMap_alpha(std::string &newMap)
{
    map_alpha = newMap;
}

void Material::setMap_bump(std::string &newMap)
{
    map_bump = newMap;
}

std::string Material::getMaterialName(void)
{
    return materialName;
}

VecD Material::getKa(void)
{
    return Ka;
}
VecD Material::getKd(void)
{
    return Kd;
}
VecD Material::getKs(void)
{
    return Ks;
}

double Material::getNs(void)
{
    return Ns;
}

double Material::getNi(void)
{
    return Ni;
}

double Material::getDissolve(void)
{
    return dissolve;
}

int Material::getIllum(void)
{
    return illum;
}


std::string Material::getMap_Ka(void)
{
    return map_Ka;
}
std::string Material::getMap_Kd(void)
{
    return map_Kd;
}
std::string Material::getMap_Ks(void)
{
    return map_Ks;
}
std::string Material::getMap_Ns(void)
{
    return map_Ns;
}

std::string Material::getMap_alpha(void)
{
    return map_alpha;
}
std::string Material::getMap_bump(void)
{
    return map_bump;
}

void Material::setSpecularity(const double &new_spec)
{
    specularity = new_spec;
}
void Material::setReflectivity(const double &new_reflect)
{
    reflectivity = new_reflect;
}
void Material::setRefraction(const double &new_refract)
{
    refraction = new_refract;
}


double Material::getSpecularity() const
{
    return specularity;
}

double Material::getReflectivity() const
{
    return reflectivity;
}

double Material::getRefraction() const
{
    return refraction;
}
