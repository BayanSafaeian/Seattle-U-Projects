//Bayan Safaeian HW4 F# assignment
// May 5, 2022
// The code written here is my own, I only refered to the slides for the loops used in part 1 and 2.

//part 1
let maxCubeVolume ls = 
    match ls with
    | [] -> 0.0
    | _ ->
            let cubeVol  = function //cubeVol takes an element in the list and calculates and returns the volume in that cube
                | (a,b,c) -> a*b*c

            let rec loop max ls= //recursively loop through list multiplying the volumes and..
                match ls with  //..Retriving the maximum volume to the client
                | [] -> max 
                | head :: tail -> loop (if (cubeVol head) > max then (cubeVol head) else max) tail //if new volume is greater than max then make that the new max, else ignore it
            loop 0.0 ls

//part2

let findMatches key ls = 
    match ls with
    | head :: tail ->
        let rec tailRecurse acc = function // do a tail recursition to get back all the int values on the list 
            | [] -> acc 
            | head :: tail -> 
            let k, v = head // k is the key in the tuple, v is the Value in the tuple
            tailRecurse ( if (key = k) then v :: acc else acc ) tail // if key is found append value onto the list, else ignore it
        List.sort( tailRecurse [] ls ) // return sorted list

    | _ ->  List.empty<int> // if empty list is entered no matches found so return empty list

//part3

// Tree definition for problem 3
type BST =
    | Empty
    | TreeNode of int * BST * BST

let rec insert value tree = 
    match tree with
    |   Empty ->TreeNode(value,Empty,Empty) // if the tree is empty and value is inserted make a new node with value as it's data
    |   TreeNode(data, left,right )->
            match data with
            |  data when data > value -> TreeNode(data,insert value left, right) // if value entered < data in the node traverse left
            |  data when data < value -> TreeNode(data,left,insert value right) // if value entered > data in the node traverse left
            |  _ -> tree // if equal return the tree and do nothing 

let rec contains value tree =
    match tree with
    |   Empty -> false // if there's no tree it's always false because there's no value 
    |   TreeNode(data, left,right )->
            match data with
            |  data when data > value -> contains value left // traverse left subtree when value is less than data in the node
            |  data when data < value -> contains value right // otherwise traverse right
            |  _ -> true // if data is found return true


let rec count func tree =
    match tree with
    |   Empty -> 0 // empty trees always have zero events
    |   TreeNode(data, left,right )->
        let total = count func left + count func right //calculate total value of count function for both subtrees
        match data with
        | data when func data-> 1 + total // if function returns true for data in a node add one to total and return it
        | _ -> 0 + total // otherwise return just the total

let evenCount tree = 
    count (fun x-> x%2 =0) tree // fun x-> x%2 =0 is an anonymous function that determines when a value is odd or even using modulo

//test remove later 
let bt1 = insert 10 Empty
let bt2 = insert 5 bt1
let bt3 = insert 3 bt2
let bt4 = insert 17 bt3
let bt5 = insert 12 bt4
let bt6 = insert 24 bt5

let gtTen x = x > 10
let a = count gtTen bt6
let even = evenCount bt6

//--- code improvement

printf "done"
