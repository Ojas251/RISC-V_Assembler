#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <bitset>
#include <sstream>
using namespace std;

int main(){
    string line;
    char format;
    smatch match;
    string matchs;
    bitset <32> mc;
    long int text=0x0; 
    long long int data=0x10000000;
    long long int datav;
    long  int lowlimit=0xffffffff;
    long  int uplimit=0x7fffffff;
    long long int lowlimitd=0xffffffffffffffff;
    long long int uplimitd=0x7fffffffffffffff;
    int lowlimith=0xffff;
    int uplimith=0x7fff;
    int lowlimitb=0xff;
    int uplimitb=0x7f;

    string hexdata,hexdatav;
    vector<pair<string,long int>> labels;

    ifstream file("help.s");     // file with the instructions
    
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }
   
    regex patt_all(R"(^\s*(\.text\s*([:]|$)|\.data\s*([:]|$)|[_a-zA-Z]\w*:|([_a-zA-Z]\w*:)?\.word|([_a-zA-Z]\w*:)?\.dword|([_a-zA-Z]\w*:)?\.byte|([_a-zA-Z]\w*:)?\.half|([_a-zA-Z]\w*:)?\.asciz))");
    
    regex patt_text(R"(^\s*\.text([:]|$))"); 
   
    regex patt_data(R"(^\s*\.data([:]|$))");
    
    regex patt_label(R"(^\s*[_a-zA-Z]\w*:\s*$)");
   
    regex patt_word(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,1}\s*\.word)");
    
    regex patt_dword(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,1}\s*\.dword)");
    
    regex patt_byte(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,1}\s*\.byte)");
   
    regex patt_half(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,1}\s*\.half)");
    
    regex patt_asciz(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,1}\s*\.asciz)");
    
    regex patt_int(R"((0x(\d|[a-f]|[A-F])+|\d+)( |$))");
    
    regex patt_str(R"("\w*")");
   
    regex pattern("^[a-z]{2,5}\\b");
   
    ofstream tempFile("temp.s");
    ofstream mcFile("mc.txt");

    while(getline(file,line)){
        
        regex_search(line,match,patt_all);
        
        if(match.size()!=0){
            
            regex_search(line,match,patt_text);
            if(match.size()!=0){
                
               continue;
            }
            regex_search(line,match,patt_data);
            if (match.size()!=0){
                
                continue;
            }
            regex_search(line,match,patt_label);
            if(match.size()!=0){
                
               matchs=match.str();
               size_t found = matchs.find(":");
                if (found != std::string::npos) {
                matchs.erase(found);
               }
               labels.push_back(make_pair(matchs,text));
               continue;
            }
            
            regex_search(line,match,patt_word);
            if(match.size()!=0){
                
                
                regex_search(line,match,patt_int);
                matchs=match.str();
                
                datav=stoi(matchs, nullptr, 16);
                if(datav<lowlimit || datav>uplimit){
                    mcFile<<"Error";
                } 
                stringstream ss,ss1;
                ss << hex << data;
                hexdata = ss.str();
 
                ss1 << hex << datav;
                hexdatav = ss1.str();

                
                mcFile<<"0x"<<hexdata<<" "<<"0x"<<hexdatav<<"\n";
                data=data+4;
                continue;
            }
             regex_search(line,match,patt_dword);
            if(match.size()!=0){
                
                regex_search(line,match,patt_int);
                matchs=match.str();
                datav=stoi(matchs, nullptr, 16);
                if(datav<lowlimitd || datav>uplimitd){
                    mcFile<<"Error";
                }
                
                
                   
                
                stringstream ss,ss1;
                ss << hex << data;
                hexdata = ss.str();
 
                ss1 << hex << datav;
                hexdatav = ss1.str();

                
                mcFile<<"0x"<<hexdata<<" "<<"0x"<<hexdatav<<"\n";
                 data=data+8;
                continue;
            }
            regex_search(line,match,patt_half);
            if(match.size()!=0){
                
                regex_search(line,match,patt_int);
                matchs=match.str();
                datav=stoi(matchs, nullptr, 16);
                if(datav<lowlimith || datav>uplimith){
                    mcFile<<"Error";
                }
                
                    
                
                stringstream ss,ss1;
                ss << hex << data;
                hexdata = ss.str();
 
                ss1 << hex << datav;
                hexdatav = ss1.str();

                mcFile<<"0x"<<hexdata<<" "<<"0x"<<hexdatav<<"\n";
                data=data+2;
                continue;
            }
            regex_search(line,match,patt_byte);
            if(match.size()!=0){
                
                regex_search(line,match,patt_int);
                matchs=match.str();
                datav=stoi(matchs, nullptr, 16);
                if(datav<lowlimitb || datav>uplimitb){
                    mcFile<<"Error";
                }
                
                    
                
                stringstream ss,ss1;
                ss << hex << data;
                hexdata = ss.str();
 
                ss1 << hex << datav;
                hexdatav = ss1.str();

                
                mcFile<<"0x"<<hexdata<<" "<<"0x"<<hexdatav<<"\n";
                data=data+1;
                continue;
            }
            regex_search(line,match,patt_asciz);
            
            if(match.size()!=0){
               
                regex_search(line,match,patt_str);
                matchs=match.str();
               matchs.erase(0,1);
                matchs.erase(matchs.size() - 1, 1);
                stringstream ss;
                ss << hex << data;
                hexdata = ss.str();

                mcFile<<"0x"<<hexdata<<" "<<matchs<<"\n";
                data=data+matchs.size();
                continue;
            }
        }
        else{
            
              regex_search(line,match,pattern);
              if(match.size()!=0){
                  tempFile<<line<<"\n";

                  text=text+4;
              }
           }
    }
    cout<<"labels:\n";
    for(int i=0;i<labels.size();i++){
        cout << labels[i].first<<","<<labels[i].second<<"\n";
    }
    file.close();
    return 0;
}
