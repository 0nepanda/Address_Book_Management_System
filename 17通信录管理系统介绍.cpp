#include <iostream>
#include <string>
#include <cstdlib> //system
#include <stdlib.h>
using namespace std;
#define MAX 1000  //宏常量

//菜单界面
void showMenu()
{
    cout << "****************************" << endl;
    cout << "*****  1、 添加联系人  *****" << endl;
    cout << "*****  2、 显示联系人  *****" << endl;
    cout << "*****  3、 删除联系人  *****" << endl;
    cout << "*****  4、 查找联系人  *****" << endl;
    cout << "*****  5、 修改联系人  *****" << endl;
    cout << "*****  6、 清空联系人  *****" << endl;
    cout << "*****  0、 退出通信录  *****" << endl;
    cout << "****************************" << endl;

}

//联系人结构体
struct Person
{
    string m_Name;
    int m_Sex;       //1男2女
    int m_age;
    string m_Phone;
    string m_Address; //地址
};

//通讯录结构体
struct AddressBooks
{   
    struct Person personArray[MAX];  //通讯录中保存的联系人数组

    int m_Size;               //通讯录中人员个数
};

// 1、添加联系人函数
void addPerson(struct AddressBooks *abs)
{
    //判断通讯库是否满了
    if (abs->m_Size == MAX)
    {
        /* 已经满了 */
        cout << "通讯录已满，无法添加！" << endl;
        return;
    }
    else
    {
        // 添加具体联系人

        // 姓名
        string name;
        cout << "请输入姓名： " << endl;
        cin >> name;
        abs->personArray[abs->m_Size].m_Name = name;

        // 性别
        int sex = 0;
        while (true)
        {
            /* 写对性别为止 */
            cout << "请输入性别：" << endl;
            cout << "1---男 " << endl;
            cout << "2---女 " << endl;
            cin >> sex;
            if (sex == 1 || sex == 2)  //性别无误
            {
                /* code */
                abs->personArray[abs->m_Size].m_Sex = sex;
                break;
            }
            else
            {
                cout << "输入有误，重新输入" << endl;
            }
        }
        
        // 年龄
        int age = 0 ;
        cout << "请输入年龄：" << endl;
        cin >> age;
        abs->personArray[abs->m_Size].m_age = age;

        // 联系电话
        string phone;
        cout << "请输入联系电话：" << endl;
        cin >> phone;
        abs->personArray[abs->m_Size].m_Phone = phone;

        // 住址
        string address;
        cout << "请输入地址：" << endl;
        cin >> address;
        abs->personArray[abs->m_Size].m_Address = address;

        // 更新通讯录人数
        abs->m_Size++;
        cout << "添加成功" <<endl;

        system("pause");    //按任意键继续
        system("cls");      //清屏
        
    }
    
}

// 2、显示联系人
void showPerson(struct AddressBooks *abs)
{
    //判断通讯录是否为空
    if (abs->m_Size == 0)
    {
        /* code */
        cout << "当前通讯录为空" << endl;
    }
    else
    {
        for (int i = 0; i < abs->m_Size; i++)
        {
            /* code */
            cout << "姓名：" << abs->personArray[i].m_Name << "\t";
            cout << "性别：" << (abs->personArray[i].m_Sex == 1 ? "男" : "女") << "\t";  //三目运算符
            cout << "年龄：" << abs->personArray[i].m_age << "\t";
            cout << "联系电话：" << abs->personArray[i].m_Phone << "\t";
            cout << "住址：" << abs->personArray[i].m_Address<< endl;
        }
        
    }
    
}

// 3、删除联系人
// 3.1 检测联系人是否存在 （因为查找和修改联系人都需要用到这个模块所以单独拉出）。
int isExist(struct AddressBooks *abs, string name)
{
    // cout << "判断" << endl;
    for (int i = 0; i < abs->m_Size+1; i++) //检测的本质就是遍历  ||这里有过修改，循环不进入
    {
        /* code */
        // cout << "判断14" << endl;
        if (abs->personArray[i].m_Name == name)
        {
            /* 通讯录某行找到该姓名 */
            // cout << "名字相等" << endl;
            return i;  //传回这个人在数组中的编号
        }
        else          //遍历结束仍没找到
        {
            // cout << "名字不相等" << endl;
            return -1;
        }
    }
    
}

// 3.2 检测后删除联系人
void deletePerson(struct AddressBooks *abs)
{
    cout << "请输入一个联系人：" << endl;

    string name;
    cin >> name;

    int ret = isExist(abs, name);  //137行定义的是地址啊，为什么这里放结构体名？  是因为结构体名就是首地址？

    if (ret != -1)
    {
        /* 有这个联系人，等会删除.即将结构体数组中要删除的内容后的所有数组元素前移 */
        for (int i = ret; i < abs->m_Size; i++)
        {
            /* 数据前移 */
            abs->personArray[i] = abs->personArray[i+1];
        }
        abs->m_Size--; // 更新联系人结构体数组，数组少了一组元素
        cout << "删除成功" << endl;
    }
    
}

