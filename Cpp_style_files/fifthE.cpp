#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

int winside = 2; // 0 is red, 1 is blue, 2 is no one

string weapons[3] = {"sword", "bomb", "arrow"};

string creature[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int life_of_creatures[5] = {0, 0, 0, 0, 0};
int power_of_creature[5] = {0, 0, 0, 0, 0};
int city_num;

class object;

class weaponss
{
public:
    int power;
    int usetime;
    int num;
    string name;
    virtual void get_attack_power(object &p) = 0;
};

class object
{
public:
    int loyalty;
    int loyalty_decrease;

    void modify_weapon()
    // 战斗开始前，双方先对自己的武器排好使用顺序，然后再一件一件地按顺序使用。编号小的武器，排在前面。
    // 若有多支arrow，用过的排在前面。排好序后，攻击者按此排序依次对敌人一件一件地使用武器。
    // 如果一种武器有多件，那就都要用上。每使用一件武器，被攻击者生命值要减去武器攻击力。
    // 用完的武器不再使用（即可以从武器序列中删除）。
    {
        useweapon_num = 0;
        // 删除用过的武器
        for (int i = 0; i < num_of_weapons; i++)
        {
            if (have_weapons[i]->usetime == 0)
            {
                for (int j = i; j < num_of_weapons - 1; j++)
                {
                    have_weapons[j] = have_weapons[j + 1];
                }
                num_of_weapons--;
            }
        }
        // 排序
        for (int i = 0; i < num_of_weapons; i++)
        {
            for (int j = i + 1; j < num_of_weapons; j++)
            {
                if (have_weapons[i]->num > have_weapons[j]->num)
                {
                    weaponss *temp = have_weapons[i];
                    have_weapons[i] = have_weapons[j];
                    have_weapons[j] = temp;
                }
                else if (have_weapons[i]->num == have_weapons[j]->num)
                {
                    if (have_weapons[i]->usetime > have_weapons[j]->usetime)
                    {
                        weaponss *temp = have_weapons[i];
                        have_weapons[i] = have_weapons[j];
                        have_weapons[j] = temp;
                    }
                }
            }
        }
    }

    string name;
    int life;
    int weapon;
    int position;
    int num;
    int type;
    bool side; // 0 is red , 1 is blue;
    int useweapon_num;

    static int dragon_num;
    static int ninjia_num;
    static int iceman_num;
    static int lion_num;
    static int wolf_num;

    virtual void cheer()
    {
        return;
    }

    virtual bool is_scape()
    {
        return false;
    }

    virtual void rob_weapons(object *pobject, int time)
    {
        return;
    }

    bool isdead()
    {
        if (life <= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // 战斗的胜方获得对方手里的武器。武士手里武器总数不超过10件。缴获武器时，按照武器种类编号从小到大缴获。如果有多件arrow，优先缴获没用过的。
    void obtain_weapons_from_dead_ennemy(object *pobject)
    {
        // 把已死去敌人武器数组清空用完的武器
        for (int i = 0; i < pobject->num_of_weapons; i++)
        {
            if (pobject->have_weapons[i]->usetime == 0)
            {
                for (int j = i; j < pobject->num_of_weapons - 1; j++)
                {
                    pobject->have_weapons[j] = pobject->have_weapons[j + 1];
                }
                pobject->num_of_weapons--;
            }
        }

        // 排序
        for (int i = 0; i < pobject->num_of_weapons; i++)
        {
            for (int j = i + 1; j < pobject->num_of_weapons; j++)
            {
                if (pobject->have_weapons[i]->num > pobject->have_weapons[j]->num)
                {
                    weaponss *temp = pobject->have_weapons[i];
                    pobject->have_weapons[i] = pobject->have_weapons[j];
                    pobject->have_weapons[j] = temp;
                }
                else if (pobject->have_weapons[i]->num == pobject->have_weapons[j]->num)
                {
                    if (pobject->have_weapons[i]->usetime > pobject->have_weapons[j]->usetime)
                    {
                        weaponss *temp = pobject->have_weapons[i];
                        pobject->have_weapons[i] = pobject->have_weapons[j];
                        pobject->have_weapons[j] = temp;
                    }
                }
            }
        }
        // 缴获武器
        int robbed_num = 0;
        for (int i = 0; i < 10 - num_of_weapons; i++)
        {
            if (i < pobject->num_of_weapons)
            {
                have_weapons[num_of_weapons + i] = pobject->have_weapons[i];
                robbed_num++;
            }
            else
            {
                break;
            }
        }
        num_of_weapons += robbed_num;
    }

    weaponss *have_weapons[10];
    int num_of_weapons;

    object(int num1, bool side1, int loyalty1 = 0, int loyaltydecrease1 = 0) : num(num1), side(side1), loyalty(loyalty1), loyalty_decrease(loyaltydecrease1)
    {
        if (side == 0)
        {
            position = 0;
        }
        else
        {
            position = city_num + 1;
        }
        for (int i = 0; i < 10; i++)
        {
            have_weapons[i] = NULL;
        }
        useweapon_num = 0;
    };

    /*
    双方轮流使用武器，甲用过一件，就轮到乙用。某一方把自己所有的武器都用过一轮后，就从头开始再用一轮。如果某一方没有武器了，那就挨打直到死去或敌人武器用完。武器排序只在战斗前进行，战斗中不会重新排序。
     如果双方武器都用完且都还活着，则战斗以平局结束。如果双方都死了，也算平局。
    有可能由于武士自身攻击力太低，而导致武器攻击力为0。攻击力为0的武器也要使用。如果战斗中双方的生命值和武器的状态都不再发生变化，则战斗结束，算平局。
    战斗的胜方获得对方手里的武器。武士手里武器总数不超过10件。缴获武器时，按照武器种类编号从小到大缴获。如果有多件arrow，优先缴获没用过的。
    如果战斗开始前双方都没有武器，则战斗视为平局。如果先攻击方没有武器，则由后攻击方攻击
    */

    virtual void attack(object *pobject)
    {
        this->modify_weapon();
        pobject->modify_weapon();
        int first_attacker_weapon = 0;
        int second_attacker_weapon = 0;

        int first_attacker_weapon_num = num_of_weapons;
        int second_attacker_weapon_num = pobject->num_of_weapons;

        int first_attacker_useout_weapon[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int second_attacker_useout_weapon[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        int first_attacker_useout_weapon_num = 0;
        int second_attacker_useout_weapon_num = 0;

        int ticktick = 0;

        while (1)
        {
            ticktick++;
            if (ticktick > 1000)
            {
                goto NOWEAPON;
            }
            // 主动者没武器了
            if (num_of_weapons == 0)
            {
                if (pobject->num_of_weapons == 0)
                {

                NOWEAPON:
                    string redname;
                    string bluename;
                    int rednum;
                    int bluenum;

                    if (side == 0)
                    {
                        redname = name;
                        rednum = num;
                        bluename = pobject->name;
                        bluenum = pobject->num;
                    }
                    else
                    {
                        redname = pobject->name;
                        rednum = pobject->num;
                        bluename = name;
                        bluenum = num;
                    }

                    // 武器处理
                    for (int i = 0; i < first_attacker_useout_weapon_num; i++)
                    {
                        have_weapons[first_attacker_useout_weapon[i]] = NULL;
                        for (int j = first_attacker_useout_weapon[i]; j < num_of_weapons; j++)
                        {
                            have_weapons[j] = have_weapons[j + 1];
                        }
                    }
                    for (int i = 0; i < second_attacker_useout_weapon_num; i++)
                    {
                        pobject->have_weapons[second_attacker_useout_weapon[i]] = NULL;
                        for (int j = second_attacker_useout_weapon[i]; j < pobject->num_of_weapons; j++)
                        {
                            pobject->have_weapons[j] = pobject->have_weapons[j + 1];
                        }
                    }

                    cout << ":40" << " both red " << redname << " " << rednum << " and blue " << bluename << " " << bluenum << " were alive in city " << position << endl;
                    return;
                }
                else
                {
                    // 被动者有武器，且继续发动攻击
                    if (pobject->have_weapons[second_attacker_weapon] == NULL || pobject->have_weapons[second_attacker_weapon]->usetime == 0)
                    {
                        while (1)
                        {
                            second_attacker_weapon++;
                            if (second_attacker_weapon == second_attacker_weapon_num + 1)
                            {
                                second_attacker_weapon = 0;
                            }
                            if (pobject->have_weapons[second_attacker_weapon] != NULL && pobject->have_weapons[second_attacker_weapon]->usetime != 0)
                            {
                                break;
                            }
                        }
                    }
                    pobject->have_weapons[second_attacker_weapon]->get_attack_power(*pobject);
                    life -= pobject->have_weapons[second_attacker_weapon]->power;
                    if (pobject->have_weapons[second_attacker_weapon]->usetime == 0)
                    {
                        second_attacker_useout_weapon[second_attacker_useout_weapon_num] = second_attacker_weapon;
                        second_attacker_useout_weapon_num++;
                    }

                    second_attacker_weapon++;
                }
            }
            else // 主动者有武器
            {
                if (pobject->num_of_weapons == 0)
                {
                    // 被动者没武器，主动者继续攻击
                    if (have_weapons[first_attacker_weapon] == NULL || have_weapons[first_attacker_weapon]->usetime == 0)
                    {
                        while (1)
                        {
                            first_attacker_weapon++;
                            if (first_attacker_weapon == first_attacker_weapon_num + 1)
                            {
                                first_attacker_weapon = 0;
                            }
                            if (have_weapons[first_attacker_weapon] != NULL && have_weapons[first_attacker_weapon]->usetime != 0)
                            {
                                break;
                            }
                        }
                    }
                    have_weapons[first_attacker_weapon]->get_attack_power(*this);
                    pobject->life -= have_weapons[first_attacker_weapon]->power;
                    if (have_weapons[first_attacker_weapon]->usetime == 0)
                    {
                        first_attacker_useout_weapon[first_attacker_useout_weapon_num] = first_attacker_weapon;
                        first_attacker_useout_weapon_num++;
                    }
                    first_attacker_weapon++;
                }
                else
                {
                    // 双方都有武器
                    if (have_weapons[first_attacker_weapon] == NULL || have_weapons[first_attacker_weapon]->usetime == 0)
                    {
                        while (1)
                        {
                            first_attacker_weapon++;
                            if (first_attacker_weapon == first_attacker_weapon_num + 1)
                            {
                                first_attacker_weapon = 0;
                            }
                            if (have_weapons[first_attacker_weapon]->usetime != 0)
                            {
                                break;
                            }
                        }
                    }

                    if (pobject->have_weapons[second_attacker_weapon] == NULL || pobject->have_weapons[second_attacker_weapon]->usetime == 0)
                    {
                        while (1)
                        {
                            second_attacker_weapon++;
                            if (second_attacker_weapon == second_attacker_weapon_num + 1)
                            {
                                second_attacker_weapon = 0;
                            }
                            if (pobject->have_weapons[second_attacker_weapon]->usetime != 0)
                            {
                                break;
                            }
                        }
                    }

                    have_weapons[first_attacker_weapon]->get_attack_power(*this);
                    pobject->life -= have_weapons[first_attacker_weapon]->power;
                    if (have_weapons[first_attacker_weapon]->usetime == 0)
                    {
                        first_attacker_useout_weapon[first_attacker_useout_weapon_num] = first_attacker_weapon;
                        first_attacker_useout_weapon_num++;
                    }
                    first_attacker_weapon++;

                    // 考虑一种情况，炸弹把自己炸死了
                    if (life <= 0)
                    {
                        goto END;
                    }

                    if (pobject->life > 0)
                    {
                        pobject->have_weapons[second_attacker_weapon]->get_attack_power(*pobject);
                        life -= pobject->have_weapons[second_attacker_weapon]->power;
                        if (pobject->have_weapons[second_attacker_weapon]->usetime == 0)
                        {
                            second_attacker_useout_weapon[second_attacker_useout_weapon_num] = second_attacker_weapon;
                            second_attacker_useout_weapon_num++;
                        }
                        second_attacker_weapon++;
                        if (life <= 0)
                        {
                            goto END;
                        }
                    }
                    else
                    {
                        goto END;
                    }
                }
            }

        END:
            // 输赢判断
            if (life <= 0 && pobject->life <= 0)
            {
                string redname;
                string bluename;
                int rednum;
                int bluenum;

                if (side == 0)
                {
                    redname = name;
                    rednum = num;
                    bluename = pobject->name;
                    bluenum = pobject->num;
                }
                else
                {
                    redname = pobject->name;
                    rednum = pobject->num;
                    bluename = name;
                    bluenum = num;
                }

                cout << ":40" << " both red " << redname << " " << rednum << " and blue " << bluename << " " << bluenum << " died in city " << position << endl;
                return;
            }
            else if (life <= 0)
            {

                for (int i = 0; i < second_attacker_useout_weapon_num; i++)
                {
                    pobject->have_weapons[second_attacker_useout_weapon[i]] = NULL;
                    for (int j = second_attacker_useout_weapon[i]; j < pobject->num_of_weapons; j++)
                    {
                        pobject->have_weapons[j] = pobject->have_weapons[j + 1];
                    }
                }
                cout << ":40 " << (pobject->side ? "blue" : "red") << ' ' << pobject->name << " " << pobject->num << " killed " << (side ? "blue" : "red") << ' ' << name << " " << num << " in city " << position << " remaining " << pobject->life << " elements" << endl;
                pobject->obtain_weapons_from_dead_ennemy(this);
                return;
            }
            else if (pobject->life <= 0)
            {
                // 武器结算
                for (int i = 0; i < first_attacker_useout_weapon_num; i++)
                {
                    have_weapons[first_attacker_useout_weapon[i]] = NULL;
                    for (int j = first_attacker_useout_weapon[i]; j < num_of_weapons; j++)
                    {
                        have_weapons[j] = have_weapons[j + 1];
                    }
                }

                cout << ":40 " << (side ? "blue" : "red") << ' ' << name << " " << num << " killed " << (pobject->side ? "blue" : "red") << ' ' << pobject->name << " " << pobject->num << " in city " << position << " remaining " << life << " elements" << endl;
                obtain_weapons_from_dead_ennemy(pobject);
                return;
            }
        }
    }
    virtual void move(int time)
    {

        if (side == 0)
        {
            if (position == city_num)
            {
                return;
            }
            else
            {
                position++;
                cout << setw(3) << setfill('0') << time;
                cout << ":10 red " << name << " " << num << " marched to city " << position << " with " << life << " elements and force " << power_of_creature[type] << endl;
            }
        }
        else
        {
            if (position == 1)
            {
                return;
            }
            else
            {
                position--;
                cout << setw(3) << setfill('0') << time;
                cout << ":10 blue " << name << " " << num << " marched to city " << position << " with " << life << " elements and force " << power_of_creature[type] << endl;
            }
        }
    }
};

int object ::dragon_num = 0;
int object ::ninjia_num = 0;
int object ::iceman_num = 0;
int object ::lion_num = 0;
int object ::wolf_num = 0;

class sword : public weaponss
{
public:
    bool is_zero_power = false;
    sword()
    {
        name = "sword";
        usetime = 1;
        num = 0;
    }
    void get_attack_power(object &p) // 其实就相当于攻击，因为每次攻击就会调用攻击力计算函数
    {
        power = power_of_creature[p.type] * 2 / 10;
        if (power == 0)
        {
            is_zero_power = true;
        }
    }
};

class bomb : public weaponss
{
public:
    bomb()
    {
        name = "bomb";
        usetime = 1;
        num = 1;
    }

    void get_attack_power(object &p)
    {
        power = power_of_creature[p.type] * 4 / 10;
        usetime--;
        if (p.name != "ninja")
        {
            p.life -= power_of_creature[p.type] * 2 / 10;
        }
        if (usetime <= 0)
        {
            p.num_of_weapons--;
        }
    }
};

class arrow : public weaponss
{
public:
    arrow()
    {
        name = "arrow";
        usetime = 2;
        num = 2;
    }

    void get_attack_power(object &p)
    {
        power = power_of_creature[p.type] * 3 / 10;
        usetime--;
        if (usetime <= 0)
        {
            p.num_of_weapons--;
        }
    }
};

class dragon : public object
{
public:
    dragon(int num1, bool side1) : object(num1, side1)
    {
        name = "dragon";
        type = 0;
        num_of_weapons = 1;
        int weapon_num = num % 3;
        life = life_of_creatures[type];
        if (side1 == 0)
        {
            position = 0;
        }
        else
        {
            position = city_num + 1;
        }

        weaponss *a;

        switch (weapon_num)
        {
        case 0:
            a = new sword();
            have_weapons[0] = a;
            break;
        case 1:
            a = new bomb();
            have_weapons[0] = a;
            break;
        case 2:
            a = new arrow();
            have_weapons[0] = a;
            break;
        default:
            break;
        }
    };

    void cheer()
    {
        if (side == 0)
        {
            cout << ":40 red dragon " << num << " yelled in city " << position << endl;
        }
        else if (side == 1)
        {
            cout << ":40 blue dragon " << num << " yelled in city " << position << endl;
        }
    }
};

class ninjia : public object
{
public:
    ninjia(int num1, bool side1) : object(num1, side1)
    {
        name = "ninja";
        type = 1;
        num_of_weapons = 2;
        life = life_of_creatures[type];

        int weapon_num = num % 3;

        weaponss *a;

        switch (weapon_num)
        {
        case 0:
            a = new sword();
            have_weapons[0] = a;
            break;
        case 1:
            a = new bomb();
            have_weapons[0] = a;
            break;
        case 2:
            a = new arrow();
            have_weapons[0] = a;
            break;
        default:
            break;
        }

        weaponss *b;
        weapon_num = (num + 1) % 3;
        switch (weapon_num)
        {
        case 0:
            b = new sword();
            have_weapons[1] = b;
            break;
        case 1:
            b = new bomb();
            have_weapons[1] = b;
            break;
        case 2:
            b = new arrow();
            have_weapons[1] = b;
            break;
        default:
            break;
        }
    }
};

class iceman : public object
{
public:
    iceman(int num1, bool side1) : object(num1, side1)
    {
        name = "iceman";
        type = 2;
        num_of_weapons = 1;
        int weapon_num = num % 3;
        weaponss *a;
        life = life_of_creatures[type];
        switch (weapon_num)
        {
        case 0:
            a = new sword();
            have_weapons[0] = a;
            break;
        case 1:
            a = new bomb();
            have_weapons[0] = a;
            break;
        case 2:
            a = new arrow();
            have_weapons[0] = a;
            break;
        default:
            break;
        }
    }

    void move(int time)
    {
        if (side == 0 && position != city_num)
        {
            position++;
            ;
            life -= life / 10;
            cout << setw(3) << setfill('0') << time;
            cout << ":10 red iceman " << num << " marched to city " << position << " with " << life << " elements and force " << power_of_creature[type] << endl;
        }
        else if (side == 1 && position != 1)
        {
            position--;
            life -= life / 10;
            cout << setw(3) << setfill('0') << time;
            cout << ":10 blue iceman " << num << " marched to city " << position << " with " << life << " elements and force " << power_of_creature[type] << endl;
        }
    }
};

class lion : public object
{
public:
    lion(int num1, bool side1, int rest_life, int loyalty_decrease1) : object(num1, side1, rest_life, loyalty_decrease1)
    {
        name = "lion";
        type = 3;
        num_of_weapons = 1;
        int weapon_num = num % 3;
        weaponss *a;
        loyalty_decrease = loyalty_decrease1;
        life = life_of_creatures[type];
        switch (weapon_num)
        {
        case 0:
            a = new sword();
            have_weapons[0] = a;
            break;
        case 1:
            a = new bomb();
            have_weapons[0] = a;
            break;
        case 2:
            a = new arrow();
            have_weapons[0] = a;
            break;
        default:
            break;
        }
    }

    void move(int time)
    {
        if (side == 0 && position != city_num)
        {
            position++;
            loyalty -= loyalty_decrease;
            cout << setw(3) << setfill('0') << time;
            cout << ":10 red lion " << num << " marched to city " << position << " with " << life << " elements and force " << power_of_creature[type] << endl;
        }
        else if (side == 1 && position != 1)
        {
            position--;
            loyalty -= loyalty_decrease;
            cout << setw(3) << setfill('0') << time;
            cout << ":10 blue lion " << num << " marched to city " << position << " with " << life << " elements and force " << power_of_creature[type] << endl;
        }
    }

    bool is_scape()
    {
        if (side == 0)
        {
            if (position == city_num + 1)
            {
                return false;
            }
            else
            {
                if (loyalty <= 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            if (position == 0)
            {
                return false;
            }
            else
            {
                if (loyalty <= 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
};

class wolf : public object
{
public:
    wolf(int num1, bool side1) : object(num1, side1)
    {
        name = "wolf";
        type = 4;
        num_of_weapons = 0;
        life = life_of_creatures[type];
    }

    void rob_weapons(object *pobject, int time)
    {
        string robed_weapon;
        int robbed_num = 0;
        if (pobject->name != "wolf")
        {
            // wolf降生时没有武器，但是在战斗开始前会抢到敌人编号最小的那种武器。如果敌人有多件这样的武器，则全部抢来。Wolf手里武器也不能超过10件。如果敌人arrow太多没法都抢来，那就先抢没用过的
            // Wolf手里武器也不能超过10件。如果敌人arrow太多没法都抢来，那就先抢没用过的。如果敌人也是wolf，则不抢武器。

            // 先对敌人的武器进行排序
            pobject->modify_weapon();
            // 抢武器
            if (pobject->num_of_weapons > 0)
            {
                string weaponfirst = pobject->have_weapons[0]->name;
                int index = 0;
                for (; index < pobject->num_of_weapons; index++)
                {
                    if (pobject->have_weapons[index]->name != weaponfirst)
                    {
                        break;
                    }
                }
                robed_weapon = weaponfirst;

                for (int i = index - 1; i >= 0; i--)
                {
                    if (num_of_weapons < 10)
                    {
                        have_weapons[num_of_weapons] = pobject->have_weapons[i];
                        for (int j = i; j < pobject->num_of_weapons; j++)
                        {
                            pobject->have_weapons[j] = pobject->have_weapons[j + 1];
                        }
                        robbed_num++;

                        pobject->num_of_weapons--;
                        num_of_weapons++;
                    }
                    else
                    {
                        break;
                    }
                }
                cout << setw(3) << setfill('0') << time;

                cout << ":35 " << (side ? "blue" : "red") << " wolf " << num << " took " << robbed_num << " " << robed_weapon << " from " << (pobject->side ? "blue" : "red") << " " << pobject->name << " " << pobject->num << " in city " << position << endl;
            }
            else
            {
                return;
            }
        }
    }
};

class city
{
public:
    int num;
    object *creature_in_the_city[2];
    bool isbattle = false;

    bool is_blue_creature_in_the_city()
    {
        if (creature_in_the_city[1] != NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool is_red_creature_in_the_city()
    {
        if (creature_in_the_city[0] != NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class headquarter
{
public:
    int life;
    bool side; // 0 is red, 1 is blue
    int loyalty_decrease;

    int total_creature_num;

    headquarter(int life1, int decrease) : life(life1), loyalty_decrease(decrease)
    {
    }
};

class red : public headquarter
{
public:
    red(int life1, int decrease) : headquarter(life1, decrease)
    {
        side = 0;
        total_creature_num = 0;
    }

    int born_order[5] = {2, 3, 4, 1, 0};
    int born_num[5] = {0, 0, 0, 0, 0};
    int born_num_now = 0;

    object *born(int time)
    {

        total_creature_num++;
        if (life < life_of_creatures[born_order[born_num_now]])
        {
            return NULL;
        }
        cout << setw(3) << setfill('0') << time;
        int creature1 = born_order[born_num_now];
        born_num_now = (born_num_now + 1) % 5;
        born_num[creature1]++;
        life -= life_of_creatures[creature1];

        cout << ":00" << " red " << creature[creature1] << " " << total_creature_num << " born" << endl;
        if (creature[creature1] == "lion")
        {
            cout << "Its loyalty is " << life << endl;
        }

        switch (creature1)
        {
        case 0:
        {
            dragon *a = new dragon(total_creature_num, side);
            return a;
            break;
        }
        case 1:
        {
            ninjia *b = new ninjia(total_creature_num, side);
            return b;
            break;
        }

        case 2:
        {
            iceman *c = new iceman(total_creature_num, side);
            return c;
        }
        case 3:
        {
            lion *d = new lion(total_creature_num, side, life, loyalty_decrease);
            return d;
            break;
        }

        case 4:
        {
            wolf *e = new wolf(total_creature_num, side);
            return e;
            break;
        }
        default:
            break;
        }
        return NULL;
    }
};

class blue : public headquarter
{
public:
    blue(int life1, int decrease) : headquarter(life1, decrease)
    {
        total_creature_num = 0;
        side = 1;
    }

    int born_order[5] = {3, 0, 1, 2, 4};
    int born_num[5] = {0, 0, 0, 0, 0};
    int born_num_now = 0;

    object *born(int time)
    {

        if (life < life_of_creatures[born_order[born_num_now]])
        {
            return NULL;
        }
        total_creature_num++;
        cout << setw(3) << setfill('0') << time;
        int creature1 = born_order[born_num_now];
        born_num_now = (born_num_now + 1) % 5;
        born_num[creature1]++;
        life -= life_of_creatures[creature1];
        cout << ":00" << " blue " << creature[creature1] << " " << total_creature_num << " born" << endl;
        if (creature[creature1] == "lion")
        {
            cout << "Its loyalty is " << life << endl;
        }
        switch (creature1)
        {
        case 0:
        {
            dragon *a = new dragon(total_creature_num, side);
            return a;
            break;
        }
        case 1:
        {
            ninjia *b = new ninjia(total_creature_num, side);
            return b;
            break;
        }
        case 2:
        {
            iceman *c = new iceman(total_creature_num, side);
            return c;
            break;
        }
        case 3:
        {
            lion *d = new lion(total_creature_num, side, life, loyalty_decrease);
            return d;
            break;
        }
        case 4:
        {
            wolf *e = new wolf(total_creature_num, side);
            return e;
            break;
        }
        default:
            break;
        }
        return NULL;
    }
};

int main()
{
    int t;
    int ini = 0;
    cin >> t;
    while (t--)
    {
        cout << "Case " << ++ini << ':' << endl;
        int m, n, k, t;
        cin >> m >> n >> k >> t;
        city_num = n;
        red red1(m, k);
        blue blue1(m, k);
        city cities[n + 2];
        for (int i = 0; i < n + 2; i++)
        {
            cities[i].num = i;
            cities[i].creature_in_the_city[0] = NULL;
            cities[i].creature_in_the_city[1] = NULL;
        }
        for (int i = 0; i < 5; i++)
            cin >> life_of_creatures[i];
        for (int i = 0; i < 5; i++)
            cin >> power_of_creature[i];
        int time = 0;
        while (1)
        {
            // 武士降生
            if (time > t / 60)
                break;
            object *new_red_warior = red1.born(time);
            object *new_blue_warior = blue1.born(time);
            cities[0].creature_in_the_city[0] = new_red_warior;
            cities[n + 1].creature_in_the_city[1] = new_blue_warior;
            // lion逃跑
            if (time * 60 + 5 > t)
                break;
            for (int i = 0; i < n + 2; i++)
            {
                if (cities[i].creature_in_the_city[0] != NULL && cities[i].creature_in_the_city[0]->name == "lion")
                {
                    if (cities[i].creature_in_the_city[0]->is_scape())
                    {
                        cout << setw(3) << setfill('0') << time;
                        cout << ":05 red lion " << cities[i].creature_in_the_city[0]->num << " ran away" << endl;
                        cities[i].creature_in_the_city[0] = NULL;
                    }
                }
                if (cities[i].creature_in_the_city[1] != NULL && cities[i].creature_in_the_city[1]->name == "lion")
                {
                    if (cities[i].creature_in_the_city[1]->is_scape())
                    {
                        cout << setw(3) << setfill('0') << time;
                        cout << ":05 blue lion " << cities[i].creature_in_the_city[1]->num << " ran away" << endl;
                        cities[i].creature_in_the_city[1] = NULL;
                    }
                }
            }
            if (time * 60 + 10 > t)
                break;
            // 武士前进到某一城市  ,同时更新city里的creature
            city temp_city[n + 2];
            for (int i = 0; i < n + 2; i++)
            {
                temp_city[i].creature_in_the_city[0] = NULL;
                temp_city[i].creature_in_the_city[1] = NULL;
            }

            if (cities[1].creature_in_the_city[1] != NULL)
            {
                cities[0].creature_in_the_city[1] = cities[1].creature_in_the_city[1];
                cities[1].creature_in_the_city[1] = NULL;
                cout << setw(3) << setfill('0') << time;
                if (cities[0].creature_in_the_city[0]->name == "iceman")
                    cities[0].creature_in_the_city[0]->life -= cities[0].creature_in_the_city[0]->life / 10;
                cout << ":10 blue " << cities[0].creature_in_the_city[1]->name << " " << cities[0].creature_in_the_city[1]->num << " reached red headquarter with " << cities[0].creature_in_the_city[1]->life << " elements and force " << power_of_creature[cities[0].creature_in_the_city[1]->type] << endl;
                cout << setw(3) << setfill('0') << time;
                cout << ":10 red headquarter was taken" << endl;
            }

            for (int i = 0; i < n + 2; i++)
            {

                if (i != 0 && cities[i - 1].creature_in_the_city[0] != NULL)
                {
                    cities[i - 1].creature_in_the_city[0]->move(time);
                    temp_city[i].creature_in_the_city[0] = cities[i - 1].creature_in_the_city[0];
                    cities[i - 1].creature_in_the_city[0] = NULL;
                }

                if (i != n + 1 && cities[i + 1].creature_in_the_city[1] != NULL)
                {
                    cities[i + 1].creature_in_the_city[1]->move(time);
                    cities[i].creature_in_the_city[1] = cities[i + 1].creature_in_the_city[1];
                    cities[i + 1].creature_in_the_city[1] = NULL;
                }
                if (i == n && cities[i].creature_in_the_city[0] != NULL)
                {
                    temp_city[n + 1].creature_in_the_city[0] = cities[i].creature_in_the_city[0];
                    cities[i].creature_in_the_city[0] = NULL;
                    if (temp_city[n + 1].creature_in_the_city[0]->name == "iceman")
                        temp_city[n + 1].creature_in_the_city[0]->life -= temp_city[n + 1].creature_in_the_city[0]->life / 10;
                    cout << setw(3) << setfill('0') << time;
                    cout << ":10 red " << temp_city[n + 1].creature_in_the_city[0]->name << " " << temp_city[n + 1].creature_in_the_city[0]->num << " reached blue headquarter with " << temp_city[n + 1].creature_in_the_city[0]->life << " elements and force " << power_of_creature[temp_city[n + 1].creature_in_the_city[0]->type] << endl;
                    cout << setw(3) << setfill('0') << time;
                    cout << ":10 blue headquarter was taken" << endl;
                }
            }

            // 恢复city里的creature
            for (int i = 0; i < n + 2; i++)
            {
                cities[i].creature_in_the_city[0] = temp_city[i].creature_in_the_city[0];
            }

            bool flag = false;
            // 判断是否有武士到达对方司令部
            if (cities[0].creature_in_the_city[1] != NULL)
                flag = true;
            if (cities[n + 1].creature_in_the_city[0] != NULL)
                flag = true;
            if (flag)
                break;
            if (time * 60 + 35 > t)
                break;
            // wolf抢武器
            for (int i = 0; i < n + 2; i++)
                if (cities[i].creature_in_the_city[0] != NULL && cities[i].creature_in_the_city[1] != NULL)
                {
                    cities[i].creature_in_the_city[0]->rob_weapons(cities[i].creature_in_the_city[1], time);
                    cities[i].creature_in_the_city[1]->rob_weapons(cities[i].creature_in_the_city[0], time);
                }
            if (time * 60 + 40 > t)
                break;
            for (int i = 1; i < n + 1; i++)
            {
                if (i % 2 == 1)
                {
                    if (cities[i].creature_in_the_city[0] != NULL && cities[i].creature_in_the_city[1] != NULL)
                    {
                        cities[i].isbattle = true;
                        cout << setw(3) << setfill('0') << time;
                        cities[i].creature_in_the_city[0]->attack(cities[i].creature_in_the_city[1]);
                        if (cities[i].creature_in_the_city[0]->isdead())
                            cities[i].creature_in_the_city[0] = NULL;
                        if (cities[i].creature_in_the_city[1]->isdead())
                            cities[i].creature_in_the_city[1] = NULL;
                    }
                    else
                        cities[i].isbattle = false;
                    if (cities[i].isbattle)
                    {
                        if (cities[i].creature_in_the_city[0] != NULL && cities[i].creature_in_the_city[0]->name == "dragon")
                        {
                            cout << setw(3) << setfill('0') << time;
                            cities[i].creature_in_the_city[0]->cheer();
                        }
                        if (cities[i].creature_in_the_city[1] != NULL && cities[i].creature_in_the_city[1]->name == "dragon")
                        {
                            cout << setw(3) << setfill('0') << time;
                            cities[i].creature_in_the_city[1]->cheer();
                        }
                    }
                }
                else
                {
                    if (cities[i].creature_in_the_city[0] != NULL && cities[i].creature_in_the_city[1] != NULL)
                    {
                        cities[i].isbattle = true;
                        cout << setw(3) << setfill('0') << time;
                        cities[i].creature_in_the_city[1]->attack(cities[i].creature_in_the_city[0]);
                        if (cities[i].creature_in_the_city[0]->isdead())
                            cities[i].creature_in_the_city[0] = NULL;
                        if (cities[i].creature_in_the_city[1]->isdead())
                            cities[i].creature_in_the_city[1] = NULL;
                    }
                    else
                        cities[i].isbattle = false;
                    if (cities[i].isbattle)
                    {
                        if (cities[i].creature_in_the_city[0] != NULL && cities[i].creature_in_the_city[0]->name == "dragon")
                        {
                            cout << setw(3) << setfill('0') << time;
                            cities[i].creature_in_the_city[0]->cheer();
                        }
                        if (cities[i].creature_in_the_city[1] != NULL && cities[i].creature_in_the_city[1]->name == "dragon")
                        {
                            cout << setw(3) << setfill('0') << time;
                            cities[i].creature_in_the_city[1]->cheer();
                        }
                    }
                }
            }
            if (time * 60 + 50 > t)
                break;
            // 司令部报告生命元数量
            cout << setw(3) << setfill('0') << time;
            cout << ":50 " << red1.life << " elements in red headquarter" << endl;
            cout << setw(3) << setfill('0') << time;
            cout << ":50 " << blue1.life << " elements in blue headquarter" << endl;
            if (time * 60 + 55 > t)
                break;
            // 武士报告情况
            for (int i = 0; i < n + 2; i++)
            {
                if (cities[i].creature_in_the_city[0] != NULL)
                {
                    int weapons_num[3] = {0, 0, 0};
                    for (int j = 0; j < cities[i].creature_in_the_city[0]->num_of_weapons; j++)
                    {
                        if (cities[i].creature_in_the_city[0]->have_weapons[j]->name == "sword")
                            weapons_num[0]++;
                        else if (cities[i].creature_in_the_city[0]->have_weapons[j]->name == "bomb")
                            weapons_num[1]++;
                        else if (cities[i].creature_in_the_city[0]->have_weapons[j]->name == "arrow")
                            weapons_num[2]++;
                    }
                    cout << setw(3) << setfill('0') << time;
                    cout << ":55 red " << cities[i].creature_in_the_city[0]->name << " " << cities[i].creature_in_the_city[0]->num << " has " << weapons_num[0] << " sword " << weapons_num[1] << " bomb " << weapons_num[2] << " arrow and " << cities[i].creature_in_the_city[0]->life << " elements" << endl;
                }
                if (cities[i].creature_in_the_city[1] != NULL)
                {
                    int weapons_num[3] = {0, 0, 0};
                    for (int j = 0; j < cities[i].creature_in_the_city[1]->num_of_weapons; j++)
                    {
                        if (cities[i].creature_in_the_city[1]->have_weapons[j]->name == "sword")
                            weapons_num[0]++;
                        else if (cities[i].creature_in_the_city[1]->have_weapons[j]->name == "bomb")
                            weapons_num[1]++;
                        else if (cities[i].creature_in_the_city[1]->have_weapons[j]->name == "arrow")
                            weapons_num[2]++;
                    }
                    cout << setw(3) << setfill('0') << time;
                    cout << ":55 blue " << cities[i].creature_in_the_city[1]->name << " " << cities[i].creature_in_the_city[1]->num << " has " << weapons_num[0] << " sword " << weapons_num[1] << " bomb " << weapons_num[2] << " arrow and " << cities[i].creature_in_the_city[1]->life << " elements" << endl;
                }
            }
            time++;
        }
    }
}