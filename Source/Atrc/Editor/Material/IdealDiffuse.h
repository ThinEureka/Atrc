#pragma once

#include <Atrc/Editor/ResourceInstance/ResourceSlot.h>
#include <Atrc/Editor/Material/Material.h>
#include <Atrc/Editor/Texture/Texture.h>

class IdealDiffuse : public IMaterial
{
    ResourceSlot<TextureFactory> albedo_;

public:

    IdealDiffuse(const HasName *creator);

    std::string Save(const std::filesystem::path &relPath) const override;

    void Load(const AGZ::ConfigGroup &params, const std::filesystem::path &relPath) override;

    std::string Export(const std::filesystem::path &relPath) const override;

    void Display() override;

    bool IsMultiline() const noexcept override;
};

DEFINE_DEFAULT_RESOURCE_CREATOR(IMaterialCreator, IdealDiffuse, "IdealDiffuse");
