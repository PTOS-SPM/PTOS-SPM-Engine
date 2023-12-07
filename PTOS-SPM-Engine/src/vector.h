#pragma once

#define PTOS_VECTOR_POS 1
#define PTOS_VECTOR_DIR 0
#define PTOS_VECTOR_UND -1
#define PTOS_VECTOR_DEFAULT_TYPE double

namespace PTOS {

    template<typename T=PTOS_VECTOR_DEFAULT_TYPE>
    struct Vector3 {

        inline static Vector3<T> zero() { return Vector3<T>(0, 0, 0); }
        inline static Vector3<T> one() { return Vector3<T>(1, 1, 1); }
        inline static Vector3<T> of(const T& value) { return Vector3<T>(value, value, value); }
        //cite: https://stackoverflow.com/a/30011781    where alpha=hdegrees, beta=vdegrees
        inline static Vector3<T> ofAngle(const T& hdegrees, const T& vdegrees) {
            return Vector3<T>(
                (T)(cos(hdegrees) * cos(vdegrees)),
                (T)sin(vdegrees),
                (T)(sin(hdegrees) * cos(vdegrees)),
                PTOS_VECTOR_DIR
            );
        }
        inline static Vector3<T> forward() { return Vector3<T>(0, 0, 1, PTOS_VECTOR_DIR); }
        inline static Vector3<T> backward() { return Vector3<T>(0, 0, -1, PTOS_VECTOR_DIR); }
        inline static Vector3<T> right() { return Vector3<T>(1, 0, 0, PTOS_VECTOR_DIR); }
        inline static Vector3<T> left() { return Vector3<T>(-1, 0, 0, PTOS_VECTOR_DIR); }
        inline static Vector3<T> up() { return Vector3<T>(0, 1, 0, PTOS_VECTOR_DIR); }
        inline static Vector3<T> down() { return Vector3<T>(0, -1, 0, PTOS_VECTOR_DIR); }

        Vector3(T x, T y, T z, T w) { this->x() = x; this->y() = y; this->z() = z; this->w() = w; }
        Vector3(T x, T y, T z) : Vector3(x, y, z, PTOS_VECTOR_POS) {}

        T values[4];

        inline T& x() { return values[0]; }
        inline T& y() { return values[1]; }
        inline T& z() { return values[2]; }
        inline T& w() { return values[3]; }

        Vector3<T> normalize() {
            T sum = x() + y() + z();
            return Vector3<T>(x() / sum, y() / sum, z() / sum, PTOS_VECTOR_DIR);
        }
    };

    template<typename T=PTOS_VECTOR_DEFAULT_TYPE>
    struct Vector2 {
        inline static Vector2<T> zero() { return Vector2<T>(0, 0); }
        inline static Vector2<T> one() { return Vector2<T>(1, 1); }
        inline static Vector2<T> of(const T& value) { return Vector2<T>(value, value, value); }
        inline static Vector2<T> ofAngle(const T& degrees) { return Vector2<T>((T)cos(degrees), (T)sin(degrees), PTOS_VECTOR_DIR); }
        inline static Vector2<T> right() { return Vector2<T>(1, 0, PTOS_VECTOR_DIR); }
        inline static Vector2<T> left() { return Vector2<T>(-1, 0, PTOS_VECTOR_DIR); }
        inline static Vector2<T> up() { return Vector2<T>(0, 1, PTOS_VECTOR_DIR); }
        inline static Vector2<T> down() { return Vector2<T>(0, -1, PTOS_VECTOR_DIR); }

        Vector2(T x, T y, T w) { this->x() = x; this->y() = y; this->w() = w; }
        Vector2(T x, T y) : Vector2(x, y, PTOS_VECTOR_POS) {}

        T values[3];

        inline T& x() { return values[0]; }
        inline T& y() { return values[1]; }
        inline T& w() { return values[2]; }

        Vector2<T> normalize() {
            T sum = x() + y();
            return Vector2<T>(x() / sum, y() / sum, PTOS_VECTOR_DIR);
        }
    };

    //3d operators

    template<typename T> Vector3<T> operator* (Vector3<T>& v1, Vector3<T>& v2) {
        return Vector3<T>(
            v1.x() * v2.x(),
            v1.y() * v2.y(),
            v1.z() * v2.z(),
            v1.w() * v2.w()
        );
    }

    template<typename T> Vector3<T> operator/ (Vector3<T>& v1, Vector3<T>& v2) {
        return Vector3<T>(
            v1.x() / v2.x(),
            v1.y() / v2.y(),
            v1.z() / v2.z(),
            PTOS_VECTOR_DIR
        );
    }

    template<typename T> Vector3<T> operator+ (Vector3<T>& v1, Vector3<T>& v2) {
        return Vector3<T>(
            v1.x() + v2.x(),
            v1.y() + v2.y(),
            v1.z() + v2.z(),
            v1.w() || v2.w()
        );
    }

    template<typename T> Vector3<T> operator- (Vector3<T>& v1, Vector3<T>& v2) {
        return Vector3<T>(
            v1.x() - v2.x(),
            v1.y() - v2.y(),
            v1.z() - v2.z(),
            v1.w() || v2.w()
        );
    }

    //2d operators

    template<typename T> Vector2<T> operator* (Vector2<T>& v1, Vector2<T>& v2) {
        return Vector2<T>(
            v1.x() * v2.x(),
            v1.y() * v2.y(),
            v1.w() * v2.w()
        );
    }

    template<typename T> Vector2<T> operator/ (Vector2<T>& v1, Vector2<T>& v2) {
        return Vector2<T>(
            v1.x() / v2.x(),
            v1.y() / v2.y(),
            PTOS_VECTOR_DIR
        );
    }

    template<typename T> Vector2<T> operator+ (Vector2<T>& v1, Vector2<T>& v2) {
        return Vector2<T>(
            v1.x() + v2.x(),
            v1.y() + v2.y(),
            v1.w() || v2.w()
        );
    }

    template<typename T> Vector2<T> operator- (Vector2<T>& v1, Vector2<T>& v2) {
        return Vector2<T>(
            v1.x() - v2.x(),
            v1.y() - v2.y(),
            v1.w() || v2.w()
        );
    }

}
