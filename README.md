# User-Staff-Management-CPP
````markdown
# 👤 User & Staff Management System in C++

A simple and effective C++ console application for managing users and staff with support for JSON export and MongoDB integration. Built using core Object-Oriented Programming concepts.

---

## 🚀 Features

- 🔐 Role-based access: **Admin** and **Staff**
- 👥 Add and view **Users** and **Staff**
- 📂 Save user data to **JSON** files
- 🌐 Export data to **MongoDB** using `mongoimport`
- 🧠 Clean class structure using **OOP Principles**

---

## 🧑‍💻 User Roles

### 👑 Admin
- Password: `admin`
- Add/View Users and Staff
- Export to JSON and MongoDB

### 🧾 Staff
- Requires valid username & password (stored in `staff.json`)
- Add Users
- Export Users to JSON or MongoDB

---

## 📁 Files Used

| File         | Purpose                          |
|--------------|----------------------------------|
| `main.cpp`   | Source code                      |
| `users.json` | Stores added users               |
| `staff.json` | Stores staff credentials         |

---

## 🛠️ How to Use

### 🔧 Prerequisites

- C++ compiler (`g++`, `clang++`, etc.)
- MongoDB installed and running
- `mongoimport` command available

### ⚙️ Compile

```bash
g++ main.cpp -o usermanager
````

### ▶️ Run

```bash
./usermanager
```

---

## 🌐 MongoDB Export Example

Internally uses:

```bash
mongoimport --db loginDB --collection users --file users.json --jsonArray
```

Replace `users` with `staff` accordingly. Make sure MongoDB is running.

---

## 📄 Sample JSON Output

```json
[
  {
    "username": "john_doe",
    "password": "secret123"
  },
  {
    "username": "alice_01",
    "password": "mypassword"
  }
]
```

---

## 🧩 Object-Oriented Structure

* `UserManager`: Base class to manage users
* `StaffManager`: Inherits `UserManager`, adds login + staff menu
* `AdminManager`: Uses `UserManager` for users & staff

---

## 💡 Future Enhancements

* 🔐 Hash passwords for better security
* 🖥️ Add GUI (e.g., using Qt or web frontend)
* 🗄️ Use MongoDB C++ driver instead of `mongoimport`
* 📋 Add input validation & duplicate checks

---

## 📝 License

This project is licensed under the [MIT License](LICENSE).

---

## ✨ Author

**Made with 💻 by \[Shiwani YAduka]**

> Feel free to fork this project, improve it, and give a ⭐ if you found it useful!

```


