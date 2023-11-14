# Turing Machine in C

It is a simple program that can execute turing machine programs

### Usage
```turing_machine.exe <file_with_instructions.tu> [-s [input]]```

### Usage examples:
-   #### Binary increment

    Command: ```turing_machine.exe instructions.tu```

    Input + Output:
    ```
    Enter start ribbon:100
    
    _100___________________________
        ^
    Executing: 0 _ < increment
    
    _100___________________________
       ^
    Executing: increment 0 1 move_right
    
    _101___________________________
       ^
    Executing: move_right 1 > move_end
    
    _101___________________________
        ^
    Executing: move_end _ # move_end
    Ended!
    ```


-   #### Binary increment (silent)

    Command: ```turing_machine.exe instructions.tu -s```

    Input + Output:
    ```
    Enter start ribbon: 100
    _101___________________________
    ```


-   #### Binary increment (silent)
    Command: ```turing_machine.exe instructions.tu -s 100```

    Output:
    ```
    _101___________________________
    ```


### instructions.tu Syntax
```
<current_state> <current_symbol> <new_symbol> <new_state>
# Comment
```

It means that if turing machine is in state `current_state` 
and carriage points to `current_symbol`, new symbol and new state will be set.

It also supports comments started with `#`

##### Example: 
```
# Program that will increment binary number
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
```

##### You can find more examples in `examples` folder