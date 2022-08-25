"""
GEDCOM parser design

Create empty dictionaries of individuals and families
Ask user for a file name and open the gedcom file
Read a line
Skip lines until a FAM or INDI tag is found
    Call functions to process those two types

Processing an Individual
Get pointer string
Make dictionary entry for pointer with ref to Person object
Find name tag and identify parts (surname, given names, suffix)
Find FAMS and FAMC tags; store FAM references for later linkage
Skip other lines

Processing a family
Get pointer string
Make dictionary entry for pointer with ref to Family object
Find HUSB WIFE and CHIL tags
    Add included pointers to Family object
Skip other lines

Testing to show the data structures:
    Print info from the collections of Person and Family objects
    Print descendant chart after all lines are processed

"""
from collections import namedtuple
from multiprocessing.dummy.connection import families
from xxlimited import new

#-----------------------------------------------------------------------

class Person():
    # Stores info about a single person
    # Created when an Individual (INDI) GEDCOM record is processed.
    #-------------------------------------------------------------------

    def __init__(self,ref):
        # Initializes a new Person object, storing the string (ref) by
        # which it can be referenced.
        self._id = ref
        self._asSpouse = []  # use a list to handle multiple families
        self._asChild = None
                
    def addName(self, names):
        # Extracts name parts from a list of names and stores them
        self._given = names[0]
        self._surname = names[1]
        self._suffix = names[2]

    def addIsSpouse(self, famRef):
        # Adds the string (famRef) indicating family in which this person
        # is a spouse, to list of any other such families
        self._asSpouse.append(famRef)
        
    def addIsChild(self, famRef):
        # Stores the string (famRef) indicating family in which this person
        # is a child
        self._asChild = famRef

    def printDescendants(self, prefix=''):
        # print info for this person and then call method in Family
        print(prefix + self.name())
        # recursion stops when self is not a spouse
        for fam in self._asSpouse:
            families[fam].printFamily(self._id,prefix)

    def printAncestors(self, prefix= '', gen= 0):
        print("|"+prefix + self.name()) #print out name of individual

        gen +=1 #increase generation 
        prefix = prefix +"  |" + str(gen) #adds a tab and number for every generation
        prefix = prefix.replace(str(gen-1), " ")# removes previous generation numbers for a cleaner output

        if(self._asChild != None):# if the person isn't a child of a family in the database stop searching
            fam =  families[self._asChild]
            spouse1 = fam._spouse1.personRef #after finding the parents of the child. Call printAncestors on both parents.
            getPerson(spouse1).printAncestors(prefix,gen)
            spouse2 = fam._spouse2.personRef
            getPerson(spouse2).printAncestors(prefix, gen)

    def printCousins(self, n=1, prefix= '', level=0, printMode = False):
        if(level == 0):#only prints out the person that called the method
            print(prefix +self.name())

        if(printMode):#print mode looks through all decendants and prints out the children that are the same level as self
            if(level == 1 ):

                for fam in self._asSpouse: 
                    _neices_nephews = families[fam]._children #find all the cousins in your family
                    
                    for cousins in _neices_nephews:
                        print(prefix +getPerson(cousins).name())#print cousins that are the same level as you
                return

            level += -1

            for fam in self._asSpouse:
                relatives = families[fam]._children #find children of _Grandparents and process them

                for rel in relatives:
                    getPerson(rel).printCousins(n,prefix,level-1, printMode)

        else: #when not in print mode go up the tree n levels and print cousins

            if self._asChild != None:# if the person isn't a child of a family in the database stop searching
                fam =  families[self._asChild]
                _parent1 = getPerson(fam._spouse1.personRef) #after finding the parents of the child. Call printAncestors on both parents.
                _parent2 = getPerson(fam._spouse2.personRef)
                
                level += 1
                prefix = prefix +"  |" + str(level) +" "  #adds a tab and number for every cousin level
                prefix = prefix.replace(str(level-1), "")# removes previous level numbers for a cleaner output

                _parent1.auntsUncles_printCousins(n,prefix,level)
                _parent2.auntsUncles_printCousins(n,prefix,level)

                if level < n:
                    _parent1.printCousins(n,prefix,level, printMode=False) #keep on going up the tree until n levels
                    _parent2.printCousins(n,prefix,level, printMode=False)

    def auntsUncles_printCousins(self, n, prefix, level, printMode = True):
        if self._asChild != None: #go through each parents family
            _AuntsAND_Uncles = families[self._asChild]._children
                
            for A_U in _AuntsAND_Uncles:
                if A_U != self._id:
                    getPerson(A_U).printCousins(n,prefix,level, printMode) #for aunts and uncles, print only decendants that are level 0

    def name (self):
        # returns a simple name string 
        return self._given + ' ' + self._surname.upper()\
               + ' ' + self._suffix
    
    def treeInfo (self):
        # returns a string representing the structure references included in self
        if self._asChild: # make sure value is not None
            childString = ' | asChild: ' + self._asChild
        else: childString = ''
        if self._asSpouse != []: # make sure _asSpouse list is not empty
            # Use join() to put commas between identifiers for multiple families
            # No comma appears if there is only one family on the list
            spouseString = ' | asSpouse: ' + ','.join(self._asSpouse)
        else: spouseString = ''
        return childString + spouseString
    
    def eventInfo(self):
        ## add code here to show information from events once they are recognized
        string = ''
        for events in event[self._id]: #gets all events in a persons life
            string = string + events.getStr()

        for fam in self._asSpouse:
            for events in event[fam]:
                string = string + events.getStr()

        return string

    def __str__(self):
        # Returns a string representing all info in a Person instance
        # When treeInfo is no longer needed for debugging it can 
        return self.name() \
                + self.eventInfo()  \
                + self.treeInfo()  ## Comment out when not needed for debugging

    def isDescendant(self, personID,gen =0):
        if self._id == personID: #check if the decendant is found
            print(gen)
            return True #if person in question is a decendant return true

        for fam in self._asSpouse: #get families that they are spouses of
            family = getFamily(fam)
            children = family._children #get children of those familes

            for child in children:
                if getPerson(child).isDescendant(personID,gen+1):#check if the decendants of the children are the person in question
                    return True
        
        return False #if no decendants are found return false

    def printGenChange(self,personID,gen=0):
        if(self._id == personID):
            return gen
        elif (self._asChild == None):
            return None
        
        fam = families[self._asChild]
        par1 = fam._spouse1.personRef
        par2 =fam._spouse2.personRef

        genpar1 = getPerson(par1).printGenChange(personID,gen+1)
        genpar2 = getPerson(par2).printGenChange(personID,gen+1)

        if(genpar1 != None):
            return genpar1
        else:
            return genpar2
        
        
