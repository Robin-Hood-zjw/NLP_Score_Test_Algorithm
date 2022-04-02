#include <iostream>
#include <fstream>
#include <cassert>

#include "reviews.h"

using namespace std;

int main() {

    // Some made up keywords/weights for testing purposes
    vector<string> keywords = {"snobby", "friendly", "expensive"};
    vector<double> weights = {-1.10, 0.29, -0.21};




    // A sample unit tests for the wordWeight function
    string testWord = "snobby";
    double correctWeight = -1.10;
    double actualWeight = wordWeight(testWord, keywords, weights);

    // An assertion will pass by with no problem if the given expression is true.
    // If the expression is false, however, the assertion reports a test failure!
    assert(actualWeight == correctWeight);




    // Here's a more concise way we could write another test for wordWeight
    assert(wordWeight("expensive", keywords, weights) == -0.21);




    // And here's a test for the reviewScore function.
    // (The review is "They were snobby, yet friendly!" but it's split
    //  into separate words as a vector for the test.)
    vector<string> testReview = {"They", "were", "snobby,", "yet", "friendly!"};
    assert(reviewScore(testReview, keywords, weights) == -0.81);




    // If we get to the bottom of main, that means no assertions failed and
    // that we passed all the tests. Nice!
    cout << "Tests PASS" << endl;
}



