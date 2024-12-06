#include <bits/stdc++.h>

using namespace std;

struct MovieNode {
    string movieName;
    string showTime;
    int totalSeats;
    int availableSeats;
    MovieNode *next;
    MovieNode *prev;

    MovieNode(string name, string time, int seats)
        : movieName(name), showTime(time), totalSeats(seats), availableSeats(seats), next(NULL), prev(NULL) {}
};

class MovieList {
public:
    MovieNode *head;
    MovieNode *tail;

    MovieList() : head(NULL), tail(NULL) {}

    void addMovie(string name, string time, int seats) {
        MovieNode *newMovie = new MovieNode(name, time, seats);
        if (!head) {
            head = tail = newMovie;
        } else {
            tail->next = newMovie;
            newMovie->prev = tail;
            tail = newMovie;
        }
        cout << "\n[Success] Movie added successfully!\n";
    }

    void deleteMovie(string name) {
        MovieNode *temp = head;
        while (temp) {
            if (temp->movieName == name) {
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (temp == head) head = temp->next;
                if (temp == tail) tail = temp->prev;
                delete temp;
                cout << "\n[Deleted] Movie deleted successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "\n[Warning] Movie not found.\n";
    }

    void searchMovieByShowtime(string showtime) {
        MovieNode *temp = head;
        bool found = false;
        while (temp) {
            if (temp->showTime == showtime) {
                cout << "\n[Movie] Name: " << temp->movieName
                     << "\n  Showtime: " << temp->showTime
                     << "\n  Available Seats: " << temp->availableSeats << "/" << temp->totalSeats << "\n";
                found = true;
            }
            temp = temp->next;
        }
        if (!found) cout << "\n[Warning] No movies found at this showtime.\n";
    }

    void displayMovies() {
        if (!head) {
            cout << "\n[Warning] No movies available.\n";
            return;
        }
        cout << "\n[Available Movies]:\n";
        cout << endl;
        MovieNode *temp = head;
        while (temp) {
            cout << "[Film] " << setw(30) << left << temp->movieName
                 << " | Showtime: " << setw(10) << left << temp->showTime
                 << " | Available Seats: " << temp->availableSeats << "/" << temp->totalSeats << "\n";
            temp = temp->next;
        }
    }

    MovieNode *searchMovie(string name) {
        MovieNode *temp = head;
        while (temp) {
            if (temp->movieName == name) return temp;
            temp = temp->next;
        }
        return NULL;
    }
};

class TicketQueue {
public:
    queue<string> q;

    void enqueueUser(string userName) {
        q.push(userName);
        cout << "\n[Wait] No seats available. You are added to the waitlist.\n";
    }

    void dequeueUser() {
        if (!q.empty()) {
            cout << "\n[Serve User] " << q.front() << "\n";
            q.pop();
        }
    }

    void displayQueue() {
        if (q.empty()) {
            cout << "\n[No Waiting] No users in the waiting queue.\n";
            return;
        }
        cout << "\n[Wait] Waiting Queue:\n";
        queue<string> temp = q;
        while (!temp.empty()) {
            cout << "[User] " << temp.front() << "\n";
            temp.pop();
        }
    }
};

string selectCinemaHall() {
    cout << "\n[Movie] Select a cinema hall:\n";
    cout << "------------------------------------\n";
    cout << "1. STAR Cineplex, Mirpur 1\n";
    cout << "2. STAR Cineplex, Gulshan 1\n";
    cout << "3. STAR Cineplex, Bashundhara\n";
    cout << "4. Modhumita Cinema Hall\n";
    cout << "5. Rupban Cinema Hall\n";
    cout << "------------------------------------\n";
    cout << "Enter your choice (1-5): ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: return "STAR Cineplex, Mirpur 1";
    case 2: return "STAR Cineplex, Gulshan 1";
    case 3: return "STAR Cineplex, Bashundhara";
    case 4: return "Modhumita Cinema Hall";
    case 5: return "Rupban Cinema Hall";
    default:
        cout << "\n[Warning] Invalid choice. Try again.\n";
        return selectCinemaHall();
    }
}

bool adminLogin() {
    string username, password;
    const string correctUsername = "jpa";
    const string correctPassword = "654";
    int attempts = 3;

    while (attempts > 0) {
        cout << "\n[Login] Admin Login\n";
        cout << "------------------------------------\n";
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        cin >> password;

        if (username == correctUsername && password == correctPassword) {
            return true;
        } else {
            cout << "\n[Error] Incorrect credentials. You have " << --attempts << " attempts remaining.\n";
            if (attempts == 0) {
                cout << "[Denied] Access denied. Exiting...\n";
                return false;
            }
        }
    }
    return false;
}

void displayCinemaHall(string cinemaHall) {
    cout << "\n------------------------------------\n";
    cout << "[Movie] Cinema Hall: " << cinemaHall << "\n";
    cout << "------------------------------------\n";
}

void adminPortal(map<string, MovieList> &movieLists, map<string, TicketQueue> &ticketQueues) {
    if (!adminLogin()) {
        return;
    }

    string cinemaHall = selectCinemaHall();
    MovieList &movieList = movieLists[cinemaHall];

    displayCinemaHall(cinemaHall);

    int choice;
    do {
        cout << "\n[Admin Portal]\n";
        cout << "------------------------------------\n";
        cout << "1. Add Movie\n";
        cout << "2. Delete Movie\n";
        cout << "3. Search Movie by Showtime\n";
        cout << "4. View Available Movies\n";
        cout << "5. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, time;
            int seats;
            cout << "\nEnter movie name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter showtime: ";
            getline(cin, time);
            cout << "Enter total seats: ";
            cin >> seats;
            movieList.addMovie(name, time, seats);
            break;
        }
        case 2: {
            string name;
            cout << "\nEnter movie name to delete: ";
            cin.ignore();
            getline(cin, name);
            movieList.deleteMovie(name);
            break;
        }
        case 3: {
            string time;
            cout << "\nEnter showtime: ";
            cin.ignore();
            getline(cin, time);
            movieList.searchMovieByShowtime(time);
            break;
        }
        case 4:
            movieList.displayMovies();
            break;
        case 5:
            cout << "\n[Exit] Exiting Admin Portal...\n";
            break;
        default:
            cout << "\n[Warning] Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

void userPortal(map<string, MovieList> &movieLists, map<string, TicketQueue> &ticketQueues) {
    string cinemaHall = selectCinemaHall();
    MovieList &movieList = movieLists[cinemaHall];
    TicketQueue &ticketQueue = ticketQueues[cinemaHall];

    displayCinemaHall(cinemaHall);

    int choice;
    do {
        cout << "\n[User Portal]\n";
        cout << "------------------------------------\n";
        cout << "1. Book Ticket\n";
        cout << "2. Search Movie by Showtime\n";
        cout << "3. Cancel Ticket\n";
        cout << "4. View Available Movies\n";
        cout << "5. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string userName, movieName;
            cout << "\nEnter your name: ";
            cin.ignore();
            getline(cin, userName);
            cout << "Enter movie name: ";
            getline(cin, movieName);

            MovieNode *movie = movieList.searchMovie(movieName);
            if (movie) {
                if (movie->availableSeats > 0) {
                    movie->availableSeats--;
                    cout << "\n[Success] Ticket booked successfully for " << userName << "!\n";
                } else {
                    ticketQueue.enqueueUser(userName);
                }
            } else {
                cout << "\n[Warning] Movie not found.\n";
            }
            break;
        }
        case 2: {
            string time;
            cout << "\nEnter showtime: ";
            cin.ignore();
            getline(cin, time);
            movieList.searchMovieByShowtime(time);
            break;
        }
        case 3: {
            string userName, movieName;
            cout << "\nEnter your name: ";
            cin.ignore();
            getline(cin, userName);
            cout << "Enter movie name: ";
            getline(cin, movieName);

            MovieNode *movie = movieList.searchMovie(movieName);
            if (movie) {
                if (movie->availableSeats < movie->totalSeats) {
                    movie->availableSeats++;
                    cout << "\n[Success] Ticket canceled successfully for " << userName << "!\n";
                    ticketQueue.dequeueUser();
                } else {
                    cout << "\n[Warning] No booked tickets to cancel.\n";
                }
            } else {
                cout << "\n[Warning] Movie not found.\n";
            }
            break;
        }
        case 4:
            movieList.displayMovies();
            break;
        case 5:
            cout << "\n[Exit] Exiting User Portal...\n";
            break;
        default:
            cout << "\n[Warning] Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

int main() {
    map<string, MovieList> movieLists;
    map<string, TicketQueue> ticketQueues;

    int choice;
    do {
        cout << "\n[Movie Ticket Booking System]\n";
        cout << "------------------------------------\n";
        cout << "1. Admin Portal\n";
        cout << "2. User Portal\n";
        cout << "3. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            adminPortal(movieLists, ticketQueues);
            break;
        case 2:
            userPortal(movieLists, ticketQueues);
            break;
        case 3:
            cout << "\n[Exit] Thank you for using the Movie Ticket Booking System. Goodbye!\n";
            break;
        default:
            cout << "\n[Warning] Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
