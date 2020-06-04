
# So Simple Array Class

This array class is written in C++ language and meant to be used in Arduino project.


## Example

```c++
#include "SimpleArray.h"
typedef SimpleArray<uint8_t, int> array_t;

#define HEAP_SIZE  100
#define TEST_SIZE  20
#define TEST_COUNT 1000

void showArray(const char * pre_msg, array_t & array) {
    printf("%s", pre_msg);
    for (int i = 0; i < array.length(); i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main(int argc, char * argv[]) {
    printf("Test SimpleArray\n");
    printf("----------------\n");


    /********************************************
     * Test functions
     */
    int i;

    array_t arr1(HEAP_SIZE);
    array_t arr2(HEAP_SIZE);
    for (i = 0; i < TEST_SIZE; i++) {
        arr1 += i;
    }
    arr2 += arr1;

    // ------------------------------------------
    if (arr1 == arr2)
        printf("Operator == , arr1 equal arr2\n");

    printf("Remove arr2 from 2 to 2+%d = %d units:", TEST_SIZE, arr2.remove(8, TEST_SIZE));
    showArray(" ", arr2);

    if (arr1 != arr2)
        printf("Operator != , arr1 not equal arr2\n");
    printf("\n");

    // ------------------------------------------
    printf("Lvalue accessing of arr2:");
    for (i = 0; i < arr2.length(); i++)
        arr2[i] = i;
    showArray(" ", arr2);
    printf("\n");

    // ------------------------------------------
    char buf[4];
    printf("readToBuffer %d of arr2: ", arr2.getBytes(buf, 4));
    for (i = 0; i < 4; i++)
        printf("%d ", buf[i]);
    showArray(" from arr2, left: ", arr2);
    printf("\n");

    // ------------------------------------------
    uint8_t ibuf[] = { 5, 5, 5, 5 };
    arr2.append(ibuf, sizeof(ibuf));
    showArray("append from buf to arr2, so arr2: ", arr2);
    printf("\n");


    /********************************************
     * Test reliability
     */
    for (int t = 0; t < TEST_COUNT; t++) {
        uint8_t tmp = arr1[1];
        arr1.remove(1, 10);
        for (int j = tmp; j < tmp+10; j++) {
            if (j < TEST_SIZE)
                arr1 += j;
            else
                arr1 += j - TEST_SIZE + 1;
        }

        if (t % 100 == 0) {
            printf("arr1 after %d tests.. ", t);
            for (i = 0; i < TEST_SIZE; i++)
                printf("%d ", arr1[i]);
            printf("\n");
        }
    }

    return 0;
} 
```
