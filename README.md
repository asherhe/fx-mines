<div align="center">
    <img width="25%" src="assets-fx/splash.png" alt="fx-mines logo" />
</div>

<h1 align="center">fx-mines</h1>

A basic minesweeper clone for CASIO fx-9860G series calculators.

This software was tested on a fx-9750GIII calculator, but it should ideally work on any fx-9860G series calculator. At present there is no support for color graphing calculators as I do not own one for development.

## How to Play

Press any key to exit the splash screen

- Arrow keys to move the cursor.
- `EXE` to clear a cell
- `1` to flag/unflag a cell

Uncovered cells will indicate the number of neighboring mines. The goal is to determine the positions of the mines and uncover all other cells.

Upon winning/losing, press any key to play again. `MENU` can be used to return to main menu.

## Building

To build fx-Mines for yourself, first install [fxSDK](https://gitea.planet-casio.com/Lephenixnoir/fxsdk#installing), a versatile development kit for add-ins for both fx-9860G and CG50 series calculators.

Afterwards, simply clone this repository and run

```
$ fxsdk build-fx
```

to build a G1A file for fx-9860G calculators. Executing this add-in is simply a matter of copying this file into the root directory of your calculator.
