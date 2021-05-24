
#ifndef SOUNDBOARD_UI_HPP_INCLUDED
#define SOUNDBOARD_UI_HPP_INCLUDED

#include <memory>
#include "filesystem.hpp"
#include "DistrhoUI.hpp"
//#include "Window.hpp"
#include "Pad.hpp"
#include "CbColors.hpp"
#include "fonts.hpp"
#include "DistrhoPluginInfo.h"
#include <string>

namespace fs = ghc::filesystem;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

class SoundBoardUI : public UI,
                     public Pad::Callback

{
public:
    SoundBoardUI();
    ~SoundBoardUI();

protected:
    void parameterChanged(uint32_t index, float value) override;
    void onNanoDisplay() override;
    void uiFileBrowserSelected(const char *filename) override;
    void stateChanged(const char *key, const char *value) override;
    void onPadClicked(Pad *pad, int button) override;

private:
    std::string note_number_to_name(int nn);
    std::unique_ptr<Pad> fPad[16];
    fs::path pad_paths[16];
    fs::path sampleDir;
    uint keys[16];
    uint currentPad;
    std::string noteNames[12] = {"C", "C#", "D", "Eb", "E", "F",
                                 "F#", "G", "Ab", "A", "Bb", "B"};
 
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoundBoardUI)
};

END_NAMESPACE_DISTRHO

#endif