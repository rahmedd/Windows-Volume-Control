# Windows Volume Control

This is a simple tool for controlling windows master volume through the [Windows Core Audio APIs](https://docs.microsoft.com/en-us/windows/win32/api/endpointvolume/nf-endpointvolume-iaudioendpointvolume-getmastervolumelevel), without emulating multiple volume key presses. This is for applications that require direct control of the **volume percentage**.

All credits go to the original author of the ChangeVolume function, [Sayyed Mostafa Hashemi from codeproject.com](https://www.codeproject.com/Tips/233484/Change-Master-Volume-in-Visual-Cplusplus)

## Usage
Runs the [executable](https://github.com/rahmedd/Windows-Volume-Control/releases) with percentage as an argument.

Command Prompt:
```python
volctrl.exe 35
```
Python 3:
```python
import subprocess

percentage = 0
for i in range(3):
	subprocess.run("volctrl.exe " + str(percentage), shell=True)
	percentage += 10 #increases volume by 10%
```
## Compiling

Compiled on Windows 10 in Visual Studio 2019 Community Edition.

Or download from [releases](https://github.com/rahmedd/Windows-Volume-Control/releases).

