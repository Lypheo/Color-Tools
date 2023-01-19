```py
core.color.ShowGamut(clip clip[, string gamut])
```
Plots the 1931 chromaticity diagram, highlighting the specified gamut (or nothing if not supplied/``gamut == ""``).
All colors that appear in a given frame are colored black in the diagram, or white if they lie outside the specified gamut.

Expects linear XYZ clips which you can obtain like so, for example:
```py
linear = core.resize.Point(src, format=vs.RGBS, range_in_s="full", transfer_in_s="srgb", transfer_s="linear")
xyz = core.resize.Point(linear, primaries_in_s="709", primaries_s="xyz")
```
It may be necessary to clamp linear RGB values if converting from YCbCr in order to avoid pixels outside the images’s gamut being marked.

Supported gamuts:
```
"dcip3"
"adobe98"
"adobewide"
"apple"
"ciergb"
"filmc"
"jedec_p22"
"470bg"
"470m"
"2020"
"smpte_c"
```