# SoundBoard

WIP sample launcher

## linux only

## note : only the lv2 version plays samples from the user interface

- left click plays sample
- right click assign sample (don't mention the file dialog!)
- play samples via midi from c4 up (white keys only)
- latest binaries are [here](https://github.com/clearly-broken-software/SoundBoard/releases/download/testing/SoundBoard_binaries.zip)

---

### INSTALL

you can use the attached binaries on the release page or build SoundBoard yourself.

#### Build instructions

**Dependencies**

- libgl1-mesa-dev
- libx11-dev

```bash
git clone --recursive https://github.com/clearly-broken-software/SoundBoard.git
cd SoundBoard
make
```

optionally:

```bash
make install
```

or simply copy the plugin from `<soundboard dir>bin/` to `~/.lv2`
