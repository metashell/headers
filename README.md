# Headers

The purpose of this repository is to have multiple versions of headers of
different libraries in one place. By setting the right include path, one can
easily try different versions of the same library from utilities like
[Preshell](https://github.com/sabel83/preshell) or
[Metashell](https://github.com/sabel83/metashell).

## Structure

The `include` directory contains a sub-directory for each library. These
directories contain a sub-directory for each version of the library. Those
sub-directories should be added to the include path. For example to use Boost
version `1.54.0` and Loki version `0.1.7`, one should use
`-Iinclude/boost/0.54.0 -Iinclude/loki/0.1.7`.

## Components
This repository contains the following libraries:

* [Boost](http://www.boost.org/) (`1.21.1` - `1.54.0`)
* [Loki](http://loki-lib.sourceforge.net/) (`0.0.2` - `0.1.7`)

## Creating an installer

* `mkdir bin`
* `cd bin`
* `cmake ..`
* `cpack -G DEB` (Note that this step will take a long time to complete)


