#pragma once

#include <memory>

#include <AGZUtils/Utils/Config.h>
#include <Atrc/Editor/ResourceInstance/ResourceInstance.h>
#include <Atrc/Editor/Texture/Texture.h>

namespace Atrc::Editor
{

class IMaterial : public ResourceCommon<IMaterial>
{
protected:

    static void Range01(ITexture &tex) { tex.SetRange(0, 1); }

public:

    using ResourceCommon<IMaterial>::ResourceCommon;

    static const char *StrID() noexcept { return "material"; }

    virtual std::string Save(const std::filesystem::path &relPath) const = 0;

    virtual void Load(const AGZ::ConfigGroup &params, const std::filesystem::path &relPath) = 0;

    virtual std::string Export(const std::filesystem::path &relPath) const = 0;

    virtual void Display() = 0;

    virtual bool IsMultiline() const noexcept = 0;
};

DEFINE_DEFAULT_RESOURCE_CREATOR_INTERFACE(IMaterial);

void RegisterBuiltinMaterialCreators(MaterialFactory &factory);

}; // namespace Atrc::Editor
