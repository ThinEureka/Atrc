#pragma once

#include <AGZUtils/Utils/Texture.h>

#include <Atrc/Mgr/Context.h>

namespace Atrc::Mgr
{

void RegisterBuiltinTextureCreators(Context &context);

/*
    type = Constant

    texel = Spectrum
*/
class ConstantTextureCreator : public Creator<Texture>
{
public:

    std::string GetTypeName() const override { return "Constant"; }

    Texture *Create(const ConfigGroup &group, Context &context, Arena &arena) const override;
};

/*
    type = Constant1

    texel = Real
*/
class ConstantTexture1Creator : public Creator<Texture>
{
public:

    std::string GetTypeName() const override { return "Constant1"; }

    Texture *Create(const ConfigGroup &group, Context &context, Arena &arena) const override;
};

/*
    type = HDR

    filename = String
    sampler  = Nearest | Linear
    wrapper  = Clamp
    reverseV = True | False | null(False)
*/
class HDRTextureCreator : public Creator<Texture>
{
    mutable std::unordered_map<std::string, const AGZ::Texture2D<Color3f>*> path2Tex_;

public:

    std::string GetTypeName() const override { return "HDR"; }

    Texture *Create(const ConfigGroup &group, Context &context, Arena &arena) const override;
};

/*
    type = Image

    filename = String
    sampler  = Nearest | Linear
    wrapper  = Clamp
    reverseV = True | False | null(False)
*/
class ImageTextureCreator : public Creator<Texture>
{
    mutable std::unordered_map<std::string, const AGZ::Texture2D<Color3b>*> path2Tex_;

public:

    std::string GetTypeName() const override { return "Image"; }

    Texture *Create(const ConfigGroup &group, Context &context, Arena &arena) const override;
};

/*
    type = Mul

    lhs = Texture
    rhs = Texture
*/
class TextureMultiplierCreator : public Creator<Texture>
{
public:

    std::string GetTypeName() const override { return "Mul"; }

    Texture *Create(const ConfigGroup &group, Context &context, Arena &arena) const override;
};

} // namespace Atrc::Mgr
