/*
    Teacher Name : Dr.Dalvand
    Student Name : mAhDi gHaEmI
    Year         : 2023
    ******************************
    This is classroom practice 
    This script will generate datas and test time complexity for 3 search algorithm with unsorted array
        1.Liniear search
        2.Random search
        3.Full random search
    ******************************
    Out put will be like this : 
        Average time complexity for Liniear search     = N
        Average time complexity for Random search      = N 
        Average time complexity for Full random search = N
*/

#include <stdio.h>   // contains header information for 'File related Input/Output' functions,
#include <stdlib.h>  // contains header information for 'Memory Allocation/Freeing' functions.
#include <time.h>    // contains header information for 'time' functions.
#include <math.h>    // contains header information for 'math' functions.

#define TEST_DATAS_SIZE 10000           // how many data generated for searching
#define TEST_DATAS_SHUFFLE_COUNT 10000  // how many time datas will shuffle for search test
#define TEST_DATA_MIN 0                 // minimum of random numbers
#define TEST_DATA_MAX 10000             // maximum of random numbers
#define TEST_REPEATE_COUNT 10000        // how many time will repeat test
#define RANDOM_SEARCH_STEP_COUNT 100    // how many time will repeat test
#define DATA_NOT_FOUND_SYMBOL -1        // a symbol for when a index not found
#define DATA_WAS_READED_SYMBOL -2       // a symbol for when this data readed in array

enum FULL_RANDOM_SEARCH_POSITION{
    START_UP=0,                     // search 0/4 to 1/4 array
    MIDLLE_UP=1,                    // search 1/4 to 2/4 array
    MIDLLE_DOWN=2,                  // search 2/4 to 3/4 array
    END_DOWN=3                      // search 3/4 to 4/4 array
}; // Full random search positions for full random search algorithm

long int testDatas[TEST_DATAS_SIZE];          // our entire datas
long int testAearchDatas[TEST_DATAS_SIZE];   // this numbers will used for searchng

/*
    Function prototypes for app
    Read it top to bottom like a story ;]
*/

int main(int argc, char *argv[]);

void init();
void initLibs();
void seedRadom2Now();

void initVars();
void fillArrayWithOrdinalNumber (long int datas[],long int datasSize,long int minNumber,long int maxNumber);
void shuffleArray (long int datas[],long int maxIndex,long int count);
void copyArray(long int source[],long int distanation[],long int maxIndex);

double getRandomNumber0To1();
long int getRandomNumberMinToMax(long int min,long int max);

void searchAlgorithmAnalyze();
double getAvgFromIntArray(long int intArray[] ,long int arraySize);
double calculateRunCountAvg(long int (*func)(long int[],long int) ,long int datas[],long int testDatas[]);

long int liniearSearchCounter(long int datas[], long int searchData);
long int randomSearchCounter(long int datas[], long int searchData);
long int fullRandomSearchCounter(long int datas[], long int searchData);

void printIntArray(long int intArray[],long int maxIndex);


int main(int argc, char *argv[]) {
    /*
        Our main function will call init and search analyze fnctions
            1.libs
            2.vars
    */

    init();
    searchAlgorithmAnalyze();
    return 0;
}

void init(){
    /*
        this function will call 2 initializer
            1.libs
            2.vars
    */

    initLibs();
    initVars();
}


void initLibs(){
    /*
        this function init libraris
    */
    seedRadom2Now();

}

void seedRadom2Now(){
    /*
        this function seed randoms for prevent repeted data for every run
    */
    srand(time(NULL));
}

void initVars(){
    /*
        this function init variables
    */

    fillArrayWithOrdinalNumber(testDatas,TEST_DATAS_SIZE,TEST_DATA_MIN,TEST_DATA_MAX); 
    copyArray(testDatas,testAearchDatas,TEST_DATAS_SIZE); 
    shuffleArray(testAearchDatas,TEST_DATAS_SIZE,TEST_DATAS_SHUFFLE_COUNT);
}


