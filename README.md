# LibEsp32IDF

C++17 Library for Esp32 IDF version 5.0. 

## License

In each header license, copyright and tems has been added.

```C++
/** Copyright (C) 2023 brian_d (https://github.com/briand-hub)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
```

## Contents

This is my own utility library when I need to use ESP32/IDF system. 

This time library will be built as an **IDF Component**! I paste there my remarks and notes about how this project has been created. Documentation about creating an IDF Component is poor and component creation is a little bit tricky!

Includes utilities and simple, easy-to-use and ready-to-go objects to use ESP32 WiFi and check the System.

## Use as source (easier)

To be used as source, simply create a *components/* subfolder in your project, use git to add this repo there:

```
git clone https://github.com/briand-hub/LibEsp32IDF.git
mv .\LibEsp32IDF\components\briand_libesp32idf\ .
```

Remove the cloned repo, in your project *components* folder you should only have *briand_libesp32idf/* directory. That's all! Build your project and you're ready to go!

Remember to use the right target (esp32, esp32s3 and so on). Project must be built with IDF v5.0 (or above). You can also check the example for easy get started tutorial.

Of course, you can also download and add .hxx and .cpp files under *components/briand_libesp32idf* in your main/ folder!

## Use as static library (.a)

In order to use as a static library you can download .a file from *build/esp-idf/briand_libesp32idf/* directory and place it in your project directory under main/. Then you will need at least include files, otherwise would be impossible to use the library. Download .hxx files under components/briand_libesp32idf/includein your main/ folder.
At the end you should have your project main/ folder that contains both .hxx files and static .a file. 

Now you have to tell compiler to use .hxx and link .a file. To do that check your CMakeLists.txt in main/ folder. Should be like that:

```
idf_component_register(SRCS "main.cpp"
                    INCLUDE_DIRS ".")
```

You have to add the following lines at the end:

```
# This line is added to tell the project needs a static library and will be called briand_libesp32idf
# REQUIRES directive is needed and fit the library needs (see CMakeLists.txt of the library project)

add_prebuilt_library(briand_libesp32idf "libbriand_libesp32idf.a" REQUIRES esp_wifi spi_flash esp_psram nvs_flash)

# This line tells that a library must be linked together.

target_link_libraries(${COMPONENT_LIB} PUBLIC briand_libesp32idf)

```

## Use in Windows or Linux

Like the previous version I'd like to make it available also under linux and windows. It's enough easy even if not all objects will be working (of course, no wifi or bluetooth!).

# Project history: tutorial of this project and, generally, for static libraries (or, better, IDF Components)

In general, when ESP-IDF project is started with ``idf.py create-project`` command or ESP-IDF extension, it will include a main/main.c file and CMakeLists.txt file to build an ELF or binary ready to be flashed.

When project is built first time (or any time when editing sdkconfig) all IDF components/sources are compiled and the build/ directory will contain (under esp-idf subdir) the required components with its CMake files.

### IDF Component folder

What we would create is one of those components. An IDF Component is just a subfolder of components/ directory which contains at least a *component.mk* file and sources/headers.
So I started with an empty project created from ESP-IDF VSCode extension. I git-ignored the main folder and created a *component* directory then a subdirectory *briand_libesp32idf*.
The folder has .cpp files and a subdir with *includes/* containing .hxx files. (*note: an example/ dir is containing the original main.cpp file I used for testing!*).

### CMakeLists.txt file

Then let's start with IDF Component. First of all a CMakeLists.txt file must exist to tell compiler what to do with our files. File is very easy:

```CMake
# CMakeList file for component.

idf_component_register(SRCS "BriandLibEsp32IDF.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_wifi spi_flash esp_psram nvs_flash)
```

**WARNING: all sources .cpp files must be included in SRCS directive!**

This file must only include all sources we want to build (SRCS) and where to search for headers (INCLUDE_DIRS). The latest, REQUIRES, is the most tricky part! There must be listed all components (_IDF existing components_) that my component requires. Is enough easy to be discovered if you do not know all IDF components and related headers: just build and when an error like this:

```
In file included from C:/........./components/briand_libesp32idf/BriandLibEsp32IDF.cpp:17:
C:/............/components/briand_libesp32idf/include/BriandLibEsp32IDF.hxx:35:10: fatal error: esp_psram.h: No such file or directory
   35 | #include "esp_psram.h"
      |          ^~~~~~~~~~~~~
compilation terminated.
ninja: build stopped: subcommand failed.
```

It means that you are missing a component requirment. Just take a look at components/ folder under ESP-IDF installation sources or open the header. Will find the component name (easy: folder name). For example *esp_flash.h* header file is under (IDF_PATH) C:\Espressif\frameworks\esp-idf-v5.0\components\ **esp_psram** (containing esp_psram.h file!) then the component requirment is **esp_psram**. Just add it to REQUIRES and you're done!

#### Pure component without any app_main() ?

If that, just remove SRCS from CMakeLists.txt in main/ folder! Like that:

```
idf_component_register(INCLUDE_DIRS ".")
```

This will produce just build/ folder (see below) static file and nothing else!

### Build

Build project as usual (ESP-IDF Extension or ``idf.py build`` command). Here magic happens: under *build/esp-idf* directory created by build system you will find *briand_libesp32idf* folder created and inside it the **libbriand_libesp32idf.a** static file ready to be used :-D
In fact, IDF components are always built in static .a files and can be used in other projects (see above).

### Other notes

IDF Component may also have a KConfig file for sdkconfig but this is not discussed there. Maybe in future!

More informations could be found here: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html
