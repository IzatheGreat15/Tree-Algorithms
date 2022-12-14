#include <stdio.h>
#include <stdlib.h>

typedef int *Array;

typedef struct{
    int optimal_price;
    Array optimal_cuts;
}*RodCutting, RodCutNode;

RodCutNode getMax(RodCutNode a, RodCutNode b){
    return (a.optimal_price > b.optimal_price) ? a : b;
}

RodCutNode rodCut(RodCutting optimal, int *price, int length, int i){
    RodCutNode max;
    max.optimal_price = 0;
    max.optimal_cuts = (Array)calloc(length, sizeof(int));
    
    if(length == i){
        max.optimal_price = price[length - 1];
        max.optimal_cuts[length - 1] = 1;
        return max;
    }

    max.optimal_price = optimal[i - 1].optimal_price + price[length - i - 1];
    max.optimal_cuts[i - 1]++;
    max.optimal_cuts[length - i - 1]++;

    max = getMax(max, rodCut(optimal, price, length, i + 1));

    return max;
}

void main(){
    int price[] = {1, 5, 8, 9, 10, 17, 17, 20};
    int length = sizeof(price) / sizeof(price[0]);
    
    // ARRAY CONTAINING ALL THE OPTIMAL PROFIT FOR EACH LENGTH
    RodCutting optimal = (RodCutting)calloc(length, sizeof(RodCutNode));

    // iterate for each length
    for(int x = 0; x < length; x++){
        optimal[x] = rodCut(optimal, price, x + 1, 1);

        // display output
        printf("Length: %d\n", x + 1);
        for(int y = 0; y <= x; y++){
            if(optimal[x].optimal_cuts[y] > 0)
                printf("Cut %d: %d\n", y + 1, optimal[x].optimal_cuts[y]);
        }
        printf("Optimal Price: %d\n\n", optimal[x].optimal_price);
    }
}