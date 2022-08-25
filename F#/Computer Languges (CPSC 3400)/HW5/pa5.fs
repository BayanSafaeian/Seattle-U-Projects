(*
    Bayan Safaeian HW4 F# assignment
    May 16, 2022
    The code written here is my own using only the slides as a reference
*)

let findMatches key ls =
    let rec tailRecurse acc = function //use tail recursion to find the value of the varible you're looking for
        | [] -> acc 
        | head :: tail -> 
        let k, v = head // k is the key in the tuple, v is the Value in the tuple
        tailRecurse ( if (key = k) then v :: acc else acc ) tail // if key is found append value onto the list, else ignore it
    let LS =tailRecurse [] ls 
    
    match LS with // once recursion is done check the result, if there's no match we just return the key
    | [] -> "" // if empty list return "" as the null value
    | _ -> LS[0].ToString()// otherwise return integer value in string form

//doOP performs a computation depending on the opperation symbol that's inputted
let doOP key ls = 
    //all computations done in this function require two items to be taken off the stack to perform the opperation on
    let SecondElm :: next = ls
    let FirstElm :: rest = next // The SecondElm is always the head, while the FirstElm is the value next to the head. 
    //Rest is the rest of stack without the first two elements on it

    let frElm = FirstElm|>int // The values contained in those varibles are converted to an integer in order to perform arithmatic opperations on them
    let scElm = SecondElm|>int
    match key with
    | str when str = "+" -> (frElm + scElm).ToString() :: rest //for arithmetic opperations the values are conputed ..
    | str when str = "-" -> (frElm - scElm).ToString() :: rest //.. converted to a string and put back on the rest of the stack
    | str when str = "*" -> (frElm * scElm).ToString() :: rest 
    | str when str = "/" -> (frElm / scElm).ToString() :: rest
    | str when str = "$" -> FirstElm :: SecondElm :: rest // Since the real order of the stack is SecondElm::FirstElm all this does is switch those postions
    | _ -> ls // all these pattern matches result in return it's respective stack, this one just returns a stack with no opperations done on it

//checkOP returns a bool used in determining if I need to call the doOP function
let checkOP str =
        let op = ["+";"-"; "*"; "/";"$"] // all the opperations that doOP does are in one list

        let rec loop found op= // all this loop does is check if str is a valid opperation, if it is return true, otherwise return false
            match op with  
                | [] -> found 
                | head :: tail -> loop (if str = head || found  then true else found) tail 
        loop false op

let push key ls = 
    match key with  
    | _ -> findMatches key ls // if key is found append value onto the opperations list, else ignore it

//this function finds if the key is a part of the varible list, then that means that key's value must be updated.
let find key ls =
    match ls with
    | head :: _ ->
        let rec loop found key ls= // all this loop does is check if str is a valid opperation, if it is return true, otherwise return false
            match ls with  
                | [] -> found 
                | head :: tail -> 
                let k,v = head
                loop (if key = k.ToString() || found  then true else found) key tail
        loop false key ls
    | _ -> false

//the bind function binds a key (varible) to it's value
let bind key val_ ls =
    match key with
    | key when find key ls -> ls |> List.map( fun(k,v) -> if key = k  then k, val_ else k,v ) // if key is already in the varbile list, find it and update it's value
    | key when key = "" -> ls // if the key entered is empty do nothing
    | _ -> List.rev ((key, val_) :: List.rev(ls)) // if the key isnt found append it and it's valeu to the end of the list

//eval is the main driving function, it takes the string and performs the computations in postfix Polish notation
let eval lsVar str = 
    let strLS = str |> Seq.toList // strLS is converted to a char list

    let rec tailRecurse acc ls lsVar = //ls is the char list entered in, lsVar is the list of varibles
        match ls with
        | [] -> acc 
        | head :: tail -> 
            let str = head.ToString()
            match str with
            | str when str = " " -> tailRecurse(acc) tail lsVar // if the current item is a space do nothing
            | str when checkOP str -> tailRecurse( doOP str acc) tail lsVar // if the current item is an operation, do that operation
            | str when str = "@" -> //if the operation is a "@" opperation bind the numerial value to it's key and opperate using the updated list
                let var :: tl = tail
                let newstr = var|>string// this just takes the next letter and assigns it the value of the next item on the stack
                let num :: restACC = acc
                let newVar = bind newstr (num|>int) lsVar 
                tailRecurse(restACC) tail newVar // the tail recursion is called with a new updated Varible list
            | _ -> tailRecurse( findMatches str lsVar :: acc) tail lsVar // if key is found append value onto the list, else ignore it
    let STRLS = tailRecurse [] strLS lsVar // return resulting operation 
    STRLS[0] |> int// return integer value of resulting computation.

//remove tests when turning in

let testEval = eval [("a",5);("b",2);("c",9)]  

let a = testEval "ab+"
let b = testEval "cab+-"
let c = testEval "cab+$-"
let d = testEval "ab+cb-*"
let e = testEval "ab+cb-* @d bd+"
let f = testEval "ab-ab*ab+--"
let g = testEval "bbb @q bqbq*****" 
let h = testEval "ca- @b bc$-"
let i = testEval "cabcab* @d ddd**@e e****"
let j = testEval "aaaaaaaaa ********"

let rec myFunc p lst =
    match lst with
    | [] -> []
    | head::tail -> (1 + p head)::(myFunc p tail)
let twodec x = x - 2
let test = myFunc twodec
let mylist = [for n in 1 .. 5 do yield n*n] |> test

printf "yolo"