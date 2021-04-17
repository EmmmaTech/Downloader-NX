# Downloader

A cross-platform download manager for PC and Switch. GUI powered by borealis.

Downloader works by getting URL links to download from and filenames to name the downloaded files.
It then uses curl to download all of the files queued.

In-progress right now. Look at the Projects tab to see the progress!

# Compiling

## For Switch

Compiling for the Nintendo Switch requires a devkitpro environment. Refer to [this guide](https://devkitpro.org/wiki/Getting_Started) to help you with this.

After you have a devkitpro environment setup, use the following commands to build:

```bash
(sudo) (dkp-)pacman -S switch-glfw switch-mesa switch-glm switch-curl switch-zlib
cd /path/to/Downloader
make # optionally, add -j$(nproc) (won't work on Windows)
```

Copy the Downloader.nro file to `/switch/Downloader` in the SD Card. Enjoy!

## For Mac/Linux (PC)

### Note: I have no idea how to compile this for Windows, so these instructions will be for Mac/Linux only. Feel free to Pull Request and add instructions.

Compiling for PC requires a few things (how to install them varies):
- meson/ninja build system
- C++ compiler supporting C++17 or above
- GLFW library (3.3 or higher)
- GLM library (0.9.8 or higher)
- Libcurl (should be automatically installed depending on your setup)
- Zipper library (refer to [here](https://github.com/sebastiandev/zipper) to install)

Of course, the commands to build vary from system to system. They generally should look like this:

```bash
cd /path/to/Downloader
meson build
ninja -C build
./build/Downloader
```

Make sure the working directory when running the program is the project root (a folder named Downloader). Otherwise, borealis cannot find the resources for the application.

# Credits

natinusala and contributors for making/maintaining borealis.

HamletDuFromage for the Zipper fork for Switch and idea of the `downloader-forwarder`.

sebastiandev for originally making Zipper.

# License

Downloader is licensed under the GPL v3.0 license. See license.md for more details.

borealis is licensed under the Apache v2.0 license. See lib/borealis/LICENSE for more details.

Zipper (fork from HamletDuFromage) is licensed under the MIT License. See lib/switch-zipper/LICENSE.md for more details.
