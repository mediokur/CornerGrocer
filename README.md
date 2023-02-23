# CornerGrocer
## CS-210 Portfolio Project Submission
### Project Overview
This program was designed to take a text file comprised of names of objects at a grocery store, and then store them into a data structure while keeping track of the
frequency of each word (how many times each word has shown up on the text file which relates to a purchase record). The program continues to provide a user interface
that allows a user to interact with the extracted data by querying an object and being returned the frequency of that object in the record if it exists. Through the 
main menu in the user interface, the user can also have 2 different text files printed out to the project directory. One document is each object that was present in 
the given text file with its frequency (how many times it showed up in the original text file) right next to it. The second document is also each object, however 
instead of the frequency of that object being represented by a number, the output is an asterisk that gets printed the same amount of times as the frequency of that
object. This creates a histogram so that the user can which objects have greater frequency than others visually and rapidly without having to compare number values.
Every single menu option also prints out anything that is requested by the user to the CLI so that the user doesn't need to go digging for the output files if they 
simply want a quick check of the objects in the system. I believe the program has good readability/maintainability due to the comments I have placed throughout
the program, as well as the structure. Just about any core function that the program performs is split into its own method such that commenting out and experimenting
with the code, and commenting back in when needed is intuitive, and keeps the screen clean due to all the collapsing methods in the IDE.

### Point of Pride and the Challenge
I think I did well in my *itemLookup()* method, which proved more difficult than I imagined it would be. I needed to perform string comparison for every string object
in the map I stored all of the text data in against a user input. I knew that all string in my map had an uppercase first letter, and I wanted to keep it like that
to simplify file writing for the other menu options. I initially thought to iterate through every key in my map, iterate through every letter of the key during the loop
to lowercase the word and store it into a vector, while simultaneously taking the value of the map(the frequency of that word) and store it into another vector and ensure
that inserts occurred at the same time so I could retrieve a lower case word at its index value, which I would use to extract the integer value from the corresponding 
vector. I ended up removing this execution once it was functional because I realized that it created a major flaw in the program, if one single developer at any point
were to take this code and accidentally push a value into either vector without updating the corresponding vector correctly, it would keep the program fully functional
but provide bad information without raising any flags. I kept the original map so that the frequency of a word was tied to it at every level, and then used storage
variables to pull both the user input and map keys into for the iteration, so that the variables can be lowercased for string comparison(C++ standard libraries do not
allow for case insensitive string comparison). This meant that the original data was preserved so that a user can make menu selections in any order without the formatting
of the printouts being affected. This was the most challenging method to
write because there are so many other ways this could be performed, and I believe the method I used is the best I could think of since I do not think 
an input and map key iteration and comparison could occur with fewer than 1 nested conditional/loop.  Below is the code block for that method, but can also be found in context in the files.
```c++

void grocerMenu::itemLookUp() {
    
    std::cout << "Please enter the name of the item you are looking to find a quantity for:";
    cin >> localString; //stores user input to this string variable so it can be lowercased for comparison
    unalteredString = localString; //before lowercasing occurs, copies the information of what was just typed so it can be returned to the user later
    for (int i = 0; i < localString.length(); i++) {
        localString[i]=tolower(localString[i]); //iterates through every letter of the input and lowercases it
    }
    for (auto& word : wordCounter) { //iterate through every single key,value pair in my wordCounter map
        holdingStringMap = word.first; //take the first value(which for this map is the object name) and toss it into a storage variable
        for (int i = 0; i < holdingStringMap.size(); i++) {
            holdingStringMap[i] = tolower(holdingStringMap[i]); //iterate through that storage variable to lowercase it while preserving the map keys
        }
        tempInt = localString.compare(holdingStringMap); //assign the string comparison results to an integer
        if (tempInt == 0) { //0 means that the word searched was a valid object in the system and outputs its map value for the matching key
            std::cout << "The item you searched for \"" << unalteredString << "\" appeared " << word.second << " times!\n"; // and returns what user typed 
            std::cout << "Please enter any key to return to the main menu!\n";
            system("pause"); 
            menuSelection();
        }
        else {
            continue; //ensure that for loop continues if no match is found up to this point until all of the elements in wordCounter have been evaluated
        }
        std::cout << "Your item was not found in our system. If your spelling is correct, then your item may not be in our system.\n";
        std::cout << " Please enter any key to return to the main menu and try again!";
        system("pause");
        menuSelection();
    }

  }

```
### Improvements to be Made and Lessons Learned
I believe the way my variables were accessed could have been done better. I started out with pass by references to all my variables which were held in setters and getters. I ultimately
had to ditch this method of variable access since I was struggling with the implmentation of standard library methods in combination with getter/setter methods and 
needed to complete the project, simply throwing the variables into the privated section of the only class I had which would protect access from non-inheriting files.
I loved encapsulation when I learned it for a Java course, and will spend some time figuring out how to neatly add more security more to variable access while preserving
functionality and efficiency. I think the biggest takeaway from this course and project is changing how I think about the execution of a program. Whilst learning software
I have only made lightweight CLI applications, and when needed to parse through large data sets, have had the benefit of Python, SQL, and all of the libraries/tool that
support those languages to make quick work of data. For the first time ever, my beefy computer picked up a challenging CPU load since one of my first methods that was
triple nested did indeed execute but took so much more time than I was used to. Tying my hands, so-to-speak, with C++ made me sit and think not simply about functionality,
but to look for a solution that took up as few computer resources as possible. It is something I am going to consider for everything moving forward, not just if I can build
a solution, but can I build a solution using standard tools to be efficient?
