![Project's banner](images/virtualOscilloscope_banner.png)

## 1.0 Files

| Files/Dirs   | Description                           |
|--------------|---------------------------------------|
| images       | Pictures for RADME.md file            |
| INSTALL.sh   | BASH script for software installation |
| lgpl-3.0.txt | Project's licence                     |
| src          | Project's source code                 |

## 2.0 Decription
Virtual Oscilloscope is a lightweight Qt-based application for visualizing signals stored in CSV files. It provides an
oscilloscope-like interface with adjustable X/Y scaling, multi-channel display, and interactive signal inspection, making it
useful for embedded development, data analysis, and filter debugging.

### 2.1 Build the source code
In order to build the software you need the standard QT libraries and the Qmake (ver 6) building tool. For the next step
enter in the <project>/src sub folder and type the following command:
	qmake6 && make
If you want to install just the binary, you can use the following command
	[PREFIX=<folder>] make install

### 2.2 Application installation
In order to build and install all the files you can run the *INSTALL.sh* script

## 3.0 Licence:
This project is a free software; you can redistribute it and/or modify it under the terms	of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 3.0 of the License, or (at your option) any later version. 

For further details please read the full [LGPL text file](https://www.gnu.org/licenses/lgpl-3.0.txt).
You should find a copy of the GNU General Public License document in the root folder of the project; if not, write to the 

	Free Software Foundation, Inc.,
	59 Temple Place, Suite 330,
	Boston, MA  02111-1307  USA
