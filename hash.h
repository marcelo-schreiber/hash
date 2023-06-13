#define MAX 40
#define M 11

enum
{
  AVALIABLE,
  UNAVALIABLE,
  REMOVED
};

// Function prototypes

// Function to initialize hash table
void initialize_hash_table(int t[]);

// Function to print the hash tables
void print_table(int t1[], int t2[]);

// Function to insert values in the hash tables
void insert(int key, int t1[], int t2[]);

// Function to destroy values in the hash tables
void remove_item(int key, int t1[], int t2[]);