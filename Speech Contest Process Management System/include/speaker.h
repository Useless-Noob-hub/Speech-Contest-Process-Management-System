#pragma once
#include <iostream>
using namespace std;

//选手类
class Speaker
{
friend class speechManager;
public:
    Speaker(string name );
    void setScore(int i, int score);
    ~Speaker();


private:
    string m_Name;  //姓名
    double m_Score[2];  //分数 ，最多有两轮得分

};