#include "speechManager.h"

speechManager::speechManager(/* args */)
{
    this->initSpeech();
    this->createSpeaker();
    this->loadRecord();
}

speechManager::~speechManager()
{

}

void speechManager::show_Menu()
{
    cout << "************************************************" << endl;
    cout << "**************  欢迎参加演讲比赛  **************" << endl;
    cout << "**************  1. 开始演讲比赛   **************" << endl;
    cout << "**************  2. 查看往届记录   **************" << endl;
    cout << "**************  3. 删除比赛记录   **************" << endl;
    cout << "**************  0. 退出系统       **************" << endl;
    cout << "************************************************" << endl;

}

void speechManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}

void speechManager::initSpeech()
{
    //容器保证为空
    this->vNum.clear();     //清空选手编号
    this->mSpeaker.clear(); //清空选手容器
    //初始化比赛论数
    this->m_Index=1;
    this->m_Record.clear();
}

void speechManager::createSpeaker()
{
    string nameseed = "ABCDEFGHIJKL";
    int i = 0;
    while(i<nameseed.size())
    {
        string name = "选手";
        name += nameseed[i++];
        this->vNum.push_back(i+1000);
        this->mSpeaker.insert(pair<int,Speaker>(i+1000,Speaker(name)));
    }
}

void speechManager::startSpeech()
{   
    //显示所有选手
    cout << "所有选手如下：" << endl;
    for(map<int,Speaker>::iterator it = this->mSpeaker.begin();it!=this->mSpeaker.end();it++)
    {
        cout<<it->first<<"号选手："<<it->second.m_Name<<endl;
    }
    system("pause");
    system("cls");
    for(m_Index=1;m_Index<3;m_Index++){
    //第一轮比赛
    //1、抽签
    this->speechDraw();
    //2、比赛
    this->speechContest();
    //3、显示晋级结果
    this->showScore();
    //第二轮比赛
    }
    //4、保存分数
    saveRecord();

    //充值比赛，获取记录
    this->initSpeech();
    this->createSpeaker();
    this->loadRecord();

    cout<<"本次比赛结束"<<endl;

    system("pause");
    system("cls");

}

void speechManager::speechDraw()
{
    random_shuffle(this->vNum.begin(),this->vNum.end());
    cout<< "第《" << this->m_Index << "》轮比赛抽签结果：" << endl;
    //  (this->vNum.size()/group_num+1)表示总分组数
    for(int group=1;group<(this->vNum.size()/group_num+1);group++)
    {
        cout<<"第"<<group<<"组：";
        //偏移量
        int offset = (group-1)*group_num;
        for_each(this->vNum.begin()+offset,this->vNum.begin()+offset+group_num,[](int v)
    {cout <<v << " " ;});
    cout << endl;
    }
    
    system("pause");
    system("cls");
}



void  speechManager::speechContest()
{
    //排序容器
    multimap<double,int,greater<double>> m_Group;

    //第几轮

    int num = 0;//确定该选手属于第几轮
    //第几组
    for(vector<int>::iterator it=this->vNum.begin();it!=this->vNum.end();it++)
    {
        cout<<*it<<"号选手："<<this->mSpeaker.find(*it)->second.m_Name<<"得分情况：";
        //开始打分
        deque<double> scores;
        for(int j=0;j<10;j++)
        {
            scores.push_back((rand()%410+600)/10);
        }
        for_each(scores.begin(),scores.end(),[](double v){cout<<v<<" ";});
        cout<<endl;
        
        sort(scores.begin(),scores.end(),greater<double>());
        scores.pop_back();
        scores.pop_front();
        double sum=accumulate(scores.begin(),scores.end(),0);
        double avg=sum/scores.size();
        this->mSpeaker.find(*it)->second.m_Score[m_Index-1]=avg;
        //分组排序容器
        m_Group.insert(make_pair(avg,*it));


        num++;
        if(num%group_num==0)
        {
            cout<<"第"<<num/group_num<<"组比赛结果："<<endl;
            cout<<"编号\t姓名\t分数"<<endl;
            int finalnum=3;
            for(multimap<double,int>::iterator it=m_Group.begin();it!=m_Group.end();it++)
            {
                cout<<it->second<<"\t"<<this->mSpeaker.find(it->second)->second.m_Name<<"\t"<<it->first<<endl;
                //将晋级的选手编号保存到vFinal容器中
                if(finalnum>0)
                {
                    this->vFinal.push_back(it->second);
                    finalnum--;
                }
            }
            m_Group.clear();

        }
    }
    vNum=vFinal;//将晋级选手编号保存到vNum容器中
    if(m_Index==2)
    {
        vVictory=vFinal;
    }
    vFinal.clear();
    system("pause");
    system("cls");

}