# end of class Person
 
#-----------------------------------------------------------------------

# Declare a named tuple type used by Family to create a list of spouses
Spouse = namedtuple('Spouse',['personRef','tag'])

class Family():
    # Stores info about a family
    # An instance is created when an Family (FAM) GEDCOM record is processed.
    #-------------------------------------------------------------------


    def __init__(self, ref):
        # Initializes a new Family object, storing the string (ref) by
        # which it can be referenced.
        self._id = ref
        self._spouse1 = None
        self._spouse2 = None
        self._children = []

    def addSpouse(self, personRef, tag):
        # Stores the string (personRef) indicating a spouse in this family
        newSpouse = Spouse(personRef, tag)
        if self._spouse1 == None:
            self._spouse1 = newSpouse
        else: self._spouse2 = newSpouse

    def addChild(self, personRef):
        # Adds the string (personRef) indicating a new child to the list
        self._children.append(personRef)
        
    def printFamily(self, firstSpouse, prefix):
        # Used by printDecendants in Person to print other spouse
        # and recursively invoke printDescendants on children

        # Manipulate prefix to prepare for adding a spouse and children
        if prefix != '': prefix = prefix[:-2]+'  '
        
        # Print out a '+' and the name of the second spouse, if present
        if self._spouse2:  # check for the presence of a second spouse
            # If a second spouse is included, figure out which is the
            # "other" spouse relative to the descendant firstSpouse
            if self._spouse1.personRef == firstSpouse:
                secondSpouse = self._spouse2.personRef
            else: secondSpouse = self._spouse1.personRef
            print(prefix+ '+' + persons[secondSpouse].name())

        # Make a recursive call for each child in this family
        for child in self._children:
             persons[child].printDescendants(prefix+'|--')
        
    def __str__(self):
        ## Constructs a single string including all info about this Family instance
        spousePart = ''
        for spouse in (self._spouse1, self._spouse2):  # spouse will be a Spouse namedtuple (spouseRef,tag)
            if spouse:  # check that spouse is not None
                if spouse.tag == 'HUSB':
                    spousePart += ' Husband: ' + spouse.personRef
                else: spousePart += ' Wife: ' + spouse.personRef
        childrenPart = '' if self._children == [] \
            else' Children: ' + ','.join(self._children)
        return spousePart + childrenPart

