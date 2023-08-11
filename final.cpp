#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;

unordered_map<string,int> location_hasher;
vector<pair<int,int>> location_list[13];

int shortest_length[13] = {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX}; 
bool visited[13] = {false,false,false,false,false,false,false,false,false,false,false,false,false};
//for adding edge
void add_edge(vector<pair<int,int>> list[],int u,int v,int weight){
    pair<int,int> edge;
    edge.second = weight;
    edge.first = v;
    list[u].push_back(edge);
    edge.first = u;
    list[v].push_back(edge);
}


//finding shortest path
void dijkstra(vector<pair<int,int>> list[],int *shortest_len,int source,bool finalised[],int nodes){
    shortest_len[source] = 0;
    int counter = nodes;
    for(int i = 0;i<counter;i++){
        int temp_min = -1;
        for(int j = 0;j<nodes;j++){
            if(finalised[j] == false){
                if(temp_min == -1){
                    temp_min = j;
                }else{
                    if(shortest_len[temp_min] > shortest_len[j]){
                        temp_min = j;
                    }
                }
            }
        }
        finalised[temp_min] = true;
        for(int j = 0;j<list[temp_min].size();j++){
            if(finalised[(list[temp_min][j]).first] == false){
                shortest_len[list[temp_min][j].first] = min(shortest_len[list[temp_min][j].first],shortest_len[temp_min]+list[temp_min][j].second);
            }
        }
    }
}

class User
{
private:
    string user_name;
    int user_id;
    string delivery_address;
    string password;
    string membership;

public:
    User() 
    {
    }
    User(string _user_name, int _user_id, string _delivery_address, string _password, string _membership)
    {
        user_name = _user_name;
        user_id = _user_id;
        delivery_address = _delivery_address;
        password = _password;
        membership = _membership;
    }

    void set_values(string _user_name, int _user_id, string _delivery_address, string _password, string _membership)
    {
        user_name = _user_name;
        user_id = _user_id;
        delivery_address = _delivery_address;
        password = _password;
        membership = _membership;
    }

    string get_user_name()
    {
        return user_name;
    }
    int get_user_id()
    {
        return user_id;
    }
    string get_delivery_address()
    {
        return delivery_address;
    }
    string get_password()
    {
        return password;
    }
    string get_membership()
    {
        return membership;
    }
    void display()
    {
        cout << "NAME: " << user_name << endl;
        cout << "USER ID: " << user_id << endl;
        cout << "CITY: " << delivery_address << endl;
    }
};

class Hash
{
    int BUCKET; // No. of buckets

    // Pointer to an array containing buckets
    

public:
    Hash(int V); // Constructor
    list<User> *table;
    // inserts a key into hash table
    void insertItem(int x, User u);

    // deletes a key from hash table
    void deleteItem(int key);

    // hash function to map values to key
    int hashFunction(int x)
    {
        return (x % BUCKET);
    }

    void displayHash();

    void print_user_details(int key);

    bool check_user(int key);

    bool check_password(int key, string pword);
};

Hash::Hash(int b)
{
    this->BUCKET = b;
    table = new list<User>[BUCKET];
}

void Hash::insertItem(int key, User u)
{
    int index = hashFunction(key);
    table[index].push_back(u);
}

void Hash::deleteItem(int key)
{
    // get the hash index of key
    int index = hashFunction(key);

    // find the key in (index)th list
    list<User>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++)
    {
        if (i->get_user_id() == key)
            break;
    }

    // if key is found in hash table, remove it
    if (i != table[index].end())
        table[index].erase(i);
}

// function to display hash table
void Hash::displayHash()
{
    for (int i = 0; i < BUCKET; i++)
    {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x.get_user_id();
        cout << endl;
    }
}

void Hash::print_user_details(int key)
{
    int index = hashFunction(key);
    for (auto x : table[index])
        if (x.get_user_id() == key)
        {
            x.display();
        }
}
bool Hash::check_user(int key)
{
    int index = hashFunction(key);
    for (auto x : table[index])
        if (x.get_user_id() == key)
        {
            return true;
        }
    return false;
}

bool Hash::check_password(int key, string pword)
{
    int index = hashFunction(key);
    for (auto x : table[index])
        if (x.get_user_id() == key)
        {
            if (x.get_password() == pword)
                return true;
        }
    return false;
}


// products
class Product
{
private:
    string product_name;
    string product_id;
    float price;
    vector<pair<string, int>> availability;

public:
    Product()
    {
    }

    Product(string _product_name, string _product_id, float _price, vector<pair<string, int>> &_availability);
    string get_product_name();
    string get_product_id();
    vector<pair<string,int>> &get_product_address();
    float get_price();
};

Product ::Product(string _product_name, string _product_id, float _price, vector<pair<string, int>> &_availability)
{
    product_name = _product_name;
    product_id = _product_id;
    price = _price;
    availability = _availability;
}

