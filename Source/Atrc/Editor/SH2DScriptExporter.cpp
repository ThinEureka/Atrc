#include <Atrc/Editor/Global.h>
#include <Atrc/Editor/SH2DScriptExporter.h>

namespace
{
    template<typename TResource>
    void ExportResourcesInPool(ResourceManager &rscMgr, SceneExportingContext &ctx)
    {
        ctx.AddLine(TResource::GetPoolName(), " = {");
        ctx.IncIndent();
        for(auto &rsc : rscMgr.GetPool<TResource>())
            ResourceInstance::ExportSubResource(rsc->GetName(), rscMgr, ctx, *rsc);
        ctx.DecIndent();
        ctx.AddLine("};");
    }
}

std::string SH2DSceneScriptExporter::Export(
    ResourceManager &rscMgr, SceneExportingContext &ctx,
    int workerCount, int taskGridSize, int SHOrder,
    const Vec2i &outputFilmSize,
    const Atrc::Editor::IFilmFilter *filmFilter,
    const Atrc::Editor::ISampler *sampler) const
{
    ctx.ClearString();

    ctx.AddLine("workspace = \"@", relative(ctx.workspaceDirectory, ctx.scriptDirectory).string(), "\";");

    ctx.AddLine();

    ctx.AddLine("film = {");
    ctx.IncIndent();
    ctx.AddLine("size = (", outputFilmSize.x, ", ", outputFilmSize.y, ");");
    if(filmFilter)
        ctx.AddLine("filter = ", filmFilter->Export(), ";");
    else
        Global::ShowNormalMessage("film filter is unspecified");
    ctx.DecIndent();
    ctx.AddLine("};");

    ctx.AddLine();

    ctx.AddLine("pool = {");
    ctx.IncIndent();
    ExportResourcesInPool<CameraInstance>(rscMgr, ctx);
    ExportResourcesInPool<EntityInstance>(rscMgr, ctx);
    ExportResourcesInPool<GeometryInstance>(rscMgr, ctx);
    ExportResourcesInPool<MaterialInstance>(rscMgr, ctx);
    ExportResourcesInPool<TextureInstance>(rscMgr, ctx);
    ctx.DecIndent();
    ctx.AddLine("};");

    ctx.AddLine();

    if(sampler)
    {
        ctx.AddLine("sampler=", sampler->Export(), ";");
        ctx.AddLine();
    }
    else
        Global::ShowNormalMessage("sampler is unspecified");

    if(ctx.camera)
    {
        ResourceInstance::ExportSubResourceAsReference("camera", rscMgr, ctx, *ctx.camera);
        ctx.AddLine();
    }
    else
        Global::ShowNormalMessage("camera is unspecified");

    ctx.AddLine("workerCount = ", workerCount, ";");
    ctx.AddLine("taskGridSize = ", taskGridSize, ";");
    ctx.AddLine("SHOrder = ", SHOrder, ";");

    ctx.AddLine();

    ctx.AddLine("entities = (");
    for(auto &ent : rscMgr.GetPool<EntityInstance>())
    {
        ctx.AddLine("{");
        ctx.IncIndent();
        ent->ExportAsReference<EntityInstance>(rscMgr, ctx);
        ctx.DecIndent();
        ctx.AddLine("},");
    }
    ctx.AddLine(");");
    ctx.AddLine();

    return ctx.GetString();
}
