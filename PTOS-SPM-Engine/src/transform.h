#pragma once

#include "vector.h"

namespace PTOS {

    template<typename T=PTOS_VECTOR_DEFAULT_TYPE>
    struct Transform3 {
        T values[4][4];
        inline T& w() { return values[3][3]; }
    };

    template<typename T=PTOS_VECTOR_DEFAULT_TYPE>
    struct Transform2 {
        T values[3][3];
        inline T& w() { return values[2][2]; }
    };

    //vector3 translation generators

    template<typename T>
    Transform3<T> translate3(T x, T y, T z) {
        //TODO figure out how to set w
        return Transform3<T>{{
            {1, 0, 0, x},
            { 0, 1, 0, y },
            { 0, 0, 1, z },
            { 0, 0, 0, PTOS_VECTOR_UND }
        }};
    }

    template<typename T>
    Transform3<T> scale3(T x, T y, T z) {
        return Transform3<T>{{
            {x, 0, 0, 0},
            {0, y, 0, 0},
            {0, 0, z, 0},
            {0, 0, 0, PTOS_VECTOR_UND}
        }};
    }

    template<typename T>
    Transform3<T> rotateX3(T r) {
        return Transform3<T>{{
            {1, 0, 0, 0},
            {0, cos(r), -sin(r), 0},
            {0, sin(r), cos(r), 0},
            {0, 0, 0, PTOS_VECTOR_UND}
        }};
    }

    template<typename T>
    Transform3<T> rotateY3(T r) {
        return Transform3<T>{{
            {cos(r), 0, sin(r), 0},
            {0, 1, 0, 0},
            {-sin(r), 0, cos(0), 0},
            {0, 0, 0, PTOS_VECTOR_UND}
        }};
    }

    template<typename T>
    Transform3<T> rotateZ3(T r) {
        return Transform3<T>{{
            {cos(r), -sin(r), 0, 0},
            {sin(r), cos(r), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, PTOS_VECTOR_UND}
        }};
    }

    //3d operators

    //transform */+- transform = transform

