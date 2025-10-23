# 🩺 MedFiles

**MedFiles** is a C-based console application designed to manage patient and appointment records for small healthcare centres or clinics.  It provides efficient CRUD (Create, Read, Update, Delete) operations for both patients and appointments, ensuring organized and accessible medical data.

---

## 📘 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [How to Run](#how-to-run)
- [Sample Operations](#sample-operations)
- [Future Improvements](#future-improvements)
- [Contributors](#contributors)
- [License](#license)

---

## 🩹 Overview

 MedFiles is a C-based console system for hospital management, providing secure staff login with **SHA256 encryption.** Key features include managing patient records in CSV, booking appointments, generating patient-specific **PDF prescriptions**, and handling billing. Built with sha256.h for security and pdfgen.h for PDF creation, functionalities are role-specific for admins, medical, and support staff.

---

## ⚙️ Key Features 

### 👩‍💼 Admin Mode

1. Add, edit, and view patient, doctor, and staff information.  
2. Manage ambulance services by adding or updating hospital ambulance details.

### 🩺 Medical Staff Mode

1. Maintain personal patient lists — each doctor can view and add patients unique to their account.  Automatically generates unique IDs for new patients.  
2. Search and track patient history by ID.  
3. Add additional notes on patient history and **generate prescriptions as PDF**.  
4. View scheduled appointments.

### 🧑‍🔧 Support Staff Mode

1. Access and manage the list of ambulances assigned to the hospital.  
2. Book or unbook ambulance services.  
3. View and manage lab tests, and compute total cabin and lab bills.  
4. Handle appointment bookings and cancellations for doctors and medical staff.  
5. Access the complete billing history of any patient.

### 🧠 Overall Highlights

✅ Persistent file-based data storage  
✅ SHA256-based password system  
✅ Simple text-based interface  
✅ Modular code organization (easy to extend and maintain)

--- 

## 🚀 How to Run

### 🧩 Step 1: Clone the Repository

Open your terminal or command prompt and run the following command:

`git clone https://github.com/Loona6/MedFiles.git

### 🧩 Step 2: Open the Project in Code::Blocks

1. Launch **Code::Blocks**.
2. Click **File → Open**.
3. Browse to the cloned folder and select **`MedFiles.cbp`**.

### 🧩 Step 3: Build and Run the Project

- Press **F9** or click **Build and Run** in Code::Blocks.
- The program will compile and execute within the IDE.

### ⚙️ _Optional: Run via Terminal (without Code::Blocks)_

If you prefer using the terminal or another compiler:
`g++ main.cpp -o MedFiles ./MedFiles`

---

## 🔮 Future Improvements

- GUI version using C++ or Qt
- Integration with a database (MySQL / SQLite)
- Exporting patient data as PDF or CSV
-  Advanced security features and integration

---

## 👩‍💻 Contributors



---

## 🪪 License

This project is for **academic purposes only** and is not intended for commercial use.  
All source code and materials are shared under the terms of this repository.


