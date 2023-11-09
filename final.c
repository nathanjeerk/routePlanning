#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//-----------------------------------------------------------------------------------------------------------
//Copyright By Shinnachot Jeerakan
//-----------------------------------------------------------------------------------------------------------
//This program allow user to select up to 5 destination, and make the total distance travelled is minimised
//This program involes in using permutation and 2D distance calculations
//-----------------------------------------------------------------------------------------------------------
//Input arguments:  The argument requires user to send input how many destinations they want and calculate
//the shortest distance for a parcel delivery company
//Return value: shortest distance and re ordered locations by using permutation method

//-----------------------------------------------------------------------------------------------------------
//Declare the function to the program
//-----------------------------------------------------------------------------------------------------------
float totalDistanceOfRoute(float* xCoord, float* yCoord, int* orderLocationVisited, int numberOfLocations);
float distanceBetweenLocations(float x1, float y1, float x2, float y2);
void swap(int* a, int* b);
void permutation(float* xCoord, float* yCoord, int* route, int l, int r, int* minRoute, float* minDistance);

//---------------------------------------------TEST DATA-----------------------------------------------------
//float xCoord[11] = {0,9,6,7,1,21,7,11,5,9,8};
//float yCoord[11] = {0,8,8,8,1,11,11,11,5,9,1};

// 1 2 3 -> The shortest possible distance to travel is 25.041595 which requires visiting in the order 1 3 2
// 3 2 1 -> The shortest possible distance to travel is 25.041595 which requires visiting in the order 2 3 1

// Note route "reversal" doesn't affect distance

// 1 2 3 4 -> The shortest possible distance to travel is 25.044359 which requires visiting in the order 2 3 1 4
// 9 1 7 4 -> The shortest possible distance to travel is 31.203493 which requires visiting in the order 1 7 9 4
//-----------------------------------------------------------------------------------------------------------

//This is the pre-programmed destination and will be displayed on the screen
float xCoord[11] = {0,9,6,7,1,21,7,11,5,9,8};
float yCoord[11] = {0,8,8,8,1,11,11,11,5,9,1};

//The function to calculate the distance between TWO points
float distanceBetweenLocations(float x1, float y1, float x2, float y2) {
    //using the method to find the distance of 2D planes
    float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return distance;
}

//The function to calculate the total distance of all the route
float totalDistanceOfRoute(float* xCoord, float* yCoord, int* orderLocationVisited, int numberOfLocations) {
    float totalDistance = 0;
    int i = 0; //i is for the location, while set to 0 is mean location is at depot
    //Looping while the i is in range
    while((i < numberOfLocations - 1) || numberOfLocations == 0) {
        int j = orderLocationVisited[i];
        //let int K be the i + 1th location visited
        int k = orderLocationVisited[i + 1];
        //add the distance in to the total distance that we initially with 0
        totalDistance += distanceBetweenLocations(xCoord[j], yCoord[j], xCoord[k], yCoord[k]);
        //i++ is to indicates that we are moving into another locations
        i++;
    }
    //Loop is ended since we returned to depot or (0, 0)
    totalDistance += distanceBetweenLocations(xCoord[0], yCoord[0], xCoord[orderLocationVisited[0]], yCoord[orderLocationVisited[0]]);
    totalDistance += distanceBetweenLocations(xCoord[orderLocationVisited[numberOfLocations - 1]], yCoord[orderLocationVisited[numberOfLocations - 1]], xCoord[0],yCoord[0]);
    return totalDistance;
}

//The function is to swap two integers which will be use later in permutation
void swap(int* a, int* b) {
    int sub = *a;
    *a = *b;
    *b = sub;
}

//This permute function actions in the way to re ordered the locations for the shortest routes
void permutation(float* xCoord, float* yCoord, int* route, int l, int r, int* minRoute, float* minDistance) {
    if (l == r) {
        float totalDistance = totalDistanceOfRoute(xCoord, yCoord, route, r+1);
        if (totalDistance < *minDistance) {
            *minDistance = totalDistance;
            for (int i = 0; i < r+1; i++) {
                minRoute[i] = route[i];
            }
        }
    } else {
        for (int i = l; i <= r; i++) {
            swap(&route[l], &route[i]);
            permutation(xCoord, yCoord, route, l+1, r, minRoute, minDistance);
            swap(&route[l], &route[i]); 
        }
    }
}

//Required header files: stdio.h, time.h, stdlib.h

int main() {
    int destination[5]; //store the input of the user
    int minRoute[5]; //store the shortest route 
    float minDistance; //minDistance is not set but declared
    int n; //to store the number of destination that user input

    //this printf and loop just show the user pre-programmed destination in the terminal
    printf("Pre-programmed Destination\n");
    for (int i = 0; i < 11; i++) {
        printf("(%.1f, %.1f)\n", xCoord[i], yCoord[i]);
    }

    printf("Enter number of destination (5 maximum): ");
    scanf("%d", &n); //ask for user input and store in integer n
    //set the condition if user put more than 5 destination, the error comes up
    if((n > 5) || (n == 0)) {
        printf("Number of destinations is invailid\n");
        return 0;
    }

    printf("Examples: put in this format (1 2 3 4)\n");
    printf("Enter your destination in order (1 to 10): ");
    for (int i = 0; i < n ; i++) {
        scanf("%d", &destination[i]);
    }

    minDistance = totalDistanceOfRoute(xCoord, yCoord, destination, n);
    //call the permutation to re order the destination for the shortest route
    permutation(xCoord, yCoord, destination, 0, n - 1, minRoute, &minDistance);
    
    printf("The total distance of the shortest route is: %.6f ", minDistance);
    printf("which require visiting in order ");
    for (int i = 0; i < n; i++) {
        printf("%d ", minRoute[i]);
    }
    return 0;
}
//-----------------------------------------------------------------------------------------------------------