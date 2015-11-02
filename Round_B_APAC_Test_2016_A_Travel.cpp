//
// solution for https://code.google.com/codejam/contest/10214486/dashboard
// 
//  main.cpp
//  Google_Code_Jam
//
//  Created by grs on 10/15/15.
//  Copyright © 2015 grs. All rights reserved.
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

#include <chrono>
#include <thread>

#include "runtime.h"

using namespace std;


#define null_symble  -2147483648
#define infinity 2147483647
#define timeRough 24

int tiggle = 0;

class UndirectedGraphNode {

public:
	int label;
	vector<UndirectedGraphNode *> neighbors;

	int costHour = infinity;
	int arriveTime = 0;
	UndirectedGraphNode* previous = NULL;
	
	
	UndirectedGraphNode(int x){
		this->label = x;
	}
	
	void setCostHour(int coutHour){
		this->costHour = coutHour;
	}
	
	void setArriveTime(int pathcost){
		this->arriveTime = (this->previous->arriveTime + pathcost) % timeRough;
	}
	
	/**
	 * 清除节点的路径记录
	 */
	void clearPathRecord(){
		costHour = infinity;
		arriveTime = 0;
		previous = NULL;
	}
	
	void printSelf(){
		
		cout << label << "| " << costHour << ", " << arriveTime << " |";
		if (previous) {
			cout << previous->label << "\n";
		}else{
			cout << previous << "\n";
		}
	}
	
};



class Path{
private:
	map<string, vector<int>> path_cost;
	
public:
	
	Path(){}
	
	void setPathCost(UndirectedGraphNode* node1, UndirectedGraphNode* node2, vector<int> cost){
		string tmp = to_string(node1->label) + "|" + to_string(node2->label);
		path_cost[tmp] = cost;
	}
	
	int getPathCost(UndirectedGraphNode* node1, UndirectedGraphNode* node2){
		string tmp = to_string(node1->label) + "|" + to_string(node2->label);
		vector<int> cost_vect = path_cost[tmp];
		
		int arriveTime1 = node1->arriveTime;
		int cost = cost_vect[arriveTime1];
		
		return cost;
	}
	
	void printSelf(){
		map<string, vector<int>>::iterator m_iter;
		
		cout << "\t\t";
		for (int i = 0 ; i < timeRough; i++) {
			cout << i << "\t";
		}
		cout << "\n";
		
		for (m_iter = path_cost.begin(); m_iter != path_cost.end(); m_iter++) {
			cout << m_iter->first << "\t\t";
			vector<int> tmp = m_iter->second;
			for (int i = 0 ; i < tmp.size(); i++) {
				cout << tmp[i] << "\t";
			}
			cout << "\n";
		}
	}
};





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





class NodeSet{
private:
	map<int, UndirectedGraphNode*> label_node;
	
public:
	long contain(int label){
		long res =label_node.count(label);
		return res;
	}
	
	void append(UndirectedGraphNode* node){
		label_node[node->label] = node;
	}
	
	UndirectedGraphNode* getNode(int label){
		return label_node[label];
	}
	
	map<int, UndirectedGraphNode*> getLableNode(){
		return label_node;
	}
	
	/**
	 * 获取集合中，耗费时间最短的那个点，并将那个点从集合中去掉。
	 *
	 */
	UndirectedGraphNode* Extract_minCostHour(){
		map<int, UndirectedGraphNode*>::iterator m_iter;
		UndirectedGraphNode* minCost = label_node.begin()->second;
		for (m_iter = label_node.begin(); m_iter != label_node.end(); m_iter++) {
			if (minCost->costHour > m_iter->second->costHour) {
				minCost = m_iter->second;
			}
		}
		
		label_node.erase(minCost->label);
		
		return minCost;
	}
	
	long size(){
		return label_node.size();
	}
	
	/**
	 * 清除所有节点的路径记录
	 *
	 */
	void clearAllNodePathRecord(){
		map<int, UndirectedGraphNode*>::iterator m_iter;
		for (m_iter = label_node.begin(); m_iter != label_node.end(); m_iter++) {
			m_iter->second->clearPathRecord();
		}
	}
	
	void printself(){
		map<int, UndirectedGraphNode*>::iterator m_iter;
		for (m_iter = label_node.begin(); m_iter != label_node.end(); m_iter++) {
			UndirectedGraphNode* tmpNode = m_iter->second;
			cout << tmpNode->label << " | " << tmpNode->costHour << ", " << tmpNode->arriveTime << " | ";
			
			if (tmpNode->previous != NULL) {
				cout << tmpNode->previous->label << "\n";
			}else{
				cout << tmpNode->previous << "\n";
			}
			
		}
	}
	
	NodeSet(){}
};


/**
 * 获得 s 时刻从节点 1 出发到达目标节点 target 的最小时间成本
 *
 */
