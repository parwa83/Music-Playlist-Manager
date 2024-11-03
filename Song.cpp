#include <iostream>
#include <string>

class Song {
public:
    std::string title;
    std::string artist;
    double duration;

    Song(std::string title = "", std::string artist = "", double duration = 0.0)
        : title(title), artist(artist), duration(duration) {}

    void display() const {
        std::cout << "Title: " << title << ", Artist: " << artist << ", Duration: " << duration << " mins\n";
    }
};
