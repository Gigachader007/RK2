#include <fstream>
#include <iostream>
#include <tuple>

std::pair<std::string,std::size_t> replace(const std::string& str, const std::string& old, const std::string& new_string){
    std::string res = "";
    std::size_t word_count = 0;
    for(auto i = 0; i < str.size(); ++i){
        bool found = true;
        for(auto j = 0; j < old.size(); ++j){
            if(i + j >= str.size()){
                found = false;
                break;
            }
            if(str[i + j] != old[j]){
                found = false;
                break;
            }
        }
        if(i == 0 && str[old.size()] != ' '){
            found = false;
        }
        else if(str[i-1] != ' ' || (i+old.size() < str.size() && str[i+old.size()] != ' ')){
            found = false;
        }

        if(found){
            i += old.size() - 1;
            res += new_string;
            word_count++;
        }
        else{
            res += str[i];
        }
    }
    return {res,word_count};
}

std::size_t remove_words(std::ifstream& file, std::ofstream& o_file, const std::string& word) {
    std::size_t word_count = 0;
    for(std::string line = ""; std::getline(file,line,'\n'); )
    {
        auto [str, count] = replace(line,word,"");
        word_count += count;
        o_file << str << "\n";
    }
    return word_count;
}

int main(){
    std::ifstream file{"text.txt"};
    std::ofstream ofile{"text2.txt"};
    remove_words(file,ofile,"test");
}