# eg. 11100110 -> 00011001

0 _ < invert

invert 1 0 move_left
invert 0 1 move_left
invert _ # invert

move_left 1 < invert
move_left 0 < invert