# end of class Family

#-----------------------------------------------------------------------

class Event():
    def __init__(self, ref): #initalize event object
        self.eventRef = ref
        self.date= None
        self.place= None
        self.tag= None

    def addEvent(self,tag): #add event tag to label the event
        self.tag = tag
    
    def updateEvent(self,date,place): #update information regarding the event

        if date != None: self.date= date

        if place != None: self.place= place

    def getStr(self): # get information about the event object into string form
        tag =''
        date=''
        place=''

        if self.tag == None:
            return ''

        if self.date != None: date = self.date
        if self.place != None: place = self.place
        if self.tag == "BIRT" : tag = "BIRTH"
        if self.tag == "DEAT": tag = "DEATH"
        if self.tag == "MARR": tag = "MARRIDGE"

        return " "+tag + " " + date + " " + place
            

        

#end of class Event

#-----------------------------------------------------------------------
# Global dictionaries used by Person and Family to map INDI and FAM identifier
# strings to corresponding object instances

persons = dict()  # saves references to all of the Person objects
families = dict() # saves references to all of the Family objects
event = dict() #saves references to all of the Event objects

## Access functions to map identifier strings to Person and Family objects
## Meant to be used in a module that tests this one

def getPerson (personID):
    return persons[personID]

def getFamily (familyID):
    return families[familyID]

def getEvent (personID): #use personID to return a list of events that are connected to that person
    return event[personID]

## Print functions that print the info in all Person and Family objects 
## Meant to be used in a module that tests this one
def printAllPersonInfo():
    # Print out all information stored about individuals
    for ref in sorted(persons.keys()):
        print(ref + ':' + str(persons[ref]))
    print()

def printAllFamilyInfo():
    # Print out all information stored about families
    for ref in sorted(families.keys()):
        print(ref + ':' + str(families[ref]))
    print()

