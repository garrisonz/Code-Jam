//
//  main.cpp
//  code_jam_Charging_Chaos2
//
//  code jame 练习，问题见链接：
//  https://code.google.com/codejam/contest/2984486/dashboard
//
//  Created by grs on 15/3/29.
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

long start_time = time(NULL);
long end_time;

/**
 * 输出程序耗费的时间
 */
void spend_time(string str){
    
    end_time = time(NULL);
    cout << "[ " << str << " ]" << end_time - start_time << "s " << endl;
    
}


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

/**
 * 把字符串分割为 字符串向量
 *
 * @param string separator 分隔字符串
 * @param string str
 */
map<string, string> explode_map(const string& separator, const string& str){
    
    vector<string> result;
    map<string, string> m_str;
    
    std::string::size_type pos1, pos2;
    
    pos2 = str.find(separator);
    pos1 = 0;
    
    while(std::string::npos != pos2){
        result.push_back(str.substr(pos1, pos2 - pos1));
        
        m_str[str.substr(pos1, pos2 - pos1)] = "";
        
        pos1 = pos2 + separator.size();
        pos2 = str.find(separator, pos1);
    }
    
    if(pos1 != str.length()){
        result.push_back(str.substr(pos1));
        m_str[str.substr(pos1)] = "";
    }
    
    
    return m_str;
}


/**
 * 获得十进制的 二进制表示法，返回含有二进制的字符串
 */
string get_binary_int(int n){
    stack<int> bin_stack;
    string str;
    
    while (n >= 2) {
        bin_stack.push(n % 2);
        n = n/2;
    }
    bin_stack.push(n);
    
    while (!bin_stack.empty()) {
        str += to_string(bin_stack.top());
        bin_stack.pop();
    }
    
    return str;
}

/**
 * 获得十进制的 二进制表示法，当位数不足时，在最前面补 0
 *
 * @param int n 十进制值
 * @param int lenth 位数
 *
 */
string get_binary_int_full(int n, int lenth){
    string bin_str = get_binary_int(n);
    while (bin_str.length() < lenth) {
        bin_str = "0" + bin_str;
    }
    
    return bin_str;
}


/**
 * 根据开关bin_str 对 一个出口电流 iter_str 做出口电流调整。
 */
string string_yh_operate(string bin_str, string iter_str){
    
    for (int i = 0; i< bin_str.length(); i++) {
        if(bin_str[i] == '1'){
            int i_tmp = abs(iter_str[i] - '1');
            iter_str[i] = (int)'0' + i_tmp;
        }
    }
    
    return iter_str;
}

/**
 * 根据字符串中的 1 的个数，进行对比
 */
bool lessmark(const string& stItem1, const string& stItem2)
{
    int one_num_str1=0;
    for (int i = 0; i <stItem1.size(); i++) {
        if(stItem1[i] == '1'){
            one_num_str1++;
        }
    }
    
    int one_num_str2=0;
    for (int i = 0; i <stItem2.size(); i++) {
        if(stItem2[i] == '1'){
            one_num_str2++;
        }
    }
    
    return one_num_str1 < one_num_str2;
}


/**
 * 对一次 出口电流、设备要求的流量进行匹配。
 * 返回出口电流 至少需要改变的电流位数；
 * 返回 -1 表示 出口电流所有改变都不可以满足设备要求
 *
 * @param int num 出口电流个数，同时也是设备要求的电流个数
 * @param int lenth 电流位数
 * @param string outlet_s 出口电流，不同电流 用空格分隔，如 01 11 10
 * @param string require_s 设备要求的电流，不同电流 用空格分隔，如 11 00 10
 *
 */