    template<typename T> Transform3<T> operator+ (Transform3<T>& t1, Transform3<T>& t2) {
        T rtv[4][4] = t1.values;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] += t2.values[i][j];
        if (t1.w() == PTOS_VECTOR_UND && t2.w() != PTOS_VECTOR_UND)
            rtv[3][3] = t2.w();
        return Transform3<T>{rtv};
    }

    template<typename T> Transform3<T> operator- (Transform3<T>& t1, Transform3<T>& t2) {
        T rtv[4][4] = t1.values;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] -= t2.values[i][j];
        if (t1.w() == PTOS_VECTOR_UND && t2.w() != PTOS_VECTOR_UND)
            rtv[3][3] = t2.w();
        return Transform3<T>{rtv};
    }

    template<typename T> Transform3<T> operator* (Transform3<T>& t1, Transform3<T>& t2) {
        T rtv[4][4] = t1.values;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] *= t2.values[i][j];
        if (t1.w() == PTOS_VECTOR_UND && t2.w() != PTOS_VECTOR_UND)
            rtv[3][3] = t2.w();
        return Transform3<T>{rtv};
    }

    template<typename T> Transform3<T> operator/ (Transform3<T>& t1, Transform3<T>& t2) {
        T rtv[4][4] = t1.values;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] /= t2.values[i][j];
        if (t1.w() == PTOS_VECTOR_UND && t2.w() != PTOS_VECTOR_UND)
            rtv[3][3] = t2.w();
        return Transform3<T>{rtv};
    }


    //transform */+- T = transform

    template<typename T> Transform3<T> operator* (Transform3<T>& t1, T& val) {
        T rtv[4][4] = t1.values;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] *= val;

        return Transform3<T>{rtv};
    }

    template<typename T> Transform3<T> operator/ (Transform3<T>& t1, T& val) {
        T rtv[4][4] = t1.values;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] /= val;

        return Transform3<T>{rtv};
    }

    template<typename T> Transform3<T> operator+ (Transform3<T>& t1, T& val) {
        T rtv[4][4] = t1.values;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] += val;

        return Transform3<T>{rtv};
    }

    template<typename T> Transform3<T> operator- (Transform3<T>& t1, T& val) {
        T rtv[4][4] = t1.values;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] -= val;

        return Transform3<T>{rtv};
    }

    template<typename T> Transform3<T> operator* (T& val, Transform3<T>& t1) { return t1 * val; }
    template<typename T> Transform3<T> operator/ (T& val, Transform3<T>& t1) { return t1 * (1 / val); }
    template<typename T> Transform3<T> operator+ (T& val, Transform3<T>& t1) { return t1 + val; }
    template<typename T> Transform3<T> operator- (T& val, Transform3<T>& t1) { return (t1 - val) * -1; }

    //transfotm * vector = vector

    template<typename T> Vector3<T> operator* (Transform3<T>& t, Vector3<T>& v) {
        Vector3<T> rtv = Vector3<T>::zero();
        t.w() = v.w();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rtv.values[i] = t.values[i][j] * v.values[i];
        return rtv;
    }

    template<typename T> Vector3<T> operator* (Vector3<T>& v, Transform3<T>& t) { return t * v; }

    //vector2 translation generators

    template<typename T>
    Transform2<T> translate2(T x, T y) {
        return Transform2<T>{{
            {1, 0, x},
            {0, 1, y},
            {0, 0, PTOS_VECTOR_UND}
        }};
    }

    template<typename T>
    Transform2<T> scale2(T x, T y) {
        return Transform2<T>{{
            {x, 0, 0},
            {0, y, 0},
            {0, 0, PTOS_VECTOR_UND}
        }};
    }

    template<typename T>
    Transform2<T> rotate2(T r) {
        return Transform2<T>{{
            {cos(r), -sin(r), 0},
            {sin(r), cos(r), 0},
            {0, 0, PTOS_VECTOR_UND}
        }};
    }

    //2d operators

    //transform */+- transform = transform

    template<typename T> Transform2<T> operator+ (Transform2<T>& t1, Transform2<T>& t2) {
        T rtv[4][4] = t1.values;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] += t2.values[i][j];
        if (t1.w() == PTOS_VECTOR_UND && t2.w() != PTOS_VECTOR_UND)
            rtv[3][3] = t2.w();
        return Transform2<T>{rtv};
    }

    template<typename T> Transform2<T> operator- (Transform2<T>& t1, Transform2<T>& t2) {
        T rtv[4][4] = t1.values;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] -= t2.values[i][j];
        if (t1.w() == PTOS_VECTOR_UND && t2.w() != PTOS_VECTOR_UND)
            rtv[3][3] = t2.w();
        return Transform2<T>{rtv};
    }

    template<typename T> Transform2<T> operator* (Transform2<T>& t1, Transform2<T>& t2) {
        T rtv[4][4] = t1.values;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] *= t2.values[i][j];
        if (t1.w() == PTOS_VECTOR_UND && t2.w() != PTOS_VECTOR_UND)
            rtv[3][3] = t2.w();
        return Transform2<T>{rtv};
    }

    template<typename T> Transform2<T> operator/ (Transform2<T>& t1, Transform2<T>& t2) {
        T rtv[4][4] = t1.values;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] /= t2.values[i][j];
        if (t1.w() == PTOS_VECTOR_UND && t2.w() != PTOS_VECTOR_UND)
            rtv[3][3] = t2.w();
        return Transform2<T>{rtv};
    }


    //transform */+- T = transform

    template<typename T> Transform2<T> operator* (Transform2<T>& t1, T& val) {
        T rtv[4][4] = t1.values;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] *= val;

        return Transform2<T>{rtv};
    }

    template<typename T> Transform2<T> operator/ (Transform2<T>& t1, T& val) {
        T rtv[4][4] = t1.values;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] /= val;

        return Transform2<T>{rtv};
    }

    template<typename T> Transform2<T> operator+ (Transform2<T>& t1, T& val) {
        T rtv[4][4] = t1.values;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] += val;

        return Transform2<T>{rtv};
    }

    template<typename T> Transform2<T> operator- (Transform2<T>& t1, T& val) {
        T rtv[4][4] = t1.values;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                rtv[i][j] -= val;

        return Transform2<T>{rtv};
    }
    
    template<typename T> Transform2<T> operator* (T& val, Transform2<T>& t1) { return t1 * val; }
    template<typename T> Transform2<T> operator/ (T& val, Transform2<T>& t1) { return t1 * (1 / val); }
    template<typename T> Transform2<T> operator+ (T& val, Transform2<T>& t1) { return t1 + val; }
    template<typename T> Transform2<T> operator- (T& val, Transform2<T>& t1) { return (t1 - val) * -1; }

    //transfotm * vector = vector

    template<typename T> Vector2<T> operator* (Transform2<T>& t, Vector2<T>& v) {
        Vector2<T> rtv = Vector2<T>::zero();
        t.w() = v.w();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rtv.values[i] = t.values[i][j] * v.values[i];
        return rtv;
    }

    template<typename T> Vector2<T> operator* (Vector2<T>& v, Transform2<T>& t) { return t * v; }
}
