#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <bits/stdc++.h>
#include <map>

using namespace std;

void Get_Spells(std::map<string, int> &spells_pow_container, vector<string> H_or_V_or_A);
void Battle(int Harry_spell_power, int Voldmort_spell_power, int *Harry_energy, int *Voldmort_energy, int *Harry_health, int *Voldmort_health);

class Wizerd
{
public:
    string name, spell_name;
};

class Wizard_calc : public Wizerd
{
public:
    int health, energy, spell_power;

    Wizard_calc(int aHealth, int aEnergy, int aSpell_power)
    {
        health = aHealth;
        energy = aEnergy;
        spell_power = aSpell_power;
    }
    int Energy_Difference()
    {
        energy = energy - spell_power;
        return energy;
    }
};

int main()
{
    string line, spell, power;
    int postion1, postion2, power_int;
    ifstream xfile;
    vector<string> H_or_V_or_A;                 //vector wil be used to detrmain weather the user enter the format correctly
    std::map<string, int> spells_pow_container; //map contain spells and corrspending power

    xfile.open("spells.txt"); //open the file
    while (xfile)
    {
        getline(xfile, line);      //read line by line
        postion1 = line.find(" "); // postions used to help split the line in file to the spell and power
        postion2 = line.find(" ", postion1 + 1);
        H_or_V_or_A.push_back(line.substr(0, postion2));

        spell = line.substr(postion1, postion2 - 1);
        power = line.substr(postion2 + 1);
        power_int = stoi(power); //convert the power to integer
        spells_pow_container[spell] = power_int;
    }
    xfile.close(); //close file

    Get_Spells(spells_pow_container, H_or_V_or_A);

    return 0;
}

void Get_Spells(std::map<string, int> &spells_pow_container, vector<string> H_or_V_or_A)
{
    //create object
    Wizard_calc Harry(100, 500, 10);
    Wizard_calc Voldmort(100, 500, 10);
    Harry.name = "Harry Potter";
    Voldmort.name = "Voldmort";
    Harry.spell_name = "None";
    Voldmort.spell_name = "None";

    string line;
    int postion;
    char blank = ' ';
    int V_sheld_count = 0;
    int H_sheld_count = 0;

    while ((Harry.health > 0 && Voldmort.health > 0) && (Harry.energy > 0 && Voldmort.energy > 0))
    {
        //4 booleans used to tell weather th spell entered is correct or not
        bool A_Harry_Spell_Found = false;
        bool H_Harry_Spell_Found = false;
        bool A_Voldmort_Spell_Found = false;
        bool V_Voldmort_Spell_Found = false;

        cout << "Enter the two spells (H then V): ";
        getline(cin, line);
        postion = line.find(" ");
        Harry.spell_name = line.substr(0, postion);
        Voldmort.spell_name = line.substr(postion + 1);

        //check if spell enterd is in the vector and is correct
        if (std::find(H_or_V_or_A.begin(), H_or_V_or_A.end(), "A " + Harry.spell_name) != H_or_V_or_A.end())
            A_Harry_Spell_Found = true;
        if (std::find(H_or_V_or_A.begin(), H_or_V_or_A.end(), "H " + Harry.spell_name) != H_or_V_or_A.end())
            H_Harry_Spell_Found = true;
        if (std::find(H_or_V_or_A.begin(), H_or_V_or_A.end(), "A " + Voldmort.spell_name) != H_or_V_or_A.end())
            A_Voldmort_Spell_Found = true;
        if (std::find(H_or_V_or_A.begin(), H_or_V_or_A.end(), "V " + Voldmort.spell_name) != H_or_V_or_A.end())
            V_Voldmort_Spell_Found = true;

        if ((H_Harry_Spell_Found == true && V_Voldmort_Spell_Found == true) || (A_Harry_Spell_Found == true && A_Voldmort_Spell_Found == true) || (H_Harry_Spell_Found == true && A_Voldmort_Spell_Found == true) || (A_Harry_Spell_Found == true && V_Voldmort_Spell_Found == true))
        {
            Harry.spell_name.insert(0, 1, blank);
            Voldmort.spell_name.insert(0, 1, blank);

            //get speell power from the map
            Harry.spell_power = spells_pow_container[Harry.spell_name];
            Voldmort.spell_power = spells_pow_container[Voldmort.spell_name];

            //count number of times sheld is used
            if (Harry.spell_power == 0)
                H_sheld_count++;
            if (Voldmort.spell_power == 0)
                V_sheld_count++;

            if (H_sheld_count != 4 && V_sheld_count != 4)
            {
                //get new value of energy by using the function created above in the class
                Harry.energy = Harry.Energy_Difference();
                Voldmort.energy = Voldmort.Energy_Difference();
                //call Battle function
                Battle(Harry.spell_power, Voldmort.spell_power, &Harry.energy, &Voldmort.energy, &Harry.health, &Voldmort.health);
            }

            else
            {
                cout << "Bad Entry,Maxmimum Sheld Usage,Maxmimum=3!,Game will restart" << endl;
                Get_Spells(spells_pow_container, H_or_V_or_A);
            }
        }
        else
        {
            cout << "Bad Entry!,Game will restart" << endl;
            Get_Spells(spells_pow_container, H_or_V_or_A);
        }
    }
}

void Battle(int Harry_spell_power, int Voldmort_spell_power, int *Harry_energy, int *Voldmort_energy, int *Harry_health, int *Voldmort_health)
{

    //get the winner by comparing the spells power and health
    if (Harry_spell_power != 0 && Voldmort_spell_power != 0)
    {
        if (Harry_spell_power > Voldmort_spell_power)
        {
            *Voldmort_health = *Voldmort_health - (Harry_spell_power - Voldmort_spell_power);
        }
        else
        {
            *Harry_health = *Harry_health - (Voldmort_spell_power - Harry_spell_power);
        }
    }
    //check if health or energy is -ve to assign them to zreo
    if (*Harry_health < 0)
        *Harry_health = 0;
    if (*Harry_energy < 0)
        *Harry_energy = 0;

    if (*Voldmort_health < 0)
        *Voldmort_health = 0;
    if (*Voldmort_energy < 0)
        *Voldmort_energy = 0;

    //Output
    cout << "        Harry          Voldmort" << endl;
    cout << "Health: " << *Harry_health << "             " << *Voldmort_health << endl;
    cout << "Energy: " << *Harry_energy << "             " << *Voldmort_energy << endl;

    //check if Players tied
    if (*Harry_health == 0 && *Voldmort_health == 0)
    {
        cout << "Players tied" << endl;
    }
    else if (*Harry_energy == 0 && *Voldmort_energy == 0)
    {
        cout << "Players tied" << endl;
    }
    //get the winner
    else
    {
        if (*Harry_health == 0 || *Harry_energy == 0)
        {
            cout << "Voldmort is the winner";
        }
        else if (*Voldmort_health == 0 || *Voldmort_energy == 0)
        {
            cout << "Harry Potter is the winner";
        }
    }
}