#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

struct User {
    string username;
    string password;
};

class UserManager {
protected:
    vector<User> users;

public:
    void addUser() {
        User u;
        cout << "Enter username: ";
        cin >> u.username;
        cout << "Enter password: ";
        cin >> u.password;
        
        users.push_back(u);
        cout << "User added.\n";
    }

    void viewUsers() {
        if (users.empty()) {
            cout << "No users to display.\n";
            return;
        }
        cout << "[\n";
        for (size_t i = 0; i < users.size(); ++i) {
            cout << "  {\n";
            cout << "    \"username\": \"" << users[i].username << "\",\n";
            cout << "    \"password\": \"" << users[i].password << "\"\n";
            cout << "  }";
            if (i != users.size() - 1) cout << ",";
            cout << "\n";
        }
        cout << "]\n";
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error writing to " << filename << "\n";
            return;
        }
        file << "[\n";
        for (size_t i = 0; i < users.size(); ++i) {
            file << "  {\n";
            file << "    \"username\": \"" << users[i].username << "\",\n";
            file << "    \"password\": \"" << users[i].password << "\"\n";
            file << "  }";
            if (i != users.size() - 1) file << ",";
            file << "\n";
        }
        file << "]\n";
        file.close();
        cout << "Saved to " << filename << "\n";
    }

    void loadFromFile(const string& filename) {
        users.clear();
        ifstream file(filename);
        if (!file) return;
        string line;
        while (getline(file, line)) {
            if (line.find("\"username\"") != string::npos) {
                User u;
                size_t start = line.find(":") + 3;
                size_t end = line.find_last_of("\"");
                u.username = line.substr(start, end - start);

                getline(file, line); // password line
                start = line.find(":") + 3;
                end = line.find_last_of("\"");
                u.password = line.substr(start, end - start);

                users.push_back(u);
            }
        }
        file.close();
    }

    void exportToMongo(const string& db, const string& collection, const string& filename) {
        saveToFile(filename);
        string cmd = "mongoimport --db " + db + " --collection " + collection + " --file " + filename + " --jsonArray";
        int result = system(cmd.c_str());
        if (result == 0)
            cout << "Exported to MongoDB (" << db << "." << collection << ")\n";
        else
            cout << "MongoDB export failed.\n";
    }
};

class StaffManager : public UserManager {
public:
    bool login(const string& username, const string& password) {
        loadFromFile("staff.json");
        for (const auto& u : users) {
            if (u.username == username && u.password == password)
                return true;
        }
        return false;
    }

    void run() {
        UserManager userManager; // manage only normal users
        while (true) {
            cout << "\n👤 Staff Menu:\n1. Add User\n2. Export Users (JSON)\n3. Export Users (MongoDB)\n4. Exit\nChoice: ";
            int ch;
            cin >> ch;
            switch (ch) {
                case 1: userManager.addUser(); break;
                case 2: userManager.saveToFile("users.json"); break;
                case 3: userManager.exportToMongo("loginDB", "users", "users.json"); break;
                case 4: return;
                default: cout << "Invalid choice.\n";
            }
        }
    }
};

class AdminManager {
    UserManager userManager;
    UserManager staffManager;

public:
    void run() {
        while (true) {
            cout << "\nAdmin Menu:\n1. Add User\n2. Add Staff\n3. View Users\n4. View Staff\n";
            cout << "5. Export Users (JSON)\n6. Export Staff (JSON)\n7. Export Users (MongoDB)\n";
            cout << "8. Export Staff (MongoDB)\n9. Exit\nChoice: ";
            int ch;
            cin >> ch;
            switch (ch) {
                case 1: userManager.addUser(); break;
                case 2: staffManager.addUser(); break;
                case 3: userManager.viewUsers(); break;
                case 4: staffManager.viewUsers(); break;
                case 5: userManager.saveToFile("users.json"); break;
                case 6: staffManager.saveToFile("staff.json"); break;
                case 7: userManager.exportToMongo("loginDB", "users", "users.json"); break;
                case 8: staffManager.exportToMongo("loginDB", "staff", "staff.json"); break;
                case 9: return;
                default: cout << "Invalid choice.\n";
            }
        }
    }
};

int main() {
    cout << R"(
 __  __ _____ _   _ _   _ 
|  \/  | ____| \ | | | | |
| |\/| |  _| |  \| | | | |
| |  | | |___| |\  | |_| |
|_|  |_|_____|_| \_|\___/
)";
    cout << "\nLogin as 'admin' or 'staff': ";
    string role;
    cin >> role;

    if (role == "admin") {
        string pass;
        cout << "Enter admin password: ";
        cin >> pass;
        if (pass == "admin") {
            AdminManager a;
            a.run();
        } else {
            cout << "Incorrect password.\n";
        }
    } else if (role == "staff") {
        string user, pass;
        cout << "Enter staff username: ";
        cin >> user;
        cout << "Enter staff password: ";
        cin >> pass;
        StaffManager s;
        if (s.login(user, pass)) {
            cout << "Login successful.\n";
            s.run();
        } else {
            cout << "Login failed.\n";
        }
    } else {
        cout << "Invalid role.\n";
    }

    return 0;
}
