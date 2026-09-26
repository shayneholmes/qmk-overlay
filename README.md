# Shayne's QMK repository

## Goals
- Host my QMK layout with version history
- Don't include all of QMK, because it's noisy and hard to keep track of
- Retain the relation to a particular version of QMK
- Hide the QMK repo from my backups

## Methods
Git submodules manage this well enough, with the `.nobackup` path added to
avoid getting picked up by my backups. The Makefile abstracts shenanigans,
including the rsync invocation necessary to update files in the correct
location and only as needed.

## Acknowledgements
Thanks to https://www.akpain.net/blog/qmk-submodules/ for inspiration.
