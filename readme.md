# About this Repository

This software repository represents initial efforts to learn about bare metal 
programming using C and ARM assembly with the Raspberry Pi Zero as the target
hardware. The binary produced is a kernel image that is intended to replace the
`kernel.img` file that is shipped with the current Raspberry Pi firmware.

This is a work in progress and is intended as a learning exercise more than
anything. Presently, it does little more than draw to the screen.

# Compiling and Running 

## Dependencies 

The code contained is intended to be cross-compiled for ARM using the GNU
Embedded Toolchain for ARM, `arm-none-eabi` and the GNU C Compiler, `gcc`.

## Compiling

The default make target will compile a kernel image at `dist/kernel.img` 

## Installation 

The kernel image produced is intended to replace the `kernel.img` distributed
with the Raspberry Pi. Assuming the Raspberry Pi firmware is already installed
on a storage medium, installation only consists of replacing the `kernel.img`
file with the new copy compiled from this code.

# Thanks and Resources

Working in an environment without an operating system is totally new for me and
I would not have been able to get very far at all without the wealth of resources
available online. The resources below were invaluable for me and hopefully will be
to anyone viewing this who wants to learn more about bare metal programming on the pi:

[University of Cambridge - Baking Pi](https://www.cl.cam.ac.uk/projects/raspberrypi/tutorials/os/index.html)

[VALVERS' Bare Metal Programming in C](http://www.valvers.com/open-software/raspberry-pi/step01-bare-metal-programming-in-cpt1/)

[Raspberry Pi Bare Metal Programming Forums](https://www.raspberrypi.org/forums/viewforum.php?f=72)
