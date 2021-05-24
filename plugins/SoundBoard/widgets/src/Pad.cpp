/*
    SoundBoard - Easy to use sample launcher
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
#include "Pad.hpp"

START_NAMESPACE_DISTRHO

Pad::Pad(Window &parent) noexcept
    : NanoWidget(parent)
{
    padText = "NO SAMPLE LOADED";
    noteName ="note";
    background_color = Color(0.8f, 0.8f, 0.8f);
    text_color = Color(0.1f, 0.1f, 0.1f);
    border_color = Color(0.5f, 0.5f, 0.5f);
    font_size = 16;
    has_mouse_ = false;
}

Pad::Pad(Widget *widget) noexcept
    : NanoWidget(widget)
{
    padText = "NO SAMPLE LOADED";
    noteName ="note";
    background_color = Color(0.8f, 0.8f, 0.8f);
    text_color = Color(0.1f, 0.1f, 0.1f);
    border_color = Color(0.5f, 0.5f, 0.5f);
    font_size = 16;
    has_mouse_ = false;
    isActive = false;
}

bool Pad::onMouse(const MouseEvent &ev)
{
    if (contains(ev.pos) && ev.press)
    {
        callback->onPadClicked(this, ev.button);
        return true;
    }
    else
    {
        return false;
    }
}
bool Pad::onMotion(const MotionEvent &ev)
{
    if (contains(ev.pos) && !has_mouse_)
    {
        has_mouse_ = true;
        repaint();
    }
    if (!contains(ev.pos) && has_mouse_)
    {
        has_mouse_ = false;
        repaint();
    }
    return false;
}

void Pad::onNanoDisplay()
{
    int width = getWidth();
    int height = getHeight();

    if (has_mouse_ || isActive)
        fill_color_ = highlight_color;
    else
        fill_color_ = border_color;
    beginPath();
    fillColor(background_color);
    strokeColor(fill_color_);
    strokeWidth(6);
    roundedRect(3, 3,
                width -6 , height -6 ,
                12);
    fill();
    closePath();  beginPath();
    strokeColor(fill_color_);
    strokeWidth(6);
    roundedRect(3, 3,
                width -6 , height -6 ,
                12);
    stroke();
    closePath();

    // text
    beginPath();
    fontFaceId(main_font);
    fillColor(text_color);
    fontSize(font_size);
    textAlign(ALIGN_CENTER | ALIGN_MIDDLE);
    text(std::round(width / 2), std::round(height / 2.0f), padText.c_str(), NULL);
    closePath();
  
    beginPath();
    fontSize(14);
    textAlign(ALIGN_LEFT | ALIGN_BOTTOM);
    text(10, height -10, noteName.c_str(), NULL);
    closePath();
}

void Pad::setFont(const char *name, const uchar *data, uint dataSize)
{
    main_font = createFontFromMemory(name, data, dataSize, false);
}

void Pad::setCallback(Callback *cb)
{
    callback = cb;
}

END_NAMESPACE_DISTRHO
