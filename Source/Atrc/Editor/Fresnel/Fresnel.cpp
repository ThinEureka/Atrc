#include <Atrc/Editor/Fresnel/Fresnel.h>

#include <Atrc/Editor/Fresnel/Conductor.h>
#include <Atrc/Editor/Fresnel/Dielectric.h>
#include <Atrc/Editor/Fresnel/Schlick.h>

void RegisterBuiltinFresnelCreators(FresnelFactory &factory)
{
    static const ConductorCreator iConductorCreator;
    static const DielectricCreator iDielectricCreator;
    static const SchlickCreator iSchlickCreator;
    factory.AddCreator(&iConductorCreator);
    factory.AddCreator(&iDielectricCreator);
    factory.AddCreator(&iSchlickCreator);
}
