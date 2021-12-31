// C++ program to create target string, starting from
// random string using Genetic Algorithm
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <time.h>
#include <iomanip>
using namespace std;

// Number of individuals in each generation
#define POPULATION_SIZE 100
float setting_degree = 0.6;
float const phi = 0.99;

int n,S;
int *a;
// Valid Genes
const string GENES = "01";
// Target string to be generated
//const string TARGET = "1001001001";

// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}

// Create random genes for mutation
char mutated_genes()
{
    int len = GENES.size();
    int r = random_num(0, len-1);
    return GENES[r];
}

// create chromosome or string of genes
string create_gnome()
{
    int len = n;
    string gnome = "";
    for(int i = 0;i<len;i++)
        gnome += mutated_genes();
    return gnome;
}

// Class representing individual in population
class Individual
{
public:
    string chromosome;
    int fitness;
    Individual(string chromosome);
    Individual mate(Individual parent2);
    int cal_fitness();
    Individual mutation();
};

Individual::Individual(string chromosome)
{
    this->chromosome = chromosome;
    fitness = cal_fitness();
};

// Perform mating and produce new offspring
Individual Individual::mate(Individual par2)
{
    // chromosome for offspring
    string child_chromosome = "";

    int len = chromosome.size();

    // random probability
    int p = random_num(0, len);
    for(int i = 0; i < p; i++)
        child_chromosome += chromosome[i];
    for(int i = p; i < len; i++)
        child_chromosome += par2.chromosome[i];
    /*// if prob is less than 0.45, insert gene
    // from parent 1
    if(p < 0.45)
        child_chromosome += chromosome[i];

    // if prob is between 0.45 and 0.90, insert
    // gene from parent 2
    else if(p < 0.90)
        child_chromosome += par2.chromosome[i];

    // otherwise insert random gene(mutate),
    // for maintaining diversity
    else
        child_chromosome += mutated_genes();

// create new Individual(offspring) using
// generated chromosome for offspring*/
    return Individual(child_chromosome);
};

Individual Individual::mutation(){
    /*string gnome = create_gnome();
        int sum = 0;
        for(int j = 0; j < n; j++){
            sum += a[j]*((int)gnome[j]-48);
        }
        if(S-sum >= 0){
            population.push_back(Individual(gnome));
            i++;
        }*/
    string child_chromosome = chromosome;
    int len = chromosome.size();
    for(int i = 0; i < 2; i++){
        int l = random_num(0, len-1);
        if(chromosome[l] == '1')
            child_chromosome[l] = '0';
        else if(chromosome[l] == '0')
            child_chromosome[l] = '1';
    }

    return Individual(child_chromosome);
}

// Calculate fittness score, it is the number of
// characters in string which differ from target
// string.
int Individual::cal_fitness()
{
    int len = n;
    int fitness = 0;
    for(int i = 0;i<len;i++)
    {
        int number = (int)chromosome[i]-48;
        fitness += number*a[i];
    }
    if(fitness > S) return fitness;
    return S - fitness;
};

// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}

// Calculate the difference-degree
float difference_degree(string parent1, string parent2){
    int d = 0, len = parent1.length();
    for(int i =0; i < len; i++){
        if(parent1[i] != parent2[i]) d++;
    }
    return (float)d/len*1.0;
}
// Driver code
int main()
{
    cin>>n>>S;
    a = new int[n];
    for(int i = 0; i < n; i++) cin>>a[i];
    srand((unsigned)(time(0)));
    clock_t start, end;
    float cpu_time_used=0.0;
    start = clock();
    // current generation
    int generation = 0;

    vector<Individual> population;
    bool found = false;
    // create initial population
    for(int i = 0;i<POPULATION_SIZE; i++)
    {
        string gnome = create_gnome();
        population.push_back(Individual(gnome));

    }
    while(! found )
    {
        // sort the population in increasing order of fitness score
        sort(population.begin(), population.end());

        // if the individual having lowest fitness score ie.
        // 0 then we know that we have reached to the target
        // and break the loop
        if(population[0].fitness == 0)
        {
            found = true;
            break;
        }

        // Otherwise generate new offsprings for new generation
        vector<Individual> new_generation;
        new_generation.push_back(population[0]);
        new_generation.push_back(population[1]);
        // Perform Elitism, that mean 10% of fittest population
        // goes to the next generation
        int Nc = 0;
        int s = (98*POPULATION_SIZE)/100;
        while(Nc < s){
            for(int i = 0;i<(s-Nc)/2;i++){
                int r = random_num(0, 99);
                Individual parent1 = population[r];
                r = random_num(0, 99);
                Individual parent2 = population[r];
                float difer = difference_degree(parent1.chromosome, parent2.chromosome);
                if(difer >= setting_degree){
                    new_generation.push_back(parent1);
                    new_generation.push_back(parent2);
                    Nc += 2;
                }
            }
            if(Nc < s){
                for(int i = 0;i<(s-Nc)/2;i++){
                    int r = random_num(0, 99);
                    Individual parent1 = population[r];
                    r = random_num(0, 99);
                    Individual parent2 = population[r];
                    float difer = difference_degree(parent1.chromosome, parent2.chromosome);
                    if(difer < setting_degree){
                        Individual offspring1 = parent1.mutation();
                        new_generation.push_back(offspring1);
                        Nc++;
                        offspring1 = parent2.mutation();
                        new_generation.push_back(offspring1);
                        Nc++;
                    }
                }
            }
        }
        population = new_generation;
        cout<< "Generation: " << generation << "\t";
        cout<< "String: "<< population[0].chromosome <<"\t";
        cout<< "Fitness: "<< population[0].fitness << "\n";
        generation++;
        setting_degree = setting_degree*phi;
     }
    cout<< "Generation: " << generation << "\t";
    cout<< "String: "<< population[0].chromosome <<"\t";
    cout<< "Fitness: "<< population[0].fitness << "\n";

    if(population[0].fitness  == 0) cout<<"Yes";
    else cout<<"No";
    end = clock();
    cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<fixed<<setprecision(2);
    cout<<"\nTime: "<<cpu_time_used*1000<<endl;
}
