//uniqname: cjkautz; Lab Section: 040
//uniqname: jiawenz; Lab Section: 011
//Finished date: April 1, 2022

// Add any #includes for C++ libraries here.
// We have already included iostream as an example.
#include <iostream>
#include <fstream>
#include <string>

// The #include adds all the function declarations (a.k.a. prototypes) from the
// reviews.h file, which means the compiler knows about them when it is compiling
// the main function below (e.g. it can verify the parameter types and return types
// of the function declarations match the way those functions are used in main() ).
// However, the #include does not add the actual code for the functions, which is
// in reviews.cpp. This means you need to compile with a g++ command including both
// .cpp source files. For this project, we will being using some features from C++11,
// which requires an additional flag. Compile with this command:
//     g++ --std=c++11 evaluateReviews.cpp reviews.cpp -o evaluateReviews
#include "reviews.h"

using namespace std;

const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;


int main() {
    //loading the keywords and corresponding weights from the target file
    ifstream fin("keywordWeights.txt");
    if (!fin.is_open()) {
        cout << "Error: keywordWeights.txt could not be opened." << endl;
        return 1;
    }

    //initializing vectors for keywords, weights, and assign index-related values insides
    vector <string> keyWordsVector;
    vector<double> weightsVector;
    readKeywordWeights(fin, keyWordsVector, weightsVector);
    fin.close();

    //initializing a vector for NLP scores
    vector<double> scoreVector;//this vector stores each index corresponding score


    //loading all the review text files, and assign their NLP scores to the score vector
    int reviewIdx = 0;
    while (true) {
        string currentFile = makeReviewFilename(reviewIdx);
        ifstream fin1(currentFile);
        if (!fin1.is_open()) {
            break;
        }

        vector <string> reviewVector;
        readReview(fin1, reviewVector);
        double singleScore = reviewScore(reviewVector, keyWordsVector, weightsVector);
        scoreVector.push_back(singleScore);
        fin1.close();

        reviewIdx++;
    }

    //categorize each's type according to the category vector
    vector<string> evaluationVector;
    for (int scoreIdx=0; scoreIdx<int(scoreVector.size()); scoreIdx++) {
        if (scoreVector[scoreIdx] > 3.0) {
            evaluationVector.push_back("truthful");
        } else if (scoreVector[scoreIdx] < -3.0) {
            evaluationVector.push_back("deceptive");
        } else {
            evaluationVector.push_back("uncategorized");
        }
    }

    //output information
    int truthfulNum = 0;
    int deceptiveNum = 0;
    int uncategorizedNum = 0;

    //save each's category into a vector
    ofstream fOutput("report.txt");
    fOutput << "review score category" << endl;
    for (int i=0; i<int(evaluationVector.size()); i++) {
        fOutput << i << " " << scoreVector[i] << " " << evaluationVector[i] << endl;

        if (evaluationVector[i] == "truthful") {
            truthfulNum++;
        } else if (evaluationVector[i] == "deceptive") {
            deceptiveNum++;
        } else {
            uncategorizedNum++;
        }
    }
    fOutput << endl;

    //output total size, and the sizes of each category
    fOutput << "Number of reviews: " << int(evaluationVector.size()) << endl;
    fOutput << "Number of truthful reviews: " << truthfulNum << endl;
    fOutput << "Number of deceptive reviews: " << deceptiveNum << endl;
    fOutput << "Number of uncategorized reviews: " << uncategorizedNum << endl;
    fOutput << endl;

    //output the index number of the highest score and lowest score
    int highestIndex = 0;
    int lowestIndex = 0;
    for (int i=0; i<int(scoreVector.size()); i++) {
        if (scoreVector[i] > scoreVector[highestIndex]) {
            highestIndex = i;
        } else if (scoreVector[i] < scoreVector[lowestIndex]) {
            lowestIndex = i;
        }
    }
    fOutput << "Review with highest score: " << highestIndex << endl;
    fOutput << "Review with lowest score: " << lowestIndex << endl;
    fOutput.close();

    //end of the main() function
    return 0;
}