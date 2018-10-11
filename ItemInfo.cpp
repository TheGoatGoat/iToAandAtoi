#include "proj2-ItemInfo.hpp"
#include <iomanip>



//Sets item ID
void ItemInfo::setItemId(const char *num)
{
    int res = 0;
    int isNeg = 1;
    int i = 0;

    // If number is negative, then update sign
    if (num[0] == '-')
    {
        isNeg = -1;
        i++;
    }

    for (; num[i] != '\0'; ++i)
        res = res*10 + (num[i] - '0');

    this->itemId = isNeg * res;

}

//Sets description
void ItemInfo::setDescription(const char *cstr)
{
    int counter = 0;
    while( cstr[counter] != '\0')
    {
        this->description[counter] = cstr[counter];
        counter++;
    }
}

//Sets manufacturing cost
void ItemInfo::setManCost(const char *num)
{
    this->manCost = stuCstrToDbl(num);
};

//Sets sell price

void ItemInfo::setSellPrice(const char *num)
{
    this->sellPrice = stuCstrToDbl(num);
}

//Returns item ID
int ItemInfo::getItemId()
{
    return this->itemId;
}

//Returns item description
const char* ItemInfo::getDescription()
{
    return this->description;
}

//Returns manufacturing cost
double ItemInfo::getManCost()
{
    return this->manCost;
}

//Returns sell price
double ItemInfo::getSellPrice()
{
    return this->sellPrice;
}


//Prints in the format of JSON
void ItemInfo::toAmazonJSON(ostream &out)
{
    static int counter = 0;
    if(counter < 5) {
        const char *store = "\"AarsStore\": [\n";
        const int bufSIZE = 50;
        char *buffer = new char[bufSIZE];

        if (counter == 0) {
            printCString(out, store);
            stuCstrCpy(buffer, "first");
        } else if (counter == 1) {
            stuCstrCpy(buffer, "second");
        } else if (counter == 2) {
            stuCstrCpy(buffer, "third");
        } else if (counter == 3) {
            stuCstrCpy(buffer, "fourth");
        } else {
            stuCstrCpy(buffer, "fifth");
        }

        char numBuffer[bufSIZE];


        printCString(out, "\t \"");
        printCString(out, buffer);

        printCString(out, "Item\":{\n\t\t\"itemId\": ");
        stuDblToCstr(numBuffer, this->getItemId());
        printCString(out, numBuffer);

        printCString(out, "\n\t\t");

        printCString(out, "\"description\": ");
        printCString(out, this->getDescription());

        printCString(out, "\n\t\t");

        printCString(out, "\"manPrice\": ");

        stuDblToCstr(numBuffer, this->getManCost());
        printCString(out, numBuffer);
        printCString(out, "\n\t\t");
        printCString(out, "\"sellPrice\": ");

        stuDblToCstr(numBuffer, this->getSellPrice());
        printCString(out, numBuffer);
        printCString(out, "\n\t},\n");

        if (counter == 5) {
            printCString(out, "]\n");
        }

        delete[] buffer;
        counter++;
    }
}


//Calculates the profit made from each item
double ItemInfo::calcProfit()
{
    return(this->sellPrice - this->manCost);
}


//Prints in the format of the project specification
void ItemInfo::displayItemInfo(ostream &out)
{
    const int buffSize = 500;
    char buffer[buffSize];

    printCString(out, "itemId: ");
    stuDblToCstr(buffer, this->getItemId());
    printCString(out,buffer);
    out.put('\n');

    printCString(out, "description: ");
    printCString(out, this-> getDescription());
    out.put('\n');

    printCString(out, "manCost: ");
    stuDblToCstr(buffer ,this-> getManCost());
    printCString(out,buffer);
    out.put('\n');

    printCString(out, "sellPrice: ");
    stuDblToCstr(buffer,this-> getSellPrice());
    printCString(out,buffer);
    out.put('\n');

    printCString(out,"calculatedProfit: ");
    stuDblToCstr(buffer,this->calcProfit());
    printCString(out,buffer);
    out.put('\n');
    out.put('\n');
    out.put('\n');
}


//AtoI
double stuCstrToDbl(const char *num)
{
    double rez = 0, fact = 1;
    if (*num == '-'){
        num++;
        fact = -1;
    }
    for (int deci = 0; *num; num++){
        if (*num == '.'){
            deci = 1;

        }
        int d = *num - '0';
        if (d >= 0 && d <= 9){
            if (deci) fact /= 10.0;
            rez = rez * 10.0 + (double)d;
        }
    }
    return rez * fact;

}


//iToA
void stuDblToCstr(char *cstr, double num)
{
    int numCount = 0, compare = 0;
    bool decimal = false;
    bool isNeg = false;
    int wholenum = num;
    if(wholenum * 1 < 0){
        isNeg = true;
    }

    if(num - wholenum != 0){
        decimal = true;
    }

    while (compare != (int)num){
        num = num / 10;
        numCount++;
    }

    char buffer[50];
    int counter = 0;

    for(int i =0; i < numCount+2; i ++){
        num *= 10;
    }
    int digit = num;
    int ndx = 0;

    if(isNeg){
        cstr[ndx] = '-';
        ndx++;
        numCount++;
        digit *= -1;
    }
    while(digit > 0){

        buffer[counter] = (digit % 10) + '0';
        digit = digit / 10;
        counter++;
    }

    while(ndx < numCount){
        cstr[ndx] = buffer[--counter];
        ndx++;
    }

    if(decimal){
        cstr[numCount] = '.';
        while( counter > 0) {
            cstr[++numCount] = buffer[--counter];
        }
        cstr[numCount + 1] = '\0';
    }else {
        cstr[numCount] = '\0';
    }
}

//Calculates the length of the cStr
int stuCstrLen(const char *src)
{
    int counter = 0;
    while(src[counter] != '\0')
    {
        counter++;
    }

    return counter;
}

//Makes a copy of the cstring
void stuCstrCpy(char *dest, const char *src){

    int counter = 0;
    while(src[counter] != '\0') {
        dest[counter] = src[counter];
        counter++;
    }
    dest[counter] = '\0';
}

//Prints a cstring
ostream& printCString(ostream &out, const char *src){
    out.write(src , stuCstrLen(src)* sizeof(char));
    return out;
}