int getSingleSourceMinCost(NodeSet* graphNode, Path* graphPath, int target, int s){
	
	
	graphNode->clearAllNodePathRecord();
	
	UndirectedGraphNode* source = graphNode->getNode(1);
	source->costHour = 0;
	source->arriveTime = s;
	source->previous = source;
	
	NodeSet* S = new NodeSet();
	
	NodeSet* Q = new NodeSet();
	
	map<int , UndirectedGraphNode*> tmp_nodeSet = graphNode->getLableNode();
	map<int, UndirectedGraphNode*>::iterator m_iter;
	for (m_iter = tmp_nodeSet.begin(); m_iter != tmp_nodeSet.end(); m_iter++) {
		Q->append(m_iter->second);
	}
	
	// Dijkstra 算法，求单源最短路径成本
	while (Q->size()) {
		UndirectedGraphNode* u = Q->Extract_minCostHour();
		S->append(u);
		
		for (int i = 0 ; i < u->neighbors.size(); i++) {
			UndirectedGraphNode* v = u->neighbors[i];
			
			int thePathCost = graphPath->getPathCost(u, v);
			
			if (u->costHour == infinity) {
				continue;
			}
			
			if (v->costHour > u->costHour + thePathCost) {
				v->previous = u;
				v->setCostHour(u->costHour + thePathCost);
				v->setArriveTime(thePathCost);
			}
		}
	}
	
//	graphNode->printself();
//	exit(0);
	
	UndirectedGraphNode* targetNode = graphNode->getNode(target);
	
//	targetNode->printSelf();
	
	int minCost = targetNode->costHour;
	
	if (minCost == infinity) {
		minCost = -1;
	}
	
	return minCost;
}

/**
 * 获得一个图 案例的结果
 *
 */
void caseResolve(ifstream& from_filecontent){
	
	
	string s;
	
	getline(from_filecontent, s);
	vector<string> vect_str = explode(" ", s);
	
	int N, M, K;
	N = stoi(vect_str[0]);
	M = stoi(vect_str[1]);
	K = stoi(vect_str[2]);
	
	Path* graphPath = new Path();
	
	NodeSet* graphNode = new NodeSet();
	
	for (int i = 1; i <= N ; i++) {
		UndirectedGraphNode* tmpNode = new UndirectedGraphNode(i);
		graphNode->append(tmpNode);
	}
	
	
	for (int i = 0; i < M ; i++) {
		
		string city_str;
		getline(from_filecontent, city_str);
		
		vector<string> vect_str = explode(" ", city_str);
		
		int city1 = stoi(vect_str[0]);
		int city2 = stoi(vect_str[1]);
		
		
		// 建立节点之间的连接关系
		
		UndirectedGraphNode* node1 = graphNode->getNode(city1);
		UndirectedGraphNode* node2 = graphNode->getNode(city2);
		
		
		node1->neighbors.push_back(node2);
		node2->neighbors.push_back(node1);
		
		
		// 放进成本映射表
		
		string cost_str;
		getline(from_filecontent, cost_str);
		vector<string> cost_vect = explode(" ", cost_str);
		
		vector<int> cost_vect_int;
		for (int i = 0; i < cost_vect.size(); i++) {
			cost_vect_int.push_back(stoi(cost_vect[i]));
		}
		
		graphPath->setPathCost(node1, node2, cost_vect_int);
		graphPath->setPathCost(node2, node1, cost_vect_int);
	}
	
//	graphNode->printself();
//	cout << "\n----\n";
//	graphPath->printSelf();
//	exit(0);
	
	
	// 求从原节点 1 开始出发，在 t 时刻出发，得到的单源最短路径
	
	for (int i = 1; i <= K ; i++) {
		
		string q_str;
		getline(from_filecontent, q_str);
		vector<string> q_vect = explode(" ", q_str);
		
		int d = stoi(q_vect[0]);
		int t = stoi(q_vect[1]);
		int costHour;
		
		costHour = getSingleSourceMinCost(graphNode, graphPath, d, t);
		
//		cout << " Q"<< i << " - " ;

		cout << costHour << " ";
		
//		cout << "\n";

		if (i % 500 == 0) {
			std::this_thread::sleep_for(std::chrono::microseconds(1000000));
		}
		
	}
}


int main(int argc, const char * argv[]) {
	
//	runtime* rt = new runtime();
	
	ifstream from_filecontent;
	
	from_filecontent.open("/Users/grs/Documents/c_program/Programming_Pearls/Google_Code_Jam/A-large-practice.in");

	
	string s;
	getline(from_filecontent, s);
	int T = stoi(s);
	
	for (int i = 1 ; i <= T; i++) {
		
		cout << "Case #"<< i << ": ";
		
		caseResolve(from_filecontent);
		
		cout << "\n\n\n";
		break;
	}


//	rt->havespend(" end ");
	
    return 0;
}
