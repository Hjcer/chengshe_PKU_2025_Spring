#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

string warrors[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int life[5] = {0, 0, 0, 0, 0};
int attack[5] = {0, 0, 0, 0, 0};
string weapons[3] = {"sword", "bomb", "arrow"};

// 定义 1 为红方, 0 为蓝方

int R; // 弓箭的攻击力

string redorder[5] = {"iceman", "lion", "wolf", "ninja", "dragon"};
string blueorder[5] = {"lion", "dragon", "ninja", "iceman", "wolf"};

class weapon
{
public:
    string name;
    int attack;
    int life;
    int formerAttack; // 记录原始攻击力
    weapon(string n, int a, int l) : name(n), attack(a), life(l) {}

    virtual int attackEnemy()
    {
        return attack;
    }

    virtual bool isusable() { return true; } // 是否可用
};

class sword : public weapon
{
public:
    sword(int attack) : weapon("sword", attack, 0) {}

    virtual int attackEnemy()
    {
        int formerAttack = attack;
        attack = attack * 0.8;
        return formerAttack;
    }

    virtual bool isusable()
    {
        return attack > 0;
    }
};

class arrow : public weapon
{
public:
    arrow() : weapon("arrow", R, 3) {}

    virtual int attackEnemy()
    {
        life--;
        return attack;
    }

    virtual bool isusable()
    {
        return life > 0;
    }
};

class bomb : public weapon
{
public:
    bomb() : weapon("bomb", 0, 0) {}

    virtual int attackEnemy()
    {
        return 0;
    }

    virtual bool isusable()
    {
        return true;
    }
};

class warrior
{
public:
    string name;
    int id;
    int life;
    int attack;
    int colorflag;                  // 1为红方, 0 为蓝方
    int weapon_count;               // 武器数量
    bool isAlive = true;            // 是否存活
    bool is_shoot_to_death = false; // 是否被射死
    vector<weapon *> weapons;       // 武器列表
    int loyalty;                    // 忠诚度
    warrior(string n, int id, int life, int attack, int colorflag) : name(n), id(id), life(life), attack(attack), colorflag(colorflag), weapon_count(0) {}

    virtual void stepDown() {}; // 步数增加

    virtual void getWeapon(warrior *enemy) {} // 获取武器
    virtual bool isLoyal() { return true; }   // 忠诚度
};

class dragon : public warrior
{
public:
    double morale; // 士气
    dragon(int id, int life, int attack, int colorflag, double morale) : warrior("dragon", id, life, attack, colorflag)
    {
        int weapon_num = (id) % 3;
        if (weapon_num == 0)
        {
            weapons.push_back(new sword(attack * 0.2));
        }
        else if (weapon_num == 2)
        {
            weapons.push_back(new arrow());
        }
        else
        {
            weapons.push_back(new bomb());
        }
        this->morale = morale;
        weapon_count = 1;
    }
};

class ninja : public warrior
{
public:
    ninja(int id, int life, int attack, int colorflag) : warrior("ninja", id, life, attack, colorflag)
    {
        int weapon_num1 = (id) % 3;
        int weapon_num2 = (id + 1) % 3;
        if (weapon_num1 == 0)
        {
            weapons.push_back(new sword(attack * 0.2));
        }
        else if (weapon_num1 == 2)
        {
            weapons.push_back(new arrow());
        }
        else
        {
            weapons.push_back(new bomb());
        }
        if (weapon_num2 == 0)
        {
            weapons.push_back(new sword(attack * 0.2));
        }
        else if (weapon_num2 == 2)
        {
            weapons.push_back(new arrow());
        }
        else
        {
            weapons.push_back(new bomb());
        }
        weapon_count = 2;
    }
};

class iceman : public warrior
{
public:
    int step = 0;
    iceman(int id, int life, int attack, int colorflag) : warrior("iceman", id, life, attack, colorflag)
    {
        int weapon_num = (id) % 3;
        if (weapon_num == 0)
        {
            weapons.push_back(new sword(attack * 0.2));
        }
        else if (weapon_num == 2)
        {
            weapons.push_back(new arrow());
        }
        else
        {
            weapons.push_back(new bomb());
        }
        weapon_count = 1;
    }
    // iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死。
    void stepDown()
    {
        if (step % 2 == 1)
        {
            life -= 9;
            if (life <= 0)
            {
                life = 1;
            }
            attack += 20;
        }
        step++;
    }
};

class lion : public warrior
{
public:
    lion(int id, int life, int attack, int colorflag, int loyalty) : warrior("lion", id, life, attack, colorflag)
    {
        this->loyalty = loyalty;
        weapon_count = 0;
    }

    // 每经过一场未能杀死敌人的战斗，忠诚度就降低K。忠诚度降至0或0以下，则该lion逃离战场,永远消失。但是已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑。
    bool isLoyal()
    {
        return loyalty > 0;
    }
};

class wolf : public warrior
{
public:
    wolf(int id, int life, int attack, int colorflag) : warrior("wolf", id, life, attack, colorflag)
    {
    }

    // wolf降生时没有武器，但是在战斗中如果获胜（杀死敌人），就会缴获敌人的武器，但自己已有的武器就不缴获了。被缴获的武器当然不能算新的，已经被用到什么样了，就是什么样的。
    void getWeapon(warrior *enemy)
    {
        for (int i = 0; i < enemy->weapon_count; i++)
        {
            // 检查自己是否拥有这件武器
            bool hasWeapon = false;
            for (int j = 0; j < weapon_count; j++)
            {
                if (weapons[j]->name == enemy->weapons[i]->name)
                {
                    hasWeapon = true;
                    break;
                }
            }
            // 如果没有这件武器，就缴获
            if (!hasWeapon)
            {
                weapons.push_back(enemy->weapons[i]);
                weapon_count++;
            }
        }
    }
};

class city
{
public:
    int id;
    int colorflag = -1;
    int last_win_color; // 上次获胜的颜色 1为红方, 0 为蓝方
    int last_win_time;
    int last_count; // 上次该方获胜的数量
    int life;       // 生命值
    bool is_bomb_test_kill = false;
    vector<warrior *> warriors = vector<warrior *>(2, nullptr);      // 武士列表
    vector<warrior *> temp_warriors = vector<warrior *>(2, nullptr); // 计划已转移到该城的武士列表
};

class headquarter : public city
{
public:
    string name;
    int colorflag;              // 1为红方, 0 为蓝方
    int life;                   // 生命值
    int warrior_count;          // 战士数量
    int warrior_id;             // 战士id
    int warrior_type;           // 战士类型
    vector<warrior *> warriors; // 武士列表

    headquarter(string n, int colorflag, int life) : name(n), colorflag(colorflag), life(life), warrior_count(0), warrior_id(0) {}
};

int main(void)
{
    // freopen("aba.txt", "w", stdout);
    int t;
    cin >> t;
    int op = 1;
    while (t--)
    {
        cout << "Case " << op++ << ":" << endl;

        int M, N, Ri, K, T;
        cin >> M >> N >> Ri >> K >> T;

        vector<city *> cities(N + 2, nullptr);

        headquarter *red = new headquarter("red", 1, M);
        headquarter *blue = new headquarter("blue", 0, M);

        cities[0] = new headquarter("red", 1, M);
        cities[N + 1] = new headquarter("blue", 0, M);

        bool is_finish = false;

        for (int i = 1; i <= N; i++)
        {
            cities[i] = new city();
            cities[i]->id = i;
            cities[i]->colorflag = -1;
            cities[i]->last_win_color = -1;
            cities[i]->last_count = 0;
            cities[i]->life = 0;
        }
        R = Ri;

        for (int i = 0; i < 5; i++)
        {
            cin >> life[i];
        }

        for (int i = 0; i < 5; i++)
        {
            cin >> attack[i];
        }

        int hour = T / 60;
        int minute = T % 60;

        for (int iour = 0; iour < hour + 1; iour++)
        {
            if (iour * 60 > T)
            {
                goto CON;
            }
            // 整点0分, 司令部降生武士
            int red_life_acc = 0;
            int blue_life_acc = 0;
            if (redorder[red->warrior_count % 5] == "dragon" && red->life >= life[0])
            {
                red->life -= life[0];
                dragon *r = new dragon(red->warrior_id + 1, life[0], attack[0], red->colorflag, red->life / (double)life[0]);
                red->warrior_id++;
                red->warrior_count++;
                cities[0]->warriors[1] = r;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " red dragon " << red->warrior_id << " born\n";
                cout << "Its morale is " << fixed << setprecision(2) << r->morale << endl;
            }
            else if (redorder[red->warrior_count % 5] == "ninja" && red->life >= life[1])
            {
                red->life -= life[1];
                ninja *r = new ninja(red->warrior_id + 1, life[1], attack[1], red->colorflag);
                red->warrior_id++;
                red->warrior_count++;
                cities[0]->warriors[1] = r;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " red ninja " << red->warrior_id << " born\n";
            }
            else if (redorder[red->warrior_count % 5] == "iceman" && red->life >= life[2])
            {
                red->life -= life[2];
                iceman *r = new iceman(red->warrior_id + 1, life[2], attack[2], red->colorflag);
                red->warrior_id++;
                red->warrior_count++;
                cities[0]->warriors[1] = r;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " red iceman " << red->warrior_id << " born\n";
            }
            else if (redorder[red->warrior_count % 5] == "lion" && red->life >= life[3])
            {
                red->life -= life[3];
                lion *r = new lion(red->warrior_id + 1, life[3], attack[3], red->colorflag, red->life);
                red->warrior_id++;
                red->warrior_count++;
                cities[0]->warriors[1] = r;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " red lion " << red->warrior_id << " born\n";
                cout << "Its loyalty is " << red->life << endl;
            }
            else if (redorder[red->warrior_count % 5] == "wolf" && red->life >= life[4])
            {
                red->life -= life[4];
                wolf *r = new wolf(red->warrior_id + 1, life[4], attack[4], red->colorflag);
                red->warrior_id++;
                red->warrior_count++;
                cities[0]->warriors[1] = r;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " red wolf " << red->warrior_id << " born\n";
            }

            // 整点0分, 蓝方司令部降生武士
            if (blueorder[blue->warrior_count % 5] == "dragon" && blue->life >= life[0])
            {
                blue->life -= life[0];
                dragon *b = new dragon(blue->warrior_id + 1, life[0], attack[0], blue->colorflag, blue->life / (double)life[0]);
                blue->warrior_id++;
                blue->warrior_count++;
                cities[N + 1]->warriors[0] = b;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " blue dragon " << blue->warrior_id << " born\n";
                cout << "Its morale is " << fixed << setprecision(2) << b->morale << endl;
            }
            else if (blueorder[blue->warrior_count % 5] == "ninja" && blue->life >= life[1])
            {
                blue->life -= life[1];
                ninja *b = new ninja(blue->warrior_id + 1, life[1], attack[1], blue->colorflag);
                blue->warrior_id++;
                blue->warrior_count++;
                cities[N + 1]->warriors[0] = b;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " blue ninja " << blue->warrior_id << " born\n";
            }
            else if (blueorder[blue->warrior_count % 5] == "iceman" && blue->life >= life[2])
            {
                blue->life -= life[2];
                iceman *b = new iceman(blue->warrior_id + 1, life[2], attack[2], blue->colorflag);
                blue->warrior_id++;
                blue->warrior_count++;
                cities[N + 1]->warriors[0] = b;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " blue iceman " << blue->warrior_id << " born\n";
            }
            else if (blueorder[blue->warrior_count % 5] == "lion" && blue->life >= life[3])
            {
                blue->life -= life[3];
                lion *b = new lion(blue->warrior_id + 1, life[3], attack[3], blue->colorflag, blue->life);
                blue->warrior_id++;
                blue->warrior_count++;
                cities[N + 1]->warriors[0] = b;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " blue lion " << blue->warrior_id << " born\n";
                cout << "Its loyalty is " << blue->life << endl;
            }
            else if (blueorder[blue->warrior_count % 5] == "wolf" && blue->life >= life[4])
            {
                blue->life -= life[4];
                wolf *b = new wolf(blue->warrior_id + 1, life[4], attack[4], blue->colorflag);
                blue->warrior_id++;
                blue->warrior_count++;
                cities[N + 1]->warriors[0] = b;
                cout << setw(3) << setfill('0') << iour << ":" << "00" << " blue wolf " << blue->warrior_id << " born\n";
            }

            if (iour * 60 + 5 > T)
            {
                goto CON;
            }

            // 整点5分, 让该逃跑的lion逃跑
            for (int j = 0; j < N + 2; j++)
            {
                if (cities[j]->warriors[1] != nullptr && cities[j]->warriors[1]->isAlive && cities[j]->warriors[1]->name == "lion")
                {
                    lion *l = (lion *)cities[j]->warriors[1];
                    if (!l->isLoyal())
                    {
                        cout << setw(3) << setfill('0') << iour << ":" << "05" << " red lion " << l->id << " ran away\n";
                        l->isAlive = false;
                        cities[j]->warriors[1] = nullptr;
                    }
                }
                if (cities[j]->warriors[0] != nullptr && cities[j]->warriors[0]->isAlive && cities[j]->warriors[0]->name == "lion")
                {
                    lion *l = (lion *)cities[j]->warriors[0];
                    if (!l->isLoyal())
                    {
                        cout << setw(3) << setfill('0') << iour << ":" << "05" << " blue lion " << l->id << " ran away\n";
                        l->isAlive = false;
                        cities[j]->warriors[0] = nullptr;
                    }
                }
            }

            if (iour * 60 + 10 > T)
            {
                goto CON;
            }

            // 整点10分, 让武士们前进!

            if (cities[1]->warriors[0] != nullptr && cities[1]->warriors[0]->isAlive) // 蓝方武士向红方前进
            {
                if (cities[1]->warriors[0]->name == "iceman")
                {
                    cities[1]->warriors[0]->stepDown();
                }
                red->warriors.push_back(cities[1]->warriors[0]);

                cout << setw(3) << setfill('0') << iour << ":" << "10" << " blue " << cities[1]->warriors[0]->name << " " << cities[1]->warriors[0]->id << " reached red headquarter with " << cities[1]->warriors[0]->life << " elements and force " << cities[1]->warriors[0]->attack << endl;

                // 判断司令部是否被两个敌方武士占领
                if (red->warriors.size() == 2 && red->warriors[0]->isAlive && red->warriors[1]->isAlive)
                {
                    cities[0]->colorflag = 0;
                    cities[0]->last_win_color = 0;
                    cities[0]->last_count++;
                    cout << setw(3) << setfill('0') << iour << ":" << "10" << " red headquarter was taken\n";
                    is_finish = true;
                }
            }

            for (int j = 1; j < N + 1; j++)
            {
                if (cities[j - 1]->warriors[1] != nullptr && cities[j - 1]->warriors[1]->isAlive)
                {
                    if (cities[j - 1]->warriors[1]->name == "iceman")
                    {
                        cities[j - 1]->warriors[1]->stepDown();
                    }
                    cities[j]->temp_warriors[1] = cities[j - 1]->warriors[1];

                    cout << setw(3) << setfill('0') << iour << ":" << "10" << " red " << cities[j]->temp_warriors[1]->name << " " << cities[j]->temp_warriors[1]->id << " marched to city " << j << " with " << cities[j]->temp_warriors[1]->life << " elements and force " << cities[j]->temp_warriors[1]->attack << endl;
                }

                if (cities[j + 1]->warriors[0] != nullptr && cities[j + 1]->warriors[0]->isAlive)
                {
                    if (cities[j + 1]->warriors[0]->name == "iceman")
                    {
                        cities[j + 1]->warriors[0]->stepDown();
                    }
                    cities[j]->temp_warriors[0] = cities[j + 1]->warriors[0];

                    cout << setw(3) << setfill('0') << iour << ":" << "10" << " blue " << cities[j]->temp_warriors[0]->name << " " << cities[j]->temp_warriors[0]->id << " marched to city " << j << " with " << cities[j]->temp_warriors[0]->life << " elements and force " << cities[j]->temp_warriors[0]->attack << endl;
                }
            }

            if (cities[N]->warriors[1] != nullptr && cities[N]->warriors[1]->isAlive) // 红方武士向蓝方前进
            {
                if (cities[N]->warriors[1]->name == "iceman")
                {
                    cities[N]->warriors[1]->stepDown();
                }
                blue->warriors.push_back(cities[N]->warriors[1]);

                cout << setw(3) << setfill('0') << iour << ":" << "10" << " red " << cities[N]->warriors[1]->name << " " << cities[N]->warriors[1]->id << " reached blue headquarter with " << cities[N]->warriors[1]->life << " elements and force " << cities[N]->warriors[1]->attack << endl;

                if (blue->warriors.size() == 2 && blue->warriors[0]->isAlive && blue->warriors[1]->isAlive)
                {
                    cities[N + 1]->colorflag = 1;
                    cities[N + 1]->last_win_color = 1;
                    cities[N + 1]->last_count++;
                    cout << setw(3) << setfill('0') << iour << ":" << "10" << " blue headquarter was taken\n";
                    is_finish = true;
                }
            }
            for (int i = 0; i < N + 2; i++)
            {
                cities[i]->warriors[0] = cities[i]->temp_warriors[0];
                cities[i]->warriors[1] = cities[i]->temp_warriors[1];

                cities[i]->temp_warriors[0] = nullptr;
                cities[i]->temp_warriors[1] = nullptr;
            }

            // 整点20分, 每座城市产出10点生命值
            for (int i = 1; i < N + 1; i++)
            {
                cities[i]->life += 10;
            }

            if (iour * 60 + 30 > T || is_finish)
            {
                goto CON;
            }

            // 在每个小时的第30分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，并立即将这些生命元传送到其所属的司令部。
            for (int j = 1; j < N + 1; j++)
            {
                if (cities[j]->warriors[0] != nullptr && ((cities[j]->warriors[1] == nullptr) || (cities[j]->warriors[1]->isAlive == false)) && cities[j]->warriors[0]->isAlive)
                {
                    blue->life += cities[j]->life;
                    cout << setw(3) << setfill('0') << iour << ":" << "30" << " blue " << cities[j]->warriors[0]->name << " " << cities[j]->warriors[0]->id << " earned " << cities[j]->life << " elements for his headquarter\n";
                    cities[j]->life = 0;
                }
                if (cities[j]->warriors[1] != nullptr && ((cities[j]->warriors[0] == nullptr) || (cities[j]->warriors[0]->isAlive == false)) && cities[j]->warriors[1]->isAlive)
                {
                    red->life += cities[j]->life;
                    cout << setw(3) << setfill('0') << iour << ":" << "30" << " red " << cities[j]->warriors[1]->name << " " << cities[j]->warriors[1]->id << " earned " << cities[j]->life << " elements for his headquarter\n";
                    cities[j]->life = 0;
                }
            }
            if (iour * 60 + 35 > T)
            {
                goto CON;
            }

            // 在每个小时的第35分，拥有arrow的武士放箭，对敌人造成伤害。放箭事件应算发生在箭发出的城市。注意，放箭不算是战斗，因此放箭的武士不会得到任何好处。武士在没有敌人的城市被箭射死也不影响其所在城市的旗帜更换情况
            // 输出样例： 000:35 blue dragon 1 shot
            // 表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭。如果射出的箭杀死了敌人，则应如下输出：
            // 000:35 blue dragon 1 shot and killed red lion 4
            // 表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭，杀死了编号为4的红魔lion。
            for (int i = 1; i < N + 1; i++)
            {
                // 再看看城市里有没有蓝色武士
                if (cities[i]->warriors[1] != nullptr && cities[i]->warriors[1]->isAlive && cities[i]->warriors[1]->weapons.size() > 0)
                {
                    for (int j = 0; j < cities[i]->warriors[1]->weapon_count; j++)
                    {
                        if (cities[i]->warriors[1]->weapons[j]->name == "arrow")
                        {
                            if (cities[i]->warriors[1]->weapons[j]->isusable())
                            {
                                if (cities[i + 1]->warriors[0] != nullptr && cities[i + 1]->warriors[0]->isAlive)
                                {
                                    int attack = cities[i]->warriors[1]->weapons[j]->attackEnemy();
                                    if (cities[i + 1]->warriors[0]->life > attack)
                                    {
                                        cities[i + 1]->warriors[0]->life -= attack;
                                        cout << setw(3) << setfill('0') << iour << ":" << "35" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " shot\n";
                                    }
                                    else
                                    {
                                        cout << setw(3) << setfill('0') << iour << ":" << "35" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " shot and killed blue " << cities[i + 1]->warriors[0]->name << " " << cities[i + 1]->warriors[0]->id << endl;
                                        cities[i + 1]->warriors[0]->is_shoot_to_death = true;
                                    }
                                }
                            }
                            else
                            {
                                cities[i]->warriors[1]->weapons.erase(cities[i]->warriors[1]->weapons.begin() + j);
                                cities[i]->warriors[1]->weapon_count--;
                                break;
                            }
                        }
                    }
                }
                // 先看看城市里有没有红色武士
                if (cities[i]->warriors[0] != nullptr && cities[i]->warriors[0]->isAlive && cities[i]->warriors[0]->weapons.size() > 0)
                {
                    for (int j = 0; j < cities[i]->warriors[0]->weapon_count; j++)
                    {
                        if (cities[i]->warriors[0]->weapons[j]->name == "arrow")
                        {
                            if (cities[i]->warriors[0]->weapons[j]->isusable())
                            {

                                if (cities[i - 1]->warriors[1] != nullptr && cities[i - 1]->warriors[1]->isAlive)
                                {
                                    int attack = cities[i]->warriors[0]->weapons[j]->attackEnemy();
                                    if (cities[i - 1]->warriors[1]->life > attack)
                                    {
                                        cities[i - 1]->warriors[1]->life -= attack;
                                        cout << setw(3) << setfill('0') << iour << ":" << "35" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " shot\n";
                                    }
                                    else
                                    {
                                        cout << setw(3) << setfill('0') << iour << ":" << "35" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " shot and killed red " << cities[i - 1]->warriors[1]->name << " " << cities[i - 1]->warriors[1]->id << endl;
                                        cities[i - 1]->warriors[1]->is_shoot_to_death = true;
                                    }
                                }
                            }
                            else
                            {
                                cities[i]->warriors[0]->weapons.erase(cities[i]->warriors[0]->weapons.begin() + j);
                                cities[i]->warriors[0]->weapon_count--;
                                break;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < N + 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (cities[i]->warriors[j] != nullptr && cities[i]->warriors[j]->isAlive && cities[i]->warriors[j]->is_shoot_to_death)
                    {
                        cities[i]->warriors[j]->isAlive = false;
                    }
                }
            }

            if (iour * 60 + 38 > T)
            {
                goto CON;
            }

            // 武士使用bomb
            for (int i = 1; i < N + 1; i++)
            {
                if (cities[i]->warriors[0] != nullptr && cities[i]->warriors[0]->isAlive && cities[i]->warriors[1] != nullptr && cities[i]->warriors[1]->isAlive)
                {
                    int who_attack_first;

                    int red_sword_attack = 0;
                    int blue_sword_attack = 0;

                    for (int j = 0; j < cities[i]->warriors[0]->weapon_count; j++)
                    {
                        if (cities[i]->warriors[0]->weapons[j]->name == "sword")
                        {
                            blue_sword_attack = cities[i]->warriors[0]->weapons[j]->attack;
                        }
                    }

                    for (int j = 0; j < cities[i]->warriors[1]->weapon_count; j++)
                    {
                        if (cities[i]->warriors[1]->weapons[j]->name == "sword")
                        {
                            red_sword_attack = cities[i]->warriors[1]->weapons[j]->attack;
                        }
                    }

                    int blue_attack = cities[i]->warriors[0]->attack + blue_sword_attack;
                    int red_attack = cities[i]->warriors[1]->attack + red_sword_attack;

                    if (cities[i]->colorflag == -1 && (i) % 2 == 0) // 蓝方先攻击
                    {
                        who_attack_first = 0;
                    }
                    else if (cities[i]->colorflag == -1 && (i) % 2 == 1) // 红方先攻击
                    {
                        who_attack_first = 1;
                    }
                    else if (cities[i]->colorflag == 1) // 红方先攻击
                    {
                        who_attack_first = 1;
                    }
                    else if (cities[i]->colorflag == 0) // 蓝方先攻击
                    {
                        who_attack_first = 0;
                    }

                    if (who_attack_first == 0) // 蓝方先攻击
                    {
                        // cities[i]->warriors[1]->life -= blue_attack;
                        if (cities[i]->warriors[1]->life <= blue_attack)
                        {
                            for (int j = 0; j < cities[i]->warriors[1]->weapon_count; j++)
                            {
                                if (cities[i]->warriors[1]->weapons[j]->name == "bomb")
                                {
                                    cout << setw(3) << setfill('0') << iour << ":" << "38" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " used a bomb and killed blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << endl;
                                    cities[i]->warriors[0] = nullptr;
                                    cities[i]->warriors[1] = nullptr;
                                    goto END;
                                }
                            }
                        }
                        else if (cities[i]->warriors[1]->name != "ninja")
                        {
                            red_attack = cities[i]->warriors[1]->attack / 2 + red_sword_attack;
                            // cities[i]->warriors[0]->life -= red_attack;
                            if (cities[i]->warriors[0]->life <= red_attack)
                            {
                                for (int j = 0; j < cities[i]->warriors[0]->weapon_count; j++)
                                {
                                    if (cities[i]->warriors[0]->weapons[j]->name == "bomb")
                                    {
                                        cout << setw(3) << setfill('0') << iour << ":" << "38" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " used a bomb and killed red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << endl;
                                        cities[i]->warriors[0] = nullptr;
                                        cities[i]->warriors[1] = nullptr;
                                        goto END;
                                    }
                                }
                            }
                        }
                    }
                    else if (who_attack_first == 1) // 红方先攻击
                    {
                        // cities[i]->warriors[0]->life -= red_attack;
                        if (cities[i]->warriors[0]->life <= red_attack)
                        {
                            for (int j = 0; j < cities[i]->warriors[0]->weapon_count; j++)
                            {
                                if (cities[i]->warriors[0]->weapons[j]->name == "bomb")
                                {
                                    cout << setw(3) << setfill('0') << iour << ":" << "38" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " used a bomb and killed red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << endl;
                                    cities[i]->warriors[0] = nullptr;
                                    cities[i]->warriors[1] = nullptr;
                                    goto END;
                                }
                            }
                        }
                        else if (cities[i]->warriors[0]->name != "ninja")
                        {
                            blue_attack = cities[i]->warriors[0]->attack / 2 + blue_sword_attack;
                            // cities[i]->warriors[1]->life -= blue_attack;
                            if (cities[i]->warriors[1]->life <= blue_attack)
                            {
                                for (int j = 0; j < cities[i]->warriors[1]->weapon_count; j++)
                                {
                                    if (cities[i]->warriors[1]->weapons[j]->name == "bomb")
                                    {
                                        cout << setw(3) << setfill('0') << iour << ":" << "38" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " used a bomb and killed blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << endl;
                                        cities[i]->warriors[0] = nullptr;
                                        cities[i]->warriors[1] = nullptr;
                                        goto END;
                                    }
                                }
                            }
                        }
                    }
                }
            END:
                continue;
            }

            if (iour * 60 + 40 > T)
            {
                goto CON;
            }

            // 整点40分, 让武士们战斗
            for (int i = 1; i < N + 1; i++)
            {
                // 考虑一座城市, 有一方的武士被射死, 另一方还存活着
                if (cities[i]->warriors[0] != nullptr && cities[i]->warriors[0]->is_shoot_to_death && cities[i]->warriors[1] != nullptr && cities[i]->warriors[1]->isAlive)
                {
                    int who_attack_first;
                    if (cities[i]->colorflag == -1 && (i) % 2 == 0) // 蓝方先攻击
                    {
                        who_attack_first = 0;
                    }
                    else if (cities[i]->colorflag == -1 && (i) % 2 == 1) // 红方先攻击
                    {
                        who_attack_first = 1;
                    }
                    else if (cities[i]->colorflag == 1) // 红方先攻击
                    {
                        who_attack_first = 1;
                    }
                    else if (cities[i]->colorflag == 0) // 蓝方先攻击
                    {
                        who_attack_first = 0;
                    }

                    if (who_attack_first == 1 && cities[i]->warriors[1]->name == "dragon")
                    {
                        dragon *d = (dragon *)cities[i]->warriors[1];
                        d->morale += 0.2;
                        if (d->morale > 0.8)
                        {
                            cout << setw(3) << setfill('0') << iour << ":40" << " red dragon " << cities[i]->warriors[1]->id << " yelled in city " << i << endl;
                        }
                    }

                    if (cities[i]->warriors[1]->name == "wolf")
                    {
                        wolf *w = (wolf *)cities[i]->warriors[1];
                        w->getWeapon(cities[i]->warriors[0]);
                    }
                    cout << setw(3) << setfill('0') << iour << ":40" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " earned " << cities[i]->life << " elements for his headquarter\n";
                    red_life_acc += cities[i]->life;
                    cities[i]->life = 0;

                    if (cities[i]->last_win_color == 1)
                    {
                        if (cities[i]->colorflag != 1)
                        {
                            cities[i]->colorflag = 1;
                            cout << setw(3) << setfill('0') << iour << ":40" << " red flag raised in city " << i << '\n';
                        }
                    }
                    cities[i]->last_win_color = 1;
                    cities[i]->last_win_time = iour;

                    goto OI;
                }
                else if (cities[i]->warriors[1] != nullptr && cities[i]->warriors[1]->is_shoot_to_death && cities[i]->warriors[0] != nullptr && cities[i]->warriors[0]->isAlive)
                {
                    int who_attack_first;
                    if (cities[i]->colorflag == -1 && (i) % 2 == 0) // 蓝方先攻击
                    {
                        who_attack_first = 0;
                    }
                    else if (cities[i]->colorflag == -1 && (i) % 2 == 1) // 红方先攻击
                    {
                        who_attack_first = 1;
                    }
                    else if (cities[i]->colorflag == 1) // 红方先攻击
                    {
                        who_attack_first = 1;
                    }
                    else if (cities[i]->colorflag == 0) // 蓝方先攻击
                    {
                        who_attack_first = 0;
                    }

                    if (who_attack_first == 0 && cities[i]->warriors[0]->name == "dragon")
                    {
                        dragon *d = (dragon *)cities[i]->warriors[0];
                        d->morale += 0.2;
                        if (d->morale > 0.8)
                        {
                            cout << setw(3) << setfill('0') << iour << ":40" << " blue dragon " << cities[i]->warriors[0]->id << " yelled in city " << i << endl;
                        }
                    }

                    if (cities[i]->warriors[0]->name == "wolf")
                    {
                        wolf *w = (wolf *)cities[i]->warriors[0];
                        w->getWeapon(cities[i]->warriors[1]);
                    }
                    cout << setw(3) << setfill('0') << iour << ":40" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " earned " << cities[i]->life << " elements for his headquarter\n";
                    blue_life_acc += cities[i]->life;
                    cities[i]->life = 0;

                    if (cities[i]->last_win_color == 0)
                    {
                        if (cities[i]->colorflag != 0)
                        {
                            cities[i]->colorflag = 0;
                            cout << setw(3) << setfill('0') << iour << ":40" << " blue flag raised in city " << i << '\n';
                        }
                    }
                    cities[i]->last_win_color = 0;
                    cities[i]->last_win_time = iour;

                    goto OI;
                }
                // 两个都被射死
                else if (cities[i]->warriors[0] != nullptr && cities[i]->warriors[0]->is_shoot_to_death && cities[i]->warriors[1] != nullptr && cities[i]->warriors[1]->is_shoot_to_death)
                {
                    // cout << "00" << iour << ":40" << "red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " and blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " died in city " << i << endl;
                    cities[i]->warriors[0] = nullptr;
                    cities[i]->warriors[1] = nullptr;
                    goto OI;
                }

                else if (cities[i]->warriors[0] != nullptr && cities[i]->warriors[0]->isAlive && cities[i]->warriors[1] != nullptr && cities[i]->warriors[1]->isAlive)
                {
                    int who_attack_first;

                    int red_sword_attack = 0;
                    int blue_sword_attack = 0;

                    int red_life = cities[i]->warriors[1]->life;
                    int blue_life = cities[i]->warriors[0]->life;

                    if (cities[i]->colorflag == -1 && (i) % 2 == 0) // 蓝方先攻击
                    {
                        who_attack_first = 0;
                    }
                    else if (cities[i]->colorflag == -1 && (i) % 2 == 1) // 红方先攻击
                    {
                        who_attack_first = 1;
                    }
                    else if (cities[i]->colorflag == 1) // 红方先攻击
                    {
                        who_attack_first = 1;
                    }
                    else if (cities[i]->colorflag == 0) // 蓝方先攻击
                    {
                        who_attack_first = 0;
                    }
                    for (int j = 0; j < cities[i]->warriors[0]->weapon_count; j++)
                    {
                        if (cities[i]->warriors[0]->weapons[j]->name == "sword")
                        {
                            if (cities[i]->warriors[0]->name == "ninja" && who_attack_first == 1)
                            {
                                break;
                            }
                            else
                            {
                                blue_sword_attack = cities[i]->warriors[0]->weapons[j]->attackEnemy();
                            }
                        }
                    }

                    for (int j = 0; j < cities[i]->warriors[1]->weapon_count; j++)
                    {
                        if (cities[i]->warriors[1]->weapons[j]->name == "sword")
                        {
                            if (cities[i]->warriors[1]->name == "ninja" && who_attack_first == 0)
                            {
                                break;
                            }
                            else
                            {
                                red_sword_attack = cities[i]->warriors[1]->weapons[j]->attackEnemy();
                            }
                        }
                    }

                    int blue_attack = cities[i]->warriors[0]->attack + blue_sword_attack;
                    int red_attack = cities[i]->warriors[1]->attack + red_sword_attack;

                    if (who_attack_first == 0) // 蓝方先攻击
                    {
                        // cities[i]->warriors[1]->life -= blue_attack;
                        cout << setw(3) << setfill('0') << iour << ":" << "40" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " attacked red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " in city " << i << " with " << cities[i]->warriors[0]->life << " elements and force " << cities[i]->warriors[0]->attack << endl;
                        if (cities[i]->warriors[1]->life <= blue_attack)
                        {
                            cout << setw(3) << setfill('0') << iour << ":" << "40" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " was killed in city " << i << endl;

                            for (int j = 0; j < cities[i]->warriors[1]->weapon_count; j++)
                            {
                                if (cities[i]->warriors[1]->weapons[j]->name == "sword" && cities[i]->warriors[1]->name != "ninja")
                                {
                                    cities[i]->warriors[1]->weapons[j]->attack = red_sword_attack;
                                }
                            }

                            if (cities[i]->warriors[0]->name == "dragon")
                            {
                                dragon *d = (dragon *)cities[i]->warriors[0];
                                d->morale += 0.2;
                                if (d->morale > 0.8)
                                {
                                    cout << setw(3) << setfill('0') << iour << ":40" << " blue dragon " << cities[i]->warriors[0]->id << " yelled in city " << i << endl;
                                }
                            }
                            if (cities[i]->warriors[1]->name == "lion")
                            {
                                cities[i]->warriors[0]->life += red_life;
                            }

                            if (cities[i]->warriors[0]->name == "wolf")
                            {
                                wolf *w = (wolf *)cities[i]->warriors[0];
                                w->getWeapon(cities[i]->warriors[1]);
                                // cout << w->weapons[0]->name << " " << w->weapons[0]->attack << endl;
                            }

                            cout << setw(3) << setfill('0') << iour << ":40" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " earned " << cities[i]->life << " elements for his headquarter\n";

                            blue_life_acc += cities[i]->life;
                            cities[i]->life = 0;
                            if (cities[i]->last_win_color == 0)
                            {
                                if (cities[i]->colorflag != 0)
                                {
                                    cities[i]->colorflag = 0;
                                    cout << setw(3) << setfill('0') << iour << ":40" << " blue flag raised in city " << i << '\n';
                                }
                            }
                            cities[i]->last_win_color = 0;
                            cities[i]->last_win_time = iour;
                            cities[i]->warriors[1]->isAlive = false;
                            cities[i]->warriors[1] = nullptr;

                            goto OI;
                        }
                        else if (cities[i]->warriors[1]->name != "ninja")
                        {
                            cities[i]->warriors[1]->life -= blue_attack;
                            red_attack = cities[i]->warriors[1]->attack / 2 + red_sword_attack;
                            // cities[i]->warriors[0]->life -= red_attack;
                            cout << setw(3) << setfill('0') << iour << ":" << "40" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " fought back against blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " in city " << i << endl;
                            if (cities[i]->warriors[0]->life <= red_attack)
                            {
                                cout << setw(3) << setfill('0') << iour << ":" << "40" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " was killed in city " << i << endl;

                                if (cities[i]->warriors[1]->name == "dragon")
                                {
                                    dragon *d = (dragon *)cities[i]->warriors[1];
                                    d->morale += 0.2;
                                }
                                if (cities[i]->warriors[0]->name == "lion")
                                {
                                    cities[i]->warriors[1]->life += blue_life;
                                }
                                if (cities[i]->warriors[1]->name == "wolf")
                                {
                                    wolf *w = (wolf *)cities[i]->warriors[1];
                                    w->getWeapon(cities[i]->warriors[0]);
                                }

                                cout << setw(3) << setfill('0') << iour << ":40" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " earned " << cities[i]->life << " elements for his headquarter\n";
                                red_life_acc += cities[i]->life;
                                cities[i]->life = 0;

                                if (cities[i]->last_win_color == 1)
                                {
                                    if (cities[i]->colorflag != 1)
                                    {
                                        cities[i]->colorflag = 1;
                                        cout << setw(3) << setfill('0') << iour << ":40" << " red flag raised in city " << i << '\n';
                                    }
                                }
                                cities[i]->last_win_color = 1;
                                cities[i]->last_win_time = iour;
                                cities[i]->warriors[0] = nullptr;
                                goto OI;
                            }
                            else
                            {
                                cities[i]->warriors[0]->life -= red_attack;
                            }
                            // cities[i]->last_win_color = -1;

                            if (cities[i]->warriors[0]->name == "lion")
                            {
                                cities[i]->warriors[0]->loyalty -= K;
                            }
                            if (cities[i]->warriors[1]->name == "lion")
                            {
                                cities[i]->warriors[1]->loyalty -= K;
                            }

                            cities[i]->last_win_color = -1;

                            if (cities[i]->warriors[1]->name == "dragon")
                            {
                                dragon *d = (dragon *)cities[i]->warriors[1];
                                d->morale -= 0.2;
                                if (who_attack_first == 1 && d->morale > 0.8)
                                {
                                    cout << setw(3) << setfill('0') << iour << ":40" << " red dragon " << cities[i]->warriors[1]->id << " yelled in city " << i << endl;
                                }
                            }
                            if (cities[i]->warriors[0]->name == "dragon")
                            {
                                dragon *d = (dragon *)cities[i]->warriors[0];
                                d->morale -= 0.2;
                                if (who_attack_first == 0 && d->morale > 0.8)
                                {
                                    cout << setw(3) << setfill('0') << iour << ":40" << " blue dragon " << cities[i]->warriors[0]->id << " yelled in city " << i << endl;
                                }
                            }
                        }
                        else if (cities[i]->warriors[1]->name == "ninja")
                        {
                            cities[i]->warriors[1]->life -= blue_attack;

                            cities[i]->last_win_color = -1;
                            if (cities[i]->warriors[0]->name == "lion")
                            {
                                cities[i]->warriors[0]->loyalty -= K;
                            }

                            if (cities[i]->warriors[0]->name == "dragon")
                            {
                                dragon *d = (dragon *)cities[i]->warriors[0];
                                d->morale -= 0.2;
                                if (d->morale > 0.8)
                                {
                                    cout << setw(3) << setfill('0') << iour << ":40" << " blue dragon " << cities[i]->warriors[0]->id << " yelled in city " << i << endl;
                                }
                            }
                        }
                    }
                    else // 红方先攻击
                    {
                        // cities[i]->warriors[0]->life -= red_attack;
                        cout << setw(3) << setfill('0') << iour << ":" << "40" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " attacked blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " in city " << i << " with " << cities[i]->warriors[1]->life << " elements and force " << cities[i]->warriors[1]->attack << endl;
                        if (cities[i]->warriors[0]->life <= red_attack)
                        {
                            cout << setw(3) << setfill('0') << iour << ":" << "40 " << "blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " was killed in city " << i << endl;

                            for (int j = 0; j < cities[i]->warriors[0]->weapon_count; j++)
                            {
                                if (cities[i]->warriors[0]->weapons[j]->name == "sword" && cities[i]->warriors[0]->name != "ninja")
                                {
                                    cities[i]->warriors[0]->weapons[j]->attack = blue_sword_attack;
                                }
                            }
                            if (cities[i]->warriors[1]->name == "dragon")
                            {
                                dragon *d = (dragon *)cities[i]->warriors[1];
                                d->morale += 0.2;
                                if (d->morale > 0.8)
                                {
                                    cout << setw(3) << setfill('0') << iour << ":40 " << "red dragon " << cities[i]->warriors[1]->id << " yelled in city " << i << endl;
                                }
                            }
                            if (cities[i]->warriors[0]->name == "lion")
                            {
                                cities[i]->warriors[1]->life += blue_life;
                            }

                            if (cities[i]->warriors[1]->name == "wolf")
                            {
                                wolf *w = (wolf *)cities[i]->warriors[1];
                                w->getWeapon(cities[i]->warriors[0]);
                            }

                            cout << setw(3) << setfill('0') << iour << ":40 " << "red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " earned " << cities[i]->life << " elements for his headquarter\n";
                            red_life_acc += cities[i]->life;
                            cities[i]->life = 0;
                            if (cities[i]->last_win_color == 1)
                            {
                                if (cities[i]->colorflag != 1)
                                {
                                    cities[i]->colorflag = 1;
                                    cout << setw(3) << setfill('0') << iour << ":40 " << "red flag raised in city " << i << '\n';
                                }
                            }
                            cities[i]->last_win_color = 1;
                            cities[i]->last_win_time = iour;
                            cities[i]->warriors[0] = nullptr;

                            goto OI;
                        }
                        else if (cities[i]->warriors[0] != nullptr && cities[i]->warriors[0] != nullptr && cities[i]->warriors[1] != nullptr && cities[i]->warriors[1] != nullptr && cities[i]->warriors[0]->name != "ninja")
                        {
                            cities[i]->warriors[0]->life -= red_attack;
                            blue_attack = cities[i]->warriors[0]->attack / 2 + blue_sword_attack;

                            // cities[i]->warriors[1]->life -= blue_attack;
                            cout << setw(3) << setfill('0') << iour << ":" << "40" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " fought back against red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " in city " << i << endl;
                            if (cities[i]->warriors[1]->life <= blue_attack)
                            {
                                cout << setw(3) << setfill('0') << iour << ":" << "40" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " was killed in city " << i << endl;

                                if (cities[i]->warriors[0]->name == "dragon")
                                {
                                    dragon *d = (dragon *)cities[i]->warriors[0];
                                    d->morale += 0.2;
                                }
                                if (cities[i]->warriors[1]->name == "lion")
                                {
                                    cities[i]->warriors[0]->life += red_life;
                                }
                                if (cities[i]->warriors[0]->name == "wolf")
                                {
                                    wolf *w = (wolf *)cities[i]->warriors[0];
                                    w->getWeapon(cities[i]->warriors[1]);
                                }
                                cout << setw(3) << setfill('0') << iour << ":40" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " earned " << cities[i]->life << " elements for his headquarter\n";
                                blue_life_acc += cities[i]->life;
                                cities[i]->life = 0;

                                if (cities[i]->last_win_color == 0)
                                {
                                    if (cities[i]->colorflag != 0)
                                    {
                                        cities[i]->colorflag = 0;
                                        cout << setw(3) << setfill('0') << iour << ":40" << " blue flag raised in city " << i << '\n';
                                    }
                                }
                                cities[i]->last_win_color = 0;
                                cities[i]->last_win_time = iour;
                                cities[i]->warriors[1] = nullptr;

                                goto OI;
                            }
                            else
                            {
                                cities[i]->warriors[1]->life -= blue_attack;
                            }

                            if (cities[i]->warriors[1]->name == "lion")
                            {
                                cities[i]->warriors[1]->loyalty -= K;
                            }
                            if (cities[i]->warriors[0]->name == "lion")
                            {
                                cities[i]->warriors[0]->loyalty -= K;
                                // cout << setw(3) << setfill('0') << iour << ":" << "40" << " blue lion " << cities[i]->warriors[0]->id << "has " << cities[i]->warriors[0]->loyalty << " loyalty\n";
                            }

                            cities[i]->last_win_color = -1;

                            if (cities[i]->warriors[1]->name == "dragon")
                            {
                                dragon *d = (dragon *)cities[i]->warriors[1];
                                d->morale -= 0.2;
                                // cout << "red dragon " << cities[i]->warriors[1]->id << " morale: " << d->morale << endl;
                                if (who_attack_first == 1 && d->morale > 0.8)
                                {
                                    cout << setw(3) << setfill('0') << iour << ":40" << " red dragon " << cities[i]->warriors[1]->id << " yelled in city " << i << endl;
                                }
                            }
                            if (cities[i]->warriors[0]->name == "dragon")
                            {
                                dragon *d = (dragon *)cities[i]->warriors[0];
                                d->morale -= 0.2;
                                if (who_attack_first == 0 && d->morale > 0.8)
                                {
                                    cout << setw(3) << setfill('0') << iour << ":40" << " blue dragon " << cities[i]->warriors[0]->id << " yelled in city " << i << endl;
                                }
                            }
                        }
                        else if (cities[i]->warriors[0]->name == "ninja")
                        {
                            cities[i]->warriors[0]->life -= red_attack;

                            cities[i]->last_win_color = -1;
                            if (cities[i]->warriors[1]->name == "lion")
                            {
                                cities[i]->warriors[1]->loyalty -= K;
                            }

                            if (cities[i]->warriors[1]->name == "dragon")
                            {
                                dragon *d = (dragon *)cities[i]->warriors[1];
                                d->morale -= 0.2;
                                // cout << "red dragon " << cities[i]->warriors[1]->id << " morale: " << d->morale << endl;
                                if (who_attack_first == 1 && d->morale > 0.8)
                                {
                                    cout << setw(3) << setfill('0') << iour << ":40" << " red dragon " << cities[i]->warriors[1]->id << " yelled in city " << i << endl;
                                }
                            }
                        }
                    }
                }
            OI:
                continue;
            }

            // 开始MVP发放阶段
            // 如果武士在战斗中杀死敌人（不论是主动进攻杀死还是反击杀死），则其司令部会立即向其发送8个生命元作为奖励，使其生命值增加8。当然前提是司令部得有8个生命元。如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。

            // 先对蓝色奖励
            for (int i = 1; i < N + 1; i++)
            {
                if (cities[i]->warriors[0] != nullptr && cities[i]->warriors[0]->isAlive)
                {
                    if (cities[i]->last_win_color == 0 && cities[i]->last_win_time == iour)
                    {
                        if (blue->life >= 8)
                        {
                            blue->life -= 8;
                            cities[i]->warriors[0]->life += 8;
                        }
                    }
                }
            }

            // 然后对红色奖励
            for (int i = N; i >= 1; i--)
            {
                if (cities[i]->warriors[1] != nullptr && cities[i]->warriors[1]->isAlive)
                {
                    if (cities[i]->last_win_color == 1 && cities[i]->last_win_time == iour)
                    {
                        if (red->life >= 8)
                        {
                            red->life -= 8;
                            cities[i]->warriors[1]->life += 8;
                        }
                    }
                }
            }

            red->life += red_life_acc;
            blue->life += blue_life_acc;
            if (iour * 60 + 50 > T)
            {
                goto CON;
            }

            // 在每个小时的第50分，司令部报告它拥有的生命元数量。
            cout << setw(3) << setfill('0') << iour << ":" << "50 " << red->life << " elements in red headquarter\n";
            cout << setw(3) << setfill('0') << iour << ":" << "50 " << blue->life << " elements in blue headquarter\n";

            // 在每个小时的第55分，每个武士报告其拥有的武器情况。
            /*
            000:55 blue wolf 2 has arrow(2),bomb,sword(23)
            000:55 blue wolf 4 has no weapon
            000:55 blue wolf 5 has sword(20)
            表示在0点55分，蓝魔2号武士wolf有一支arrow（这支arrow还可以用2次），一个bomb，还有一支攻击力为23的sword。
            蓝魔4号武士wolf没武器。
            蓝魔5号武士wolf有一支攻击力为20的sword。
            交代武器情况时，次序依次是：arrow,bomb,sword。如果没有某种武器，某种武器就不用提。报告时，先按从西向东的顺序所有的红武士报告，然后再从西向东所有的蓝武士报告。

            */

            if (iour * 60 + 55 > T)
            {
                goto CON;
            }

            for (int i = 1; i < N + 1; i++)
            {
                if (cities[i]->warriors[1] != nullptr && cities[i]->warriors[1]->isAlive)
                {
                    cout << setw(3) << setfill('0') << iour << ":" << "55" << " red " << cities[i]->warriors[1]->name << " " << cities[i]->warriors[1]->id << " has ";
                    if (cities[i]->warriors[1]->weapons.size() == 0)
                    {
                        cout << "no weapon\n";
                    }
                    else
                    {
                        // 先排序
                        for (int j = 0; j < cities[i]->warriors[1]->weapon_count; j++)
                        {
                            for (int k = j + 1; k < cities[i]->warriors[1]->weapon_count; k++)
                            {
                                if (cities[i]->warriors[1]->weapons[j]->name > cities[i]->warriors[1]->weapons[k]->name)
                                {
                                    swap(cities[i]->warriors[1]->weapons[j], cities[i]->warriors[1]->weapons[k]);
                                }
                            }
                        }

                        // 再清理无用武器
                        for (int j = 0; j < cities[i]->warriors[1]->weapon_count; j++)
                        {
                            if (cities[i]->warriors[1]->weapons[j]->name == "arrow" && cities[i]->warriors[1]->weapons[j]->life == 0)
                            {
                                cities[i]->warriors[1]->weapons.erase(cities[i]->warriors[1]->weapons.begin() + j);
                                cities[i]->warriors[1]->weapon_count--;
                                j--;
                                continue;
                            }

                            if (cities[i]->warriors[1]->weapons[j]->name == "sword" && cities[i]->warriors[1]->weapons[j]->attack == 0)
                            {
                                cities[i]->warriors[1]->weapons.erase(cities[i]->warriors[1]->weapons.begin() + j);
                                cities[i]->warriors[1]->weapon_count--;
                                j--;
                                continue;
                            }
                        }

                        for (int j = 0; j < cities[i]->warriors[1]->weapon_count; j++)
                        {
                            if (cities[i]->warriors[1]->weapons[j]->name == "arrow")
                            {
                                cout << "arrow(" << cities[i]->warriors[1]->weapons[j]->life << ")";
                            }
                            else if (cities[i]->warriors[1]->weapons[j]->name == "bomb")
                            {
                                cout << "bomb";
                            }
                            else if (cities[i]->warriors[1]->weapons[j]->name == "sword")
                            {
                                cout << "sword(" << cities[i]->warriors[1]->weapons[j]->attack << ")";
                            }
                            if (j != cities[i]->warriors[1]->weapon_count - 1)
                            {
                                cout << ",";
                            }
                        }

                        if (cities[i]->warriors[1]->weapon_count == 0)
                        {
                            cout << "no weapon\n";
                        }
                        else
                        {
                            cout << '\n';
                        }
                    }
                }
            }

            for (int j = 0; j < blue->warriors.size(); j++)
            {
                if (blue->warriors[j] != nullptr && blue->warriors[j]->isAlive)
                {
                    cout << setw(3) << setfill('0') << iour << ":" << "55" << " red " << blue->warriors[j]->name << " " << blue->warriors[j]->id << " has ";
                    if (blue->warriors[j]->weapons.size() == 0)
                    {
                        cout << "no weapon\n";
                    }
                    else
                    {
                        // 先排序
                        for (int k = 0; k < blue->warriors[j]->weapon_count; k++)
                        {
                            for (int l = k + 1; l < blue->warriors[j]->weapon_count; l++)
                            {
                                if (blue->warriors[j]->weapons[k]->name > blue->warriors[j]->weapons[l]->name)
                                {
                                    swap(blue->warriors[j]->weapons[k], blue->warriors[j]->weapons[l]);
                                }
                            }
                        }

                        // 再清理无用武器
                        for (int k = 0; k < blue->warriors[j]->weapon_count; k++)
                        {
                            if (blue->warriors[j]->weapons[k]->name == "arrow" && blue->warriors[j]->weapons[k]->life == 0)
                            {
                                blue->warriors[j]->weapons.erase(blue->warriors[j]->weapons.begin() + k);
                                blue->warriors[j]->weapon_count--;
                                k--;
                                continue;
                            }

                            if (blue->warriors[j]->weapons[k]->name == "sword" && blue->warriors[j]->weapons[k]->attack == 0)
                            {
                                blue->warriors[j]->weapons.erase(blue->warriors[j]->weapons.begin() + k);
                                blue->warriors[j]->weapon_count--;
                                k--;
                                continue;
                            }
                        }

                        for (int k = 0; k < blue->warriors[j]->weapon_count; k++)
                        {
                            if (blue->warriors[j]->weapons[k]->name == "arrow")
                            {
                                cout << "arrow(" << blue->warriors[j]->weapons[k]->life << ")";
                            }
                            else if (blue->warriors[j]->weapons[k]->name == "bomb")
                            {
                                cout << "bomb";
                            }
                            else if (blue->warriors[j]->weapons[k]->name == "sword")
                            {
                                cout << "sword(" << blue->warriors[j]->weapons[k]->attack << ")";
                            }
                            if (k != blue->warriors[j]->weapon_count - 1)
                            {
                                cout << ",";
                            }
                        }
                        if (blue->warriors[j]->weapon_count == 0)
                        {
                            cout << "no weapon\n";
                        }
                        else
                        {
                            cout << '\n';
                        }
                    }
                }
            }

            for (int j = 0; j < red->warriors.size(); j++)
            {
                if (red->warriors[j] != nullptr && red->warriors[j]->isAlive)
                {
                    cout << setw(3) << setfill('0') << iour << ":" << "55" << " blue " << red->warriors[j]->name << " " << red->warriors[j]->id << " has ";
                    if (red->warriors[j]->weapons.size() == 0)
                    {
                        cout << "no weapon\n";
                    }
                    else
                    {
                        // 先排序
                        for (int k = 0; k < red->warriors[j]->weapon_count; k++)
                        {
                            for (int l = k + 1; l < red->warriors[j]->weapon_count; l++)
                            {
                                if (red->warriors[j]->weapons[k]->name > red->warriors[j]->weapons[l]->name)
                                {
                                    swap(red->warriors[j]->weapons[k], red->warriors[j]->weapons[l]);
                                }
                            }
                        }

                        // 再清理无用武器

                        for (int k = 0; k < red->warriors[j]->weapon_count; k++)
                        {
                            if (red->warriors[j]->weapons[k]->name == "arrow" && red->warriors[j]->weapons[k]->life == 0)
                            {
                                red->warriors[j]->weapons.erase(red->warriors[j]->weapons.begin() + k);
                                red->warriors[j]->weapon_count--;
                                k--;
                                continue;
                            }

                            if (red->warriors[j]->weapons[k]->name == "sword" && red->warriors[j]->weapons[k]->attack == 0)
                            {
                                red->warriors[j]->weapons.erase(red->warriors[j]->weapons.begin() + k);
                                red->warriors[j]->weapon_count--;
                                k--;
                                continue;
                            }
                        }

                        for (int k = 0; k < red->warriors[j]->weapon_count; k++)
                        {
                            if (red->warriors[j]->weapons[k]->name == "arrow")
                            {
                                cout << "arrow(" << red->warriors[j]->weapons[k]->life << ")";
                            }
                            else if (red->warriors[j]->weapons[k]->name == "bomb")
                            {
                                cout << "bomb";
                            }
                            else if (red->warriors[j]->weapons[k]->name == "sword")
                            {
                                cout << "sword(" << red->warriors[j]->weapons[k]->attack << ")";
                            }
                            if (k != red->warriors[j]->weapon_count - 1)
                            {
                                cout << ",";
                            }
                        }

                        if (red->warriors[j]->weapon_count == 0)
                        {
                            cout << "no weapon\n";
                        }
                        else
                        {
                            cout << '\n';
                        }
                    }
                }
            }

            for (int i = 1; i < N + 1; i++)
            {
                if (cities[i]->warriors[0] != nullptr && cities[i]->warriors[0]->isAlive)
                {
                    cout << setw(3) << setfill('0') << iour << ":" << "55" << " blue " << cities[i]->warriors[0]->name << " " << cities[i]->warriors[0]->id << " has ";
                    if (cities[i]->warriors[0]->weapons.size() == 0)
                    {
                        cout << "no weapon\n";
                    }
                    else
                    {
                        // 先排序
                        for (int j = 0; j < cities[i]->warriors[0]->weapon_count; j++)
                        {
                            for (int k = j + 1; k < cities[i]->warriors[0]->weapon_count; k++)
                            {
                                if (cities[i]->warriors[0]->weapons[j]->name > cities[i]->warriors[0]->weapons[k]->name)
                                {
                                    swap(cities[i]->warriors[0]->weapons[j], cities[i]->warriors[0]->weapons[k]);
                                }
                            }
                        }

                        // 再清理无用武器
                        for (int j = 0; j < cities[i]->warriors[0]->weapon_count; j++)
                        {
                            if (cities[i]->warriors[0]->weapons[j]->name == "arrow" && cities[i]->warriors[0]->weapons[j]->life == 0)
                            {
                                cities[i]->warriors[0]->weapons.erase(cities[i]->warriors[0]->weapons.begin() + j);
                                cities[i]->warriors[0]->weapon_count--;
                                j--;
                                continue;
                            }

                            if (cities[i]->warriors[0]->weapons[j]->name == "sword" && cities[i]->warriors[0]->weapons[j]->attack == 0)
                            {
                                cities[i]->warriors[0]->weapons.erase(cities[i]->warriors[0]->weapons.begin() + j);
                                cities[i]->warriors[0]->weapon_count--;
                                j--;
                                continue;
                            }
                        }

                        for (int j = 0; j < cities[i]->warriors[0]->weapon_count; j++)
                        {
                            if (cities[i]->warriors[0]->weapons[j]->name == "arrow")
                            {
                                cout << "arrow(" << cities[i]->warriors[0]->weapons[j]->life << ")";
                            }
                            else if (cities[i]->warriors[0]->weapons[j]->name == "bomb")
                            {
                                cout << "bomb";
                            }
                            else if (cities[i]->warriors[0]->weapons[j]->name == "sword")
                            {
                                cout << "sword(" << cities[i]->warriors[0]->weapons[j]->attack << ")";
                            }
                            if (j != cities[i]->warriors[0]->weapon_count - 1)
                            {
                                cout << ",";
                            }
                        }

                        if (cities[i]->warriors[0]->weapon_count == 0)
                        {
                            cout << "no weapon\n";
                        }
                        else
                        {
                            cout << '\n';
                        }
                    }
                }
            }
        }
        if (false)
        {
        CON:
            continue;
        }
    }
}