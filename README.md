<h1 align="center">
  <br>
  <a><img src="media/logo.png" alt="avsys" width="400"></a>
  <br>
  avsys
  <br>
</h1>

<h4 align="center">My first Operating System.</a></h4>

<p align="center">
  <a href="https://github.com/averyocean65/avsys/actions"
    ><img
      src="https://img.shields.io/github/actions/workflow/status/averyocean65/avsys/makefile.yml"
      alt="GitHub Actions workflow status"
  /></a>
  <a href="https://twitter.com/averyocean65"
    ><img
      src="https://img.shields.io/badge/twitter-@averyocean65-1DA1F3?style=flat-square"
      alt="Follow @averyocean65 on Twitter"
  /></a>
</p>


<p align="center">
  <a href="#prerequisites">Prerequisites</a> •
  <a href="#installing-and-building">Installing</a> •
  <a href="#contributing">Contributing</a>
</p>

<p align="center">
  <a href="README.md"
    ><img
      height="20"
      src="media/flag-us.png"
      alt="English"
  /></a>
  &nbsp;
  <a
    href="media/README-ru.md"
    ><img
      height="20"
      src="media/flag-ru.png"
      alt="Русский"
  /></a>
</p>

## Prerequisites
- [GNU Compiler Collection](https://gcc.gnu.org/)
- [NASM](https://www.nasm.us/)
- [xorriso](https://www.gnu.org/software/xorriso/)
- [QEMU](https://www.qemu.org/)
- [mtools](https://www.gnu.org/software/mtools/)
- grub-common

## Installing and building
1. Make sure you have a [GCC](https://gcc.gnu.org/) set up.
2. Make sure the [Cross Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) is in your PATH.
3. ``make``
4. If the compilation succeeds, ``make run``
5. Enjoy!

## Contributing
If the compilation doesn't succeed, feel free to [open an issue](https://github.com/averyocean65/avsys/issues/new)!
