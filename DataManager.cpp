#include <iostream>
#include <array>
#include <string_view>
#include <tuple>
#include <utility>

#include "DataManager.h"

using namespace std;

struct MenuItem {
    int option;
    string_view label;
};

constexpr array<MenuItem, 4> dataMenu {{
    {1, "Save Data"},
    {2, "Load Data"},
    {3, "Clear Data"},
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
            (
                [&]{
                    if (choice == dataMenu[I].option) {
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

void DataManager::saveData()
{
    cout << "\nData Saved Successfully.\n";
}

void DataManager::loadData()
{
    cout << "\nData Loaded Successfully.\n";
}

void DataManager::clearData()
{
    cout << "\nAll Data Cleared.\n";
}

void DataManager::menu()
{
    int choice;

    do {
        cout << "\n=========================================\n";
        cout << "          DATA MANAGEMENT\n";
        cout << "=========================================\n";

        for (auto& item : dataMenu)
            cout << item.option << ". " << item.label << "\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        dispatch(choice,
            [&]{ saveData(); },
            [&]{ loadData(); },
            [&]{ clearData(); },
            [&]{ /* Back */ }
        );

    } while (choice != 0);
}