string Product ::get_product_name()
{
    return product_name;
}
vector<pair<string,int>> &Product ::get_product_address()
{
    return availability;
}
string Product ::get_product_id()
{
    return product_id;
}
float Product ::get_price()
{
    return price;
}

class Node
{
public:
    string key;
    Node *left;
    Node *right;
    int height;

    Product product_details;
};

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}


//avl tree
Node *newNode(string key, Product &p)
{
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    node->product_details = p;
    return (node);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, string key, Product &p)
{
    if (node == NULL)
        return (newNode(key, p));

    if (key < node->key)
        node->left = insert(node->left, key, p);
    else if (key > node->key)
        node->right = insert(node->right, key, p);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void print_details(Node *root)
{
    cout << "DETAILS:\n";
    cout << "NAME: " << root->product_details.get_product_name() << endl;
    cout << "PRICE: Rs." << root->product_details.get_price();
}

Node *search(Node *root, string key)
{
    if (root == NULL)
    {
        cout << "Not Available\n";
        return root;
    }
    if (root->key == key)
    {
        print_details(root);
        return root;
    }

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

Node *minValueNode(Node *node)
{
    Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, string key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            Node *temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preorder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}
// avl tree ends
Node *root = NULL;

void search_page(int userid, Hash &h)
{
    int ch = 1;
    char buy;
    string name;
    while (ch)
    {
        cout << "\n1. Search\n";
        cout << "0. Exit\n";
        cout << "Enter Choice: ";
        cin >> ch;
        if (ch)
        {
            cout << "Enter name of product: ";
            cin >> name;
            Node *prd_node = search(root, name);
            if (prd_node)
                cout << "\nBUY (y / n): ";
            else continue;
            cin >> buy;
            if (buy == 'y')
            {
                int index = h.hashFunction(userid);
                int src;
                for (auto x : h.table[index]){
                    if (x.get_user_id() == userid)
                    {
                        src = location_hasher[x.get_delivery_address()];
                    }
                }
                dijkstra(location_list,shortest_length,src,visited,13);
                vector<pair<string,int>> temp_availabilty;
                temp_availabilty = prd_node->product_details.get_product_address();
                int shortest_days = INT_MAX;
                string shortest_city;
                for(auto it : temp_availabilty){
                    cout << it.first << " " << shortest_length[location_hasher[it.first]] << " days";
                    cout << endl;
                }
                for(auto it : temp_availabilty){
                    if(shortest_length[location_hasher[it.first]] < shortest_days && it.second > 0){
                        shortest_city = it.first;
                        shortest_days = shortest_length[location_hasher[it.first]];
                    }
                }

                cout << "The product will be delivered to you within from " << shortest_city;
                if(shortest_days == 0){
                    cout << " tomorrow" << endl;
                    shortest_days++;
                }else{
                    cout << shortest_days << " days"<<endl;
                } 
                cout << "The delivery cost of the product will be: Rs." << shortest_days * 10;
                cout << "\nTotal Cost: " << prd_node->product_details.get_price() + shortest_days * 10;
                for(int count = 0;count<13;count++){
                    shortest_length[count] = INT_MAX;
                }
                for(int count = 0;count<13;count++){
                    visited[count] = false;
                }
            }
        }
        else
            exit(0);
    }
}

void sign_up(Hash &h)
{
    string name;
    int userid;
    string pword;
    string city;
    string m;
    cout << "SIGN UP\n";
    cout << "NAME: ";
    cin >> name;
    cout << "USER ID: ";
    cin >> userid;
    cout << "CITY: ";
    cin >> city;
    cout << "PASSWORD: ";
    cin >> pword;
    cout << "MEMBERSHIP (Basic / Premium): ";
    cin >> m;
    User u(name, userid, city, pword, m);
    h.insertItem(u.get_user_id(), u);
}

void login(Hash &h)
{
    int userid;
    string pword;
    cout << "LOGIN\n";
    cout << "USER ID: ";
    cin >> userid;
    cout << "PASSWORD: ";
    cin >> pword;
    if (h.check_user(userid) == false)
    {
        cout << "Account not found\n";
        sign_up(h);
        login(h);
    }
    else if (h.check_password(userid, pword) == false)
    {
        cout << "Incorrect Password\n";
        login(h);
    }
    h.print_user_details(userid);
    search_page(userid, h);
}

User u1("aa", 1234567, "chennai", "aa123", "premium");
User u2("bb", 6586461, "delhi", "bb123", "basic");
User u3("cc", 6491646, "kolkata", "cc123", "basic");
User u4("dd", 2845782, "mumbai", "dd123", "premium");
User u5("ee", 5693498, "coimbatore", "ee123", "basic");
User u6("ff", 1467702, "pune", "ff123", "basic");
User u7("gg", 1956936, "nagpur", "gg123", "basic");
User u8("hh", 3156936, "coimbatore", "hh123", "basic");
User u9("ii", 4735404, "madurai", "ii123", "basic");
User u10("jj", 4566523, "trichy", "jj123", "basic");

Hash h(7);

vector<pair<string, int>> vect1{{"trichy", 45}, {"mumbai", 21}, {"coimbatore", 82}, {"kolkata", 56}};
Product p1("samsungm21", "p1", 18899.0, vect1);

vector<pair<string, int>> vect2{{"udupi", 22}, {"delhi", 12}, {"pune", 68}, {"kolkata", 6}};
Product p2("oppof19", "p2", 21499.0, vect2);

vector<pair<string, int>> vect3{{"chennai", 54}, {"delhi", 120}, {"coimbatore", 98}, {"kolkata", 56}};
Product p3("oneplus5", "p3", 13499.0, vect3);

vector<pair<string, int>> vect4{{"chennai", 54}, {"delhi", 120}, {"kolkata", 56}};
Product p4("redminote11t", "p4", 16799.0, vect4);

vector<pair<string, int>> vect5{{"delhi", 120}, {"mumbai", 98}, {"hooghly", 36}};
Product p5("iphone11", "p5", 15000.0, vect5);

vector<pair<string, int>> vect6{{"chennai", 54}};
Product p6("motorolag31", "p6", 12000.0, vect6);

vector<pair<string, int>> vect7{{"chennai", 1}, {"bangalore", 62}};
Product p7("oneplusnord", "p7", 31999.0, vect7);

vector<pair<string, int>> vect8{{"chennai", 54}, {"nagpur", 3120}, {"mumbai", 98}};
Product p8("realme8", "p8", 44499.0, vect8);

vector<pair<string, int>> vect9{{"delhi", 120}, {"mumbai", 98}, {"kolkata", 56}};
Product p9("samsunga52", "p9", 22499.0, vect9);

vector<pair<string, int>> vect10{{"trichy", 45}, {"mumbai", 21}, {"coimbatore", 82}, {"kolkata", 56}};
Product p10("s9", "p10", 18899.0, vect10);

int main()
{   
    //tamil_nadu
    location_hasher["chennai"] = 0;
    location_hasher["trichy"] = 1;
    location_hasher["madurai"] = 2;
    location_hasher["coimbatore"] = 3;

    //karnataka
    location_hasher["bangalore"] = 4;
    location_hasher["mysore"] = 5;
    location_hasher["udupi"] = 6;

    //mumbai
    location_hasher["mumbai"] = 7;
    location_hasher["pune"] = 8;
    location_hasher["nagpur"] = 9;

    //delhi
    location_hasher["delhi"] = 10;

    //kolkata
    location_hasher["kolkata"] = 11;
    location_hasher["hooghly"] = 12;
    //tn
    add_edge(location_list,0,3,1);
    add_edge(location_list,0,2,2);
    add_edge(location_list,0,1,3);

    //knt
    add_edge(location_list,4,5,1);
    add_edge(location_list,4,6,2);

    add_edge(location_list,0,4,1);

    add_edge(location_list,7,8,1);
    add_edge(location_list,7,9,2);

    add_edge(location_list,7,4,2);

    add_edge(location_list,7,10,3);
    add_edge(location_list,7,11,5);

    add_edge(location_list,10,0,4);
    add_edge(location_list,10,11,3);

    add_edge(location_list,11,0,3);
    add_edge(location_list,11,12,2);
  
    h.insertItem(u1.get_user_id(), u1);
    h.insertItem(u2.get_user_id(), u2);
    h.insertItem(u3.get_user_id(), u3);
    h.insertItem(u4.get_user_id(), u4);
    h.insertItem(u5.get_user_id(), u5);
    h.insertItem(u6.get_user_id(), u6);
    h.insertItem(u7.get_user_id(), u7);
    h.insertItem(u8.get_user_id(), u8);
    h.insertItem(u9.get_user_id(), u9);
    h.insertItem(u10.get_user_id(), u10);

    cout << "Contents of Hash Table:\n";
    h.displayHash();
    cout << endl;

    root = insert(root, "samsungm21", p1);
    root = insert(root, "oppof19", p2);
    root = insert(root, "oneplus5", p3);
    root = insert(root, "redminote11t", p4);
    root = insert(root, "iphone11", p5);
    root = insert(root, "motorolag31", p6);
    root = insert(root, "oneplusnord", p7);
    root = insert(root, "realme8", p8);
    root = insert(root, "samsunga52", p9);

    cout << "Contents of AVL Tree: \n";
    preorder(root);
    cout << endl;

    root = insert(root, "s9", p10);

    cout << "\nContents of AVL Tree after insertion : \n";
    preorder(root);
    cout << endl; 
    
    int ch, flag = 0;
    cout << "1. LOGIN\n"
        << "2. SIGN UP\n"
        << "0. EXIT\n"
        << "Enter Choice : ";
    cin >> ch;
    if (ch == 1)
    {
        login(h);
    }
    if (ch == 2)
    {
        sign_up(h);
        login(h);
    }
    else
    {
        exit(0);
    }
}
