#include <iostream>
#include <vector>
#include <string>
#include<iomanip>

using namespace std;
#define Worriernum 5

string stdstring[Worriernum] = {"dragon", "ninja", "iceman", "lion", "wolf"};
string weapons[3] = {"sword", "bomb", "arrow"};

class bosshouse
{
private:
    int lifenum;
    int nowi = 0;
    vector<int> life;
    vector<int> count;
    vector<string> line;
    bool isbuild = true;
    int chrachtor;
    int time;
    int totalnum = 1;
    int minhealth = __INT_MAX__;

public:
    bosshouse(int i, int M, vector<int> &a)
    {
        time = 0;
        line.resize(Worriernum);
        count.resize(Worriernum);
        life.resize(Worriernum);

        if (i == 0) // 是红方
        {
            line[0] = "iceman";
            line[1] = "lion";
            line[2] = "wolf";
            line[3] = "ninja";
            line[4] = "dragon";
            chrachtor = 0;
        }
        else if (i == 1)
        {
            line[0] = "lion";
            line[1] = "dragon";
            line[2] = "ninja";
            line[3] = "iceman";
            line[4] = "wolf";
            chrachtor = 1;
        }
        lifenum = M;
        for (int i = 0; i < Worriernum; i++)
        {
            count[i] = 0;
        }

        for (int i = 0; i < Worriernum; i++)
        {
            for (int j = 0; j < Worriernum; j++)
            {
                if (line[i] == stdstring[j])
                {
                    life[i] = a[j];
                    minhealth = min(minhealth, life[i]);
                }
            }
        }
    }

    bool produce()
    {
        int i = nowi % 5;
        string role;
        if (chrachtor == 0)
        {
            role = "red";
        }
        else
        {
            role = "blue";
        }
        string realtimel;
        if (time / 10 == 0)
        {
            realtimel = "00" + to_string(time);
        }
        else if (time / 100 == 0)
        {
            realtimel = "0" + to_string(time);
        }
        else
        {
            realtimel = to_string(time);
        }

        if (isbuild)
        {
            if (lifenum >= life[i])
            {
                cout << realtimel << ' ' << role << ' ' << line[i] << ' ' << totalnum << " born with strength " << life[i] << "," << count[i] + 1 << ' ' << line[i] << " in " << role << " headquarter" << '\n';
                if(line[i] == "dragon")
                {
                    cout << "It has a " << weapons[totalnum % 3] <<",and it's morale is " << fixed<< setprecision(2)<<((lifenum - life[i]) * 1.0) / (life[i] * 1.0) << '\n';
                }
                if(line[i] == "ninja")
                {
                    cout <<"It has a " << weapons[totalnum % 3] << " and a " << weapons[(totalnum + 1) % 3] << '\n';
                }
                if(line[i] == "iceman")
                {
                    cout << "It has a " <<weapons[totalnum % 3] << '\n';
                }
                if(line[i] == "lion")
                {
                    cout << "It's loyalty is " << lifenum - life[i] << '\n';
                }

                count[i]++;
                totalnum++;
                lifenum -= life[i];
                nowi++;
                time++;
                

            }
            else
            {
                if (lifenum < minhealth)
                {
                    cout << realtimel << ' ' << role << " headquarter stops making warriors\n";
                    isbuild = false;
                }
                else
                {
                    while (lifenum < life[(++nowi) % Worriernum])
                    {
                    }
                    i = (nowi) % Worriernum;
                    cout << realtimel << ' ' << role << ' ' << line[i] << ' ' << totalnum << " born with strength " << life[i] << "," << count[i] + 1 << ' ' << line[i] << " in " << role << " headquarter" << '\n';
                    if(line[i] == "dragon")
                    {
                        cout << "It has a " << weapons[totalnum % 3] <<",and it's morale is " << fixed << setprecision(2)<< ((lifenum - life[i]) * 1.0) / (life[i] * 1.0) << '\n';
                    }
                    if(line[i] == "ninja")
                    {
                        cout <<"It has a " << weapons[totalnum % 3] << " and a " << weapons[(totalnum + 1) % 3] << '\n';
                    }
                    if(line[i] == "iceman")
                    {
                        cout << "It has a " <<weapons[totalnum % 3] << '\n';
                    }
                    if(line[i] == "lion")
                    {
                        cout << "It's loyalty is " << lifenum - life[i] << '\n';
                    }
                    count[i]++;
                    totalnum++;
                    lifenum -= life[i];
                    nowi++;
                    time++;
                }
            }
        }

        return isbuild;
    }
};

int main(void)
{
    int sum = 0;
    cin >> sum;
    int count = 1;

    while (count <= sum)
    {
        cout << "Case:" << count << '\n';
        count++;

        int m;
        vector<int> health(Worriernum, 0);

        cin >> m;

        for (int i = 0; i < Worriernum; i++)
        {
            cin >> health[i];
        }

        bosshouse red(0, m, health);
        bosshouse blue(1, m, health);

        while (1)
        {
            bool a = red.produce();
            bool b = blue.produce();
            if (!(a || b))
            {
                break;
            }
        }
    }
}