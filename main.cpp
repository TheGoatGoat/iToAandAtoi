/**
 * date modified: 9/29/2018
 *      -implemented printCString function
 *      -removed insertion operators
 *
 * date modified: 9/27/2018
 *      -Finished JSON
 *      -DisplayFunction
 *      -dblToCstr
 *      -bubbleSort
 *
 * date modified: 9/26/2018
 *       =finished algorithm for dynamically resizing item array
 *
 * date modified: 9/24/2018
 *      -finished algorithm to read each character from .csv file
 *
 * date modified: 9/23/2018
 *      -fully implemented cstrToDbl, cstrCpy, cstrLen
 *
 * date modified:  9/17/2018
 *      - file created
 *
 * This is the main.cpp for the project 2
 */


#include <iostream>
#include "proj2-ItemInfo.hpp"
#include <fstream>
#include <cstdlib>

using namespace std;

void bubblesort(ItemInfo arr[], int SIZE);

int main() {
    const int BigBuffer = 500;
    const int SmallBuffer = 50;
    ifstream inFile;

    //Iteminfo Array
    int SIZE = 2;
    ItemInfo *items;
    items = new ItemInfo[SIZE];
    int itemsIndex = 0;

    //Buffers
    char buffer[BigBuffer];
    char descriptionBuffer[BigBuffer];
    char manBuffer[SmallBuffer];
    char sellBuffer[SmallBuffer];
    char itemIDbuffer[SmallBuffer];

    //Counters
    int i = 0;
    int commaCounter = 0;
    int j = 0;                          //running total

    char delimit = ',';

    int bufferCounter = 0;
    char fName[BigBuffer] = "proj2TestFile.csv";
    inFile.open(fName);

    //Checks if file opens
    if(!inFile)
    {
        char error1[] = "ERROR-- FILE DID NOT OPEN";
        printCString(cerr,error1);
    } else {
        //Reads character by character
        while (inFile.get(buffer[i])) {
            //Activates whenever comma or new line is read
            if (buffer[i] == delimit || buffer[i] == '\r' ||
                buffer[i] == '\0') {
                commaCounter++;
                //Assumes the format(idnumber, description, mancost, sellprice)
                switch (commaCounter) {
                    case 1:
                        //Sets itemID
                        while (buffer[j] != delimit) {
                            itemIDbuffer[bufferCounter] = buffer[j];
                            bufferCounter++;
                            j++;
                        }
                        itemIDbuffer[bufferCounter] = '\0';
                        items[itemsIndex].setItemId(itemIDbuffer);
                        bufferCounter = 0;
                        break;

                    case 2:
                        j++;
                        //sets item description
                        while (buffer[j] != delimit) {
                            descriptionBuffer[bufferCounter] = buffer[j];
                            bufferCounter++;
                            j++;
                        }
                        descriptionBuffer[bufferCounter] = '\0';
                        items[itemsIndex].setDescription(descriptionBuffer);
                        bufferCounter = 0;
                        break;

                    case 3:
                        j++;
                        //sets item man cost
                        while (buffer[j] != delimit) {
                            manBuffer[bufferCounter] = buffer[j];
                            bufferCounter++;
                            j++;
                        }
                        manBuffer[bufferCounter] = '\0';
                        items[itemsIndex].setManCost(manBuffer);
                        bufferCounter = 0;
                        break;

                    default:
                        j++;
                        //sets items sell price
                        while (buffer[j] != '\r' && buffer[j] != '\0') {
                            sellBuffer[bufferCounter] = buffer[j];
                            bufferCounter++;
                            j++;
                        }
                        j++;
                        sellBuffer[bufferCounter] = '\0';
                        items[itemsIndex].setSellPrice(sellBuffer);
                        bufferCounter = 0;
                        itemsIndex++;
                }

                //Resets comma counter because buffer reached new line
                if (commaCounter > 3) {
                    commaCounter = 0;
                }

                //Dynamically resizes item array
                if (itemsIndex >= SIZE) {
                    ItemInfo *temp = items;
                    SIZE += 2;
                    items = new ItemInfo[SIZE];
                    for (int k = 0; k < itemsIndex; k++) {
                        items[k] = temp[k];
                    }
                    delete[] temp;
                }
            }
            i++;
        }
        //Accounts for empty file
        if(i > 0) {
            j++;
            //Reads the last sell price in the buffer
            while (buffer[j] != '\r' && buffer[j] != '\0') {
                sellBuffer[bufferCounter] = buffer[j];
                bufferCounter++;
                j++;
            }
            sellBuffer[bufferCounter] = '\0';
            items[itemsIndex].setSellPrice(sellBuffer);
            itemsIndex++;

            //Sorts array in terms of highest profit -> lowest profit
            bubblesort(items, itemsIndex);

            //Displays all items in array
            for(int k = 0; k < itemsIndex; k++){
                items[k].displayItemInfo(cout);

            }

            //Displays only the top 5 most profitable items in JSON format
            for(int k = 0; k < itemsIndex; k++) {
                items[k].toAmazonJSON(cout);
            }


        }else{
            char error2[] = "ERROR-- FILE IS EMPTY";
            cerr.write(error2, stuCstrLen(error2));
        }
    }

    delete [] items;
    inFile.close();
    return 0;
}

//Sorts array by most profitable -> least profitable
void bubblesort(ItemInfo arr[], int SIZE){
    for(int pass = 0; pass < SIZE; pass++){
        for(int k = 0; k < SIZE - pass - 1; k++){
            if(arr[k].calcProfit() < arr[k+1].calcProfit()){
                swap(arr[k] , arr[k+1]);
            }
        }
    }
}