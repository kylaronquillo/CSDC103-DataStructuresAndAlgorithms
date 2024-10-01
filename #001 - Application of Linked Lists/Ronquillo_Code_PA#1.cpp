/*
C++ Code for a Song Playlist that can (1) add songs, (2) delete songs, (3) play next songs, (4) view playlist, 
and (5) shuffle playlist. Please check the user's manual to navigate this.

This code was written by: Kyla Ronquillo 
References:
    Lecture 3 - Linked List (PPT - for linked lists c++ syntax) 
    Basic Linked List C++ by lazytutorials (Video - for linked lists c++ syntax)
    Introduction to Linked Lists (Video - for visualizing linked lists)
    Fisher Yates Shuffle Algorithm by Tutorialspoint (Webpage - for shuffle algorithm)
    https://cplusplus.com/forum/beginner/217812/ (Webpage - for input validation  using numeric_limits<streamsize>::max(), '\n')
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// defines a structure named Song with five members
typedef struct Song {
    string titleOfSong;
    string artistsOfSong;
    int durationOfSong;
    string songID;
    struct Song* next;

    // use a constructor that initialized the parameters and sets next to null pointer
    Song(const string& title, const string& artists, int duration, string idNum) {
        titleOfSong = title;
        artistsOfSong = artists;
        durationOfSong = duration;
        songID = idNum;
        next = nullptr;
    }

} Node;

// defines class named Playlist
class Playlist {
private:
    // a pointer that points at the first song of the playlist
    Node* head;

public:
    // Constructor that initializes the head (from the private class) to null pointer
    Playlist() {
        head = nullptr;
    }

    // Function that allows user to add a song to the playlist
    void addSong(const string& title, const string& artists, int duration, string idNum) {
        // to check if input for duration if it's an integer
        while (cin.fail()) {
            cin.clear(); // Clear the failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "\nERROR: Invalid input for duration.\n\n";
            cout << "Please enter a valid integer (in seconds) for duration: ";
            cin >> duration;
        }

        //assigns a new dynamically created instance of the struct Node to pointer addNewSong
        Node* addNewSong = new Node(title, artists, duration, idNum);
        char choice;
        Node* current = head;

        while (current != nullptr) {
                if (current->titleOfSong == title && current->artistsOfSong == artists && current->durationOfSong == duration && current->songID == idNum) {
                    char choice;
                    while (true) {
                        cout << "\nNOTIF: The song '" << title << "' by " << artists << " is already in the playlist. Do you want to add it anyway? (y/n): ";
                        cin >> choice;
                        if (choice == 'Y' || choice == 'y') {
                            break;
                        } 
                        else if (choice == 'N' || choice == 'n') {
                            cout << "\nNOTIF: The song, " << current->titleOfSong << ", by " << current->artistsOfSong << " was not added to the playlist.\n\n";
                            return;
                        }
                        else {
                            cout << "\nNOTIF: Invalid Input. Please enter 'y' or 'n'.\n";
                        }
                    }
                }
          current = current->next;
        }
        
        if (head == nullptr) { //checks if the list is empty
            head = addNewSong; //assigns the newly added song as the header
        } 
        else { // if the list is not empty, then...
            Node* last = head;

            // loop the last pointer until it reaches the end or until it reaches the last song of the playlist
            while (last->next) {
                last = last->next; 
            }

            last->next = addNewSong; // assigns the new dynamically created instance to the node being pointed by the last pointer
        }
        cout << "\nNOTIF: The Song '" << title << "' by " << artists << " is added to the playlist.\n\n"; //notify the user
    }

    // Function that allows user to remove a song from the playlist if they search for it
    void removeSong(const string& title, string idNum) {
        //checks if playlist is empty
        if (head == nullptr) {
            cout << "\nNOTIF: The song playlist is empty.\n\n";
            return;
        }

        // declare and initialize two pointers
        Node* current = head;
        Node* previous = nullptr;

        // use while loop to search for the song to be removed
        while (current != nullptr) {
            //checks if the current song is the same as the song title inputted by the user
            if (current->titleOfSong == title && current->songID == idNum) {
                if (previous == nullptr) {
                    head = current->next;
                } 
                else {
                    previous->next = current->next;
                }
                delete current;
                cout << "\nNOTIF: You have removed " << title << " from the playlist." << endl << endl;
                return;
            } 
            else { // if not the same song, move to the next song in the playlist
                previous = current;
                current = current->next;
            }
        }
        cout << "\nNOTIF: The Song, " << title << ", is not found.\n\n"; //notify the user
    }

    // Function that allows user to play the next song from the playlist
    void playNextSong() {
        //checks if playlist is empty
        if (head == nullptr) {
            cout << "\nNOTIF: The song playlist is empty.\n\n";
        } 
        else { // if not empty...
            Node* current = head;
            head = current->next;
            current->next = nullptr;  // disconnect the current node from the list
            cout << "Now Playing: " << current->titleOfSong << " by " << current->artistsOfSong << " (" << current->durationOfSong << " seconds)\n\n" ;

            // move the current node to the end of the list
            if (head == nullptr) {
                head = current;  // if the list is empty, make the current node the new head
            } 
            else {
                Node* last = head;
                while (last->next) {
                    last = last->next;
                }
                last->next = current;
            }
        }
    }

