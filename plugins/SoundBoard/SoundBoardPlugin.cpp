#include "DistrhoPlugin.hpp"
#include "SoundBoardPlugin.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------

SoundBoardPlugin::SoundBoardPlugin() : Plugin(kParameterCount, 0, 1)
{
    synth.setSampleRate(getSampleRate());
    synth.setNumVoices(9);
    initSFZ();
    makeSFZ();
}

void SoundBoardPlugin::initState(uint32_t index, String &stateKey, String &defaultStateValue)
{
    switch (index)
    {
    case 0:
        stateKey = "filename";
        defaultStateValue = "";
        break;

    default:
        printf("initState %i\n", index);
        break;
    }
}

void SoundBoardPlugin::setState(const char *key, const char *value)
{
    if (std::strcmp(key, "filepath") == 0)
    {
        char dst[strlen(value) + 1];
        std::strcpy(dst, value);
        char *ptr = strtok(dst, ",");
        int currentButton = atoi(ptr);
        while (ptr != nullptr)
        {
            printf(" %s\n", ptr);
            ptr = strtok(nullptr, ",");
            if (ptr != nullptr)
                sample_paths[currentButton] = ptr;
        }
        makeSFZ();
    }
}

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

void SoundBoardPlugin::initSFZ()
{
    for (int i = 0; i < 9; i++)
    {
        sample_paths[i] = "*sine";
    }
    sample_paths[0] = "/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/sample1.wav";
    sample_paths[1] = "/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/sample2.wav";
    sample_paths[2] = "/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/sample3.wav";
    sample_paths[3] = "/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/sample4.wav";
    sample_paths[4] = "/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/sample5.wav";
    sample_paths[5] = "/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/sample6.wav";
    sample_paths[6] = "/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/sample7.wav";
    sample_paths[7] = "/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/sample8.wav";
    sample_paths[8] = "/home/rob/git/ClearlyBroken/SoundBoard/scratchpad/sample9.wav";

    keys[0] = "c4";
    keys[1] = "d4";
    keys[2] = "e4";
    keys[3] = "f4";
    keys[4] = "g4";
    keys[5] = "a4";
    keys[6] = "b4";
    keys[7] = "c5";
    keys[8] = "d5";
}

void SoundBoardPlugin::makeSFZ()
{
    std::stringstream buffer;
    for (int i = 0; i < 9; i++)
    {
        buffer << "<region>\n";
        buffer << "sample=" << sample_paths[i] << "\n";
        buffer << "key=" << keys[i] << "\n";
        buffer << "loop_mode=one_shot\n";
        buffer << "amp_veltrack=0\n";
    }
    //    std::string sfz = "<region>\nsample=*sine\n";
    std::lock_guard<std::mutex> lock(synthMutex);
    std::string sfz = buffer.str();
    std::cout << sfz;
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
    std::unique_lock<std::mutex> lock(synthMutex, std::try_to_lock);
    if (!lock.owns_lock())
    { // synth is locked?
        std::fill_n(outputs[0], frames, 0.0f);
        std::fill_n(outputs[1], frames, 0.0f);
        return;
    }
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
            printf("message %i data1 %i, data2 %i\n", midi_message, midi_data1, midi_data2);
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
