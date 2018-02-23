#include <iostream>
#include <random>
#include <map>
#include <fstream>
#include <regex>
#include <sstream>
#include<string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

const int size = 20;
//auto *temp1 = new int[size];



//============================================================================================
//配置majority vote，读取其中数据 flatten随机电路
void get_Majority_vote(vector<string> cellnumber ,int i)
{
    ifstream openfile;
    //文件路径需要更改,提取文件的路径
    openfile.open("C:\\Users\\ZhuHe\\Desktop\\majority.txt");

    string s;

    regex reg_input1("\\(a\\)");
    regex reg_input2("\\(b\\)");
    regex reg_input3("\\(c\\)");
    regex reg_input4("\\(d\\)");
    regex reg_input5("\\(z\\)");

    while (getline(openfile, s))
    {

        s = regex_replace(s, reg_input1, "(O"+cellnumber[0]+")");
        s = regex_replace(s, reg_input2, "(O"+cellnumber[1]+")");
        s = regex_replace(s, reg_input3, "(O"+cellnumber[2]+")");
        s = regex_replace(s, reg_input4, "(O"+cellnumber[3]+")");
        s = regex_replace(s, reg_input5, "("+cellnumber[4]+")");

        //文件路径需要更改，输出文件路径
        ostringstream Convert;
        Convert<<"random_circuit_"<<i<<".txt";
        string filename="C:\\Users\\ZhuHe\\Desktop\\test\\" +Convert.str();
        ofstream out_circuit(filename.c_str(),ios::app);

        out_circuit << s << endl;

    }



}


//============================================================================================
//下三角矩阵层序遍历
class Cell_Interface
{
public:
    vector<int> input;
    int output;

    Cell_Interface() {}

    void add_input(int input)
    {
        this->input.push_back(input);
    }

    void add_output(int output)
    {
        this->output = output;
    }
};

// 找到矩阵中的 "1"，并把所有符合要求的数放进vector的cell中， cell中保存着input的元件编号。 再把cell放入vector的cells中， 让每个元件都记录连接信息
vector<string> Cell_inout(vector<vector<int>> &adjM, vector<string> CellTypeName,int i)
{
    vector<string> cellnumber;
    cellnumber.resize(10);

    vector<Cell_Interface> cells;
    int j = 0;

    //输出文件

    ostringstream Convert;
    Convert<<"random_circuit_"<<i<<".txt";
    string filename="C:\\Users\\ZhuHe\\Desktop\\test\\" +Convert.str();
    ofstream out_circuit(filename.c_str(),ios::app);


//    Cell_Interface cell;


    for (int i = 0; i < adjM.size(); ++i)
    {
        Cell_Interface cell;

        // get input & output
        for (int j = 0; j < adjM.size(); ++j)
        {
            if (adjM[j][i] == 1)
            {
                cell.add_input(j);              //input的数字，可提取

            }
            if (adjM[i][j] == 1)
            {
                cell.add_output(i);             //cell.add_output(i)
            }

        }

        if (cell.input.size() == 4)
        {
            for (int i = 0; i < cell.input.size(); i++)
            {
                cellnumber[i] = to_string(cell.input[i]);
//                cout << "arr[i]:" << cellnumber[i] << endl;               //把这个arr[i]返回出来
            }

            cellnumber[4]="O"+to_string(cell.output);
        }

        cells.push_back(cell);
    }

    char cell_name = 'a';

    //============================================================================================
    //output to console
    for (int k = 0; k < adjM.size(); ++k)
    {

        //当输入时4个的时候，不显示verilog代码，直接接上下面从majority vote中提取的东西
//        if (cells[k].input.size()==4)
//        {
//            continue;
//        }

        //需要更改文件路径


//        else
        if(k==adjM.size()-1)
        {
            cout << "  and2 ";
            cout << "g0" << k << "(.a(a), .b(b), .O("<<cells[k].output<<"))"<<endl;
        }
        else
        {
            cout << "  "<<CellTypeName[k];
            cout << "g0" << k << "(";

            for (int m = 0; m < cells[k].input.size(); ++m)
            {
                //打印输入的名字a, b, c, d 等。 打印链接的节点

                cout << "." << char(cell_name + m) << "(O" << cells[k].input[m] << ")" << ", ";
            }


            if (k == 0)
            {
                cout << ".O(g))" << endl;
                //如果第一个元件为4输入，则它的output为0.   我们想想把它转换为g
                if (cells[0].input.size()==4)
                {
                    cellnumber[4]= "g";      //cell.output
                }

            }
            else
            {
                cout << ".O(O" << cells[k].output << "))" << endl;
            }
        }

    }

    //============================================================================================
    //output to file
    for (int k = 0; k < adjM.size(); ++k)
    {

        //当输入时4个的时候，不显示verilog代码，直接接上下面从majority vote中提取的东西
//        if (cells[k].input.size()==4)
//        {
//            continue;
//        }

        //需要更改文件路径


//        else
        if(k==adjM.size()-1)
        {
            out_circuit << "  and2 ";
            out_circuit << "g0" << k << "(.a(a), .b(b), .O("<<cells[k].output<<"))"<<endl;
        }
        else
        {
            out_circuit << "  "<<CellTypeName[k];
            out_circuit << "g0" << k << "(";

            for (int m = 0; m < cells[k].input.size(); ++m)
            {
                //打印输入的名字a, b, c, d 等。 打印链接的节点

                out_circuit << "." << char(cell_name + m) << "(O" << cells[k].input[m] << ")" << ", ";
            }


            if (k == 0)
            {
                out_circuit << ".O(g))" << endl;
                //如果第一个元件为4输入，则它的output为0.   我们想想把它转换为g
                if (cells[0].input.size()==4)
                {
                    cellnumber[4]= "g";      //cell.output
                }

            }
            else
            {
                out_circuit << ".O(O" << cells[k].output << "))" << endl;
            }
        }

    }
    //============================================================================================
    return cellnumber;

}


