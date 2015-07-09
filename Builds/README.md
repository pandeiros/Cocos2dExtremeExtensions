##Different builds compability check
###Windows (Visual Studio)
---
####Seting up a build
1)  Download a version of your choice from [here](http://www.cocos2d-x.org/download/version#Cocos2d-x).
2)  Run `install_build_win.bat` from the cmd with following arguments:

* First argument being your version and folder name as well (e.g. 3.4 or 3.6).
* Second argument being a path to corresponding cocos library root folder (e.g. C:\cocos\cocos2d-x-3.6).
* Third (optional) argument being compilation mode: either `release` or `debug` (or leave it empty with `debug` being default one).

*for example:
C:\PolyCocos\Builds> install_build_win.bat 3.5 C:\cocos\cocos2d-x-3.5 debug*

3) After project is prepared and compiled, libraries will be copied to version directory (e.g. `Builds/3.5/`).
4) Open `PolyCocosBuilds.sln` solution and manually add created `PolyCocos_VERSION.vcxproj` project to the solution.
5) Compile projects of your choice. Output files will be generated in `Debug_VERSION` or `Release_VERSION` directories and after build copied into `lib/VERSION/` directory.

####Clean
You can clean generated project file and cocos project folder with `clear_build_win.bat` script with one parameter being version you want to get rid of.
However, you still have to remove project from solution manually.

*for example:
C:\PolyCocos\Builds> clean_build_win.bat 3.5*
