#include <workerPage.hpp>

#include <switch.h>

#include <string>
#include <functional>
#include <cmath>

#include <progressEvent.hpp>
#include <mainFrame.hpp>

using namespace brls::i18n::literals;

WorkerPage::WorkerPage(brls::StagedAppletFrame *frame, const std::string &text, WorkerFunction_T func)
    : frame(frame), text(text), func(func)
{
    this->progress = new brls::ProgressDisplay();
    this->progress->setParent(this);

    this->label = new brls::Label(brls::LabelStyle::DIALOG, text, true);
    this->label->setHorizontalAlign(NVG_ALIGN_CENTER);
    this->label->setParent(this);

    this->button = new brls::Button(brls::ButtonStyle::REGULAR);
    this->button->setParent(this);

    this->registerAction("", brls::Key::B, [this] { return true; });
    this->registerAction("", brls::Key::A, [this] { return true; });
}

WorkerPage::~WorkerPage()
{
    if (this->startedwork && workerThread->joinable())
    {
        this->workerThread->join();
        if (this->workerThread)
            delete this->workerThread;
    }

    delete this->progress;
    delete this->label;
    delete this->button;
}

void WorkerPage::draw(NVGcontext* vg, int x, int y, unsigned width, unsigned height, brls::Style* style, brls::FrameContext* ctx)
{
    if (this->drawPage)
    {
        ProgressEvent &pe = ProgressEvent::getInstance();

        if (!this->startedwork)
        {
            appletSetMediaPlaybackState(true);
            this->startedwork = true;
            pe.reset();
            workerThread = new std::thread(&WorkerPage::work, this);
        }
        else if (pe.finished())
        {
            appletSetMediaPlaybackState(false);
            if (!frame->isLastStage())
                frame->nextStage();
            else
                brls::Application::pushView(new MainFrame());
        }
        else
        {
            this->progress->setProgress(pe.getStep(), pe.getMax());
            this->progress->frame(ctx);
            this->label->frame(ctx);
        }
    }
}

void WorkerPage::layout(NVGcontext *vg, brls::Style *style, brls::FontStash *stash)
{
    this->label->setWidth(roundf( (float)this->width * style->CrashFrame.labelWidth ));

    this->label->setBoundaries(
        this->x + this->width / 2 - this->label->getWidth() / 2,
        this->y + (this->height - style->AppletFrame.footerHeight) / 2,
        this->label->getWidth(),
        this->label->getHeight()
    );

    this->progress->setBoundaries(
        this->x + this->width / 2 - style->CrashFrame.buttonWidth,
        this->y + this->height / 2,
        style->CrashFrame.buttonWidth * 2,
        style->CrashFrame.buttonHeight
    );
}

brls::View *WorkerPage::getDefaultFocus()
{
    return this->button;
}

void WorkerPage::work()
{
    if (this->func)
        this->func();
}