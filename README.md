# dsPIC33 MotorBench Reference Projects

This repository contains reference MPLAB X projects targeting the **dsPIC33EP256MC506** microcontroller. The projects were generated with Microchip's [MotorBench](https://www.microchip.com/motorbench) tool and demonstrate basic motor control and peripheral usage on the **MCLV‑2** development board.

## Projects

The `all/` folder includes several example projects:

| Project | Description |
| ------- | ----------- |
| `sample-mb-33ep256mc506-mclv2.X` | Full MotorBench project configured for the MCLV‑2 board. Includes generated motor control drivers and HAL files. |
| `PWM-X2C-EXAMPLE.X` | Minimal example that enables PWM1 and blinks the on‑board LED. Useful as a starting point for experimenting with the PWM module. |
| `X2Cscope_blinky_dsPIC33EP_X2CDevBoard.X-master` | Demo showcasing X2Cscope integration. Generates simple waveforms and allows interaction through the scope interface. |

Each project comes with a companion `*-Makefile` that can be used for command‑line builds with `make`.

## Usage

1. Install [MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide) and the appropriate XC16 compiler.
2. Open the desired `.X` project from within the IDE or build it using its provided makefile:
   ```bash
   make -f sample-mb-33ep256mc506-mclv2.X-Makefile
   ```
3. Program the resulting `.hex` file to a dsPIC33EP256MC506 device mounted on the MCLV‑2 board.

## Demo

Below are two placeholders for demonstration GIFs.

![Motor running demo](docs/motor-demo.gif)

![PWM example demo](docs/pwm-demo.gif)

## License

The generated source files include Microchip's standard license text. See `all/sample-mb-33ep256mc506-mclv2.X/mcc_generated_files/motorBench/LICENSE.txt` for details.

