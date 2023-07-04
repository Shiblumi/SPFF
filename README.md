# :warning: **NOT DONE -- WORK IN PROGRESS -- POTENTIAL FOR FILE LOSS IF USED INCORRECTLY** :warning:


# ShadowPlay File Format (SPFF)
## What is SPFF
SPFF is a program that lets you reformat ShadowPlay filenames (clips & screenshots) within the directory where a game's Shadowplay files are stored.

## How to Use
SPFF uses a format string provided by the user to replace format specifiers within the string with the file's associated metadata.

### Format Specifiers
`{gn}`=game_name `{y}`=year 

`{m}`=month  `{mn}`=month_name `{mns}`=month_name_short

`{d}`=day    `{dn}`=day_name  `{dns}`=day_name_short

`{hr}`=hours `{min}`=minutes  `{sec}`=seconds  `{ms}`=milliseconds
  
### Example:
```
Original Filename:   "Game Name 2023-07-01 - 01-41-31-02.DVR.mp4"

Format String:       "{gn} - {mns} {d}, {y} ({dns}) - {hr}h.{min}m.{sec}s"

Modified Filename:   "Game Name - Jul 1, 2023 (Fri) - 01h.41m.31s"
```

To-Do:
[x] Add validation of modified filenames' correctness
[ ] Test this validation

[ ] Add option to get file's metadata directly from system (currently only gets it from a ShadowPlay's unmodified filename)