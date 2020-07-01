/********** 
Problem Statement:  https://www.hackerrank.com/challenges/attribute-parser/problem
Difficulty:         Medium
Problem Author:     vatsalchanana (https://www.hackerrank.com/profile/vatsalchanana)
Solution Author:    menisorfeas   (https://www.hackerrank.com/profile/menisorfeas)
**********/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>

using namespace std;


int main() {
    int N,Q;
    cin >> N >> Q;

    /* "m" maps a tag to its pairs of attribute names and values*/
    map<string, map<string, string>> m;

    /* "tags" maps a tag to its tag path according to the ierarchy given in input */
    /* e.g. for the example given in the problem definition: tags["tag2"] = "tag1.tag2" */
    map<string,string> tags;

    string input;
    string path = "";
    getline(cin, input);

    /* Parse N inputs */
    for (int i=0; i<N; i++){
        getline(cin, input);
        std::smatch match;
        regex rgx("^</.*"); //match closing tags
        if (!regex_match(input, rgx)){
            regex rgx2("^<(\\w*)(.*)>");
            if (std::regex_search(input, match, rgx2)){
                string tag = match[1];
                if (path!=""){
                    path += ".";
                }
                path += tag;
                tags[tag] = path;
                input = match[2];
                regex rgx2(" (\\w*) = \"([^\"]*)\"(.*)");
                while (input.size() > 1){   //recursively match attribute pairs 
                    if (std::regex_search(input, match, rgx2)){
                        m[tag][match[1]] = match[2];
                        input = match[3];
                    }
                }
            }
        }
        else{   //delete last tag from path if closing tag is found
            int index = path.find_last_of(".");
            if (index == string::npos){
                path = "";
            }
            else{
                path = path.substr(0,index);
            }
        }
    }

    /* Parse Q queries */
    for (int i; i<Q; i++){
        getline(cin, input);
        bool flag = true;  
        std::smatch match;
        regex rgx3("^(.*)~(.*)");   //match[1] = tags path , match[2] = attribute
        if (input.find(".") == string::npos && std::regex_search(input, match, rgx3)){
            if (tags[match[1]] == match[1] && m[match[1]].find(match[2]) != m[match[1]].end()){
                cout << m[match[1]][match[2]] << "\n";
                flag = false;
            }
        }
        else if (std::regex_search(input, match, rgx3)){
            string attribute = match[2];
            string my_path = match[1];
            int index = my_path.find_last_of(".");
            string my_tag = my_path.substr(index+1, my_path.length());
            
            
            if (m.find(my_tag) != m.end() && tags[my_tag] == my_path){
                if((m[my_tag]).find(attribute) != m[my_tag].end()){
                    cout << m[my_tag][attribute] << "\n";
                    flag = false;
                }
            } 
            
        }
        if (flag){  //if there is no such attribute in the source program
            cout << "Not Found!\n";
        }
    }
    return 0;
}
