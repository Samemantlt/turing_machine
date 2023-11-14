# eg. 111001 -> 100111

0 _ < reverse

reverse 0 < move_left_and_set_0
reverse 1 < move_left_and_set_1
reverse @ > move_to_end
reverse ! > move_to_end

# Left 0

move_left_and_set_0 0 < move_left_and_set_0
move_left_and_set_0 1 < move_left_and_set_0

move_left_and_set_0 _ > left_set_0
move_left_and_set_0 ! > left_set_0
move_left_and_set_0 @ > left_set_0


left_set_0 0 @ shift_right_and_set_0
left_set_0 1 @ shift_right_and_set_1
left_set_0 @ > move_to_end
left_set_0 ! > move_to_end


# Left 1

shift_left ! < reverse
shift_left @ < reverse

move_left_and_set_1 0 < move_left_and_set_1
move_left_and_set_1 1 < move_left_and_set_1

move_left_and_set_1 _ > left_set_1
move_left_and_set_1 ! > left_set_1
move_left_and_set_1 @ > left_set_1


left_set_1 0 ! shift_right_and_set_0
left_set_1 1 ! shift_right_and_set_1
left_set_1 @ > move_to_end
left_set_1 ! > move_to_end


# Right

shift_right_and_set_0 ! > move_right_and_set_0
shift_right_and_set_0 @ > move_right_and_set_0

move_right_and_set_0 0 > move_right_and_set_0
move_right_and_set_0 1 > move_right_and_set_0

move_right_and_set_0 _ < right_set_0
move_right_and_set_0 ! < right_set_0
move_right_and_set_0 @ < right_set_0


right_set_0 0 @ shift_left
right_set_0 1 @ shift_left
right_set_0 @ > move_to_end
right_set_0 ! > move_to_end


# Right 1

shift_right_and_set_1 ! > move_right_and_set_1
shift_right_and_set_1 @ > move_right_and_set_1

move_right_and_set_1 0 > move_right_and_set_1
move_right_and_set_1 1 > move_right_and_set_1

move_right_and_set_1 _ < right_set_1
move_right_and_set_1 ! < right_set_1
move_right_and_set_1 @ < right_set_1

right_set_1 0 ! shift_left
right_set_1 1 ! shift_left
right_set_1 @ > move_to_end
right_set_1 ! > move_to_end


move_to_end ! > move_to_end
move_to_end @ > move_to_end
move_to_end 1 > move_to_end
move_to_end 0 > move_to_end
move_to_end _ < fix_chars


# Fixing chars @ -> 0; ! -> 1

fix_chars ! 1 fix_chars
fix_chars @ 0 fix_chars
fix_chars 1 < fix_chars
fix_chars 0 < fix_chars
fix_chars _ > move_to_end_2

move_to_end_2 1 > move_to_end_2
move_to_end_2 0 > move_to_end_2
move_to_end_2 _ # move_to_end_2