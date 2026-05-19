#include <iostream>
#include <tuple>
#include <array>
#include <string_view>
#include <utility>
#include "RoutineManager.h"

using namespace std;

struct MenuItem {
    int option;
    string_view label;
};

constexpr array<MenuItem, 10> routineMenu {{
    {1, "Add New Routine"},
    {2, "View All Routines"},
    {3, "View Pending Routines"},
    {4, "View Completed Routines"},
    {5, "Mark Routine as Completed"},
    {6, "Update Priority"},
    {7, "Categorize Routine"},
    {8, "Delete Routine"},
    {9, "Search Routine"},
    {0, "Back"}
}};


namespace {
    template<typename... Actions>
    void dispatch(int choice, Actions&&... actions)
    {
        auto actionsTuple = make_tuple(std::forward<Actions>(actions)...);
        constexpr size_t N = sizeof...(Actions);
        bool executed = false;

        [&]<size_t... I>(index_sequence<I...>)
        {
            ([&]{
                if (choice == routineMenu[I].option) 
                {
                    get<I>(actionsTuple)();
                    executed = true;
                }
            }(), ...);
        }(make_index_sequence<N>{});

        if (!executed)
            cout << "Invalid Choice.\n";
    }
}

void RoutineManager::addRoutine()
{
    Routine r;
    cout << "\nEnter ID : ";
    cin >> r.id;
    cin.ignore();

    cout << "Enter Title : ";
    getline(cin, r.title);

    cout << "Enter Category : ";
    getline(cin, r.category);

    cout << "Enter Priority : ";
    getline(cin, r.priority);

    r.completed = false;
    routines.push_back(r);

    cout << "\nRoutine Added.\n";
}

void RoutineManager::viewRoutines()
{
    cout << "\n========== ALL ROUTINES ==========\n";
    for (auto& r : routines) {
        cout << "\nID       : " << r.id;
        cout << "\nTitle    : " << r.title;
        cout << "\nCategory : " << r.category;
        cout << "\nPriority : " << r.priority;
        cout << "\nStatus   : " << (r.completed ? "Completed" : "Pending");
        cout << "\n-----------------------------\n";
    }
}

void RoutineManager::viewPending()
{
    cout << "\n========== PENDING ROUTINES ==========\n";
    for (auto& r : routines)
        if (!r.completed)
            cout << r.id << " - " << r.title << "\n";
}

void RoutineManager::viewCompleted()
{
    cout << "\n========== COMPLETED ROUTINES ==========\n";
    for (auto& r : routines)
        if (r.completed)
            cout << r.id << " - " << r.title << "\n";
}

void RoutineManager::markCompleted()
{
    int id;
    cout << "\nEnter Routine ID : ";
    cin >> id;

    for (auto& r : routines) {
        if (r.id == id) {
            r.completed = true;
            cout << "Routine Marked Completed.\n";
            return;
        }
    }
    cout << "Routine Not Found.\n";
}

void RoutineManager::updatePriority()
{
    int id;
    cout << "\nEnter Routine ID : ";
    cin >> id;
    cin.ignore();

    for (auto& r : routines)
    {
        if (r.id == id) 
        {
            cout << "Enter New Priority : ";
            getline(cin, r.priority);
            cout << "Priority Updated.\n";
            return;
        }
    }
    cout << "Routine Not Found.\n";
}

void RoutineManager::categorizeRoutine()
{
    int id;
    cout << "\nEnter Routine ID : ";
    cin >> id;
    cin.ignore();

    for (auto& r : routines) 
    {
        if (r.id == id) {
            cout << "Enter New Category : ";
            getline(cin, r.category);
            cout << "Category Updated.\n";
            return;
        }
    }
    cout << "Routine Not Found.\n";
}

void RoutineManager::deleteRoutine()
{
    int id;
    cout << "\nEnter Routine ID : ";
    cin >> id;

    for (int i = 0; i < static_cast<int>(routines.size()); i++) 
    {
        if (routines[i].id == id) {
            routines.erase(routines.begin() + i);
            cout << "Routine Deleted.\n";
            return;
        }
    }
    cout << "Routine Not Found.\n";
}

void RoutineManager::searchRoutine()
{
    string keyword;
    cout << "\nEnter Title Keyword : ";
    cin.ignore();
    getline(cin, keyword);

    cout << "\n========== SEARCH RESULTS ==========\n";
    for (auto& r : routines) 
    {
        if (r.title.find(keyword) != string::npos)
            cout << r.id << " - " << r.title << " (" << (r.completed ? "Completed" : "Pending") << ")\n";
    }
}


void RoutineManager::menu()
{
    int choice;
    do {
        cout << "\n=========================================\n";
        cout << "        ROUTINE MANAGEMENT\n";
        cout << "=========================================\n";

        for (auto& item : routineMenu)
            cout << item.option << ". " << item.label << "\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        dispatch(choice,
            [&]{ addRoutine(); },
            [&]{ viewRoutines(); },
            [&]{ viewPending(); },
            [&]{ viewCompleted(); },
            [&]{ markCompleted(); },
            [&]{ updatePriority(); },
            [&]{ categorizeRoutine(); },
            [&]{ deleteRoutine(); },
            [&]{ searchRoutine(); },
            [&]{ /* Back */ }
        );

    } while (choice != 0);
}
