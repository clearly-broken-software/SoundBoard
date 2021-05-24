#include "SoundBoardUI.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------

SoundBoardUI::SoundBoardUI()
    : UI(300, 300)
{
    sampleDir = fs::current_path();
    for (int i = 0; i < 9; i++)
    {
        fButton[i].reset(new Button(this, this));
        fButton[i]->setId(kButton1 + i);
        fButton[i]->setLabelColor(Color(0.8f, 0.8f, 0.8f));
        fButton[i]->setBackgroundColor(Color(0.1f, 0.1f, 0.1f));
        fButton[i]->setLabel(std::string("Sample " + std::to_string(i + 1)));
        fButton[i]->setSize(100, 300 / 9);
        fButton[i]->setAbsolutePos(10, (300 / 9) * i);
        pad[i].clear();
    }

    keys[0] = 60; // c4 (middle c)
    keys[1] = 62;
    keys[2] = 64;
    keys[3] = 65;
    keys[4] = 67;
    keys[5] = 69;
    keys[6] = 71;
    keys[7] = 72;
    keys[8] = 74;
}

SoundBoardUI::~SoundBoardUI()
{
}

void SoundBoardUI::parameterChanged(uint32_t index, float value)
{
}

void SoundBoardUI::onNanoDisplay()
{
    float width = getWidth();
    float height = getHeight();
    // background
    beginPath();
    fillColor(0.1f, 0.2f, 0.3f);
    rect(0.0f, 0.0f, width, height);
    fill();
    closePath();
}

void SoundBoardUI::uiFileBrowserSelected(const char *filename)
{
    // if a file was selected, tell DSP
    if (filename != nullptr)
    {
        char buffer[1024];
        sprintf(buffer, "%i,%s", currentButton, filename);
        setState("filepath", buffer);
        sampleDir = fs::path(filename).parent_path();
        std::string sample_name(fs::path(filename).filename());
        fButton[currentButton]->setLabel(sample_name);
        repaint();
    }
}

void SoundBoardUI::stateChanged(const char *key, const char *value)
{
    if (strcmp(key, "filepath") == 0)
    {
        // fileName = std::string(value);
        // if (plugin->loadedSample)
        // {
        //     loadSample();
        //     sampleDir = dirnameOf(fileName.c_str());
        //     fileopen_button->setText(fileName);
        // }
    }
#ifdef DEBUG
    printf("SoundBoardUI::stateChanged(key = %s, value = %s)\n", key, value);
#endif
}

void SoundBoardUI::buttonClicked(Button *button, int value)
{
    uint32_t id = button->getId();
    if (value == 1)
    {
        // todo : check index
        printf("sending note %i\n", keys[id]);
        sendNote(0, keys[id], 127);
        return;
    }
    if (value == 3)
    {
        currentButton = id;
        DGL::Window::FileBrowserOptions opts;
        opts.title = "Load SFZ";
        opts.startDir = sampleDir.c_str();
        opts.buttons.showPlaces = 2;
        getParentWindow().openFileBrowser(opts);
    }

    const char *whichButton = (value == 1) ? "left" : "right";
    printf("%s button clicked\n", whichButton);
}
UI *createUI()
{
    return new SoundBoardUI();
}

// -----------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
