#include <Atrc/Lib/PostProcessor/FlipImage.h>
#include <Atrc/Mgr/BuiltinCreator/PostProcessorCreator.h>

namespace Atrc::Mgr
{
    
void RegisterBuiltinPostProcessorCreators(Context& context)
{
    static FlipImageCreator flipImageCreator;
    context.AddCreator(&flipImageCreator);
}

PostProcessor *FlipImageCreator::Create([[maybe_unused]] const ConfigGroup &group, [[maybe_unused]] Context &context, Arena &arena) const
{
    ATRC_MGR_TRY
    {
        return arena.Create<FlipImage>();
    }
    ATRC_MGR_CATCH_AND_RETHROW("In creating post processor (flip image)")
}

} // namespace Atrc::Mgr
