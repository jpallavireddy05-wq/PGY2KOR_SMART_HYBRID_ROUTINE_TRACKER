#include <iostream>
#include <array>
#include <string_view>
#include <tuple>
#include <utility>
#include "ReportManager.h"

using namespace std;

struct MenuItem {
    int option;
    string_view label;
};

constexpr array<MenuItem, 7> reportMenu {{
    {1, "Total Routines"},
    {2, "Completed Routines"},
    {3, "Pending Routines"},
    {4, "Completion Percentage"},
    {5, "Category-wise Report"},
    {6, "Priority-wise Report"},
    {0, "Back"}
}};

namespace {
    template<typename... Actions>
    void dispatch(int choice, Actions&&... actions)
    {
        auto actionsTuple = make_tuple(std::forward<Actions>(actions)...);
        constexpr size_t N = sizeof...(Actions);
        bool executed = false;

        [&]<size_t... I>(index_sequence<I...>) {
            (
                [&]{
                    if (choice == reportMenu[I].option) {
                        get<I>(actionsTuple)();
                        executed = true;
                    }
                }(),
            ...);
        }(make_index_sequence<N>{});

        if (!executed)
            cout << "Invalid Choice.\n";
    }
}

void ReportManager::menu()
{
    int choice;

    do {
        cout << "\n=========================================\n";
        cout << "        STATISTICS & REPORTS\n";
        cout << "=========================================\n";

        for (auto& item : reportMenu)
            cout << item.option << ". " << item.label << "\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        dispatch(choice,
            [&]{ cout << "\nTotal Routines Report.\n"; },
            [&]{ cout << "\nCompleted Routines Report.\n"; },
            [&]{ cout << "\nPending Routines Report.\n"; },
            [&]{ cout << "\nCompletion Percentage Report.\n"; },
            [&]{ cout << "\nCategory-wise Report.\n"; },
            [&]{ cout << "\nPriority-wise Report.\n"; },
            [&]{ /* Back */ }
        );

    } while (choice != 0);
}
