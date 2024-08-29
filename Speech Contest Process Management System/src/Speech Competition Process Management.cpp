#include "speechManager.h"

int main()
{
    srand((unsigned int)time(NULL));
    speechManager sm;
    //测试12名选手的创建

    int choice = 0;//用于用户的输入
    cout<<"**********************************************"<<endl;
    while(true)
    {
        sm.show_Menu();
        cout << "请输入您的选择：" << endl;
        cin >> choice; 

        switch(choice)
        {
            case 1:
                sm.startSpeech();
                break;
            case 2:
                sm.showRecord();
                break;
            case 3:
                sm.clearRecord();
                break;
            case 0:
                sm.exitSystem();
                break;  
            default:
                cout << "输入错误，请重新输入" << endl;
                system("cls");

        }
    }

    system("pause");
    return 0;
}