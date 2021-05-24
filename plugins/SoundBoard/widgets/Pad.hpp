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

#ifndef TEXT_BUTTON_HPP
#define TEXT_BUTTON_HPP

#include "Window.hpp"
#include "Widget.hpp"
#include "NanoVG.hpp"
#include <string>

START_NAMESPACE_DISTRHO

class Pad : public NanoWidget
{
public:
  class Callback
  {
  public:
    virtual ~Callback() {}
    virtual void onPadClicked(Pad *pad, int button) = 0;
  };
  explicit Pad(Window &parent) noexcept;
  explicit Pad(Widget *widget) noexcept;
  void setCallback(Callback *cb);
  void setFont(const char *name, const uchar *data, uint dataSize);
  Color background_color;
  Color text_color;
  Color highlight_color;
  Color border_color;
  std::string padText;
  std::string noteName;
  bool isActive;

  float font_size;

protected:
  void onNanoDisplay() override;
  bool onMouse(const MouseEvent &) override;
  bool onMotion(const MotionEvent &) override;

private:
  FontId main_font;
  bool has_mouse_;
  Callback *callback;
  Color fill_color_;

  DISTRHO_LEAK_DETECTOR(Pad)
};

END_NAMESPACE_DISTRHO

#endif // TEXT_BUTTON_HPP
