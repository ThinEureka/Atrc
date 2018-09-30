#pragma once

#include <Atrc/Common.h>
#include <Atrc/Math/Ray.h>

AGZ_NS_BEG(Atrc)

class Transform
{
    Mat4r mat_, inv_;

public:

    struct FromInv_t { };

    static Transform Translate(const Vec3r &v);
    static Transform Rotate(const Vec3r &axis, Radr angle);
    static Transform RotateX(Radr angle);
    static Transform RotateY(Radr angle);
    static Transform RotateZ(Radr angle);
    static Transform Scale(const Vec3r &s);
    static Transform ScaleX(Real s);
    static Transform ScaleY(Real s);
    static Transform ScaleZ(Real s);

    Transform();

    explicit Transform(const Mat4r &mat);

    Transform(const Mat4r &mat, const Mat4r &inv);

    Transform(FromInv_t, const Mat4r &inv);

    Transform operator*(const Transform &rhs) const;

    Transform Inverse() const;

    Vec3r ApplyToPoint(const Vec3r &p) const;
    Vec3r ApplyInverseToPoint(const Vec3r &p) const;

    Vec3r ApplyToVector(const Vec3r &v) const;
    Vec3r ApplyInverseToVector(const Vec3r &v) const;

    Vec3r ApplyToNormal(const Vec3r &n) const;
    Vec3r ApplyInverseToNormal(const Vec3r &n) const;

    Ray ApplyToRay(const Ray &r) const;
    Ray ApplyInverseToRay(const Ray &r) const;

    Intersection ApplyToIntersection(const Intersection &inct) const;
    Intersection ApplyInverseToIntersection(const Intersection &inct) const;
};

inline Transform::FromInv_t FROM_INV;

inline Transform TRANSFORM_IDENTITY(Mat4r::IDENTITY());

inline Transform Transform::Translate(const Vec3r &v)
{
    return Transform(Mat4r::Translate(v), Mat4r::Translate(-v));
}

inline Transform Transform::Rotate(const Vec3r &axis, Radr angle)
{
    return Transform(Mat4r::Rotate(axis, angle), Mat4r::Rotate(axis, -angle));
}

inline Transform Transform::RotateX(Radr angle)
{
    Mat4r m = Mat4r::RotateX(angle);
    return Transform(m, m.Transpose());
}

inline Transform Transform::RotateY(Radr angle)
{
    Mat4r m = Mat4r::RotateY(angle);
    return Transform(m, m.Transpose());
}

inline Transform Transform::RotateZ(Radr angle)
{
    Mat4r m = Mat4r::RotateZ(angle);
    return Transform(m, m.Transpose());
}

inline Transform Transform::Scale(const Vec3r &s)
{
    Vec3r invS(Real(1) / s.x, Real(1) / s.y, Real(1) / s.z);
    return Transform(Mat4r::Scale(s), Mat4r::Scale(invS));
}

inline Transform Transform::ScaleX(Real s)
{
    Vec3r SV(s, Real(1), Real(1)), invSV(Real(1) / s, Real(1), Real(1));
    return Transform(Mat4r::Scale(SV), Mat4r::Scale(invSV));
}

inline Transform Transform::ScaleY(Real s)
{
    Vec3r SV(Real(1), s, Real(1)), invSV(Real(1), Real(1) / s, Real(1));
    return Transform(Mat4r::Scale(SV), Mat4r::Scale(invSV));
}

inline Transform Transform::ScaleZ(Real s)
{
    Vec3r SV(Real(1), Real(1), s), invSV(Real(1), Real(1), Real(1) / s);
    return Transform(Mat4r::Scale(SV), Mat4r::Scale(invSV));
}

inline Transform::Transform()
    : mat_(Real(1)), inv_(Real(1))
{

}

inline Transform::Transform(const Mat4r &mat)
    : mat_(mat), inv_(mat.Inverse())
{

}

inline Transform::Transform(const Mat4r &mat, const Mat4r &inv)
    : mat_(mat), inv_(inv)
{

}

inline Transform::Transform(FromInv_t, const Mat4r &inv)
    : mat_(inv.Inverse()), inv_(inv)
{

}

inline Transform Transform::operator*(const Transform &rhs) const
{
    return Transform(mat_ * rhs.mat_, rhs.inv_ * inv_);
}

inline Transform Transform::Inverse() const
{
    return Transform(inv_, mat_);
}

inline Vec3r Transform::ApplyToPoint(const Vec3r &p) const
{
    return mat_.ApplyToPoint(p);
}

inline Vec3r Transform::ApplyInverseToPoint(const Vec3r &p) const
{
    return inv_.ApplyToPoint(p);
}

inline Vec3r Transform::ApplyToVector(const Vec3r &v) const
{
    return mat_.ApplyToVector(v);
}

inline Vec3r Transform::ApplyInverseToVector(const Vec3r &v) const
{
    return inv_.ApplyToVector(v);
}

inline Vec3r Transform::ApplyToNormal(const Vec3r &n) const
{
    return inv_.ApplyInverseToNormal(n).Normalize();
}

inline Vec3r Transform::ApplyInverseToNormal(const Vec3r &n) const
{
    return mat_.ApplyInverseToNormal(n).Normalize();
}

inline Ray Transform::ApplyToRay(const Ray &r) const
{
    return Ray(
        ApplyToPoint(r.origin),
        ApplyToVector(r.direction),
        r.minT, r.maxT);
}

inline Ray Transform::ApplyInverseToRay(const Ray &r) const
{
    return Ray(
        ApplyInverseToPoint(r.origin),
        ApplyInverseToVector(r.direction),
        r.minT, r.maxT);
}

inline Intersection Transform::ApplyToIntersection(const Intersection &inct) const
{
    return Intersection{
        ApplyToVector(inct.wr),
        ApplyToPoint(inct.pos),
        ApplyToNormal(inct.nor),
        inct.t, inct.entity, inct.flag
    };
}

inline Intersection Transform::ApplyInverseToIntersection(const Intersection &inct) const
{
    return Intersection{
        ApplyInverseToVector(inct.wr),
        ApplyInverseToPoint(inct.pos),
        ApplyInverseToNormal(inct.nor),
        inct.t, inct.entity, inct.flag
    };
}

AGZ_NS_END(Atrc)