void speechManager::showScore()
{
    cout<<"-------------第"<<this->m_Index<<"轮晋级选手---------------"<<endl;
    
    vector<int>v=this->vNum;

    for(vector<int>::iterator it=v.begin();it!=v.end();it++)
    {
        cout<<*it<<"号选手："<<this->mSpeaker.find(*it)->second.m_Name<<"得分："<<this->mSpeaker.find(*it)->second.m_Score[this->m_Index-1];
        cout<<endl;
    }
    v.clear();
    system("pause");
    system("cls");
}

void speechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("bin/speech.csv",ios::out|ios::app);   //用追加的方式写文件

    // 将每个选手数据 写入到文件中
    for(vector<int>::iterator it =vVictory.begin();it!=vVictory.end();it++)
    {
        ofs<<*it<<","<<this->mSpeaker.find(*it)->second.m_Score[1]<<",";
    }
    ofs<<endl;

    // 关闭文件
    ofs.close();
    cout<<"保存成功"<<endl;
    //有记录了，文件不为空
    this->fileIsEmpty = false;
}

void speechManager::loadRecord()
{
    ifstream ifs("bin/speech.csv",ios::in);//读文件

    if(!ifs.is_open())
    {
        this->fileIsEmpty = true;
        cout<<"文件不存在"<<endl;
        ifs.close();
        return;
    }

    //文件清空清空
    char ch;
    ifs>>ch;
    if(ifs.eof())
    {
        this->fileIsEmpty = true;
        cout<<"文件为空"<<endl;
        ifs.close();
        return;
    }

    //文件不为空
    this->fileIsEmpty = false;
    ifs.putback(ch);    //将上面读取的单个字符 放回来
    string data;
    int index = 0;
    while(ifs>>data)
    {
        vector<string>v;
        // cout<<data<<endl;
        // 解析数据
        int pos =-1;//查到，位置的变量
        int start = 0;

        while(1){
            pos = data.find(",",start);
            if(pos==-1)
            {
                //没找到
                break;
            }
            string temp = data.substr(start,pos-start);
            // cout<<temp<<endl;
            v.push_back(temp);

            start = pos+1;
        }
        this->m_Record.insert(make_pair(index,v));
        index++;
    }

    ifs.close();

    // for(map<int,vector<string>>::iterator it=this->m_Record.begin();it!=this->m_Record.end();it++)
    // {
    //     cout<<"第"<<it->first+1<<"届"<<"比赛记录："<<"冠军编号："<<it->second[0]<<"分数："<<it->second[1]<<endl;

    // }
}

void speechManager::showRecord()
{
    if(this->fileIsEmpty)
    {
        cout<<"文件为空或者文件不存在"<<endl;
    }
    for(int i =0 ;i<this->m_Record.size();i++)
    {
        cout<<"第"<<i+1<<"届"<<"比赛记录："<<"冠军编号："<<this->m_Record[i][0]<<"分数："<<this->m_Record[i][1]<<endl;
        cout<<"第"<<i+1<<"届"<<"比赛记录："<<"亚军编号："<<this->m_Record[i][2]<<"分数："<<this->m_Record[i][3]<<endl;
        cout<<"第"<<i+1<<"届"<<"比赛记录："<<"季军编号："<<this->m_Record[i][4]<<"分数："<<this->m_Record[i][5]<<endl;
    }
    system("pause");
    system("cls");
}

void speechManager::clearRecord()
{
    cout<<"确认清空？1.确认 0.取消"<<endl;
    int select = 0;
    cin>>select;
    if(select==1)
    {
        //打开模式 ios::trunc 如果存在删除文件并重新创建
        ofstream ofs("bin/speech.csv",ios::trunc);
        ofs.close();
        //初始化
        this->initSpeech();
        this->createSpeaker();
        this->loadRecord();
        this->m_Record.clear();
        this->fileIsEmpty = true;
        cout<<"清空成功"<<endl;
    }
    system("pause");
    system("cls");
}
