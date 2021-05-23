/*
    SoundBoard
    Copyright (C) 2021  Rob van den Berg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef SOUNDBOARD_HPP_INCLUDED
#define SOUNDBOARD_HPP_INCLUDED

#include "DistrhoPlugin.hpp"
#include "sfizz.hpp"
#include <iostream>
#include <sndfile.hh>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <mutex>
START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class SoundBoardPlugin : public Plugin
{
public:
    SoundBoardPlugin();

protected:
    const char *getLabel() const noexcept override
    {
        return "SoundBoard";
    }

    const char *getDescription() const override
    {
        return "Easy to use sample launcher plugin";
    }

    const char *getMaker() const noexcept override
    {
        return "Clearly Broken Software";
    }

    const char *getHomePage() const override
    {
        return "https://github.com/clearly-broken-software/drops";
    }

    const char *getLicense() const noexcept override
    {
        return "GPL V3";
    }

    uint32_t getVersion() const noexcept override
    {
        return d_version(1, 0, 0);
    }

    int64_t getUniqueId() const noexcept override
    {
        return d_cconst('D', 'r', 'p', 'S');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter &parameter) override;
    void setState(const char *key, const char *value) override;
    String getState(const char *key) const override;
    void initState(unsigned int, String &, String &) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;
    // -------------------------------------------------------------------
    // Process

    //void activate() override;
    void run(const float **, float **outputs, uint32_t frames, const MidiEvent *midiEvents, uint32_t midiEventCount) override;

    // -------------------------------------------------------------------

private:
    void initSFZ();
    void makeSFZ();
    //   int loadSample(const char *fp);

    double sampleRate;
    std::string sample_paths[9];
    std::string keys[9];
    sfz::Sfizz synth;
    std::mutex synthMutex;

//    friend class SoundBoardUI;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoundBoardPlugin)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // SOUNDBOARD_HPP_INCLUDED
