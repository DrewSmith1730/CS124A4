#include "string"
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

//
// Created by drews on 9/15/2020.
//

#ifndef CS124_TENNISWINNERS_H
#define CS124_TENNISWINNERS_H

class TennisWinners {
private:
    std::string tournoment;
    std::string winner;
    std::string level;
    float age;
    std::string score;
    std::string uniquiIdentifier;


public:
    // default constructor
    TennisWinners(){
        tournoment = "Wimbldon";
        winner = "Drew Smith";
        level = "A";
        age = 18.0000;
        score = "6-0 0-6 6-0";
        uniquiIdentifier = "0000-000-0";
    }

    // constructor with all the info required
    TennisWinners(std::string tour, std::string level, std::string win, float age, std::string score, std::string uniqui){
        tournoment = tour;
        this->level = level;
        winner = win;
        this->age = age;
        this->score = score;
        uniquiIdentifier = uniqui;
    }

    /**
     * getTour()
     * @return the string saved in tournoment
     */
    std::string getTour(){
        return tournoment;
    }

    /**
     * getLevel()
     * @return the strin saved in level
     */
    std::string getLevel(){
        return level;
    }

    /**
     * getWinner()
     * @return the string in winner
     */
    std::string getWinner(){
        return winner;
    }

    /**
    * getAge()
    * @return the float in age
    */
    float getAge(){
        return age;
    }

    /**
    * getScore()
    * @return the string in score
    */
    std::string getScore(){
        return score;
    }

    /**
     * getUnique()
     * @return the string saved in uniquiidentifier
     */
    std::string getUnique(){
        return uniquiIdentifier;
    }

    // setters
    /**
    * sets tournoment as what you want
    */
    void setTournoment(std::string tour){
        tournoment = tour;
    }

    /**
    * sets the tournoment level what you want it to be
    */
    void setLevel(std::string level){
        this->level = level;
    }

    /**
    * sets the winner to what ever you enter
    */
    void setWinner(std::string win){
        winner = win;
    }

    /**
    * sets the age of the winner to what ever you set it to
    */
    void setAge(float age){
        this->age = age;
    }

    /**
    * sets the score of the matches to what you enter
    */
    void setScore(std::string score){
        this->score = score;
    }

    /**
     * sets the uniquiidentifier value
     * @param unique
     */
    void setUnique(std::string unique){
        uniquiIdentifier = unique;
    }

    friend std::ostream& operator << (std::ostream &outs, const TennisWinners &tWin){
        outs << std::setw(21) << std::left << tWin.tournoment;
        outs << std::setw(3) << std::left << tWin.level;
        outs << std::setw(24) << std::left << tWin.winner;
        outs << std::setw(6) << std::right << tWin.age;
        outs << std::setw(30) << std::right << tWin.score;
        outs << std::setw(14) << std::right << tWin.uniquiIdentifier;
        return outs;
    }

    // overload the == operator
    friend bool operator == (const TennisWinners &lhs, const TennisWinners &rhs){
        return lhs.uniquiIdentifier == rhs.uniquiIdentifier;
    }

    // overload the < operator
    friend bool operator < (const TennisWinners &lhs, const TennisWinners &rhs){
        // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
        // the spliting of the variables was from here
        // assignment statements
        std::string mainstring1 = lhs.uniquiIdentifier;
        std::string mainstring2 = rhs.uniquiIdentifier;
        std::string dl = "-";

        // getting the important data out of the unique identifer
        std::string date1 = mainstring1.substr(5, mainstring1.find(dl));
        date1.erase(3, mainstring1.find(dl) + dl.length());
        std::string match1 = mainstring1.substr(9, mainstring1.size());

        // getting the important data out of the unique identifer pt2
        std::string date2 = mainstring2.substr(5, mainstring2.find(dl));
        date2.erase(3, mainstring2.find(dl) + dl.length());
        std::string match2 = mainstring2.substr(9, mainstring2.size());

        // checking the individual parts for the answer
        if(date1 == date2){
            return match1 < match2;
        } else {
            return date1 < date2;
        }
    }

