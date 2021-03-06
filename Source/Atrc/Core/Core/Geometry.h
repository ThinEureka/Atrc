#pragma once

#include <Atrc/Core/Core/AABB.h>
#include <Atrc/Core/Core/SurfacePoint.h>
#include <Atrc/Core/Core/Transform.h>

namespace Atrc
{

class Geometry
{
protected:

    Transform local2World_;

public:

    explicit Geometry(const Transform &transform) noexcept;

    virtual ~Geometry() = default;

    virtual bool HasIntersection(const Ray &r) const noexcept = 0;

    virtual bool FindIntersection(const Ray &r, GeometryIntersection *inct) const noexcept = 0;

    virtual Real GetSurfaceArea() const noexcept = 0;

    virtual AABB GetLocalBound() const noexcept = 0;

    virtual AABB GetWorldBound() const noexcept;

    struct SampleResult
    {
        Vec3 pos;
        Vec3 nor;
        Real pdf;
    };

    virtual SampleResult Sample(const Vec3 &sample) const noexcept = 0;

    virtual Real SamplePDF(const Vec3 &pos) const noexcept = 0;

    virtual SampleResult Sample(const Vec3 &ref, const Vec3 &sample) const noexcept;

    virtual Real SamplePDF(const Vec3 &pos, const Vec3 &ref) const noexcept;
};

// ================================= Implementation

inline Geometry::Geometry(const Transform &local2World) noexcept
    : local2World_(local2World)
{

}

inline AABB Geometry::GetWorldBound() const noexcept
{
    return local2World_.ApplyToAABB(GetLocalBound());
}

inline Geometry::SampleResult Geometry::Sample([[maybe_unused]] const Vec3 &ref, const Vec3 &sample) const noexcept
{
    return Sample(sample);
}

inline Real Geometry::SamplePDF(const Vec3 &pos, [[maybe_unused]] const Vec3 &ref) const noexcept
{
    return SamplePDF(pos);
}

} // namespace Atrc
