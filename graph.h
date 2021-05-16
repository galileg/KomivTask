#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>
#include<QPair>
#include<QString>
#include<string>
using namespace std;

vector<int>save;
int M = -5;
int LongofWay;
string str;
vector<vector<int>>matrix = {{0 ,12 ,18,5,0 ,34 },
                             {12 ,0 ,16 ,0 ,53 ,45 },
                             {18 ,16 ,0 ,3 ,21,0 },
                             {5 ,0 ,3 ,0 ,0 ,0 },
                             {0 ,53, 21,0,0 ,0 },
                             {34,45 ,0 ,0 ,0 ,0 }};

vector<vector<int>>m2 = matrix;

bool isFindEnd(vector<vector<int>>&m)
{
    for (int i = 0;i < m.size();i++)
    {
        for (int j = 0;j < m.size();j++)
        {
            if (m[i][j]>=0)
                return false;
        }
    }
    return true;
}

void GettingM(vector<vector<int>>&m)
{
    for (int i = 0;i < m.size();i++)
    {
        for (int j = 0;j < m.size();j++)
        {
            if (m[i][j] == 0)
            {
                m[i][j] = M;
            }
        }
    }
}

void RowReduction(vector<vector<int>>&m)
{
    for (int i = 0;i < m.size();i++)
    {
        int min = 10000;
        for (int j = 0;j < m.size();j++)
        {
            if (m[i][j] < min && m[i][j] >= 0)
            {
                min = m[i][j];
            }
        }
        for (int j = 0;j < m.size();j++)
        {
            m[i][j]-=min;
        }
    }
}

void ColReduction(vector<vector<int>>&m)
{
    for (int i = 0;i < m.size();i++)
    {
        int min = 10000;
        for (int j = 0;j < m.size();j++)
        {
            if (m[j][i] < min && m[j][i] >= 0)
            {
                min = m[j][i];
            }
        }
        for (int j = 0;j < m.size();j++)
        {
            m[j][i]-=min;
        }
    }
}



int MininR(int r, int c)
{
    int min = 10000;
    for (int i = 0;i < matrix.size();i++)
    {
        if (i != c && matrix[r][i]<min && matrix[r][i]>=0)
            min = matrix[r][i];
    }
    return min;
}

int MininC(int r, int c)
{
    int min = 10000;
    for (int i = 0;i < matrix.size();i++)
    {
        if (i != c && matrix[i][c]<min && matrix[i][c]>=0)
            min = matrix[i][c];
    }
    return min;
}

vector<vector<int>>Zeromatrix = matrix;

void SetMarks (vector<vector<int>>&m)
{
    for (int i = 0;i < m.size();i++)
    {
        for (int j = 0;j < m.size();j++)
        {
            Zeromatrix[i][j] = 0;
        }
    }

    for (int i = 0;i < m.size();i++)
    {
        for (int j = 0;j < m.size();j++)
        {
            if (m[i][j] == 0)
            {
                MininR(i,j);
                MininC(i,j);
                Zeromatrix[i][j] = MininR(i,j)+MininC(i,j);
            }
        }
    }
}

void InsertWay(int dep, int arr)
{
    if (save.size()==0)
    {
        save.push_back(dep);
        save.push_back(arr);
    }
    else
    {
        unsigned int ind = 0;
        while (ind < save.size() && save[ind] != dep) ind++;
        if (ind < save.size())
        {
            if (ind + 1 == save.size())
            {
                save.push_back(arr);
            }
            else if (ind+1==save.size() && save[ind+1]!=arr)
            {
                save.insert(save.begin() + ind + 1, arr);
            }
        }
        else
        {
            ind = 0;
            while (ind < save.size() && save[ind] != arr)ind++;
            if (ind < save.size())
            {
                save.insert(save.begin()+ind, dep);
            }
            else
            {
                save.push_back(dep);
                save.push_back(arr);
            }
        }
    }
}

void SearchMax(vector<vector<int>>&m)
{
    int Zmax = -1;
    int needi =-1;
    int needj= -1;

    for (int i = 0;i < m.size();i++)
    {
        for (int j = 0;j < m.size();j++)
        {
            if (Zeromatrix[i][j] > Zmax)
            {
                Zmax = Zeromatrix[i][j];
                needi = i;
                needj = j;
            }
        }
    }

    InsertWay(needi, needj);
    //save.push_back(pair<int,int>(needi,needj));


    for (int i = 0;i < m.size();i++)
    {
        for (int j = 0;j < m.size();j++)
        {
            if (i==needi || j == needj)
            {
                m[i][j] = M;
            }
        }
    }
    m[needj][needi]= M;
}


string Kommivoyajer()
{
    save = vector<int>();

    GettingM(matrix);

    while (!(isFindEnd(matrix)))
    {
        ColReduction(matrix);
        RowReduction(matrix);
        SetMarks(matrix);
        SearchMax(matrix);
    }
    //return save;

    for (int i=0; i<save.size();i++)
    {
        if (i == save.size()-1)
            str+=to_string(save[i]+1);
        else
            str+=to_string(save[i]+1)+" => ";

    }
    return str;

}
int WAY_LONG()
{
    for (int i=0; i<save.size()-1;i++)
    {
        LongofWay += (m2[save[i]][save[i+1]]);
    }
    return LongofWay;
}


#endif // GRAPH_H
