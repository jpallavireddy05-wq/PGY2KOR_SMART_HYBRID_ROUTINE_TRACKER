#include <iostream>
#include <tuple>
#include <array>
#include <string_view>
#include <utility>
#include "ReminderService.h"

using namespace std;

struct MenuItem {
    int option;
    string_view label;
};

constexpr array<MenuItem, 6> reminderMenu {{
    {1, "Start Reminder Service"},
    {2, "Stop Reminder Service"},
    {3, "View Scheduled Notifications"},
    {4, "Execute Notifications"},
    {5, "Add Reminder Callback"},
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
            ([&]{
                if (choice == reminderMenu[I].option) 
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

void ReminderService::startService()
{
    cout << "\nReminder Service Started.\n";
}

void ReminderService::stopService()
{
    cout << "\nReminder Service Stopped.\n";
}

void ReminderService::viewNotifications()
{
    cout << "\nScheduled Notifications:\n";
    for (auto& n : notifications)
        cout << "- " << n << "\n";
}

void ReminderService::executeNotifications()
{
    cout << "\nExecuting Notifications...\n";
    for (auto& n : notifications)
        cout << ">> " << n << "\n";
}

void ReminderService::addCallback()
{
    string msg;
    cout << "\nEnter Reminder Message : ";
    cin.ignore();
    getline(cin, msg);
    notifications.push_back(msg);
    cout << "Reminder Callback Added.\n";
}

void ReminderService::menu()
{
    int choice;
    do {
        cout << "\n=========================================\n";
        cout << "        REMINDER MANAGEMENT\n";
        cout << "=========================================\n";

        for (auto& item : reminderMenu)
            cout << item.option << ". " << item.label << "\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        dispatch(choice,
            [&]{ startService(); },
            [&]{ stopService(); },
            [&]{ viewNotifications(); },
            [&]{ executeNotifications(); },
            [&]{ addCallback(); },
            [&]{ /* Back */ }
        );

    } while (choice != 0);
}
