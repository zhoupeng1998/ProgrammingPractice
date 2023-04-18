# Windows DLL Demo

### Building the Program

1. Use Visual Studio 2022 to build the mydll project
2. Copy `mydll/x64/Debug/mydll.dll` into `mycalc/mycalc`
3. Use Visual Studio 2022 to build the mycalc project

You can also use the `dumpbin /exports mydll.dll` in Developer Powershell to see the exposed symbols