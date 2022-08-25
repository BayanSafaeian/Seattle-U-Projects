from ast import Dict
from collections import deque

#create a dictionary using words inputted from a external file
def create_dictionary(inputfile:str):
    dictionary = {}
    count = 0

    for word in open(inputfile):
        word = word.strip() #each word is shortend so that only the the length of the actual word is measured

        if(len(word) <= 7): #loop through each word and add it to the dictionary
            tup = {}
            tup[word] = count
            dictionary.update(tup)
            count += 1
    
    return dictionary

#returns lists of words that make up the word_ladder, or if no word ladder exists it only returns the initial word
def find_word_ladder(initial_word:str, final_word:str , dictionary:dict ):
    alph = "abcdefghijklmnopqrstuvwxyz" #alph contains all the letters of the alphabet

    hold_word = [initial_word] #hold_word contains the current version of the word ladder, this will be the list that is returned
    all_found_words= [initial_word] #hold word contains all the words currently found, 
    deq = deque()

    if(initial_word.__len__() != final_word.__len__()): #there is no word ladders with words of different lengths
        print("Words are of different length, no word ladder found for words: " + initial_word+", "+ final_word)
        return list()

    cur_word = initial_word
    while( not all_found_words.__contains__(final_word)): #algortihm continues until final word is found

        index_char = 0

        for ch in initial_word: #loops through each character of the word
            for ch in alph:
                my_word = cur_word
                my_word = my_word.replace(my_word[index_char], ch,1)# there are 25*ch number of different 'words' to look through that are 1 char apart from the cur_word
                tup = hold_word.copy()
                if( dictionary.__contains__(my_word) and not all_found_words.__contains__(my_word)): #if that word is in the dictionary then add it to the dictionary
                    tup.append(my_word)
                    deq.append(tup)#add word to the current constructed wordladder and add it onto the queue
                    all_found_words.append(my_word)
                    if (my_word == final_word):# if we found the word we return the current word ladder
                        return tup
            
            index_char += 1# keeps indexing through each char in the word

        if( deq.__len__() == 0): # if the length of the queue is 0, no word ladder is found
            print("Word ladder not found for word pair: " + initial_word+", "+ final_word)
            return list()

        pop = deq.popleft() #remove the earliest placed tuple on the queue
        cur_word = pop[-1] #cur word is always the last word in the list, that will be compared in the next iteration of the while loop
        hold_word = pop #set that queue as the current word_ladder that will be added to

#main
dictionary = create_dictionary("words.txt")

word_ladder = []
for line in open("pairs.txt"):
    line = line.strip()
    word1, word2 = line.split()
    word_ladder.append(find_word_ladder(word1,word2,dictionary)) # adds word_ladder lists to a word_ladder list.

print(word_ladder)
