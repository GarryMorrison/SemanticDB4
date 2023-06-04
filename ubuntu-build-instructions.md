# Semantic DB 4 Ubuntu build instructions

This text file gives brief build instructions for Ubuntu. For windows users, use the provided Visual Studio solution or use the [release .exe](https://github.com/GarryMorrison/SemanticDB4/releases).

The SDB4 code-base is divided into 3 parts, the core library, the CLI interface and the GUI interface. 
All three require the installation of flex and bison, and for windows [winflexbison](https://github.com/lexxmark/winflexbison).
The GUI interface further requires the installation of [wxWidgets](https://www.wxwidgets.org/).

First, we need to install these files:
```
sudo apt install build-essential cmake bison flex libfl-dev
```

For the GUI the full wxWidgets build instructions are [here](https://wiki.wxwidgets.org/Compiling_and_getting_started). 
We start by downloading the sources and if interested the docs from [here](https://www.wxwidgets.org/downloads/).
Then we run these commands:
```
sudo apt install libgtk-3-dev
cd wx/wxWidgets-3.2.2.1
mkdir buildgtk
cd buildgtk
../configure --with-gtk
make
sudo make install
sudo ldconfig
```

Now on to the SDB4 project:
```
wget https://github.com/GarryMorrison/SemanticDB4/archive/refs/heads/master.zip
unzip master.zip
mv SemanticDB4-master/ SemanticDB4/
mkdir build
cd build
```

For the core library only:
```
cmake ../SemanticDB4/
make
```

For the core library and the CLI:
```
cmake -DBUILD_CLI=ON ../SemanticDB4/
make
```

For all three:
```
cmake -DBUILD_GUI=ON -DBUILD_CLI=ON ../SemanticDB4/
make
```

Now a quick test of the CLI:
```
./SDB4_CLI ../SemanticDB4/sw-examples/temperature-conversion.sw4 

+---------+-----------+---------------+
| Celsius | to-Kelvin | to-Fahrenheit |
+---------+-----------+---------------+
| 0       | 273.15    | 32            |
| 5       | 278.15    | 41            |
| 10      | 283.15    | 50            |
| 15      | 288.15    | 59            |
| 20      | 293.15    | 68            |
| 25      | 298.15    | 77            |
| 30      | 303.15    | 86            |
| 35      | 308.15    | 95            |
| 40      | 313.15    | 104           |
| 45      | 318.15    | 113           |
| 50      | 323.15    | 122           |
| 55      | 328.15    | 131           |
| 60      | 333.15    | 140           |
| 65      | 338.15    | 149           |
| 70      | 343.15    | 158           |
| 75      | 348.15    | 167           |
| 80      | 353.15    | 176           |
| 85      | 358.15    | 185           |
| 90      | 363.15    | 194           |
| 95      | 368.15    | 203           |
| 100     | 373.15    | 212           |
+---------+-----------+---------------+
```

To enter the interactive agent:
```
./SDB4_CLI -i

Welcome to the Semantic DB version 4 shell.
Last updated 3rd June 2023.
Type h for help.
Online info for the SDB language at http://semantic-db.org/docs/usage4/

sa: 
```

And for the GUI:
```
./SDB4_GUI &
```

Congratulations! You have now installed the Semantic DB 4.
