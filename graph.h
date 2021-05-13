#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>
using namespace std;

vector<int>save;
int M = -5;
vector<vector<int>>matrix = {{0 ,12 ,18,5,0 ,34 },
                             {12 ,0 ,16 ,0 ,53 ,45 },
                             {18 ,16 ,0 ,3 ,21,0 },
                             {5 ,0 ,3 ,0 ,0 ,0 },
                             {0 ,0,53 ,21,0 ,0 },
                             {34,45 ,0 ,0 ,0 ,0 } };

bool isFindEnd(vector<vector<int>>m)
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

void GettingM(vector<vector<int>>m)
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

void RowReduction(vector<vector<int>>m)
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

void ColReduction(vector<vector<int>>m)
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

vector<vector<int>>Zeromatrix = matrix;

void SetMarks (vector<vector<int>>m)
{
    for (int i = 0;i < m.size();i++)
    {
        for (int j = 0;j < m.size();j++)
        {
            Zeromatrix[i][j] = 0;
        }
    }

    int minR = 10000;
    int minC = 10000;
    for (int i = 0;i < m.size();i++)
    {
        for (int j = 0;j < m.size();j++)
        {
            if (m[i][j] == 0)
            {
                for (int needi = 0; needi < m.size();needi++ )
                {
                    if (m[needi][j] < minR &&  needi!=j)
                        minR = m[needi][j];
                }
                for (int needj = 0;needj < m.size();needj++ )
                {
                    if (m[needj][i] < minR &&  needj!=i)
                        minC = m[needj][i];
                }
                Zeromatrix[i][j] = minC+minR;
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

void SearchMax(vector<vector<int>>m)
{
    int Zmax = -1;
    int needi;
    int needj;
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
}


vector<int>Kommivoyajer()
{
    save = vector<int>();
    GettingM(matrix);
    while (isFindEnd(matrix))
    {
        ColReduction(matrix);
        RowReduction(matrix);
        SetMarks(matrix);
        SearchMax(matrix);
    }
    return save;
}


#endif // GRAPH_H
