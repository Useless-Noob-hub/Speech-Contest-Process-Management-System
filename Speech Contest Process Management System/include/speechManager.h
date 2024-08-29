#pragma once
#include "iostream"
using namespace std;
#include "speaker.h"
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <ctime>
#include <deque>
#include<numeric>
#define group_num 6
#include <fstream>

//设计演讲管理类

class speechManager
{
private:
    //比赛选手容器 12人
    vector<int>vNum;
    //决赛选手容器
    vector<int>vFinal;
    //最终选手容器
    vector<int>vVictory;
    //存放编号 以及 对应的具体选手容器
    map<int,Speaker>mSpeaker;

    //记录比赛论数
    int m_Index;
    
    //存放往届记录的容器
    map<int,vector<string>>m_Record;
        //判断文件是否为空
    bool fileIsEmpty;
public:
    //构造函数
    speechManager(/* args */);
    // 析构函数
    ~speechManager();
    // 显示菜单
    void show_Menu();
    // 退出系统
    void exitSystem();

    // 初始化容器
    void initSpeech();

    // 创建选手
    void createSpeaker();
    // 开始比赛
    void startSpeech();

    //抽签
    void speechDraw();

    //分组
    void speechGroup();

    //评委评分
    void speechContest();

    //显示得分
    void showScore();

    void saveRecord();

    //读取记录
    void loadRecord();

    //显示往届记录
    void showRecord();

    //清空往届记录
    void clearRecord();
};