    // Function that allows the user to view the entire playlist
    void viewPlaylist() {
        //checks if playlist is empty
        if (head == nullptr) {
            cout << "\nNOTIF: The song playlist is empty.\n\n";
            return;
        } 
        else { // if not empty, then print the playlist
            Node* current = head;

            cout << left << setw(30) << "Song ID" << setw(30) << "Title" << setw(30) << "Artist/s" << setw(30) << "Duration (sec)" << endl;

            while (current != nullptr) {
                cout << left << setw(30) << current->songID << setw(30) << current->titleOfSong << setw(30) << current->artistsOfSong << setw(30) << current->durationOfSong << endl;
                current = current->next;
            }     
              
            cout << endl << endl;
        }
    }

    // Function that allows to shuffle the songs in the playlist
    void shufflePlaylist() {
        // Check if the playlist is empty
        if (head == nullptr) {
            // there is no need to output a notif because it will output the notification using the viewPlaylist method
            return;
        }

        // Count the number of songs in the playlist
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }

        // Seed a random number generator using the current time
        srand(time(0));

        // Shuffle the playlist using the Fisher-Yates algorithm
        for (int i = count - 1; i > 0; i--) {
            int y;

            do {
                y = rand() % (i + 1);
            } while (y == i);

            // Find the ith and yth songs in the playlist
            current = head;
            Node* iSong = nullptr;
            Node* ySong = nullptr;

            for (int k = 0; k <= i; k++) {
                if (k == i) iSong = current;
                if (k == y) ySong = current;
                current = current->next;
            }

            // Swap the song details (title, artist, duration)
            swap(iSong->titleOfSong, ySong->titleOfSong);
            swap(iSong->artistsOfSong, ySong->artistsOfSong);
            swap(iSong->durationOfSong, ySong->durationOfSong);
            swap(iSong->songID, ySong->songID);
        }

        // Inform the user that the playlist has been shuffled
        cout << "\nNOTIF: Your playlist has been shuffled.\n\n";
    }

    // Destructor for the class
    ~Playlist() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
        }
    }

};

int main() {
    // creates an instance of the class playlist and declares variables
    Playlist openPlaylist;
    string inputTitle, inputArtists, inputID;
    int inputDuration;
    char choice;

    // while loop to continuously ask the user to what they wish to do
    while (true) {
        //interface
        cout << "Welcome to your Song Playlist!\n";
        cout << "Input the number of your choice:\n";
        cout << "1 - Add a Song\n";
        cout << "2 - Remove a Song\n";
        cout << "3 - Play the Next Song\n";
        cout << "4 - View your Song Playlist\n";
        cout << "5 - Shuffle your Playlist\n";
        cout << "6 - Quit\n";
        cout << "Please enter your choice: ";
        cin >> choice;

        system("cls");

        // switch statement to call the functions from the class Playlist and if the user wants to exit
        switch (choice) {
            // allows user to add a song with its artist and duration
            case '1':
                cout << "\nCHOICE: You have chosen to add a song!\n\n";
                cout << "Enter the Song ID: ";
                cin >> inputID;
                cout << "Enter the title of the song: ";
                cin.ignore();
                getline(cin, inputTitle);
                cout << "Enter the artist/s of the song: ";
                getline(cin, inputArtists);
                cout << "Enter the duration of the song (in seconds): ";
                cin >> inputDuration;
                openPlaylist.addSong(inputTitle, inputArtists, inputDuration, inputID);
                break;
            //allows user to delete a song
            case '2':
                cout << "\nCHOICE: You have chosen to remove a song!\n\n";
                cout << "Enter the title of the song: ";
                cin.ignore();
                getline(cin, inputTitle);
                cout << "Enter the Song ID: ";
                cin >> inputID;
                openPlaylist.removeSong(inputTitle, inputID);
                break;
            // allows user to play next song
            case '3':
                cout << "\nCHOICE: You have chosen to play the next song in the playlist!\n\n";
                openPlaylist.playNextSong();
                break;
            // allows user to view playlist
            case '4':
                cout << "\nCHOICE: You have chosen to view your playlist!\n\n";
                openPlaylist.viewPlaylist();
                break;
            //allows user to shuffle playlist and it will also show your shuffled playlist
            case '5':
                cout << "\nCHOICE: You have chosen to shuffle your playlist!\n\n";
                openPlaylist.shufflePlaylist();
                openPlaylist.viewPlaylist();
                break;
            //allows user to quit playlist
            case '6':
                cout << "\nCHOICE: Thank you for managing your playlist!\n\n";
                return 0;
            // tells user that they input an invalid choice
            default:
                cout << "\nERROR: Invalid choice. Please try again.\n\n";
        }
    }

    return 0;
}
