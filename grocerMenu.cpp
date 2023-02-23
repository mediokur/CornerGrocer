#include <iostream>
#include <fstream> 
#include <map>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <cstring>
#include "grocerMenu.h"

using namespace std;

//core methods below

void grocerMenu::populateVec() {
    inPutFile.open("groceryItems.txt", ios::in); //opening text file
    if (inPutFile.is_open()) { //conditional to ensure that program doesn't continue if file can't open
        string line; 
        while (getline(inPutFile, line)) {
            stringstream streamer;
            string temp;
            streamer << line; //store my string object into a stream object so I can have it loop through sub strings
            while (!streamer.eof()) {
                streamer >> temp;
                wordList.push_back(temp); //pushes all stream objects(strings) into a vector for later use
            }
        }
        inPutFile.close(); //closes file when done
    }
    else {
        std::cout << "File didn't open\n"; //error "handling" for file opening issues
        system("pause");
        exit(0);
    }
}

void grocerMenu::populateMap() {
    for (int i = 0; i < wordList.size(); i++) { //iterates through my word only populated vector
        if (wordCounter.find(wordList[i]) == wordCounter.end()) {
            wordCounter[wordList[i]] = 1; //catches the condition in which a word only occurs once and assings it a frequency value
        }
        else {
            wordCounter[wordList[i]]++;//anyother time the element from the map sees another of the same value in 
                                       //the vector, it simply increments my frequency counter value
        }
    }
}

void grocerMenu::printQuants() {
    outPutFile.open("GroceryItemQuantities.txt", ios::out);//write mode
    if (outPutFile.is_open()) {
        outPutFile << "Grocery Items& Their Quantities " << endl;
        std::cout << "Check project directory for a text file with all grocery items and their quantities."<< endl;
        std::cout << "A copy of that data is now being shown below!" << endl;
        for (auto& word : wordCounter) { //inline iterator to add in each key value pair (item, frequency) to a line in the txt file output
            outPutFile<< word.first << " " << word.second << endl;
            std::cout << word.first << " " << word.second << endl; //good for user and test validation to output data that was also going to the text file
        }
        outPutFile.close();
        std::cout << "Please enter any key to return to the main menu!\n";
        system("pause");
        menuSelection();
    }
    else {
        std::cout << "Could not properly open a file to write into!";
        std::cout << "Please enter any key to return to the main menu!\n";
        system("pause");
        menuSelection();
    }
}

void grocerMenu::printHistogram() {
    outPutFile.open("GroceryItemHistogram.txt", ios::out);//write mode
    if (outPutFile.is_open()) {
        outPutFile << "Grocery Items & Their Quantities Visually Represented " << '\n';
        std::cout << "Check project directory for a text file with all grocery items and their quantity represented visually" << '\n';
        std::cout << "A copy of that data is now being shown below!" << '\n';
        for (auto& word : wordCounter) { //inline iterator to add in each key value pair (item, frequency) to a line in the txt file output
            outPutFile << word.first << " " << setfill('*') << setw(word.second + 1) << '\n'; //set fill for the frequency value+1 (width starts at 0) 
            std::cout << word.first << " " << setfill('*') << setw(word.second+1) << '\n'; //for the key it is associated with
        }
        outPutFile.close();
        std::cout << "Please enter any key to return to the main menu!\n";
        system("pause");
        menuSelection();
    }
    else {
        std::cout << "Could not properly open a file to write into!";
        std::cout << "Please enter any key to return to the main menu!\n";
        system("pause");
        menuSelection();
    }
}

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

void grocerMenu::screenDecorator() {
    //easy way to spruce up the cli interface without using curses and easily make changes to just this method instead of anytime i need to change a format
    std::cout << "------------------------------------------\n";
    std::cout << "------------------------------------------\n";
    std::cout << "||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||\n";
    std::cout << "------------------------------------------\n";
    std::cout << "------------------------------------------\n";
}

void grocerMenu::menuSelection() {
   
    std::cout << "Please make a selection from the menu below by entering the number of the menu item you wish to execute!\n";
    std::cout << "Number 1: Type in the name of an item whose quantity you want to look up!\n";
    std::cout << "Number 2: Print the list of all items in the system with their numeric quantity attached to the item!\n";
    std::cout << "Number 3: Print the list of all the items in the system with their quantities visually represented!\n";
    std::cout << "Number 4: Quit the application!\n";
    screenDecorator();
    cin >> temp; //storage variable used for switch evaluation below
    switch (temp) {
    case 1:
        itemLookUp();
        break;
    case 2:
        printQuants();
        break;
    case 3:
        printHistogram();
        break;
    case 4:
        exit(0);
    default:
        std::cout << "You have an incorrect input, please only enter the number of the option you wish to execute, please try again!\n";
        cin.clear();
        cin.ignore(1000, '\n'); //if we don't clean the cin buffer stream and ignore all inputs up to and including the last 
        menuSelection();        //newline, this loops forever since it holds the last cin value and reuses it erroniously forever
    }
}

void grocerMenu::initialMenu() { //initialize the menu and store all the text items into a vec
    std::cout << "Welcome To The Corner Grocer Application!\n";
    screenDecorator();
    //it is vital that the vector is populated before the map, and the map before the other menu options are available
    populateVec();
    populateMap();
    menuSelection();
}