#include<iostream>
#include<vector>
#include<deque>

using namespace std;

int main(void)
{
    int K;
    cin >> K;
    while (K--)
    {
        int m, T;
        cin >> m >> T;
        vector<vector<char>>field(m, vector<char>(m, '0'));
        vector<vector<bool>>is_visi(m, vector<bool>(m, true));
        vector<vector<int>>distace(m, vector<int>(m, 0));
        int nowi, nowj;

        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < m; j++)
            {
                cin >> field[i][j];
                if(field[i][j] == '#')
                {
                    is_visi[i][j] = false;
                }

                if(field[i][j] == 'S')
                {
                    nowi = i;
                    nowj = j;
                }
            }
        }

        deque<int>iii;
        deque<int>jjj;

        deque<int>newi;
        deque<int>newj;

        iii.push_back(nowi);
        jjj.push_back(nowj);
        //is_visi[nowi][nowj] = false;

        int cnt = 0;
        while (!iii.empty())
        {
            nowi = iii.front();
            iii.pop_front();
            nowj = jjj.front();
            jjj.pop_front();
            if(is_visi[nowi][nowj])
            {
                if(nowi + 1 < m && is_visi[nowi + 1][nowj])
                {
                    iii.push_back(nowi + 1);
                    jjj.push_back(nowj);
                    distace[nowi + 1][nowj] = distace[nowi][nowj] + 1;
                    if(field[nowi + 1][nowj] == 'E')
                    {
                        cnt = distace[nowi + 1][nowj];
                        break;
                    }
                }
                if(nowi - 1 >= 0 && is_visi[nowi - 1][nowj])
                {
                    iii.push_back(nowi - 1);
                    jjj.push_back(nowj);
                    distace[nowi - 1][nowj] = distace[nowi][nowj] + 1;
                    if(field[nowi - 1][nowj] == 'E')
                    {
                        cnt = distace[nowi - 1][nowj];
                        break;
                    }
                }
                if(nowj + 1 < m && is_visi[nowi][nowj + 1])
                {
                    iii.push_back(nowi);
                    jjj.push_back(nowj + 1);
                    distace[nowi][nowj + 1] = distace[nowi][nowj] + 1;
                    if(field[nowi][nowj + 1] == 'E')
                    {
                        cnt = distace[nowi][nowj + 1];
                        break;
                    }
                }
                if(nowj - 1 >= 0 && is_visi[nowi][nowj - 1])
                {
                    iii.push_back(nowi);
                    jjj.push_back(nowj - 1);
                    distace[nowi][nowj - 1] = distace[nowi][nowj] + 1;
                    if(field[nowi][nowj - 1] == 'E')
                    {
                        cnt = distace[nowi][nowj - 1];
                        break;
                    }
                }
                is_visi[nowi][nowj] = false;  
            }
        }

        if(cnt == 0)
        {
            cout << "NO"<< '\n';
        }
        else
        {
            if(cnt <= T)
            {
                cout << "YES" <<'\n';
            }
            else
            {
                cout << "NO" << '\n';
            }
        }
        

        
        




    }
    

}