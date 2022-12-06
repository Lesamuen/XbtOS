# XBtOS
## Intro
A project originally made for the Fall 2022 CSE165 class of UC Merced under Pengfei Su.

"XbtOS" stands for "X by the One Shot", or further expanded, "**Live by the One Shot, Die by the One Shot**"

Credits to my friend Robert Kubos for the idea.

Made possible by SDL2.

### Premise
**Live by the One Shot, Die by the One Shot** is a game where you, the hero of a kingdom, is sent out to slay the Demon King.
When you were but a child, and had escaped from the destruction of your home village, the Demon King himself had spared you for fun, placing a terrible curse upon you: *any damage ever dealt to you will inevitably instantly kill you*; that is, you will die in One Shot.
The Goddess of the Humans took pity in you, and blessed you with a power that could slay any enemy in One Shot. The Holy Temple found you, and took you in to train you for your inevitable deed.

To survive, you've trained in the arts of movement and immunity; to avoid damage at all costs, you must either not get hit at all, or negate all damage that you would take.

## Dependencies
The only dependency is SDL2, so depending on whether you are building for Linux or Windows, get the SDL2 distribution for that OS.

Currently using SDL 2.26.0; the project might work with previous versions, but get this version or up in case it doesn't.

Otherwise, use provided Makefile to compile.

### Linux
To install dependencies:
`sudo apt-get install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev`

Then to compile:
`make`

To run:
`make run`

To remove executable:
`make clean`

### Windows (MinGW)
Get the devel-mingw zip from [their github](https://github.com/libsdl-org/SDL/releases/tag/release-2.26.0).
Place include and lib folders in repo, but pull bin/SDL2.dll separately out into the repo.

Do the same for the extension libraries:
[Images](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.2)
[Fonts](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.1)

Then, use `make` with MinGW to compile.
Targets:
`make`
`make run`
`make clean`