#pragma once

#include <borealis.hpp>
#include <thread>

typedef std::function<void()> WorkerFunction_T;

struct WorkerPage : public brls::View
{
    WorkerPage(brls::StagedAppletFrame *frame, const std::string &text, WorkerFunction_T func);
    ~WorkerPage();

    void draw(NVGcontext *vg, int x, int y, unsigned width, unsigned height, brls::Style *style, brls::FrameContext *ctx) override;
    void layout(NVGcontext *vg, brls::Style *style, brls::FontStash *stash) override;
    brls::View *getDefaultFocus() override;

    private:
    void work();

    brls::ProgressDisplay *progress = nullptr;
    brls::StagedAppletFrame *frame = nullptr;
    brls::Button *button = nullptr;
    brls::Label *label = nullptr;

    std::string text;

    int progressVal = 0;
    bool startedwork = false;
    bool drawPage = true;
    std::thread *workerThread = nullptr;
    WorkerFunction_T func;
};