// 4、查找指定联系人信息
void findPerson(struct AddressBooks *abs)
{
    cout << "请输入要查找的联系人姓名：" << endl;
    
    string name;
    cin >> name;
    
    int ret = isExist(abs, name);
    cout << ret << endl;
    if (ret != -1)
    {
        /* 存在 */
        cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
        cout << "性别：" << abs->personArray[ret].m_Sex << "\t";
        cout << "年龄：" << abs->personArray[ret].m_age << "\t";
        cout << "电话：" << abs->personArray[ret].m_Phone << "\t";
        cout << "住址：" << abs->personArray[ret].m_Address << endl;
    }
    else
    {
        cout << "查无此人。" << endl;
    }
    //任意键按下后清屏
    system("pause");
    system("cls");
}

// 5、修改指定联系人信息
void modifyPerson(struct AddressBooks *abs)
{
    cout << "请输入要修改的联系人姓名：" << endl;

    string name;
    cin >> name;

    int ret = isExist(abs, name);
    if (ret != -1)
    {
        /* 有这个人才能修改 */
        cout << "请输入要修改的姓名: " << endl;  //修改姓名
        string name;
        cin >> name;
        abs->personArray[ret].m_Name = name;

        cout << "请输入要修改的性别: " << endl;  //修改性别
        cout << "1---男 " << endl;
        cout << "2---女 " << endl;
        int sex;
        while (true)
        {
            /* 保证输入正确 */
            cin >> sex;
            if (sex ==1 || sex ==2)
            {
                /* 正确 */
                abs->personArray[ret].m_Sex = sex;
                break;
            }
            else
            {
                cout << "输入错误，重新输入" << endl;
            }
            
        }
        
        
        cout << "请输入要修改的年龄: " << endl;  //修改年龄
        int age;
        cin >> age;
        abs->personArray[ret].m_age = age;

        cout << "请输入要修改的Phone: " << endl;  //修改Phone
        int phone;
        cin >> phone;
        abs->personArray[ret].m_Phone = phone;  //修改之后显示内容与输入内容不匹配？

        cout << "请输入要修改的住址: " << endl;  //修改住址
        string address;
        cin >> address;
        abs->personArray[ret].m_Address = address;
    }
    else
    {
        cout << "查无此人5" << endl;
    }
    
    //任意键按下后清屏
    system("pause");
    system("cls");

    
}

// 6、清空联系人
void cleanPerson(struct AddressBooks *abs)
{
    abs->m_Size = 0 ; //将当前记录联系人数置为0，做逻辑清空。即不进入循环，找不到信息。其实在内存中存在
    cout << "通讯录已清空" << endl;
    system("pause");
    system("cls");
}


int main() {

    //创建通讯录结构体变量
    struct AddressBooks abs;
    //初始化通讯录当前人员个数
    abs.m_Size = 0; 

    int select = 0;  //创建用户选择输入的变量

    while (true)
    {
        /* 根据输入循环 */
        // 1、封装函数showMenu()
        showMenu();

        cin >> select;
    
        switch (select)  //根据用户输入选择分支
        {
        case 1:          //1、 添加联系人 
            addPerson(&abs);  //要利用地址传参
            break;
        case 2:          //2、 显示联系人
            showPerson(&abs);
            break;
        case 3:          //3、 删除联系人
        {    //在case语句中的大段代码需要用{}封装成一个代码段
            cout << "请输入删除联系人的姓名：" << endl;
            string name;
            cin >> name;

            if(isExist(&abs, name)==-1)
            {
                cout << "查无此人" << endl;
            }
            else
            {
                cout << "找到此人" << endl;
            }
            
        }
            deletePerson(&abs);
            break;
        case 4:          //4、 查找联系人
            findPerson(&abs);
            break;
        case 5:          //5、 修改联系人
            modifyPerson(&abs);
            break;
        case 6:          //6、 清空联系人
        {
            cout << "当前通讯录共有 " << abs.m_Size << "个联系人，是否要全部清空？" << endl;
            cout << "确认清空-----1" << endl;
            cout << "取消清空-----2" << endl;
            int clean ;
            cin >> clean;
            if (clean == 1)
            {
                /* 确认清空 */
                cleanPerson(&abs);
            }
            break;
        }
        case 0:          //0、 退出通信录
            cout << "欢迎下次使用" << endl;
            // system("pause");
            break;
            // return 0;
        default:
            break;
        }
        
    }
    
    
    // 2、退出功能
    return 0;
}