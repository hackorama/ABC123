ABC123 (2008)
=============

Created for my toddler to play on the laptop and learn alphabets and numbers.

This was way before tablets and thousands of applications for kids.

Bare bones single window application that will go full screen and will only respond to alphanumeric key strokes and won't lose focus.

![tag screenshot](https://github.com/hackorama/ABC123/blob/master/screenshots/screenshot-1.jpg)

![tag screenshot](https://github.com/hackorama/ABC123/blob/master/screenshots/screenshot-2.jpg)

![tag screenshot](https://github.com/hackorama/ABC123/blob/master/screenshots/screenshot-3.jpg)

To Build ABC123
---------------

### Using the Makefile

Bring Up Visual Studio Command Prompt

Start->All Programs->Visual C++ X.X XXX Edition->Visual Studio Tools->Visual Studio Command Prompt

Use name from Visual Studio command prompt to build using Makefile

    cd ABC123
    nmake /f Makefile res
    nmake /f Makefile run

### Using the VC++ IDE

Create an Empty Project (General -> Empty Project) and add all the source files including the resource.rc

Packaging ABC123
----------------

![tag installer](https://github.com/hackorama/ABC123/blob/master/screenshots/installer.png)

Check NSIS folder to see the packaging using NullSoft Installer.
Copy  msvcm90.dll, msvcp90.dll, msvcr90.dll from Visual Studio to NSIS/Microsoft.VC90.CRT/ and copy ABC123.exe to NSIS/

