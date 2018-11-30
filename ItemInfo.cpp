
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
