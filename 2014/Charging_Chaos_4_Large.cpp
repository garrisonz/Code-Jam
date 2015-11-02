//
//  main.cpp
//  Code_jam_Charging_Chaos4
//
//  the problem : https://code.google.com/codejam/contest/2984486/dashboard
//
//  Created by grs on 15/4/12.
//  Copyright (c) 2015年 grs. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>

#include <unistd.h>
#include <time.h>
#include <math.h>


using namespace std;



/**
 * 把字符串分割为 字符串向量
 *
 * @param string separator 分隔字符串
 * @param string str
 */
vector<string> explode(const string& separator, const string& str){
    
    vector<string> v;
    
    std::string::size_type pos1, pos2;
    
    pos2 = str.find(separator);
    pos1 = 0;
    
    while(std::string::npos != pos2){
        v.push_back(str.substr(pos1, pos2 - pos1));
        
        pos1 = pos2 + separator.size();
        pos2 = str.find(separator, pos1);
    }
    
    if(pos1 != str.length()){
        v.push_back(str.substr(pos1));
    }
    
    
    return v;
}



int resolve_charge(int num, int length, string outlet_s, string require_s){
    
    vector<string> v_outlet = explode(" ", outlet_s);
    vector<string> v_require = explode(" ", require_s);
    
    
    vector<vector<string>> flip_map;
    
    vector<string>::iterator out_itor;
    vector<string>::iterator req_itor;
    for (out_itor = v_outlet.begin(); out_itor != v_outlet.end(); out_itor++) {
        
        //        cout << *out_itor << endl;
        
        string out_tmp = *out_itor;
        
        vector<string> map_v_tmp;
        
        for (req_itor = v_require.begin(); req_itor != v_require.end(); req_itor++) {
            //            cout << " - " << *req_itor ;
            
            string map_str_tmp = "";
            string req_tmp = *req_itor;
            for (int i = 0; i < length ; i++) {
                map_str_tmp += req_tmp[i] == out_tmp[i] ? "0" : "1";
            }
            
            //            cout  << "|" << map_str_tmp << endl;
            
            map_v_tmp.push_back(map_str_tmp);
        }
        
        flip_map.push_back(map_v_tmp);
    }
    //    cout << endl;
    
    map<string, int> m_xor_result;
    
    vector<string> v_str;
    for (vector<vector<string>>::iterator  map_vv = flip_map.begin(); map_vv != flip_map.end(); map_vv++) {
        v_str = * map_vv;
        for (vector<string>::iterator s_itor = v_str.begin(); s_itor != v_str.end(); s_itor++) {
            
            if(m_xor_result.find(*s_itor) == m_xor_result.end()){
                m_xor_result[*s_itor] = 1;
                //                cout << " no " << *s_itor << endl;
                
            }else{
                m_xor_result[*s_itor]++;
                //                cout << " ++ " << *s_itor;
            }
        }
    }
    //    cout << endl;
    
    //    for (map<string, int>::iterator m_itor = m_xor_result.begin(); m_itor != m_xor_result.end(); m_itor++) {
    //        cout << m_itor->first << " " << m_itor->second << endl;
    //    }
    
    
    int mini_filp_cnt = -1;
    for (map<string, int>::iterator m_itor = m_xor_result.begin(); m_itor != m_xor_result.end(); m_itor++) {
        
        if(m_itor->second == num){
            string xor_s = m_itor->first;
            int flip_cnt = 0;
            for (int i = 0; i < xor_s.length(); i++) {
                if (xor_s[i] == '1') {
                    flip_cnt++;
                }
            }
            
            if (mini_filp_cnt == -1 || flip_cnt < mini_filp_cnt) {
                mini_filp_cnt = flip_cnt;
            }
            
//            cout << "[ok]" << xor_s << " " << m_itor->second << endl;
        }
    }
    
//    cout << "[ ]" << mini_filp_cnt;

    return mini_filp_cnt;
    
}

int main(int argc, const char * argv[]) {
    
    string s;
    string outlet_s;
    string require_s;
    
    
    ifstream from_filecontent;
    
    //        from_filecontent.open("/Users/grs/Documents/c_program/code_jam_Charging_Chaos3/A-large-practice.in");
    from_filecontent.open("/Users/grs/Documents/c_program/Charging_Chaos_resource/A-large-practice.in");
    
    
    getline(from_filecontent, s);
    int case_num = stoi(s);
    
    for (int case_i = 1; case_i <= case_num; case_i++) {
        
        
        getline(from_filecontent, s);
        vector<string> vect_str = explode(" ", s);
        
        int num, length;
        num = stoi(vect_str[0]);
        length = stoi(vect_str[1]);
        
        
        getline(from_filecontent, outlet_s);
        getline(from_filecontent, require_s);
        
        //    cout << "[ outlet ]" << outlet_s << endl;
        //    cout << "[ requir ]"<< require_s << endl;
        
        int flip_cnt = resolve_charge(num, length, outlet_s, require_s);
        
        if (flip_cnt == -1) {
            cout << "Case #" << case_i << ": " << "NOT POSSIBLE" << endl;
        }else{
            cout << "Case #" << case_i << ": " <<flip_cnt << endl;
        }
        
        
    }

    
    return 0;
}






