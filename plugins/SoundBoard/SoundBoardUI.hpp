
#ifndef SOUNDBOARD_UI_HPP_INCLUDED
#define SOUNDBOARD_UI_HPP_INCLUDED

#include <memory>
#include "filesystem.hpp"
#include "DistrhoUI.hpp"
#include "Window.hpp"
#include "NanoButton.hpp"
#include "DistrhoPluginInfo.h"

namespace fs = ghc::filesystem;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

class SoundBoardUI : public UI,
                     public Button::Callback

{
public:
    SoundBoardUI();
    ~SoundBoardUI();

protected:
    void parameterChanged(uint32_t index, float value) override;
    void onNanoDisplay() override;
    void uiFileBrowserSelected(const char *filename) override;
    void stateChanged(const char *key, const char *value) override;
    void buttonClicked(Button *bt, int button) override;

private:
    std::unique_ptr<Button> fButton[9];
    fs::path pad[9];
    fs::path sampleDir;
    uint keys[9];
    uint currentButton;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoundBoardUI)
};

END_NAMESPACE_DISTRHO

#endif