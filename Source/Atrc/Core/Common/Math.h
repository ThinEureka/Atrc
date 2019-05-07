#pragma once

#include <AGZUtils/Utils/Math.h>

namespace Atrc::Core
{
    
using Real = float;

extern const Real EPS;
constexpr Real PI = AGZ::Math::PI<Real>;
constexpr Real InvPI = AGZ::Math::InvPI<Real>;

using Vec2r = AGZ::Math::Vec2<Real>;
using Vec3r = AGZ::Math::Vec3<Real>;
using Vec4r = AGZ::Math::Vec4<Real>;

using Vec2u = AGZ::Math::Vec2<uint32_t>;
using Vec2i = AGZ::Math::Vec2<int32_t>;

using Rectr = AGZ::Math::Rect<Real>;
using Rectu = AGZ::Math::Rect<uint32_t>;
using Recti = AGZ::Math::Rect<int32_t>;

using Mat3r = AGZ::Math::RM_Mat3<Real>;
using Mat4r = AGZ::Math::RM_Mat4<Real>;

using Radr = AGZ::Math::Rad<Real>;
using Degr = AGZ::Math::Deg<Real>;

using AGZ::Math::Abs;
using AGZ::Math::ApproxEq;
using AGZ::Math::Arccos;
using AGZ::Math::Arcsin;
using AGZ::Math::Arctan2;
using AGZ::Math::Clamp;
using AGZ::Math::Cos;
using AGZ::Math::Exp;
using AGZ::Math::Log_e;
using AGZ::Math::Min;
using AGZ::Math::Mix;
using AGZ::Math::Max;
using AGZ::Math::Pow;
using AGZ::Math::Saturate;
using AGZ::Math::Sin;
using AGZ::Math::Sqr;
using AGZ::Math::Sqrt;
using AGZ::Math::Tan;

inline Real Cos(const Vec3r &lhs, const Vec3r &rhs) noexcept
{
    return Dot(lhs, rhs) / (lhs.Length() * rhs.Length());
}

} // namespace Atrc::Core