void fillArrayWithOrdinalNumber (long int datas[],long int datasSize,long int minNumber,long int maxNumber){
    /*
        this function will fill array with minNumber to maxNumber numbers
    */

    long int data = minNumber;
    for(long int i=0;i<datasSize;i++){
        datas[i] = data;

        if(data < maxNumber){
            data++;
        }
    }
}

void copyArray(long int source[],long int distanation[],long int maxIndex){
    /*
        this function will copy source array to distanation array with index 0 to maxIndex
    */

    for(long int i=0;i<maxIndex;i++){
        distanation[i] = source[i];
    }
}


void shuffleArray (long int datas[],long int maxIndex,long int count){
    /*
        this function will fill array by numbers between min and max 
    */

    for(long int i=0;i<count;i++){
        long int firstIndex = getRandomNumberMinToMax(0,maxIndex);
        long int secondIndex = getRandomNumberMinToMax(0,maxIndex);

        long int firstNumber = datas[firstIndex];
        long int secondNumber = datas[secondIndex];

        datas[firstIndex] = secondNumber;
        datas[secondIndex] = firstNumber;
    }
}


double getRandomNumber0To1(){
    /*
        this function will return a number between 0 and 1
    */
    double randomNumber0To1 = (double) rand() / (double) (RAND_MAX - 1);
    return randomNumber0To1;
}

long int getRandomNumberMinToMax(long int min,long int max){
    /*
        this function will return a number between min and max from function parameters
    */

    double randomNumber0To1 = getRandomNumber0To1();
    long int randomNumberMinToMa = min + ((max - min) * randomNumber0To1);
    return randomNumberMinToMa;
}


void searchAlgorithmAnalyze(){
    /*
        this function will call 2 initializer
            1.libs
            2.vars
    */

    double runCountAvgLiniearSearch = calculateRunCountAvg(liniearSearchCounter,testDatas,testAearchDatas);
    printf("Average time complexity for Liniear search     = %lf \n",runCountAvgLiniearSearch);

    double runCountAvgRandomSearch = calculateRunCountAvg(randomSearchCounter,testDatas,testAearchDatas);
    printf("Average time complexity for Random search      = %lf \n",runCountAvgRandomSearch);

    double runCountAvgFullRandomSearch = calculateRunCountAvg(fullRandomSearchCounter,testDatas,testAearchDatas);
    printf("Average time complexity for Full random search = %lf \n",runCountAvgFullRandomSearch);
}



double calculateRunCountAvg(long int (*func)(long int[],long int) ,long int datas[],long int testDatas[]){
    /*
        this function wil run and repeat run count test for search algorithm from function parameter
        and return avrage of how many time liniear search run it loop for finding testDatas 
        from function parameter
    */

    long int runCounts[TEST_REPEATE_COUNT];

    for(long int i=0;i<TEST_REPEATE_COUNT;i++){
        
        long int targetIndex = i % TEST_DATAS_SIZE;
        long int testData = testDatas[targetIndex];
        long int runCount = (*func)(datas,testData);

        runCounts [i] = runCount;
        // if(i % 1000 == 0) printf("RUNNING i = %d from 0,%d \n",i,TEST_REPEATE_COUNT);
    }

    double runCountAvg = getAvgFromIntArray(runCounts,TEST_REPEATE_COUNT);
    return runCountAvg;
}



double getAvgFromIntArray(long int intArray[] ,long int arraySize){
    /*
        this function wil calculate avrage of long int array
    */

    long int sum = 0;
    for (long int i=0;i<arraySize;i++){
        long int intElement = intArray[i];

        sum += intElement;
    }
    double avg = (double) sum / arraySize;
    return avg;
}


long int liniearSearchCounter(long int datas[], long int searchData){
    /*
        this function wil count every time linear search loop run for finding search data 
        from function parameter
    */

    long int loopCounter = 0 ;
    for(long int i=0;i<TEST_DATAS_SIZE;i++){
        loopCounter++;

        long int data = datas[i];
        if(data == searchData){
            break;
        }
    }

    return loopCounter;
}