#-----------------------------------------------------------------------
eventTag = ["BIRT","DEAT","MARR","DATE","PLAC"]
count_Event = 0
def processGEDCOM(file):

    def getPointer(line):
        # A helper function used in multiple places in the next two functions
        # Depends on the syntax of pointers in certain GEDCOM elements
        # Returns the string of the pointer without surrounding '@'s or trailing
        return line[8:].split('@')[0]
            
    def processPerson(newPerson, ):
        nonlocal line
        line = f.readline()
        while line[0] != '0': # process all lines until next 0-level
            tag = line[2:6]  # substring where tags are found in 0-level elements
            if tag == 'NAME':
                names = line[6:].split('/')  #surname is surrounded by slashes
                names[0] = names[0].strip()
                names[2] = names[2].strip()
                newPerson.addName(names)

                lastEvent = None
                event[newPerson._id] = list() #everytime person is stored their events will be kept together in one list

            elif tag == 'FAMS':
                newPerson.addIsSpouse(getPointer(line))
            elif tag == 'FAMC':
                newPerson.addIsChild(getPointer(line))
            ## add code here to look for other fields
            elif eventTag.__contains__(tag):
                field = line[6:].strip()
                lastEvent = processEvent(lastEvent,newPerson,tag, field,count_Event) #take all the data from process person and

            # read to go to next line
            line = f.readline()

    def processFamily(newFamily):
        nonlocal line
        line = f.readline()
        while line[0] != '0':  # process all lines until next 0-level
            tag = line[2:6]

            if not event.__contains__(newFamily._id) :
                lastEvent = None
                event[newFamily._id] = list() #everytime a family is stored their events will be kept together in one list

            if tag == 'HUSB':
                newFamily.addSpouse(getPointer(line),'HUSB')
            elif tag == 'WIFE':
                newFamily.addSpouse(getPointer(line),'WIFE')
            elif tag == 'CHIL':
                newFamily.addChild(getPointer(line))
            ## add code here to look for other fields 
            elif eventTag.__contains__(tag):
                field = line[6:].strip()
                lastEvent = processEvent(lastEvent,newFamily,tag, field,count_Event) #take all the data from process person and

            # read to go to next line
            line = f.readline()

    def processEvent(newEvent,newObject,tag, field, countEvent): #takes input from
        if(newEvent == None):
            ref = "E"+ str(countEvent)
            newEvent = Event(ref)
            event[newObject._id].append(newEvent)
            countEvent += 1

        if tag == "BIRT" :
            if newEvent.tag == None : #if there's no tag then BIRTH must be the event in question
                newEvent.addEvent(tag="BIRT")
            else:
                ref = "E"+ str(countEvent)
                newEvent = Event(ref)
                event[newObject._id].append(newEvent)
                countEvent += 1

        elif tag == "DEAT": #code for birth is repeated for death and marridge
            if newEvent.tag == None : 
                newEvent.addEvent(tag="DEAT")
            else:
                ref = "E"+ str(countEvent)
                newEvent = Event(ref)
                event[newObject._id].append(newEvent)
                countEvent += 1

        elif tag == "MARR":
            if newEvent.tag == None : 
                newEvent.addEvent(tag="MARR")
            else:
                ref = "E"+ str(countEvent)
                newEvent = Event(ref)
                event[newObject._id].append(newEvent)
                countEvent += 1

        elif tag == "DATE":
            newEvent.date = field
            
        elif tag == "PLAC":
            newEvent.place = field

        return newEvent #return event for potential further processing


    ## f is the file handle for the GEDCOM file, visible to helper functions
    ## line is the "current line" which may be changed by helper functions

    f = open (file)
    line = f.readline()
    while line != '':  # end loop when file is empty
        fields = line.strip().split(' ')
        # print(fields)
        if line[0] == '0' and len(fields) > 2:
            # print(fields)
            if (fields[2] == "INDI"): 
                ref = fields[1].strip('@')
                ## create a new Person and save it in mapping dictionary
                persons[ref] = Person(ref)
                ## process remainder of the INDI record
                processPerson(persons[ref])
                
            elif (fields[2] == "FAM"):
                ref = fields[1].strip('@')
                ## create a new Family and save it in mapping dictionary
                families[ref] = Family(ref) 
                ## process remainder of the FAM record
                processFamily(families[ref])
                
            else:    # 0-level line, but not of interest -- skip it
                line = f.readline()
        else:    # skip lines until next candidate 0-level line
            line = f.readline()

    ## End of ProcessGEDCOM

#-----------------------------------------------------------------------    
## Test code starts here
            
def _main():
    filename = "Kennedy.ged"  # Set a default name for the file to be processed
##    Uncomment the next line to make the program interactive
##    filename = input("Type the name of the GEDCOM file:")

    processGEDCOM(filename)

    printAllPersonInfo()

    printAllFamilyInfo()
    
    person = "I46"  # Default selection to work with Kennedy.ged file
##    Uncomment the next line to make the program interactive
##    person = input("Enter person ID for descendants chart:")

    getPerson(person).printDescendants()

    #string = getPerson(person).__str__()

    isD = getPerson(person).isDescendant("I69")
    print(isD)

    #getPerson("I69").printAncestors()

    getPerson("I69").printCousins(10)
    print(str(getPerson("I69").printGenChange("I46")))

if __name__ == '__main__':
    _main()

