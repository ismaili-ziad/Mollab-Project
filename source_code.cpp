#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <ctype.h>
#define LANG 2
#define LD 40
#define MEM 1
#define LEN 10
#define NATOM 20

//MEM is defined as the MOLLAB community members

using namespace std;
int LNG = 0, NB_ATO = 0, NB_BDS = 0, n_max = 0;
vector <int> stacking_chain; vector <int> real_st;
vector <int> carbons;
//IMPORTANT: LANG and MEM must be updated
//before modifying the length of "lang" and "members"
string lang[LANG] = {"Chosen language: ENGLISH", "Langue choisie: FRANCAIS"};
//So far, the maximum capacity for the longest chain is 10 carbons
string chain_len[LEN] = {"methyl", "ethyl", "prop", "but", "pent", "hex", "hept", "oct", "non", "dec"};

//Boolean declarations
//Used to find the functional group efficiently
bool is_O = false, is_N = false;
int o_id, n_id;

//DATA STRUCTURE: GRAPH OR TREE (for acyclic molecules)
//WARNING! NOTE THAT THIS DATA STRUCTURE CAN'T HANDLE CYCLIC MOLECULES
//YET. PLEASE KEEP AWARE OF THAT CHANGE TO MAKE SURE THAT THIS D.S. STILL
//WORKS.
struct Atom{
    public:
    char type;
    vector<int> connected_atoms;
};

Atom ATOM[NATOM];
int seen_a[NATOM] = {0};
bool is_carbon[NATOM] = {false};

void line_drawer(){
    printf("\t");
    for(int l = 0; l < LD; ++l) printf("-"); printf("\n");
    return;
}

void find_longest_chain(int carbon, int len){
    seen_a[carbon] = 1;
    stacking_chain.push_back(carbon);
    for(unsigned int i = 0; i < ATOM[carbon].connected_atoms.size(); ++i){
        int pass = ATOM[carbon].connected_atoms[i];
        if(!seen_a[pass] && is_carbon[pass]){
            find_longest_chain(pass, len+1);
        }
    }
    seen_a[carbon] = 0;
    if(stacking_chain.size() > n_max) n_max = stacking_chain.size();
    stacking_chain.pop_back();
    return;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    printf("\n\n\n\tWELCOME TO MOLLAB! BIENVENUE SUR MOLLAB!\n");
    printf("\tVersion: 1.0.0 (11/18/2019)\n\n");
    printf("\tDeveloped by / Developpe par: ISMAILI ALAOUI Ziad (%d member(s))\n", MEM);
    printf("\tThanks to / Remerciments a:\n\tMrs. MAILLY Emeline (P&C teacher in St. Paul HS, Lens, FRANCE)\n");
    printf("\n\n\tSELECT A LANGUAGE / SELECTIONNEZ UNE LANGUE:\n\t1 - FRANCAIS\n\t2 - ENGLISH\n\tChoice: ");
    cin >> LNG;
    if(LNG == 1){
        printf("\n\tSorry, French is not available yet :(\n\tYou are redirected to ENGLISH...\n");
    }
    else{
        while(LNG != 2){
            printf("\n\tPlease enter a correct value (which is 2).\n\tChoice: ");
            cin >> LNG;
        }
    }
    line_drawer();
    printf("\n\tThank you for using MOLLAB!\n\tBefore processing, make sure you read readme.pdf\n\tin the application folder.\n");
    printf("\n\tRECALL: in the following questions, never count hydrogens.\n");
    printf("\n\tHow many atoms does your molecule have? (don't count H's)\n\tAnswer (integer): ");
    cin >> NB_ATO;
    printf("\n\tHow many bounds does your molecule have? (including double bounds...)\n\tAnswer (exclude any (X)-H bound, no hydrogen): ");
    cin >> NB_BDS;
    printf("\n\n\tDescribe the pattern as mentioned in readme.pdf:\n\n\t");
    for(int l = 0; l < NB_BDS; ++l){
        int a, b;
        cin >> a >> b;
        printf("\n\t");
        ATOM[a].connected_atoms.push_back(b);
        ATOM[b].connected_atoms.push_back(a);
    }
    printf("As stated in the documentation, assign the types:\n\t");
    for(int t = 0; t < NB_ATO; ++t){
        char c; cin >> c;
        switch(c){
            case 'O': is_O = true; o_id = t; break;
            case 'N': is_N = true; n_id = t; break;
        }
        if(c == 'C'){
            carbons.push_back(t);
            is_carbon[t] = true;
        }
    }
    printf("\n\t");
    for(unsigned int c = 0; c < carbons.size(); ++c){
        find_longest_chain(c, 0);
        /*if(stacking_chain.size() > n_max){
            n_max = stacking_chain.size();
            while(!real_st.empty()) real_st.pop_back();
            while(!stacking_chain.empty()){
                real_st.push_back(stacking_chain[0]);
                stacking_chain.erase(stacking_chain.begin());
            }
        }*/
        if(stacking_chain.size() == NB_ATO) break;
    }
    printf("The longest chain is composed of %d ", n_max);
    if(n_max == 1) printf("carbon.\n\t");
    else printf("carbons.\n\t");
    printf("This molecule is an ");
    if(!is_O && !is_N) printf("Alkane.\n\t");
    else if(is_O) printf("Alcohol.\n\t");
    else if(is_N) printf("Amine.\n\t");
    system("PAUSE");
    return 0;
}