long int randomSearchCounter(long int datas[], long int searchData){
    /*
        this function wil count every time random search loop run for finding search data 
        from function parameter
    */

    long int loopCounter = 0;
    long int searchedData = 0;
    long int workingDatas[TEST_DATAS_SIZE];

    copyArray(datas,workingDatas,TEST_DATAS_SIZE);

    while(1){
        long int startSearchIndex = getRandomNumberMinToMax(0,TEST_DATAS_SIZE);

        for(long int j=0;j<RANDOM_SEARCH_STEP_COUNT;j++){             
            long int targetIndex = startSearchIndex + j;
            if(targetIndex > TEST_DATAS_SIZE ) break;  

            long int data = workingDatas[targetIndex];            
            loopCounter++;

            if(data == DATA_WAS_READED_SYMBOL) break;

            workingDatas[targetIndex] = DATA_WAS_READED_SYMBOL;
            searchedData++;

            if(data == searchData) return loopCounter;
            if(searchedData == TEST_DATAS_SIZE) return loopCounter;
        }
    }
}


long int fullRandomSearchCounter(long int datas[], long int searchData){
    /*
        this function wil count every time full random search loop run for finding search data 
        from function parameter
    */

    long int loopCounter = 0;
    long int searchedData = 0;
    long int workingDatas[TEST_DATAS_SIZE];

    enum FULL_RANDOM_SEARCH_POSITION status = START_UP;

    copyArray(datas,workingDatas,TEST_DATAS_SIZE);

    while(1){
        long int startSearchIndex;
        long int endSearchIndex;

        if(status == START_UP){
            long int startMin = 0;
            long int startMax = ceil(TEST_DATAS_SIZE / 4.0);
            startSearchIndex = getRandomNumberMinToMax(startMin,startMax);
            endSearchIndex = startSearchIndex + RANDOM_SEARCH_STEP_COUNT;
            status = MIDLLE_DOWN;

         }else if(status == MIDLLE_DOWN){
            long int startMin = floor(TEST_DATAS_SIZE / 4.0);
            long int startMax = ceil(TEST_DATAS_SIZE / 4.0 * 2);

            startSearchIndex = getRandomNumberMinToMax(startMin,startMax);
            endSearchIndex = startSearchIndex + RANDOM_SEARCH_STEP_COUNT;
            status = MIDLLE_UP;

         }else if(status == MIDLLE_UP){
            long int startMin = floor(TEST_DATAS_SIZE / 4.0 * 2);
            long int startMax = ceil(TEST_DATAS_SIZE / 4.0 * 3);

            startSearchIndex = getRandomNumberMinToMax(startMin,startMax);
            endSearchIndex = startSearchIndex + RANDOM_SEARCH_STEP_COUNT;
            status = END_DOWN;

         }else if(status == END_DOWN){
            long int startMin = floor(TEST_DATAS_SIZE / 4.0 * 3);
            long int startMax = TEST_DATAS_SIZE;

            startSearchIndex = getRandomNumberMinToMax(startMin,startMax);
            endSearchIndex = startSearchIndex + RANDOM_SEARCH_STEP_COUNT;
            status = START_UP;
        }  

        for(long int targetIndex=startSearchIndex;targetIndex<=endSearchIndex;targetIndex++){
            long int data = workingDatas[targetIndex];            
            loopCounter++;

            if(data == DATA_WAS_READED_SYMBOL) break;

            workingDatas[targetIndex] = DATA_WAS_READED_SYMBOL;
            searchedData++;

            if(data == searchData) return loopCounter;
            if(searchedData == TEST_DATAS_SIZE) return loopCounter;
        }
    }
}




void printIntArray(long int intArray[],long int maxIndex){
    /*
        this function will prlong int a long int array to terminal
    */

    for(long int i=0;i<maxIndex;i++){
        long int data = intArray[i];
        printf("Index : %d , Data : %d \n",i,data);
    }
}
