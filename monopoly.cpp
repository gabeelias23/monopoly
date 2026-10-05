#include <iostream>
#include <string>
#include <random>
using namespace std;

struct Node {
    string name; 
    int cost; 
    string owner; 
    Node* next;
};

// Add a property 
void addProperty(Node*& head, string name, int cost) {
    Node* newNode = new Node{name, cost, "None", nullptr};

    // If the board is empty
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
        return;
    }

    Node* current = head;

    // Find the last property and add the new property at the end
    while (current->next != head) {
        current = current->next;
    }

    current->next = newNode;
    newNode->next = head; 
}

// Search for a property
bool searchProperty(Node* head, string propertyName) {
    if (head == nullptr){
        return false;
    }

    Node* current = head;

    // Check the first property
    if(current->name == propertyName) {
        return true; 
    }

    current = current->next;
    
    // Search through the rest of the board
    while (current != head) {
        if (current->name == propertyName) {
            return true;
        }

        current = current->next;
    }

    return false; 
}

// Remove a property
void removeProperty(Node*& head, string propertyName) {
    if (head == nullptr) {
        return; 
    }

    // Remove the first property
    if (head->name == propertyName){
        
        Node* last = head;

        while (last->next != head){
            last = last->next;
        }

        Node* temp = head;
        head = head->next;
        last->next = head;

        delete temp; 
        return;
    }

    Node* current = head;

    // Find and remove a property
    while (current->next != head) {
        if (current->next->name == propertyName){
            Node*temp = current->next; 
            current->next = current->next->next;
            delete temp;
            return;
        }

        current = current->next; 
    }
}

// Move a player around the board
void movePlayer(Node*& position, int spaces) {
    for (int i = 0; i < spaces; i++) {
        position = position->next; 
    }
}

// Buy a property if it is unowned
void buyProperty(Node* position, string player) {
    if (position->owner == "None") {
        position->owner = player;

        cout << player << " bought " << position->name 
             << " for $" << position->cost << ".\n";
    }
    else {
        cout << position->name << " is already owned by " 
             << position->owner << ".\n";
    }
}

// Print the entire board
void printBoard(Node* head){

    if(head == nullptr){
        return;
    }
    
    Node* current = head;

    // Print the first property
    cout << "Property: " << current->name << " - Cost: $" << current->cost 
         << " - Owner: " << current->owner << ".\n";

    current = current->next;

    // Print the rest of the properties 
    while (current != head){
        cout << "Property: " << current->name << " - Cost: $" << current->cost 
             << " - Owner: " << current->owner << ".\n";

        current = current->next;
    }
}

// Roll a random number from 1 to 6
int rollDice() {
    static random_device rd;
    static mt19937 generator(rd());
    static uniform_int_distribution<int> distribution(1, 6);

    return distribution(generator);
}

int main(){

    Node* first = nullptr;

    // Build the circular board
    addProperty(first, "Mediterranean Ave", 60);
    addProperty(first, "Baltic Ave", 60);
    addProperty(first, "Oriental Ave", 100);
    addProperty(first, "Vermont Ave", 100);
    addProperty(first, "Connecticut Ave", 120);
    addProperty(first, "St. Charles Place", 140);
    addProperty(first, "States Ave", 140);
    addProperty(first, "Virginia Ave", 160);
    addProperty(first, "St. James Place", 180);
    addProperty(first, "Tennessee Ave", 180);

    cout << "\nSTART GAME\n\n";

    // Test searching for a property
    string searchName = "Connecticut Ave";

    if(searchProperty(first, searchName)){
        cout << searchName << " was found.\n\n";
    }
    else{
        cout << searchName << " was not found.\n\n";
    }

    // Test adding a property
    string addName = "New York Ave";
    int addCost = 200;

    addProperty(first, addName, addCost);

    cout << "After adding " << addName << ":\n\n";
    printBoard(first);

    cout << "\n";

    // Test removing a property
    string removeName = "New York Ave";

    removeProperty(first, removeName);

    cout << "After removing " << removeName << "\n\n";
    printBoard(first);

    // Create two players
    string player1 = "Player 1";
    string player2 = "Player 2";

    // Both players start at first property
    Node* player1Position = first;
    Node* player2Position = first;

    // Alternate between players
    bool isPlayer1Turn = true;

    for (int turn = 0; turn < 10; turn++){
        cout << "\nTurn " << turn + 1 << ":\n";

        // Roll the dice
        int roll = rollDice();
        
        // Player 1's turn
        if (isPlayer1Turn){
            cout << player1 << " rolled a " << roll << ".\n";

            movePlayer(player1Position, roll);

            cout << player1 << " landed on "
                 << player1Position->name << ".\n";

            buyProperty(player1Position, player1);

            isPlayer1Turn = false; 
        }
        else{
            // Player 2's turn
            cout << player2 << " rolled a " << roll << ".\n";

            movePlayer(player2Position, roll);

            cout << player2 << " landed on "
                 << player2Position->name << ".\n";
            
            buyProperty(player2Position, player2);

            isPlayer1Turn = true; 
        }
    }

    // Print final board
    cout << "\nFINAL BOARD\n";
    
    printBoard(first);

    cout << "\n";

    return 0; 
}