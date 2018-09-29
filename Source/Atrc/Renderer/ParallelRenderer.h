#pragma once

#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include <Atrc/Common.h>
#include <Atrc/Renderer/Renderer.h>
#include <Atrc/Renderer/SubareaRenderer.h>

AGZ_NS_BEG(Atrc)

template<typename SR>
class ParallelRenderer
    : ATRC_IMPLEMENTS Renderer,
      ATRC_PROPERTY AGZ::Uncopiable
{
    int workerCount_;
    SR subareaRenderer_;
    
    using Area = SubareaRenderer::Subarea;
    
    struct Param
    {
        const Scene           *scene;
        const Integrator      *integrator;
        RenderTarget<Color3f> *output;
        const SubareaRenderer *subareaRenderer;

        std::mutex       *mut;
        std::queue<Area> *tasks;
    };
    
    static void Worker(Param param)
    {
        for(;;)
        {
            bool done = true;
            Area area = { 0, 0, 0, 0 };
            
            {
                std::lock_guard<std::mutex> lk(*param.mut);
                if(!param.tasks->empty())
                {
                    area = param.tasks->front();
                    param.tasks->pop();
                    done = false;
                }
            }
            
            if(done)
                break;

            param.subareaRenderer->Render(
                *param.scene, *param.integrator, *param.output, area);
        }
    }
    
public:

    template<typename...Args>
    explicit ParallelRenderer(int workerCount, Args&&...args)
        : subareaRenderer_(std::forward<Args>(args)...)
    {
        if(workerCount <= 0)
            workerCount = std::thread::hardware_concurrency();
        workerCount_ = (std::max)(1, workerCount) - 1;
    }

    void Render(
        const Scene &scene, const Integrator &integrator,
        RenderTarget<Color3f> &output) const override
    {
        AGZ_ASSERT(workerCount_ > 0);
        AGZ_ASSERT(output.IsAvailable());
        uint32_t w = output.GetWidth();
        uint32_t h = output.GetHeight();
        
        std::queue<Area> tasks;
        uint32_t yStep = w >= 1024 ? 1 : 2048 / w;
        uint32_t y = 0;
        for(; y + yStep <= h; y += yStep)
            tasks.push({ 0, w, y, y + yStep });
        if(y < h)
            tasks.push({ 0, w, y, h });

        std::mutex mut;
        Param param = {
            &scene, &integrator, &output, &subareaRenderer_,
            &mut, &tasks
        };
        
        std::vector<std::thread> workers;
        if(workerCount_)
            workers.reserve(workerCount_);
        for(int i = 0; i < workerCount_; ++i)
            workers.emplace_back(Worker, param);
        Worker(param);
        
        for(auto &worker : workers)
            worker.join();
    }
};

AGZ_NS_END(Atrc)
