#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Define structure for appointment
struct Appointment {
    string date;
    string time;
    string service;
    string professional;
};

// Function to add appointment
void createAppointment(vector<Appointment> &appointments) {
    Appointment newAppointment;
    // Get input for new appointment
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> newAppointment.date;
    cout << "Enter time (HH:MM): ";
    cin >> newAppointment.time;
    cin.ignore(); // Ignore newline character
    cout << "Enter service: ";
    getline(cin, newAppointment.service);
    cout << "Enter professional: ";
    getline(cin, newAppointment.professional);
    // Add to appointments vector
    appointments.push_back(newAppointment);
}

// Function to display all appointments
void displayAppointments(const vector<Appointment> &appointments) {
    cout << "Appointments:\n";
    for(const auto& appointment : appointments) {
        cout << "Date: " << appointment.date 
             << ", Time: " << appointment.time
             << ", Service: " << appointment.service 
             << ", Professional: " << appointment.professional << endl;
    }
}

// Function to edit appointment
void editAppointment(vector<Appointment> &appointments) {
    string date, time;
    cout << "Enter the date of the appointment to edit (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter the time of the appointment to edit (HH:MM): ";
    cin >> time;
    cin.ignore(); // Ignore newline character

    for (auto& appointment : appointments) {
        if (appointment.date == date && appointment.time == time) {
            cout << "Enter new date (YYYY-MM-DD): ";
            cin >> appointment.date;
            cout << "Enter new time (HH:MM): ";
            cin >> appointment.time;
            cin.ignore(); // Ignore newline character
            cout << "Enter new service: ";
            getline(cin, appointment.service);
            cout << "Enter new professional: ";
            getline(cin, appointment.professional);
            cout << "Appointment updated successfully.\n";
            return;
        }
    }
    cout << "Appointment not found.\n";
}

// Function to delete appointment
void deleteAppointment(vector<Appointment> &appointments) {
    string date, time;
    cout << "Enter the date of the appointment to delete (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter the time of the appointment to delete (HH:MM): ";
    cin >> time;

    for (auto it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->date == date && it->time == time) {
            appointments.erase(it);
            cout << "Appointment deleted successfully.\n";
            return;
        }
    }
    cout << "Appointment not found.\n";
}

// Function to save appointments to file
void saveAppointments(const vector<Appointment> &appointments, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for(const auto& appointment : appointments) {
            file << appointment.date << " " << appointment.time << " "
                 << appointment.service << " " << appointment.professional << endl;
        }
        file.close();
        cout << "Appointments saved to " << filename << ".\n";
    } else {
        cerr << "Unable to open file for writing.\n";
    }
}

// Function to load appointments from file
void loadAppointments(vector<Appointment> &appointments, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        appointments.clear(); // Clear existing appointments
        Appointment appointment;
        while (file >> appointment.date >> appointment.time) {
            getline(file >> ws, appointment.service); // Read service with spaces
            getline(file >> ws, appointment.professional); // Read professional with spaces
            appointments.push_back(appointment);
        }
        file.close();
    } else {
        cerr << "Unable to open file for reading.\n";
    }
}

int main() {
    vector<Appointment> appointments;
    string filename = "appointments.txt"; // File to store appointments

    // Load appointments from file
    loadAppointments(appointments, filename);

    int choice;
    do {
        // Display menu
        cout << "\nAppointment Booking System\n";
        cout << "1. Add Appointment\n";
        cout << "2. View Appointments\n";
        cout << "3. Edit Appointment\n";
        cout << "4. Delete Appointment\n";
        cout << "5. Save Appointments\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAppointment(appointments);
                break;
            case 2:
                displayAppointments(appointments);
                break;
            case 3:
                editAppointment(appointments);
                break;
            case 4:
                deleteAppointment(appointments);
                break;
            case 5:
                saveAppointments(appointments, filename);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 6);

    return 0;
}