    // overload the > operator
    friend bool operator > (const TennisWinners &lhs, const TennisWinners &rhs){
        // assignment statements
        std::string mainstring1 = lhs.uniquiIdentifier;
        std::string mainstring2 = rhs.uniquiIdentifier;
        std::string dl = "-";

        // getting the important data out of the unique identifer
        std::string date1 = mainstring1.substr(5, mainstring1.find(dl));
        date1.erase(3, mainstring1.find(dl) + dl.length());
        std::string match1 = mainstring1.substr(9, mainstring1.size());

        // getting the important data out of the unique identifer pt2
        std::string date2 = mainstring2.substr(5, mainstring2.find(dl));
        date2.erase(3, mainstring2.find(dl) + dl.length());
        std::string match2 = mainstring2.substr(9, mainstring2.size());


        // checking the individual parts for the answer
        if(date1 == date2){
            return match1 > match2;
        } else {
            return date1 > date2;
        }
    }

    // overload the <= operator
    friend bool operator <= (const TennisWinners &lhs, const TennisWinners &rhs){
        // assignment statements
        std::string mainstring1 = lhs.uniquiIdentifier;
        std::string mainstring2 = rhs.uniquiIdentifier;
        std::string dl = "-";

        // getting the important data out of the unique identifer
        std::string date1 = mainstring1.substr(5, mainstring1.find(dl));
        date1.erase(3, mainstring1.find(dl) + dl.length());
        std::string match1 = mainstring1.substr(9, mainstring1.size());

        // getting the important data out of the unique identifer pt2
        std::string date2 = mainstring2.substr(5, mainstring2.find(dl));
        date2.erase(3, mainstring2.find(dl) + dl.length());
        std::string match2 = mainstring2.substr(9, mainstring2.size());


        // checking the individual parts for the answer
        if(date1 == date2){
            return match1 <= match2;
        } else {
            return date1 <= date2;
        }
    }

    // overload the >= operator
    friend bool operator >= (const TennisWinners &lhs, const TennisWinners &rhs){
        // assignment statements
        std::string mainstring1 = lhs.uniquiIdentifier;
        std::string mainstring2 = rhs.uniquiIdentifier;
        std::string dl = "-";

        // getting the important data out of the unique identifer
        std::string date1 = mainstring1.substr(5, mainstring1.find(dl));
        date1.erase(3, mainstring1.find(dl) + dl.length());
        std::string match1 = mainstring1.substr(9, mainstring1.size());

        // getting the important data out of the unique identifer pt2
        std::string date2 = mainstring2.substr(5, mainstring2.find(dl));
        date2.erase(3, mainstring2.find(dl) + dl.length());
        std::string match2 = mainstring2.substr(9, mainstring2.size());


        // checking the individual parts for the answer
        if(date1 == date2){
            return match1 >= match2;
        } else {
            return date1 >= date2;
        }
    }
};

void getTennisWinnersFromFile(std::string filename, std::vector<TennisWinners> &tWinners){
    // read in from file
    std::ifstream fin;
    fin.open("../" + filename);

    std::string header = "";
    if(fin){
        // uses getline with 2 arguments to read the first line from the file
        getline(fin, header);
    }

    std::string tournoment = "", level = "", winner = "", score = "", notUsed = "", uniqu = "";
    float age = 0.0;
    char comma = ',';

    // while loop to read to the end of the file
    while(fin && fin.peek() != EOF){
        // read in the name of the tournoment
        // get line with 3 arguments to spec character to stop on
        // skip 1 section here
        getline(fin, notUsed, ',');
        getline(fin, tournoment, ',');
        // skip 2 sections here
        for(int i = 0; i < 2; i++){
            getline(fin, notUsed, ',');
        }
        getline(fin, level, ',');
        // skip 5 sections here
        for(int i = 0; i < 5; i++){
            getline(fin, notUsed, ',');
        }
        getline(fin, winner, ',');
        // skip 3 sections here
        for(int i = 0; i < 3; i++){
            getline(fin, notUsed, ',');
        }
        fin >> age >> comma;
        // skip 8 sections here
        for(int i = 0; i < 8; i++){
            getline(fin, notUsed, ',');
        }
        getline(fin, score, ',');
        // skip 25 sections to end of each line here
        for(int i = 0; i < 25; i++){
            getline(fin, notUsed, ',');
        }
        getline(fin, uniqu);
        // creates the tenniswinners object and puts it in the vector
        tWinners.push_back(TennisWinners(tournoment, level, winner, age, score, uniqu));
    }
    fin.close();
}

int averageAge(std::vector<TennisWinners> &tWinners){
    float total = 0.0;
    int average = 0;
    int size = tWinners.size();
    for(int i = 0; i < tWinners.size(); i++){
        total += tWinners[i].getAge();
    }
    average = total / size;
    return average;
}



#endif //CS124_TENNISWINNERS_H
