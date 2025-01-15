#pragma once


#include "Maths.h"


struct vec2 { float x, y; };
struct vec3 { float x, y, z; };
struct vec4 { float x, y, z, w; };


class Vector3
{

public:

    float* x;
    float* y;
    float* z;

    Vector3(float* _x = nullptr, float* _y = nullptr, float* _z = nullptr)
    {
        if (!_x)
            x = new float;
        else
            x = _x;

        if (!_y)
            y = new float;
        else
            y = _y;

        if (!_z)
            z = new float;
        else
            z = _z;
    }

    Vector3(float _x, float _y, float _z)
    {
        x = new float;
        y = new float;
        z = new float;

        *x = _x;
        *y = _y;
        *z = _z;
    }

    Vector3 operator+(Vector3& _vec)
    {
        Vector3 v;
        *v.x = (*this->x) + (*_vec.x);
        *v.y = (*this->y) + (*_vec.y);
        *v.z = (*this->z) + (*_vec.z);

        return v;
    };

    Vector3 operator-(Vector3& _vec)
    {
        Vector3 v;
        *v.x = (*this->x) - (*_vec.x);
        *v.y = (*this->y) - (*_vec.y);
        *v.z = (*this->z) - (*_vec.z);

        return v;
    };

    Vector3 operator/(Vector3& _vec)
    {
        Vector3 v;
        *v.x = (*this->x) / (*_vec.x);
        *v.y = (*this->y) / (*_vec.y);
        *v.z = (*this->z) / (*_vec.z);

        return *this;
    };
    Vector3 operator*(Vector3& _vec)
    {
        Vector3 v;
        *v.x = (*this->x) * (*_vec.x);
        *v.y = (*this->y) * (*_vec.y);
        *v.z = (*this->z) * (*_vec.z);

        return *this;
    };




    Vector3 operator+=(Vector3& _vec)
    {
        *(this->x) += *(_vec.x);
        *(this->y) += *(_vec.y);
        *(this->z) += *(_vec.z);

        return *this;
    };

    Vector3 operator=(Vector3& _vec)
    {
        delete x, y, z;

        this->x = _vec.x;
        this->y = _vec.y;
        this->z = _vec.z;

        return *this;
    };

    Vector3 operator-=(Vector3& _vec)
    {
        *(this->x) -= *(_vec.x);
        *(this->y) -= *(_vec.y);
        *(this->z) -= *(_vec.z);

        return *this;
    };

    Vector3 operator*=(Vector3& _vec)
    {

        *this->x *= *_vec.x;
        *this->y *= *_vec.y;
        *this->z *= *_vec.z;

        return *this;
    };

    Vector3 operator/=(Vector3& _vec)
    {
        *this->x /= *_vec.x;
        *this->y /= *_vec.y;
        *this->z /= *_vec.z;

        return *this;
    };

    vec3 GetValuePointed()
    {
        return vec3{ *this->x,*this->y,*this->z };
    }

    void SetX(float _x)
    {
        *this->x = _x;
    }

    void SetY(float _y)
    {
        *this->y = _y;
    }

    void SetZ(float _z)
    {
        *this->z = _z;
    }

    void SetXYZ(float _x, float _y, float _z)
    {
        *this->x = _x;
        *this->y = _y;
        *this->z = _z;
    }

    static float magnitude(vec3 src, vec3 point)
    {
        float pow_x = pow((src.x - point.x), 2);
        float pow_y = pow((src.y - point.y), 2);
        float pow_z = pow((src.z - point.z), 2);

        return sqrtf(pow_x + pow_y + pow_z);
    }
};

