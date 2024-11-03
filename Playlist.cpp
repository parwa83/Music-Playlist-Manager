#include "Song.cpp"
#include <iostream>
#include <fstream>

class Node {
public:
    Song song;
    Node* next;

    Node(const Song& song) : song(song), next(nullptr) {}
};

class Playlist {
private:
    Node* head;
    int count;

public:
    Playlist() : head(nullptr), count(0) {}

    ~Playlist() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addSong(const Song& song, int position = -1) {
        Node* newNode = new Node(song);
        if (position <= 0 || position >= count) {
            if (!head) head = newNode;
            else {
                Node* temp = head;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
            }
        } else {
            Node* temp = head;
            for (int i = 0; i < position - 1; ++i) temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }
        ++count;
    }

    bool removeSong(const std::string& title) {
        Node* temp = head;
        Node* prev = nullptr;
        while (temp && temp->song.title != title) {
            prev = temp;
            temp = temp->next;
        }
        if (!temp) return false;

        if (!prev) head = temp->next;
        else prev->next = temp->next;

        delete temp;
        --count;
        return true;
    }

    void displayPlaylist() const {
        Node* temp = head;
        int pos = 1;
        double totalDuration = 0;
        while (temp) {
            std::cout << pos << ". ";
            temp->song.display();
            totalDuration += temp->song.duration;
            temp = temp->next;
            ++pos;
        }
        std::cout << "Total Duration: " << totalDuration << " mins\n";
    }

    void reorderSongs(int fromPos, int toPos) {
        if (fromPos < 1 || toPos < 1 || fromPos > count || toPos > count) return;
        Node* prevFrom = nullptr, *from = head;
        for (int i = 1; i < fromPos; ++i) { prevFrom = from; from = from->next; }

        if (prevFrom) prevFrom->next = from->next;
        else head = from->next;

        if (toPos == 1) {
            from->next = head;
            head = from;
        } else {
            Node* prevTo = nullptr, *to = head;
            for (int i = 1; i < toPos; ++i) { prevTo = to; to = to->next; }
            prevTo->next = from;
            from->next = to;
        }
    }

    void reversePlaylist() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    Node* searchSong(const std::string& keyword) const {
        Node* temp = head;
        int pos = 1;
        while (temp) {
            if (temp->song.title == keyword || temp->song.artist == keyword) {
                std::cout << "Found at position: " << pos << "\n";
                return temp;
            }
            temp = temp->next;
            ++pos;
        }
        std::cout << "Song not found.\n";
        return nullptr;
    }

    void savePlaylist(const std::string& filename) const {
        std::ofstream file(filename);
        Node* temp = head;
        while (temp) {
            file << temp->song.title << "," << temp->song.artist << "," << temp->song.duration << "\n";
            temp = temp->next;
        }
        file.close();
    }

    void loadPlaylist(const std::string& filename) {
        std::ifstream file(filename);
        std::string title, artist;
        double duration;
        char delimiter;
        while (file >> title >> delimiter >> artist >> delimiter >> duration) {
            addSong(Song(title, artist, duration));
        }
        file.close();
    }
};