int flip_outlet_solution(int num, int lenth, string outlet_s, string require_s){
    
    vector<string> v_outlet = explode(" ", outlet_s);
    map<string, string> m_requie = explode_map(" ", require_s);
    
    map<string, string>::iterator m_iter;
    
    // 将出口电流 换电流，根据全组合将出口电流的所有 电流位切换的可能都换一次，并将每一次的切换 做下面的判断
    
    long combinate_num = pow(2, lenth) - 1;
    
//    cout << combinate_num;
    
    vector<string> bin_str_v ;
    for (int i=0; i<= combinate_num; i++) {
        
        // 得到足位的 二进制表示的字符串， 用于转换 出口电流
        string bin_str = get_binary_int_full(i, lenth);
        bin_str_v.push_back(bin_str);
    }

    
    vector<string>::iterator s_iter;
    
//    cout << "[ bin_str_v ]" << bin_str_v.size();
    
//    for (s_iter = bin_str_v.begin(); s_iter != bin_str_v.end(); s_iter++) {
//        cout << *s_iter << " ";
//    }
//    cout << endl;

    
    // 对 bin_str_v 里面字符串中得 1 的个数进行排序，从个数小 到个数大
    sort(bin_str_v.begin(), bin_str_v.end(), lessmark);
    
//    cout << "[ after sort ]";
//    for (s_iter = bin_str_v.begin(); s_iter != bin_str_v.end(); s_iter++) {
//        cout << *s_iter << " ";
//    }
//    cout << endl;
    
    int flip_num = -1;
    
    
    for (s_iter = bin_str_v.begin(); s_iter != bin_str_v.end(); s_iter++) {
        
        string bin_str = *s_iter;
        
        // 转换出口电流
        vector<string>::iterator ss_iter;
        vector<string> v_outlet_flip;
        for (ss_iter = v_outlet.begin(); ss_iter != v_outlet.end(); ss_iter++) {
            
            string iter_str = *ss_iter;
            iter_str = string_yh_operate(bin_str, iter_str);
            
            v_outlet_flip.push_back(iter_str);
        }
        
        // 匹配 出口电流 和 设备要求的电流
        int mapping_item = 0;
        for (ss_iter = v_outlet_flip.begin(); ss_iter != v_outlet_flip.end(); ss_iter++) {
            m_iter = m_requie.find(*ss_iter);
            if (m_iter == m_requie.end()){
                
                break;
            }else{
                // 匹配通过的个数
                mapping_item++;
            }
        }
        
        
        if (mapping_item == v_outlet.size()){
            // 全部匹配， 匹配完成
//            cout << "[ succ ]" << bin_str << endl;
            
            flip_num = 0;
            for (int s_int = 0; s_int < bin_str.size(); s_int++) {
                if(bin_str[s_int] == '1'){
                    flip_num++;
                }
            }
            break;
        }else{
            // 其中 至少有一个不匹配，匹配失败，进入下个 开关配置的匹配
            //            cout << "[ fail ]" << endl;
        }
    }
    
    return flip_num;
}


/**
 * 主函数
 */
int main(int argc, const char * argv[]) {

    string s;
    
    ifstream from_filecontent;
    
    from_filecontent.open("/Users/grs/Documents/c_program/code_jam_Charging_Chaos2/A-small-practice.in");
    getline(from_filecontent, s);
    
    int case_num = stoi(s);
    
    for (int case_i = 0; case_i < case_num; case_i++) {
        
        
        getline(from_filecontent, s);
        vector<string> vect_str = explode(" ", s);
        
        int num, lenth;
        
        num = stoi(vect_str[0]);
        lenth = stoi(vect_str[1]);
        
        string outlet_s;
        string require_s;
        
        getline(from_filecontent, outlet_s);
        getline(from_filecontent, require_s);
        
//        cout << "[ num ]" <<  num << "[ lenth ]" << lenth << endl;
        
        int flip_num = flip_outlet_solution(num, lenth, outlet_s, require_s);
        
//        spend_time("done");

        if (flip_num == -1) {
            cout << "Case #" << case_i+1 << ": " << "NOT POSSIBLE" << endl;
        }else{
            cout << "Case #" << case_i+1 << ": " << flip_num << endl;
        }
        
    }

    cout << "[ end ]" ;
    
    return 0;
}