//============================================================================================
//生成符合要求矩阵

vector<int> choose_cell(vector<int> CellTypeNum, vector<vector<int>> &adjM)
{

    vector<int> temp1;
    temp1.resize(10);

    int m = 0;
    for (int k = 0; k < size - 1; ++k)
    {

        m++;

        lab3:
        for (int col = 0; col < size; ++col)
        {
            adjM[col][k] = 0;
        }

        for (int i = 0; i < CellTypeNum[k]; ++i)         //保证与选出的input数量相等
        {
            lab2:
            temp1[i] = (rand() % (size - m)) + m;    //保证挑选的数处于下三角矩阵
            for (int j = 0; j < i; ++j)
            {
                if (temp1[i] == temp1[j])
                {
                    goto lab2;
                }
            }
            cout << temp1[i] << ", ";
            adjM[temp1[i]][k] = 1;
        }

        //如果第一行第一个是0 ， 则不需要每行都有 "1"

        int flag = 0;

        for (int l = 0; l <= k; ++l)
        {
            if (adjM[k + 1][l] == 1)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            goto lab3;
        }
        lab4:
        cout << endl;

    }

    return temp1;
}

//============================================================================================
//随机选出每个元件的input个数
vector<int> random_number()
{
//    auto *temp = new int[size];
    vector<int> temp2;
    temp2.resize(size);

//    srand(time(NULL));
    int n = size - 1;       //input 个数  选的个数  2,3,4 ...
    int m;       //  (m,n)范围     a < m

    lab2:
    cout << "";

    for (int i = 0; i < n; ++i)
    {
        lab:
        temp2[i] = (rand() % 4) + 1;    //1~3之间的数

        //保证选的input数都是1，2，4 ； 不允许出现3
        if(temp2[i]==3)
        {
            goto lab;
        }

        for (int j = 0; j < i; ++j)
        {
            if (temp2[j] == 4 && temp2[i] == 4)
            {
                goto lab;
            }
            if (temp2[i] > size - 1 - i)
            {
                goto lab;
            }
        }
    }

    //保证输入中有4， 如果没有则重新开始
    int flag;
    for (int k = 0; k < n; ++k)
    {
        if(temp2[k]==4)
        {
            flag=1;
            break;
        }
    }
    if(flag!=1)
    {
        goto lab2;
    }


    return temp2;
}


//============================================================================================
//打印数组并对应元件名称
vector<string> displayArr(vector<int> arr, int n)
{
    map<int, string> Cell_type;
//    string *cell_type = new string[size - 1];
    vector<string> cell_type;
    cell_type.resize(size - 1);

    for (int i = 0; i < n - 1; ++i)
    {
        cout << arr[i] << ", ";

        //给每个原件定义类型
        if (arr[i] == 1)
        {
            Cell_type[arr[i]] = "inv1 ";
        }

        if (arr[i] == 2)
        {
            Cell_type[arr[i]] = "and2 ";
        }

        if (arr[i] == 3)
        {
            Cell_type[arr[i]] = "nand3 ";
        }

        if (arr[i] == 4)
        {
            Cell_type[arr[i]] = "majority vote ";
        }


        cell_type[i] = Cell_type[arr[i]];
//        cout << cell_type[i];
    }

    return cell_type;
}

//======================================================================================================================
//原main函数

void Final_function(int l)
{

//    ostringstream Convert;
//    Convert<<"random_circuit.txt"<<endl;
//    string filename = Convert.str();
//
//    ofstream logFile ("C:\\Users\\ZhuHe\\Desktop\\random_circuit233333.txt");
//    streambuf *outbuf = cout.rdbuf(logFile.rdbuf());


    //定义数组
    vector<vector<int>> adjMatrix;
    adjMatrix.resize(size);
    int i, j;
    for (int k = 0; k < size; k++)
    {
        // bug
        adjMatrix[k].resize(size + 1);
    }

    //随机返回每个原件的input个数并打印
    cout << "number of input: " << endl;
//    int *CellTypeNum;
    auto CellTypeNum = random_number();
//    displayArr(CellTypeNum, size);

    //返回数组，表明每个元件的类型
//    string *CellTypeName;
    auto CellTypeName = displayArr(CellTypeNum, size);

    cout << endl << "==============================================================" << endl;

    cout << "what are the inputs："<<endl;
    choose_cell(CellTypeNum, adjMatrix);

    cout << endl << "==============================================================" << endl;

    //输出随机电路的verilog形式
    cout << "random circuit generate verilog code"<<endl;
//    Cell_inout(adjMatrix, CellTypeName);

    //返回数组，数组中存放有4个输入的元件中，哪4个输入

//    auto cellnumber = Cell_inout(adjMatrix, CellTypeName);

        auto cellnumber = Cell_inout(adjMatrix, CellTypeName,l);



    cout << endl << "==============================================================" << endl;
    cout << "majority vote"<<endl;

    if (cellnumber[0]==to_string(0))
    {

    } else
    {
        get_Majority_vote(cellnumber,l);
    }



//    cout.rdbuf(outbuf);
}

//======================================================================================================================
//主函数

int main()
{
    srand(time(NULL));
    for (int l = 0; l <10 ; ++l)
    {
        Final_function(l);
    }


    return 0;
}