#include "Playlist.cpp"
#include <iostream>
using namespace std;
void displayMenu() {
    cout << "\nMusic Playlist Manager\n";
    cout << "1. Add Song\n";
    cout << "2. Remove Song\n";
    cout << "3. Display Playlist\n";
    cout << "4. Reorder Songs\n";
    cout << "5. Reverse Playlist\n";
    cout << "6. Search Song\n";
    cout << "7. Save Playlist\n";
    cout << "8. Load Playlist\n";
    cout << "9. Exit\n";
}

int main() {
    Playlist playlist;
    int choice;

    while (true) {
        displayMenu();
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            string title, artist;
            double duration;
            int position;
            cout << "Enter title, artist, and duration: ";
            cin >> title >> artist >> duration;
            cout << "Enter position (or -1 to add at end): ";
            cin >> position;
            playlist.addSong(Song(title, artist, duration), position);
        }
        else if (choice == 2) {
            string title;
            cout << "Enter title of song to remove: ";
            cin >> title;
            if (playlist.removeSong(title)) cout << "Song removed.\n";
            else cout << "Song not found.\n";
        }
        else if (choice == 3) playlist.displayPlaylist();
        else if (choice == 4) {
            int fromPos, toPos;
            cout << "Enter from and to positions: ";
            cin >> fromPos >> toPos;
            playlist.reorderSongs(fromPos, toPos);
        }
        else if (choice == 5) playlist.reversePlaylist();
        else if (choice == 6) {
            string keyword;
            cout << "Enter title or artist to search: ";
            cin >> keyword;
            playlist.searchSong(keyword);
        }
        else if (choice == 7) {
            string filename;
            cout << "Enter filename to save: ";
            cin >> filename;
            playlist.savePlaylist(filename);
        }
        else if (choice == 8) {
            string filename;
            cout << "Enter filename to load: ";
            cin >> filename;
            playlist.loadPlaylist(filename);
        }
        else if (choice == 9) break;
        
        else cout << "Invalid choice. Try again.\n";
    }

    return 0;
}
