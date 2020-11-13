# The Game of Patterns

## Installing

You can install the game by simply running:

```bash
make
make install
```

Keep in mind that you may have to run these as root.

To run the game, run `gameofpatterns`.

To uninstall the game, run `make uninstall` or `make clean`.

## How to Play

Complete the numeric pattern you are randomly given. You are prompted
with 4 items, and then must complete the pattern up to 10.

## Features

* There are currently 10 patterns to solve (with more being actively added)
* The game doesn't repeat patterns until you have completed them all (as of v0.2.0)
* The pattern is auto-solved if you make a mistake

## A Note about the Versions

I released versions 0.1.0 and 0.2.0 alongside v0.3.0 to keep everything in order when I tranferred the
code to GitHub. Note that these two versions have no Makefile and are only available in a tarball format
(no zip archive included). You can use these versions, but I suggest using the latest version.
