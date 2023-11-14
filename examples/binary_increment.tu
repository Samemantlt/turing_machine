# eg. 001 -> 010
# eg. 0010 -> 0011
# eg. 111 -> 1000

0 _ < increment

increment 0 1 move_right
increment 1 < increment
increment _ 1 move_right

move_right 1 > move_end
move_right 0 > move_end

move_end 0 > move_end
move_end 1 0 move_end
move_end _ # move_end