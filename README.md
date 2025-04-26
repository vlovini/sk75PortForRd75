# sk75PortForRd75

This project is a port of the Womier SK75 firmware code to the Womier RD75 / PMO Wave75 keyboard.

## Background

- This port is based on the [SK75 from LiuLiuQMK](https://github.com/qmk/qmk_firmware/pull/24601), a pull request that was ultimately rejected from the QMK repository.
- As a base for the RD75-specific code, the [official RD75 firmware from Wormier](https://github.com/womierkeyboard/RD75) was used.  
  ⚠️ Note: The Wormier branch does not build properly out of the box.
- The SK75 and RD75 keyboards share a lot of similarities in terms of hardware and firmware structure, but they differ in their "common" code, requiring careful adaptation.

## Current Status

- The firmware **builds successfully**.
- However, it is **not functional yet**:  
  - The keyboard displays erratic LED behavior.
  - No keypresses are detected.
- Troubleshooting and debugging are ongoing to bring the port to a usable state.

## Project Contents

- **Original Firmware:**  
  The original built firmware provided by Wormier support is included for reference and comparison.
- **VIA JSON:**  
  A corrected and enhanced `via.json` file is included, with improved keymap details and compatibility information.

## Goals

- Get the port fully functional on the RD75 / Wave75 hardware.
- Enable VIA/VIAL configurability.
- Clean up and organize the code for possible future PRs or custom builds.

## Notes

This project is currently a **work in progress**.  
Contributions, testing, and debugging help are very welcome!
