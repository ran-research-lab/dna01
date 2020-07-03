#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

std::vector<std::string> split(const string& input, const string& regex) {
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator
        first{input.begin(), input.end(), re, -1},
        last;
    return {first, last};
}

int maxRep(const string &seq, const string &STR) {
    int lastFound = 0;
    int repeat = 0;
    int maxRepeat = 0;
    int pos;
    while  ( (pos = seq.find(STR, lastFound)) != string::npos) {
        // cout << "pos: " << pos << endl;
        if ((pos == lastFound) && lastFound > 0) 
            repeat++;
        else 
            repeat = 1;
        // cout << "repeat: " << repeat << endl;
        if (repeat > maxRepeat)  maxRepeat = repeat;
        lastFound =  STR.length() + pos;
        // cout << "lastFound: " << lastFound << endl;
    }
    return maxRepeat;
}

string matchSignature(const vector< vector <string> > &db, const vector<int> &signature) {
    int STRMaxIdx = db[0].size()-1;
    
    for (int dbIdx = 1; dbIdx < db.size();dbIdx++) {
        bool matches = true;
        int i = 1;
        // cout << "COmparing against: " << db[dbIdx][0] << endl;
        while (matches && (i < STRMaxIdx)) {
            // cout << i << "]  "  << stoi(db[dbIdx][i]) << " vs " << signature[i-1] << endl;
            matches = ( stoi(db[dbIdx][i]) == signature[i-1]); 
            i++;
        }
        if (matches) return db[dbIdx][0]; 
    }
    return "Not found";

}


int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " database sequence" << endl;
        exit(1);
    }
    ifstream dbIF, seqIF;

    dbIF.open(argv[1]);
    if (!dbIF.is_open()) {
        cout << "Could not open " << argv[1] << endl;
        exit(1);
    } 

    seqIF.open(argv[2]);
    if (!seqIF.is_open()) {
        cout << "Could not open " << argv[2] << endl;
        exit(1);
    } 
    
    string seq;
    seqIF >> seq;

    vector< vector <string> > db;

    string tmp;
    
    while( dbIF >> tmp)  {
        db.push_back(split(tmp, ","));
        cout << tmp << endl;
    }

    vector<int> signature;
    for(int i = 1; i < db[0].size(); i++)
        signature.push_back(maxRep(seq,db[0][i]));

    for (auto e: signature) {
        cout << e << endl;
    }

    cout << "Match: " << matchSignature(db, signature);



    return 0;
}
