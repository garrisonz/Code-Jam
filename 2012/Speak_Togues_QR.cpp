//
//  main.cpp
//  code_jame_Cpp
//
//  code jame 练习，问题见链接：
//  https://code.google.com/codejam/contest/1460488/dashboard
//
//  Created by grs on 15/3/18.
//  Copyright (c) 2015年 grs. All rights reserved.
//

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

void analyse_str(){
    
    string str = "ejp mysljylc kd kxveddknmc re jsicpdrysi rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd de kr kd eoya kw aej tysr re ujdr lkgc jv";
    string str_g = "our language is impossible to understand there are twenty six factorial possibilities so it is okay if you want to just give up";
    
    string str_tmp;
    
    sort(str.begin(), str.end());
    sort(str_g.begin(), str_g.end());
    
    cout << "[ str__ ]" << str << endl;
    
    cout << "[ str_g ]" << str_g << endl;
    
}

/**
 * 主方法
 */
int main(int argc, const char * argv[]) {
    
//    analyse_str();
    
    map<char, char> char_map;
    
    string inp_str = "ejp mysljylc kd kxveddknmc re jsicpdrysi rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd de kr kd eoya kw aej tysr re ujdr lkgc jv";
    
    string out_str = "our language is impossible to understand there are twenty six factorial possibilities so it is okay if you want to just give up";
    
    string kk;
    int tt;
    
    for (int i = 0; i < inp_str.length(); i++) {
        char_map[inp_str[i]] = out_str[i];
    }
    
    
    sort(inp_str.begin(), inp_str.end());
    
    char_map['q'] = 'z';
    char_map['z'] = 'q';
    char_map[' '] = ' ';
    

    ifstream from_filecontent;
    
    from_filecontent.open("/Users/grs/Documents/c_program/code_jame_Cpp/A-small-practice_googlelang.in");
    getline(from_filecontent, kk);
    
    tt = stoi(kk);
    cout << tt << endl;
    
    for (int i = 0; i< tt; i++) {
        getline(from_filecontent, kk);
        
        string output_line;
        for (int i =0; i< kk.length(); i++) {
            output_line += char_map[kk[i]];
        }
        
        cout << "Case #" << i+1 << ": " << output_line << endl;
    }

    
    return 0;
}
















