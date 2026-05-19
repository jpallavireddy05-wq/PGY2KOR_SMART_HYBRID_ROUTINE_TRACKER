#include <iostream>
#include <array>
#include <string_view>
#include <tuple>
#include <utility>

#include "RoutineManager.h"
#include "ReminderService.h"
#include "ReportManager.h"
#include "DataManager.h"

using namespace std;
struct MenuEntry {
    int option;
    string_view label;
};

constexpr array<MenuEntry, 5> mainMenu {{
    {1, "Routine Management"},
    {2, "Reminder Management"},
    {3, "Statistics & Reports"},
    {4, "Data Management"},
    {0, "Exit"}
}};

namespace {
    template<typename... Actions>
    void dispatch(int choice, Actions&&... actions)
    {
        auto actionTuple = make_tuple(std::forward<Actions>(actions)...);
        constexpr size_t N = sizeof...(Actions);
        bool executed = false;

        [&]<size_t... I>(index_sequence<I...>) {
            (
                [&]{
                    if (choice == mainMenu[I].option) {
                        get<I>(actionTuple)();
                        executed = true;
                    }
                }(),
            ...);
        }(make_index_sequence<N>{});

        if (!executed)
            cout << "\nInvalid Choice.\n";
    }
}


int main()
{
    RoutineManager routineManager;
    ReminderService reminderService;
    ReportManager reportManager;
    DataManager dataManager;

    int choice;

    do {
        cout << "\n=========================================\n";
        cout << "     SMART DAILY ROUTINE TRACKER\n";
        cout << "=========================================\n";

        for (auto& item : mainMenu)
            cout << item.option << ". " << item.label << "\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        dispatch(choice,
            [&]{ routineManager.menu(); },     
            [&]{ reminderService.menu(); },    
            [&]{ reportManager.menu(); },      
            [&]{ dataManager.menu(); },        
            [&]{ cout << "\nThank You...\n"; } 
        );

    } while (choice != 0);

    return 0;
}
