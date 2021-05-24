

#ifndef DISTRHO_PLUGIN_INFO_H_INCLUDED
#define DISTRHO_PLUGIN_INFO_H_INCLUDED

#define DISTRHO_PLUGIN_BRAND "Clearly Broken Software"
#define DISTRHO_PLUGIN_NAME "SoundBoard"
#define DISTRHO_PLUGIN_URI "http://github.com/clearly-broken-software/SoundBoard"

#define DISTRHO_PLUGIN_IS_SYNTH 1
#define DISTRHO_PLUGIN_HAS_UI 1
#define DISTRHO_PLUGIN_IS_RT_SAFE 1
#define DISTRHO_PLUGIN_NUM_INPUTS 0
#define DISTRHO_PLUGIN_NUM_OUTPUTS 2
#define DISTRHO_UI_USE_NANOVG 1
#define DISTRHO_PLUGIN_WANT_STATE 1
// #define DISTRHO_PLUGIN_WANT_FULL_STATE 1
#define DISTRHO_PLUGIN_LV2_CATEGORY "lv2:InstrumentPlugin"

enum Parameters
{
    kPad1 = 0,
    kPad2,
    kPad3,
    kPad4,
    kPad5,
    kPad6,
    kPad7,
    kPad8,
    kPad9,
    kPad10,
    kPad11,
    kPad12,
    kPad13,
    kPad14,
    kPad15,
    kPad16,
    kParameterCount
};

#endif // DISTRHO_PLUGIN_INFO_H_INCLUDED
