#include "SoundBoardUI.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------

SoundBoardUI::SoundBoardUI()
    : UI(638, 638)
{
    sampleDir = fs::current_path();
    for (int i = 0; i < 16; i++)
    {
        fPad[i].reset(new Pad(this));
        int id = i;
        fPad[i]->setId(id);
        fPad[i]->setCallback(this);
        fPad[i]->setFont("roboto", reinterpret_cast<const uchar *>(fonts::Roboto_RegularData),
                         fonts::Roboto_RegularDataSize);
        fPad[i]->background_color = cbcol::black_olive;
        fPad[i]->text_color = cbcol::floral_white;
        fPad[i]->border_color = cbcol::flame;
        fPad[i]->highlight_color = cbcol::flame_1;
        fPad[i]->noteName = note_number_to_name(60+i);
        fPad[i]->setSize(150, 150);
        pad_paths[i].clear();
        keys[i] = i + 60;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int padIndex = i * 4 + j;
            int x = 10 + j * 156;
            int y = 10 + i * 156;
            fPad[padIndex]->setAbsolutePos(x, y);
        }
    }
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
    fillColor(cbcol::eerie_black);
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
        sprintf(buffer, "%i,%s", currentPad, filename);
        setState("filepath", buffer);
        sampleDir = fs::path(filename).parent_path();
        std::string sample_name(fs::path(filename).filename());
        fPad[currentPad]->padText = sample_name;
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

void SoundBoardUI::onPadClicked(Pad *button, int value)
{
    uint32_t id = button->getId();
    if (value == 1)
    {
#ifdef DEBUG
        printf("sending note %i\n", keys[id]);
#endif
        sendNote(0, keys[id], 127);
        return;
    }
    if (value == 3)
    {
        currentPad = id;
        DGL::Window::FileBrowserOptions opts;
        opts.title = "Load SFZ";
        opts.startDir = sampleDir.c_str();
        opts.buttons.showPlaces = 2;
        getParentWindow().openFileBrowser(opts);
    }
}

std::string SoundBoardUI::note_number_to_name(int nn)
{
    int index = nn % 12;
    int octave = nn / 12 - 1;
    return noteNames[index] + std::to_string(octave);
}

UI *createUI()
{
    return new SoundBoardUI();
}

// -----------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
