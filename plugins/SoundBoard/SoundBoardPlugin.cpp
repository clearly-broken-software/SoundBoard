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

#include "DistrhoPlugin.hpp"
#include "SoundBoardPlugin.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------

SoundBoardPlugin::SoundBoardPlugin() : Plugin(kParameterCount, 0, 2)
{
    sampleRate = getSampleRate();
    synth.setSampleRate(sampleRate);
    synth.setNumVoices(9);
    //   synth.loadSfzFile("/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/SoundBoard.sfz");
    initSFZ();
    makeSFZ();
}

// --  PARAMETERS  -------------------------------------------------------------

// Init
void SoundBoardPlugin::initParameter(uint32_t index, Parameter &parameter)
{
}

float SoundBoardPlugin::getParameterValue(uint32_t index) const
{
    return 0.0f;
}

void SoundBoardPlugin::setParameterValue(uint32_t index, float value)
{
}

void SoundBoardPlugin::setState(const char *key, const char *value)
{
    if (strcmp(key, "ui_sample_loaded") == 0)
    {
        //      sig_sampleLoaded = false;
    }
    if (strcmp(key, "filepath") == 0)
    {
        //     path = std::string(value);
        //      loadSample(value);
        makeSFZ();
    }
}

String SoundBoardPlugin::getState(const char *key) const
{
    String retString = String("fix me");
#ifdef DEBUG
    printf("getState(%s)\n", key);
#endif
    if (strcmp(key, "filepath") == 0)
    {
        //       retString = path.c_str();
    }
    if (strcmp(key, "ui_sample_loaded") == 0)
    {
        retString = "ui_sample_loaded yes/no";
    }
    return retString;
};

void SoundBoardPlugin::initState(unsigned int index, String &stateKey, String &defaultStateValue)
{
    switch (index)
    {
    case 0:
        stateKey = "filepath";
        defaultStateValue = "empty";
        break;
    case 1:
        stateKey = "ui_sample_loaded";
        defaultStateValue = "false";
        break;
    default:
#ifdef DEBUG
        printf("initState %i\n", index);
#endif
        break;
    }
}

void SoundBoardPlugin::initSFZ()
{
    for (int i = 0; i < 9; i++)
    {
        sample_paths[i] = "*sine";
    }

    keys[0] = "c4";
    keys[1] = "d4";
    keys[2] = "e4";
    keys[3] = "f4";
    keys[4] = "g4";
    keys[5] = "a4";
    keys[6] = "b4";
    keys[7] = "c5";
    keys[8] = "d5";
    keys[9] = "e5";
}

void SoundBoardPlugin::makeSFZ()
{
    std::stringstream buffer;
    // for (int i = 0; i < 9; i++)
    // {
    //     buffer << "<region>\n";
    //     buffer << "sample=" << sample_paths[i] << "\n";
    //     buffer << "key=" << keys[i] << "\n";
    //     buffer << "loop_mode=one_shot\n";
    //     buffer << "amp_veltrack=0\n";
    // }

    buffer << "<region>\n";
    buffer << "sample=" << sample_paths[0] << "\n";
    buffer << "key=" << keys[0] << "\n";
    buffer << "loop_mode=one_shot\n";
    buffer << "amp_veltrack=0\n";

    // replace decimal comma wih decimal point
    //    std::string tmpSFZ = buffer.str();
    //    std::replace(tmpSFZ.begin(), tmpSFZ.end(), ',', '.'); // TODO don't replace in file path

#ifdef DEBUG
    std::cout << "----------------- SFZ FILE ------------------\n";
    std::cout << buffer.str() << std::endl;
    std::cout << "----------------- SFZ FILE ------------------\n";
#endif
    //  std::lock_guard<std::mutex> lock(synthMutex);
    //synth.loadSfzString("", buffer.str());
    std::string sfz = "<region>\nsample=*sine\n";
    synth.loadSfzString("", sfz);
}

// --  MAIN PLUGIN FUNCTIONS  --------------------------------------------------

/* Main Audio and MIDI processing function */
void SoundBoardPlugin::run(
    const float **,              // incoming audio
    float **outputs,             // outgoing audio
    uint32_t frames,             // size of block to process
    const MidiEvent *midiEvents, // MIDI pointer
    uint32_t midiEventCount      // Number of MIDI events in block
)
{
    //  std::unique_lock<std::mutex> lock(synthMutex, std::try_to_lock);
    //  if (!lock.owns_lock())
    //   { // synth is locked?
    //      std::fill_n(outputs[0], frames, 0.0f);
    //       std::fill_n(outputs[1], frames, 0.0f);
    //      return;
    //   }
    // const TimePosition &timePos(getTimePosition());
    // if (timePos.bbt.valid)
    // {
    //     synth.tempo(0, 60.0f / timePos.bbt.beatsPerMinute);
    //     synth.timeSignature(0, timePos.bbt.beatsPerBar, timePos.bbt.beatType);
    //     const double beat = timePos.bbt.beat - 1;
    //     const double fracBeat = timePos.bbt.tick / timePos.bbt.ticksPerBeat;
    //     const double barBeat = beat + fracBeat;
    //     synth.timePosition(0, timePos.bbt.bar, barBeat);
    //     //printf("barBeat %f\n", barBeat);
    //     synth.playbackState(0, static_cast<int>(timePos.playing));
    // }

    uint32_t framesDone = 0;
    uint32_t curEventIndex = 0; // index for midi event to process

    while (framesDone < frames)
    {
        while (curEventIndex < midiEventCount && framesDone == midiEvents[curEventIndex].frame)
        {
            int status = midiEvents[curEventIndex].data[0]; // midi status
                                                            //  int channel = status & 0x0F ; // get midi channel
            int midi_message = status & 0xF0;
            int midi_data1 = midiEvents[curEventIndex].data[1];
            int midi_data2 = midiEvents[curEventIndex].data[2];
            switch (midi_message)
            {
            case 0x80: // note_off
                synth.noteOff(framesDone, midi_data1, midi_data2);
                break;
            case 0x90: // note_on
                synth.noteOn(framesDone, midi_data1, midi_data2);
                break;
            default:
                break;
            }
            curEventIndex++;

        } // midi events
        ++framesDone;
    } // frames loop
    synth.renderBlock(outputs, frames, 2);
} // run

/* Plugin entry point, called by DPF to create a new plugin instance. */
Plugin *createPlugin()
{
    return new SoundBoardPlugin();
}

// -----------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
