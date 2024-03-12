#include <BaseObject.h>

std::size_t BaseObject::_nextId = 1;

void BaseObject::setMoveCoefs(const double &x, const double &y, const double &z)
{
    move_x = x;
    move_y = y;
    move_z = z;
}

void BaseObject::setScaleCoefs(const double &x, const double &y, const double &z)
{
    scale_x = x;
    scale_y = y;
    scale_z = z;
}

void BaseObject::setRotateCoefs(const double &x, const double &y, const double &z)
{
    angle_x = x;
    angle_y = y;
    angle_z = z;

    Transform rotate;
    rotate.setRotate(x, y, z);

    rotation = rotation * rotate;
}

Transform BaseObject::getObjToWorld()
{
    if (scale_x == 0 && scale_y == 0 && scale_z == 0)
    {
        scale_x = 1;
        scale_y = 1;
        scale_z = 1;
    }
    Transform scale;
    scale.setScale(scale_x, scale_y, scale_z);

    Transform move;
    move.setMove(move_x, move_y, move_z);


    Transform res;
    res.setToWorld(move, scale, rotation);

    return res;
}

Transform BaseObject::getRotationMatrix()
{
    return rotation;
}
