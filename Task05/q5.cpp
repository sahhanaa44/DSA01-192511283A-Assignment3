#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class Time {
    int seconds;

public:
    Time(int h = 0, int m = 0, int s = 0) {
        if (h < 0 || m < 0 || s < 0) throw invalid_argument("Negative time");
        seconds = h * 3600 + m * 60 + s;
    }

    Time& operator++() {
        ++seconds;
        return *this;
    }

    Time operator++(int) {
        Time old = *this;
        ++seconds;
        return old;
    }

    bool operator==(const Time& other) const {
        return seconds == other.seconds;
    }

    bool operator<(const Time& other) const {
        return seconds < other.seconds;
    }

    friend ostream& operator<<(ostream& os, const Time& t) {
        int h = t.seconds / 3600;
        int m = (t.seconds % 3600) / 60;
        int s = t.seconds % 60;
        return os << h << ':' << (m < 10 ? "0" : "") << m
                  << ':' << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
    vector<string> tracks;

public:
    explicit Playlist(vector<string> items) : tracks(std::move(items)) {}

    string& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(tracks.size()))
            throw out_of_range("Playlist index out of range");
        return tracks[static_cast<size_t>(index)];
    }

    const string& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(tracks.size()))
            throw out_of_range("Playlist index out of range");
        return tracks[static_cast<size_t>(index)];
    }

    int size() const { return static_cast<int>(tracks.size()); }
};

int main() {
    Time t(0, 59, 58);
    Time a = t++;
    Time b = ++t;
    cout << "a = " << a << "\nb = " << b << "\nt = " << t << '\n';
    cout << boolalpha << "a < b: " << (a < b) << '\n';

    Playlist playlist({"Track One", "Track Two", "Track Three"});
    cout << "Playing: " << playlist[0] << '\n';
    playlist[1] = "Updated Track";
    cout << "Updated: " << playlist[1] << '\n';

    try {
        cout << playlist[playlist.size()] << '\n';
    } catch (const out_of_range& e) {
        cout << "Error: " << e.what() << '\n';
    }
    return 0;
}
