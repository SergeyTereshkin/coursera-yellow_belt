#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string b = " ";
    string command;
    int stop_count = 0;
    string st;
    vector<string> bus_stops;
    is >> command;
    if (command == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> b >> stop_count;
        q.bus = b;
        vector<string> new_stops;
        for (int i = 0; i < stop_count; i++) {
            string stop;
            is >> stop;
            new_stops.push_back(stop);
        }
        q.stops = new_stops;
    }
    else if (command == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> st;
        q.stop = st;
    }
    else if (command == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> b;
        q.bus = b;
    }
    else if (command == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop";
    }
    else {
        for (const auto& m : r.buses) {
            os << m << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    vector<string> stops;
    map<string, vector<string>> buses;
    string bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty()) {
        os << "No bus";
    }
    for (int i = 0; i < r.stops.size(); i++) {
        os << "Stop " << r.stops[i] << ": ";
        if (r.buses.at(r.stops[i]).size() == 1) {
            os << "no interchange";
        }
        else {
            for (const string& other_bus : r.buses.at(r.stops[i])) {
                if (other_bus != r.bus) {
                    os << other_bus << " ";
                }
            }
        }
        if (i != r.stops.size() - 1) {
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
        os << "No buses";
    }
    else {
        for (const auto& bus_item : r.buses_to_stops) {
            os << "Bus " << bus_item.first << ": ";
            for (const auto& stop : bus_item.second) {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse g = {};
        if (stops_to_buses.count(stop) == 0) {
            g.buses = {};
        }
        else {
            g.buses = stops_to_buses.at(stop);
        }
        return g;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse g;
        g.bus = bus;
        if (buses_to_stops.count(bus) == 0) {
            g.stops = {};
        }
        else {
            g.stops = buses_to_stops.at(bus);
            for (const auto& m : g.stops) {
                g.buses[m] = stops_to_buses.at(m);
            }
        }
        return g;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse g;
        g.buses_to_stops = buses_to_stops;
        return g;
    }
private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
